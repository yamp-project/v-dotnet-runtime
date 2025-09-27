using System.Runtime.InteropServices;
using YAMP.Shared.Structs;

namespace YAMP.Shared.Core;

internal static class ServerLibrary
{
    [UnmanagedCallersOnly]
    private static unsafe void InitializeLibrary(SdkInterface* lookupTablePtr)
    {
    }
}
