#pragma once
#include "quadraticequationworker.hpp"

/**
 * \brief Producer.
 * For this particular program, it parses the incoming vector of strings
 * to the parameters of quadratic equation.
 * Then it puts parsed parameters to the blocking queue.
 */
class Producer final : QuadraticEquationWorker {

    // arguments from argv
    std::vector<std::string> rawData_;

public:

    explicit Producer(TasksQueuePtrType queue, std::vector<std::string>&& data)
        : QuadraticEquationWorker{ queue } 
        , rawData_{std::move(data)}
    {}

    void run() override;
};