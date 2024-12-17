/*
	Name: Adeshvir Dhillon
*/

// Imports
#define _USE_MATH_DEFINES // For M_PI, needs to be the first thing defined to work for some reason
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cmath>
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <gl/glut.h>
#include <utility>
#include <vector>
#include <windows.h>
#include <GL/freeglut.h>
#include <fstream>
#include "main.h"

//#include "glsl.h"

using namespace std;

// Measurements
const int vWidth = 650 * 1.5;    // Viewport width in pixels
const int vHeight = 500 * 1.5;    // Viewport height in pixels

float cannonCylinderRadiusTop = 1.5;
float cannonCylinderRadiusBottom = cannonCylinderRadiusTop;
float cannonCylinderDepth = 20.0;

float projectileSize = 1.0;

// Angles
float cannonHorizontalAngle = 180.0;
float cannonVerticalAngle = -2.0;

// Flags
bool gameFlag = true;
bool cannonHit = false;
bool canShoot = true;

// Counters
int canShootCounter = 0;
int robotRespawnCounter = -50000; // Initially a negative value instead of 0 to give the player time to prepare at the beginning of a game
int robotsWalkCounter = 0;
int robotID = 0;
int respawnTime = 5000;
int shootTime = 4000;
int maxRobots = 2;
int numRobotsWave = 10;
int numRobots = numRobotsWave;
int robotsDestroyed = 0;

float robotWalkSpeed = 20.0f;
float robotProjectileSpeed = 100.0f;

GLUquadric* quadric; // For quadric surfaces

// Textures
GLuint cannonTexture;
GLuint projectileTexture;
GLuint robotProjectileTexture;

// Shaders
GLuint shaderProgram;

// Lists
std::vector<Projectile> projectiles; // Holds active projectiles
std::vector<Robot> robots; // Holds active robots
std::vector<Projectile> robotProjectiles; // Holds active robot projectiles

// Lights
GLfloat light_position0[] = { 4.0F, 8.0F, 8.0F, 1.0F };
GLfloat light_position1[] = { 4.0F, 8.0F, 8.0F, 1.0F };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient[] = { 0.2F, 0.2F, 0.2F, 1.0F };

// Colours
//     Robot Blue
GLfloat blue_ambient[] = { 0.101f,0.146f,0.229f,1.0f };
GLfloat blue_specular[] = { 0.337f,0.486f,0.765f,1.0f };
GLfloat blue_diffuse[] = { 0.101f,0.146f,0.229f,1.0f };
GLfloat blue_shininess[] = { 32.0F };

//     Robot Grey
GLfloat grey_ambient[] = { 0.133f,0.16f,0.169f,1.0f };
GLfloat grey_specular[] = { 0.443f,0.533f,0.565f,1.0f };
GLfloat grey_diffuse[] = { 0.222f,0.267f,0.282f,1.0f };
GLfloat grey_shininess[] = { 32.0F };

//     Robot Red
GLfloat red_ambient[] = { 0.247f,0.066f,0.038f,1.0f };
GLfloat red_specular[] = { 0.824f,0.220f,0.125f,1.0f };
GLfloat red_diffuse[] = { 0.412f,0.110f,0.063f,1.0f };
GLfloat red_shininess[] = { 32.0F };

//     Robot White
GLfloat white_ambient[] = { 0.251f,0.268f,0.262f,1.0f };
GLfloat white_specular[] = { 0.835f,0.894f,0.875f,1.0f };
GLfloat white_diffuse[] = { 0.418f,0.447f,0.438f,1.0f };
GLfloat white_shininess[] = { 32.0F };

//     Robot Yellow
GLfloat yellow_ambient[] = { 0.274f,0.194f,0.045f,1.0f };
GLfloat yellow_diffuse[] = { 0.913f,0.647f,0.149f,1.0f };
GLfloat yellow_specular[] = { 0.457f,0.324f,0.075f,1.0f };
GLfloat yellow_shininess[] = { 32.0F };

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(vWidth, vHeight);
	glutInitWindowPosition(1000, 25);
	glutCreateWindow("Robot Attack");

	// Initializing GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		return -1;
	}

	initOpenGL(vWidth, vHeight);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(functionKeys);
	glutIdleFunc(idle);

	// Prints help output to Terminal/Debugger
	cout << "\n[Help]\n\tARROW KEYS - move the cannon\n\tSPACE - shoot a projectile\n\n\tRobots will shoot projectiles at you, even one hit is fatal\n\tEither shoot down the projectiles or shoot the robots before they fire\n\tProgressive waves of robots will have more maximum robots at a time and more robots in total\n\n\tGood luck and try your best to survive the endless waves\n\n\n";

	resetGame();

	glutMainLoop();

	return 0;
}

