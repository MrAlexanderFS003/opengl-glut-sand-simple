#pragma once
class Pared {
	float posX = 20, posY = 20; 
	int r = 2, g = 190, b = 113; 
public:
	Pared() {}
	void Dibuja();
	void Actualiza();

	//Setters y Getters
	void setPosX(float valor) { posX = static_cast<int>(valor); }
	void setPosY(float valor) { posY = static_cast<int>(valor); }

	float getPosX() { return static_cast<int>(posX); }
	float getPosY() { return static_cast<int>(posY); }

	void setRGB(int CodeR, int CodeG, int CodeB) { r = CodeR; g = CodeG; b = CodeB; }
	int getRGB() { return r + g + b; }
};
