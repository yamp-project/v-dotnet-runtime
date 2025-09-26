using System.Runtime.InteropServices;
using YAMP.Shared.Enums;

namespace YAMP.Shared.Structs;

[StructLayout(LayoutKind.Sequential)]
public struct CAnyValue
{
    public byte type;
    public AnyValueUnion value;

    [StructLayout(LayoutKind.Explicit)]
    public struct AnyValueUnion
    {
        [FieldOffset(0)] public long m_Int64;
        [FieldOffset(0)] public int m_Int32;
        [FieldOffset(0)] public short m_Int16;
        [FieldOffset(0)] public sbyte m_Int8;

        [FieldOffset(0)] public ulong m_Uint64;
        [FieldOffset(0)] public uint m_Uint32;
        [FieldOffset(0)] public ushort m_Uint16;
        [FieldOffset(0)] public byte m_Uint8;

        [FieldOffset(0)] public IntPtr m_Pointer;
        [FieldOffset(0)] public IntPtr m_String;

        [FieldOffset(0)] public double m_Double;
        [FieldOffset(0)] public float m_Float;
        [FieldOffset(0)] public bool m_Bool;

        [FieldOffset(0)] public IntPtr m_AnyArray;
        [FieldOffset(0)] public IntPtr m_Array;
        [FieldOffset(0)] public IntPtr m_Dict;
    }

    public CType ValueType => (CType)type;
}
