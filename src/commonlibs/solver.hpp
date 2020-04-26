#pragma once
#include <cmath>
#include <iostream>
#include <memory>

#include "quadricequation.hpp"

class Solver
{
public:
	std::unique_ptr<Roots> solve(std::shared_ptr<QuadricEquation> parameters)
	{
		// TODO: check overflow when multiply
		auto discriminant = parameters->b_ * parameters->b_ - 4 * parameters->a_ * parameters->c_;

		auto roots = std::make_unique<Roots>();

		auto doublea = 2 * parameters->a_;

		if (discriminant == 0)
		{
			roots->x1_ = roots->x2_ = -parameters->b_ / doublea;
		}
		else if (discriminant > 0)
		{
			roots->x1_ = (-parameters->b_ - std::sqrt(discriminant)) / doublea;
			roots->x2_ = (-parameters->b_ + std::sqrt(discriminant)) / doublea;
		}
		else
		{
			// there are no real roots, only complex
			return nullptr;
		}

		return roots;

	}
};


//
//Roots solver(QuadricEquation& equation)
//{
//	int discriminant = equation.b_ * equation.b_ - 4 * equation.a_ * equation.c_;
//
//	auto roots = Roots{};
//
//	int doublea = 2 * equation.a_;
//
//	if (discriminant == 0)
//	{
//		roots.x1_ = roots.x2_ = -equation.b_ / doublea;
//	}
//	else if (discriminant > 0)
//	{
//		roots.x1_ = (-equation.b_ - std::sqrt(discriminant)) / doublea;
//		roots.x2_ = (-equation.b_ + std::sqrt(discriminant)) / doublea;
//	}
//	else
//	{
//		// there are no real roots, only complex
//	}
//
//	return roots;
//}