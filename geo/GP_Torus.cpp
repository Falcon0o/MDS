#include "geo/GP_Torus.h"
#include "geo/GP_Circle.h"

namespace msd {
Scalar Gp_Torus::PenetrateDepth(const Gp_Torus& other, Vector3& pnt_I, Vector3& pnt_J, Vector3& norm) const
{
    GP_Circle circle_I(m_largeRadius, m_frame);
    GP_Circle circle_J(other.m_largeRadius, other.m_frame); 

    circle_I.ClosestPoints(circle_J, pnt_I, pnt_J);
    norm = pnt_J - pnt_I;
    
    Scalar depth = norm.norm();
    norm /= depth;

    depth -= m_smallRadius + other.m_smallRadius;

    pnt_I += norm * m_smallRadius;
    pnt_J -= norm * other.m_smallRadius;

    return depth;
}
} // end namespace msd