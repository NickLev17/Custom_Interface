#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <math.h>
#include "../Point.h"
class IMovingObject
{
public:
    virtual ~IMovingObject() = default;
    virtual Point getPosition() const = 0;
    virtual void setPosition(Point newPos) = 0;
    virtual vector<Point> getVelocity() const = 0;
};


