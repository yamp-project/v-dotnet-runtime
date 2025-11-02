using System.Collections.Concurrent;
using System.Collections.Immutable;
using System.Linq.Expressions;
using System.Reflection;
using YAMP.Shared.Enums;
using YAMP.Shared.Implementations;

namespace YAMP.Shared.Services;

internal static class EventService
{
    private static readonly ConcurrentDictionary<CoreEventType, ImmutableArray<Action<object[]>>> CoreEvents = new();
    private static readonly MethodInfo GetTypeMethod = typeof(object).GetMethod("GetType")!;

    private static readonly MethodInfo GetConverterMethod =
        typeof(ConversionService).GetMethod(nameof(ConversionService.GetConverter),
            BindingFlags.Static | BindingFlags.Public)!;

    private static readonly ConstructorInfo InvalidCastCtor = typeof(InvalidCastException).GetConstructor([
        typeof(string)
    ])!;

    private static readonly MethodInfo StringFormatMethod = typeof(string).GetMethod("Format", [
        typeof(string), typeof(object), typeof(object)
    ])!;

    public static void RegisterCoreEvent(CoreEventType type, RegisteredCoreEvent coreEvent)
    {
        // TODO: @Lucas - Check core event signature using GetCoreEventArgs(obv. cache it at module startup)
        var fastInvoker = CreateFastInvoker(coreEvent.CoreEventAction);

        CoreEvents.AddOrUpdate(
            type,
            _ => [fastInvoker],
            (_, existingHandlers) => existingHandlers.Add(fastInvoker)
        );
    }

    public static void TriggerCoreEvent(CoreEventType type, params object[] args)
    {
        if (CoreEvents.TryGetValue(type, out var handlers))
        {
            foreach (var handler in handlers)
            {
                handler(args);
            }
        }
    }

    private static Action<object[]> CreateFastInvoker(Delegate targetDelegate)
    {
        var targetMethod = targetDelegate.Method;
        var parameters = targetMethod.GetParameters();
        var argsParameter = Expression.Parameter(typeof(object[]), "args");

        var callArguments = new Expression[parameters.Length];
        for (var i = 0; i < parameters.Length; i++)
        {
            var paramInfo = parameters[i];
            var targetType = paramInfo.ParameterType;
            var arrayAccess = Expression.ArrayIndex(argsParameter, Expression.Constant(i));

            var isNullable = !targetType.IsValueType || Nullable.GetUnderlyingType(targetType) != null;

            var converterVar = Expression.Variable(typeof(Func<object, object>), $"converter{i}");

            var conversionBlock = Expression.Block(
                targetType,
                [converterVar],
                Expression.Assign(converterVar,
                    Expression.Call(GetConverterMethod, Expression.Call(arrayAccess, GetTypeMethod),
                        Expression.Constant(targetType, typeof(Type)))),
                Expression.Condition(
                    Expression.NotEqual(converterVar, Expression.Constant(null)),
                    Expression.Convert(Expression.Invoke(converterVar, arrayAccess), targetType),
                    Expression.Convert(
                        Expression.Throw(Expression.New(
                            InvalidCastCtor,
                            Expression.Call(StringFormatMethod,
                                Expression.Constant("Cannot convert argument of type {0} to {1}."),
                                Expression.Call(arrayAccess, GetTypeMethod),
                                Expression.Constant(targetType, typeof(Type)))
                        ), targetType),
                        targetType
                    )
                )
            );

            var nullBlock = isNullable
                ? (Expression)Expression.Constant(null, targetType)
                : Expression.Convert(
                    Expression.Throw(
                        Expression.New(InvalidCastCtor,
                            Expression.Constant($"Cannot assign null to non-nullable value type {targetType.Name}.")),
                        targetType), targetType);

            var argumentProcessor = Expression.Condition(
                Expression.Equal(arrayAccess, Expression.Constant(null)),
                nullBlock,
                Expression.Condition(
                    Expression.TypeIs(arrayAccess, targetType),
                    Expression.Convert(arrayAccess, targetType),
                    conversionBlock
                )
            );

            callArguments[i] = argumentProcessor;
        }

        var callExpression = Expression.Call(Expression.Constant(targetDelegate.Target), targetMethod, callArguments);
        var lambda = Expression.Lambda<Action<object[]>>(callExpression, argsParameter);
        return lambda.Compile();
    }
}
