
#ifndef QUADRIC_EQUATION_HPP
#define QUADRIC_EQUATION_HPP

#include <iostream>

class QuadricEquation {
public:
    int a_ = 0;
    int b_ = 0;
    int c_ = 0;

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


#endif // QUADRIC_EQUATION_HPP
