#pragma once

#include "math/Matrix.h"

#include <limits>
namespace msd {

class Vector3 : public Matrix<3, 1>{
public:
    Vector3(const Scalar& x, const Scalar& y, const Scalar& z) {
        SetXYZ(x, y, z);
    }

    Vector3() {}

    Vector3(const Scalar* arr) : Vector3(arr[0], arr[1], arr[2]) { }
    explicit Vector3(const Matrix<3, 1>& other) : Matrix<3, 1>(other) {}

    const Scalar& operator[](uint64_t id) const {
        return static_cast<const Matrix<3, 1>*>(this)->operator()(id, 0);
    }

    Scalar& operator[](uint64_t id) {
        return static_cast<Matrix<3, 1>*>(this)->operator()(id, 0);
    }

    void SetXYZ(const Scalar &x, const Scalar &y, const Scalar &z) {
        X() = x; 
        Y() = y;
        Z() = z;
    }


    Scalar& X() { return (*this)[0]; }
	const Scalar& X() const { return (*this)[0]; }
	
	Scalar& Y() { return (*this)[1];  }
	const Scalar& Y() const { return (*this)[1]; }

	Scalar&  Z() { return (*this)[2]; }
	const Scalar&  Z() const { return (*this)[2]; }

    Scalar Dot(const Vector3& other) const {
        return (this->Transpose().Product(other))(0, 0);
    }

    Matrix<3, 3> SkewSymmetricMatrix() const {
        Matrix<3, 3> ans;
        ans(0, 0) = 0;
        ans(1, 0) = (*this)[2];
        ans(2, 0) = -(*this)[1];

        ans(0, 1) = -(*this)[2];
        ans(1, 1) = 0;
        ans(2, 1) = (*this)[0];

        ans(0, 2) = (*this)[1];
        ans(1, 2) = -(*this)[0];
        ans(2, 2) = 0;

        return ans;
    }

    Vector3 Cross(const Vector3& other) const {
#if 0
        Matrix<3, 1> ans = SkewSymmetricMatrix().Times(other);
        return Vector3(ans(0, 0), ans(1, 0), ans(2, 0));
#else
        return Vector3((*this)[1] * other[2] - (*this)[2] * other[1], 
                      (*this)[2] * other[0] - (*this)[0] * other[2], 
                      (*this)[0] * other[1] - (*this)[1] * other[0]);
#endif
    }

    Vector3 operator+(const Vector3& other) const {
        return Vector3(this->Matrix<3, 1>::operator+(other));
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(this->Matrix<3, 1>::operator-(other));
    }

    Vector3 operator*(const Scalar &s) const
    {
        return Vector3(this->Matrix<3, 1>::operator*(s));
    }

    void operator/=(const Scalar &s)
    {
        this->Matrix<3, 1>::operator/=(s);
    }

    Vector3 operator/(const Scalar& s) const {
        return Vector3(this->Matrix<3, 1>::operator/(s));
    }
    Scalar Magnitude2() const
    {
        return Dot(*this);
    }

    Scalar Magnitude() const
    {
        return Sqrt(Magnitude2());
    }

    // TODO: 抛异常
    void Normalize()
    {
        operator/=(Magnitude());
    }

    bool IsIdentity() const { 
        return Fabs(Magnitude2() - 1.) < std::numeric_limits<Scalar>::epsilon(); }

    static Vector3 Rand() { return Vector3(msd::Rand(), msd::Rand(), msd::Rand()); } 
};








   
    

};