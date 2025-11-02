using YAMP.Shared.Enums;

namespace YAMP.Shared.Attributes;

[AttributeUsage(AttributeTargets.Method)]
public class CoreEventAttribute(CoreEventType eventType) : Attribute
{
    public CoreEventType EventType { get; } = eventType;
}
