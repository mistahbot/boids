#include "Boid.h"
#include <utility>

Vector2::Vector2(double x_, double y_) : x(x_), y(y_) {}
Vector2 Vector2::operator+(const Vector2 &other) const
{
    return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator-(const Vector2 &other) const
{
    return Vector2(x - other.x, y - other.y);
}
Vector2 Vector2::operator*(const double other) const
{
    return Vector2(x * other, y * other);
}
Vector2 Vector2::operator/(const double other) const
{
    if (other == 0)
        return Vector2(x, y);
    return Vector2(x / other, y / other);
}
void Vector2::Clamped(double length)
{
    if (x * x + y * y < length * length)
        return;

    double c = sqrt((x * x + y * y) / length / length);
    x /= c;
    y /= c;
}
void Vector2::Modulo(double length)
{
    while (x < 0)
        x += length;
    while (x >= length)
        x -= length;
    while (y < 0)
        y += length;
    while (y >= length)
        y -= length;
}
void Vector2::Flip()
{
    x = -x;
    y = -y;
}
void Vector2::Inverse(double r)
{
    double magnitude = this->Distance(Vector2(0, 0));
    magnitude = (1 - magnitude / r);
    (*this) = (*this) * magnitude;
}
double Vector2::Distance(const Vector2 &other)
{
    double dist_x = other.x - x;
    double dist_y = other.y - y;
    if (dist_x > 5)
        dist_x = dist_x - 10;
    if (dist_x < -5)
        dist_x = dist_x + 10;
    if (dist_y > 5)
        dist_y = dist_y - 10;
    if (dist_y < -5)
        dist_y = dist_y + 10;

    return sqrt(dist_x * dist_x + dist_y * dist_y);
}
Vector2 Vector2::DistanceVector(const Vector2 &other, double world_size)
{
    double dist_x = other.x - x;
    double dist_y = other.y - y;
    if (dist_x > 5)
        dist_x = dist_x - 10;
    if (dist_x < -5)
        dist_x = dist_x + 10;
    if (dist_y > 5)
        dist_y = dist_y - 10;
    if (dist_y < -5)
        dist_y = dist_y + 10;

    return Vector2(dist_x, dist_y);
}
std::ostream &operator<<(std::ostream &out, const Vector2 &data)
{
    out << data.x << ' ' << data.y;
    return out;
}

double Boid::r = 0.0;
Boid::Boid(Vector2 pos_, Vector2 velocity_, Vector2 acceleration_) : pos(pos_), velocity(velocity_), acceleration(acceleration_) {}
std::ostream &operator<<(std::ostream &out, const Boid &data)
{
    out << data.pos << ' ' << data.velocity << ' ' << data.acceleration;
    return out;
}