#ifndef __TDB_THREAD_POOL_H__
#define __TDB_THREAD_POOL_H__

#include <atomic>
#include <memory>
#include <mutex>

#include "task_queue.h"

namespace thread {

class Task;

class ThreadPool {
public:
    //线程池配置参数
    typedef struct tag_thread_pool_config {
        int nMaxThreadsNum;           // 最大线程数量
        int nMinThreadsNum;           // 最小线程数量
        double dbTaskAddThreadRate;  // 增 最大线程任务比 (任务数量与线程数量，什么比例的时候才加)
        double dbTaskSubThreadRate;  // 减 最小线程任务比 (任务数量与线程数量，什么比例的时候才减)
    }ThreadPoolConfig;

private:
    std::shared_ptr< TaskQueue<Task> > taskQueue_; //任务队列
    ThreadPoolConfig threadPoolConfig_;   // 线程池配置(如果最小线程数量为1，则表示需要一个常驻的处理线程)
    std::atomic<bool> atcWorking_;        //线程池是否被要求结束
    std::atomic<int>  atcCurTotalThrNum_; //当前线程数量

public:
    ThreadPool(void);
    ~ThreadPool(void);

    /**
    * @brief ：线程池资源配置初始化
    * @param ：config 初始化的配置信息
    * @return：0 执行成功  非0 执行失败
    */
    int init(const ThreadPoolConfig &config);
    /**
    * @brief ：释放资源（释放线程池、释放任务队列）
    * @return：true 执行成功  false 执行失败
    */
    bool release(void);
    /**
    * @brief ：添加任务
    * @param ：taskptr 任务类
    * @param ：priority 是否有限处理 true：优先处理
    * @return：0 执行成功  非0 执行失败
    */
    int add_task(std::shared_ptr<Task> taskptr, bool priority = false);
    /**
    * @brief ：删除任务（从就绪队列删除，如果就绪队列没有，则看执行队列有没有，有的话置下取消状态位）
    * @param ：nID 任务编号
    * @return：0 执行成功  非0 执行失败
    */
    int delete_task(size_t nID);
    /**
    * @brief ：删除所有任务
    * @return：0 执行成功  非0 执行失败
    */
    int delete_all_tasks(void);
    /**
    * @brief ：判断任务是否执行完毕
    * @param ：nID 任务编号
    * @return：执行完毕，执行完返回null，否则返回任务指针
    */
    std::shared_ptr<Task> is_task_processed(size_t nID);

private:
    /**
    * @brief ：获取当前线程任务比
    * @return：线程任务比
    */
    double get_thread_task_rate(void);
    /**
    * @brief ：当前线程是否需要结束
    * @return：true:可以结束 false:不可以结束
    * @note  ：已考虑到最小线程数量
    */
    bool should_end(void);
    /**
    * @brief ：添加指定数量的处理线程
    * @param ：nThreadsNum 添加的线程数量
    * @return：0 执行成功  非0 执行失败
    */
    int add_process_threads(int nThreadNum);
    /**
    * @brief ：释放线程池
    * @return：true 执行成功  false 执行失败
    */
    bool release_thread_pool(void);
    /**
    * @brief ：任务处理线程函数
    */
    void task_process_thread(void);
};

} //namespace thread

#endif //__TDB_THREAD_POOL_H__