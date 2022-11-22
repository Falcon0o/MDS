#include "spline/SplBase.h"

#include <fstream>

namespace msd {

size_t SplBase::FindInterval(Scalar& x) const 
{
    const std::vector<Scalar>& m_x = m_independentData;
    const std::vector<Scalar>& m_a = m_dependentData; 

    size_t idx;

    if (x >= m_x.back()) {
        idx = m_a.size() - 2;
        x = m_x.back();
    }
    else if (x <= m_x.front()) {
        idx = 0;
        x = m_x.front();
    }
    else {
        size_t left = 0, right = m_x.size() - 1;
        while (right > left + 1) {
            size_t mid = (right + left) >> 1; 
            if (m_x[mid] > x) {
                right = mid;
            } else if (m_x[mid] < x) {
                left = mid;
            }
            else return m_a[mid];
        }
        idx = left;
    }

    return idx;
}

}