#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bounding_box_t bounding_box();
    void tick();
    int power;
    double speed;
    float delta;
    float mastheight;
    float mastthickness;
    float yaccel;
    float yvelocity;
    float zautovelocity;
    float xautovelocity;
    int countTime;
private:
    VAO *frame_bottom;
    VAO *frame_sides;
    VAO *frame_borders;
    VAO *frame_mast;
    VAO *frame_sail;
    VAO *frame_cannons;
};

#endif // BOAT_H
