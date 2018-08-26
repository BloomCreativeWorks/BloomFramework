#pragma once

#include "stdIncludes.h"
#include <iostream>

namespace BloomFramework {
	class BLOOMFRAMEWORK_API Vector2D {
	public:
		Vector2D();
		Vector2D(float x, float y);

		Vector2D& add(const Vector2D& vec);
		Vector2D& subtract(const Vector2D& vec);
		Vector2D& multiply(const Vector2D& vec);
		Vector2D& divide(const Vector2D& vec);

		friend Vector2D& operator+(Vector2D& v1, const Vector2D v2);
		friend Vector2D& operator-(Vector2D& v1, const Vector2D v2);
		friend Vector2D& operator*(Vector2D& v1, const Vector2D v2);
		friend Vector2D& operator/(Vector2D& v1, const Vector2D v2);

		Vector2D& operator+=(const Vector2D vec);
		Vector2D& operator-=(const Vector2D vec);
		Vector2D& operator*=(const Vector2D vec);
		Vector2D& operator/=(const Vector2D vec);

		friend std::ostream& operator<<(std::ostream stream, const Vector2D& vec);

		float x, y;
	};
}