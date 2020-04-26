#pragma once

template<typename TasksQueuePtr>
class WorkerBase {

protected:
//    using Task = QuadricEquation;
//    using TaskPtr = std::unique_ptr<Task>;
//    using TasksQueue = BlockingQueue<TaskPtr>;
//    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

    TasksQueuePtr tasksQueue_;

public:
    explicit WorkerBase(TasksQueuePtr tasksQueue)
            : tasksQueue_{tasksQueue} {}

    virtual ~WorkerBase() = default;

    virtual void run() = 0;
};
