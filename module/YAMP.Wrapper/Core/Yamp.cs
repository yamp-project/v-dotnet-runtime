using YAMP.Shared.Core;
using YAMP.Shared.Interfaces;

namespace YAMP.Wrapper.Core;

public static class Yamp
{
    public static IResource Resource { get; set; } = null!;

    public static void OnTick(Action tick)
    {
        Resource.RegisterTick(tick);
    }

    public static void LogDebug(string message)
    {
        SharedLibrary.LogDebug(message);
    }

    public static void LogWarning(string message)
    {
        SharedLibrary.LogWarn(message);
    }

    public static void Log(string message)
    {
        SharedLibrary.LogInfo(message);
    }

    public static void LogError(string message)
    {
        SharedLibrary.LogError(message);
    }
}
