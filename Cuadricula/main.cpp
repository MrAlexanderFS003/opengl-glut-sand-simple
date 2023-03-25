/*
	Hecho por Max Flores Saldaña , Usando la programación orientada a Objetos en C++.
	Si desea ver la documentacion de GLUT: https://www.opengl.org/resources/libraries/glut/spec3/spec3.html
*/

#include "Cuadrado.h"
#include "Pared.h"
#include "Texto.h"
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <thread>

//Tamaño de la ventana
#define ANCHO 800
#define ALTO 600

//Tamaño de la Cuadricula
#define COLUMNAS 30
#define FILAS 30
#define TAMPLANO 30

using namespace std;

Cuadrado cuad;
vector<Cuadrado>Sand;

Cuadrado Guia;
Texto txt;

Pared muro;
vector<Pared>Ladrillo;

//Variables usadas para almacenar los calculos obtenidos
float objX = 0.0f, objY = 0.0f, MobjX = 0.0f, MobjY = 0.0f;
int valor = 0, tam = 0;
bool bandera = false, badBorra = false, BadInicia = false;
bool pulsa = false, MuroPinta = false;
// Borrar Objetos
float posXBor = 0.0f;
float posYBor = 0.0f;
//Posicion de Puntero/Raton
float posXPun = 0.0f;
float posYPun = 0.0f;

// Calcular FPS
int frameCount = 0;
int currentTime = 0;
int previousTime = 0;
//Convierte int a char*
int prefps  = 0;
string tempfps;
const char* f_ps;

void Init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Cuadricula() {
	glColor3ub(175, 175, 175);
	glLineWidth(1.0);
	for (int x = 0; x < COLUMNAS; x++) {
		for (int y = 0; y < FILAS; y++) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(x, y);
			glVertex2f(x + 1, y);
			glVertex2f(x + 1, y + 1);
			glVertex2f(x, y + 1);
			glEnd();
			
		}
	}
}

/// Compara la posicion de la Arena anterior con el movimiento preventivo de la arena actual
bool Compara(int &p2x, int &p2y) {
	for (int i = 0; i < Sand.size(); i++) {
		if (Sand[i].getPosX() == p2x && Sand[i].getPosY() == p2y) { return true; }
	}
	return false;
}

/// Compara La arena actual con el Muro
bool ComparaMuro(int& p2x, int& p2y) {
	for (int i = 0; i < Ladrillo.size(); i++) {
		if (Ladrillo[i].getPosX() == p2x && Ladrillo[i].getPosY() == p2y) { return true; }
	}
	return false;
}

/// Cada Arena tiene 3 movimiento: derecha, izquierda y centro, estos movimientos seran 
/// Evaluados si no se cumple devuelve un "false". 
bool Reubica(int j, int& xder, int& yder, int& xizq, int& yizq, int& xcen, int& ycen) {

	if (Compara(xder, yder) == false && xder < TAMPLANO) {
		Sand[j].setPosX(xder);
		Sand[j].setPosY(yder);
	}
	else {
		if (Compara(xizq, yizq) == false && xizq > -1 ) {
			Sand[j].setPosX(xizq);
			Sand[j].setPosY(yizq);
		}
		else {
			if (Compara(xcen, ycen) == false) {
				Sand[j].setPosY(static_cast<int>(Sand[j].getPosY() + 1));
			}
			else {
				if (ComparaMuro(xder, yder) == false ) { // Compara si hay un Muro a la derecha
					xder = xder + 1; yder = yder - 1;
				}
				else {
					if (ComparaMuro(xizq, yizq) == false) { // Compara si hay un Muro a la izquierda
						xizq = xizq - 1; yizq = yizq - 1;
					}
				}
				ycen = ycen - 1;
				Reubica(j, xder, yder, xizq, yizq, xcen, ycen);

			}
		}
	}
	return false;
}