void initOpenGL(int w, int h) {
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);   // This second light is currently off

	glEnable(GL_DEPTH_TEST);   // Remove hidded surfaces
	glShadeModel(GL_SMOOTH);   // Use smooth shading, makes boundaries between polygons harder to see 
	glClearColor(0.0F, 0.588F, 1.0F, 1.0F);  // Color and depth for glClear
	glClearDepth(1.0f);
	glEnable(GL_NORMALIZE);    // Renormalize normal vectors 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   // Nicer perspective

	loadTexture(cannonTexture, "cannon_texture.jpg");
	loadTexture(projectileTexture, "projectile_texture.jpg");
	loadTexture(robotProjectileTexture, "robotProjectile_texture.jpg");

	shaderProgram = createShaderProgram("vertexShader.txt", "fragmentShader.txt");

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void loadTexture(GLuint& textureID, const char* filename) {
	int width, height, channels;
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
	if (!data) {
		exit(1);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // Modulate mode

	stbi_image_free(data);
}

GLuint loadShader(const char* filepath, GLenum shaderType) {
	std::ifstream shaderFile(filepath);
	if (!shaderFile.is_open()) {
		exit(1);
	}

	std::string shaderCode((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	GLuint shader = glCreateShader(shaderType);
	const char* shaderCodeCStr = shaderCode.c_str();
	glShaderSource(shader, 1, &shaderCodeCStr, nullptr);
	glCompileShader(shader);

	// Check for compilation errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		exit(-1);
	}

	return shader;
}

GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath) {
	GLuint vertexShader = loadShader(vertexPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		exit(-1);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 10.0, 35.0, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);

	glUseProgram(shaderProgram);

	glUniform1i(glGetUniformLocation(shaderProgram, "useTexture"), GL_TRUE);
	drawCannon();
	glUniform1i(glGetUniformLocation(shaderProgram, "useTexture"), GL_FALSE);

	glPushMatrix();
		glDisable(GL_LIGHTING);
		drawFloor();
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glUniform1i(glGetUniformLocation(shaderProgram, "useTexture"), GL_TRUE);
	drawProjectiles();
	glUniform1i(glGetUniformLocation(shaderProgram, "useTexture"), GL_FALSE);
	drawRobots();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)w / h, 0.2, 1000.0); // Last parameter is the far clipping plane (objects that far aren't rendered)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 10.0, 35.0, 0.0, 5.0, 0.0, 0.0, 1.0, 0.0);
}

void drawFloor() {
	glPushMatrix();
	glColor3f(0.0f, 0.502f, 0.0f);

	// Draw the floor as a large quad
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-750.0f, -20.0f, -500.0f); // Bottom-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(750.0f, -20.0f, -500.0f);  // Bottom-right
	glTexCoord2f(1.0f, 1.0f); glVertex3f(750.0f, -20.0f, 100.0f);   // Top-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-750.0f, -20.0f, 100.0f);  // Top-left
	glEnd();
	glPopMatrix();
}

