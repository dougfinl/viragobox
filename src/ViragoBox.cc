#include "ViragoBox.h"
#include "SFMLRenderer.h"
#include "DMXListener.h"
#include <boost/log/utility/setup.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions.hpp>


namespace virago {

ViragoBox::ViragoBox(const unsigned int startAddress) {
    initLogging(true);

    _address = startAddress;
    _rectangle = std::make_shared<Rectangle>();
}

ViragoBox::~ViragoBox() {
}

void ViragoBox::run() {
    DMXListener dmx(1);

    dmx.newDataReceived = [&dmx,this]() {
        Rectangle newRect;

        // Populate the rectangle's values
        float intens          = dmx.getValue(_address+1,  false);
        newRect.pos.x         = dmx.getValue(_address+2,  true);
        newRect.pos.y         = dmx.getValue(_address+4,  true);
        newRect.size.width    = dmx.getValue(_address+6,  true);
        newRect.size.height   = dmx.getValue(_address+8,  true);
        newRect.color.r       = dmx.getValue(_address+10, false);
        newRect.color.g       = dmx.getValue(_address+11, false);
        newRect.color.b       = dmx.getValue(_address+12, false);
        newRect.lineThickness = dmx.getValue(_address+13, false);

        // Update the value of the existing rectangle
        *_rectangle = newRect;
    };

    dmx.Start();

    SFMLRenderer r;
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

