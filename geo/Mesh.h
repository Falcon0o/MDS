#pragma once

#include "math/Vector3.h"
#include <array>
#include <vector>
namespace msd {

class Array3;

// true 在内部，false 不在内部
bool Orient(const Array3& p, const Array3& v0, const Array3& v1, const Array3& v2, const Array3& v3);

// P = face0 + u * (face1 - face0) + v * (face2 - face0)
void ClosestPoint_PlanePoint(const Array3& vertex, 
    const Array3& face0, const Array3& face1, const Array3& face2,
    Scalar& u, Scalar& v);

void ClosestPoint_LineLine(
    const Array3& ori0, const Array3& dir0, 
    const Array3& ori1, const Array3& dir1,
    Scalar& u, Scalar& v);

void CalMassProperties(
    const std::vector<Vector3>& nodes,
    const std::vector<std::array<uint64_t, 3>>& faces,
    Scalar volume,          // 体积
    Vector3 &centroid,      // 质心
    Matrix<3, 3> &inertiaC, // 相对于质心的转动惯量
    Matrix<3, 3> &inertiaL  // 相对于随体系的转动惯量
);
} // end namespace msd 
#if 0
void Scalarest_Orient() {
    Array3<> v0(0, -1, 1);
    Array3<> v1(0, 0, 0);
    Array3<> v2(0, 1, 0);
    Array3<> v3(-1, 0, 0);

    Array3<> P(0, -1, 0.5);

    bool ans;

    ans = Orient(P, v0, v1, v2, v3);
    std::cout << (ans? "true": "false") << std::endl; // true;

    P.SetXYZ(0, -1, 2);
    ans = Orient(P, v0, v1, v2, v3);
    std::cout << (ans? "true": "false") << std::endl; // false;

    v0.SetXYZ(0, -1, -1);

    P.SetXYZ(0, -1, -0.5);
    ans = Orient(P, v0, v1, v2, v3);    
    std::cout << (ans? "true": "false") << std::endl; // false;

    P.SetXYZ(0, -1, -2);
    ans = Orient(P, v0, v1, v2, v3);    
    std::cout << (ans? "true": "false") << std::endl; // true;
}

#endif

