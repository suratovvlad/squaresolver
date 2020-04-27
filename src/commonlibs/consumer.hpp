#pragma once
#include "quadraticequationworker.hpp"

/**
 * \brief Consumer. It takes task from the task queue and executes it.
 * For this particular program, it takes parameters of quadratic equation
 * from the queue and delegates solving of this equation to the Solver class.
 */
class Consumer final : QuadraticEquationWorker {
public:
    /**
     * \brief Generic constructor for forwarding all arguments to base class.
     * Example taken from here https://stackoverflow.com/a/14122944/8369974
     */
    template<typename... Args>
    explicit Consumer(Args&&... args)
        : QuadraticEquationWorker{ std::forward<Args>(args)... } {}

    void run() override;
};
