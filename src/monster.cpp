#include "monster.h"
#include "main.h"

Monster::Monster(float x, float y, float z, float size, int health) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->size = size;
    this->health = health;
    this->counter = 0;
    this->countTime = 200;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_main_body[] = {
      -1*size,-2*size,-1*size, // triangle 1 : begin
        -1*size,-2*size, size,
        -1*size, 2*size, size, // triangle 1 : end
        size, 2*size,-1*size, // triangle 2 : begin
        -1*size,-2*size,-1*size,
        -1*size, 2*size,-1*size, // triangle 2 : end
        size,-2*size, size,
        -1*size,-2*size,-1*size,
        size,-2*size,-1*size,
        size, 2*size,-1*size,
        size,-2*size,-1*size,
        -1*size,-2*size,-1*size,
        -1*size,-2*size,-1*size,
        -1*size, 2*size, size,
        -1*size, 2*size,-1*size,
        size,-2*size, size,
        -1*size,-2*size, size,
        -1*size,-2*size,-1*size,
        -1*size, 2*size, size,
        -1*size,-2*size, size,
        size,-2*size, size,
        size, 2*size, size,
        size,-2*size,-1*size,
        size, 2*size,-1*size,
        size,-2*size,-1*size,
        size, 2*size, size,
        size,-2*size, size,
        size, 2*size, size,
        size, 2*size,-1*size,
        -1*size, 2*size,-1*size,
        size, 2*size, size,
        -1*size, 2*size,-1*size,
        -1*size, 2*size, size,
        size, 2*size, size,
        -1*size, 2*size, size,
        size,-2*size, size
    };

    this->main_body = create3DObject(GL_TRIANGLES, 12*3, vertex_main_body, COLOR_GREEN, GL_FILL);

    static const GLfloat vertex_face[] = {
      size/2+size/6, 1.6*size, size+0.001f,
      size/2-size/6, 1.6*size, size+0.001f,
      size/2, 1.4*size, size+0.001f,

      -1*size/2-size/6, 1.6*size, size+0.001f,
      -1*size/2+size/6, 1.6*size, size+0.001f,
      -1*size/2, 1.4*size, size,

      size/2, 0.6*size, size+0.001f,
      -1*size/2, 0.6*size, size+0.001f,
      0.0f, 0.2*size, size+0.001f
    };
    this->face = create3DObject(GL_TRIANGLES, 3*3, vertex_face, COLOR_YELLOW, GL_FILL);    
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->main_body);
    draw3DObject(this->face);
}

void Monster::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Monster::tick() {
  this->position.x += -0.03 + static_cast<float> (rand()) / (static_cast <float> (RAND_MAX/(0.06)));
  this->position.z += -0.03 + static_cast<float> (rand()) / (static_cast <float> (RAND_MAX/(0.06)));
  if(this->counter < this->countTime) this->counter++;
}

bounding_box_t Monster::bounding_box() {
  bounding_box_t bbox = {this->position.x, this->position.y, this->position.z, this->size, this->size, 2*this->size};
  return bbox;
}
