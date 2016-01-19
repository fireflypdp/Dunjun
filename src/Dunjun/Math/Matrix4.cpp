#include <Dunjun/Math/Matrix4.h>

namespace Dunjun
{
	Matrix4::Matrix4()
		: data{ Vector4(1, 0, 0, 0), Vector4(0, 1, 0, 0), Vector4(0, 0, 1, 0), Vector4(0, 0, 0, 1) }
	{
	}

	Matrix4::Matrix4(f32 x)
		: data{ Vector4(x, 0, 0, 0), Vector4(0, x, 0, 0), Vector4(0, 0, x, 0), Vector4(0, 0, 0, x) }
	{
	}

	Matrix4::Matrix4(const Vector4 & v0, const Vector4 & v1, const Vector4 & v2, const Vector4 & v3)
		: data{ v0, v1, v2, v3 }
	{
	}

	Vector4 & Matrix4::operator[](usize index) { return data[index]; }
	const Vector4 & Matrix4::operator[](usize index) const { return data[index]; }

	bool Matrix4::operator==(const Matrix4 & m2) const
	{
		const Matrix4 & m1 = *this;
		for (usize i = 0; i < 4; ++i)
		{
			if (m1[i] != m2[i])
				return false;
		}
		return true;
	}

	bool Matrix4::operator!=(const Matrix4 & other) const
	{
		return !operator==(other);
	}

	Matrix4 Matrix4::operator+(const Matrix4 & other) const
	{
		Matrix4 result;
		for (usize i = 0; i < 4; ++i)
		{
			result[i] = data[i] + other.data[i];
		}
		return result;
	}

	Matrix4 Matrix4::operator-(const Matrix4 & other) const
	{
		Matrix4 result;
		for (usize i = 0; i < 4; ++i)
		{
			result[i] = data[i] - other.data[i];
		}
		return result;
	}

	Matrix4 Matrix4::operator*(const Matrix4 & m2) const
	{
		const Matrix4 & m1 = *this;
		Matrix4 result;
		result[0][0] = m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3];
		result[1][0] = m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3];
		result[2][0] = m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3];
		result[3][0] = m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3];
		result[0][1] = m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3];
		result[1][1] = m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3];
		result[2][1] = m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3];
		result[3][1] = m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3];
		result[0][2] = m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3];
		result[1][2] = m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3];
		result[2][2] = m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3];
		result[3][2] = m1[0][2] * m2[3][0] + m1[1][2] * m2[3][1] + m1[2][2] * m2[3][2] + m1[3][2] * m2[3][3];
		result[0][3] = m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3];
		result[1][3] = m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3];
		result[2][3] = m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3];
		result[3][3] = m1[0][3] * m2[3][0] + m1[1][3] * m2[3][1] + m1[2][3] * m2[3][2] + m1[3][3] * m2[3][3];

		return result;
	}

	Vector4 Matrix4::operator*(const Vector4 & v) const
	{
		const Matrix4 & m = *this;

		Vector4 result;
		result[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3];
		result[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3];
		result[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3];
		result[3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3];
		return result;
	}

	Matrix4 Matrix4::operator*(f32 scalar) const
	{
		Matrix4 result;
		for (usize i = 0; i < 4; ++i)
		{
			result[i] = data[i] * scalar;
		}
		return result;
	}

	Matrix4 Matrix4::operator/(f32 scalar) const
	{
		Matrix4 result;
		for (usize i = 0; i < 4; ++i)
		{
			result[i] = data[i] / scalar;
		}
		return result;
	}

	Matrix4 & Matrix4::operator+=(const Matrix4 & other)
	{
		return (*this = (*this) + other);
	}

	Matrix4 & Matrix4::operator-=(const Matrix4 & other)
	{
		return (*this = (*this) - other);
	}

	Matrix4 & Matrix4::operator*=(const Matrix4 & other)
	{
		return (*this = (*this) * other);
	}

	Matrix4 Matrix4::Transpose() const
	{
		Matrix4 result;

		for (usize i = 0; i < 4; ++i)
		{
			for (usize j = 0; j < 4; ++j)
			{
				result[i][j] = data[j][i];
			}
		}
		return result;
	}

	f32 Matrix4::Determinant() const
	{
		const Matrix4 & m = *this;

		f32 coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		f32 coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		f32 coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		f32 coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		f32 coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		f32 coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		f32 coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		f32 coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		f32 coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		f32 coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		f32 coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		f32 coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		f32 coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		f32 coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		f32 coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		f32 coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		f32 coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		f32 coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		Vector4 fac0(coef00, coef00, coef02, coef03);
		Vector4 fac1(coef04, coef04, coef06, coef07);
		Vector4 fac2(coef08, coef08, coef10, coef11);
		Vector4 fac3(coef12, coef12, coef14, coef15);
		Vector4 fac4(coef16, coef16, coef18, coef19);
		Vector4 fac5(coef20, coef20, coef22, coef23);

		Vector4 vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		Vector4 vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		Vector4 vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		Vector4 vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		Vector4 inv0(vec1*fac0 - vec2*fac1 + vec3*fac2);
		Vector4 inv1(vec0*fac0 - vec2*fac3 + vec3*fac4);
		Vector4 inv2(vec0*fac1 - vec1*fac3 + vec3*fac5);
		Vector4 inv3(vec0*fac2 - vec1*fac4 + vec2*fac5);

		Vector4 signA(+1, -1, +1, -1);
		Vector4 signB(-1, +1, -1, +1);
		Matrix4 inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

		Vector4 row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

		Vector4 dot0(m[0] * row0);
		f32 dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);
		return dot1;
	}

	Matrix4 Matrix4::Inverse() const
	{
		const Matrix4 & m = *this;

		f32 coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		f32 coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		f32 coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		f32 coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		f32 coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		f32 coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		f32 coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		f32 coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		f32 coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		f32 coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		f32 coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		f32 coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		f32 coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		f32 coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		f32 coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		f32 coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		f32 coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		f32 coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		Vector4 fac0(coef00, coef00, coef02, coef03);
		Vector4 fac1(coef04, coef04, coef06, coef07);
		Vector4 fac2(coef08, coef08, coef10, coef11);
		Vector4 fac3(coef12, coef12, coef14, coef15);
		Vector4 fac4(coef16, coef16, coef18, coef19);
		Vector4 fac5(coef20, coef20, coef22, coef23);

		Vector4 vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		Vector4 vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		Vector4 vec3(m[1][3], m[0][3], m[0][3], m[0][3]);
		Vector4 vec0(m[1][0], m[0][0], m[0][0], m[0][0]);

		Vector4 inv0(vec1*fac0 - vec2*fac1 + vec3*fac2);
		Vector4 inv1(vec0*fac0 - vec2*fac3 + vec3*fac4);
		Vector4 inv2(vec0*fac1 - vec1*fac3 + vec3*fac5);
		Vector4 inv3(vec0*fac2 - vec1*fac4 + vec2*fac5);

		Vector4 signA(+1, -1, +1, -1);
		Vector4 signB(-1, +1, -1, +1);
		Matrix4 inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

		Vector4 row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

		Vector4 dot0(m[0] * row0);
		f32 dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

		f32 oneOverDeterminant = 1.0f / dot1;
		return inverse * oneOverDeterminant;
	}
} // namespace Dunjun
