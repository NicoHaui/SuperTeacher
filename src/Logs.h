#pragma once

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>

#define LOG(x) BOOST_LOG_TRIVIAL(x)

void log_init(void);


