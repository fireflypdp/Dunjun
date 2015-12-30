#ifndef DUNJUN_MATH_VECTOR2_H
#define DUNJUN_MATH_VECTOR2_H

#include <Dunjun/Types.h>

#include <cmath>
#include <iostream>

namespace Dunjun
{
	struct Vector2
	{
		Vector2()
			: x(0)
			, y(0)
		{
		}

		Vector2(f32 x, f32 y)
			: x(x)
			, y(y)
		{
		}

		Vector2(f32 data[2])
			: x(data[0])
			, y(data[1])
		{
		}

		Vector2(const Vector2 & other) = default;

		union
		{
			f32 data[2];
			struct
			{
				f32 x, y;
			};
			struct
			{
				f32 r, g;
			};
			struct
			{
				f32 s, t;
			};
		};

		inline f32 & operator[](usize index) { return data[index]; }
		inline const f32 & operator[](usize index) const { return data[index]; }

		bool operator==(const Vector2 & other) const
		{
			for (usize i = 0; i < 2; ++i)
			{
				if (data[i] != other.data[i])
					return false;
			}
			return true;
		}

		b08 operator!=(const Vector2 & other) const
		{
			return !operator==(other);
		}

		inline Vector2 operator-() const { return Vector2{ -x, -y }; }

		inline Vector2 operator+(const Vector2 & other) const
		{
			return Vector2{ x + other.x, y + other.y };
		}

		inline Vector2 & operator+=(const Vector2 & other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		inline Vector2 operator-(const Vector2 & other) const
		{
			return Vector2{ x - other.x, y - other.y };
		}

		inline Vector2 & operator-=(const Vector2 & other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		inline Vector2 operator*(f32 scalar) const
		{
			return Vector2{ x * scalar, y * scalar };
		}

		// Hadamard Product
		Vector2 operator*(const Vector2 & other) const
		{
			Vector2 result;
			for (usize i = 0; i < 2; ++i)
			{
				result[i] = data[i] * other.data[i];
			}
			return result;
		}

		Vector2 operator/(const Vector2 & other) const
		{
			Vector2 result;
			for (usize i = 0; i < 2; ++i)
			{
				result[i] = data[i] / other.data[i];
			}
			return result;
		}

		inline Vector2 & operator*=(f32 scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		inline Vector2 operator/(f32 scalar) const
		{
			return Vector2{ x / scalar, y / scalar };
		}

		inline Vector2 & operator/=(f32 scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}
	};

	// to handle (scalar * vec)
	inline Vector2 operator*(f32 scalar, const Vector2 & vector)
	{
		return vector * scalar;
	}

	inline f32 dot(const Vector2 & a, const Vector2 & b)
	{
		return a.x*b.x + a.y*b.y;
	}

	inline f32 cross(const Vector2 & a, const Vector2 & b)
	{
		return a.x*b.y - a.y*b.x;
	}

	inline f32 lengthSq(const Vector2 & a)
	{
		return dot(a, a);
	}

	inline f32 length(const Vector2 & a)
	{
		return std::sqrtf(lengthSq(a));
	}

	inline Vector2 normalize(const Vector2 & a, f32 scalar = 1.0f)
	{
		return a * (1.0f / length(a));
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector2 & v)
	{
		return os << "Vector2(" << v[0] << ", " << v[1] << ")";
	}
} // namespace Dunjun

#endif//DUNJUN_MATH_VECTOR2_H
