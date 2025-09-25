#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <memory>
#include <cassert>
#include <filesystem>

#include "coreclr/nethost.h"
#include "coreclr/hostfxr.h"
#include "coreclr/coreclr_delegates.h"

namespace dotnet
{
    class NetHostLibrary
    {
    public:
        explicit NetHostLibrary();
        ~NetHostLibrary();

        void Initialize();
        void InitializeHost(hostfxr_handle hostHandle);
        std::string *GetHostFxrPath();

        hostfxr_run_app_fn m_hostFxrRunApp = nullptr;
        hostfxr_initialize_for_dotnet_command_line_fn m_hostFxrInitialize = nullptr;
        hostfxr_close_fn m_hostFxrClose = nullptr;
        hostfxr_get_runtime_delegate_fn m_getRuntimeDelegate = nullptr;
        get_function_pointer_fn m_getFunctionPointer = nullptr;

    private:
#ifdef _WIN32
        HMODULE m_LibraryHandle = nullptr;
#else
        void *m_LibraryHandle = nullptr;
#endif

        void *GetExport(const char *name)
        {
            if (!m_LibraryHandle)
            {
                return nullptr;
            }

#ifdef _WIN32
            return GetProcAddress(m_LibraryHandle, name);
#else
            return dlsym(m_LibraryHandle, name);
#endif
        }
    };
} // namespace dotnet