void drawCannon() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cannonTexture);

	glMaterialfv(GL_FRONT, GL_AMBIENT, white_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, white_shininess);

	if (cannonHit) {
		if (cannonHorizontalAngle <= 185.0 && cannonHorizontalAngle >= 175.0 && cannonVerticalAngle <= -20.0) {
			cout << "GAME OVER\n"; // Play again question
			cout << "Robot destroyed: ";
			cout << (robotsDestroyed);
			cout << "\n\n";
			gameFlag = false;
			cout << "Press (Y) to play again and (N) to quit\n\n";
		}
		else {
			if (cannonHorizontalAngle > 180.0) {
				cannonHorizontalAngle -= 0.01;
			}
			else {
				cannonHorizontalAngle += 0.01;
			}
			if (cannonVerticalAngle > -25.0) {
				cannonVerticalAngle -= 0.01;
			}
		}
	}

	glPushMatrix();
	glTranslatef(0.0, 0.0, 27.5);
	glRotatef(cannonVerticalAngle, 1.0, 0.0, 0.0);
	glRotatef(cannonHorizontalAngle, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -27.5);

	glTranslatef(0.0, 0.0, 27.5);
	glPushMatrix();
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	gluCylinder(quadric, cannonCylinderRadiusTop, cannonCylinderRadiusBottom, cannonCylinderDepth, 20, 20);
	gluDeleteQuadric(quadric);
	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void drawProjectiles() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, projectileTexture);

	glMaterialfv(GL_FRONT, GL_AMBIENT, grey_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grey_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, grey_shininess);

	for (const auto& p : projectiles) {
		if (p.active) {
			glPushMatrix();
			glTranslatef(p.x, p.y, p.z);
			glutSolidSphere(projectileSize, 20, 20);
			glPopMatrix();
		}
	}

	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, robotProjectileTexture);

	glMaterialfv(GL_FRONT, GL_AMBIENT, red_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, red_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, red_shininess);

	for (const auto& p : robotProjectiles) {
		if (p.active) {
			glPushMatrix();
			glTranslatef(p.x, p.y, p.z);
			glutSolidSphere(projectileSize, 20, 20);
			glPopMatrix();
		}
	}

	glDisable(GL_TEXTURE_2D);
}

void drawRobots() {
	for (auto& r : robots) {
		if (r.active) {
			upperAngle = r.upperAngle;
			cannonSpinAngle = r.cannonSpinAngle;
			leftArmAngle = r.leftArmAngle;
			rightArmAngle = r.rightArmAngle;
			if (robotsWalkCounter > 100 && !cannonHit) {
				robotsWalkCounter = 0;
				if (r.walkCounter > 8) {
					if (r.walkFlag) {
						if (r.rightLegAngle > -46) {
							r.rightLegAngle -= 2.0;
						}
						if (r.hipAngle < 15) {
							r.hipAngle += 1.0;
						}
						if (r.leftLegAngle < 46) {
							r.leftLegAngle += 2.0;
						}
						if ((r.rightLegAngle == -46) && (r.hipAngle == 15) && (r.leftLegAngle == 46)) {
							r.walkFlag = false;
						}
					}
					else {
						if (r.rightLegAngle < 46) {
							r.rightLegAngle += 2.0;
						}
						if (r.hipAngle > -15) {
							r.hipAngle -= 1.0;
						}
						if (r.leftLegAngle > -46) {
							r.leftLegAngle -= 2.0;
						}
						if ((r.rightLegAngle == 46) && (r.hipAngle == -15) && (r.leftLegAngle == -46)) {
							r.walkFlag = true;
						}
					}
					rightLegAngle = r.rightLegAngle;
					hipAngle = r.hipAngle;
					leftLegAngle = r.leftLegAngle;
				}
				else {
					r.walkCounter++;
				}
			}
			else {
				robotsWalkCounter++;
			}
		}
		glPushMatrix();
		glTranslatef(r.x, r.y, r.z);
		drawRobot();
		glPopMatrix();
	}
}

void updateRobots(float deltaTime) {
	for (auto& r : robots) {
		if (r.active) {
			r.z += r.vz * deltaTime;
			r.upperAngle = atan2(r.x, (r.z - 27.5)) * (180 / M_PI) + 180;
			r.cannonSpinAngle += 2.0;
			if (r.z > 40.0f) {
				r.active = false;
				robotRespawnCounter = 0;
			}
			if (r.shootCounter > shootTime && r.z < -25.0) {
				fireRobotProjectile(r);
				r.shootCounter = 0;
			}
			else {
				r.shootCounter++;
			}
		}
	}
	robots.erase(std::remove_if(robots.begin(), robots.end(), [](const Robot& r) {return !r.active;}), robots.end()); // Remove inactive robots
}

void fireRobotProjectile(Robot r) {
	float shootChance = (rand() % (10000 + 1 - 0) + 0);
	if (shootChance > 7000) {
		float radHorizontal = r.upperAngle * M_PI / 180.0f;
		float radVertical = 0.0;

		Projectile p;
		p.x = r.x - 6.3;
		p.y = r.y + 6.0;
		p.z = r.z;

		float vxFactor = (rand() % (10 + 1 - (-10)) + (-10)) * M_PI / 180.0f;
		float vyFactor = (rand() % (10 + 1 - (-10)) + (-10)) * M_PI / 180.0f;
		p.vx = robotProjectileSpeed * cos(radVertical) * (sin(radHorizontal) + vxFactor);
		p.vy = robotProjectileSpeed * (sin(radVertical) + vyFactor);
		p.vz = robotProjectileSpeed * cos(radVertical) * cos(radHorizontal);

		p.active = true;

		p.robot = r;

		robotProjectiles.push_back(p);
	}
}

