#include "geo/Geo3d.h"

namespace msd {
class Torus : public Geo3d {
private:
    Scalar m_largeRadius;
    Scalar m_smallRadius;

public:
    Torus(const Scalar& largeRadius, Scalar& smallRadius) 
    : m_largeRadius(largeRadius), m_smallRadius(smallRadius) {}

    Scalar Distance(const Torus& other);
};
} // end namespace msd