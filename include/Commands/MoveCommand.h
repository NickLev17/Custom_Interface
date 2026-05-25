#include <memory>
#include <iostream>
#include "../Interfaces/ICommand.h"
#include "../Interfaces/IMovingObject.h"
class MoveCommand : public ICommand
{
    std::unique_ptr<IMovingObject> _obj;

public:
    explicit MoveCommand(std::unique_ptr<IMovingObject> obj);
    

    void execute();
    
};