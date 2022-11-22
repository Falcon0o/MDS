#pragma once

#include "math/Scalar.h"
#include "math/Quaternion.h"
#include "math/Vector3.h"

namespace msd {

// TODO: 创建一个使用方向余弦阵描述姿态的坐标系

class CoordSys {
private:
    Quaternion m_orientation;
    Vector3 m_location;
public:

    CoordSys(const Vector3& pos, const Quaternion& rot) {
        Location() = pos;
        Orientation() = rot;
    }

    CoordSys(const CoordSys& other) : CoordSys(other.m_location, other.m_orientation) {}
    const Vector3& Location() const { return m_location; }
    Vector3& Location() { return m_location; }

    const Quaternion& Orientation() const { return m_orientation;}
    Quaternion& Orientation() { return m_orientation;}
    
    /// @brief 多次转换需要先将四元数转为矩阵，单次转换用四元数即可
    Vector3 TransL2G_Dir(const Vector3&) const;
    Vector3 TransG2L_Dir(const Vector3&) const;

    Vector3 TransL2G_Pnt(const Vector3&) const;
    Vector3 TransG2L_Pnt(const Vector3&) const;
    
    CoordSys TransL2G(const CoordSys&) const;
    CoordSys TransG2L(const CoordSys&) const;
};

template <>
CoordSys Random();

template <class OutStream>
void Print(const CoordSys& c, OutStream& stream) {
	Print(c.Location(), stream);
    Print(c.Orientation(), stream);
}

} // end namespace msd