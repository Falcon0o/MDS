#pragma once

#include "geo/GP_2d.h"

namespace msd {
class GP_Circle : public GP_2d { 
public:
    Scalar m_radius;
public:
    GP_Circle(const Scalar radius, const CoordSys& c) : GP_2d(c), m_radius(radius) {}
    virtual ~GP_Circle() {}

    Scalar ClosestPoints(const GP_Circle& other, Vector3& clstPntI, Vector3& clstPntJ) const;

    static void Test();
};



} // end namespace msd