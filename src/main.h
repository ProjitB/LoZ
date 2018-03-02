#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);


// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
  float x;
  float y;
  float z;
  float width;
  float length;
  float height;
};

bool detect_collision_player(bounding_box_t a, bounding_box_t b);
bool detect_collision(bounding_box_t a, bounding_box_t b);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();
void wind();
void collisions();
void helperGenerateRocks(float LO, float HI, float quadx, float quadz);
void generaterocks();
void cannon(int viewType);
void monster_handling();
void generateMonsters();
void helperGenerateMonsters(float quadx, float quadz);
void detect_player_monflames_collisions();
bool inRange(float x1, float y1, float z1, float x2, float y2, float z2, float distance);
bool inRangeB(float x1, float y1, float z1, float x2, float y2, float z2, float distance);
float distvec(float x1, float y1, float z1, float x2, float y2, float z2);
void cannonball_rock_collisions();
void cannonball_boss_collisions();
void monster_firing(float size, float vel);
bool can_fire(float range);
bool can_fire_B(float range);
void boss_handling();
void boss_firing(float size, float vel);

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_LIGHT_BLUE;
extern const color_t COLOR_DARK_BROWN;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_DARK_RED;
#endif

