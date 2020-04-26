#pragma once
#include "FuelEnginePCH.h"

namespace fuel
{
#pragma region Vector2
	struct Vector2
	{
		Vector2(float xComp = 0, float yComp = 0)
			: x{ xComp }
			, y{ yComp }
		{}

		float x;
		float y;

		// Member functions
		const std::string& ToString() const;
		float MagnitudeSqr() const;
		float Magnitude() const;

		// Operator overloading
		friend std::ostream& operator<<(std::ostream& os, const Vector2& vec2);
		Vector2& operator+=(const Vector2& rhs);
		friend Vector2 operator+(Vector2 lhs, const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);
		friend Vector2 operator-(Vector2 lhs, const Vector2& rhs);
	};
	// Member functions
	inline const std::string& Vector2::ToString() const
	{
		return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
	}

	inline float Vector2::MagnitudeSqr() const
	{
		return (x * x + y * y);
	}
	inline float Vector2::Magnitude() const
	{
		return sqrtf(x * x + y * y);
	}

	
	// Operator overloading
	inline std::ostream& operator<<(std::ostream& os, const Vector2& vec2)
	{
		os << "[" << vec2.x << ", " << vec2.y << "]";
		return  os;
	}
	inline Vector2& Vector2::operator+=(const Vector2& rhs)
	{
		Vector2 addition{ Vector2(this->x + rhs.x, this->y + rhs.y) };
		return addition;
	}
	inline Vector2& Vector2::operator-=(const Vector2& rhs)
	{
		Vector2 substraction{ Vector2(this->x - rhs.x, this->y - rhs.y) };
		return substraction;
	}
	inline Vector2 operator+(Vector2 lhs, const Vector2& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}
	inline Vector2 operator-(Vector2 lhs, const Vector2& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}
#pragma endregion 

#pragma region Vector3
	struct Vector3
	{
		Vector3(Vector2 vec2) : Vector3(vec2.x, vec2.y) {}
		Vector3(float xComp = 0, float yComp = 0, float zComp = 0)
			: x{ xComp }
			, y{ yComp }
			, z{ zComp }
		{}

		float x;
		float y;
		float z;

		// Member functions
		const std::string& ToString() const;
		float MagnitudeSqr() const;
		float Magnitude() const;
		
		// Operator overloading
		friend std::ostream& operator<<(std::ostream os, const Vector3& vec3);
		Vector3& operator+=(const Vector3& rhs);
		friend Vector3 operator+(Vector3 lhs, const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		friend Vector3 operator-(Vector3 lhs, const Vector3& rhs);
	};
	// Member functions
	inline const std::string& Vector3::ToString() const
	{
		return "[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "]";
	}

	inline float Vector3::MagnitudeSqr() const
	{
		return (x * x + y * y + z * z);
	}
	inline float Vector3::Magnitude() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	// Operator overloading
	inline std::ostream& operator<<(std::ostream os, const Vector3& vec3)
	{
		os << "[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
		return  os;
	}
	inline Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		Vector3 addition{ Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z) };
		return addition;
	}
	inline Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		Vector3 substraction{ Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z) };
		return substraction;
	}
	inline Vector3 operator+(Vector3 lhs, const Vector3& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		return lhs;
	}
	inline Vector3 operator-(Vector3 lhs, const Vector3& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		return lhs;
	}
#pragma endregion

#pragma region Structs
	struct Color4
	{
		Color4(const float rChannel = 1.f, const float gChannel = 1.f, const float bChannel = 1.f, const float aChannel = 1.f)
			: r{ rChannel }
			, g{ gChannel }
			, b{ bChannel }
			, a{ aChannel }
		{}
		
		float r{ 1.f };
		float g{ 1.f };
		float b{ 1.f };
		float a{ 1.f };
	};
	
	struct ColoredText
	{
		ColoredText(Color4 textColor = {1.f, 1.f, 1.f, 1.f}, const std::string& message = "")
			: color{ textColor }
			, text{ message }
		{}
		
		Color4 color;
		std::string text;
	};
#pragma endregion

#pragma region Shapes
	struct Rectf
	{
		Rectf(const float posX = 0, const float posY = 0, const float widthRect = 0, const float heightRect = 0)
			: x{ posX }
			, y{ posY }
			, width{ widthRect }
			, height{ heightRect }
		{}
		Rectf(const Vector2 position, const Vector2 dimensions)
			: x{ position.x }
			, y{ position.y }
			, width{ dimensions.x }
			, height{ dimensions.y }
		{}
		
		float x{ 0.f };
		float y{ 0.f };
		float width{ 0.f };
		float height{ 0.f };
	};

	struct Spheref
	{
		Spheref(const Vector2& pos = Vector2(), const float r = 10.f)
			: x{ pos.x }
			, y{ pos.y }
			, radius{ r }
		{}
		Spheref(const float xPos = 0.f, const float yPos = 0.f, const float r = 10.f)
			: x{ xPos }
			, y{ yPos }
			, radius{ r }
		{}
		
		float x{ 0.f };
		float y{ 0.f };
		float radius{ 10.f };
	};
#pragma endregion 
}

#pragma region HelperFunctions
template<typename T>
void SafeDelete(T object)
{
	if (object != nullptr)
	{
		delete object;
		object = nullptr;
	}
}

template<typename T>
void Clamp(T& value, T hi, T lo)
{
	if (value > hi)
		value = hi;

	if (value < lo)
		value = lo;
}
#pragma endregion 