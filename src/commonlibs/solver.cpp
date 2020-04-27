#include "solver.hpp"

#include <cmath>
#include <iostream>

std::unique_ptr<Roots> Solver::solve(std::shared_ptr<QuadraticEquation> parameters) const
{
	// Specific case:
	// parameter A should not be equal 0, because in that case it is not a quadratic equation.
	// So, I decided to return no roots for that case

	if (parameters->a_ == 0)
	{
		return nullptr;
	}

	// convert to double to avoid overflow
	// because std::numeric_limits<std::int64_t>::max() < std::numeric_limits<double>::max();

	const auto b_square = static_cast<double>(parameters->b_) * parameters->b_;
	const auto multi_a_c = static_cast<double>(parameters->a_) * parameters->c_;
	const auto discriminant = b_square - 4 * multi_a_c;
	const auto doublea = 2 * static_cast<double>(parameters->a_);

	auto roots = std::make_unique<Roots>();

	if (discriminant == 0.0)
	{
		roots->x1_ = roots->x2_ = -parameters->b_ / doublea;
	}
	else if (discriminant > 0.0)
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