void fireProjectile() {
	float radHorizontal = cannonHorizontalAngle * M_PI / 180.0f;
	float radVertical = cannonVerticalAngle * M_PI / 180.0f;

	Projectile p;
	p.x = 0.0f;
	p.y = 0.0f;
	p.z = 27.5f;

	float speed = 100.0f;
	p.vx = speed * cos(radVertical) * sin(radHorizontal);
	p.vy = speed * sin(radVertical);
	p.vz = speed * cos(radVertical) * cos(radHorizontal);

	p.active = true;

	projectiles.push_back(p);
}

void updateProjectiles(float deltaTime) {
	for (auto& p : projectiles) {
		if (p.active) {
			p.x += p.vx * deltaTime;
			p.y += p.vy * deltaTime;
			p.z += p.vz * deltaTime;
		}
	}
	for (auto& p : robotProjectiles) {
		if (p.active) {
			p.x += p.vx * deltaTime;
			p.y += p.vy * deltaTime;
			p.z += p.vz * deltaTime;
		}
	}
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p) {return !p.active;}), projectiles.end()); // Remove inactive projectiles
	robotProjectiles.erase(std::remove_if(robotProjectiles.begin(), robotProjectiles.end(), [](const Projectile& p) {return !p.active;}), robotProjectiles.end()); // Remove inactive robot projectiles
}

void checkCollisions() {
	for (auto& p : projectiles) { // Player projectiles
		if (p.active) {
			for (auto& r : robots) {
				if (r.active && abs(p.x - r.x) < 7.5f && (p.y - r.y > -15.0f && p.y - r.y < 10.0f) && abs(p.z - r.z) < 1.0f) {
					r.active = false; // Projectile hits robot
					p.active = false;
					robotRespawnCounter = 0;
					numRobots--;
					robotsDestroyed++;
				}
			}
			if (p.y <= -19.0) { // Player projectile hits ground
				p.active = false;
			}
		}
	}
	for (auto& p : robotProjectiles) { // Robot projectiles
		if (p.active) {
			for (auto& r : robots) {
				if (r.active && !(r.ID == (p.robot).ID) && abs(p.x - r.x) < 7.5f && (p.y - r.y > -15.0f && p.y - r.y < 10.0f) && abs(p.z - r.z) < 1.0f) {
					p.active = false; // A robot projectile hitting a robot just disappears
				}
			}
			for (auto& p2 : projectiles) {
				if (p2.active && abs(p.x - p2.x) < 1.5f && abs(p.y - p2.y) < 1.5f && abs(p.z - p2.z) < 1.5f) {
					p.active = false; // A robot projectile and player projectile hitting each other cancel out
					p2.active = false;
				}
			}
			if (((abs(p.x) <= 3.5f && (p.y <= 3.0f && p.y >= -0.5f) && abs(p.z - 27.5) <= 20.0f) || (abs(p.x) <= 8.5f && (p.y <= 22.5f && p.y >= -15.0f) && abs(p.z - 27.5) <= 1.0f))) {
				cannonHit = true; // Robot projectile hits cannon (game over)
			}
			if (p.y <= -19.0) { // Robot projectile hits ground
				p.active = false;
			}
		}
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case ' ': // Space Key
		if (canShoot == true && cannonHit == false) {
			fireProjectile();
			canShoot = false;
		}
		break;
	case 'y':
	case 'Y':
		if (!gameFlag) {
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			resetGame();
		}
		break;
	case 'n':
	case 'N':
		if (!gameFlag) {
			exit(0);
		}
		break;
	}
	glutPostRedisplay();   // Trigger a window redisplay
}

