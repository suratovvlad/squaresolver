#include "producer.hpp"

#include <memory>
#include <string>

void Producer::run()
{
    auto parameters = std::make_unique<Task>();

    auto currentParameter = Parameter::A;

    // Iterate over all strings
    for (const auto& paramStr : rawData_)
    {
        try {
            // Try to parse string to long long.
            // I didn't implemented the Arbitrary-precision arithmetic, so I use largest available integer type.
            // It could throw exceptions described here https://en.cppreference.com/w/cpp/string/basic_string/stol
            const auto param = std::stoll(paramStr);

            switch (currentParameter)
            {
            case Parameter::A:
                parameters->a_ = param;             // write down parameter A
                currentParameter = Parameter::B;    // switch to next parameter
                break;
            case Parameter::B:
                parameters->b_ = param;             // write down parameter B
                currentParameter = Parameter::C;    // switch to next parameter
                break;
            case Parameter::C:
                parameters->c_ = param;                 // write down parameter C
                currentParameter = Parameter::A;        // switch to next parameter
                tasksQueue_->schedule(parameters);      // put parameters to queue (ownership is transferred)
                parameters = std::make_unique<Task>();     // create new pointer.
                break;
            }
        }
        catch (std::invalid_argument&) {
            // Skip invalid argument
            continue;
        }
        catch (std::out_of_range&) {
            // Skip another conversion error
            continue;
        }
        catch (std::exception& exc) {
            // Skip if something bad happened
            continue;
        }
    }

    // Specific case on last input.
    // If we have only 1st or 1st and 2nd parameters, then we should assume other parameters as 0
    if (currentParameter != Parameter::A)
    {
        tasksQueue_->schedule(parameters);
    }

    // End of work, insert poison pill to queue.
    TaskPtr poisonPill = std::make_unique<PoisonPill>();
    tasksQueue_->schedule(poisonPill);
}
