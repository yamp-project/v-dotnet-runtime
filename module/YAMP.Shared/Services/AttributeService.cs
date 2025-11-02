using System.Reflection;

namespace YAMP.Shared.Services;

internal static class AttributeService
{
    public static void ScanClassInstanceAttributes(object instance)
    {
        ScanMethodAttributes(instance);
    }

    private static void ScanMethodAttributes(object instance)
    {
        var type = instance.GetType();
        var methods = type.GetMethods(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance |
                                      BindingFlags.Static);

        foreach (var method in methods)
        {
            var coreEventAttributes = method.GetCustomAttributes(typeof(Attributes.CoreEventAttribute), true);
            foreach (Attributes.CoreEventAttribute coreEventAttribute in coreEventAttributes)
            {
                var delegateType = GetDelegateType(method);
                var @delegate = method.IsStatic
                    ? Delegate.CreateDelegate(delegateType, method)
                    : Delegate.CreateDelegate(delegateType, instance, method);

                var coreEvent = new Implementations.RegisteredCoreEvent { CoreEventAction = @delegate };

                EventService.RegisterCoreEvent(coreEventAttribute.EventType, coreEvent);
            }
        }
    }

    private static Type GetDelegateType(MethodInfo method)
    {
        var parameters = method.GetParameters();
        var paramTypes = parameters.Select(p => p.ParameterType).ToArray();

        if (method.ReturnType == typeof(void))
        {
            return paramTypes.Length switch
            {
                0 => typeof(Action),
                1 => typeof(Action<>).MakeGenericType(paramTypes),
                2 => typeof(Action<,>).MakeGenericType(paramTypes),
                3 => typeof(Action<,,>).MakeGenericType(paramTypes),
                4 => typeof(Action<,,,>).MakeGenericType(paramTypes),

                _ => throw new NotSupportedException($"Too many parameters: {paramTypes.Length}")
            };
        }
        else
        {
            var allTypes = paramTypes.Concat([method.ReturnType]).ToArray();
            return allTypes.Length switch
            {
                1 => typeof(Func<>).MakeGenericType(allTypes),
                2 => typeof(Func<,>).MakeGenericType(allTypes),
                3 => typeof(Func<,,>).MakeGenericType(allTypes),
                4 => typeof(Func<,,,>).MakeGenericType(allTypes),

                _ => throw new NotSupportedException($"Too many parameters: {allTypes.Length}")
            };
        }
    }
}