void resetGame() { // Resets all necessary variables for restarting game
	gameFlag = true;
	cannonHorizontalAngle = 180.0;
	cannonVerticalAngle = -2.0;
	cannonHit = false;
	canShoot = true;
	canShootCounter = 0;
	robotRespawnCounter = -50000;
	robotsWalkCounter = 0;
	robotID = 0;
	maxRobots = 2;
	numRobotsWave = 10;
	numRobots = numRobotsWave;
	robotWalkSpeed = 20.0f;
	robotProjectileSpeed = 100.0f;
	robotsDestroyed = 0;
	projectiles.clear();
	robots.clear();
	robotProjectiles.clear();
	cout << "Wave ";
	cout << (maxRobots - 1);
	cout << "\n\tMax Robots: ";
	cout << (maxRobots);
	cout << "\n\tTotal Robots: ";
	cout << (numRobotsWave);
	cout << "\n\n";
}

void functionKeys(int key, int x, int y) {
	if (!gameFlag) {
		return;
	}
	switch (key) {
	case GLUT_KEY_F1: // Help Key, prints to Terminal/Debugger
		cout << "\n\n[Help]\n\tARROW KEYS - move the cannon\n\tSPACE - shoot a projectile\n\n\tRobots will shoot projectiles at you, even one hit is fatal\n\tEither shoot down the projectiles or shoot the robots before they fire\n\tProgressive waves of robots will have more maximum robots at a time and more robots in total\n\n\tGood luck and try your best to survive the endless waves\n\n\n";
		break;

	case GLUT_KEY_UP:
		if (cannonVerticalAngle < 12.0) {
			cannonVerticalAngle += 2.0;
		}
		break;

	case GLUT_KEY_DOWN:
		if (cannonVerticalAngle > -4.0) {
			cannonVerticalAngle -= 2.0;
		}
		break;

	case GLUT_KEY_RIGHT:
		if (cannonHorizontalAngle > 135.0) {
			cannonHorizontalAngle -= 2.0;
		}
		break;

	case GLUT_KEY_LEFT:
		if (cannonHorizontalAngle < 225.0) {
			cannonHorizontalAngle += 2.0;
		}
		break;
	}
	glutPostRedisplay();   // Trigger a window redisplay
}

void idle() {
	static int lastTime = glutGet(GLUT_ELAPSED_TIME);
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	if (gameFlag) {
		if (!cannonHit) {
			if (canShoot == false) {
				if (canShootCounter < 2000) { // To stop the user from firing a constant beam of projectiles
					canShootCounter++;
				}
				else {
					canShootCounter = 0;
					canShoot = true;
				}
			}
			if (numRobots > 0) { // Robot creation
				if (robotRespawnCounter >= respawnTime) {
					if (robots.size() < maxRobots) {
						Robot r;
						float x_val = (rand() % (60 + 1 - 20) + 20);
						if (rand() % 2 == 0) {
							r.x = x_val;
						}
						else {
							r.x = x_val * -1.0;
						}
						r.y = 0.0f;
						r.z = -250.0f;

						r.vx = 0.0f;
						r.vy = 0.0f;
						r.vz = robotWalkSpeed;

						r.active = true;

						r.walkFlag = true;

						r.hipAngle = 0.0;
						r.leftLegAngle = 0.0;
						r.rightLegAngle = 0.0;

						r.upperAngle = atan2(r.x, (r.z - 27.5)) * (180 / M_PI) + 180; // Constantly angled towards cannon (uses the angles of a right angle triangle)

						r.cannonSpinAngle = 0.0;

						r.leftArmAngle = 0.0;
						r.rightArmAngle = 270.0;

						r.walkCounter = 0;
						r.shootCounter = 0;

						r.ID = robotID; // To identify a robot so that a robot projectile doesn't collide with the robot that shot it
						robotID++; // Keep on increasing indefinitely

						robots.push_back(r); // Add current robot struct to robots vector list

						robotRespawnCounter = 0;
					}
				}
				else {
					robotRespawnCounter++;
				}
				updateRobots(deltaTime);
			}
			else { // Wave over, start next wave
				numRobotsWave++;
				numRobots = numRobotsWave;
				maxRobots++;
				respawnTime = respawnTime * 0.9;
				shootTime = shootTime * 0.9;
				robotWalkSpeed += 5.0;
				robotProjectileSpeed += 10.0;

				cout << "Wave ";
				cout << (maxRobots - 1);
				cout << "\n\tMax Robots: ";
				cout << (maxRobots);
				cout << "\n\tTotal Robots: ";
				cout << (numRobotsWave);
				cout << "\n\n";
			}
		}
		updateProjectiles(deltaTime);
		checkCollisions();
		glutPostRedisplay();
	}
}