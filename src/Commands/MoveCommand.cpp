#include "../../include/Commands/MoveCommand.h"

MoveCommand::MoveCommand(std::unique_ptr<IMovingObject> obj) : _obj(std::move(obj))
{

        std::cout << " Constructor Move " << _obj->getPosition()._x << " " << _obj->getPosition()._y << "\n";
}

void MoveCommand::execute()
{
        _obj->setPosition(_obj->getPosition().moveTo(_obj->getVelocity()));
        std::cout << " Execute " << _obj->getPosition()._x << " " << _obj->getPosition()._y << "\n";
}
