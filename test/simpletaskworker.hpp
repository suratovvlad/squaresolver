#pragma once

#include <blockingqueue.hpp>
#include <workerbase.hpp>

class SimpleTaskWorker : public WorkerBase<std::shared_ptr<BlockingQueue<int>>> {
protected:
    int POISON_PILL = 1000;
public:
    template<typename... Args>
    explicit SimpleTaskWorker(Args &&... args)
            : WorkerBase{std::forward<Args>(args)...} {}
};