#include "DMXListener.h"


DMXListener::DMXListener(const unsigned short universe) :
        _universe(universe) {
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
    _wrapper = new ola::client::OlaClientWrapper;
    if (!_wrapper->Setup()) {
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

    return ola::thread::Thread::Start();
}

void DMXListener::Stop() {
    _wrapper->GetSelectServer()->Terminate();
}

float DMXListener::getValue(const unsigned short address, const bool isFine) const {
    float value;
    auto rawValue = this->getRawValue(address, isFine);
    
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
    /*
    if (result.Success()) {
        BOOST_LOG_TRIVIAL(trace) << "Updated name of universe " << _universe;
    } else {
        BOOST_LOG_TRIVIAL(error) << "Failed to change name of universe " << _universe << ": " << result.Error();
    }
    */
}

void DMXListener::onUniverseRegister(const ola::client::Result &result) {
    /*
    if (result.Success()) {
        BOOST_LOG_TRIVIAL(info) << "Registered DMX listener on universe " << _universe;
    } else {
        BOOST_LOG_TRIVIAL(warning) << "Failed to register DMX listener for universe " << _universe << ": " << result.Error();
    }
    */
}

void DMXListener::onDMXReceived(const ola::client::DMXMetadata &metadata, const ola::DmxBuffer &data) {
    unsigned int length;
    data.Get(_universeData, &length);
}

uint8_t DMXListener::getByte(const unsigned short address) const {
    if ((address > 0) && (address <= 512)) {
        return _universeData[address-1];
    } else {
        return 0;
    }
}

