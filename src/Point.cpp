#include "../include/Point.h"
Point::Point(double x, double y) : _x(x), _y(y)
{
}

Point Point::moveTo(vector<Point> velocity)
{
        const Point &lastVelocity = velocity.back();
        return Point(_x + lastVelocity._x, _y + lastVelocity._y);
}

double Point::norm() const
{
        return sqrt(_x * _x + _y * _y);
}

double Point::distance(const Point &other)
{
        double dx = _x - other._x;
        double dy = _y - other._y;
        return sqrt(dx * dx + dy * dy);
}

bool operator==(const Point& lhs, const Point& rhs) 
{
    
    return (lhs._x == rhs._x) && (lhs._y == rhs._y);
}