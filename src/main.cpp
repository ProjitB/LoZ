#include "main.h"
#include "timer.h"
#include "boat.h"
#include "water.h"
#include "rock.h"
#include "flame.h"
#include "monster.h"
#include "boss.h"
#include "powerup.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int health = 1000, level = 1, score = 0;
Boat player;
Water water;
Boat testloc;
int viewType = 1;
float screen_zoom = 100, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
vector<Rock> rocks;
vector<Flame> flames;
vector<Flame> monflames;
vector<Monster> monsters;
vector<Boss> bosses;
vector<Powerup> powerups;

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
      return player.position.x - 1.75*sin(player.rotation*M_PI/180.0f);
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
      return player.position.z - 1.75*cos(player.rotation*M_PI/180.0f);
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
    if (viewType == 4) target.z -= 100*cos(player.rotation*M_PI/180.0f), target.x -= 100*sin(player.rotation*M_PI/180.0f);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);
    if (viewType == 2) up.y = 0, up.z = -1*cos(player.rotation*M_PI/180.0f), up.x = -1*sin(player.rotation*M_PI/180.0f);
    else up.y = 1, up.z = 0, up.x = 0;
    
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
    for (int i = 0; i < (int)rocks.size(); rocks[i++].draw(VP));
    for (int i = 0; i < (int)flames.size(); flames[i++].draw(VP));
    for (int i = 0; i < (int)monflames.size(); monflames[i++].draw(VP));     
    for (int i = 0; i < (int)monsters.size(); monsters[i++].draw(VP));
    for (int i = 0; i < (int)bosses.size(); bosses[i++].draw(VP));
    for (int i = 0; i < (int)powerups.size(); powerups[i++].draw(VP));
}


void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int f = glfwGetKey(window, GLFW_KEY_F);
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
    if (f) {
        cannon(viewType);
    }
}

int canCount = 0;
void cannon(int viewType){
  if (viewType == 1 || viewType == 2){
    if(canCount < player.countTime) return;
    canCount = 0;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if(xpos < 0 || xpos > 600 || ypos < 0 || ypos > 600) //Valid Mouse Locations
      return;
    float dist = sqrt((xpos-300)*(xpos-300) + (ypos-300)*(ypos-300));
    float angle = acos((ypos-300) * (-300) / (300*dist)); //dot product
    if (xpos <= 300) angle *= -1;
    angle -= player.rotation * M_PI / 180.0f;
    flames.push_back(Flame(player.position.x, player.position.y+2, player.position.z, 0.3, angle, 0.5, dist/900.0, COLOR_RED));
    //  cout << // XXX: pos << ", " << ypos << ", " << dist << ", " << angle << "\n";
  }
  return;
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
  canCount++;
  player.tick();
  for (int i = 0; i < (int)rocks.size(); rocks[i++].tick());
  
  for (int i = 0; i < (int)flames.size(); i++) {
    flames[i].tick();
    if(flames[i].position.y < 0) flames.erase(flames.begin() + i);
  }
  
  for (int i = 0; i < (int)monflames.size(); i++) {
    if(monflames[i].position.y < 0 || monflames[i].position.y > 10) monflames.erase(monflames.begin() + i);
    monflames[i].tick();
  }
  
  for (int i = 0; i < (int)monsters.size();  monsters[i++].tick());

  for (int i = 0; i < (int)bosses.size(); bosses[i++].tick());
  for (int i = 0; i < (int)powerups.size(); powerups[i++].tick());
  
  wind();
}

int windlock = 400, windCounter = 0, windLast = 80, windLastCounter = 0, windBool = 0;
void wind(){
  if(windCounter == windlock && !windBool){//Wind Start,Intialize Wind
    windBool = 1;
    windLastCounter = 0;
    float windAngle = 0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/360));
    windlock = 300 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/300));
    player.xautovelocity = 0.1 * sin(windAngle * M_PI / 180.0f);
    player.zautovelocity = 0.1 * cos(windAngle * M_PI / 180.0f);
  }
  if(windBool){//When Wind
    windLastCounter++;
  }
  else{//When Not Wind
    windCounter++;
  }
  if(windLastCounter == windLast && windBool){//Wind End
    windBool = 0;
    windCounter = 0;
    player.xautovelocity = 0;
    player.zautovelocity = 0;
    windLast = 200 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100));
  }
}

