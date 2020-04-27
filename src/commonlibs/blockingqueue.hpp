#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

/**
 * \brief Implementation of the Blocking Queue.
 * It is the basic thing resolving Producer-Consumer problem.
 *
 * Good description of the problem could be found here
 * https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
 *
 * The blocking queue implementation was taken from several sources
 * The main source: https://en.wikipedia.org/wiki/Monitor_(synchronization)#Solving_the_bounded_producer/consumer_problem
 * Example of implementation https://gist.github.com/dpressel/de9ea7603fa3f20b55bf
 *
 * There is a not clear what is better to use: notify_one or notify_all,
 * but it should not be an issue to use notify_all as it done here
 * 
 * The separate question is about when to unlock mutex - before notifying or after
 * There is a huge discussion https://stackoverflow.com/questions/17101922/do-i-have-to-acquire-lock-before-calling-condition-variable-notify-one/17102100#17102100
 * The main answer points the mutex could be unlocked before notification, but it should not be an issue to notify first.
 * However there is a strange answer where some person votes for notification before unlocking https://stackoverflow.com/a/52671238/8369974
 *
 *
 * \tparam Task underlying type for what the queue should save a
 */
template<typename Task>
class BlockingQueue final
{
    // A thread-unsafe buffer of tasks.
    std::queue<Task> queue_;

    // A mutex for the buffer of tasks.
    std::mutex queueLock_;

    // A condition variable for consumer threads waiting for the queue to become non-empty.
    // Its associated lock is "queueLock".
    std::condition_variable queueEmpty_;

    // A condition variable for producer threads waiting for the queue to become non-full.
    // Its associated lock is also "queueLock".
    std::condition_variable queueFull_;

    // alias for convenience
    using CapacityType = typename std::queue<Task>::size_type;

    // Maximum size of the queue. Configured with constructor.
    const CapacityType capacity_;

    // Warning if result discarded https://en.cppreference.com/w/cpp/language/attributes/nodiscard
    [[nodiscard]] bool empty() const {
        return queue_.empty();
    }

    // Warning if result discarded https://en.cppreference.com/w/cpp/language/attributes/nodiscard
    [[nodiscard]] bool full() const {
        return queue_.size() >= capacity_;
    }

public:
    explicit BlockingQueue(const CapacityType& capacity)
        : capacity_(capacity)
    {
    }

    // Rule of five in action.
    ~BlockingQueue() = default;
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue(BlockingQueue&&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;
    BlockingQueue& operator=(BlockingQueue&&) = delete;

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

        // End of critical sections related to the queue.
    }
};
