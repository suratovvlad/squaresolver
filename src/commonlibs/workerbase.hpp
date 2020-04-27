#pragma once

/**
 * \brief Basic class for any type of Producers and Consumers
 * Contains Blocking Queue for their tasks.
 * Provides method run for execution in thread.
 * \tparam TasksQueuePtr Type of the shared pointer to the queue
 */
template<typename TasksQueuePtr>
class WorkerBase {

protected:
//    using Task = QuadraticEquation;
//    using TaskPtr = std::unique_ptr<Task>;
//    using TasksQueue = BlockingQueue<TaskPtr>;
//    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

    // Alias for convenience 
    using TasksQueuePtrType = TasksQueuePtr;

    TasksQueuePtr tasksQueue_;

public:
    explicit WorkerBase(TasksQueuePtr tasksQueue)
            : tasksQueue_{tasksQueue} {}

    virtual ~WorkerBase() = default;
    WorkerBase(const WorkerBase&) = default;
    WorkerBase(WorkerBase&&) = default;
    WorkerBase& operator=(const WorkerBase&) = default;
    WorkerBase& operator=(WorkerBase&&) = default;

    /**
     * \brief Pure virtual function. Executed in thread.
     */
    virtual void run() = 0;
};
