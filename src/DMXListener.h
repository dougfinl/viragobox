#ifndef DMX_LISTENER_H_
#define DMX_LISTENER_H_

#include <ola/DmxBuffer.h>
#include <ola/Logging.h>
#include <ola/client/ClientWrapper.h>
#include <ola/thread/Thread.h>
#include <ola/StringUtils.h>
#include <functional>


class DMXListener : public ola::thread::Thread {
    public:
        explicit DMXListener(const unsigned short universe);
        virtual ~DMXListener();

        virtual bool Start();
        virtual void Stop();

        float getValue(const unsigned short address, const bool isFine) const;
        unsigned int getRawValue(const unsigned short address, const bool isFine) const;

        std::function<void()> newDataReceived;

    private:
        virtual void* Run();
        void onUniverseName(const ola::client::Result &result);
        void onUniverseRegister(const ola::client::Result &result);
        void onDMXReceived(const ola::client::DMXMetadata &metadata, const ola::DmxBuffer &data);
        uint8_t getByte(const unsigned short address) const;

        unsigned int                   _universe;
        uint8_t*                       _universeData;
        ola::client::OlaClientWrapper* _wrapper;
        ola::client::OlaClient*        _client;
        ola::LogDestination*           _logDestination;
};


#endif // DMX_LISTENER_H_

