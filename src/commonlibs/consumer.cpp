#include "consumer.hpp"

#include <iostream>
#include <memory>
#include <sstream>

#include "solver.hpp"
#include "quadraticequation.hpp"

void Consumer::run()
{
    for (;;) {
        // for using dynamic_pointer_cast, because there is no such thing for unique_ptr
        auto task = std::shared_ptr<Task>{}; 

        {
            // Get task from queue
            auto task_unique = TaskPtr{};
            tasksQueue_->consume(task_unique);

            // transfer ownership to shared_ptr
            task = std::move(task_unique);
        }

        // Check with the cast if this task is Poison Pill
        if (std::dynamic_pointer_cast<PoisonPill>(task))
        {
            // Return poison pill back to queue, because in general case number of consumers could not be known
            // I decided not create a new poison pill to not transferring ownership back from shared_pointer.
            TaskPtr poisonPill = std::make_unique<PoisonPill>();
            tasksQueue_->schedule(poisonPill);

            // Exit from infinite loop
            break;
        }

        // Solve the equation with Solver.
        auto solver = Solver{};
        auto roots = solver.solve(task);

        // Use the stringstream for the output as described here https://stackoverflow.com/a/15034536/8369974
        // However solving of each equation could have different order, because of multiple threads for consumers.
        // I didn't implemented the synchronized (to the input order) output.
        auto stream = std::stringstream{};
        stream << "(" << task->a_ << " " << task->b_ << " " << task->c_ << ") => ";

        
        if (roots)
        {
            // If roots are found print roots
            stream << "(" << roots->x1_ << ", " << roots->x2_ << ")" << std::endl;
        }
        else
        {
            // If not, print no roots
            stream << "no roots" << std::endl;
        }

        // Put everything to cout with one <<
        std::cout << stream.str();
    }
}
