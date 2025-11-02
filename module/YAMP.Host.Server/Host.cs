using System.Runtime.InteropServices;
using YAMP.Host.Server.Handler;
using YAMP.Shared.Enums;
using YAMP.Shared.Implementations;
using YAMP.Shared.Services;
using YAMP.Shared.Structs;
using YAMP.Shared.Writers;

namespace YAMP.Host.Server;

internal static class Host
{
    private static ResourceService _resourceService = null!;

    private static void Main()
    {
        _resourceService = new ResourceService();

        Console.SetOut(new InterceptWriter(LogLevel.Info));
        Console.SetError(new InterceptWriter(LogLevel.Error));

        ExceptionHandler.SetupExceptionHandling();
    }

    [UnmanagedCallersOnly]
    private static unsafe void OnResourceStart(SdkResource* resourcePtr)
    {
        var sdkResource = Marshal.PtrToStructure<SdkResource>((IntPtr)resourcePtr);

        var resource = _resourceService.RegisterResource(sdkResource);
        _resourceService.LoadWrapperForResource(resource);

        resource.LoadAssembly();
    }

    [UnmanagedCallersOnly]
    private static unsafe void OnResourceStop(SdkResource* resourcePtr)
    {
        var resource = Marshal.PtrToStructure<SdkResource>((IntPtr)resourcePtr);
    }

    [UnmanagedCallersOnly]
    private static void OnTick()
    {
        foreach (var resource in _resourceService.Resources)
        {
            foreach (var tick in resource.Ticks)
            {
                tick();
            }
        }
    }

    [UnmanagedCallersOnly]
    private static unsafe void OnCoreEvent(CoreEventType type, CAnyArray* argsPtr)
    {
        var args = Marshal.PtrToStructure<CAnyArray>((IntPtr)argsPtr);
        var parsedArgs = CArgParser.ParseArguments(args);

        EventService.TriggerCoreEvent(type, parsedArgs);
    }

    [UnmanagedCallersOnly]
    private static unsafe void OnResourceEvent(char* namePtr, CAnyArray* argsPtr)
    {
        var name = Marshal.PtrToStringAnsi((IntPtr)namePtr);
        var args = Marshal.PtrToStructure<CAnyArray>((IntPtr)argsPtr);
        var parsedArgs = CArgParser.ParseArguments(args);
    }
}
