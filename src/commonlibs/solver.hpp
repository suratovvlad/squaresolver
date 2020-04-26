#pragma once
#include <cmath>
#include <iostream>

#include "quadricequation.hpp"

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