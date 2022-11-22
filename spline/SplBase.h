#pragma once

#include "math/Scalar.h"

#include <vector>

namespace msd {

class SplBase
{
protected:
    std::vector<Scalar> m_independentData;
    std::vector<Scalar> m_dependentData;

    bool LoadFile(const char* fileName);

    /// @brief 
    /// @param x 若 x < x[0] 或 x > x[max] 会修正x的值
    /// @return 
    size_t FindInterval(Scalar& x) const;

    SplBase(std::vector<Scalar>&& independentData, std::vector<Scalar>&& dependentData) 
    :   m_independentData(independentData), m_dependentData(dependentData) 
    { }

    SplBase(const std::vector<Scalar>& independentData, const std::vector<Scalar>& dependentData) 
    :   m_independentData(independentData), m_dependentData(dependentData) 
    { }

    SplBase(const SplBase& other) : SplBase(other.m_independentData, other.m_dependentData)
    { }

    SplBase(SplBase&& other) : SplBase(other.m_independentData, other.m_dependentData)
    { }

public:
    virtual Scalar operator()(Scalar x, size_t order) const = 0;
};

}