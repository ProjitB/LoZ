#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->countTime = 40;
    speed = 0.2;
    power = 10;
    delta = 0.01;
    yvelocity = 0;
    xautovelocity = 0;
    zautovelocity = 0;
    yaccel = -0.01;
    static const GLfloat vertex_main_frame_borders[] = {
      //Right bottom
      0.5f-delta/2, 0.0f, -1.0f,
      0.5f-delta/2, 0.0f, 1.0f,
      0.5f+delta/2, 0.0f, 1.0f,
      0.5f-delta/2, 0.0f, -1.0f,
      0.5f+delta/2, 0.0f, 1.0f,
      0.5f+delta/2, 0.0f, -1.0f,
      //Left bottom
      -0.5f+delta/2, 0.0f, -1.0f,
      -0.5f+delta/2, 0.0f, 1.0f,
      -0.5f-delta/2, 0.0f, 1.0f,
      -0.5f+delta/2, 0.0f, -1.0f,
      -0.5f-delta/2, 0.0f, 1.0f,
      -0.5f-delta/2, 0.0f, -1.0f,
      //Right top slant
      0.5f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.5f,
      0.0f, 0.0f, -1.5f+delta,
      0.5f-delta, 0.0f, -1.0f,
      0.5f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.5f+delta,
      //Left top slant
      -0.5f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.5f,
      0.0f, 0.0f, -1.5f+delta,
      -0.5f+delta, 0.0f, -1.0f,
      -0.5f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.5f+delta,
      //Front Slant
      0.0f+delta, 0.0f, -1.5f+delta/2,
      0.0f-delta, 0.75f, -1.75f+delta/2,
      0.0f-delta, 0.0f, -1.5f+delta/2,
      0.0f+delta, 0.75f, -1.75f+delta/2,
      0.0f-delta, 0.75f, -1.75f+delta/2,
      0.0f+delta, 0.0f, -1.5f+delta/2,
      //Right Front Slant
      0.5f, 0.0f, -1.0f,
      0.75f, 0.75f, -1.0f,
      0.75f-delta/2, 0.75f, -1.0f,
      0.5f-delta/2, 0.0f, -1.0f,
      0.5f, 0.0f, -1.0f,
      0.75f-delta/2, 0.75f, -1.0f,
      //Left Front Slant
      -0.5f, 0.0f, -1.0f,
      -0.75f, 0.75f, -1.0f,
      -0.75f+delta/2, 0.75f, -1.0f,
      -0.5f+delta/2, 0.0f, -1.0f,
      -0.5f, 0.0f, -1.0f,
      -0.75f+delta/2, 0.75f, -1.0f,
      //Right Bottom slant
      0.5f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.5f,
      0.0f, 0.0f, 1.5f-delta,
      0.5f-delta, 0.0f, 1.0f,
      0.5f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.5f-delta,
      //Left Bottom slant
      -0.5f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.5f,
      0.0f, 0.0f, 1.5f-delta,
      -0.5f+delta, 0.0f, 1.0f,
      -0.5f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.5f-delta,
      //Back Slant
      0.0f+delta, 0.0f, 1.5f-delta/2,
      0.0f-delta, 0.75f, 1.75f-delta/2,
      0.0f-delta, 0.0f, 1.5f-delta/2,
      0.0f+delta, 0.75f, 1.75f-delta/2,
      0.0f-delta, 0.75f, 1.75f-delta/2,
      0.0f+delta, 0.0f, 1.5f-delta/2,
      //Right Back Slant
      0.5f, 0.0f, 1.0f,
      0.75f, 0.75f, 1.0f,
      0.75f-delta/2, 0.75f, 1.0f,
      0.5f-delta/2, 0.0f, 1.0f,
      0.5f, 0.0f, 1.0f,
      0.75f-delta/2, 0.75f, 1.0f,
      //Left Back Slant
      -0.5f, 0.0f, 1.0f,
      -0.75f, 0.75f, 1.0f,
      -0.75f+delta/2, 0.75f, 1.0f,
      -0.5f+delta/2, 0.0f, 1.0f,
      -0.5f, 0.0f, 1.0f,
      -0.75f+delta/2, 0.75f, 1.0f
    };
    this->frame_borders = create3DObject(GL_TRIANGLES, 24*3, vertex_main_frame_borders, COLOR_BLACK, GL_FILL);
    
    static const GLfloat vertex_main_frame_bottom[] = {
      //Bottom Rectangle
      0.5f, 0.01f, -1.0f,
      0.5f, 0.01f, 1.0f,
      -0.5f, 0.01f, 1.0f,
      0.5f, 0.01f, -1.0f,
      -0.5f, 0.01f, 1.0f,
      -0.5f, 0.01f, -1.0f,
      //Triangles on both ends
      0.5f, 0.01f, -1.0f,
      -0.5f, 0.01f, -1.0f,
      0.0f, 0.01f, -1.5f,
      0.5f, 0.01f, 1.0f,
      -0.5f, 0.01f, 1.0f,
      0.0f, 0.01f, 1.5f
    };
    this->frame_bottom = create3DObject(GL_TRIANGLES, 4*3, vertex_main_frame_bottom, COLOR_DARK_BROWN, GL_FILL);

    static const GLfloat vertex_main_frame_sides[] = {
      //Right Top Side
      0.0f, 0.75f, -1.75f,
      0.0f, 0.0f, -1.5f,
      0.5f, 0.0f, -1.0f,
      0.0f, 0.75f, -1.75f,
      0.5f, 0.0f, -1.0f,
      0.75, 0.75f, -1.0f,
      //Left Top Side
      0.0f, 0.75f, -1.75f,
      0.0f, 0.0f, -1.5f,
      -0.5f, 0.0f, -1.0f,
      0.0f, 0.75f, -1.75f,
      -0.5f, 0.0f, -1.0f,
      -0.75, 0.75f, -1.0f,
      //Right Bottom Side
      0.0f, 0.75f, 1.75f,
      0.0f, 0.0f, 1.5f,
      0.5f, 0.0f, 1.0f,
      0.0f, 0.75f, 1.75f,
      0.5f, 0.0f, 1.0f,
      0.75, 0.75f, 1.0f,
      //Left Bottom Side
      0.0f, 0.75f, 1.75f,
      0.0f, 0.0f, 1.5f,
      -0.5f, 0.0f, 1.0f,
      0.0f, 0.75f, 1.75f,
      -0.5f, 0.0f, 1.0f,
      -0.75, 0.75f, 1.0f,
      //Right Side
      0.5f, 0.0f, -1.0f,
      0.75f, 0.75f, -1.0f,
      0.5f, 0.0f, 1.0f,
      0.75f, 0.75f, -1.0f,
      0.5f, 0.0f, 1.0f,
      0.75f, 0.75f, 1.0f,
      //Left Side
      -0.5f, 0.0f, -1.0f,
      -0.75f, 0.75f, -1.0f,
      -0.5f, 0.0f, 1.0f,
      -0.75f, 0.75f, -1.0f,
      -0.5f, 0.0f, 1.0f,
      -0.75f, 0.75f, 1.0f
    };
    this->frame_sides = create3DObject(GL_TRIANGLES, 12*3, vertex_main_frame_sides, COLOR_BROWN, GL_FILL);
    mastheight = 3.0f;
    mastthickness = 0.01f;
    static const GLfloat vertex_main_frame_mast[] = {
      //Front part
      mastthickness, 0.0f, -1*mastthickness,
      -1*mastthickness, 0.0f, -1*mastthickness,
      mastthickness, mastheight, -1*mastthickness,
      -1*mastthickness, 0.0f, -1*mastthickness,
      mastthickness, mastheight, -1*mastthickness,
      -1*mastthickness, mastheight, -1*mastthickness,
      //Bottom part
      mastthickness, 0.0f, mastthickness,
      -1*mastthickness, 0.0f, mastthickness,
      mastthickness, mastheight, mastthickness,
      -1*mastthickness, 0.0f, mastthickness,
      mastthickness, mastheight, mastthickness,
      -1*mastthickness, mastheight, mastthickness,
      //Right part
      mastthickness, 0.0f, -1*mastthickness,
      mastthickness, mastheight, -1*mastthickness,
      mastthickness, 0.0f, mastthickness,
      mastthickness, mastheight, -1*mastthickness,
      mastthickness, 0.0f, mastthickness,
      mastthickness, mastheight, mastthickness,
      //Right part
      -1*mastthickness, 0.0f, -1*mastthickness,
      -1*mastthickness, mastheight, -1*mastthickness,
      -1*mastthickness, 0.0f, mastthickness,
      -1*mastthickness, mastheight, -1*mastthickness,
      -1*mastthickness, 0.0f, mastthickness,
      -1*mastthickness, mastheight, mastthickness,
      //Top Square
      mastthickness, mastheight, -1*mastthickness,
      -1*mastthickness, mastheight, -1*mastthickness,
      -1*mastthickness, mastheight, mastthickness,
      mastthickness, mastheight, -1*mastthickness,
      -1*mastthickness, mastheight, mastthickness,
      mastthickness, mastheight, mastthickness,
    };
    this->frame_mast = create3DObject(GL_TRIANGLES, 10*3, vertex_main_frame_mast, COLOR_BROWN, GL_FILL);

    static const GLfloat vertex_main_frame_sail[] = {
      mastthickness, mastheight, -1*mastthickness,
      mastthickness, mastheight/2, -1*mastthickness,
      -0.2f, 3*mastheight/4, -1.75,
      -1*mastthickness, mastheight, -1*mastthickness,
      -1*mastthickness, mastheight/2, -1*mastthickness,
      -0.2f, 3*mastheight/4, -1.75
    };
    this->frame_sail = create3DObject(GL_TRIANGLES, 1*3, vertex_main_frame_sail, COLOR_RED, GL_FILL);

    static const GLfloat vertex_main_cannons[] = {
      //Right Front
      0.5f, 0.75f, -0.6f,
      0.5f, 0.75f, -0.4f,
      1.0f, 0.75f, -0.4f,
      1.0f, 0.75f, -0.4f,
      0.5f, 0.75f, -0.6f,
      1.0f, 0.75f, -0.6f,

      0.5f, 0.95f, -0.6f,
      0.5f, 0.95f, -0.4f,
      1.0f, 0.95f, -0.4f,
      1.0f, 0.95f, -0.4f,
      0.5f, 0.95f, -0.6f,
      1.0f, 0.95f, -0.6f,

      0.5f, 0.75f, -0.6f,
      0.5f, 0.75f, -0.4f,
      0.5f, 0.95f, -0.6f,
      0.5f, 0.75f, -0.4f,
      0.5f, 0.95f, -0.6f,
      0.5f, 0.95f, -0.4f,

      0.5f, 0.75f, -0.6f,
      0.5f, 0.95f, -0.6f,
      1.0f, 0.75f, -0.6f,
      0.5f, 0.95f, -0.6f,
      1.0f, 0.75f, -0.6f,
      1.0f, 0.95f, -0.6f,

      0.5f, 0.75f, -0.4f,
      0.5f, 0.95f, -0.4f,
      1.0f, 0.75f, -0.4f,
      0.5f, 0.95f, -0.4f,
      1.0f, 0.75f, -0.4f,
      1.0f, 0.95f, -0.4f,

      //Right Back
      0.5f, 0.75f, 0.6f,
      0.5f, 0.75f, 0.4f,
      1.0f, 0.75f, 0.4f,
      1.0f, 0.75f, 0.4f,
      0.5f, 0.75f, 0.6f,
      1.0f, 0.75f, 0.6f,

      0.5f, 0.95f, 0.6f,
      0.5f, 0.95f, 0.4f,
      1.0f, 0.95f, 0.4f,
      1.0f, 0.95f, 0.4f,
      0.5f, 0.95f, 0.6f,
      1.0f, 0.95f, 0.6f,

      0.5f, 0.75f, 0.6f,
      0.5f, 0.75f, 0.4f,
      0.5f, 0.95f, 0.6f,
      0.5f, 0.75f, 0.4f,
      0.5f, 0.95f, 0.6f,
      0.5f, 0.95f, 0.4f,

      0.5f, 0.75f, 0.6f,
      0.5f, 0.95f, 0.6f,
      1.0f, 0.75f, 0.6f,
      0.5f, 0.95f, 0.6f,
      1.0f, 0.75f, 0.6f,
      1.0f, 0.95f, 0.6f,

      0.5f, 0.75f, 0.4f,
      0.5f, 0.95f, 0.4f,
      1.0f, 0.75f, 0.4f,
      0.5f, 0.95f, 0.4f,
      1.0f, 0.75f, 0.4f,
      1.0f, 0.95f, 0.4f,



      //Left Front
      -0.5f, 0.75f, -0.6f,
      -0.5f, 0.75f, -0.4f,
      -1.0f, 0.75f, -0.4f,
      -1.0f, 0.75f, -0.4f,
      -0.5f, 0.75f, -0.6f,
      -1.0f, 0.75f, -0.6f,

      -0.5f, 0.95f, -0.6f,
      -0.5f, 0.95f, -0.4f,
      -1.0f, 0.95f, -0.4f,
      -1.0f, 0.95f, -0.4f,
      -0.5f, 0.95f, -0.6f,
      -1.0f, 0.95f, -0.6f,

      -0.5f, 0.75f, -0.6f,
      -0.5f, 0.75f, -0.4f,
      -0.5f, 0.95f, -0.6f,
      -0.5f, 0.75f, -0.4f,
      -0.5f, 0.95f, -0.6f,
      -0.5f, 0.95f, -0.4f,

      -0.5f, 0.75f, -0.6f,
      -0.5f, 0.95f, -0.6f,
      -1.0f, 0.75f, -0.6f,
      -0.5f, 0.95f, -0.6f,
      -1.0f, 0.75f, -0.6f,
      -1.0f, 0.95f, -0.6f,

      -0.5f, 0.75f, -0.4f,
      -0.5f, 0.95f, -0.4f,
      -1.0f, 0.75f, -0.4f,
      -0.5f, 0.95f, -0.4f,
      -1.0f, 0.75f, -0.4f,
      -1.0f, 0.95f, -0.4f,

      //Left Back
      -0.5f, 0.75f, 0.6f,
      -0.5f, 0.75f, 0.4f,
      -1.0f, 0.75f, 0.4f,
      -1.0f, 0.75f, 0.4f,
      -0.5f, 0.75f, 0.6f,
      -1.0f, 0.75f, 0.6f,

      -0.5f, 0.95f, 0.6f,
      -0.5f, 0.95f, 0.4f,
      -1.0f, 0.95f, 0.4f,
      -1.0f, 0.95f, 0.4f,
      -0.5f, 0.95f, 0.6f,
      -1.0f, 0.95f, 0.6f,

      -0.5f, 0.75f, 0.6f,
      -0.5f, 0.75f, 0.4f,
      -0.5f, 0.95f, 0.6f,
      -0.5f, 0.75f, 0.4f,
      -0.5f, 0.95f, 0.6f,
      -0.5f, 0.95f, 0.4f,

      -0.5f, 0.75f, 0.6f,
      -0.5f, 0.95f, 0.6f,
      -1.0f, 0.75f, 0.6f,
      -0.5f, 0.95f, 0.6f,
      -1.0f, 0.75f, 0.6f,
      -1.0f, 0.95f, 0.6f,

      -0.5f, 0.75f, 0.4f,
      -0.5f, 0.95f, 0.4f,
      -1.0f, 0.75f, 0.4f,
      -0.5f, 0.95f, 0.4f,
      -1.0f, 0.75f, 0.4f,
      -1.0f, 0.95f, 0.4f,
    
      
    };
    this->frame_cannons = create3DObject(GL_TRIANGLES, 40*3, vertex_main_cannons, COLOR_BLACK, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->frame_bottom);
    draw3DObject(this->frame_sides);
    draw3DObject(this->frame_borders);
    draw3DObject(this->frame_mast);
    draw3DObject(this->frame_sail);
    draw3DObject(this->frame_cannons);        
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
  this->position.z += this->zautovelocity;
  this->position.x += this->xautovelocity;
  this->position.y += this->yvelocity;
  this->yvelocity += this->yaccel;
  if(this->position.y <= 0 && this->yvelocity < 0) this->position.y = 0, this->yvelocity = 0;
}

bounding_box_t Boat::bounding_box() {
  bounding_box_t bbox = { this->position.x, this->position.y, this->position.z, 0.75, 1.75, this->mastheight};
  return bbox;
}
