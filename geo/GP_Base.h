#pragma once

#include "math/CoordSys.h"

namespace msd {
class GP_Base
{ 
protected:
    CoordSys m_frame;
protected:
    GP_Base(const CoordSys& c) : m_frame(c) {}
    virtual ~GP_Base() {}
    virtual uint32_t Dim() const = 0;
};

} // end namespace msd