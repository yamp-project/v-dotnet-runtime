using System.Runtime.InteropServices;

namespace YAMP.Shared.Structs;

[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
public struct SdkInterface
{
    public IntPtr entityApi;
    public IntPtr pedApi;

    public IntPtr anyValueFactory;
    public IntPtr nativesFactory;

    public IntPtr GetLocalPlayer;

    public IntPtr LogDebug;
    public IntPtr LogInfo;
    public IntPtr LogWarn;
    public IntPtr LogError;

    public IntPtr GetCoreEventMetas;
    public IntPtr GetCoreEventArgs;
    public IntPtr EmitResourceEvent;
}
