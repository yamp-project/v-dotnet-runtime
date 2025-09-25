#include "net_host_library.h"

namespace dotnet
{
    NetHostLibrary::NetHostLibrary()
    {
    }

    void NetHostLibrary::Initialize()
    {
        auto *hostFxrPath = GetHostFxrPath();
        assert(hostFxrPath != nullptr);

#ifdef _WIN32
        m_LibraryHandle = std::make_unique<void *>(LoadLibraryExA(hostFxrPath->c_str(), nullptr, 0));
#else
        m_LibraryHandle = std::make_unique<void *>(dlopen(hostFxrPath->c_str(), RTLD_LAZY | RTLD_LOCAL));
#endif
        assert(m_LibraryHandle.get() != nullptr);

        m_hostFxrInitialize = reinterpret_cast<hostfxr_initialize_for_dotnet_command_line_fn>(
            GetExport("hostfxr_initialize_for_dotnet_command_line"));
        m_hostFxrRunApp = reinterpret_cast<hostfxr_run_app_fn>(
            GetExport("hostfxr_run_app"));
        m_hostFxrClose = reinterpret_cast<hostfxr_close_fn>(
            GetExport("hostfxr_close"));
        m_getRuntimeDelegate = reinterpret_cast<hostfxr_get_runtime_delegate_fn>(
            GetExport("hostfxr_get_runtime_delegate"));
    }

    void NetHostLibrary::InitializeHost(hostfxr_handle hostHandle)
    {
        int result = m_getRuntimeDelegate(hostHandle,
                                          hdt_get_function_pointer,
                                          reinterpret_cast<void **>(&m_getFunctionPointer));

        assert(result == 0);
        assert(m_getFunctionPointer != nullptr);
    }

    std::string *NetHostLibrary::GetHostFxrPath()
    {
#ifdef _WIN32
        const std::filesystem::path dotnetRoot = "C:/Program Files/dotnet/host/fxr";
#else
        const std::filesystem::path dotnetRoot = "/usr/share/dotnet/host/fxr";
#endif

        if (!std::filesystem::exists(dotnetRoot))
        {
            return nullptr;
        }

        std::string latestVersion;

        for (const auto &entry : std::filesystem::directory_iterator(dotnetRoot))
        {
            if (entry.is_directory())
            {
                const std::string version = entry.path().filename().string();
                if (version > latestVersion)
                    latestVersion = version;
            }
        }

        if (latestVersion.empty())
        {
            return nullptr;
        }

#ifdef _WIN32
        return &(dotnetRoot / latestVersion / "hostfxr.dll").string();
#else
        return &(dotnetRoot / latestVersion / "libhostfxr.so").string();
#endif
    }
} // namespace dotnet