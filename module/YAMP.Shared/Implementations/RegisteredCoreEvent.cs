namespace YAMP.Shared.Implementations;

internal class RegisteredCoreEvent
{
    public required Delegate CoreEventAction { get; init; }
}
