#pragma once

#include "geo/GP_2d.h"

namespace msd {
class GP_Circle : public GP_2d { 
public:
    Scalar m_radius;
public:
    GP_Circle(const Scalar radius, const Coord7& c) : GP_2d(c) {}
    virtual ~GP_Circle() {}

    Scalar Distance(const GP_Circle& other) const;
};



} // end namespace msd