#include "simpletaskgenerator.hpp"

#include <iostream>

void SimpleTaskGenerator::run() {
    std::cout << "Start scheduling ... " << std::endl;

    for (int i = 0; i < 500; ++i) {
        std::cout << "Scheduling i = " << i << std::endl;
        tasksQueue_->schedule(i);
    }

    std::cout << "Scheduling POISON_PILL " << POISON_PILL << std::endl;

    tasksQueue_->schedule(POISON_PILL);

    std::cout << "... End scheduling" << std::endl;
}
