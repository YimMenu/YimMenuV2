#pragma once
#include <cmath>

#pragma pack(push, 0x10)
namespace rage
{
	// atVector<float, 2>?
	class vector2
	{
	public:
		float x, y;

		constexpr vector2(float x, float y) :
		    x(x),
		    y(y)
		{
		}

		constexpr vector2() :
		    x(),
		    y()
		{
		}
	};

	// atVector<float, 3>?
	class alignas(16) vector3
	{
	public:
		float x, y, z;

	public:
		constexpr vector3(float x, float y, float z) :
		    x(x),
		    y(y),
		    z(z)
		{
		}

		constexpr vector3() :
		    x(),
		    y(),
		    z()
		{
		}

		bool operator==(const vector3& other) const
		{
			return this->x == other.x && this->y == other.y && this->z == other.z;
		}

		template<typename T>
		bool operator!=(const vector3& other) const
		{
			return this->x != other.x || this->y != other.y || this->z != other.z;
		}

		vector3 operator+(const vector3& other) const
		{
			vector3 vec;
			vec.x = this->x + other.x;
			vec.y = this->y + other.y;
			vec.z = this->z + other.z;
			return vec;
		}

		vector3 operator-(const vector3& other) const
		{
			vector3 vec;
			vec.x = this->x - other.x;
			vec.y = this->y - other.y;
			vec.z = this->z - other.z;
			return vec;
		}

		vector3 operator*(const vector3& other) const
		{
			vector3 vec;
			vec.x = this->x * other.x;
			vec.y = this->y * other.y;
			vec.z = this->z * other.z;
			return vec;
		}

		vector3 operator*(const float& other) const
		{
			vector3 vec;
			vec.x = this->x * other;
			vec.y = this->y * other;
			vec.z = this->z * other;
			return vec;
		}

		inline float GetMagnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		inline float GetDistance(const vector3& other) const
		{
			return (*this - other).GetMagnitude();
		}
	};
	static_assert(sizeof(rage::vector3) == 0x10);

	// atVector<float, 4>?
	class vector4
	{
	public:
		float x, y, z, w;

		constexpr vector4(float x, float y, float z, float w) :
		    x(x),
		    y(y),
		    z(z),
		    w(w)
		{
		}

		constexpr vector4() :
		    x(),
		    y(),
		    z(),
		    w()
		{
		}
	};

	union matrix34 {
		float data[4][4]; // yes, the underlying representation is 4x4
		struct
		{
			struct
			{
				float x, y, z, w;
			} rows[3];
		};
	};

	union matrix44 {
		float data[4][4];
		struct
		{
			struct
			{
				float x, y, z, w;
			} rows[4];
		};
	};


	// backwards compatibility
	// TODO: remove these!
	using fvector2 = vector2;
	using fvector3 = vector3;
	using fvector4 = vector4;
};
#pragma pack(pop)