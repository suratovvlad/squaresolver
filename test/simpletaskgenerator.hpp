#pragma once

#include "simpletaskworker.hpp"

/**
 * \brief For testing propose.
 */
class SimpleTaskGenerator : public SimpleTaskWorker {

public:
    template<typename... Args>
    explicit SimpleTaskGenerator(Args &&... args)
            : SimpleTaskWorker{std::forward<Args>(args)...} {}

    void run() override;
};

