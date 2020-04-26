#pragma once

#include <cstdint>

class QuadricEquation
{

public:
    std::int64_t a_ = 0;
    std::int64_t b_ = 0;
    std::int64_t c_ = 0;

    // Virtual destructor is needed because there is a derived class used as Poison Pill
    virtual ~QuadricEquation() = default;

    // Rule of five in action
    QuadricEquation(const QuadricEquation& params) = default;
    QuadricEquation(QuadricEquation&& params) = default;
    QuadricEquation& operator=(const QuadricEquation& params) = default;
    QuadricEquation& operator=(QuadricEquation&& params) = default;

    // Declare also default constructor for symmetry
    QuadricEquation() = default;
};

enum class Parameter
{
    A = 1,
    B = 2,
    C = 3
};

struct Roots final
{
    double x1_ = 0;
    double x2_ = 0;
};
