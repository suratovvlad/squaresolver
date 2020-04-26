#pragma once
#include "quadricequationworker.hpp"

class Producer : QuadricEquationWorker {

public:

    template<typename... Args>
    explicit Producer(Args&&... args)
        : QuadricEquationWorker{ std::forward<Args>(args)... } {}

    void run() override;
};