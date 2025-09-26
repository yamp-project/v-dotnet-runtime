using System.Diagnostics;
using System.Reflection;
using System.Runtime.Loader;
using YAMP.Shared.Core;
using YAMP.Shared.Interfaces;
using YAMP.Shared.Structs;

namespace YAMP.Shared.Implementations;

public class Resource(SdkResource resource) : IResource
{
    public string Name => resource.Name;
    public string Path => resource.Path;
    public string MainFile => resource.MainFile;
    public AssemblyLoadContext LoadContext { get; init; } = new(Guid.NewGuid().ToString(), true);
    public Assembly WrapperAssembly { get; set; } = null!;
    public YampResource ResourceInfo { get; set; } = null!;
    public List<Action> Ticks { get; init; } = new();

    public void LoadAssembly()
    {
        var mainFilePath = System.IO.Path.Combine(Path, MainFile);
        Trace.Assert(File.Exists(mainFilePath), $"Main file not found at path: {mainFilePath}");

        Trace.Assert(WrapperAssembly is not null, "Wrapper assembly is not loaded.");

        var entryPointType = WrapperAssembly.GetType("YAMP.Wrapper.EntryPoint");
        Trace.Assert(entryPointType is not null, "EntryPoint class not found in Wrapper assembly");

        var mainMethod = entryPointType.GetMethod("Main", BindingFlags.Public | BindingFlags.Static);
        Trace.Assert(mainMethod is not null, "Main method not found in EntryPoint class");

        var assemblyData = File.ReadAllBytes(mainFilePath);

        mainMethod.Invoke(null, [this, assemblyData]);
    }

    public void RegisterTick(Action tick)
    {
        Trace.Assert(tick is not null, "Tick action cannot be null.");

        Ticks.Add(tick);
    }
}
