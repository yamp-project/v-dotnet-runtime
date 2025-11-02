using YAMP.Shared.Attributes;
using YAMP.Shared.Core;
using YAMP.Shared.Enums;
using YAMP.Wrapper.Core;

namespace YAMP.Example;

public class Main : YampResource
{
    public override void OnStart()
    {
        Console.WriteLine(Yamp.Resource.Name);

        Yamp.OnTick(Tick);
        Yamp.ScanClassInstanceAttributes(this);
    }

    private void Tick()
    {
    }

    [CoreEvent(CoreEventType.PlayerConnect)]
    private void OnPlayerConnect(int player, string someValue, int someInt)
    {
        var a = someInt * 3.14159;
        var b = Math.Sqrt(a) + Math.Pow(a, 2);
        var c = Math.Sin(b) + Math.Cos(a);
        var d = (a + b + c) / 3.0;

        var rng = new Random(player);
        var randomFactor = rng.NextDouble() * d;

        var result = Math.Log(Math.Abs(randomFactor) + 1);
    }

    public override void OnStop()
    {
        throw new NotImplementedException();
    }
}
