#ifndef DUNJUN_MATH_VECTOR4_H
#define DUNJUN_MATH_VECTOR4_H

#include <Dunjun/Types.h>

#include <cmath>
#include <iostream>

namespace Dunjun
{
	struct Vector4
	{
		Vector4()
			: x(0)
			, y(0)
			, z(0)
			, w(0)
		{
		}

		Vector4(f32 x, f32 y, f32 z, f32 w)
			: x(x)
			, y(y)
			, z(z)
			, w(w)
		{
		}

		Vector4(f32 data[4])
			: x(data[0])
			, y(data[1])
			, z(data[2])
			, w(data[3])
		{
		}

		Vector4(const Vector4 & other) = default;

		union
		{
			f32 data[4];
			struct
			{
				f32 x, y, z, w;
			};
			struct
			{
				f32 r, g, b, a;
			};
			struct
			{
				f32 s, t, p, q;
			};
		};

		inline f32 & operator[](usize index) { return data[index]; }
		inline const f32 & operator[](usize index) const { return data[index]; }

		b08 operator==(const Vector4 & other) const
		{
			for (usize i = 0; i < 4; ++i)
			{
				if (data[i] != other.data[i])
					return false;
			}
			return true;
		}

		b08 operator!=(const Vector4 & other) const
		{
			return !operator==(other);
		}

		inline Vector4 operator-() const { return Vector4{ -x, -y, -z, -w }; }

		inline Vector4 operator+(const Vector4 & other) const
		{
			return Vector4{ x + other.x, y + other.y, z + other.z, w + other.w };
		}

		inline Vector4 & operator+=(const Vector4 & other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		inline Vector4 operator-(const Vector4 & other) const
		{
			return Vector4{ x - other.x, y - other.y, z - other.z, w - other.w };
		}

		inline Vector4 & operator-=(const Vector4 & other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		inline Vector4 operator*(f32 scalar) const
		{
			return Vector4{ x * scalar, y * scalar, z * scalar, w * scalar };
		}

		// Hadamard Product
		Vector4 operator*(const Vector4 & other) const
		{
			Vector4 result;
			for (usize i = 0; i < 4; ++i)
			{
				result[i] = data[i] * other.data[i];
			}
			return result;
		}

		Vector4 operator/(const Vector4 & other) const
		{
			Vector4 result;
			for (usize i = 0; i < 4; ++i)
			{
				result[i] = data[i] / other.data[i];
			}
			return result;
		}

		inline Vector4 & operator*=(f32 scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		inline Vector4 operator/(f32 scalar) const
		{
			return Vector4{ x / scalar, y / scalar, z / scalar, w / scalar };
		}

		inline Vector4 & operator/=(f32 scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}
	};

	// to handle (scalar * vec)
	inline Vector4 operator*(f32 scalar, const Vector4 & vector)
	{
		return vector * scalar;
	}

	inline f32 dot(const Vector4 & a, const Vector4 & b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
	}

	inline f32 lengthSq(const Vector4 & a)
	{
		return dot(a, a);
	}

	inline f32 length(const Vector4 & a)
	{
		return std::sqrtf(lengthSq(a));
	}

	inline Vector4 normalize(const Vector4 & a, f32 scalar = 1.0f)
	{
		return a * (1.0f / length(a));
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector4 & v)
	{
		return os << "Vector4(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
	}
} // namespace Dunjun

#endif//DUNJUN_MATH_VECTOR4_H
