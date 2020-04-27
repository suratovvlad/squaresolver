#pragma once

#include <memory>
#include "quadraticequation.hpp"

/**
 * \brief Solver for the quadratic equation.
 * Implements standard solution with calculation of discriminant and finding roots from it.
 * More about discriminant here https://en.wikipedia.org/wiki/Quadratic_equation#Discriminant
 * It does not searches for complex roots, it returns nullptr if D < 0.
 *
 * If needed other solvers could be implemented and used.
 */
class Solver
{
public:
    // Warning if result discarded https://en.cppreference.com/w/cpp/language/attributes/nodiscard
    [[nodiscard]] std::unique_ptr<Roots> solve(std::shared_ptr<QuadraticEquation> parameters) const;
};
