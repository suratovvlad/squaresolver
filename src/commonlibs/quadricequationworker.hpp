#pragma once
#include "quadricequation.hpp"
#include "blockingqueue.hpp"
#include "workerbase.hpp"

class QuadricEquationWorker : public WorkerBase<std::shared_ptr<BlockingQueue<std::unique_ptr<QuadricEquation>>>>
{
protected:
    struct PoisonPill : public QuadricEquation
    {};

    using Task = QuadricEquation;
    using TaskPtr = std::unique_ptr<Task>;
    using TasksQueue = BlockingQueue<TaskPtr>;
    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

public:
    template<typename... Args>
    explicit QuadricEquationWorker(Args&&... args)
        : WorkerBase{ std::forward<Args>(args)... } {}

};
