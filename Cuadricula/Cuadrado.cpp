#include "Cuadrado.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void Cuadrado::Dibuja() {
	//Actualiza();
	glPushMatrix();
	glColor3ub(r, g, b);
	glRectd(posX, posY, posX + 1, posY + 1.08f);
	glPopMatrix();
}

void Cuadrado::Puntero() {
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glRectd(posX, posY, posX + 1, posY + 1);
	glPopMatrix();
}

void Cuadrado::Actualiza() {
	posY -= velocidad;

	if (posY < 1) { // Mover hacia abajo
		velocidad = 0.0f;
		posY = 1;
	}
	glutPostRedisplay(); 
}