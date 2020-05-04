#ifndef _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_SIMULATE_THREAD_H
#define _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_SIMULATE_THREAD_H

#pragma once

#include "space.h"
#include "threader.h"

#include <future>
#include <memory>
#include <mutex>
#include <thread>

// see comment in render_thread.h
Threader::Action simulator_action(std::mutex &, const std::shared_ptr<Space>,
                                  int sleep_millis, double dt);

#endif
