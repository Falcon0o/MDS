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


// template <>
// class Matrix<3, 1>{
// public:
//     Matrix(const Scalar& x, const Scalar& y, const Scalar& z) {
//         SetXYZ(x, y, z);
//     }

//     Matrix() {}

//     // Matrix(const Scalar* arr) : Matrix(arr[0], arr[1], arr[2]) { }
//     // explicit Vector3(const Matrix<3, 1>& other) : Matrix<3, 1>(other) {}

//     const Scalar& operator[](uint64_t id) const {
//         return (*this)(id, 0);
//     }

//     Scalar& operator[](uint64_t id) {
//         return (*this)(id, 0);
//     }

//     void SetXYZ(const Scalar &x, const Scalar &y, const Scalar &z) {
//         X() = x; 
//         Y() = y;
//         Z() = z;
//     }


//     Scalar& X() { return (*this)[0]; }
// 	const Scalar& X() const { return (*this)[0]; }
	
// 	Scalar& Y() { return (*this)[1];  }
// 	const Scalar& Y() const { return (*this)[1]; }

// 	Scalar& Z() { return (*this)[2]; }
// 	const Scalar&  Z() const { return (*this)[2]; }

//     Scalar Dot(const Matrix& other) const {
//         return (this->Transpose().Product(other))(0, 0);
//     }

//     Matrix<3, 3> SkewSymmetricMatrix() const {
//         Matrix<3, 3> ans;
//         ans(0, 0) = 0;
//         ans(1, 0) = (*this)[2];
//         ans(2, 0) = -(*this)[1];

//         ans(0, 1) = -(*this)[2];
//         ans(1, 1) = 0;
//         ans(2, 1) = (*this)[0];

//         ans(0, 2) = (*this)[1];
//         ans(1, 2) = -(*this)[0];
//         ans(2, 2) = 0;

//         return ans;
//     }

//     Matrix Cross(const Matrix& other) const {
// #if 0
//         Matrix<3, 1> ans = SkewSymmetricMatrix().Times(other);
//         return Vector3(ans(0, 0), ans(1, 0), ans(2, 0));
// #else
//         return Matrix((*this)[1] * other[2] - (*this)[2] * other[1], 
//                       (*this)[2] * other[0] - (*this)[0] * other[2], 
//                       (*this)[0] * other[1] - (*this)[1] * other[0]);
// #endif
//     }

//     // Matrix operator+(const Matrix& other) const {
//     //     return Vector3(this->Matrix<3, 1>::operator+(other));
//     // }

//     // Vector3 operator-(const Vector3& other) const {
//     //     return Vector3(this->Matrix<3, 1>::operator-(other));
//     // }

//     // Vector3 operator*(const Scalar &s) const
//     // {
//     //     return Vector3(this->Matrix<3, 1>::operator*(s));
//     // }

//     // void operator/=(const Scalar &s)
//     // {
//     //     this->Matrix<3, 1>::operator/=(s);
//     // }

//     // Vector3 operator/(const Scalar& s) const {
//     //     return Vector3(this->Matrix<3, 1>::operator/(s));
//     // }
//     Scalar Magnitude2() const
//     {
//         return Dot(*this);
//     }

//     Scalar Magnitude() const
//     {
//         return Sqrt(Magnitude2());
//     }

//     // TODO: 抛异常
//     void Normalize()
//     {
//         operator/=(Magnitude());
//     }

//     bool IsIdentity() const { 
//         return Fabs(Magnitude2() - 1.) < std::numeric_limits<Scalar>::epsilon(); }

//     static Matrix Rand() { return Matrixcle(msd::Rand(), msd::Rand(), msd::Rand()); } 
// };

// using Vector3 = Matrix<3, 1>;   
    

};