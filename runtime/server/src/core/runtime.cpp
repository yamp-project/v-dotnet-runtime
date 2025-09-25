#include "runtime.h"

namespace dotnet
{
    std::unique_ptr<Runtime> Runtime::s_Instance = nullptr;
    std::unique_ptr<NetHost> Runtime::s_NetHost = nullptr;

    bool Init()
    {
        return true;
    }

    void Shutdown()
    {
        Runtime::Shutdown();
    }

    void OnResourceStart(SDK_Resource *resource)
    {
        assert(resource != nullptr);

        auto *runtime = Runtime::GetInstance();
        auto *netHost = runtime->GetOrCreateNetHost();

        netHost->OnResourceStart(resource);
    }

    void OnResourceStop(SDK_Resource *resource)
    {
        assert(resource != nullptr);

        auto *runtime = Runtime::GetInstance();
        auto *netHost = runtime->GetOrCreateNetHost();

        netHost->OnResourceStop(resource);
    }

    void OnTick()
    {
        auto *runtime = Runtime::GetInstance();
        auto *netHost = runtime->GetOrCreateNetHost();

        netHost->OnTick();
    }

    void OnCoreEvent(CoreEventType type, CAnyArray *args)
    {
        auto *runtime = Runtime::GetInstance();
        auto *netHost = runtime->GetOrCreateNetHost();

        netHost->OnCoreEvent(type, args);
    }

    void OnResourceEvent(const char *name, CAnyArray *args)
    {
        assert(name != nullptr);

        auto *runtime = Runtime::GetInstance();
        auto *netHost = runtime->GetOrCreateNetHost();

        netHost->OnResourceEvent(name, args);
    }

    Runtime::Runtime(SDK_Interface *lookupTable) : m_LookupTable(lookupTable) {}

    Runtime *Runtime::GetInstance()
    {
        assert(s_Instance != nullptr);

        return s_Instance.get();
    }

    Runtime *Runtime::Initialize(SDK_Interface *lookupTable)
    {
        assert(s_Instance == nullptr);
        s_Instance = std::make_unique<Runtime>(lookupTable);

        return s_Instance.get();
    }

    void Runtime::Shutdown()
    {
        assert(s_Instance != nullptr);

        ShutdownNetHost();
        s_Instance.reset();
    }

    bool Runtime::InitializedNetHost()
    {
        assert(s_Instance != nullptr);

        return s_NetHost != nullptr;
    }

    void Runtime::ShutdownNetHost()
    {
        if (s_NetHost != nullptr)
        {
            s_NetHost->Shutdown();
            s_NetHost.reset();
        }
    }
}; // namespace dotnet