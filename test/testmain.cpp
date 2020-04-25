
#define CATCH_CONFIG_MAIN

#include <iostream>
#include <catch2/catch.hpp>
#include <solver.hpp>

#include <monitor.hpp>

TEST_CASE("simple equation, D > 0")
{
    auto equation = QuadricEquation{};
    equation.a_ = 1;
    equation.b_ = -8;
    equation.c_ = 12;

    auto roots = solver(equation);

    REQUIRE(roots.x1_ == 2);
    REQUIRE(roots.x2_ == 6);
}

TEST_CASE("simple equation, D == 0")
{
    auto equation = QuadricEquation{};
    equation.a_ = 1;
    equation.b_ = 12;
    equation.c_ = 36;

    auto roots = solver(equation);

    REQUIRE(roots.x1_ == -6);
    REQUIRE(roots.x2_ == -6);
}

TEST_CASE("simple equation, D < 0")
{
    //auto equation = QuadricEquation{};
    //equation.a_ = 1;
    //equation.b_ = 12;
    //equation.c_ = 36;

    //auto roots = solver(equation);

    //REQUIRE(roots.x1_ == -6);
    //REQUIRE(roots.x2_ == -6);
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

TEST_CASE("Blocked Queue with QuadricEquation")
{
    const size_t capacity = 10;
    auto blockedQueue = std::make_unique<BlockingQueue<std::unique_ptr<QuadricEquation>>>(capacity);

    for (size_t i = 1; i <= capacity; ++i)
    {
        auto task = std::make_unique<QuadricEquation>();
        task->a_ = i;
        task->b_ = 2 * i;
        task->c_ = 4 * i;
        blockedQueue->schedule(task);
    }

    for (size_t i = 1; i <= capacity; ++i)
    {
        std::unique_ptr<QuadricEquation> task;
        blockedQueue->consume(task);
        REQUIRE(task);
        REQUIRE(task->a_ == i);
        REQUIRE(task->b_ == 2 * i);
        REQUIRE(task->c_ == 4 * i);
    }
}

TEST_CASE("Blocked Queue with QuadricEquation 2")
{
    const size_t capacity = 10;
    auto blockedQueue = std::make_unique<BlockingQueue<QuadricEquation>>(capacity);

    for (size_t i = 1; i <= capacity; ++i)
    {
        auto task = QuadricEquation{};
        task.a_ = i;
        task.b_ = 2 * i;
        task.c_ = 4 * i;
        blockedQueue->schedule(task);
    }

    for (size_t i = 1; i <= capacity; ++i)
    {
        auto task = QuadricEquation{};
        blockedQueue->consume(task);
        REQUIRE(task.a_ == i);
        REQUIRE(task.b_ == 2 * i);
        REQUIRE(task.c_ == 4 * i);
    }
}

//using namespace std;
//int main()
//{
//	cout << "Hello CMake Test." << endl;
//	return 0;
//}
