using System.Runtime.InteropServices;

namespace YAMP.Shared.Structs;

[StructLayout(LayoutKind.Sequential)]
public struct CDict
{
    public UIntPtr size;
    public IntPtr keys;
    public IntPtr values;

    public string[] GetKeys()
    {
        if (keys == IntPtr.Zero || size == UIntPtr.Zero)
        {
            return [];
        }

        var length = (int)size;
        var result = new string[length];
        for (var i = 0; i < length; i++)
        {
            var ptr = Marshal.ReadIntPtr(keys, i * IntPtr.Size);
            result[i] = Marshal.PtrToStringAnsi(ptr) ?? string.Empty;
        }

        return result;
    }

    public CAnyValue[] GetValues()
    {
        if (values == IntPtr.Zero || size == UIntPtr.Zero)
        {
            return [];
        }

        var length = (int)size;
        var result = new CAnyValue[length];
        for (var i = 0; i < length; i++)
        {
            var ptr = Marshal.ReadIntPtr(values, i * IntPtr.Size);
            result[i] = Marshal.PtrToStructure<CAnyValue>(ptr);
        }

        return result;
    }
}
