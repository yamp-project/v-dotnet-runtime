#include "net_host_library.h"

namespace dotnet
{
    NetHostLibrary::NetHostLibrary()
    {
    }

    NetHostLibrary::~NetHostLibrary()
    {
#ifdef _WIN32
        if (m_LibraryHandle)
        {
            FreeLibrary(m_LibraryHandle);
        }
#else
        if (m_LibraryHandle)
        {
            dlclose(m_LibraryHandle);
        }
#endif
    }

    void NetHostLibrary::Initialize()
    {
        auto *hostFxrPath = GetHostFxrPath();
        assert(hostFxrPath != nullptr);

#ifdef _WIN32
        m_LibraryHandle = LoadLibraryExA(hostFxrPath->c_str(), nullptr, 0);
        assert(m_LibraryHandle != nullptr);
#else
        m_LibraryHandle = dlopen(hostFxrPath->c_str(), RTLD_LAZY | RTLD_LOCAL);
        assert(m_LibraryHandle != nullptr);
#endif

        m_hostFxrInitialize = reinterpret_cast<hostfxr_initialize_for_dotnet_command_line_fn>(
            GetExport("hostfxr_initialize_for_dotnet_command_line"));
        m_hostFxrRunApp = reinterpret_cast<hostfxr_run_app_fn>(
            GetExport("hostfxr_run_app"));
        m_hostFxrClose = reinterpret_cast<hostfxr_close_fn>(
            GetExport("hostfxr_close"));
        m_getRuntimeDelegate = reinterpret_cast<hostfxr_get_runtime_delegate_fn>(
            GetExport("hostfxr_get_runtime_delegate"));

        assert(m_hostFxrInitialize != nullptr);
        assert(m_hostFxrRunApp != nullptr);
        assert(m_hostFxrClose != nullptr);
        assert(m_getRuntimeDelegate != nullptr);
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
        static std::string cachedPath;

        if (!cachedPath.empty())
        {
            return &cachedPath;
        }

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
        cachedPath = (dotnetRoot / latestVersion / "hostfxr.dll").string();
#else
        cachedPath = (dotnetRoot / latestVersion / "libhostfxr.so").string();
#endif
        return &cachedPath;
    }
} // namespace dotnet