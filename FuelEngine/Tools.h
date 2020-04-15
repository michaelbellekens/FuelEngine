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

		// Operator overloading
		friend std::ostream& operator<<(std::ostream& os, const Vector2& vec2);
		
	};
	// Member functions
	inline const std::string& Vector2::ToString() const
	{
		return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
	}

	
	// Operator overloading
	inline std::ostream& operator<<(std::ostream& os, const Vector2& vec2)
	{
		os << "[" << vec2.x << ", " << vec2.y << "]";
		return  os;
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

		// Operator overloading
		friend std::ostream& operator<<(std::ostream os, const Vector3& vec3);
	};
	// Member functions
	inline const std::string& Vector3::ToString() const
	{
		return "[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "]";
	}

	// Operator overloading
	inline std::ostream& operator<<(std::ostream os, const Vector3& vec3)
	{
		os << "[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
		return  os;
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