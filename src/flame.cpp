#include "flame.h"
#include "main.h"

Flame::Flame(float x, float y, float z, float size, float angle, float velocity, float yvelocity, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->velocity = velocity;
    this->angle = angle;
    this->rotation = 0;
    this->size = size;
    this->yvelocity = yvelocity;
    this->xvelocity = 0;
    this->zvelocity = 0;
    this->yaccel = -0.01;
    speed = 1;
    this->damage = 50;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f*size,-1.0f*size,-1.0f*size, // triangle 1 : begin
        -1.0f*size,-1.0f*size, 1.0f*size,
        -1.0f*size, 1.0f*size, 1.0f*size, // triangle 1 : end
        1.0f*size, 1.0f*size,-1.0f*size, // triangle 2 : begin
        -1.0f*size,-1.0f*size,-1.0f*size,
        -1.0f*size, 1.0f*size,-1.0f*size, // triangle 2 : end
        1.0f*size,-1.0f*size, 1.0f*size,
        -1.0f*size,-1.0f*size,-1.0f*size,
        1.0f*size,-1.0f*size,-1.0f*size,
        1.0f*size, 1.0f*size,-1.0f*size,
        1.0f*size,-1.0f*size,-1.0f*size,
        -1.0f*size,-1.0f*size,-1.0f*size,
        -1.0f*size,-1.0f*size,-1.0f*size,
        -1.0f*size, 1.0f*size, 1.0f*size,
        -1.0f*size, 1.0f*size,-1.0f*size,
        1.0f*size,-1.0f*size, 1.0f*size,
        -1.0f*size,-1.0f*size, 1.0f*size,
        -1.0f*size,-1.0f*size,-1.0f*size,
        -1.0f*size, 1.0f*size, 1.0f*size,
        -1.0f*size,-1.0f*size, 1.0f*size,
        1.0f*size,-1.0f*size, 1.0f*size,
        1.0f*size, 1.0f*size, 1.0f*size,
        1.0f*size,-1.0f*size,-1.0f*size,
        1.0f*size, 1.0f*size,-1.0f*size,
        1.0f*size,-1.0f*size,-1.0f*size,
        1.0f*size, 1.0f*size, 1.0f*size,
        1.0f*size,-1.0f*size, 1.0f*size,
        1.0f*size, 1.0f*size, 1.0f*size,
        1.0f*size, 1.0f*size,-1.0f*size,
        -1.0f*size, 1.0f*size,-1.0f*size,
        1.0f*size, 1.0f*size, 1.0f*size,
        -1.0f*size, 1.0f*size,-1.0f*size,
        -1.0f*size, 1.0f*size, 1.0f*size,
        1.0f*size, 1.0f*size, 1.0f*size,
        -1.0f*size, 1.0f*size, 1.0f*size,
        1.0f*size,-1.0f*size, 1.0f*size
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Flame::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Flame::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Flame::tick() {
  float LO = -0.1;
  float HI = 0.1;
  this->position.x += this->velocity * sin(this->angle);
  this->position.z += this->velocity * cos(this->angle) * -1;
  this->position.y += this->yvelocity;
  this->yvelocity += this->yaccel;
  this->position.x += this->xvelocity;
  this->position.z += this->zvelocity;
}

bounding_box_t Flame::bounding_box() {
  bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, this->size, this->size, this->size};
  return bbox;
}
