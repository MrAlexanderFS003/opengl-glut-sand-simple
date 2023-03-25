#include "Pared.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void Pared::Dibuja() {
	glPushMatrix();
	glColor3ub(r, g, b);
	glRectd(posX, posY, posX + 1, posY + 1.08f);
	glPopMatrix();
}

void Pared::Actualiza() {
	glutPostRedisplay();
}