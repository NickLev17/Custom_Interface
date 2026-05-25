#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <gtest/gtest.h>
#include <math.h>
#include <gmock/gmock.h>
#include "../include/Interfaces/IMovingObject.h"

using ::testing::Return;
using ::testing::_;
using namespace testing; 

using namespace std;



class MockMovingObject : public IMovingObject {
public:
    MOCK_CONST_METHOD0(getPosition, Point());
    MOCK_METHOD1(setPosition, void(Point newPos));
    MOCK_CONST_METHOD0(getVelocity, std::vector<Point>());
};



TEST(MovingObjectTest, ChangeLocation) {
    MockMovingObject mockObj;

   
    Point coord{12, 5};     
    Point expected{5, 8};  

    EXPECT_CALL(mockObj, getPosition())
        .WillOnce(testing::Return(expected));

    EXPECT_CALL(mockObj, setPosition(coord));

    mockObj.setPosition(coord);

    EXPECT_EQ(mockObj.getPosition(), expected);
}

TEST(MovingObjectTest, ShiftFailsWhenPositionReadFails) {
    MockMovingObject mockObj;

    EXPECT_CALL(mockObj, getPosition())
        .WillOnce(Throw(std::runtime_error("Ошибка чтения координат")));

    EXPECT_CALL(mockObj, setPosition(_))
        .Times(0);

    ASSERT_THROW(
        ([&mockObj]{
            struct Point current_pos = mockObj.getPosition();
            struct Point new_pos{current_pos._x + 10.0, current_pos._y + 5.0};
            mockObj.setPosition(new_pos);
        }()),
    std::runtime_error);
}

TEST(MovingObjectTest, ShiftFailsWhenVelocityReadFails) 
{
    MockMovingObject mockObj;

    EXPECT_CALL(mockObj, getVelocity())
        .WillOnce(testing::Throw(std::runtime_error("Ошибка чтения скорости")));


    EXPECT_CALL(mockObj, setPosition(_))
        .Times(0);

    ASSERT_THROW(
        ([&mockObj]{

            std::vector<Point> current_velocity = mockObj.getVelocity(); 

            const Point& speed_vector = current_velocity.back();

            struct Point current_pos = mockObj.getPosition();

            struct Point new_pos{current_pos._x + speed_vector._x, current_pos._y + speed_vector._y};
            mockObj.setPosition(new_pos);

        }()),
    std::runtime_error);
}

TEST(MovingObjectTest, ShiftFailsWhenPositionChangeFails) 
{
    MockMovingObject mockObj;

    EXPECT_CALL(mockObj, getPosition())
        .WillOnce(testing::Return(Point{10.0, 20.0}));

    EXPECT_CALL(mockObj, getVelocity())
        .WillOnce(testing::Return(std::vector<Point>{Point{5.0, -3.0}}));

    EXPECT_CALL(mockObj, setPosition(_))
        .WillOnce(testing::Throw(std::runtime_error("Ошибка записи координат: привод заблокирован")));

    ASSERT_THROW(
        ([&mockObj]{
            std::vector<Point> current_velocity = mockObj.getVelocity();
            const Point& speed_vector = current_velocity.back();
            
            struct Point current_pos = mockObj.getPosition();
            
            struct Point new_pos{current_pos._x + speed_vector._x, current_pos._y + speed_vector._y};
            
            mockObj.setPosition(new_pos); 
        }()),
    std::runtime_error);
}












int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// g++ -std=c++17 main.cpp -lgtest -lgmock -lgtest_main -pthread -o test_run
// ./test_run