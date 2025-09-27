#pragma once

#include <yamp-sdk/sdk.h>
#include <memory>
#include <filesystem>

#include "net_host_library.h"

#if defined(_WIN32)
#ifdef _WCHAR_T_DEFINED
#define CHAR_T_LITERAL(x) L##x
#else
#define CHAR_T_LITERAL(x) reinterpret_cast<const char_t *>(u##x)
#endif
#else
#define CHAR_T_LITERAL(x) x
#endif

typedef void (*resourceStartDelegate)(SDK_Resource *resource);
typedef void (*resourceStopDelegate)(SDK_Resource *resource);
typedef void (*tickDelegate)();
typedef void (*coreEventDelegate)(CoreEventType type, CAnyArray *args);
typedef void (*resourceEventDelegate)(const char *name, CAnyArray *args);

namespace dotnet
{
    class NetHost
    {
    public:
        explicit NetHost();
        ~NetHost() = default;

        void Initialize();
        void Shutdown();

        void OnResourceStart(SDK_Resource *resource);
        void OnResourceStop(SDK_Resource *resource);
        void OnTick();
        void OnCoreEvent(CoreEventType type, CAnyArray *args);
        void OnResourceEvent(const char *name, CAnyArray *args);

    private:
        std::unique_ptr<NetHostLibrary> m_Library;
        std::shared_ptr<hostfxr_handle> m_HostHandle;

        resourceStartDelegate m_resourceStartDelegate = nullptr;
        resourceStopDelegate m_resourceStopDelegate = nullptr;
        tickDelegate m_tickDelegate = nullptr;
        coreEventDelegate m_coreEventDelegate = nullptr;
        resourceEventDelegate m_resourceEventDelegate = nullptr;

        void InitializeDelegates();
        void InitializeDelegate(const char_t *typeName, const char_t *methodName, void **delegatePtr);
    };
} // namespace dotnet