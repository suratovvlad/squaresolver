
#ifndef MONITOR_HPP
#define MONITOR_HPP

#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
#include <thread>
#include <random>
#include <chrono>

#include "blockingqueue.hpp"
#include "workerbase.hpp"
#include "quadricequation.hpp"

//class BoundedBuffer
//{
//    std::queue<int> queue_;
//    const std::queue<int>::size_type maxSize_ = 10;
//public:
//
//    void push(const std::queue<int>::value_type & value)
//    {
////        if (queue_.size() < maxSize_)
////            queue_.push(value);
////        else
////        {
////            throw std::out_of_range{};
////        }
//        queue_.push(value);
//    }
//
////    void push(std::queue<int>::value_type && value)
////    {
////        queue_.push(std::forward<int>(value))
////    }
//
//    std::queue<int>::reference front()
//    {
//        return
//    }
//
//    bool empty() const {
//        return queue_.empty();
//    }
//
//    bool full() const {
//        return queue_.size() >= maxSize_;
//    }
//
//
//};



class QuadricEquationWorker : public WorkerBase<std::shared_ptr<BlockingQueue<std::unique_ptr<QuadricEquation>>>>
{
protected:
    struct PoisonPill : public QuadricEquation
    {};

    using Task = QuadricEquation;
    using TaskPtr = std::unique_ptr<Task>;
    using TasksQueue = BlockingQueue<TaskPtr>;
    using TasksQueuePtr = std::shared_ptr<TasksQueue>;

public:
    template<typename... Args>
    explicit QuadricEquationWorker(Args &&... args)
            : WorkerBase{std::forward<Args>(args)...} {}

};

class Producer : QuadricEquationWorker {


public:

    template<typename... Args>
    explicit Producer(Args &&... args)
            : QuadricEquationWorker{std::forward<Args>(args)...} {}

    void run() override
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
                    tasksQueue_->schedule(parameters);
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
        tasksQueue_->schedule(poisonPill);

        std::cout << "End producing ... " << std::endl;
    }
};

class Consumer : QuadricEquationWorker {
public:

    template<typename... Args>
    explicit Consumer(Args &&... args)
            : QuadricEquationWorker{std::forward<Args>(args)...} {}

    void run() override
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

            std::cout << "(" << task->a_ << "," << task->b_ << "," << task->c_ << ")=>" << std::endl;
        }
        std::cout << "End consuming ... " << std::endl;
    }
};

#endif // MONITOR_HPP