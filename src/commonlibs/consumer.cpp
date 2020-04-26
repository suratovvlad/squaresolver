#include "consumer.hpp"

#include <iostream>
#include <memory>
#include "solver.hpp"
#include "quadricequation.hpp"

void Consumer::run()
{
    std::cout << "Start consuming ... " << std::endl;
    for (;;) {
        auto task = std::shared_ptr<Task>{}; // for using dynamic_pointer_cast

        {
            auto task_unique = TaskPtr{};
            tasksQueue_->consume(task_unique);

            // transfer ownership to shared_ptr
            task = std::move(task_unique);
        }

        if (std::dynamic_pointer_cast<PoisonPill>(task))
        {
            std::cout << "Poison pill found, insert one more for other consumers" << std::endl;
            // I decided not create a new poison pill to not transferring ownership back from shared_pointer.
            TaskPtr poisonPill = std::make_unique<PoisonPill>();
            tasksQueue_->schedule(poisonPill);
            break;
        }

        auto solver = Solver{};
        auto roots = solver.solve(task);

        if (roots)
        {
            std::cout << "(" << task->a_ << " " << task->b_ << " " << task->c_ << ") => " 
                << "(" << roots->x1_ << ", " << roots->x2_ << ")" << std::endl;
        }
        else
        {
            std::cout << "(" << task->a_ << " " << task->b_ << " " << task->c_ << ") => no roots" << std::endl;
        }

    }
    std::cout << "End consuming ... " << std::endl;
}
