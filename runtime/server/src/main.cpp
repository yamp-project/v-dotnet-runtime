#include <yamp-sdk/include/yamp-sdk/sdk.h>
#include "runtime.h"

SDK_Context GetRuntimeContext()
{
    return {
        .version = "0.0.1",
        .sdkVersion = "0.0.1",

        .Init = dotnet::Init,
        .Shutdown = dotnet::Shutdown,

        .OnTick = dotnet::OnTick,
    };
}

SDK_EXPORT void RuntimeEntry(RegisterRuntime registerRuntime)
{
    dotnet::Runtime *runtime = dotnet::Runtime::Initialize(registerRuntime("dotnet", GetRuntimeContext()));
    runtime->GetLogger().Info("[dotnet] Runtime registered");
}