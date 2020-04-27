#pragma once

#include <blockingqueue.hpp>
#include <workerbase.hpp>

/**
 * \brief For testing propose.
 */
class SimpleTaskWorker : public WorkerBase<std::shared_ptr<BlockingQueue<int>>> {
protected:
    int POISON_PILL = std::numeric_limits<int>::max();
public:
    template<typename... Args>
    explicit SimpleTaskWorker(Args &&... args)
            : WorkerBase{std::forward<Args>(args)...} {}
};