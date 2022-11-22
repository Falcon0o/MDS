#pragma once 

#include "geo/GP_Base.h"
namespace msd {
class GP_2d : public GP_Base { 
public:
    GP_2d(const CoordSys& c) : GP_Base(c) {}
    virtual ~GP_2d() {}

    virtual uint32_t Dim() const final override { return 2; } 
};
} // end namespace msd