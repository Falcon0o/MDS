#include "geo/GP_Circle.h"
#include <iostream>

namespace msd {

Scalar GP_Circle::ClosestPoints(const GP_Circle& other, Vector3& clstPntI, Vector3& clstPntJ) const
{
    CoordSys frameJ2I = m_frame.TransG2L(other.m_frame);
    
    Vector3 axisI(0, 0, 1);
    Vector3 axisJ = frameJ2I.TransL2G_Dir(axisI);

    Vector3 tangent = axisI.cross(axisJ);
    
    Scalar len2 = tangent.squaredNorm();
    if (len2 < std::numeric_limits<Scalar>::epsilon())
    {

    }
    tangent /= msd::Sqrt(len2);

    Vector3 pntI[] = {
        Vector3(-tangent(1, 0), tangent(0, 0), 0) * m_radius,
        Vector3(tangent(1, 0), -tangent(0, 0), 0) * m_radius
    };

    tangent = frameJ2I.TransG2L_Dir(tangent);

    Vector3 pntJ[] = {
        Vector3(-tangent(1, 0), tangent(0, 0), 0) * other.m_radius,
        Vector3(tangent(1, 0), -tangent(0, 0), 0) * other.m_radius
    };

    pntJ[0] = frameJ2I.TransL2G_Pnt(pntJ[0]);
    pntJ[1] = frameJ2I.TransL2G_Pnt(pntJ[1]);

    Scalar dist2 = (pntJ[0] - pntI[0]).squaredNorm();

    uint8_t ans = 0;
    for (uint8_t ii = 1; ii < 4; ++ii)
    {
        Scalar tmp = (pntJ[ii >> 1] - pntI[ii & 1]).squaredNorm();
        if (tmp < dist2)
        {
            ans = ii;
            dist2 = tmp;
        }
    }

    clstPntI = pntI[ans & 1];
    clstPntJ = pntI[ans >> 1];
    return msd::Sqrt(dist2);
}

void GP_Circle::Test() {
    CoordSys coord1(Vector3(0, 0, 0), Quaternion(1, 0, 0, 0));
    GP_Circle circle1(10., coord1);  
    Quaternion q(Eigen::AngleAxis<Scalar>(-msd::Degree2Radian(30), Vector3(0, 1, 0)));
    CoordSys coord2(
        Vector3(4. * msd::Sqrt(3.) - 10., 0, 6.), q);

    GP_Circle circle2(8., coord2);  

    Vector3 vI, vJ;
    std::cout << circle1.ClosestPoints(circle2, vI, vJ) << " ";
    // Print<Vector3>(vI, std::cout);
    // Print<Vector3>(vJ, std::cout);
    std::cout << std::endl;
}
}; // end namespace msd