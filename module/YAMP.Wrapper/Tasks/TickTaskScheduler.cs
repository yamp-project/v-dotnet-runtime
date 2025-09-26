using System.Collections.Concurrent;

namespace YAMP.Wrapper.Tasks;

public class TickTaskScheduler : TaskScheduler
{
    private readonly ConcurrentQueue<Task> _tasks = new();
    private readonly int _mainThreadId = Thread.CurrentThread.ManagedThreadId;

    protected override void QueueTask(Task task)
    {
        _tasks.Enqueue(task);
    }

    protected override bool TryExecuteTaskInline(Task task, bool taskWasPreviouslyQueued)
    {
        if (Thread.CurrentThread.ManagedThreadId != _mainThreadId)
        {
            return false;
        }

        return TryExecuteTask(task);
    }

    protected override IEnumerable<Task> GetScheduledTasks()
    {
        return _tasks.ToArray();
    }

    public void ExecutePendingTasks()
    {
        while (_tasks.TryDequeue(out var task))
        {
            TryExecuteTask(task);
        }
    }
}
