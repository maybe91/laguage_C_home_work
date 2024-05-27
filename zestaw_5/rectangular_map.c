#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAX_CARS 10
#define TABLE_SIZE 1000

struct RectangularMap {
    int Height;
    int Width;
};

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

bool isCollision(struct Car cars[], int carCount, struct Vector position, int excludeIndex) {
    for (int i = 0; i < carCount; i++) {
        if (i != excludeIndex && Car_isAt(cars[i], position)) {
            return true;
        }
    }
    return false;
}

bool isValidPosition(struct Vector position, struct RectangularMap map) {
    return position.x >= 0 && position.y >= 0 && position.x < map.Width && position.y < map.Height;
}

void Car_move(struct Car *car, enum MoveDirection direction, struct RectangularMap map, struct Car cars[], int carCount, int carIndex) {
    struct Vector newPosition = car->position;

    switch (direction) {
        case FORWARD:
            switch (car->orientation) {
                case NORTH:
                    newPosition.y += 1;
                    break;
                case EAST:
                    newPosition.x += 1;
                    break;
                case SOUTH:
                    newPosition.y -= 1;
                    break;
                case WEST:
                    newPosition.x -= 1;
                    break;
            }
            break;
        case RIGHT:
            car->orientation = (car->orientation + 1) % 4;
            break;
        case BACKWARD:
            switch (car->orientation) {
                case NORTH:
                    newPosition.y -= 1;
                    break;
                case EAST:
                    newPosition.x -= 1;
                    break;
                case SOUTH:
                    newPosition.y += 1;
                    break;
                case WEST:
                    newPosition.x += 1;
                    break;
            }
            break;
        case LEFT:
            car->orientation = (car->orientation - 1 + 4) % 4;
            break;
    }

    if (direction == FORWARD || direction == BACKWARD) {
        if (isValidPosition(newPosition, map) && !isCollision(cars, carCount, newPosition, carIndex)) {
            car->position = newPosition;
        } else {
            printf("Error: Collision detected or out of map bounds. Move reverted.\n");
        }
    }
}

bool addCar(struct Car cars[], int *carCount, int x, int y) {
    for (int i = 0; i < *carCount; i++) {
        if (Car_isAt(cars[i], (struct Vector){x, y})) {
            printf("Error: Duplicate coordinates entered.\n");
            return false;
        }
    }
    if (*carCount >= MAX_CARS) {
        printf("Maximum number of cars reached.\n");
        return false;
    }
    cars[*carCount] = createCar(x, y);
    (*carCount)++;
    return true;
}

enum MoveDirection charToMoveDirection(char c) {
    switch (c) {
        case 'f':
            return FORWARD;
        case 'b':
            return BACKWARD;
        case 'l':
            return LEFT;
        case 'r':
            return RIGHT;
        default:
            return -1;
    }
}

void test() {
    struct RectangularMap map = {10, 10};


    struct Car car1 = createCar(2, 3);
    assert(car1.position.x == 2);
    assert(car1.position.y == 3);
    assert(car1.orientation == NORTH);

    struct Car car2 = createCar(5, 5);
    assert(car2.position.x == 5);
    assert(car2.position.y == 5);
    assert(car2.orientation == NORTH);


    struct Car cars[MAX_CARS];
    int carCount = 0;

    assert(addCar(cars, &carCount, 2, 3) == true);
    assert(carCount == 1);
    assert(Car_isAt(cars[0], (struct Vector){2, 3}) == true);

    assert(addCar(cars, &carCount, 5, 5) == true);
    assert(carCount == 2);
    assert(Car_isAt(cars[1], (struct Vector){5, 5}) == true);

    assert(addCar(cars, &carCount, 2, 3) == false);


    Car_move(&cars[0], FORWARD, map, cars, carCount, 0);
    assert(cars[0].position.x == 2);
    assert(cars[0].position.y == 4);

    Car_move(&cars[0], RIGHT, map, cars, carCount, 0);
    assert(cars[0].orientation == EAST);

    Car_move(&cars[0], FORWARD, map, cars, carCount, 0);
    assert(cars[0].position.x == 3);
    assert(cars[0].position.y == 4);

    Car_move(&cars[0], BACKWARD, map, cars, carCount, 0);
    assert(cars[0].position.x == 2);
    assert(cars[0].position.y == 4);

    Car_move(&cars[0], LEFT, map, cars, carCount, 0);
    assert(cars[0].orientation == NORTH);


    Car_move(&cars[1], BACKWARD, map, cars, carCount, 1);
    Car_move(&cars[1], LEFT, map, cars, carCount, 1);
    Car_move(&cars[1], FORWARD, map, cars, carCount, 1);
    assert(cars[1].position.x == 4);
    assert(cars[1].position.y == 4);

    printf("All tests passed!\n");
}

int main() {

    test();


    struct RectangularMap map;
    printf("Enter the map dimensions in the format: Width Height\n");
    scanf("%d %d", &map.Width, &map.Height);

    struct Car cars[MAX_CARS];
    int carCount = 0;
    int numCars;

    printf("Enter the number of cars (maximum 10):\n");
    scanf("%d", &numCars);
    if (numCars > MAX_CARS) {
        printf("Error: The number of cars cannot exceed 10.\n");
        return 1;
    }

    while (true) {
        bool valid = true;
        carCount = 0;
        for (int i = 0; i < numCars; i++) {
            int x, y;
            printf("Enter the coordinates for car %d in the format: x y\n", i + 1);
            scanf("%d %d", &x, &y);
            if (x < 0 || x >= map.Width || y < 0 || y >= map.Height) {
                printf("Error: Car coordinates out of map bounds.\n");
                valid = false;
                break;
            }
            if (!addCar(cars, &carCount, x, y)) {
                valid = false;
                break;
            }
        }
        if (valid) break;
        else printf("Please re-enter the car coordinates.\n");
    }

    for (int i = 0; i < carCount; i++) {
        Car_toString(cars[i]);
    }

    getchar();

    while (true) {
        char commands[TABLE_SIZE];
        printf("Enter the commands separated by spaces (f for FORWARD, b for BACKWARD, l for LEFT, r for RIGHT, or 'exit' to quit):\n");
        fgets(commands, TABLE_SIZE, stdin);

        if (strncmp(commands, "exit", 4) == 0) {
            break;
        }

        char *command = strtok(commands, " \n");
        int currentCar = 0;

        while (command != NULL) {
            if (strlen(command) != 1) {
                printf("Error: Invalid command length '%s'. Commands must be single characters.\n", command);
                return 1;
            }
            enum MoveDirection direction = charToMoveDirection(command[0]);
            if (direction == -1) {
                printf("Error: Invalid command '%s' entered.\n", command);
                return 1;
            }
            Car_move(&cars[currentCar], direction, map, cars, carCount, currentCar);
            Car_toString(cars[currentCar]);
            command = strtok(NULL, " \n");
            currentCar = (currentCar + 1) % carCount;
        }
    }

    return 0;
}





