#include "water.h"
#include "main.h"

Water::Water(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        -100.0f, 0.0f,-100.0f, // triangle 1 : begin
        -100.0f, 0.0f, 100.0f,
         100.0f, 0.0f, 100.0f, // triangle 1 : end
        -100.0f, 0.0f,-100.0f,
         100.0f, 0.0f, 100.0f,
        100.0f, 0.0f, -100.0f
    };
    this->size = 100.0f;

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Water::tick() {
  ;
}

