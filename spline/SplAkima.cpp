#include "spline/SplAkima.h"
#include "spline/Spline.h"


#include <assert.h>

namespace msd {

template <>
Spline Spline::Create<Spline::Akima>(const std::vector<Scalar>& independentData, const std::vector<Scalar>& dependentData)
{
    return Spline(std::make_shared<SplAkima>(independentData, dependentData));
}

template <>
Spline Spline::Create<Spline::Akima>(std::vector<Scalar>&& independentData, std::vector<Scalar>&& dependentData)
{
    return Spline(std::make_shared<SplAkima>(independentData, dependentData));
}

void SplAkima::Initialize() {

    std::vector<Scalar> m(m_dependentData.size() - 1);
    std::vector<Scalar>& s = m_b; 
    s.resize(m_dependentData.size());

    const std::vector<Scalar>& x = m_independentData;
    const std::vector<Scalar>& y = m_dependentData; 

    for (size_t ii = 0; ii < m.size(); ++ii) {
        m[ii] = (y[ii + 1] - y[ii]) / (x[ii + 1] - x[ii]);
    }

    s[0] = m[0];
    s[1] = (m[0] + m[1]) * 0.5;

    for (size_t ii = m.size()-3; ii >= 2; --ii) {
        Scalar denom_0 = Fabs(m[ii-1] - m[ii-2]);
        Scalar denom_1 = Fabs(m[ii] - m[ii+1]);

        Scalar denom = denom_0 + denom_1;

        s[ii] = m[ii] * denom_0 + m[ii - 1] * denom_1;
        s[ii] /= denom;

        if (std::isnan(s[ii])) {
            s[ii] = (m[ii] + m[ii-1]) * 0.5;
        }
    }

    s[s.size() - 2] = (m[m.size() - 2] + m.back()) * 0.5;
    s.back() = m.back();

    m_c.resize(m_independentData.size() - 1);
    m_d.resize(m_independentData.size() - 1);

    for (size_t ii = 0; ii < m_c.size(); ++ii) {
        m_c[ii] = (3. * m[ii] - 2. * s[ii] - s[ii + 1]);
        m_c[ii] /= x[ii + 1] - x[ii];
    }

    for (size_t ii = 0; ii < m_d.size(); ++ii) {
        m_d[ii] = s[ii] + s[ii + 1] - 2. * m[ii];
        Scalar tmp = (x[ii + 1] - x[ii]);
        m_d[ii] /= tmp * tmp;
    }
}

Scalar SplAkima::operator()(Scalar x, size_t order) const 
{
    const std::vector<Scalar>& m_x = m_independentData;
    const std::vector<Scalar>& m_a = m_dependentData; 

    size_t idx = FindInterval(x);

    Scalar deltaX = x - m_x[idx]; 

    switch (order) {
    
    case 0 : 
    {
        Scalar deltaX2 = deltaX * deltaX; 
        return m_a[idx] + m_b[idx] * deltaX + m_c[idx] * deltaX2 + m_d[idx] * deltaX2 * deltaX;  
    }
    case 1 : return m_b[idx] + 2. * m_c[idx] * deltaX + 3. * m_d[idx] * deltaX * deltaX;  
    case 2 : return 2. * m_c[idx] + 6. * m_d[idx] * deltaX;
    case 3 : return 6. * m_d[idx];

    default: assert(0);
    }

    
    return 0;
}
}
