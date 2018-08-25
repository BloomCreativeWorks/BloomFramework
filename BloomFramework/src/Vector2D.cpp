#include "../inc/Vector2D.h"

BloomFramework::Vector2D::Vector2D() { x = y = 0.0f; }

BloomFramework::Vector2D::Vector2D(float x, float y) { this->x = x; this->y = y; }

BloomFramework::Vector2D & BloomFramework::Vector2D::add(const Vector2D & vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

BloomFramework::Vector2D & BloomFramework::Vector2D::subtract(const Vector2D & vec) {
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

BloomFramework::Vector2D & BloomFramework::Vector2D::multiply(const Vector2D & vec) {
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

BloomFramework::Vector2D & BloomFramework::Vector2D::divide(const Vector2D & vec) {
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

BloomFramework::Vector2D & BloomFramework::operator+(Vector2D & v1, const Vector2D v2) { return v1.add(v2); }

BloomFramework::Vector2D & BloomFramework::operator-(Vector2D & v1, const Vector2D v2) { return v1.subtract(v2); }

BloomFramework::Vector2D & BloomFramework::operator*(Vector2D & v1, const Vector2D v2) { return v1.multiply(v2); }

BloomFramework::Vector2D & BloomFramework::operator/(Vector2D & v1, const Vector2D v2) { return v1.divide(v2); }

BloomFramework::Vector2D & BloomFramework::Vector2D::operator+=(const Vector2D vec) { return this->add(vec); }

BloomFramework::Vector2D & BloomFramework::Vector2D::operator-=(const Vector2D vec) { return this->subtract(vec); }

BloomFramework::Vector2D & BloomFramework::Vector2D::operator*=(const Vector2D vec) { return this->multiply(vec); }

BloomFramework::Vector2D & BloomFramework::Vector2D::operator/=(const Vector2D vec) { return this->divide(vec); }

std::ostream & BloomFramework::operator<<(std::ostream stream, const Vector2D & vec) {
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}
