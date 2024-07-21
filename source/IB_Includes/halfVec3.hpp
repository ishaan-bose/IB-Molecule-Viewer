#pragma once
#include "raylib.h"
#include "raymath.h"
#include "raymath_operators.hpp"
#include "umHalf.h"

struct HalfVector3 {
    half x, y, z;

    HalfVector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    // Conversion from Vector3 to HalfVector3
    HalfVector3& operator=(const Vector3& vec) {
        x = half(vec.x);
        y = half(vec.y);
        z = half(vec.z);
        return *this;
    }

    HalfVector3& operator=(const HalfVector3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }

    // Conversion from HalfVector3 to Vector3
    operator Vector3() const {
        return Vector3(float(x), float(y), float(z));
    }

    // Addition operator
    HalfVector3 operator+(const HalfVector3& other) const {
        return HalfVector3(static_cast<float>(x + other.x), static_cast<float>(y + other.y), static_cast<float>(z + other.z));
    }

    // Subtraction operator
    HalfVector3 operator-(const HalfVector3& other) const {
        return HalfVector3(static_cast<float>(x - other.x), static_cast<float>(y - other.y), static_cast<float>(z - other.z));
    }

    // Scalar multiplication
    HalfVector3 operator*(const half& scalar) const {
        return HalfVector3(static_cast<float>(x * scalar), static_cast<float>(y * scalar), static_cast<float>(z * scalar));
    }

    // Scalar division
    HalfVector3 operator/(const half& scalar) const {
        return HalfVector3(static_cast<float>(x / scalar), static_cast<float>(y / scalar), static_cast<float>(z / scalar));
    }

    // Equals operator
    bool operator==(const HalfVector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // Not equals operator
    bool operator!=(const HalfVector3& other) const {
        return !(*this == other);
    }

    // Dot product function
    half hDot(const HalfVector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
};

// Typedef for HalfVector3
typedef HalfVector3 hVec3;