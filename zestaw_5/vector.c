#include "stdio.h"
#include "math.h"
#include "stdbool.h"
#include "assert.h"

struct Vector {
    int x;
    int y;
};

void Vector_toString(struct Vector vector) {
    printf("(%d, %d)", vector.x, vector.y);
}

bool Vector_precedes(struct Vector vector1, struct Vector vector2) {
    return (vector1.x <= vector2.x) && (vector1.y <= vector2.y);
}

bool Vector_follows(struct Vector vector1, struct Vector vector2) {
    return (vector1.x >= vector2.x) && (vector1.y >= vector2.y);
}

struct Vector Vector_add(struct Vector vector1, struct Vector vector2) {
    struct Vector result = {vector1.x + vector2.x, vector1.y + vector2.y};
    return result;
}

struct Vector Vector_subtract(struct Vector vector1, struct Vector vector2) {
    struct Vector result = {vector1.x - vector2.x, vector1.y - vector2.y};
    return result;
}

struct Vector Vector_upperRight(struct Vector vector1, struct Vector vector2) {
    int x = fmax(vector1.x, vector2.x);
    int y = fmax(vector1.y, vector2.y);
    struct Vector result = {x, y};
    return result;
}

struct Vector Vector_lowerLeft(struct Vector vector1, struct Vector vector2) {
    int x = fmin(vector1.x, vector2.x);
    int y = fmin(vector1.y, vector2.y);
    struct Vector result = {x, y};
    return result;
}

struct Vector Vector_opposite(struct Vector vector) {
    int x = -vector.x;
    int y = -vector.y;
    struct Vector result = {x, y};
    return result;
}

bool Vector_equals(struct Vector vector1, struct Vector vector2) {
    return (vector1.x == vector2.x) && (vector1.y == vector2.y);
}

int main() {
    struct Vector v1 = {2, 3};
    struct Vector v2 = {3, 4};

    assert(Vector_precedes(v1, v2) == true);
    assert(Vector_follows(v2, v1) == true);

    struct Vector add_result = Vector_add(v2, v1);
    assert(add_result.x == 5 && add_result.y == 7);

    struct Vector subtract_result = Vector_subtract(v2, v1);
    assert(subtract_result.x == 1 && subtract_result.y == 1);

    struct Vector upper_right_result = Vector_upperRight(v2, v1);
    assert(upper_right_result.x == 3 && upper_right_result.y == 4);

    struct Vector lower_left_result = Vector_lowerLeft(v1, v2);
    assert(lower_left_result.x == 2 && lower_left_result.y == 3);

    struct Vector opposite_result = Vector_opposite(v2);
    assert(opposite_result.x == -3 && opposite_result.y == -4);

    assert(Vector_equals(v1, v2) == false);

    printf("All tests passed.\n");

    return 0;
}