/// Movimiento de la Arena
void MoveSand() {
	for (int i = 0; i < Sand.size(); i++) { // Objeto anterior
		for (int j = i + 1; j < Sand.size(); j++) { // Objeto actual

			// Variable para calcular si hay colision : Arena a Muro
			int Mx = Sand[j].getPosX();
			int My = Sand[j].getPosY();

			//Variables para evaluar si hay un objeto a la derecha
			int tempXder = Sand[j].getPosX() + 1;
			int tempYder = Sand[j].getPosY();
			//Variables para evaluar si hay un objeto a la izquierda
			int tempXizq = Sand[j].getPosX() - 1;
			int tempYizq = Sand[j].getPosY();
			//Variables para evaluar si hay un objeto en el centro
			int tempXcen = Sand[j].getPosX();
			int tempYcen = Sand[j].getPosY() - 1;

			if (ComparaMuro(Mx, My) == true) {
				Sand[j].setVelocidad(0.0f);
			}

			if (Sand[i].getPosX() == Sand[j].getPosX() && Sand[i].getPosY() == Sand[j].getPosY() == true) {
				Sand[j].setVelocidad(0.0f);
				if (Reubica(j,tempXder, tempYder, tempXizq, tempYizq, tempXcen, tempYcen) == false) {
					Sand[j].setVelocidad(1.0f);
				}
			}
		}
	}
}

void TextoEnPantalla() {
	glPushMatrix();
	glColor3ub(255, 255, 255);

	//Convirtiendo Numeros a Texto (X)
	string tex = "FPS: " + to_string(prefps);
	const char* texc= tex.c_str();

	//txt.printw(Tipo de fuente de letra, x, y, z, texto a dibujar)
	txt.printw(2, COLUMNAS / 2, FILAS - 5, 0, texc);
	glPopMatrix();
}


void Dibuja() {
	glClear(GL_COLOR_BUFFER_BIT);

	//Cuadricula();

	glPushMatrix();
	
	// Dibuja La arena
	if (Sand.size() != NULL) {
		for (int i = 0; i < Sand.size(); i++) {
			Sand[i].Dibuja();
			if (BadInicia == true) { Sand[i].Actualiza(); }
			if (badBorra == true) {
				if (Sand[i].getPosX() == Guia.getPosX() && Sand[i].getPosY() == Guia.getPosY()) {
					Sand.erase(Sand.begin() + i);
				}
			}
		}
	}

	//Dibuja el muro
	if (Ladrillo.size() != NULL) {
		for (int i = 0; i < Ladrillo.size(); i++) {
			Ladrillo[i].Dibuja();
			if (badBorra == true) {
				if (Ladrillo[i].getPosX() == Guia.getPosX() && Ladrillo[i].getPosY() == Guia.getPosY()) {
					Ladrillo.erase(Ladrillo.begin() + i);
				}
			}
		}
	}

	Guia.Puntero(); // Puntero/Cuadro para saber la posicion  donde se genera la arena/Muro.

	glPopMatrix();

	TextoEnPantalla();

	glutSwapBuffers();
	frameCount++;

	// Medimos el tiempo transcurrido desde el último fotograma
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = currentTime - previousTime;
	if (timeInterval > 1000) {
		// Calculamos el número de cuadros por segundo
		float fps = frameCount / (timeInterval / 1000);
		prefps = fps;
		previousTime = currentTime;
		frameCount = 0;
	}
	this_thread::sleep_for(chrono::milliseconds(5)); // Configurado a 60 fps
}

void Actualiza() { 
	if (BadInicia == true) { 
		MoveSand(); 
	} 
	glutPostRedisplay(); 
}

void CasosColor(int opc) {
	switch (opc) {
	case 0:
		cuad.setRGB(255, 255, 0);
		break;
	case 1:
		cuad.setRGB(255, 231, 0);
		break;
	case 2:
		cuad.setRGB(255, 203, 0);
		break;
	case 3:
		cuad.setRGB(255, 162, 0);
		break;
	default:
		break;
	}
}

