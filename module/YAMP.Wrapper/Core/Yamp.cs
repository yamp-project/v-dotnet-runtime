using YAMP.Shared.Core;
using YAMP.Shared.Enums;
using YAMP.Shared.Implementations;
using YAMP.Shared.Interfaces;
using YAMP.Shared.Services;

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

    public static void RegisterCoreEvent(CoreEventType type, Delegate coreEventAction)
    {
        var coreEvent = new RegisteredCoreEvent { CoreEventAction = coreEventAction };

        EventService.RegisterCoreEvent(type, coreEvent);
    }

    public static void ScanClassInstanceAttributes(object instance)
    {
        AttributeService.ScanClassInstanceAttributes(instance);
    }
}
