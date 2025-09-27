namespace YAMP.Wrapper.Tasks;

internal class TickSynchronizationContext(TickTaskScheduler scheduler) : SynchronizationContext
{
    public override void Post(SendOrPostCallback callback, object? state)
    {
        Task.Factory.StartNew(
            () => callback(state),
            CancellationToken.None,
            TaskCreationOptions.None,
            scheduler);
    }

    public override void Send(SendOrPostCallback callback, object? state)
    {
        Post(callback, state);
    }
}
