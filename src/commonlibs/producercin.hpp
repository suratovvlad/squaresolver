#pragma once
#include "quadraticequationworker.hpp"

/**
 * \brief The class could be used for parsing stdin, however it is not used
 * anymore in this project and it is not tested.
 * It is left here as legacy
 */
class ProducerCin final : QuadraticEquationWorker {

public:
    /**
     * \brief Generic constructor for forwarding all arguments to base class.
     * Example taken from here https://stackoverflow.com/a/14122944/8369974
     */
    template<typename... Args>
    explicit ProducerCin(Args&&... args)
        : QuadraticEquationWorker{ std::forward<Args>(args)... } {}

    void run() override;
};