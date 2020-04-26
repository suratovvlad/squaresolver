#pragma once
#include "quadricequationworker.hpp"

class Consumer : QuadricEquationWorker {
public:

    template<typename... Args>
    explicit Consumer(Args&&... args)
        : QuadricEquationWorker{ std::forward<Args>(args)... } {}

    void run() override;
};
