#pragma once

#include "simpletaskworker.hpp"

/**
 * \brief For testing propose.
 */
class SimpleTaskConsumer : public SimpleTaskWorker {

public:
    template<typename... Args>
    explicit SimpleTaskConsumer(Args &&... args)
            : SimpleTaskWorker{std::forward<Args>(args)...} {}

    void run() override;
};