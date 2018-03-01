#include "DMXListener.h"
#include "OLABoostLogDestination.h"
#include <boost/log/trivial.hpp>


DMXListener::DMXListener(const unsigned short universe) :
        _universe(universe) {
    _logDestination = new ola::OLABoostLogDestination;
    _universeData = new uint8_t[512];

    // Initialise the universe data with zeros
    for (int i=0; i<512; i++) {
        _universeData[512] = 0;
    }
}

DMXListener::~DMXListener() {
    delete _client;
    delete[] _universeData;
}

bool DMXListener::Start() {
    BOOST_LOG_TRIVIAL(info) << "Initialising the Open Lighting Architecture";
    ola::InitLogging(ola::OLA_LOG_MAX, _logDestination);

    _wrapper = new ola::client::OlaClientWrapper;
    if (!_wrapper->Setup()) {
        BOOST_LOG_TRIVIAL(fatal) << "FAILED";
        exit(1);
    }

    _client = _wrapper->GetClient();
    _client->RegisterUniverse(_universe,
            ola::client::REGISTER,
            ola::NewSingleCallback(this, &DMXListener::onUniverseRegister));
    std::stringstream universeName;
    universeName << "ViragoBox";
    _client->SetUniverseName(_universe, universeName.str(), ola::NewSingleCallback(this, &DMXListener::onUniverseName));
    _client->SetDMXCallback(ola::NewCallback(this, &DMXListener::onDMXReceived));

    BOOST_LOG_TRIVIAL(info) << "DONE";

    return ola::thread::Thread::Start();
}

void DMXListener::Stop() {
    BOOST_LOG_TRIVIAL(info) << "Terminating OLA";

    _wrapper->GetSelectServer()->Terminate();
    
    BOOST_LOG_TRIVIAL(info) << "DONE";
}

float DMXListener::getValue(const unsigned short address, const bool isFine) const {
    float value;
    float rawValue = this->getRawValue(address, isFine);
    
    if (isFine) {
        value = rawValue / 65535;
    } else {
        value = rawValue / 255;
    }

    return value;
}

unsigned int DMXListener::getRawValue(const unsigned short address, const bool isFine) const {
    unsigned int value; 

    value = this->getByte(address);
    if (isFine) {
        value = value<<8 | this->getByte(address+1);
    }

    return value;
}

void* DMXListener::Run() {
    _wrapper->GetSelectServer()->Run();
    return nullptr;
}

void DMXListener::onUniverseName(const ola::client::Result &result) {
    if (result.Success()) {
        BOOST_LOG_TRIVIAL(debug) << "Updated name of universe " << _universe;
    } else {
        BOOST_LOG_TRIVIAL(warning) << "Failed to change name of universe " << _universe << ": " << result.Error();
    }
}

void DMXListener::onUniverseRegister(const ola::client::Result &result) {
    if (result.Success()) {
        BOOST_LOG_TRIVIAL(info) << "Listening for DMX data on universe " << _universe;
    } else {
        BOOST_LOG_TRIVIAL(warning) << "Failed to register DMX listener on universe " << _universe << ": " << result.Error();
    }
}

void DMXListener::onDMXReceived(const ola::client::DMXMetadata &metadata, const ola::DmxBuffer &data) {
    unsigned int length;
    data.Get(_universeData, &length);

    this->newDataReceived();
}

uint8_t DMXListener::getByte(const unsigned short address) const {
    if ((address > 0) && (address <= 512)) {
        return _universeData[address-1];
    } else {
        return 0;
    }
}

