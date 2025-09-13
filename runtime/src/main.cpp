#include <yamp-sdk/include/yamp-sdk/sdk.h>
#include "runtime.h"

SDK_Context GetRuntimeContext()
{
    SDK_Context ctx{};

    ctx.version = "0.0.1";
    ctx.sdkVersion = "0.0.1";

    ctx.Init = dotnet::Init;
    ctx.Shutdown = dotnet::Shutdown;

    ctx.OnTick = dotnet::OnTick;

    return ctx;
}

SDK_EXPORT void RuntimeEntry(RegisterRuntime registerRuntime)
{
    dotnet::Runtime *runtime = dotnet::Runtime::Initialize(registerRuntime("dotnet", GetRuntimeContext()));
    runtime->GetLogger().Info("[dotnet] Runtime registered");
}