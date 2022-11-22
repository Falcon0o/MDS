#include "geo/GP_3d.h"

namespace msd {
class Gp_Torus : public GP_3d {
private:
    Scalar m_largeRadius;
    Scalar m_smallRadius;

public:
    Gp_Torus(const Scalar& largeRadius, const Scalar& smallRadius, const CoordSys& coord) 
    : GP_3d(coord), m_largeRadius(largeRadius), m_smallRadius(smallRadius) {}

    Scalar PenetrateDepth(const Gp_Torus& other, Vector3& pnt_I, Vector3& pnt_J, Vector3& norm) const;
};
} // end namespace msd