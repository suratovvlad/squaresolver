#pragma once

#include <cstdint>

/**
 * \brief Class describes quadratic equation parameters.
 * I didn't implemented the Arbitrary-precision arithmetic, so I use largest available integer type.
 * More about quadratic equations https://en.wikipedia.org/wiki/Quadratic_equation
 */
class QuadraticEquation
{

public:
    std::int64_t a_ = 1; // parameter A, should not be equal to 0
    std::int64_t b_ = 0; // parameter B
    std::int64_t c_ = 0; // parameter C

    // Virtual destructor is needed because there is a derived class used as Poison Pill
    virtual ~QuadraticEquation() = default;

    // Rule of five in action
    QuadraticEquation(const QuadraticEquation& params) = default;
    QuadraticEquation(QuadraticEquation&& params) = default;
    QuadraticEquation& operator=(const QuadraticEquation& params) = default;
    QuadraticEquation& operator=(QuadraticEquation&& params) = default;

    // Declare also default constructor for symmetry
    QuadraticEquation() = default;
};


/**
 * \brief Enumeration describes parameters for convenient usage.
 */
enum class Parameter
{
    A = 1,
    B = 2,
    C = 3
};

/**
 * \brief Roots of the quadratic equation.
 */
struct Roots final
{
    double x1_ = 0;
    double x2_ = 0;
};
