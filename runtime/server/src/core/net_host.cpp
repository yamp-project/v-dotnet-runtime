#include "net_host.h"

namespace dotnet
{
    NetHost::NetHost()
    {
    }

    void NetHost::Initialize()
    {
        assert(std::filesystem::exists("YAMP.Host.Server.dll"));

        m_Library = std::make_unique<NetHostLibrary>();
        m_Library->Initialize();

        const char_t **argv = new const char_t *[1];
        argv[0] = CHAR_T_LITERAL("YAMP.Host.Server.dll");

        hostfxr_handle rawHandle = nullptr;

        int result = m_Library->m_hostFxrInitialize(1, argv, nullptr, &rawHandle);
        delete[] argv;

        assert(result == 0);

        m_HostHandle = std::shared_ptr<hostfxr_handle>(new hostfxr_handle(rawHandle), [](hostfxr_handle *ptr)
                                                       { delete ptr; });
        assert(m_HostHandle != nullptr);

        m_Library->InitializeHost(*m_HostHandle);

        InitializeDelegates();

        result = m_Library->m_hostFxrRunApp(*m_HostHandle);
        assert(result == 0);
    }

    void NetHost::InitializeDelegates()
    {
        InitializeDelegate(
            CHAR_T_LITERAL("YAMP.Host.Server.Host, YAMP.Host.Server"),
            CHAR_T_LITERAL("OnResourceStart"),
            reinterpret_cast<void **>(&m_resourceStartDelegate));

        InitializeDelegate(
            CHAR_T_LITERAL("YAMP.Host.Server.Host, YAMP.Host.Server"),
            CHAR_T_LITERAL("OnResourceStop"),
            reinterpret_cast<void **>(&m_resourceStopDelegate));

        InitializeDelegate(
            CHAR_T_LITERAL("YAMP.Host.Server.Host, YAMP.Host.Server"),
            CHAR_T_LITERAL("OnTick"),
            reinterpret_cast<void **>(&m_tickDelegate));

        InitializeDelegate(
            CHAR_T_LITERAL("YAMP.Host.Server.Host, YAMP.Host.Server"),
            CHAR_T_LITERAL("OnCoreEvent"),
            reinterpret_cast<void **>(&m_coreEventDelegate));

        InitializeDelegate(
            CHAR_T_LITERAL("YAMP.Host.Server.Host, YAMP.Host.Server"),
            CHAR_T_LITERAL("OnResourceEvent"),
            reinterpret_cast<void **>(&m_resourceEventDelegate));
    }

    void NetHost::InitializeDelegate(const char_t *typeName, const char_t *methodName, void **delegatePtr)
    {
        int result = m_Library->m_getFunctionPointer(
            typeName,
            methodName,
            UNMANAGEDCALLERSONLY_METHOD, nullptr, nullptr,
            delegatePtr);

        assert(result == 0);
        assert(*delegatePtr != nullptr);
    }

    void NetHost::Shutdown()
    {
        if (m_Library && m_HostHandle)
        {
            m_Library->m_hostFxrClose(*m_HostHandle);
            m_HostHandle.reset();
        }

        m_resourceStartDelegate = nullptr;
        m_resourceStopDelegate = nullptr;
        m_tickDelegate = nullptr;
        m_coreEventDelegate = nullptr;
        m_resourceEventDelegate = nullptr;

        m_Library.reset();
    }

    void NetHost::OnResourceStart(SDK_Resource *resource)
    {
        assert(m_resourceStartDelegate != nullptr);

        m_resourceStartDelegate(resource);
    }

    void NetHost::OnResourceStop(SDK_Resource *resource)
    {
        assert(m_resourceStopDelegate != nullptr);

        m_resourceStopDelegate(resource);
    }

    void NetHost::OnTick()
    {
        assert(m_tickDelegate != nullptr);

        m_tickDelegate();
    }

    void NetHost::OnCoreEvent(CoreEventType type, CAnyArray *args)
    {
        assert(m_coreEventDelegate != nullptr);

        m_coreEventDelegate(type, args);
    }

    void NetHost::OnResourceEvent(const char *name, CAnyArray *args)
    {
        assert(m_resourceEventDelegate != nullptr);

        m_resourceEventDelegate(name, args);
    }
} // namespace dotnet
