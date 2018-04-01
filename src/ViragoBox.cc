#include "ViragoBox.h"
#include <boost/log/utility/setup.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions.hpp>


namespace virago {

ViragoBox::ViragoBox(const ViragoBoxOptions options) {
    initLogging(options.debug);

    _renderer = std::make_unique<SFMLRenderer>(options.resX, options.resY, options.fullscreen);
    _dmx      = std::make_unique<DMXListener>(options.address);

    _dmx->newDataReceived = [options,this]() {
        float intens = _dmx->getValue(options.address,    false);
        float posX   = _dmx->getValue(options.address+1,  true);
        float posY   = _dmx->getValue(options.address+3,  true);
        float width  = _dmx->getValue(options.address+5,  true);
        float height = _dmx->getValue(options.address+7,  true);
        float red    = _dmx->getValue(options.address+9,  false);
        float green  = _dmx->getValue(options.address+10, false);
        float blue   = _dmx->getValue(options.address+11, false);
        float line   = _dmx->getValue(options.address+12, false);

        _renderer->updateRectangleFromPercentages(intens, posX, posY, width, height, red, green, blue, line);

        int control = _dmx->getRawValue(options.address+13, false);
        if (control == 255) {
            _renderer->showAlignmentGrid();
        } else {
            _renderer->showAlignmentGrid(false);
        }
    };
}

ViragoBox::~ViragoBox() {
}

void ViragoBox::run() {
    _dmx->Start();
    _renderer->start();

    // Once the rendeder is closed...
    _dmx->Stop();
}

void ViragoBox::initLogging(const bool debug) {
    boost::log::add_console_log(
            std::cout,
            boost::log::keywords::format = (
                boost::log::expressions::stream << "["
                << boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S.%f")
                << "] "
                << boost::log::trivial::severity
                << "\t> "
                << boost::log::expressions::smessage
                ),
            boost::log::keywords::auto_flush = true
            );

    boost::log::add_common_attributes();

    if (debug) {
        boost::log::core::get()->set_filter(
                boost::log::trivial::severity >= boost::log::trivial::trace
                );
    } else {
        boost::log::core::get()->set_filter(
                boost::log::trivial::severity >= boost::log::trivial::info
                );
    }

    BOOST_LOG_TRIVIAL(debug) << "Initialised logging";
}

}

