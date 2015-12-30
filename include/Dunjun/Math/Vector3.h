#ifndef DUNJUN_MATH_VECTOR3_H
#define DUNJUN_MATH_VECTOR3_H

#include <Dunjun/Types.h>

#include <cmath>
#include <iostream>

namespace Dunjun
{
	struct Vector3
	{
		Vector3()
			: x(0)
			, y(0)
			, z(0)
		{
		}

		Vector3(f32 x, f32 y, f32 z)
			: x(x)
			, y(y)
			, z(z)
		{
		}

		Vector3(f32 data[3])
			: x(data[0])
			, y(data[1])
			, z(data[2])
		{
		}

		Vector3(const Vector3 & other) = default;

		union
		{
			f32 data[3];
			struct
			{
				f32 x, y, z;
			};
			struct
			{
				f32 r, g, b;
			};
			struct
			{
				f32 s, t, p;
			};
		};

		inline f32 & operator[](usize index) { return data[index]; }
		inline const f32 & operator[](usize index) const { return data[index]; }

		b08 operator==(const Vector3 & other) const
		{
			for (usize i = 0; i < 3; ++i)
			{
				if (data[i] != other.data[i])
					return false;
			}
			return true;
		}

		b08 operator!=(const Vector3 & other) const
		{
			return !operator==(other);
		}

		inline Vector3 operator-() const { return Vector3{ -x, -y, -z }; }

		inline Vector3 operator+(const Vector3 & other) const
		{
			return Vector3{ x + other.x, y + other.y, z + other.z };
		}

		inline Vector3 & operator+=(const Vector3 & other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		inline Vector3 operator-(const Vector3 & other) const
		{
			return Vector3{ x - other.x, y - other.y, z - other.z };
		}

		inline Vector3 & operator-=(const Vector3 & other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		inline Vector3 operator*(f32 scalar) const
		{
			return Vector3{ x * scalar, y * scalar, z * scalar };
		}

		// Hadamard Product
		Vector3 operator*(const Vector3 & other) const
		{
			Vector3 result;
			for (usize i = 0; i < 3; ++i)
			{
				result[i] = data[i] * other.data[i];
			}
			return result;
		}

		Vector3 operator/(const Vector3 & other) const
		{
			Vector3 result;
			for (usize i = 0; i < 3; ++i)
			{
				result[i] = data[i] / other.data[i];
			}
			return result;
		}

		inline Vector3 & operator*=(f32 scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		inline Vector3 operator/(f32 scalar) const
		{
			return Vector3{ x / scalar, y / scalar, z / scalar };
		}

		inline Vector3 & operator/=(f32 scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}
	};

	// to handle (scalar * vec)
	inline Vector3 operator*(f32 scalar, const Vector3 & vector)
	{
		return vector * scalar;
	}

	inline f32 dot(const Vector3 & a, const Vector3 & b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	inline Vector3 cross(const Vector3 & a, const Vector3 & b)
	{
		return Vector3{ a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
	}

	inline f32 lengthSq(const Vector3 & a)
	{
		return dot(a, a);
	}

	inline f32 length(const Vector3 & a)
	{
		return std::sqrtf(lengthSq(a));
	}

	inline Vector3 normalize(const Vector3 & a, f32 scalar = 1.0f)
	{
		return a * (1.0f / length(a));
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector3 & v)
	{
		return os << "Vector3(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
	}
} // namespace Dunjun

#endif//DUNJUN_MATH_VECTOR3_H
