#ifndef _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_RENDER_THREAD_H
#define _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_RENDER_THREAD_H

#pragma once

#include "space.h"
#include "threader.h"

#include <memory>
#include <mutex>

Threader::Action renderer_action(std::mutex &, std::shared_ptr<Space>, int);

#endif
