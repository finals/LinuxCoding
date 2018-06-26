#ifndef __FUNCTIONTASK_H__
#define __FUNCTIONTASK_H__

#include <functional>

#include "../task.h"

class FunctionTask :
    public thread::Task
{

private:

    typedef std::function<int(void)> PvFunc;

public:
    FunctionTask(std::function<int(void)> f) : pf_(f) {}
    FunctionTask(void) :pf_ (nullptr) {}

    virtual FunctionTask(void) {}


    template <typename F, typename... Args>
    void 
	asynBind(F(*f)(Args...), Args... args) {
        pf_ = std::bind(f, args...);
    }


    virtual int 
	doWork(void) {
        if (pf_ == nullptr)
            return 86;
        return pf_();
    };

private:

    PvFunc pf_;

};

#endif // __FUNCTIONTASK_H__

