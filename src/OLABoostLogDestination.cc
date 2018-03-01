#include "OLABoostLogDestination.h"
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string/trim.hpp>


namespace ola {

void OLABoostLogDestination::Write(ola::log_level level, const std::string &log_line) {
    auto text = std::string("(OLA) ").append(log_line);
    boost::algorithm::trim(text);

    switch (level) {
        case log_level::OLA_LOG_FATAL:
            BOOST_LOG_TRIVIAL(fatal) << text;
            break;
        case log_level::OLA_LOG_WARN:
            BOOST_LOG_TRIVIAL(warning) << text;
            break;
        case log_level::OLA_LOG_DEBUG:
            BOOST_LOG_TRIVIAL(debug) << text;
            break;
        case log_level::OLA_LOG_INFO:
            BOOST_LOG_TRIVIAL(info) << text;
            break;
        default:
            break;
    }
}

} // namespace ola
