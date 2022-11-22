#pragma once

#include "geo/GP_Base.h"

namespace msd {
class GP_3d : public GP_Base { 
public:
    GP_3d(const CoordSys& c) : GP_Base(c) {}
    virtual ~GP_3d() {}

    virtual uint32_t Dim() const final override { return 3; }

};

} // end namespace msd