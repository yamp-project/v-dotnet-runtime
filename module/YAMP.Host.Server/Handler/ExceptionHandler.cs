using YAMP.Shared.Core;

namespace YAMP.Host.Server.Handler;

public static class ExceptionHandler
{
    public static void SetupExceptionHandling()
    {
        AppDomain.CurrentDomain.UnhandledException += OnUnhandledException;
        TaskScheduler.UnobservedTaskException += OnUnobservedTaskException;
    }

    private static void OnUnhandledException(object sender, UnhandledExceptionEventArgs e)
    {
        SharedLibrary.LogError($"An unhandled exception occurred: {e.ExceptionObject}");
    }

    private static void OnUnobservedTaskException(object? sender, UnobservedTaskExceptionEventArgs e)
    {
        SharedLibrary.LogError($"An unobserved task exception occurred: {e.Exception}");
    }
}
