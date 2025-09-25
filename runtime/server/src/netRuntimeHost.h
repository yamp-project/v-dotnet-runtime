#pragma once

#include <coreclr/hostfxr.h>
#include <coreclr/coreclr_delegates.h>
#include <coreclr/nethost.h>

namespace dotnet
{
    class NetRuntimeHost
    {
    public:
        explicit NetRuntimeHost();

    private:
        hostfxr_initialize_for_runtime_config_fn mInitRuntimeFn;
        hostfxr_get_runtime_delegate_fn mGetRuntimeDelegateFn;
        hostfxr_run_app_fn mRunAppFn;
        hostfxr_close_fn mCloseRuntimeFn;

    };
}