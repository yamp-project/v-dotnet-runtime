using YAMP.Shared.Interfaces;

namespace YAMP.Wrapper.Core;

public static class Yamp
{
    public static IResource Resource { get; set; } = null!;

    public static void OnTick(Action tick)
    {
        Resource.RegisterTick(tick);
    }
}
