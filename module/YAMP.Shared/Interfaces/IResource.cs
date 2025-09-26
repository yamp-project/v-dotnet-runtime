using System.Reflection;
using System.Runtime.Loader;
using YAMP.Shared.Core;
using YAMP.Shared.Structs;

namespace YAMP.Shared.Interfaces;

public interface IResource
{
    public string Name { get; }
    public string Path { get; }
    public string MainFile { get; }
    internal AssemblyLoadContext LoadContext { get; init; }
    internal Assembly WrapperAssembly { get; set; }
    internal YampResource ResourceInfo { get; set; }
    internal List<Action> Ticks { get; init; }

    internal void RegisterTick(Action tick);

    internal void LoadAssembly();
}