void detect_player_rock_collisions(){
  for (int i = 0; i < (int)rocks.size(); i++) {
    if(detect_collision_player(rocks[i].bounding_box(), player.bounding_box()))
      health--, player.yvelocity = 0.2;
    
  }
}

void cannonball_monster_collisions(){
  for (int i = 0; i < (int)monsters.size(); i++){
    for (int j = 0; j < (int)flames.size(); j++){
      if (detect_collision(flames[j].bounding_box(), monsters[i].bounding_box())){
        monsters[i].health -= player.power;
        flames.erase(flames.begin() + j);        
      }
    }
  }
}

void cannonball_boss_collisions(){
  for (int i = 0; i < (int)bosses.size(); i++){
    for (int j = 0; j < (int)flames.size(); j++){
      if (detect_collision(flames[j].bounding_box(), bosses[i].bounding_box())){
        bosses[i].health -= player.power;
        flames.erase(flames.begin() + j);        
      }
    }
  }
}


void cannonball_rock_collisions(){
  for(int i = 0; i < (int)flames.size(); i++){
    for(int j = 0; j < (int)rocks.size(); j++)
      if(detect_collision(flames[i].bounding_box(), rocks[j].bounding_box())){
        score += 1;
        flames.erase(flames.begin() + i);
        rocks.erase(rocks.begin() + j);        
      }
  }
    
}

void detect_player_monflames_collisions() {
  for (int i = 0; i < (int)monflames.size(); i++){
    if (detect_collision_player(monflames[i].bounding_box(), player.bounding_box())){
      health -= monflames[i].damage;
      monflames.erase(monflames.begin() + i);
    }
  }
}

void detect_player_powerups_collisions(){
  for (int i = 0; i < (int)powerups.size(); i++){
    if (detect_collision_player(powerups[i].bounding_box(), player.bounding_box())){
      switch(powerups[i].type){
      case 1:
        health += powerups[i].value;
        break;
      case 2:
        player.countTime += powerups[i].value;
        break;
      case 3:
        score += powerups[i].value;
        break;
      }
      powerups.erase(powerups.begin() + i);
    }
  }
}

void collisions() {
  detect_player_rock_collisions();
  cannonball_monster_collisions();
  detect_player_monflames_collisions();
  cannonball_rock_collisions();
  cannonball_boss_collisions();
  detect_player_powerups_collisions();
}

void helperGenerateRocks(float LO, float HI, float quadx, float quadz){
  int numRocks = 10.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(10.0)));
  for(int i = 0; i < numRocks; i++)
    {
      float y = 0.25 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.75)));
      float x = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
      float z = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
      rocks.push_back(Rock(x*quadx, y, z*quadz, COLOR_BLACK));
    }
  return;
}

void generaterocks(){
  helperGenerateRocks(5.0, 90.0, 1, 1);
  helperGenerateRocks(5.0, 90.0, 1, -1);
  helperGenerateRocks(5.0, 90.0, -1, -1);
  helperGenerateRocks(5.0, 90.0, -1, 1);

  return;
}
void helperGenerateMonsters(float quadx, float quadz, float size){
  float LO = 5.0, HI = 90.0;
  float x = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
  float z = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
  monsters.push_back(Monster(x*quadx, 2*size, z*quadz, size, 50));
}

void generateMonsters(){
  helperGenerateMonsters(1,1,1);
  helperGenerateMonsters(1,-1,1);
  helperGenerateMonsters(-1,-1,1);
  helperGenerateMonsters(-1,1,1);
  return;
}

