#include "spline/SplLagrange3.h"
#include "spline/Spline.h"

#include <assert.h>

namespace msd {

template <>
Spline Spline::Create<Spline::Lagrange3>(const std::vector<Scalar>& independentData, const std::vector<Scalar>& dependentData)
{
    return Spline(std::make_shared<SplLagrange3>(independentData, dependentData));
}

template <>
Spline Spline::Create<Spline::Lagrange3>(std::vector<Scalar>&& independentData, std::vector<Scalar>&& dependentData) {
    return Spline(std::make_shared<SplLagrange3>(independentData, dependentData));
}


Scalar SplLagrange3::operator()(Scalar x, size_t order) const 
{
    size_t idx = FindInterval(x);

    const std::vector<Scalar>& m_x = m_independentData;
    const std::vector<Scalar>& m_y = m_dependentData; 
    if (idx == 0) {
        idx = 1;
    } else if (idx == m_x.size() - 2) {
        idx = m_x.size() - 3;
    }

    Scalar ans = 0;
    for (size_t ii = idx - 1; ii < idx + 3; ++ii) {
                
        Scalar deltaX[3];
        size_t kk = 0;

        Scalar tmp = m_y[ii];

        for (size_t jj = idx - 1; jj < idx + 3; ++jj) {
                    
            if (jj == ii) {
                continue;
            }
            deltaX[kk++] = x - m_x[jj];

            tmp /= (m_x[ii] - m_x[jj]);
        }

        switch (order) {
        case 0:
            tmp *= deltaX[0] * deltaX[1] * deltaX[2];
            break;
        case 1:
            tmp *= deltaX[0] * deltaX[1] + deltaX[0] * deltaX[2] + deltaX[2] * deltaX[1];
            break;
        case 2:
            tmp *= deltaX[0] + deltaX[1] + deltaX[2];
            tmp *= 2;
            break;
        case 3:
            tmp *= 6;
            break;
        default:
            assert(0);
        }

        ans += tmp;
    }
    
    return ans; 
}
}