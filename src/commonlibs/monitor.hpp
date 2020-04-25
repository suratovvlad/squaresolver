
#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
#include <thread>
#include <random>
#include <chrono>

#include "solver.hpp"

//class BoundedBuffer
//{
//    std::queue<int> queue_;
//    const std::queue<int>::size_type maxSize_ = 10;
//public:
//
//    void push(const std::queue<int>::value_type & value)
//    {
////        if (queue_.size() < maxSize_)
////            queue_.push(value);
////        else
////        {
////            throw std::out_of_range{};
////        }
//        queue_.push(value);
//    }
//
////    void push(std::queue<int>::value_type && value)
////    {
////        queue_.push(std::forward<int>(value))
////    }
//
//    std::queue<int>::reference front()
//    {
//        return
//    }
//
//    bool empty() const {
//        return queue_.empty();
//    }
//
//    bool full() const {
//        return queue_.size() >= maxSize_;
//    }
//
//
//};

template<class Task>
class BlockingQueue {
    std::queue<Task> queue_;
    std::mutex queueLock_;
    std::condition_variable queueEmpty_;
    std::condition_variable queueFull_;

    using CapacityType = typename std::queue<Task>::size_type;
    const CapacityType maxSize_ = 10;

    bool empty() const {
        return queue_.empty();
    }

    bool full() const {
        return queue_.size() >= maxSize_;
    }

public:
    BlockingQueue(const CapacityType& capacity)
        : maxSize_(capacity)
    {

    }

    ~BlockingQueue() = default; // TODO: unlock mutex needed?
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue(BlockingQueue&&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;
    BlockingQueue& operator=(BlockingQueue&&) = delete;

    // TODO: think about &&
    void schedule(Task& task) {
        // Acquire lock for initial predicate check.
        std::unique_lock<std::mutex> lock(queueLock_);

        while (full()) // Check if the queue is non-full.
        {
            // Wait until queue becomes non-full
            queueFull_.wait(lock, [this]() {
                return !full();
            });
        }

        // Critical section that requires the queue to be non-full.
        queue_.push(std::move(task)); // Add the task to the queue.

        // Notify one or all that queue is non-empty
        queueEmpty_.notify_all(); //queueEmpty_.notify_one();

        // End of critical sections related to the queue.
    }

    void consume(Task& task) {
        // Acquire lock for initial predicate check.
        std::unique_lock<std::mutex> lock(queueLock_);

        while (empty()) // Check if the queue is non-empty.
        {
            // Wait until queue becomes non-empty
            queueEmpty_.wait(lock, [this] {
                return !empty();
            });
        }

        // Critical section that requires the queue to be non-empty

        // Take a task off of the queue.
        task = std::move(queue_.front());
        queue_.pop();

        // Notify one or all that queue is non-full
        queueFull_.notify_all(); //queueFull_.notify_one();

//        return task;
    }
};

template<class TasksQueuePtr>
class WorkerBase {

protected:
//    using Task = QuadricEquation;
//    using TaskPtr = std::unique_ptr<Task>;
//    using TasksQueue = BlockingQueue<TaskPtr>;
//    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

    TasksQueuePtr tasksQueue_;

public:
    explicit WorkerBase(TasksQueuePtr tasksQueue)
    : tasksQueue_{tasksQueue}
    {

    }

    virtual ~WorkerBase() = default;

    virtual void run() = 0;
};


class SimpleTaskGenerator : public WorkerBase<std::shared_ptr<BlockingQueue<int>>> {

//    using Task = int;
//    using TaskPtr = std::unique_ptr<Task>;
//    using TasksQueue = BlockingQueue<TaskPtr>;
//    using TasksQueuePtr = std::shared_ptr<TasksQueue>;
    int POISON_PILL = 1000;

public:
    explicit SimpleTaskGenerator(std::shared_ptr<BlockingQueue<int>> tasksQueue)
        : WorkerBase{tasksQueue}
    {

    }
    void run() override
    {
        std::cout << "Start scheduling ... " << std::endl;
        for (int i = 0; i < 500; ++i)
        {
            std::cout << "Scheduling i = " << i << std::endl;
            tasksQueue_->schedule(i);
        }

        std::cout << "Scheduling POISON_PILL " << POISON_PILL << std::endl;

        tasksQueue_->schedule(POISON_PILL);


        std::cout << "... End scheduling" << std::endl;
    }
};

class SimpleTaskConsumer : public WorkerBase<std::shared_ptr<BlockingQueue<int>>>
{
//    std::shared_ptr<BlockingQueue<int>> tasksQueue_;
    int POISON_PILL = 1000;

public:
    explicit SimpleTaskConsumer(std::shared_ptr<BlockingQueue<int>> tasksQueue)
    : WorkerBase{tasksQueue}
    {

    }
    void run() override
    {
        std::cout << "Start consuming ... " << std::endl;
        for (;;)
        {
            int task = 0;
            tasksQueue_->consume(task);

            if (task == POISON_PILL) {
                std::cout << "POISON_PILL found" << POISON_PILL << std::endl;
                // return poison pill back to queue,
                // because in general case number of consumers could not be known
                tasksQueue_->schedule(POISON_PILL);
                break;
            }

            std::cout << "Start task : " << task << std::endl;

            std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
            std::uniform_int_distribution<> dist{10, 100};
            auto time = std::chrono::milliseconds{dist(eng)};
            std::this_thread::sleep_for(time);

            std::cout << "End task : " << task
                << " after time : " << std::to_string(time.count()) << std::endl;

        }
        std::cout << "... End consuming" << std::endl;
    }
};

class Producer {
    using Task = QuadricEquation;
    using TaskPtr = std::unique_ptr<Task>;
    using TasksQueue = BlockingQueue<TaskPtr>;
    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

    TasksQueuePtr tasksQueue_;
public:

    explicit Producer(TasksQueuePtr tasksQueue)
            : tasksQueue_{tasksQueue}
    {

    }

    void run()
    {
        int input = 0;
        int count = 0;
        int skippedCount = 0;

        auto parameters = std::make_unique<Task>();

        for (;;) {
            std::cin >> input;

            if (std::cin.eof() || std::cin.bad()) {
                break;
            }
            else if (std::cin.fail()) {
                ++skippedCount;
                std::cin.clear(); // unset failbit
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // skip bad input
            }
            else {
                if (count == 0)
                {
                    parameters->a_ = input;
                    ++count;
                }
                else if (count == 1)
                {
                    parameters->b_ = input;
                    ++count;
                }
                else if (count == 2)
                {
                    parameters->c_ = input;
                    ++count;
                }
                else {
                    tasksQueue_->schedule(parameters);
                    count = 0;
                    parameters = std::make_unique<Task>();
                }
                std::cout << input << std::endl;
            }
        }
    }
};

class Consumer {

};