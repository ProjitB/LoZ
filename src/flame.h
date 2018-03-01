#include "main.h"

#ifndef FLAME_H
#define FLAME_H


class Flame {
public:
    Flame() {}
    Flame(float x, float y, float z, float size, float angle, float velocity, float yvelocity, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
    float yvelocity;
    float zvelocity;
    float xvelocity;
    float yaccel;
    float velocity;
    float angle;
    float size;
    int damage;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // FLAME_H
