namespace YAMP.Shared.Enums;

public enum CType : byte
{
    CAny = 0,

    CInt64 = 1,
    CInt32 = 2,
    CInt16 = 3,
    CInt8 = 4,

    CUint64 = 5,
    CUint32 = 6,
    CUint16 = 7,
    CUint8 = 8,

    CDouble = 9,
    CFloat = 10,
    CBool = 11,

    CNull = 12,
    CString = 13,

    CAnyArray = 14,
    CArray = 15,
    CDict = 16,

    CVector = 17,
    CDate = 18
}
