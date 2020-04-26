
#pragma once

#include <iostream>

class QuadricEquation {
public:
    std::int64_t a_ = 0;
    std::int64_t b_ = 0;
    std::int64_t c_ = 0;

    QuadricEquation() //= default;
    {
        std::cout << "QuadricEquation()" << std::endl;
    }

    QuadricEquation(const QuadricEquation &params) //= default;
            : a_{params.a_}, b_{params.b_}, c_{params.c_} {
        std::cout << "QuadricEquation(const QuadricEquation&)" << std::endl;
    }

    QuadricEquation(QuadricEquation &&params) //= default;
            : a_{std::move(params.a_)}, b_{std::move(params.b_)}, c_{std::move(params.c_)} {
        std::cout << "QuadricEquation(QuadricEquation&&)" << std::endl;
    }

    virtual ~QuadricEquation() // = default;
    {
        std::cout << "~QuadricEquation()" << std::endl;
    }

    QuadricEquation &operator=(const QuadricEquation &params) //= default;
    {
        a_ = params.a_;
        b_ = params.b_;
        c_ = params.c_;
        std::cout << "operator=(const QuadricEquation&)" << std::endl;
        return *this;
    }

    QuadricEquation &operator=(QuadricEquation &&params) //= default;
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
