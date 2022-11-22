#pragma once

#include "math/Quaternion.h"
#include "math/Vector3.h"

namespace msd {
class Coord7
{ 
private:
    Quaternion m_rot;
    Vector3 m_pos;

public:
    Coord7(const Coord7& other) :  Coord7(other.m_pos, other.m_rot) {}
    Coord7(const Vector3& pos, const Quaternion& rot) : m_rot(rot), m_pos(pos) {}

    Coord7 TransL2G(const Coord7&) const;
    Coord7 TransG2L(const Coord7&) const;

    Vector3 TransL2G_Pnt(const Vector3&) const;
    Vector3 TransG2L_Pnt(const Vector3&) const;
    
    Vector3 TransL2G_Dir(const Vector3&) const;
    Vector3 TransG2L_Dir(const Vector3&) const;
};
} // end namespace msd