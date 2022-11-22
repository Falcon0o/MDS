#pragma once

#include "math/Scalar.h"
#include <eigen3/Eigen/Dense>

namespace msd {

typedef Eigen::Matrix<Scalar,3,1> Vector3;

template <class OutStream>
void Print(const Vector3& v, OutStream& stream) 
{
	stream << v(0, 0) << " ";
	stream << v(1, 0) << " ";
	stream << v(2, 0) << " ";
}

template <>
inline Vector3 Random() {
    return Vector3::Random();
}


};