#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <memory>
#include <cassert>
#include <filesystem>

#include "coreclr/hostfxr.h"
#include "coreclr/coreclr_delegates.h"

namespace dotnet
{
    class NetHostLibrary
    {
    public:
        explicit NetHostLibrary();
        ~NetHostLibrary() = default;

        void Initialize();
        void InitializeHost(hostfxr_handle hostHandle);
        std::string *GetHostFxrPath();

        hostfxr_run_app_fn m_hostFxrRunApp = nullptr;
        hostfxr_initialize_for_dotnet_command_line_fn m_hostFxrInitialize = nullptr;
        hostfxr_close_fn m_hostFxrClose = nullptr;
        hostfxr_get_runtime_delegate_fn m_getRuntimeDelegate = nullptr;
        get_function_pointer_fn m_getFunctionPointer = nullptr;

    private:
        std::unique_ptr<void> m_LibraryHandle;

        void *GetExport(const char *name)
        {
            if (!m_LibraryHandle)
            {
                return nullptr;
            }

#ifdef _WIN32
            return GetProcAddress(static_cast<HMODULE>(m_LibraryHandle.get()), name);
#else
            return dlsym(m_LibraryHandle.get(), name);
#endif
        }
    };
} // namespace dotnet