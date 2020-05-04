#pragma once

#include "space.h"
#include "threader.h"

#include <memory>
#include <mutex>

Threader::Action renderer_action(std::mutex &, std::shared_ptr<Space>, int);
