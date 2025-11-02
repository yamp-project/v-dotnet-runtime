using System.Runtime.InteropServices;
using YAMP.Shared.Enums;
using YAMP.Shared.Structs;

namespace YAMP.Shared.Implementations;

internal static class CArgParser
{
    private static T ParseArgument<T>(CAnyValue arg)
    {
        var type = arg.ValueType;

        switch (type)
        {
            case CType.CInt64:
                return (T)(object)arg.value.m_Int64;
            case CType.CInt32:
                return (T)(object)arg.value.m_Int32;
            case CType.CInt16:
                return (T)(object)arg.value.m_Int16;
            case CType.CInt8:
                return (T)(object)arg.value.m_Int8;

            case CType.CUint64:
                return (T)(object)arg.value.m_Uint64;
            case CType.CUint32:
                return (T)(object)arg.value.m_Uint32;
            case CType.CUint16:
                return (T)(object)arg.value.m_Uint16;
            case CType.CUint8:
                return (T)(object)arg.value.m_Uint8;

            case CType.CDouble:
                return (T)(object)arg.value.m_Double;
            case CType.CFloat:
                return (T)(object)arg.value.m_Float;
            case CType.CBool:
                return (T)(object)arg.value.m_Bool;

            case CType.CNull:
                return default!;
            case CType.CString:
            {
                var strPtr = arg.value.m_String;
                var str = Marshal.PtrToStringAnsi(strPtr)!;

                return (T)(object)str;
            }

            case CType.CAnyArray:
            {
                var anyArrayPtr = arg.value.m_AnyArray;
                var anyArray = Marshal.PtrToStructure<CAnyArray>(anyArrayPtr);

                return (T)(object)ParseArguments(anyArray);
            }
            case CType.CArray:
            {
                var arrayPtr = arg.value.m_Array;
                var array = Marshal.PtrToStructure<CArray>(arrayPtr);

                return (T)(object)ParseArguments(array);
            }
            case CType.CDict:
            {
                var dictPtr = arg.value.m_Dict;
                var dict = Marshal.PtrToStructure<CDict>(dictPtr);

                var keys = dict.GetKeys();
                var values = dict.GetValues();

                var result = new Dictionary<string, object?>();

                for (var i = 0; i < keys.Length; i++)
                {
                    var key = keys[i];
                    var value = ParseArgument<object>(values[i]);

                    result[key] = value;
                }

                return (T)(object)result;
            }

            default:
                throw new NotSupportedException($"The CType '{type}' is not supported.");
        }
    }

    public static object[] ParseArguments(CAnyArray args)
    {
        var values = args.GetValues();
        var objects = new object[values.Length];

        for (var i = 0; i < values.Length; i++)
        {
            objects[i] = ParseArgument<object>(values[i]);
        }

        return objects;
    }

    private static object[] ParseArguments(CArray args)
    {
        var values = args.GetValues();
        var objects = new object[values.Length];
        for (var i = 0; i < values.Length; i++)
        {
            objects[i] = ParseArgument<object>(values[i]);
        }

        return objects;
    }
}
