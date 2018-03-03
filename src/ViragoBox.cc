#include "ViragoBox.h"
#include "SFMLRenderer.h"
#include "DMXListener.h"
#include <boost/log/utility/setup.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions.hpp>
#include <algorithm>


namespace virago {

ViragoBox::ViragoBox(const unsigned int startAddress) {
    initLogging(true);

    _address = startAddress;
}

ViragoBox::~ViragoBox() {
}

void ViragoBox::run() {
    DMXListener dmx(1);
    SFMLRenderer r;

    dmx.newDataReceived = [&dmx,&r,this]() {
        float intens = dmx.getValue(_address,    false);
        float posX   = dmx.getValue(_address+1,  true);
        float posY   = dmx.getValue(_address+3,  true);
        float width  = dmx.getValue(_address+5,  true);
        float height = dmx.getValue(_address+7,  true);
        float red    = dmx.getValue(_address+9,  false);
        float green  = dmx.getValue(_address+10, false);
        float blue   = dmx.getValue(_address+11, false);
        float line   = dmx.getValue(_address+12, false);

        r.updateRectangleFromPercentages(intens, posX, posY, width, height, red, green, blue, line);
    };

    dmx.Start();
    r.start();

    dmx.Stop();
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