float distvec(float x1, float y1, float z1, float x2, float y2, float z2){
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

bool inRange(float x1, float y1, float z1, float distance, Monster& M){
  float x2 = M.position.x, y2 = M.position.y, z2 = M.position.z;
  float dist = distvec(x1, y1, z1, x2, y2, z2);
  if(dist <= distance) return 1;
  else return 0;
}

bool inRangeB(float x1, float y1, float z1, float distance, Boss& M){
  float x2 = M.position.x, y2 = M.position.y, z2 = M.position.z;
  float dist = distvec(x1, y1, z1, x2, y2, z2);
  if(dist <= distance) return 1;
  else return 0;
}


void monster_firing(Monster& M, float size, float vel, int damage){
  float dist = distvec(M.position.x, M.position.y, M.position.z, player.position.x, player.position.y, player.position.z);
  float vecx = player.position.x - M.position.x;
  float vecy = player.position.y - M.position.y;
  float vecz = player.position.z - M.position.z;
  float t = dist / vel;
  Flame temp = Flame(M.position.x, M.position.y, M.position.z, size, 0, 0,vel*vecy/dist, COLOR_DARK_RED);
  temp.yaccel = 0;
  temp.xvelocity = vel*vecx/dist;
  temp.zvelocity = vel*vecz/dist;
  temp.damage = damage;
  monflames.push_back(temp);
  M.counter = 0;
  return;
}


void boss_firing(Boss& M, float size, float vel, int damage){
  float dist = distvec(M.position.x, M.position.y, M.position.z, player.position.x, player.position.y, player.position.z);
  float vecx = player.position.x - M.position.x;
  float vecy = player.position.y - M.position.y;
  float vecz = player.position.z - M.position.z;
  float t = dist / vel;
  Flame temp = Flame(M.position.x, M.position.y, M.position.z, size, 0, 0,vel*vecy/dist, COLOR_DARK_RED);
  temp.yaccel = 0;
  temp.xvelocity = vel*vecx/dist;
  temp.zvelocity = vel*vecz/dist;
  temp.damage = damage;
  monflames.push_back(temp);
  M.counter = 0;
  return;
}


bool can_fire(Monster& M, float range){
  if (inRange(player.position.x, player.position.y, player.position.z, range, M) && M.counter >= M.countTime) return 1;
  return 0;
}

bool can_fire_B(Boss& M, float range){
  if (inRangeB(player.position.x, player.position.y, player.position.z, range, M) && M.counter >= M.countTime) return 1;
  return 0;
}


void boss_handling(){
  for (int i = 0; i < (int)bosses.size(); i++)
    {
        //Monster Dies
      if (bosses[i].health <= 0) bosses.erase(bosses.begin() + i), score += 200;
      if(can_fire_B(bosses[i], 150))
        boss_firing(bosses[i], 3, 0.3, 200);
    }
}

int bosslock = 0;
void monster_handling(){
  for (int i = 0; i < (int)monsters.size(); i++)
    {
      //Monster Dies
      if (monsters[i].health <= 0){
        int typePowerup = (rand() % 3) + 1;
        powerups.push_back(Powerup(monsters[i].position.x, monsters[i].position.y - 0.5, monsters[i].position.z, typePowerup));
        monsters.erase(monsters.begin() + i);
        score += 50;
      } 
      if (monsters.size() == 0 && bosslock == 0) {
        //Create Boss
        bosslock = 1;
        float x = -95 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(190)));
        float z = -95 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(190)));
        Boss temp = Boss(x, 10, z, 5, 200);
        temp.countTime = 100;
        temp.isBoss = 1;
        bosses.push_back(temp);
      }
      //If in Range fire and Time Gap, fire
      if (can_fire(monsters[i], 20.0)){
        monster_firing(monsters[i], 0.75, 0.2, 50);
        }
    }
}

void powerups_handling(){
  for(int i = 0; i < (int)powerups.size(); i++){
    if(powerups[i].counter > powerups[i].countMax) powerups.erase(powerups.begin() + i);
  }
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player = Boat(0, 0, 3);
    water = Water(0, 0, 0, COLOR_BLUE);
    testloc = Boat(0, 0, -5);
    generaterocks();
    generateMonsters();
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices.projection = glm::perspective(glm::radians(screen_zoom), (float)height / (float)width, 0.1f, 100.0f);

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
          monster_handling();
          boss_handling();
          powerups_handling();
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
  return (abs(a.x - b.x) < (a.width + b.width + b.length*sin(player.rotation*M_PI/180.0f))) &&
           (abs(a.y - b.y) < k) &&
    (abs(a.z - b.z) < (a.length + b.length - b.width*sin(player.rotation*M_PI/180.0f)));
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
