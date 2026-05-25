#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <math.h>

using namespace std;
struct Point
{
    double _x, _y;

    Point(double x = 0, double y = 0);
   

    Point moveTo(vector<Point> velocity);
  
    double norm() const;

    double distance(const Point &other);
};
bool operator==(const Point& lhs, const Point& rhs);
