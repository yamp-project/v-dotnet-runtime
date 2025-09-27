using System.Diagnostics;
using System.Text;
using YAMP.Shared.Core;

namespace YAMP.Wrapper.Writers;

public class InterceptWriter : TextWriter
{
    public override Encoding Encoding => Encoding.UTF8;

    public override void WriteLine(string? value)
    {
        if (value == null)
        {
            return;
        }

        SharedLibrary.LogInfo(value);
    }

    public override void Write(string? value)
    {
        if (value == null)
        {
            return;
        }

        SharedLibrary.LogInfo(value);
    }
}
