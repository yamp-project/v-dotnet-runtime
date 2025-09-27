using System.Text;
using YAMP.Shared.Core;
using YAMP.Shared.Enums;

namespace YAMP.Shared.Writers;

public class InterceptWriter(LogLevel logLevel) : TextWriter
{
    public override Encoding Encoding => Encoding.UTF8;

    private void Log(string message)
    {
        switch (logLevel)
        {
            case LogLevel.Error:
            {
                SharedLibrary.LogError(message);
                break;
            }
            default:
            {
                SharedLibrary.LogInfo(message);
                break;
            }
        }
    }

    public override void WriteLine(string? value)
    {
        if (value == null)
        {
            return;
        }

        Log(value);
    }

    public override void Write(string? value)
    {
        if (value == null)
        {
            return;
        }

        Log(value);
    }
}
