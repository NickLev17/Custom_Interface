class IRotatingObject
{
public:
    virtual ~IRotatingObject() = default;
    virtual int getDirection() const = 0;
    virtual int getAngularVelocity() const = 0;
    virtual void setDirection(int newV) = 0;
    virtual int getDirectionsNumber() const = 0;
};
