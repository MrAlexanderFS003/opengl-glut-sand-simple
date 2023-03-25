#include "Texto.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <GL/glut.h>

int Texto::window_width = 800;
int Texto::window_height = 600;

Texto::Texto() {}

void Texto::display(void) {}

void Texto::reshape(int w, int h) {
	window_width = w;
	window_height = h;

	glViewport(0, 0, window_width, window_height);
}

void Texto::printw(int val, float x, float y, float z, const char* format, ...)
{
	va_list args;
	int len;
	int i;
	char* text;
	GLvoid* font_style;
	if (val == 1) {
		font_style = GLUT_BITMAP_TIMES_ROMAN_10;
	}
	else {
		font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	}

	va_start(args, format);

	len = _vscprintf(format, args) + 1;

	text = (char*)malloc(len * sizeof(char));

	vsprintf(text, format, args);
	va_end(args);

	glRasterPos3f(x, y, z);

	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	free(text);
}