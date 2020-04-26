#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename Task>
class BlockingQueue final
{
    std::queue<Task> queue_;
    std::mutex queueLock_;
    std::condition_variable queueEmpty_;
    std::condition_variable queueFull_;

    using CapacityType = typename std::queue<Task>::size_type;
    const CapacityType capacity_ = 10;

    bool empty() const {
        return queue_.empty();
    }

    bool full() const {
        return queue_.size() >= capacity_;
    }

public:
    explicit BlockingQueue(const CapacityType& capacity)
            : capacity_(capacity)
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
