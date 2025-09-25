#include "netRuntimeHost.h"

#include "runtime.h"

#include <yamp-sdk/sdk.h>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace dotnet {
    NetRuntimeHost::NetRuntimeHost() {
        char_t buffer[256];
        size_t bufferSize = sizeof(buffer) / sizeof(char_t);

        int rc = get_hostfxr_path(buffer, &bufferSize, nullptr);

        if (rc != 0) {
            Runtime::GetInstance()->GetLogger().Error("Failed to get hostfxr path");
            return;
        }

#ifdef _WIN32
        HMODULE h = LoadLibraryW(buffer);
        assert(h != nullptr);

        this->mInitRuntimeFn = reinterpret_cast<hostfxr_initialize_for_runtime_config_fn>(GetProcAddress(
            h, "hostfxr_initialize_for_dotnet_command_line"));
        this->mGetRuntimeDelegateFn = reinterpret_cast<hostfxr_get_runtime_delegate_fn>(GetProcAddress(
            h, "hostfxr_get_runtime_delegate"));
        this->mRunAppFn = reinterpret_cast<hostfxr_run_app_fn>(GetProcAddress(h, "hostfxr_run_app"));
        this->mCloseRuntimeFn = reinterpret_cast<hostfxr_close_fn>(GetProcAddress(h, "hostfxr_close"));
#endif
    }


}
