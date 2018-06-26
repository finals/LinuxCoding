#ifndef __TDB_TASK_H__
#define __TDB_TASK_H__

#include <time.h>
#include <atomic>

namespace thread {

//任务基类
class Task {
protected:
    size_t   id_;          //任务的唯一标识
    clock_t  createTime_;  //任务创建时间(非Unix时间戳)

private:
    static std::atomic<size_t> nRequestID_;
    std::atomic<bool> isCancelRequired_;

public:
    Task(void);
    virtual ~Task(void) {}

public:
    virtual int doWork(void) = 0; //任务类虚接口，继承这个类必须实现这个接口
    virtual int onCanceled(void) { return 1; } //任务已取消回调
    virtual int onCompleted(int) { return 1; } //任务已完成回调
    virtual bool isTimeout(const clock_t &now)
    {
         return ((now - createTime_) > 5000);
    }
    size_t getID(void) { return id_; } //获取任务ID
    bool isCancelRequired(void) { return isCancelRequired_; }  //获取任务取消状态
    void setCancelRequired(void) { isCancelRequired_ = true; } //设置任务取消状态
};

//__declspec(selectany) std::atomic<size_t> Task::nRequestID_(100000);
//std::atomic<size_t> Task::nRequestID_(100000);

} //namespace thread

#endif //__TDB_TASK_H__