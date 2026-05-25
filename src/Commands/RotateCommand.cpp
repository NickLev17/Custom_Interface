#include "../../include/Commands/RotateCommand.h"
RotateCommand::RotateCommand(std::unique_ptr<IRotatingObject> obj) : _obj(std::move(obj))
{
        std::cout << " Constructor Rotate ";
}


void RotateCommand::execute()
{
        _obj->setDirection((_obj->getDirection() + _obj->getAngularVelocity()) % _obj->getDirectionsNumber());
       
}