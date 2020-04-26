#pragma once
#include "quadricequationworker.hpp"

class Producer : QuadricEquationWorker {

private:

    std::vector<std::string> rawData_;

public:

    explicit Producer(TasksQueuePtrType queue, std::vector<std::string>&& data)
        : QuadricEquationWorker{ queue } 
        , rawData_{std::move(data)}
    {}

    void run() override;
};