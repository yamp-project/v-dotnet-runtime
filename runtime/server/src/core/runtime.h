#pragma once

#include <yamp-sdk/sdk.h>

#include <cassert>
#include <memory>

#include "net_host.h"

namespace dotnet
{
    bool Init();
    void Shutdown();
    void OnResourceStart(SDK_Resource *resource);
    void OnResourceStop(SDK_Resource *resource);
    void OnTick();
    void OnCoreEvent(CoreEventType type, CAnyArray *args);
    void OnResourceEvent(const char *name, CAnyArray *args);

    class Runtime
    {
    public:
        static Runtime *GetInstance();
        static Runtime *Initialize(SDK_Interface *lookupTable);
        static void Shutdown();

        static bool InitializedNetHost();
        static void ShutdownNetHost();

        explicit Runtime(SDK_Interface *lookupTable);
        ~Runtime() = default;

        SDK_Interface *GetLookupTable() const
        {
            return m_LookupTable;
        }

        NetHost *GetOrCreateNetHost()
        {
            if (s_NetHost == nullptr)
            {
                s_NetHost = std::make_unique<NetHost>();
                s_NetHost->Initialize();
            }

            return s_NetHost.get();
        }

    private:
        static std::unique_ptr<Runtime> s_Instance;
        static std::unique_ptr<NetHost> s_NetHost;

        SDK_Interface *m_LookupTable = nullptr;
    };
} // namespace dotnet
