#include "geo/Mesh.h"
#include "math/Vector3.h"

#include <array>
#include <vector>

namespace msd {

bool Orient(const Vector3& p, const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3) 
{
    Vector3 e12 = v2 - v1;
    Vector3 e13 = v3 - v1;
    Vector3 e10 = v0 - v1;

    Vector3 axisY = e12.Cross(e13);
    Vector3 axisX = e13.Cross(axisY);

    Scalar projX = axisX.Dot(e10);
    Scalar projY = axisY.Dot(e10);
    Scalar angleF = Atan2(projY, projX);
     
    Vector3 tmp = p - v1;
    projX = axisX.Dot(tmp);
    projY = axisY.Dot(tmp);
    Scalar angleP = Atan2(projY, projX);
    // std::cout << angleF << " " << angleP << std::endl;
    return angleP > angleF;
}

void ClosestPoint_PlanePoint(const Vector3& vertex, 
    const Vector3& face0, const Vector3& face1, const Vector3& face2,
    Scalar& u, Scalar& v)
{
    const Vector3 edge01 = face1 - face0;
    const Vector3 edge02 = face2 - face0;

    Scalar A00 = edge01.Dot(edge01);
    Scalar A01 = edge01.Dot(edge02);
    Scalar A10 = A01;
    Scalar A11 = edge02.Dot(edge02);

    Scalar b0 = (vertex - face0).Dot(edge01);  
    Scalar b1 = (vertex - face0).Dot(edge02);  

    v = (A10 * b0 - A00 * b1) / (A10 * A01 - A11 * A00);
    u = (b0 - A01 * v) / A00;
}

void ClosestPoint_LineLine(
    const Vector3& ori0, const Vector3& dir0, 
    const Vector3& ori1, const Vector3& dir1,
    Scalar& u, Scalar& v) 
{
    Scalar A00 = dir0.Dot(dir0);
    Scalar A01 = -dir0.Dot(dir1);
    Scalar A10 = -A01;
    Scalar A11 = -dir1.Dot(dir1);

    Scalar b0 = ori1.Dot(dir0) - ori0.Dot(dir0);
    Scalar b1 = ori1.Dot(dir1) - ori0.Dot(dir1);

    v = (A10 * b0 - A00 * b1) / (A10 * A01 - A11 * A00);
    u = (b0 - A01 * v) / A00;
}


void CalMassProperties(
    const std::vector<Vector3>& nodes,
    const std::vector<std::array<uint64_t, 3>>& faces, 
    Scalar volume,          // 体积
    Vector3& centroid,      // 质心
    Matrix<3, 3>& inertiaC, // 相对于质心的转动惯量
    Matrix<3, 3>& inertiaL  // 相对于随体系的转动惯量
) {
    constexpr Scalar fOneDiv6     = 1.0 / 6.0;
    constexpr Scalar fOneDiv24    = 1.0 / 24.0;
    constexpr Scalar fOneDiv60    = 1.0 / 60.0;
    constexpr Scalar fOneDiv120   = 1.0 / 120.0;

    // order:  1, x, y, z, x^2, y^2, z^2, xy, yz, zx
    Scalar afIntegral[10] = {0.0};

    for (size_t ii = 0; ii < faces.size(); ii++)
    {
        // get vertices of triangle i
        const Vector3& node0 = nodes[faces[ii][0]];
        const Vector3& node1 = nodes[faces[ii][1]];
        const Vector3& node2 = nodes[faces[ii][2]];

        // get cross product of edges
        Vector3 triNorm = (node1 - node0).Cross(node2 - node0);

        Scalar fTmp0 = node0.X() + node1.X();
        Scalar fF1x = fTmp0 + node2.X();
        Scalar fTmp1 = node0.X() * node0.X();
        Scalar fTmp2 = fTmp1 + node1.X() * fTmp0;
        Scalar fF2x = fTmp2 + node2.X() * fF1x;
        Scalar fF3x = node0.X() * fTmp1 + node1.X() * fTmp2 + node2.X() * fF2x;
        Scalar fG0x = fF2x + node0.X() * (fF1x + node0.X());
        Scalar fG1x = fF2x + node1.X() * (fF1x + node1.X());
        Scalar fG2x = fF2x + node2.X() * (fF1x + node2.X());

        fTmp0 = node0.Y() + node1.Y();
        Scalar fF1y = fTmp0 + node2.Y();
        fTmp1 = node0.Y() * node0.Y();
        fTmp2 = fTmp1 + node1.Y() * fTmp0;
        Scalar fF2y = fTmp2 + node2.Y() * fF1y;
        Scalar fF3y = node0.Y() * fTmp1 + node1.Y() * fTmp2 + node2.Y() * fF2y;
        Scalar fG0y = fF2y + node0.Y() * (fF1y + node0.Y());
        Scalar fG1y = fF2y + node1.Y() * (fF1y + node1.Y());
        Scalar fG2y = fF2y + node2.Y() * (fF1y + node2.Y());

        fTmp0 = node0.Z() + node1.Z();
        Scalar fF1z = fTmp0 + node2.Z();
        fTmp1 = node0.Z() * node0.Z();
        fTmp2 = fTmp1 + node1.Z() * fTmp0;
        Scalar fF2z = fTmp2 + node2.Z() * fF1z;
        Scalar fF3z = node0.Z() * fTmp1 + node1.Z() * fTmp2 + node2.Z() * fF2z;
        Scalar fG0z = fF2z + node0.Z() * (fF1z + node0.Z());
        Scalar fG1z = fF2z + node1.Z() * (fF1z + node1.Z());
        Scalar fG2z = fF2z + node2.Z() * (fF1z + node2.Z());

        // update integrals
        afIntegral[0] += triNorm.X() * fF1x;
        afIntegral[1] += triNorm.X() * fF2x;
        afIntegral[2] += triNorm.Y() * fF2y;
        afIntegral[3] += triNorm.Z() * fF2z;
        afIntegral[4] += triNorm.X() * fF3x;
        afIntegral[5] += triNorm.Y() * fF3y;
        afIntegral[6] += triNorm.Z() * fF3z;
        afIntegral[7] += triNorm.X() * (node0.Y() * fG0x + node1.Y() * fG1x + node2.Y() * fG2x);
        afIntegral[8] += triNorm.Y() * (node0.Z() * fG0y + node1.Z() * fG1y + node2.Z() * fG2y);
        afIntegral[9] += triNorm.Z() * (node0.X() * fG0z + node1.X() * fG1z + node2.X() * fG2z);
    }
       
    afIntegral[0] *= fOneDiv6;
    afIntegral[1] *= fOneDiv24;
    afIntegral[2] *= fOneDiv24;
    afIntegral[3] *= fOneDiv24;
    afIntegral[4] *= fOneDiv60;
    afIntegral[5] *= fOneDiv60;
    afIntegral[6] *= fOneDiv60;
    afIntegral[7] *= fOneDiv120;
    afIntegral[8] *= fOneDiv120;
    afIntegral[9] *= fOneDiv120;

    volume = afIntegral[0];
    centroid = Vector3(afIntegral + 1) / volume;
    
    inertiaL(0, 0) = afIntegral[5] + afIntegral[6];
    inertiaL(0, 1) = -afIntegral[7];
    inertiaL(0, 2) = -afIntegral[9];
    inertiaL(1, 0) = inertiaL(0, 1);
    inertiaL(1, 1) = afIntegral[4] + afIntegral[6];
    inertiaL(1, 2) = -afIntegral[8];
    inertiaL(2, 0) = inertiaL(0, 2);
    inertiaL(2, 1) = inertiaL(1, 2);
    inertiaL(2, 2) = afIntegral[4] + afIntegral[5];

    inertiaC(0, 0) = inertiaL(0, 0) - volume * (centroid.Y() * centroid.Y() + centroid.Z() * centroid.Z());
    inertiaC(0, 1) = inertiaL(0, 1) + volume * centroid.X() * centroid.Y();
    inertiaC(0, 2) = inertiaL(0, 2) + volume * centroid.Z() * centroid.X();
    inertiaC(1, 0) = inertiaC(0, 1);
    inertiaC(1, 1) = inertiaL(1, 1) - volume * (centroid.Z() * centroid.Z() + centroid.X() * centroid.X());
    inertiaC(1, 2) = inertiaL(1, 2) + volume * centroid.Y() * centroid.Z();
    inertiaC(2, 0) = inertiaC(0, 2);
    inertiaC(2, 1) = inertiaC(1, 2);
    inertiaC(2, 2) = inertiaL(2, 2) - volume * (centroid.X() * centroid.X() + centroid.Y() * centroid.Y());
    
}

} // end namespace msd 