//Posicion del raton
void Raton(int btn, int state, int x, int y) {
	valor = 1;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		// Escalar las coordenadas del ratón para que correspondan a la proyección
		float scaleX = TAMPLANO / (double)ANCHO;
		float scaleY = TAMPLANO / (double)ALTO;
		float mouseX = x * scaleX;
		float mouseY = (ALTO - y) * scaleY;
		// Convertir las coordenadas escaladas a coordenadas de ventana OpenGL
		float winX = static_cast<int>(mouseX);
		float winY = static_cast<int>(mouseY);

		Guia.setPosX(winX);
		Guia.setPosY(winY);

		cuad.setPosX(winX);
		cuad.setPosY(winY);

		if (MuroPinta == true) {
			muro.setPosX(winX);
			muro.setPosY(winY);
			Ladrillo.emplace_back(muro);
		}
		
		/*
		for (int i = 0; i < 20; i++) {
			// Radio = (rand() % 10)
			cuad.setPosX(winX + static_cast<int>((rand() % 10) * cos(i)));
			cuad.setPosY(winY + static_cast<int>((rand() % 10) * sin(i)));
			cuad.setVelocidad(0.1f);
			int cRGB = rand() % 4;
			CasosColor(cRGB);
			Sand.emplace_back(cuad);
		}
		*/
	}
}

//Movimiento de la figura en base al raton
int pass = 0;
void MoverRaton(int x, int y) {
	if (valor) {
		Guia.setPosX(MobjX);
		Guia.setPosY(MobjY);		
	}
	int temCuadX = cuad.getPosX();
	int temCuadY = cuad.getPosY();
	if (temCuadX != Guia.getPosX() && temCuadY != Guia.getPosY() + 1 || temCuadX != Guia.getPosX() + 1 && temCuadY != Guia.getPosY()) { pass = 1; }
	else { pass = 0; }

	if (pulsa == true && valor &&  pass == 1) {
		cuad.setPosX(MobjX);
		cuad.setPosY(MobjY);
		cuad.setVelocidad(1.0f);
		int cRGB = rand() % 4;
		CasosColor(cRGB);
		Sand.emplace_back(cuad);	
	}
	// Escalar las coordenadas del ratón para que correspondan a la proyección
	float scaleX = TAMPLANO / (double)ANCHO;
	float scaleY = TAMPLANO / (double)ALTO;
	float mouseX = x * scaleX;
	float mouseY = (ALTO - y) * scaleY;

	// Convertir las coordenadas escaladas a coordenadas de ventana OpenGL
	MobjX = static_cast<int>(mouseX);
	MobjY = static_cast<int>(mouseY);
	objX = MobjX;
	objY = MobjY;
	
}

void Teclado(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 'e':
		BadInicia = true;
		break;
	case 'q':
		BadInicia = false;
		break;
	case 'b':
		badBorra = true;
		break;
	case 'v':
		badBorra = false;
		break;
	case 'x':
		Sand.clear();
		break;
	case 'k':
		pulsa = true;
		MuroPinta = false;
		break;
	case 'l':
		pulsa = false;
		MuroPinta = true;
		break;
	case 27:
		exit(0);
		Sand.clear();
		Ladrillo.clear();
	default:
		break;
	}
}


void redimensionar(int w, int h) {
	glutReshapeWindow(ANCHO, ALTO); // Evita que la ventana se maximize
}

int main() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(ANCHO, ALTO);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("CUADRICULA");

	Init();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMNAS, 1.0f, FILAS, -1.0f, 1.0f);
	Sand.reserve(1000000);

	//glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(Dibuja);
	glutIdleFunc(Actualiza);
	glutReshapeFunc(redimensionar);
	glutKeyboardFunc(Teclado);
	glutMouseFunc(Raton); // Posicion del raton
	glutPassiveMotionFunc(MoverRaton);
	glutMainLoop();
	return 0;
}