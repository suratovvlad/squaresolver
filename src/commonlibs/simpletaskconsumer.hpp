#pragma once

#include "simpletaskworker.hpp"

class SimpleTaskConsumer : public SimpleTaskWorker {
    int POISON_PILL = 1000;

public:
    template<typename... Args>
    explicit SimpleTaskConsumer(Args &&... args)
            : SimpleTaskWorker{std::forward<Args>(args)...} {}

    void run() override;
};