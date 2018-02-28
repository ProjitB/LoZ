#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // WATER_H
