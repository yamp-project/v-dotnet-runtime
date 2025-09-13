#pragma once

#include "utils/logger.h"

#include <yamp-sdk/sdk.h>

#include <cassert>
#include <memory>

namespace dotnet
{
    bool Init();
    void Shutdown();
    void OnTick();

    class Runtime
    {
    public:
        static Runtime *GetInstance();
        static Runtime *Initialize(SDK_Interface* sdkInt);
        static void Shutdown();

        explicit Runtime(SDK_Interface* sdkInt);
        ~Runtime() = default;

        SDK_Interface* GetInterface() const
        {
            return mInterface;
        }

        Logger& GetLogger()
        {
            return mLogger;
        }

    private:
        static std::unique_ptr<Runtime> sInstance;

        SDK_Interface* mInterface = nullptr;
        Logger mLogger;
    };
}
