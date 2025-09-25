#include "runtime.h"

namespace dotnet
{
    std::unique_ptr<Runtime> Runtime::s_Instance = nullptr;

    bool Init()
    {
        return true;
    }

    void Shutdown()
    {
    }

    void OnResourceStart(SDK_Resource *resource)
    {
        static auto *runtime = Runtime::GetInstance();
        static auto *netHost = runtime->GetOrCreateNetHost();

        netHost->OnResourceStart(resource);
    }

    void OnResourceStop(SDK_Resource *resource)
    {
        static auto *runtime = Runtime::GetInstance();
        static auto *netHost = runtime->GetOrCreateNetHost();

        netHost->OnResourceStop(resource);
    }

    void OnTick()
    {
        static auto *runtime = Runtime::GetInstance();
        static auto *netHost = runtime->GetOrCreateNetHost();

        netHost->OnTick();
    }

    void OnCoreEvent(CoreEventType type, CAnyArray *args)
    {
        static auto *runtime = Runtime::GetInstance();
        static auto *netHost = runtime->GetOrCreateNetHost();

        netHost->OnCoreEvent(type, args);
    }

    void OnResourceEvent(const char *name, CAnyArray *args)
    {
        static auto *runtime = Runtime::GetInstance();
        static auto *netHost = runtime->GetOrCreateNetHost();

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

        s_Instance.reset();
    }

    bool Runtime::InitializedNetHost()
    {
        assert(s_Instance != nullptr);
        assert(s_NetHost == nullptr);

        return true;
    }
}; // namespace dotnet