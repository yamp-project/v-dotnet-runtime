using System.Runtime.InteropServices;
using YAMP.Shared.Enums;

namespace YAMP.Shared.Structs;

[StructLayout(LayoutKind.Sequential)]
public struct CArray
{
    public byte type;
    public UIntPtr size;
    public IntPtr buffer;

    private IntPtr[] GetBufferPointers()
    {
        if (buffer == IntPtr.Zero || size == UIntPtr.Zero)
        {
            return [];
        }

        var length = (int)size;
        var pointers = new IntPtr[length];
        for (var i = 0; i < length; i++)
        {
            pointers[i] = Marshal.ReadIntPtr(buffer, i * IntPtr.Size);
        }

        return pointers;
    }

    public CAnyValue[] GetValues()
    {
        var pointers = GetBufferPointers();
        var values = new CAnyValue[pointers.Length];
        for (var i = 0; i < pointers.Length; i++)
        {
            values[i] = Marshal.PtrToStructure<CAnyValue>(pointers[i]);
        }

        return values;
    }

    public CType ValueType => (CType)type;
}
