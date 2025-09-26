using System.Runtime.InteropServices;

namespace YAMP.Shared.Structs;

[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
public struct SdkResource
{
    private IntPtr name;
    private IntPtr type;
    private IntPtr path;
    private IntPtr mainFile;

    public string Name => Marshal.PtrToStringAnsi(name) ?? string.Empty;
    public string Path => Marshal.PtrToStringAnsi(path) ?? string.Empty;
    public string MainFile => Marshal.PtrToStringAnsi(mainFile) ?? string.Empty;
}
