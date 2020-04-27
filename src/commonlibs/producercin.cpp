#include "producercin.hpp"
#include <iostream>
#include <limits>
#include <memory>

void ProducerCin::run()
{
    std::cout << "Start producing ... " << std::endl;
    int input = 0;
    int count = 0;
    int skippedCount = 0;

    auto parameters = std::make_unique<Task>();

    for (;;) {
        std::cin >> input;

        if (std::cin.eof() || std::cin.bad()) {
            break;
        }
        else if (std::cin.fail()) {
            ++skippedCount;
            std::cin.clear(); // unset failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // skip bad input
        }
        else {
            if (count == 0)
            {
                parameters->a_ = input;
                ++count;
            }
            else if (count == 1)
            {
                parameters->b_ = input;
                ++count;
            }
            else if (count == 2)
            {
                parameters->c_ = input;
                ++count;
            }
            else {
                std::cout << "Schedule" << std::endl;
                tasksQueue_->schedule(parameters); // (ownership is transferred)
                count = 0;
                parameters = std::make_unique<Task>();
            }
            std::cout << input << std::endl;
        }
    }

    if (count != 0)
    {
        std::cout << "Not all parameters entered, guess other parameters as 0" << std::endl;
        tasksQueue_->schedule(parameters);
    }

    std::cout << "Insert poison pill" << std::endl;
    TaskPtr poisonPill = std::make_unique<PoisonPill>();
    tasksQueue_->schedule(poisonPill); // (ownership is transferred)

    std::cout << "End producing ... " << std::endl;
}
