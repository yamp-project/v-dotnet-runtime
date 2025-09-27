using System.Diagnostics;
using YAMP.Shared.Core;
using YAMP.Shared.Interfaces;
using YAMP.Wrapper.Core;
using YAMP.Wrapper.Tasks;

namespace YAMP.Wrapper;

public static class EntryPoint
{
    private static readonly TickTaskScheduler Scheduler = new();
    private static readonly TickSynchronizationContext SyncContext = new(Scheduler);

    private static void Tick()
    {
        var previousContext = SynchronizationContext.Current;

        try
        {
            SynchronizationContext.SetSynchronizationContext(SyncContext);

            Scheduler.ExecutePendingTasks();
        }
        finally
        {
            SynchronizationContext.SetSynchronizationContext(previousContext);
        }
    }

    public static void Main(IResource resource, byte[] assemblyData)
    {
        Trace.Assert(resource.WrapperAssembly is not null, "Wrapper assembly is not loaded.");
        Yamp.Resource = resource;

        using var ms = new MemoryStream(assemblyData);
        var assembly = resource.LoadContext.LoadFromStream(ms);
        Trace.Assert(assembly is not null, "Failed to load resource assembly from stream.");

        var resourceType =
            assembly.GetTypes().FirstOrDefault(t => t.IsClass && typeof(YampResource).IsAssignableFrom(t));
        Trace.Assert(resourceType is not null, "No class derived from YampResource found in resource assembly.");

        var resourceInstance = (YampResource?)Activator.CreateInstance(resourceType);
        Trace.Assert(resourceInstance is not null, "Failed to create an instance of the resource class.");

        resource.ResourceInfo = resourceInstance;
        resource.RegisterTick(Tick);

        SynchronizationContext.SetSynchronizationContext(SyncContext);

        try
        {
            resourceInstance.OnStart();
        }
        catch (Exception ex)
        {
            SharedLibrary.LogError("Error during OnStart: " + ex);
        }
    }
}
