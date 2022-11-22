#pragma once

#include "math/Scalar.h"

#include <memory>
#include <vector>

namespace msd {

class SplBase;

class Spline 
{
private:
    std::shared_ptr<SplBase> m_impl;

    Spline(std::shared_ptr<SplBase> ptr) : m_impl(ptr) {}   
public:

    enum SplType {
        Akima,      //! Akima 三次插值，二阶导不连续
        Lagrange3   //! 三次拉格朗日插值，二阶导连续
    };
    
    template <SplType>
    static Spline Create(std::vector<Scalar>&& independentData, std::vector<Scalar>&& dependentData);

    template <SplType>
    static Spline Create(const std::vector<Scalar>& independentData, const std::vector<Scalar>& dependentData);
   
    Scalar operator()(Scalar x, size_t order) const;
};
} // end namespace msd