#include <stdio.h>


enum MapDirection{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

void MapDirection_toString(enum MapDirection direction){
    switch (direction){
        case NORTH:
            printf("Północ");
            break;
        case EAST:
            printf("Wschód");
            break;
        case SOUTH:
            printf("Połudień");
            break;
        case WEST:
            printf("Zachód");
            break;
    }
}

enum MapDirection MapDirection_next(enum MapDirection direction){
    switch (direction){
        case NORTH:
            return EAST;
        case EAST:
            return SOUTH;
        case SOUTH:
            return WEST;
        case WEST:
            return NORTH;
}

}
enum MapDirection MapDirection_previous(enum MapDirection direction){
    int result = ((int)direction - 1) % 4;
    if (result<0){
        result += 4;
    }
    return result;
}

int main(){
    enum MapDirection direction = NORTH;
    direction = MapDirection_previous(direction);
    printf("%d", direction);
    printf("\n");
    enum MapDirection result = WEST;
    MapDirection_toString(result);
    printf("\n");


    return 0;

}