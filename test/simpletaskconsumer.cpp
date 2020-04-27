#include "simpletaskconsumer.hpp"
#include <iostream>
#include <random>
#include <thread>
#include <string>
#include <sstream>

void SimpleTaskConsumer::run() {
    std::cout << "Start consuming ... " << std::endl;

    for (;;) {
        int task = 0;
        tasksQueue_->consume(task);

        if (task == POISON_PILL) {
            std::cout << "POISON_PILL found: " << POISON_PILL << std::endl;
            // return poison pill back to queue,
            // because in general case number of consumers could not be known
            tasksQueue_->schedule(POISON_PILL);
            break;
        }

        std::cout << "Start task : " << task << std::endl;

        // sleep random time for simulation of some work
        std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
        std::uniform_int_distribution<> dist{10, 100};
        auto time = std::chrono::milliseconds{dist(eng)};
        std::this_thread::sleep_for(time);

        auto stream = std::stringstream{};
        stream << "End task : " << task
                  << " after time : " << std::to_string(time.count()) << std::endl;

        std::cout << stream.str();

    }
    std::cout << "... End consuming" << std::endl;
}
