#pragma once

#include <boost/log/trivial.hpp>
#include <thread>

#include "Utils.h"
#include "Settings.h"

namespace Timer
{
    void create(std::unique_ptr<ThreadData> &data);
}