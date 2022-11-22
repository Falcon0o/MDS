#pragma once

#include <stdint.h>
#include <cmath>

namespace msd {

#define USE_DOUBLE_PRECISION

#ifdef USE_DOUBLE_PRECISION
using Scalar = double;
#else 
using Scalar = float;
#endif


inline Scalar Sqrt(const Scalar& s) {
#ifdef USE_DOUBLE_PRECISION
    return sqrt(s);
#else 
    return sqrtf(s);
#endif
}

inline Scalar Fabs(const Scalar& s) {
#ifdef USE_DOUBLE_PRECISION
    return fabs(s);
#else 
    return fabsf(s);
#endif
}

inline Scalar Atan2(const Scalar& Y, const Scalar& X) {
    #ifdef USE_DOUBLE_PRECISION
    return atan2(Y, X);
#else 
    return atan2f(Y, X);
#endif
}

inline Scalar Acos(const Scalar& c) {
    #ifdef USE_DOUBLE_PRECISION
    return acos(c);
#else 
    return acosf(c);
#endif
}

inline Scalar Atan(const Scalar& c) {
    #ifdef USE_DOUBLE_PRECISION
    return atan(c);
#else 
    return atanf(c);
#endif
}

inline Scalar Sin(const Scalar& angle) {
    #ifdef USE_DOUBLE_PRECISION
    return sin(angle);
#else 
    return sinf(angle);
#endif
}

inline Scalar Cos(const Scalar& angle) {
#ifdef USE_DOUBLE_PRECISION
    return cos(angle);
#else 
    return cosf(angle);
#endif
}

const Scalar PIdiv2 = Acos(0.);
const Scalar PIdiv4 = PIdiv2 / 2;
const Scalar PI = 2. * PIdiv2;

inline Scalar Degree2Radian(const Scalar& d) {
    const Scalar tmp = PI / 180.;
    return d * tmp;
}

inline Scalar Rand() {
    return static_cast<Scalar>(rand()) / RAND_MAX;
}
} // end namespace msd