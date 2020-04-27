
#define CATCH_CONFIG_MAIN

#include <iostream>
#include <catch2/catch.hpp>
#include <thread>

#include "simpletaskgenerator.hpp"
#include "simpletaskconsumer.hpp"
#include <solver.hpp>
#include <quadraticequation.hpp>

TEST_CASE("simple equation, D > 0")
{
    auto equation = std::make_shared<QuadraticEquation>();
    equation->a_ = 1;
    equation->b_ = -8;
    equation->c_ = 12;

    auto solver = Solver{};
    auto roots = solver.solve(equation);

    REQUIRE(roots);
    REQUIRE(roots->x1_ == 2);
    REQUIRE(roots->x2_ == 6);
}

TEST_CASE("simple equation, D == 0")
{
    auto equation = std::make_shared<QuadraticEquation>();
    equation->a_ = 1;
    equation->b_ = 12;
    equation->c_ = 36;

    auto solver = Solver{};
    auto roots = solver.solve(equation);

    REQUIRE(roots);
    REQUIRE(roots->x1_ == -6);
    REQUIRE(roots->x2_ == -6);
}

TEST_CASE("simple equation, D < 0")
{
    auto equation = std::make_shared<QuadraticEquation>();
    equation->a_ = 1;
    equation->b_ = 2;
    equation->c_ = 17;

    auto solver = Solver{};
    auto roots = solver.solve(equation);

    REQUIRE(!roots);
}


TEST_CASE("Blocked Queue with simple task")
{
    struct Task {
        int x;
    };
    const size_t capacity = 10;
    auto blockedQueue = std::make_unique<BlockingQueue<std::unique_ptr<Task>>>(capacity);

    for (size_t i = 0; i < capacity; ++i)
    {
        auto task = std::make_unique<Task>();
        task->x = i;
        blockedQueue->schedule(task);
    }

    for (size_t i = 0; i < capacity; ++i)
    {
        std::unique_ptr<Task> task;
        blockedQueue->consume(task);
        REQUIRE(task);
        REQUIRE(task->x == i);
    }
}

TEST_CASE("Blocked Queue with QuadraticEquation")
{
    const size_t capacity = 10;
    auto blockedQueue = std::make_unique<BlockingQueue<std::unique_ptr<QuadraticEquation>>>(capacity);

    for (size_t i = 1; i <= capacity; ++i)
    {
        auto task = std::make_unique<QuadraticEquation>();
        task->a_ = i;
        task->b_ = 2 * i;
        task->c_ = 4 * i;
        blockedQueue->schedule(task);
    }

    for (size_t i = 1; i <= capacity; ++i)
    {
        std::unique_ptr<QuadraticEquation> task;
        blockedQueue->consume(task);
        REQUIRE(task);
        REQUIRE(task->a_ == i);
        REQUIRE(task->b_ == 2 * i);
        REQUIRE(task->c_ == 4 * i);
    }
}

TEST_CASE("Blocked Queue with QuadraticEquation 2")
{
    const size_t capacity = 10;
    auto blockedQueue = std::make_unique<BlockingQueue<QuadraticEquation>>(capacity);

    for (size_t i = 1; i <= capacity; ++i)
    {
        auto task = QuadraticEquation{};
        task.a_ = i;
        task.b_ = 2 * i;
        task.c_ = 4 * i;
        blockedQueue->schedule(task);
    }

    for (size_t i = 1; i <= capacity; ++i)
    {
        auto task = QuadraticEquation{};
        blockedQueue->consume(task);
        REQUIRE(task.a_ == i);
        REQUIRE(task.b_ == 2 * i);
        REQUIRE(task.c_ == 4 * i);
    }
}

TEST_CASE("SimpleTaskWorkers")
{
    constexpr size_t capacity = 10;
    auto tasksQueue = std::make_shared<BlockingQueue<int>>(capacity);


    std::cout << "starting producer thread..." << std::endl;
    std::thread producerThread(&SimpleTaskGenerator::run, SimpleTaskGenerator{tasksQueue});

    std::cout << "starting consumer thread..." << std::endl;
    std::thread consumerThread(&SimpleTaskConsumer::run, SimpleTaskConsumer{tasksQueue});

    std::cout << "starting consumer thread 2..." << std::endl;
    std::thread consumerThread2(&SimpleTaskConsumer::run, SimpleTaskConsumer{tasksQueue});

    std::cout << "starting consumer thread 3..." << std::endl;
    std::thread consumerThread3(&SimpleTaskConsumer::run, SimpleTaskConsumer{tasksQueue});

    std::cout << "starting consumer thread 3..." << std::endl;
    std::thread consumerThread4(&SimpleTaskConsumer::run, SimpleTaskConsumer{tasksQueue});

    std::chrono::time_point<std::chrono::system_clock> start, end;


    std::cout << "waiting for threads to finish..." << std::endl;

    start = std::chrono::system_clock::now();

    producerThread.join();
    consumerThread.join();
    consumerThread2.join();
    consumerThread3.join();
    consumerThread4.join();

    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    auto x = std::chrono::duration_cast<std::chrono::seconds>(elapsed_seconds);

    //to_string
    std::cout <<"Spent time (s): " << std::to_string(x.count()) << std::endl;
}
