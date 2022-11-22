#include "math/Quaternion.h"

#include <functional>

namespace msd {

Quaternion::Quaternion(const Matrix<3,3>& r) {
	this->operator=(r);
}

Quaternion& Quaternion::operator=(const Matrix<3,3>& m)
{
	W() = Sqrt(m.Trace() + 1.) / 2.;

	if (W() > std::numeric_limits<Scalar>::epsilon())
	{
		auto D = [&](uint64_t i, uint64_t j)->Scalar {
			return m(j, i) - m(i, j);
		};

		Scalar tmp = 4 * W();
		X() = D(1, 2) / tmp;
		Y() = D(2, 0) / tmp;
		Z() = D(0, 1) / tmp;
		return *this;
	}

	X() = m(0, 0);
	Y() = m(1, 1);
	Z() = m(2, 2);

	int id = X() > Y() ? 0 : 1;
	id = Z() > GetVector()[id] ? 2 : id;
	int id1 = (id + 1) % 3;
	int id2 = (id + 2) % 3;

	GetVector()[id] = Sqrt((GetVector()[id] + 1.) / 2.);

	Scalar tmp = GetVector()[id] * 4.;

	auto S = [&](uint64_t i, uint64_t j)->Scalar {
		return m(j, i) + m(i, j);
	};

	GetVector()[id1] = S(id, id1) / tmp;
	GetVector()[id2] = S(id, id2) / tmp;

	return *this;
}

template <typename Q>
Matrix<3,3> DirCosMatrix(const Q& q) {

	Scalar lambda00 = q.W() * q.W();
	Scalar lambda01 = q.W() * q.X();
	Scalar lambda02 = q.W() * q.Y();
	Scalar lambda03 = q.W() * q.Z();

	Scalar lambda11 = q.X() * q.X();
	Scalar lambda12 = q.X() * q.Y();
	Scalar lambda13 = q.X() * q.Z();

	Scalar lambda22 = q.Y() * q.Y();
	Scalar lambda23 = q.Y() * q.Z();

	Scalar lambda33 = q.Z() * q.Z();

	Matrix<3,3> ans;
	ans(0, 0) = 2. * (lambda00 + lambda11) - 1.;
	ans(0, 1) = 2. * (lambda12 - lambda03);
	ans(0, 2) = 2. * (lambda13 + lambda02);

	ans(1, 0) = 2. * (lambda12 + lambda03);
	ans(1, 1) = 2. * (lambda00 + lambda22) - 1.;
	ans(1, 2) = 2. * (lambda23 - lambda01);

	ans(2, 0) = 2. * (lambda13 - lambda02);
	ans(2, 1) = 2. * (lambda23 + lambda01);
	ans(2, 2) = 2. * (lambda00 + lambda33) - 1.;

	return ans;
}

Matrix<3,3> Quaternion::DirCosMatrix() const
{
	return msd::DirCosMatrix(*this);
}

Matrix<3,3> QuaternionC::DirCosMatrix() const
{
	return msd::DirCosMatrix(*this);
}
// Vector3 Quaternion::operator*(const Vector3& v) const {
// 	return Matrix<3, 3>(*this) * v;
// }

// Vector3 QuaternionC::operator*(const Vector3& v) const {
// 	return Matrix<3, 3>(*this) * v;
// }

void Quaternion::CalAxisAndAngle(Vector3& axis, Scalar& angle) const
{
	//Scalar s = W(); // $$
	//if (s > 1) s = 1;
	//if (s < -1) s = -1;

	//angle = Acos(2. * s * s - 1.);

	assert(0);
	
}
//double s = 1 < s_temp.W() ? 1 : s_temp.W();
	//double sign = s < 0 ? -1 : 1;
	//double a = (fabs(s - 1) <= 1e-40 ||
	//	fabs(s + 1) <= 1e-40) ? (2 * sign) : (sign * acos(2 * s * s - 1) / sqrt(1 - s * s));

	//double tagent[3];
	//tagent[0] = a * s_temp.X();
	//tagent[1] = a * s_temp.Y();
	//tagent[2] = a * s_temp.Z();

	//axis.Set_Value(tagent);
	//angVel = Vlength(tagent);

	//PQP_Scalar len = axis.Length_Sq();
	//if (len < 0.00000001f)
	//{
	//	axis.Set_Value(1.f, 0.f, 0.f);
	//}
	//else
	//	axis /= sqrt(len);


Quaternion Quaternion::Rand() {
	
	Vector3 axis = Vector3::Rand();
	axis.Normalize();

	Scalar angle = msd::Rand();
	
	Quaternion ans;
	ans.InitWithAxisAndAngle(axis, angle);
	return ans;
}

} // end namespace msd