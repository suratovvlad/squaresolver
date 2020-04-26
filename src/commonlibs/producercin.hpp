#pragma once
#include "quadricequationworker.hpp"

class ProducerCin : QuadricEquationWorker {

public:

    template<typename... Args>
    explicit ProducerCin(Args&&... args)
        : QuadricEquationWorker{ std::forward<Args>(args)... } {}

    void run() override;
};