#pragma once

#include "math/Coord7.h"

namespace msd {
class GP_Base
{ 
private:
    Coord7 m_coord;
protected:
    GP_Base(const Coord7& c) : m_coord(c) {}
    virtual ~GP_Base() {}
    virtual uint32_t Dim() const = 0;
};

} // end namespace msd