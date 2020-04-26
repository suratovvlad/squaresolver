#include "producer.hpp"
//#include <iostream>
//#include <limits>
#include <memory>
#include <string>

void Producer::run()
{
    //std::cout << "Start producing ... " << std::endl;

    auto parameters = std::make_unique<Task>();

    auto currentParameter = Parameter::A;

    for (const auto& paramStr : rawData_)
    {
        try {
            const auto param = std::stoll(paramStr);

            switch (currentParameter)
            {
            case Parameter::A:
                parameters->a_ = param;
                currentParameter = Parameter::B;
                break;
            case Parameter::B:
                parameters->b_ = param;
                currentParameter = Parameter::C;
                break;
            case Parameter::C:
                parameters->c_ = param;
                currentParameter = Parameter::A;
                tasksQueue_->schedule(parameters);
                parameters = std::make_unique<Task>();
                break;
            }
        }
        catch (std::invalid_argument&) {
            //std::cout << "invalid argument, skip" << std::endl;
            continue;
        }
        catch (std::out_of_range&) {
            //std::cout << "unsupported integer length" << std::endl;
            continue;
        }
        catch (std::exception& exc) {
            //std::cout << "something really bad happend: \n" << exc.what() << std::endl;
            continue;
        }
    }

    if (currentParameter != Parameter::A)
    {
        //std::cout << "Not all parameters entered, guess other parameters as 0" << std::endl;
        tasksQueue_->schedule(parameters);
    }

    //std::cout << "Insert poison pill" << std::endl;
    TaskPtr poisonPill = std::make_unique<PoisonPill>();
    tasksQueue_->schedule(poisonPill);

    //std::cout << "End producing ... " << std::endl;
}
