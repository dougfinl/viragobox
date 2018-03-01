#ifndef OLA_BOOST_LOG_DESTINATION_H_
#define OLA_BOOST_LOG_DESTINATION_H_

#include <ola/Logging.h>


namespace ola {

class OLABoostLogDestination : public LogDestination {
    public:
        virtual void Write(log_level level, const std::string &log_line);
};

} // namespace ola


#endif // OLA_BOOST_LOG_DESTINATION_H_

