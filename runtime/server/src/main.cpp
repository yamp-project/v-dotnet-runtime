#include <yamp-sdk/sdk.h>
#include <cassert>

#include "core/runtime.h"

SDK_Context GetRuntimeContext()
{
    return {
        .version = "0.0.1",
        .sdkVersion = "0.0.1",

        .Init = dotnet::Init,
        .Shutdown = dotnet::Shutdown,

        .OnResourceStart = dotnet::OnResourceStart,
        .OnResourceStop = dotnet::OnResourceStop,
        .OnTick = dotnet::OnTick,
        .OnCoreEvent = dotnet::OnCoreEvent,
        .OnResourceEvent = dotnet::OnResourceEvent,
    };
}

SDK_EXPORT void RuntimeEntry(RegisterRuntime registerRuntime)
{
    assert(registerRuntime != nullptr);

    auto *lookupTable = registerRuntime("dotnet", GetRuntimeContext());
    assert(lookupTable != nullptr);

    dotnet::Runtime::Initialize(lookupTable);
}