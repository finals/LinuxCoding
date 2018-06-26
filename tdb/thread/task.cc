#include "task.h"
#include <atomic>

namespace thread {

std::atomic<size_t> Task::nRequestID_(100000);

Task::Task(void) : id_(nRequestID_++), createTime_(clock()), isCancelRequired_(false) {}


}
