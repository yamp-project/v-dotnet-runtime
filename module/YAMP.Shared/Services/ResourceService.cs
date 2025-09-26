using System.Diagnostics;
using System.Reflection;
using YAMP.Shared.Implementations;
using YAMP.Shared.Interfaces;
using YAMP.Shared.Structs;

namespace YAMP.Shared.Services;

public class ResourceService
{
    private readonly List<IResource> _resources = new();
    public IReadOnlyList<IResource> Resources => _resources.AsReadOnly();

    public Resource RegisterResource(SdkResource resourceStruct)
    {
        Trace.Assert(_resources.All(r => r.Name != resourceStruct.Name),
            "Resource with the same name already registered.");

        var resource = new Resource(resourceStruct);
        _resources.Add(resource);

        return resource;
    }

    public void LoadWrapperForResource(IResource resource)
    {
        var currentPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
        Trace.Assert(currentPath is not null, "Current path is null.");

        var wrapperPath = Path.Combine(currentPath, $"YAMP.Wrapper.dll");
        Trace.Assert(File.Exists(wrapperPath), $"Wrapper assembly not found at path: {wrapperPath}");

        var wrapperAssembly = resource.LoadContext.LoadFromAssemblyPath(wrapperPath);
        resource.WrapperAssembly = wrapperAssembly;
    }
}
