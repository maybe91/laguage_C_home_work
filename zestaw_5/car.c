#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

enum MapDirection {
    NORTH,
    EAST,
    SOUTH,
    WEST
};


struct Vector {
    int x;
    int y;
};


struct Car {
    enum MapDirection orientation;
    struct Vector position;
};


enum MoveDirection {
    FORWARD,
    RIGHT,
    BACKWARD,
    LEFT
};


struct Car createCar(int x, int y) {
    struct Car car;
    car.orientation = NORTH;
    car.position.x = x;
    car.position.y = y;
    return car;
}


void Car_toString(struct Car car) {
    const char *direction;
    switch (car.orientation) {
        case NORTH:
            direction = "NORTH";
            break;
        case EAST:
            direction = "EAST";
            break;
        case SOUTH:
            direction = "SOUTH";
            break;
        case WEST:
            direction = "WEST";
            break;
        default:
            direction = "UNKNOWN";
            break;
    }
    printf("Car direction: %s, car position: (%d, %d)\n", direction, car.position.x, car.position.y);
}


bool Car_isAt(struct Car car, struct Vector position) {
    return (car.position.x == position.x) && (car.position.y == position.y);
}


void Car_move(struct Car *car, enum MoveDirection direction) {
    int MapHeight = 5;
    int MapWidth = 5;

    struct Vector PreviousPosition = car->position;

    switch (direction) {
        case FORWARD:
            switch (car->orientation) {
                case NORTH:
                    car->position.y += 1;
                    break;
                case EAST:
                    car->position.x += 1;
                    break;
                case SOUTH:
                    car->position.y -= 1;
                    break;
                case WEST:
                    car->position.x -= 1;
                    break;
            }
            break;
        case RIGHT:
            car->orientation = (car->orientation + 1) % 4;
            break;
        case BACKWARD:
            switch (car->orientation) {
                case NORTH:
                    car->position.y -= 1;
                    break;
                case EAST:
                    car->position.x -= 1;
                    break;
                case SOUTH:
                    car->position.y += 1;
                    break;
                case WEST:
                    car->position.x += 1;
                    break;
            }
            break;
        case LEFT:
            car->orientation = (car->orientation - 1 + 4) % 4;
            break;
    }
    if(car->position.x < 0 || car->position.y < 0 || car->position.x == MapWidth || car->position.y == MapHeight){
        car->position = PreviousPosition;
        car->orientation = (car->orientation + 2) % 4;
    }
}

int main() {
    struct Car myCar = createCar(0, 0);
    Car_toString(myCar);

    struct Vector position = {0, 1};

    assert(Car_isAt(myCar, position) == false);
    printf("Test is passed\n");


    Car_move(&myCar, FORWARD);
    assert(myCar.position.x == 0 && myCar.position.y == 1);
    assert(myCar.orientation == NORTH);
    printf("Move FORWARD test passed\n");

    Car_move(&myCar, LEFT);
    assert(myCar.orientation == WEST);
    printf("Turn LEFT test passed\n");

    Car_move(&myCar, BACKWARD);
    assert(myCar.position.x == 1 && myCar.position.y == 1);
    printf("Turn BACKWARD test passed\n");

    Car_move(&myCar, RIGHT);
    assert(myCar.orientation == NORTH);
    printf("Turn RIGHT test passed\n");


    return 0;
}
