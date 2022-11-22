#include "math/Coord7.h"

namespace msd
{

// Coord7 Coord7::TransL2G(const Coord7&) const {

// }

Coord7 Coord7::TransG2L(const Coord7& c) const {
    return Coord7(TransG2L_Pnt(c.m_pos), c.m_rot.Conjugate() * m_rot); 
}

Vector3 Coord7::TransL2G_Pnt(const Vector3& p) const {
    return m_rot * p + m_pos;
}

Vector3 Coord7::TransG2L_Pnt(const Vector3& p) const {
    return TransG2L_Dir(p - m_pos);
}

    
Vector3 Coord7::TransL2G_Dir(const Vector3& v) const {
    return m_rot * v;
}

Vector3 Coord7::TransG2L_Dir(const Vector3& v) const {
    return m_rot.Conjugate() * v;
}
} // namespace msd
