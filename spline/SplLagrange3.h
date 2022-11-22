#pragma once

#include "spline/SplBase.h"


namespace msd {

class SplLagrange3 : public SplBase
{
protected:

   

public:

    SplLagrange3(const std::vector<Scalar>& independentData, const std::vector<Scalar>& dependentData) 
    :   SplBase(independentData, dependentData) 
    { }

    SplLagrange3(std::vector<Scalar>&& independentData, std::vector<Scalar>&& dependentData) 
    :   SplBase(independentData, dependentData) 
    { }
    virtual Scalar operator()(Scalar x, size_t order) const override;
};
} // namespace msd