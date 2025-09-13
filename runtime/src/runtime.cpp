#include "runtime.h"

namespace dotnet
{
    std::unique_ptr<Runtime> Runtime::sInstance = nullptr;

    bool Init()
    {
        Runtime *runtime = Runtime::GetInstance();
        runtime->GetLogger().Info("[dotnet] Runtime initializing");

        // dotnet init stuff...

        return true;
    }

    void OnTick()
    {
        // ...
    }

    void Shutdown()
    {

    }


    Runtime::Runtime(SDK_Interface* sdkInt) : mInterface(sdkInt), mLogger(Logger(sdkInt, "dotnet"))
    {
    }

    Runtime *Runtime::GetInstance()
    {
        assert(sInstance != nullptr);
        return sInstance.get();
    }

    Runtime *Runtime::Initialize(SDK_Interface* sdkInt)
    {
        assert(sInstance == nullptr);
        sInstance = std::make_unique<Runtime>(sdkInt);

        return sInstance.get();
    }

    void Runtime::Shutdown()
    {
        assert(sInstance != nullptr);
        sInstance.reset();
    }
};