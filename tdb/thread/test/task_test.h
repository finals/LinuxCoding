#ifndef __TASKTEST_H__
#define __TASKTEST_H__

#include <iostream>

#include "../task.h"

class TaskTest
    : public thread::Task
{
public:
    TaskTest() {
        std::cout << "task : " << id_ << " is create." << std::endl;
    }
    virtual ~TaskTest() {}

    virtual int doWork() {
        // 开始工作
        std::cout << "task : " << id_ << " doing." << std::endl;
        return 0;
    }

    virtual int onCanceled(void) {
        // 任务被取消
        std::cout << "task : " << id_ << " canceled." << std::endl;
        return 0;
    }
    // 任务已完成
    virtual int onCompleted(int) {
        // 任务已完成，返回码为code
        std::cout << "task : " << id_ << " completed." << std::endl;
        return 0;
    }
};

#endif // __TASKTEST_H__

