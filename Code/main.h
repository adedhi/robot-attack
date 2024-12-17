/*
	Name: Adeshvir Dhillon
*/

// Structs
struct Robot {
	float x, y, z;
	float vx, vy, vz;
	bool active;
	bool walkFlag;
	float hipAngle, leftLegAngle, rightLegAngle, upperAngle, cannonSpinAngle, leftArmAngle, rightArmAngle;
	int walkCounter, shootCounter;
	int ID;
};

struct Projectile {
	float x, y, z;
	float vx, vy, vz;
	bool active;
	Robot robot; // Optional variable holding the robot that shot the projectile
};

// Function Prototypes
void initOpenGL(int w, int h);
void loadTexture(GLuint& textureID, const char* filename);
GLuint loadShader(const char* filepath, GLenum shaderType);
GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath);
void display(void);
void reshape(int w, int h);
void drawFloor();
void drawCannon();
void drawProjectiles();
void drawRobots();
void updateRobots(float deltaTime);
void fireRobotProjectile(Robot r);
void fireProjectile();
void updateProjectiles(float deltaTime);
void checkCollisions();
void keyboard(unsigned char key, int x, int y);
void resetGame();
void functionKeys(int key, int x, int y);
void idle();

void drawRobot();
void drawBody();
void drawHead();
void drawLeftArm();
void drawRightArm();
void drawHip();
void drawLeftLeg();
void drawRightLeg();

// Extern Variables
extern float leftArmAngle;
extern float rightArmAngle;
extern float hipAngle;
extern float leftLegAngle;
extern float rightLegAngle;
extern float cannonSpinAngle;
extern float upperAngle;

extern GLuint cannonTexture;
extern GLuint projectileTexture;
extern GLuint robotProjectileTexture;