/*
	Name: Adeshvir Dhillon
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <gl/glut.h>
#include <utility>
#include <vector>

#include "main.h"

// THE BODY IS THE BASE PART

// Robot Measurements
	// Body Measurements
float robotBodyWidth = 8.0;
float robotBodyLength = 5.0;
float robotBodyDepth = 3.0;
float robotBodyChestWidth = 7.75;
float robotBodyChestLength = 3.0;
float robotBodyChestDepth = 2.0;
float robotBodyChestCubeWidth = 1.5;
float robotBodyChestCubeLength = 1.25;
float robotBodyChestCubeDepth = 0.5;
float robotBodyMiddleWidth = 2.0;
float robotBodyMiddleLength = 4.0;
float robotBodyMiddleDepth = 1.5;
float robotBodyWaistWidth = 7.25;
float robotBodyWaistLength = 2.0;
float robotBodyWaistDepth = 2.25;
float robotBodyBackpackWidth = 5.0;
float robotBodyBackpackLength = 5.0;
float robotBodyBackpackDepth = 1.5;
float robotBodyCylinderRadiusTop = 0.4;
float robotBodyCylinderRadiusBottom = 0.4;
float robotBodyCylinderDepth = 5.0;

// Head Measurements
float robotHeadWidth = 3.2;
float robotHeadLength = 3.2;
float robotHeadDepth = 3.2;
float robotHeadBandWidth = 0.5;
float robotHeadBandLength = 0.6;
float robotHeadBandDepth = robotHeadLength + 0.5;
float robotHeadBandBackWidth = 0.5;
float robotHeadBandBackLength = 0.5;
float robotHeadBandBackDepth = 0.5;
float robotHeadRedTopWidth = 0.35;
float robotHeadRedTopLength = 0.35;
float robotHeadRedTopDepth = 0.4;
float robotHeadAntennaLength = 2.5;
float robotHeadAntennaRadius = 0.15;
float robotHeadBrowLength = 1.25;
float robotHeadBrowRadius = 0.1;
float robotHeadEyeWidth = 0.15;
float robotHeadEyeLength = 0.10;
float robotHeadEyeDepth = 0.1;
float robotHeadRedBottomWidth = 0.5;
float robotHeadRedBottomLength = 0.5;
float robotHeadRedBottomDepth = 0.5;

// Arm Measurements
float robotArmWidth = 2.0;
float robotArmLength = 10.0;
float robotArmDepth = 2.0;
float robotShoulderWidth = 2.75;
float robotShoulderLength = 2.5;
float robotShoulderDepth = 2.5;
float robotHandWidth = 2.05;
float robotHandLength = 1.5;
float robotHandDepth = 2.05;
float robotCannonCylinderRadiusTop = 1.0;
float robotCannonCylinderRadiusBottom = robotCannonCylinderRadiusTop;
float robotCannonCylinderDepth = 0.35 * robotArmLength;
float robotCannonCylinderMiniRadiusTop = 0.25;
float robotCannonCylinderMiniRadiusBottom = robotCannonCylinderMiniRadiusTop;
float robotCannonCylinderMiniDepth = 0.75 * robotArmLength;
float cannonTorusRadiusInner = 0.125 * robotCannonCylinderRadiusTop;
float cannonTorusRadiusOuter = robotCannonCylinderRadiusTop + 0.1;
float cannonArmWidth = 0.5 * robotArmWidth;
float cannonArmLength = 2.0;
float cannonArmDepth = 1.0;

// Hip Measurements
float robotHipWidth = 7.75;
float robotHipLength = 3.0;
float robotHipDepth = 3.0;
float robotHipMiddleWidth = 2.0;
float robotHipMiddleLength = 2.5;
float robotHipMiddleDepth = 2.0;
float robotHipCubeWidth = 1.75;
float robotHipCubeLength = 1.75;
float robotHipCubeDepth = 1.5;

// Leg Measurements
float robotLegWidth = 3.0;
float robotLegLength = 10.0;
float robotLegDepth = 2.5;
float robotKneeWidth = 3.5;
float robotKneeLength = 2.75;
float robotKneeDepth = 2.5;
float robotFeetWidth = 3.5;
float robotFeetLength = 1.0;
float robotFeetDepth = 4.25;

// Joint Angles
float robotAngle = 0.0;
float upperAngle = 0.0;
float headAngle = 0.0;
float leftArmAngle = 0.0;
float rightArmAngle = 270.0;
float cannonAngle = 90.0;
float cannonSpinAngle = 0.0;
float hipAngle = 0.0;
float leftLegAngle = 0.0;
float rightLegAngle = 0.0;

enum Joint { ROBOT, UPPER_BODY, HEAD, LEFT_ARM, RIGHT_ARM, HIP, LEFT_LEG, RIGHT_LEG, NONE }; // Possible joint values (for adjusting joint angles)
Joint activeJoint = NONE; // Holds the current join, when NONE -> no joint is selected

// Flags
bool cannonStop = true;
bool walkStop = true;
bool walkFlag = true; // true = right leg step | false = left leg step

GLUquadric* robotQuadric; // For robotQuadric surfaces

// Colours
// Lights
GLfloat robotLight_position0[] = { 4.0F, 8.0F, 8.0F, 1.0F };
GLfloat robotLight_position1[] = { 4.0F, 8.0F, 8.0F, 1.0F };
GLfloat robotLight_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat robotLight_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat robotLight_ambient[] = { 0.2F, 0.2F, 0.2F, 1.0F };

// Robot Blue
GLfloat robotBlue_ambient[] = { 0.101f,0.146f,0.229f,1.0f };
GLfloat robotBlue_specular[] = { 0.337f,0.486f,0.765f,1.0f };
GLfloat robotBlue_diffuse[] = { 0.101f,0.146f,0.229f,1.0f };
GLfloat robotBlue_shininess[] = { 32.0F };

// Robot Grey
GLfloat robotGrey_ambient[] = { 0.133f,0.16f,0.169f,1.0f };
GLfloat robotGrey_specular[] = { 0.443f,0.533f,0.565f,1.0f };
GLfloat robotGrey_diffuse[] = { 0.222f,0.267f,0.282f,1.0f };
GLfloat robotGrey_shininess[] = { 32.0F };

// Robot Red
GLfloat robotRed_ambient[] = { 0.247f,0.066f,0.038f,1.0f };
GLfloat robotRed_specular[] = { 0.824f,0.220f,0.125f,1.0f };
GLfloat robotRed_diffuse[] = { 0.412f,0.110f,0.063f,1.0f };
GLfloat robotRed_shininess[] = { 32.0F };

// Robot White
GLfloat robotWhite_ambient[] = { 0.251f,0.268f,0.262f,1.0f };
GLfloat robotWhite_specular[] = { 0.835f,0.894f,0.875f,1.0f };
GLfloat robotWhite_diffuse[] = { 0.418f,0.447f,0.438f,1.0f };
GLfloat robotWhite_shininess[] = { 32.0F };

// Robot Yellow
GLfloat robotYellow_ambient[] = { 0.274f,0.194f,0.045f,1.0f };
GLfloat robotYellow_diffuse[] = { 0.913f,0.647f,0.149f,1.0f };
GLfloat robotYellow_specular[] = { 0.457f,0.324f,0.075f,1.0f };
GLfloat robotYellow_shininess[] = { 32.0F };

void drawRobot() {
	glPushMatrix();
		//glTranslatef(x, y, z); // Move to initial position
		glRotatef(robotAngle, 0.0, 1.0, 0.0); // Ensures that the entire robot moves with the robot angle
		glPushMatrix();
			glRotatef(upperAngle, 0.0, 1.0, 0.0); // Ensures that the entire upper body moves with the upper angle
			drawBody();
			drawHead();
			drawLeftArm();
			drawRightArm();
		glPopMatrix();
		drawHip();
		drawLeftLeg();
		drawRightLeg();
	glPopMatrix();
}

// BASE PART
void drawBody() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, robotBlue_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotBlue_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotBlue_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotBlue_shininess);

	glPushMatrix();
		glTranslatef(0.0, 0.95, 0.0);
		glScalef(robotBodyWidth, robotBodyLength, robotBodyDepth);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 1.7, 1.0);
		glPushMatrix();
			glRotatef(45, 1.0, 0.0, 0.0);
			glScalef(robotBodyChestWidth, robotBodyChestLength, robotBodyChestDepth);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 0.325, 1.5);
		glPushMatrix();
			glRotatef(15, 1.0, 0.0, 0.0);
			glScalef(robotBodyMiddleWidth, robotBodyMiddleLength, robotBodyMiddleDepth);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, robotYellow_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotYellow_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotYellow_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotYellow_shininess);

	glPushMatrix();
		glTranslatef(2.5, 1.5, 2.0);
		glPushMatrix();
			glRotatef(45, 1.0, 0.0, 0.0);
			glScalef(robotBodyChestCubeWidth, robotBodyChestCubeLength, robotBodyChestCubeDepth);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.5, 1.5, 2.0);
		glPushMatrix();
			glRotatef(45, 1.0, 0.0, 0.0);
			glScalef(robotBodyChestCubeWidth, robotBodyChestCubeLength, robotBodyChestCubeDepth);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, robotRed_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotRed_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotRed_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotRed_shininess);

	glPushMatrix();
		glTranslatef(0.0, -2.45, 0.0);
		glPushMatrix();
			glScalef(robotBodyWaistWidth, robotBodyWaistLength, robotBodyWaistDepth);
			glutSolidCube(1.0);
		glPopMatrix();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, robotGrey_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotGrey_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotGrey_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotGrey_shininess);

	glPushMatrix();
		glTranslatef(0.0, 0.6, -2.0);
		glScalef(robotBodyBackpackWidth, robotBodyBackpackLength, robotBodyBackpackDepth);
		glutSolidCube(1.0);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, robotWhite_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, robotWhite_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, robotWhite_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, robotWhite_shininess);

	glPushMatrix();
		glTranslatef(-3.65, 6.0, -2.25);
		glPushMatrix();
			glRotatef(90, 1.0, 0.0, 0.0);
			glRotatef(30, 0.0, 1.0, 0.0);
			robotQuadric = gluNewQuadric();
			gluCylinder(robotQuadric, robotBodyCylinderRadiusTop, robotBodyCylinderRadiusBottom, robotBodyCylinderDepth, 20, 20);
			gluDisk(robotQuadric, 0.0, robotBodyCylinderRadiusTop, 100, 100);
			gluDeleteQuadric(robotQuadric);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.65, 6.0, -2.25);
		glPushMatrix();
			glRotatef(90, 1.0, 0.0, 0.0);
			glRotatef(-30, 0.0, 1.0, 0.0);
			robotQuadric = gluNewQuadric();
			gluCylinder(robotQuadric, robotBodyCylinderRadiusTop, robotBodyCylinderRadiusBottom, robotBodyCylinderDepth, 20, 20);
			gluDisk(robotQuadric, 0.0, robotBodyCylinderRadiusTop, 20, 1);
			gluDeleteQuadric(robotQuadric);
		glPopMatrix();
	glPopMatrix();
}

void drawHead() {
	glPushMatrix();
		glRotatef(headAngle, 0.0, 1.0, 0.0);

		glMaterialfv(GL_FRONT, GL_AMBIENT, robotWhite_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, robotWhite_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, robotWhite_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, robotWhite_shininess);

		glPushMatrix();
			glTranslatef(0.0, (0.5 * 7.0 + 0.5 * robotHeadLength), 0.0);
			glPushMatrix();
				glScalef(robotHeadWidth, robotHeadLength, robotHeadDepth);
				glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, (0.5 * 7.0 + robotHeadLength + 0.1), 0.05);
			glPushMatrix();
				glScalef(robotHeadBandWidth, robotHeadBandLength, robotHeadBandDepth);
				glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, (0.5 * 7.0 + robotHeadLength - 0.1), -1.55);
			glPushMatrix();
				glScalef(robotHeadBandBackWidth, robotHeadBandBackLength, robotHeadBandBackDepth);
				glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.1, (0.5 * 7.0 + robotHeadLength - 0.4), 1.75);
			glPushMatrix();
				glRotatef(-90, 1.0, 0.0, 0.0);
				glRotatef(50, 0.0, 1.0, 0.0);
				glutSolidCone(robotHeadAntennaRadius, robotHeadAntennaLength, 20, 20);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.1, (0.5 * 7.0 + robotHeadLength - 0.4), 1.75);
			glPushMatrix();
				glRotatef(-90, 1.0, 0.0, 0.0);
				glRotatef(-50, 0.0, 1.0, 0.0);
				glutSolidCone(robotHeadAntennaRadius, robotHeadAntennaLength, 20, 20);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.1, (0.5 * 7.0 + robotHeadLength - 0.45), 1.75);
			glPushMatrix();
				glRotatef(90, 1.0, 0.0, 0.0);
				glRotatef(65, 0.0, 1.0, 0.0);
				glutSolidCone(robotHeadBrowRadius, robotHeadBrowLength, 20, 20);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.1, (0.5 * 7.0 + robotHeadLength - 0.45), 1.75);
			glPushMatrix();
				glRotatef(90, 1.0, 0.0, 0.0);
				glRotatef(-65, 0.0, 1.0, 0.0);
				glutSolidCone(robotHeadBrowRadius, robotHeadBrowLength, 20, 20);
			glPopMatrix();
		glPopMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, robotRed_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, robotRed_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, robotRed_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, robotRed_shininess);

		glPushMatrix();
			glTranslatef(0.0, (0.5 * 7.0 + robotHeadLength - 0.4), 1.8);
			glPushMatrix();
				glScalef(robotHeadRedTopWidth, robotHeadRedTopLength, robotHeadRedTopDepth);
				glutSolidOctahedron();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, (0.5 * 7.0 + robotHeadLength - 2.9), 1.75);
			glPushMatrix();
				glScalef(robotHeadRedBottomWidth, robotHeadRedBottomLength, robotHeadRedBottomDepth);
				glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, robotYellow_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, robotYellow_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, robotYellow_diffuse);
		glMaterialfv(GL_FRONT, GL_SHININESS, robotYellow_shininess);

		glPushMatrix();
			glTranslatef(0.45, (0.5 * 7.0 + robotHeadLength - 0.9), 1.75);
			glPushMatrix();
				glRotatef(-10, 0.0, 0.0, 1.0);
				glScalef(robotHeadEyeWidth, robotHeadEyeLength, robotHeadEyeDepth);
				glutSolidDodecahedron();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.45, (0.5 * 7.0 + robotHeadLength - 0.9), 1.75);
			glPushMatrix();
				glRotatef(10, 0.0, 0.0, 1.0);
				glScalef(robotHeadEyeWidth, robotHeadEyeLength, robotHeadEyeDepth);
				glutSolidDodecahedron();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void drawLeftArm() {
	glPushMatrix();
		glTranslatef(-(0.5 * robotBodyWidth + 0.5 * robotArmWidth), (0.35 * robotArmLength), 0.0);
		glRotatef(leftArmAngle, 1.0, 0.0, 0.0);
		glTranslatef((0.5 * robotBodyWidth + 0.5 * robotArmWidth), -(0.35 * robotArmLength), 0.0);

		glTranslatef((0.5 * robotBodyWidth + 0.5 * robotArmWidth + 0.4), 0.0, 0.0);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, robotWhite_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotWhite_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotWhite_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotWhite_shininess);

			glPushMatrix();
				glTranslatef(0.0, -1.25, 0.0);
				glPushMatrix();
					glScalef(robotArmWidth, robotArmLength, robotArmDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 2.6, 0.0);
				glPushMatrix();
					glScalef(robotShoulderWidth, robotShoulderLength, robotShoulderDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glMaterialfv(GL_FRONT, GL_AMBIENT, robotGrey_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotGrey_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotGrey_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotGrey_shininess);

			glPushMatrix();
				glTranslatef(0.0, -6.0, 0.0);
				glPushMatrix();
					glScalef(robotHandWidth, robotHandLength, robotHandDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void drawRightArm() {
	glPushMatrix();
		glTranslatef(-(0.5 * robotBodyWidth + 0.5 * robotArmWidth), (0.35 * robotArmLength), 0.0);
		glRotatef(rightArmAngle, 1.0, 0.0, 0.0);
		glTranslatef((0.5 * robotBodyWidth + 0.5 * robotArmWidth), -(0.35 * robotArmLength), 0.0);

		glTranslatef(-(0.5 * robotBodyWidth + 0.5 * robotArmWidth + 0.4), 0.0, 0.0);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, robotWhite_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotWhite_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotWhite_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotWhite_shininess);

			glPushMatrix();
				glTranslatef(0.0, -1.25, 0.0);
				glPushMatrix();
					glScalef(robotArmWidth, robotArmLength, robotArmDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 2.6, 0.0);
				glPushMatrix();
					glScalef(robotShoulderWidth, robotShoulderLength, robotShoulderDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glMaterialfv(GL_FRONT, GL_AMBIENT, robotGrey_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotGrey_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotGrey_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotGrey_shininess);

			glPushMatrix();
				glTranslatef(0.0, -6.0, 0.0);
				glPushMatrix();
					glScalef(robotHandWidth, robotHandLength, robotHandDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();

				glTranslatef(0.0, -(0.25 * robotArmLength - 1.0), (0.7 * robotArmWidth + 1.0));
				glRotatef(cannonAngle, 1.0, 0.0, 0.0);

				glPushMatrix();
					robotQuadric = gluNewQuadric();
					gluCylinder(robotQuadric, robotCannonCylinderRadiusTop, robotCannonCylinderRadiusBottom, robotCannonCylinderDepth, 20, 20);
					gluDisk(robotQuadric, 0.0, robotCannonCylinderRadiusTop, 20, 1);

					glMaterialfv(GL_FRONT, GL_AMBIENT, robotRed_ambient);
					glMaterialfv(GL_FRONT, GL_SPECULAR, robotRed_specular);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, robotRed_diffuse);
					glMaterialfv(GL_FRONT, GL_SHININESS, robotRed_shininess);

					glPushMatrix();
						glTranslatef(0.0, 0.0, 1.0);
						gluDisk(robotQuadric, 0.0, robotCannonCylinderRadiusTop, 20, 1);
					glPopMatrix();
					gluDeleteQuadric(robotQuadric);
				glPopMatrix();

				glMaterialfv(GL_FRONT, GL_AMBIENT, robotGrey_ambient);
				glMaterialfv(GL_FRONT, GL_SPECULAR, robotGrey_specular);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, robotGrey_diffuse);
				glMaterialfv(GL_FRONT, GL_SHININESS, robotGrey_shininess);

				glPushMatrix();
					glTranslatef(0.0, 0.0, 7.25);
					glutSolidTorus(cannonTorusRadiusInner, cannonTorusRadiusOuter, 20, 20);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0.0, -0.4, 0.1);
					glPushMatrix();
						glScalef(cannonArmWidth, cannonArmLength, cannonArmDepth);
						glutSolidCube(1.0);
					glPopMatrix();
				glPopMatrix();

				glPushMatrix();
					glMaterialfv(GL_FRONT, GL_AMBIENT, robotRed_ambient);
					glMaterialfv(GL_FRONT, GL_SPECULAR, robotRed_specular);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, robotRed_diffuse);
					glMaterialfv(GL_FRONT, GL_SHININESS, robotRed_shininess);

					glRotatef(cannonSpinAngle, 0.0, 0.0, 1.0);
					glTranslatef(0.0, 0.0, 0.1);
					glPushMatrix();
						glTranslatef(0.0, 0.0, 0.0);
						glPushMatrix();
							robotQuadric = gluNewQuadric();
							gluCylinder(robotQuadric, robotCannonCylinderMiniRadiusTop, robotCannonCylinderMiniRadiusBottom, robotCannonCylinderMiniDepth, 20, 20);
							gluDisk(robotQuadric, 0.0, robotCannonCylinderMiniRadiusTop, 20, 1);
							gluDeleteQuadric(robotQuadric);
						glPopMatrix();
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0.7, 0.0, 0.0);
						glPushMatrix();
							robotQuadric = gluNewQuadric();
							gluCylinder(robotQuadric, robotCannonCylinderMiniRadiusTop, robotCannonCylinderMiniRadiusBottom, robotCannonCylinderMiniDepth, 20, 20);
							gluDisk(robotQuadric, 0.0, robotCannonCylinderMiniRadiusTop, 20, 1);
							gluDeleteQuadric(robotQuadric);
						glPopMatrix();
					glPopMatrix();

					glPushMatrix();
						glTranslatef(-0.7, 0.0, 0.0);
						glPushMatrix();
							robotQuadric = gluNewQuadric();
							gluCylinder(robotQuadric, robotCannonCylinderMiniRadiusTop, robotCannonCylinderMiniRadiusBottom, robotCannonCylinderMiniDepth, 20, 20);
							gluDisk(robotQuadric, 0.0, robotCannonCylinderMiniRadiusTop, 20, 1);
							gluDeleteQuadric(robotQuadric);
						glPopMatrix();
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0.0, 0.7, 0.0);
						glPushMatrix();
							robotQuadric = gluNewQuadric();
							gluCylinder(robotQuadric, robotCannonCylinderMiniRadiusTop, robotCannonCylinderMiniRadiusBottom, robotCannonCylinderMiniDepth, 20, 20);
							gluDisk(robotQuadric, 0.0, robotCannonCylinderMiniRadiusTop, 20, 1);
							gluDeleteQuadric(robotQuadric);
						glPopMatrix();
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0.0, -0.7, 0.0);
						glPushMatrix();
							robotQuadric = gluNewQuadric();
							gluCylinder(robotQuadric, robotCannonCylinderMiniRadiusTop, robotCannonCylinderMiniRadiusBottom, robotCannonCylinderMiniDepth, 20, 20);
							gluDisk(robotQuadric, 0.0, robotCannonCylinderMiniRadiusTop, 20, 1);
							gluDeleteQuadric(robotQuadric);
						glPopMatrix();
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0.5, 0.5, 0.0);
						glPushMatrix();
							robotQuadric = gluNewQuadric();
							gluCylinder(robotQuadric, robotCannonCylinderMiniRadiusTop, robotCannonCylinderMiniRadiusBottom, robotCannonCylinderMiniDepth, 20, 20);
							gluDisk(robotQuadric, 0.0, robotCannonCylinderMiniRadiusTop, 20, 1);
							gluDeleteQuadric(robotQuadric);
						glPopMatrix();
					glPopMatrix();

					glPushMatrix();
						glTranslatef(-0.5, 0.5, 0.0);
						glPushMatrix();
							robotQuadric = gluNewQuadric();
							gluCylinder(robotQuadric, robotCannonCylinderMiniRadiusTop, robotCannonCylinderMiniRadiusBottom, robotCannonCylinderMiniDepth, 20, 20);
							gluDisk(robotQuadric, 0.0, robotCannonCylinderMiniRadiusTop, 20, 1);
							gluDeleteQuadric(robotQuadric);
						glPopMatrix();
					glPopMatrix();

					glPushMatrix();
						glTranslatef(0.5, -0.5, 0.0);
						glPushMatrix();
							robotQuadric = gluNewQuadric();
							gluCylinder(robotQuadric, robotCannonCylinderMiniRadiusTop, robotCannonCylinderMiniRadiusBottom, robotCannonCylinderMiniDepth, 20, 20);
							gluDisk(robotQuadric, 0.0, robotCannonCylinderMiniRadiusTop, 20, 1);
							gluDeleteQuadric(robotQuadric);
						glPopMatrix();
					glPopMatrix();

					glPushMatrix();
						glTranslatef(-0.5, -0.5, 0.0);
						glPushMatrix();
							robotQuadric = gluNewQuadric();
							gluCylinder(robotQuadric, robotCannonCylinderMiniRadiusTop, robotCannonCylinderMiniRadiusBottom, robotCannonCylinderMiniDepth, 20, 20);
							gluDisk(robotQuadric, 0.0, robotCannonCylinderMiniRadiusTop, 20, 1);
							gluDeleteQuadric(robotQuadric);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void drawHip() {
	glPushMatrix();
		glRotatef(hipAngle, 0.0, 1.0, 0.0);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, robotWhite_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotWhite_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotWhite_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotWhite_shininess);

			glPushMatrix();
				glTranslatef(0.0, -(1.655 * robotHipLength), 0.0);
				glPushMatrix();
					glScalef(robotHipWidth, robotHipLength, robotHipDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, -(1.655 * robotHipLength), 1.0);
				glPushMatrix();
					glScalef(robotHipMiddleWidth, robotHipMiddleLength, robotHipMiddleDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, -(1.655 * robotHipLength), -1.0);
				glPushMatrix();
					glScalef(robotHipMiddleWidth, robotHipMiddleLength, robotHipMiddleDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glMaterialfv(GL_FRONT, GL_AMBIENT, robotYellow_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotYellow_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotYellow_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotYellow_shininess);

			glPushMatrix();
				glTranslatef(2.25, -(1.655 * robotHipLength), 1.5);
				glPushMatrix();
					glScalef(robotHipCubeWidth, robotHipCubeLength, robotHipCubeDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-2.25, -(1.655 * robotHipLength), 1.5);
				glPushMatrix();
					glScalef(robotHipCubeWidth, robotHipCubeLength, robotHipCubeDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(2.25, -(1.655 * robotHipLength), -1.5);
				glPushMatrix();
					glScalef(robotHipCubeWidth, robotHipCubeLength, robotHipCubeDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-2.25, -(1.655 * robotHipLength), -1.5);
				glPushMatrix();
					glScalef(robotHipCubeWidth, robotHipCubeLength, robotHipCubeDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void drawLeftLeg() {
	glPushMatrix();
		glTranslatef((0.325 * robotHipWidth), (-0.725 * robotLegLength), 0.0);
		glRotatef(leftLegAngle, 1.0, 0.0, 0.0);
		glTranslatef(-(0.325 * robotHipWidth), -(-0.725 * robotLegLength), 0.0);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, robotWhite_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotWhite_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotWhite_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotWhite_shininess);

			glPushMatrix();
				glTranslatef((0.325 * robotHipWidth), -(1.655 * robotHipLength + 6.5), 0.0);
				glPushMatrix();
					glScalef(robotLegWidth, robotLegLength, robotLegDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef((0.325 * robotHipWidth), -(1.655 * robotHipLength + 6.5 + 0.5), 0.5);
				glPushMatrix();
					glScalef(robotKneeWidth, robotKneeLength, robotKneeDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glMaterialfv(GL_FRONT, GL_AMBIENT, robotRed_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotRed_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotRed_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotRed_shininess);

			glPushMatrix();
				glTranslatef((0.325 * robotHipWidth), -(1.655 * robotHipLength + 6.5 + 4.5), 0.75);
				glPushMatrix();
					glScalef(robotFeetWidth, robotFeetLength, robotFeetDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void drawRightLeg() {
	glPushMatrix();
		glTranslatef((0.325 * robotHipWidth), (-0.725 * robotLegLength), 0.0);
		glRotatef(rightLegAngle, 1.0, 0.0, 0.0);
		glTranslatef(-(0.325 * robotHipWidth), -(-0.725 * robotLegLength), 0.0);
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, robotWhite_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotWhite_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotWhite_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotWhite_shininess);

			glPushMatrix();
				glTranslatef(-(0.325 * robotHipWidth), -(1.655 * robotHipLength + 6.5), 0.0);
				glPushMatrix();
					glScalef(robotLegWidth, robotLegLength, robotLegDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-(0.325 * robotHipWidth), -(1.655 * robotHipLength + 6.5 + 0.5), 0.5);
				glPushMatrix();
					glScalef(robotKneeWidth, robotKneeLength, robotKneeDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();

			glMaterialfv(GL_FRONT, GL_AMBIENT, robotRed_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, robotRed_specular);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, robotRed_diffuse);
			glMaterialfv(GL_FRONT, GL_SHININESS, robotRed_shininess);

			glPushMatrix();
				glTranslatef(-(0.325 * robotHipWidth), -(1.655 * robotHipLength + 6.5 + 4.5), 0.75);
				glPushMatrix();
					glScalef(robotFeetWidth, robotFeetLength, robotFeetDepth);
					glutSolidCube(1.0);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}