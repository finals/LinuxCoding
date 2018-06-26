#ifndef __TDB_TASK_QUEUE_H__
#define __TDB_TASK_QUEUE_H__

#include <deque>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <memory>
#include <thread>

namespace thread {

template<class T>
class TaskQueue {
private:
    std::mutex mutexQueue_;
    std::deque< std::shared_ptr<T> > queue_; //就绪任务队列
    std::mutex mutexConditPut_;
    std::condition_variable conditPut_; //条件变量
    std::mutex mutexDoingTask_;
    std::unordered_map< size_t, std::shared_ptr<T> > mapDoingTask_;

public:
    /**
    * @brief ：向队列的末尾插入任务
    * @param ：task 任务类
    */
    void put_back(std::shared_ptr<T> &task) 
    {
        std::unique_lock<std::mutex> lock(mutexQueue_);
        queue_.push_back(task);
        conditPut_.notify_one();
    }
    /**
    * @brief ：向队列的头部插入任务
    * @param ：task 任务类
    */
    void put_front(std::shared_ptr<T> &task)
    {
        std::unique_lock<std::mutex> lock(mutexQueue_);
        queue_.push_front(task);
        conditPut_.notify_one();
    }
    /**
    * @brief ：获取队首（并将任务加到运行任务列表中）
    * @return：任务类
    */
    std::shared_ptr<T> get(void)
    {
        std::unique_lock<std::mutex> lock(mutexQueue_);

        if (queue_.empty()) {
            return nullptr; 
        }

        std::lock_guard<std::mutex> lock_doing_task(mutexDoingTask_);
        std::shared_ptr<T> &task = queue_.front();
        mapDoingTask_.insert(std::make_pair(task->getID(), task));
        queue_.pop_front();

        return task;
    }
    /**
    * @brief ：获取整个双向链表的大小
    * @return：大小
    */
    size_t size(void)
    {
        std::unique_lock<std::mutex> lock(mutexQueue_);
        return queue_.size();
    }
    /**
    * @brief ：释放队列
    */
    void release(void)
    {
        delete_all_tasks();
        conditPut_.notify_all();
    }
    /**
    * @brief ：删除任务（从就绪队列删除，如果就绪队列没有，则看执行队列有没有，有的话置下取消状态位）
    * @param ：nID 任务的编号
    * @return：成功返回0 失败返回非0
    */
    int delete_task(size_t nID)
    {
        std::unique_lock<std::mutex> lock(mutexQueue_, std::defer_lock);
        lock.lock();

        auto it = queue_.begin();
        for (; it != queue_.end(); ++it) {
            if ((*it)->getID() == nID) {
                queue_.erase(it);
                lock.unlock();
                return 0;
            }
        }

        //下面的逻辑可能会造成死锁，这里先释放锁
        lock.unlock();

        //尝试取消正在执行的任务
        {
            std::lock_guard<std::mutex> lock_doing_task(mutexDoingTask_);
            auto it_map = mapDoingTask_.find(nID);
            if (it_map != mapDoingTask_.end()) {
                it_map->second->setCancelRequired();
            }
        }

        //等待任务执行完
        while (mapDoingTask_.count(nID)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        return 0;
    }
    /**
    * @brief ：删除所有任务
    * @return：成功返回0 失败返回非0
    */
    int delete_all_tasks(void)
    {
        std::unique_lock<std::mutex> lock(mutexQueue_, std::defer_lock);
        lock.lock();

        if (!queue_.empty()) {
            queue_.clear(); //清空
        }

        {
            std::lock_guard<std::mutex> lock_doing_task(mutexDoingTask_);
            if (!mapDoingTask_.empty()) {
                for (auto it_map = mapDoingTask_.begin(); it_map != mapDoingTask_.end(); ++it_map) {
                    it_map->second->setCancelRequired();
                }
            }
        }
        lock.unlock();

        //任务执行完后再返回
        while (mapDoingTask_.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        return 0;
    }
    /**
    * @brief ：任务完成回调（从运行列表中删除指定任务）
    * @param ：nID 任务的编号
    * @return：成功返回0 失败返回非0
    */
    int on_task_finished(size_t nID)
    {
        std::lock_guard<std::mutex> lock_doing_task(mutexDoingTask_);

        auto it_map = mapDoingTask_.find(nID);
        if (it_map != mapDoingTask_.end()) {
            mapDoingTask_.erase(it_map);
        }

        return 0;
    }
    /**
    * @brief ：判断任务是否执行完毕
    * @param ：nID 任务的编号
    * @return：任务类
    */
    std::shared_ptr<T> is_task_processed(size_t nID) 
    {
        std::lock_guard<std::mutex> lock_queue(mutexQueue_);
        for (auto it = queue_.begin(); it != queue_.end(); ++it) {
            if ((*it)->getID() == nID) {
                return *it;
            }
        }

        std::lock_guard<std::mutex> lock_doing_task(mutexDoingTask_);
        auto it_map = mapDoingTask_.find(nID);
        if (it_map != mapDoingTask_.end()) {
            return it_map->second;
        }

        return nullptr;
    }
    /**
    * @brief ：等待有任务到达（带超时：超时自动唤醒）
    * @param ：millsec 超时时间（毫秒）
    * @return：成功返回true 失败返回false
    */
    bool wait(std::chrono::milliseconds millsec) 
    {
        std::unique_lock<std::mutex> lock(mutexConditPut_);
        conditPut_.wait_for(lock, millsec);

        return true;
    }

};

} //namespace thread

#endif //__TDB_TASK_QUEUE_H__