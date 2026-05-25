#include <memory>
#include <iostream>
#include "../Interfaces/ICommand.h"
#include "../Interfaces/IRotatingObject.h"
class RotateCommand : public ICommand
{
    std::unique_ptr<IRotatingObject> _obj;

public:
    explicit RotateCommand(std::unique_ptr<IRotatingObject> obj) ;
    

    void execute();
    
};