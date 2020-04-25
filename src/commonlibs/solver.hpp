#pragma once
#include <cmath>
#include <iostream>

struct QuadricEquation
{
	int a_ = 0;
	int b_ = 0;
	int c_ = 0;

    QuadricEquation() //= default;
    {
        std::cout << "QuadricEquation()" << std::endl;
    }

    QuadricEquation(const QuadricEquation& params) //= default;
        : a_{params.a_}
        , b_{params.b_}
        , c_{params.c_}
    {
        std::cout << "QuadricEquation(const QuadricEquation&)" << std::endl;
    }

    QuadricEquation(QuadricEquation&& params) //= default;
        : a_{std::move(params.a_)}
        , b_{std::move(params.b_)}
        , c_{std::move(params.c_)}
    {
        std::cout << "QuadricEquation(QuadricEquation&&)" << std::endl;
    }

    ~QuadricEquation() // = default;
    {
        std::cout << "~QuadricEquation()" << std::endl;
    }

    QuadricEquation& operator=(const QuadricEquation& params) //= default;
    {
        a_ = params.a_;
        b_ = params.b_;
        c_ = params.c_;
        std::cout << "operator=(const QuadricEquation&)" << std::endl;
        return *this;
    }
    QuadricEquation& operator=(QuadricEquation&& params) //= default;
    {
        a_ = std::move(params.a_);
        b_ = std::move(params.b_);
        c_ = std::move(params.c_);
        std::cout << "operator=(QuadricEquation&&)" << std::endl;
        return *this;
    }
};

struct Roots
{
	double x1_ = 0;
	double x2_ = 0;
};

Roots solver(QuadricEquation& equation)
{
	int discriminant = equation.b_ * equation.b_ - 4 * equation.a_ * equation.c_;

	auto roots = Roots{};

	int doublea = 2 * equation.a_;

	if (discriminant == 0)
	{
		roots.x1_ = roots.x2_ = -equation.b_ / doublea;
	}
	else if (discriminant > 0)
	{
		roots.x1_ = (-equation.b_ - std::sqrt(discriminant)) / doublea;
		roots.x2_ = (-equation.b_ + std::sqrt(discriminant)) / doublea;
	}
	else
	{
		// there are no real roots, only complex
	}

	return roots;
}