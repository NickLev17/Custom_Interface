#include <iostream>
#include <vector>
#include <math.h>
#include <memory>

using namespace std;

struct Point
{
    double _x, _y;

    Point(double x = 0, double y = 0) : _x(x), _y(y)
    {
    }

    Point moveTo(vector<Point> velocity)
    {
        const Point &lastVelocity = velocity.back();
        return Point(_x + lastVelocity._x, _y + lastVelocity._y);
    }

    double norm() const
    {
        return sqrt(_x * _x + _y * _y);
    }

    double distance(const Point &other)
    {
        double dx = _x - other._x;
        double dy = _y - other._y;
        return sqrt(dx * dx + dy * dy);
    }
};

class IMovingObject
{
public:
    virtual ~IMovingObject() = default;
    virtual Point getPosition() const = 0;
    virtual void setPosition(Point newPos) = 0;
    virtual vector<Point> getVelocity() const = 0;
};

class IRotatingObject
{
public:
    virtual ~IRotatingObject() = default;
    virtual int getDirection() const = 0;
    virtual int getAngularVelocity() const = 0;
    virtual void setDirection(int newV) = 0;
    virtual int getDirectionsNumber() const = 0;
};

class Rotate
{
    std::unique_ptr<IRotatingObject> _obj;

public:
    explicit Rotate(std::unique_ptr<IRotatingObject> obj) : _obj(std::move(obj))
    {
        cout << " Constructor Rotate ";
    }

    void execute()
    {
        _obj->setDirection((_obj->getDirection() + _obj->getAngularVelocity()) % _obj->getDirectionsNumber());
    }
};

class SpaceShip : public IMovingObject, public IRotatingObject
{
    Point _position;
    vector<Point> _velocity;
    int _direction;
    int _angularVelocity;
    int _directionNumber;

public:
    SpaceShip(Point pos, vector<Point> v, int angularVelocity, int directionNumber, int direction) : _position(pos), _velocity(v), _angularVelocity(angularVelocity),
                                                                                                     _directionNumber(directionNumber)
    {
        _direction = (direction + _angularVelocity) % directionNumber;
      
    }

    void setPosition(Point newPos) override
    {
        _position._x = newPos._x;
        _position._y = newPos._y;
    }
    Point getPosition() const override
    {
        return _position;
    }

    vector<Point> getVelocity() const override
    {
        return _velocity;
    }

    int getDirection() const override
    {
        return _direction;
    }

    int getAngularVelocity() const override
    {
        return _angularVelocity;
    }

    int getDirectionsNumber() const override
    {
        return _directionNumber;
    }

    void setDirection(int newV) override
    {
        _direction = newV;
    }
};

class Move
{
    std::unique_ptr<IMovingObject> _obj;

public:
    explicit Move(std::unique_ptr<IMovingObject> obj) : _obj(std::move(obj))
    {

        cout << " Constructor Move " << _obj->getPosition()._x << " " << _obj->getPosition()._y << "\n";
    }

    void execute()
    {
        _obj->setPosition(_obj->getPosition().moveTo(_obj->getVelocity()));
        std::cout << " Execute " << _obj->getPosition()._x << " " << _obj->getPosition()._y << "\n";
    }
};

template<typename T>
 class UObject
{
std::unordered_map<string,T*> _properties;
 public:
T* getProperty(const string& key)
{
     auto it = _properties.find(key);
        if (it != _properties.end())
        return it->second;
            //return it->second.get();
        return nullptr;
}
void setProperty(const string& key, T* newValue)
{
    if((newValue!=nullptr)&&(!key.empty()))
    {
   _properties.emplace(key, newValue);
    
}
}
};


class MovableAdapter : public IMovingObject
{
    UObject <std::any*> _obj;
    public:
  MovableAdapter(UObject<std::any> otherObject)
    {
_obj=otherObject;
    }

    Point getPosition()
    {
  return Point(*std::any_cast<std::vector<Point>>(_obj.getProperty("Position")));
   }

 void setPosition(vector<Point> newVec)
 {
_obj.setProperty("Position",newVec);
 }

 vector<Point> getVeclocity()
 {
   int d = std::any_cast<int>(_obj.getProperty("Direction"));
   int n = std::any_cast<int>(_obj.getProperty("DirectionNumber"));
   int v= std::any_cast<int>(_obj.getProperty("Veclocity"));

    return vector<Point>(v*cos(double(d)/(360*n)),v*sin(double(d)/(360*n)));
 }
};


int main()
{
    std::vector<Point> vec{
        Point(-7, 3),
    };
    std::unique_ptr<IMovingObject> basePtr = std::make_unique<SpaceShip>(
        Point(12, 5), // Позиция
        vec,          // Вектор скорости 
        30,           // угловая скорость
        30,           // номер направления
        5             // направление
    );

   
    Move myMove(std::move(basePtr));
    myMove.execute();

    std::unique_ptr<IRotatingObject> basePtr_2 = std::make_unique<SpaceShip>(
        Point(12, 5), // Позиция
        vec,          // Вектор скорости 
        30,           // угловая скорость
        30,           // номер направления
        5             // направление
    );
    Rotate myRotate(std::move(basePtr_2));
    myRotate.execute();

    return 0;
}
