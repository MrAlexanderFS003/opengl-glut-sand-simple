#pragma once
class Cuadrado {
	float posX = 20, posY = 20; 
	float velocidad = 1.0f; 
	int r = 255, g = 255, b = 0; 
public:
	Cuadrado() {}
	void Dibuja();
	void Puntero();
	void Actualiza();

	//Setters y Getters
	void setPosX(float valor) { posX = static_cast<int>(valor); }
	void setPosY(float valor) { posY = static_cast<int>(valor); }

	float getPosX() { return static_cast<int>(posX); }
	float getPosY() { return static_cast<int>(posY); }

	void setRGB(int CodeR, int CodeG, int CodeB) { r = CodeR; g = CodeG; b = CodeB; }
	int getRGB() { return r + g + b; }
	void setVelocidad(float valor) { velocidad = valor; }
};
