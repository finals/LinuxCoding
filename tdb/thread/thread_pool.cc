#include <iostream>
#include <thread>

#include "task.h"
#include "task_queue.h"
#include "thread_pool.h"

namespace thread {

ThreadPool::ThreadPool(void) : taskQueue_(new TaskQueue<Task>()), atcWorking_(true), atcCurTotalThrNum_(0)
{
}

ThreadPool::~ThreadPool(void)
{
    // @note: 曾经因析构自动调用 release 触发了错误
    release();
}

int ThreadPool::init(const ThreadPoolConfig &config)
{
    if (config.dbTaskAddThreadRate < config.dbTaskSubThreadRate) {
        return 87;
    }

    threadPoolConfig_.nMaxThreadsNum = config.nMaxThreadsNum;
    threadPoolConfig_.nMinThreadsNum = config.nMinThreadsNum;
    threadPoolConfig_.dbTaskAddThreadRate = config.dbTaskAddThreadRate;
    threadPoolConfig_.dbTaskSubThreadRate = config.dbTaskSubThreadRate;

    int ret = 0;
    if (threadPoolConfig_.nMinThreadsNum > 0) {
        ret = add_process_threads(threadPoolConfig_.nMinThreadsNum);
    }

    return ret;
}

//添加任务
int ThreadPool::add_task(std::shared_ptr<Task> taskptr, bool priority)
{
    const double &rate = get_thread_task_rate();
    int ret = 0;
    if (priority) {
        if (rate > 1000) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        taskQueue_->put_front(taskptr);
    } else {
        if (rate > 100) { //检查任务数量
            taskptr->onCanceled();
            return 298;
        }

        taskQueue_->put_back(taskptr); //将任务入队列
    }

    //检查是否要扩展线程
    if (atcCurTotalThrNum_ < threadPoolConfig_.nMaxThreadsNum && rate > threadPoolConfig_.dbTaskAddThreadRate) {
        ret = add_process_threads(1);
    }

    return ret;
}

// 删除任务(从就绪队列删除，如果就绪队列没有，则看执行队列有没有，有的话置下取消状态位)
int ThreadPool::delete_task(size_t nID)
{
    return taskQueue_->delete_task(nID);
}

// 删除所有任务
int ThreadPool::delete_all_tasks(void)
{
    return taskQueue_->delete_all_tasks();
}

std::shared_ptr<Task> ThreadPool::is_task_processed(size_t nID)
{
    return taskQueue_->is_task_processed(nID);
}

// 释放资源(释放线程池、释放任务队列)
bool ThreadPool::release(void)
{
    // 1、停止线程池。2、清除就绪队列。3、等待执行队列为0
    release_thread_pool();
    taskQueue_->release();

    int i = 0;
    while (atcCurTotalThrNum_ != 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        //异常等待
        if (i++ == 10) {
            exit(23);
        }
    }

    atcCurTotalThrNum_ = 0;
    return true;
}

// 获取当前线程任务比
double ThreadPool::get_thread_task_rate(void)
{
    // @note :无所谓线程安全
    if (atcCurTotalThrNum_ != 0) {
        return taskQueue_->size() * 1.0 / atcCurTotalThrNum_;
    }

    return 0;
}

//当前线程是否需要结束
bool ThreadPool::should_end(void)
{
    bool bFlag = false;
    double dbThreadTaskRate = get_thread_task_rate();

    // 检查线程与任务比率
    if (!atcWorking_ || (atcCurTotalThrNum_ > threadPoolConfig_.nMinThreadsNum
        && dbThreadTaskRate < threadPoolConfig_.dbTaskSubThreadRate))
        bFlag = true;

    return bFlag;
}

//添加指定数量的处理线程
int ThreadPool::add_process_threads(int nThreadsNum)
{
    try {
        for (; nThreadsNum > 0; --nThreadsNum) {
            std::thread(&ThreadPool::task_process_thread, this).detach();
        }
    }
    catch (...) {
        return 155;
    }

    return 0;
}

//释放线程池
bool ThreadPool::release_thread_pool(void) 
{
    threadPoolConfig_.nMinThreadsNum = 0;
    threadPoolConfig_.dbTaskSubThreadRate = 0;
    atcWorking_ = false;
    return true;
}

//任务处理线程函数
void ThreadPool::task_process_thread(void)
{
    //线程数量加1
    atcCurTotalThrNum_.fetch_add(1);
    std::chrono::milliseconds mills_sleep(500);

    std::shared_ptr<Task> pTask;
    while (atcWorking_) {
        pTask = taskQueue_->get();
        if (pTask == nullptr) {
            if (should_end()) {
                break;
            }

            //进入睡眠池
            taskQueue_->wait(mills_sleep);
            continue;
        }

        //检测任务取消状态
        if (pTask->isCancelRequired()) {
            pTask->onCanceled();
        } else {
            pTask->onCompleted(pTask->doWork()); //处理任务
        }

        taskQueue_->on_task_finished(pTask->getID()); //从运行任务队列中移除任务

        //判断线程是否需要结束
        if (should_end()) {
            break;
        }
    }

    atcCurTotalThrNum_.fetch_sub(1); //线程计数减一
}

} //namespace thread

