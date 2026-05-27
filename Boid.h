#include <vector>
#include <iostream>
#include <cmath>

class Vector2
{
public:
    double x, y;

    Vector2(double x_, double y_);
    Vector2 operator+(const Vector2 & other) const;
    Vector2 operator-(const Vector2 & other) const;
    Vector2 operator*(const double n) const;
    Vector2 operator/(const double n) const;
    void Clamped(double length);
    void Modulo(double length);
    void Flip();
    void Inverse(double r);
    double Distance(const Vector2 & other);
    Vector2 DistanceVector(const Vector2 & other, double world_size);
};

class Boid
{
public:
    // values between -1 and 1
    Vector2 velocity;
    // values between -1 and 1
    Vector2 acceleration;
    // values between 0 and 10
    Vector2 pos;
    // radius for flock mates
    static double r;

    Boid(Vector2 pos_, Vector2 velocity_, Vector2 acceleration_);
};

std::ostream & operator<<(std::ostream & out, const Vector2 & data);
std::ostream & operator<<(std::ostream & out, const Boid & data);