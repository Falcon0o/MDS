#pragma once



#include <eigen3/Eigen/Dense>
#include "math/Scalar.h"
#include "math/Vector3.h"
namespace msd {

using Quaternion = Eigen::Quaternion<Scalar>;
// class QuaternionC;

template <>
inline Quaternion Random() {
	Vector3 axis = Vector3::Random();
	axis.normalize();
	return Quaternion(Eigen::AngleAxis<Scalar>(Random<Scalar>(), axis));

}

template <class OutStream>
void Print(const Quaternion& q, OutStream& stream) {
	stream << q.x() << " ";
	stream << q.y() << " ";
	stream << q.z() << " ";
	stream << q.w() << " ";
}


        
// class Quaternion : public Matrix<4, 1>{
// public:
// 	Quaternion() {}
// 	Quaternion(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w) {
// 		Set(x, y, z, w);
// 	}

// 	Quaternion(const Vector3& v, const Scalar& s) {
// 		Set(v, s);
// 	}

// 	// FORCE_INLINE Quaternion(const Vector3& axis, const Radian& r) { Set(axis, r); }
// 	// FORCE_INLINE Quaternion(const Vector3& axis, const Degree& d) { Set(axis, d); }

	
	
	
// 	Quaternion(const Quaternion& q) : Matrix<4, 1>(q){
// 	}

// 	Quaternion(const Matrix<3, 3>&);
// 	Quaternion& operator=(const Matrix<3, 3>& r);

// 	Quaternion& operator=(const Quaternion& q) {
// 		if (this != &q) {
// 			memcpy(this, &q, sizeof(Quaternion));
// 		}
// 		return *this;
// 	}
// 	void Set(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w) {
// 		X() = x;
// 		Y() = y;
// 		Z() = z;
//         W() = w;
// 	}

//     void Set(const Vector3& v, const Scalar& s) {
//         X() = v[0];
// 		Y() = v[1];
// 		Z() = v[2];
//         W() = s;
//     } 
//     void InitWithAxisAndAngle(const Vector3& axis, const Scalar& angle) {
//         assert(axis.IsIdentity());
// 	    Set(axis * Sin(angle * 0.5), Cos(angle * 0.5));
//     }

// 	template <uint16_t ROT_SEQ>
// 	void InitWithEulerAngle(const Scalar& angle_0, const Scalar& angle_1, const Scalar& angle_2);

// 	Scalar& X() { return (*this)(0, 0); }
// 	const Scalar& X() const { return (*this)(0, 0); }
	
// 	Scalar& Y() { return (*this)(1, 0);  }
// 	const Scalar& Y() const { return (*this)(1, 0); }

// 	Scalar&  Z() { return (*this)(2, 0); }
// 	const Scalar&  Z() const { return (*this)(2, 0); }

// 	Scalar&  W() { return (*this)(3, 0); }
// 	const Scalar&  W() const { return (*this)(3, 0); }

// 	Vector3 operator*(const Vector3& v) const {
// 		return reinterpret_cast<Vector3&&>(DirCosMatrix() * v);
// 	}

// 	const QuaternionC& Conjugate() const { return *reinterpret_cast<const QuaternionC*>(this); }

// 	void CalAxisAndAngle(Vector3& axis, Scalar& angle) const;

// 	const Vector3& GetVector() const {
// 		return *reinterpret_cast<const Vector3*>(this);
// 	}

// 	Vector3& GetVector() {
// 		return *reinterpret_cast<Vector3*>(this);
// 	}

// 	Matrix<3,3> DirCosMatrix() const;

// 	static Quaternion Rand();
// };

// class QuaternionC : public Matrix<4, 1>{
// public:
// 	Vector3 operator*(const Vector3& v) const {
// 		return reinterpret_cast<Vector3&&>(DirCosMatrix() * v);
// 	}

	
// 	Scalar X() { return -(*this)(0, 0); }
// 	const Scalar X() const { return -(*this)(0, 0); }
	
// 	Scalar Y() { return -(*this)(1, 0);  }
// 	const Scalar Y() const { return -(*this)(1, 0); }

// 	Scalar Z() { return -(*this)(2, 0); }
// 	const Scalar Z() const { return -(*this)(2, 0); }

// 	Scalar& W() { return (*this)(3, 0); }
// 	const Scalar& W() const { return (*this)(3, 0); }

// 	Matrix<3,3> DirCosMatrix() const;
// };

// template <typename Q0, typename Q1>
// Quaternion operator*(const Q0& q0, const Q1& q1) {

// 	return Quaternion(
// 		q0.W() * q1.X() + q0.X() * q1.W() - q0.Y() * q1.Z() + q0.Z() * q1.Y(),
// 		q0.W() * q1.Y() + q0.Y() * q1.W() - q0.Z() * q1.X() + q0.X() * q1.Z(),
// 		q0.W() * q1.Z() + q0.Z() * q1.W() - q0.X() * q1.Y() + q0.Y() * q1.X(),
// 		q0.W() * q1.W() - q0.X() * q1.X() - q0.Y() * q1.Y() - q0.Z() * q1.Z());
// }

// template <uint16_t ROT_SEQ>
// void Quaternion::InitWithEulerAngle(const Scalar& angle_0, const Scalar& angle_1, const Scalar& angle_2) {
// 	const Vector3 axis[] = {Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1)};

// 	constexpr uint16_t axis_0 = ROT_SEQ / 100 - 1;
// 	constexpr uint16_t axis_1 = ROT_SEQ % 100 / 10 - 1;
// 	constexpr uint16_t axis_2 = ROT_SEQ % 10 - 1;

// 	Quaternion q0;
// 	q0.InitWithAxisAndAngle(axis[axis_0], angle_0);

// 	Quaternion q1;
// 	q1.InitWithAxisAndAngle(axis[axis_1], angle_1);

// 	Quaternion q2;
// 	q2.InitWithAxisAndAngle(axis[axis_2], angle_2);

// 	(*this) = q2 * q1 * q0;	
// }
} // end namespace msd