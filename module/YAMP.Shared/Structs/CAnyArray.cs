using System.Runtime.InteropServices;

namespace YAMP.Shared.Structs;

[StructLayout(LayoutKind.Sequential)]
public struct CAnyArray
{
    public byte size;
    public IntPtr buffer;

    private IntPtr[] GetBufferPointers()
    {
        if (buffer == IntPtr.Zero || size == 0)
        {
            return [];
        }

        var pointers = new IntPtr[size];
        for (var i = 0; i < size; i++)
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
}
