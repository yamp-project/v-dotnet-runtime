using System.Collections.Concurrent;
using System.Linq.Expressions;

namespace YAMP.Shared.Services;

internal static class ConversionService
{
    private static readonly ConcurrentDictionary<(Type from, Type to), Func<object, object>> Converters = new();

    static ConversionService()
    {
        Register<string, int>(int.Parse);

        // TODO: @Lucas remove later on, its just there cause I was too lazy to properly implement the CArgParser
        // cause rn it just converts any CArray into object[]
        Register<object[], string[]>(objects => objects.Select(o => o.ToString() ?? string.Empty).ToArray());
    }

    private static void Register<TFrom, TTo>(Func<TFrom, TTo> converter)
    {
        var param = Expression.Parameter(typeof(object), "input");
        var conversion = Expression.Convert(
            Expression.Invoke(
                Expression.Constant(converter),
                Expression.Convert(param, typeof(TFrom))
            ),
            typeof(object)
        );

        var fastConverter = Expression.Lambda<Func<object, object>>(conversion, param).Compile();
        Converters[(typeof(TFrom), typeof(TTo))] = fastConverter;
    }

    public static Func<object, object>? GetConverter(Type from, Type to)
    {
        if (from == to)
        {
            return null;
        }

        Converters.TryGetValue((from, to), out var converter);
        return converter;
    }
}
