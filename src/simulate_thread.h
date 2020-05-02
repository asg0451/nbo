#pragma once

#include "space.h"
#include "threader.h"

#include <future>
#include <memory>
#include <mutex>
#include <thread>

Threader::Action simulator_action(std::mutex &, std::shared_ptr<Space>, int);
