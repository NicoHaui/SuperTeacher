//
// Created by samuel on 02.04.16.
//

#include "Logs.h"
#include <boost/log/expressions.hpp>

namespace logging = boost::log;

void log_init(void){
    logging::core::get()->set_filter(
            logging::trivial::severity >= logging::trivial::trace
    );
}