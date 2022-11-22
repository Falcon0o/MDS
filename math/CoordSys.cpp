#include "math/CoordSys.h"

namespace msd
{

Vector3 CoordSys::TransL2G_Dir(const Vector3& v) const
{
    return Orientation()._transformVector(v);
}
Vector3 CoordSys::TransG2L_Dir(const Vector3& v) const
{
    return Orientation().conjugate()._transformVector(v);
}

Vector3 CoordSys::TransL2G_Pnt(const Vector3& p) const {
    return Orientation() * p + Location();
}

Vector3 CoordSys::TransG2L_Pnt(const Vector3& p) const {
    return TransG2L_Dir(p - Location());
}

CoordSys CoordSys::TransL2G(const CoordSys& c) const {
    return CoordSys(TransL2G_Dir(c.Location()) + Location(), Orientation() * c.Orientation());
}

CoordSys CoordSys::TransG2L(const CoordSys& c) const {
    return CoordSys(TransG2L_Pnt(c.Location()), Orientation().conjugate() * c.Orientation()); 
}

template <>
CoordSys Random() {
    return CoordSys(Random<Vector3>(), Random<Quaternion>());
}

} // namespace msd
