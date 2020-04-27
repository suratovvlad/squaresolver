#pragma once
#include "quadraticequation.hpp"
#include "blockingqueue.hpp"
#include "workerbase.hpp"


/**
 * \brief Base class for the Producer and Consumer
 * that would be used for the resolving quadratic equations.
 */
class QuadraticEquationWorker : public WorkerBase<std::shared_ptr<BlockingQueue<std::unique_ptr<QuadraticEquation>>>>
{
protected:

    
    /**
     * \brief Specific pattern for stopping consumers threads.
     * Explanation could be found here https://dzone.com/articles/producers-and-consumers-part-3
     *
     * The trick here is that we put to the same queue specific object, and if consumer founds it
     * he breaks from infinite loop.
     *
     * I decided to use the specific class as the derived from QuadraticEquation to have the ability
     * to pass it to the same queue.
     * Consumer would check every task for casting to this type, and if the casting would be successful
     * it would break from infinite loop, otherwise it would continue to work on the taken task.
     */
    struct PoisonPill : public QuadraticEquation
    {};

    // Aliases for the convenience
    using Task = QuadraticEquation;
    using TaskPtr = std::unique_ptr<Task>;
    using TasksQueue = BlockingQueue<TaskPtr>;
    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

public:

    /**
     * \brief Generic constructor for forwarding all arguments to base class.
     * Example taken from here https://stackoverflow.com/a/14122944/8369974
     */
    template<typename... Args>
    explicit QuadraticEquationWorker(Args&&... args)
        : WorkerBase{ std::forward<Args>(args)... } {}

};
