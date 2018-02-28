#include "main.h"
#include "timer.h"
#include "boat.h"
#include "water.h"
#include "rock.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int health = 10, level = 1, score = 0;
Boat player;
Water water;
Boat testloc;
int viewType = 1;
float screen_zoom = 100, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
vector<Rock> rocks;

Timer t60(1.0 / 60);

float xview(int type){
  switch(type){
    case 1:
      return player.position.x + 3*sin(player.rotation*M_PI/180.0f);
    case 2:
      return player.position.x;
    case 3:
      return 0;
    case 4:
      return player.position.x;
    }
}

float yview(int type){
  switch(type){
    case 1:
      return player.position.y + 3;
    case 2 :
      return 30;
    case 3:
      return 10;
    case 4:
      return player.position.y + 0.75;
  }
}

float zview(int type){
  switch(type){
    case 1:
      return 3*cos(player.rotation*M_PI/180.0f) + player.position.z;
    case 2:
      return player.position.z;
    case 3:
      return 0;
    case 4:
      return player.position.z - 1.75;
  }
}


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (xview(viewType), yview(viewType), zview(viewType));
    
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target = player.position;
    if (viewType == 4) target.z -= 100;
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    if (viewType == 2) up.y = 0, up.z = -1;
    else up.y = 1, up.z = 0;
    
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view ;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    //player.draw(VP);
    water.draw(VP);
    player.draw(VP);
    testloc.draw(VP);
    for (int i = 0; i < (int)rocks.size(); i++) {
      rocks[i].draw(VP);
    }
}


void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    
    if (left) player.rotation += 1;
    if (right) player.rotation -= 1;
    if (up) {
      player.position.z -= player.speed*cos(player.rotation*M_PI/180.0f);
      player.position.x -= player.speed*sin(player.rotation*M_PI/180.0f);
    }
    if (down) {
      player.position.z += player.speed*cos(player.rotation*M_PI/180.0f);
      player.position.x += player.speed*sin(player.rotation*M_PI/180.0f);
    }
    if (space && player.position.y == 0) player.yvelocity = 0.3;
}

void tick_camera(GLFWwindow *window) {
  int one = glfwGetKey(window, GLFW_KEY_1);
  int two = glfwGetKey(window, GLFW_KEY_2);
  int three = glfwGetKey(window, GLFW_KEY_3);
  int four = glfwGetKey(window, GLFW_KEY_4);

  if (one) viewType = 1;
  if (two) viewType = 2;
  if (three) viewType = 3;
  if (four) viewType = 4;

}

void tick_elements() {
  player.tick();
  for (int i = 0; i < (int)rocks.size(); i++) {
    rocks[i].tick();
  }
}

void collisions() {
  for (int i = 0; i < (int)rocks.size(); i++) {
    if(detect_collision_player(rocks[i].bounding_box(), player.bounding_box()))
      health--;
  }
  
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player       = Boat(0, 0, 3);
    water       = Water(0, 0, 0, COLOR_BLUE);
    testloc     = Boat(0, 0, -5);
    rocks.push_back(Rock(10, 1, -20, COLOR_BLACK));
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices.projection = glm::perspective(glm::radians(screen_zoom), (float)height / (float)width, 0.1f, 200.0f);

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    char stringPrint[1000];
    window = initGLFW(width, height);

    initGL (window, width, height);
    //    Matrices.projection = glm::perspective(glm::radians(screen_zoom), (float)height / (float)width, 0.1f, 100000000.0f);
    Matrices.projection = glm::perspective(glm::radians(screen_zoom), (float)600 / (float)600, 0.1f, 100.0f);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
          // 60 fps
          // OpenGL Draw commands
          sprintf(stringPrint, "Level: %d  Score: %d Health: %d", level, score, health);
          glfwSetWindowTitle(window, stringPrint);
          
          draw();
          // Swap Frame Buffer in double buffering
          glfwSwapBuffers(window);

          tick_elements();
          collisions();
          tick_camera(window);
          tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision_player(bounding_box_t a, bounding_box_t b) {
  float k;
  if (a.y >= b.y) k = a.height + b.height;
  else k = a.height;
  return (abs(a.x - b.x) < (a.width + b.width)) &&
           (abs(a.y - b.y) < k) &&
           (abs(a.z - b.z) < (a.length + b.length));
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) < (a.width + b.width)) &&
           (abs(a.y - b.y) < (a.height + b.height)) &&
           (abs(a.z - b.z) < (a.length + b.length));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  if (yoffset > 0) screen_zoom -= 1;
  if (yoffset < 0) screen_zoom += 1;
  Matrices.projection = glm::perspective(glm::radians(screen_zoom), (float)600 / (float)600, 0.1f, 100.0f);
}
