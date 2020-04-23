
#define CATCH_CONFIG_MAIN

#include <iostream>
#include <catch2/catch.hpp>
#include <solver.hpp>

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

//using namespace std;
//int main()
//{
//	cout << "Hello CMake Test." << endl;
//	return 0;
//}
