#ifndef NBO_RENDER_THREAD_H
#define NBO_RENDER_THREAD_H

#include "space.h"
#include "threader.h"

#include <memory>
#include <mutex>

// mutex is a ptr rather than a ref because google style says all refs should be
// const and it cant be const since we're locking it
// NOTE: undid that cause it made a segfault...
Threader::Action renderer_action(std::mutex &, const std::shared_ptr<Space>,
                                 int);

#endif
