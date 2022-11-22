#pragma once

#include "spline/SplBase.h"

namespace msd {

class SplAkima : public SplBase
{
protected:

    std::vector<Scalar> m_b;
    std::vector<Scalar> m_c;
    std::vector<Scalar> m_d;

    void Initialize();

public:
    SplAkima(const std::vector<Scalar>& independentData, const std::vector<Scalar>& dependentData) 
    :   SplBase(independentData, dependentData) 
    { Initialize(); }

    SplAkima(std::vector<Scalar>&& independentData, std::vector<Scalar>&& dependentData) 
    :   SplBase(independentData, dependentData) 
    { Initialize(); }
    virtual Scalar operator()(Scalar x, size_t order) const override;
};
} // namespace msd

