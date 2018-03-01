#include "ViragoBox.h"
#include "SFMLRenderer.h"
#include "DMXListener.h"
#include <boost/log/utility/setup.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions.hpp>


namespace virago {

ViragoBox::ViragoBox() {
    initLogging(true);
}

ViragoBox::~ViragoBox() {
}

void ViragoBox::run() {
    DMXListener dmx(1);
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

