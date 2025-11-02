using System.Runtime.InteropServices;
using YAMP.Shared.Structs;

namespace YAMP.Shared.Core;

internal static class SharedLibrary
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    private delegate void LogFn(IntPtr fmt);

    private static LogFn _logDebugFn = null!;
    private static LogFn _logInfoFn = null!;
    private static LogFn _logWarnFn = null!;
    private static LogFn _logErrorFn = null!;

    [UnmanagedCallersOnly]
    private static unsafe void InitializeLibrary(SdkInterface* lookupTablePtr)
    {
        var sdkInterface = Marshal.PtrToStructure<SdkInterface>((IntPtr)lookupTablePtr);

        _logDebugFn = Marshal.GetDelegateForFunctionPointer<LogFn>(sdkInterface.LogDebug);
        _logInfoFn = Marshal.GetDelegateForFunctionPointer<LogFn>(sdkInterface.LogInfo);
        _logWarnFn = Marshal.GetDelegateForFunctionPointer<LogFn>(sdkInterface.LogWarn);
        _logErrorFn = Marshal.GetDelegateForFunctionPointer<LogFn>(sdkInterface.LogError);
    }

    public static void LogDebug(string format, params object[] args)
    {
        var message = args.Length > 0 ? string.Format(format, args) : format;
        var ptr = Marshal.StringToHGlobalAnsi(message);

        try
        {
            _logDebugFn(ptr);
        }
        finally
        {
            Marshal.FreeHGlobal(ptr);
        }
    }

    public static void LogInfo(string format, params object[] args)
    {
        var message = args.Length > 0 ? string.Format(format, args) : format;
        var ptr = Marshal.StringToHGlobalAnsi(message);

        try
        {
            _logInfoFn(ptr);
        }
        finally
        {
            Marshal.FreeHGlobal(ptr);
        }
    }

    public static void LogWarn(string format, params object[] args)
    {
        var message = args.Length > 0 ? string.Format(format, args) : format;
        var ptr = Marshal.StringToHGlobalAnsi(message);

        try
        {
            _logWarnFn(ptr);
        }
        finally
        {
            Marshal.FreeHGlobal(ptr);
        }
    }

    public static void LogError(string format, params object[] args)
    {
        var message = args.Length > 0 ? string.Format(format, args) : format;
        var ptr = Marshal.StringToHGlobalAnsi(message);

        try
        {
            _logErrorFn(ptr);
        }
        finally
        {
            Marshal.FreeHGlobal(ptr);
        }
    }

    public static void LogDebug(string message)
    {
        LogDebug(message, []);
    }

    public static void LogInfo(string message)
    {
        LogInfo(message, []);
    }

    public static void LogWarn(string message)
    {
        LogWarn(message, []);
    }

    public static void LogError(string message)
    {
        LogError(message, []);
    }
}
