#pragma once

#include <memory>
#include "quadricequation.hpp"

class Solver
{
public:
	std::unique_ptr<Roots> solve(std::shared_ptr<QuadricEquation> parameters);
};
