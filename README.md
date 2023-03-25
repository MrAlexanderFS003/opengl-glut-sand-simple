# SAND SIMPLE
## Solucion a Errores y otros
Al momento de querer ejecutar el programa les saldra un error, pero tranquilos, este error tiene una solución sencilla,
para solucionarlo tenemos que seguir lo siguiente:
> Copia lo siguiente: _CRT_SECURE_NO_WARNINGS

![Solucion](https://user-images.githubusercontent.com/96871746/212933383-9f5548fb-c07f-4a61-9e86-019d7020e7e3.gif)

### Modificar fuente de letras
El siguiente código solo es para ejemplo , no esta completo.
Para modificar la fuente de letra nos guiaremos de esta pag.

> https://www.opengl.org/resources/libraries/glut/spec3/node76.html#SECTION000111000000000000000

Cada *font_style* guarda el tipo de fuente de la letra , quizas no hay muchas fuentes , pero hay librerias que ayudan con mas variedad.
```C++
void Texto::printw(int val, float x, float y, float z, const char* format, ...) {
	if (val == 1) {
		font_style = GLUT_BITMAP_TIMES_ROMAN_10; 
	}
	else {
		font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	}
}
```
## LOGICA : Movimiento de la Arena
Cada cuadrado de arena tine una logica simple. Al momento de caer tiene que preguntarse si hay alguien y si esta vacio, este objeto se mueve a una posicion del plano.
Para este proyecto se uso el "glOrtho()" (configurar el plano) y para crear los cuadrados se uso "glRectd()", entonces el plano estaria de la siguiente forma:

![GIF](https://user-images.githubusercontent.com/96871746/227692947-e9e0338b-93bf-40e3-ab39-ed04b1e9369e.gif)

Teniendo esto en cuenta podremos darnos cuenta que el plano es diferente al plano cartesiano que normalmente conocemos (El 0,0 esta en la interseccion de las dos rectas). Entonces para la logica de la arena:
- Primero: Analizamos si esta colisionando con la arena. Esta puede ser Arena anterior y Arena actual, cada una de ellas se analizan una detras de otra.
> La arena anterior vendria hacer la arena que ya esta en el suelo o limite del plano y la Arena actual es la que recientemente se a creado y que aun esta cayendo.

- Segundo: Al haber colision Arena Actual y Arena Anterior, hay 3 posibles movimientos [ Izquierda , derecha y centro ] donde solo 1 de cualquiera de los 3 se debe cumplir.

Para entender esto se tiene lo siguiente:

![GIF2](https://user-images.githubusercontent.com/96871746/227695296-776a0faa-52e7-4e9d-84dc-6ea5ddf4dca5.gif)

### CONTROLES
-> RATON:
- Click izquierdo Crea Arena/Muro.

-> Teclado:

- k: Habilita creacion de arena y desabilita creacion de muro.
- l: Habilita creacion de muro y desabilita creacion de arena.
- b: Habilita Borrador.
- v: Desabilita Borrador.
- e: Habilita la logica de los objetos
- q: Desabilita la logica de los objetos

# EJECUCION DEL PROGRAMA
## Arena
![Arena](https://user-images.githubusercontent.com/96871746/227695486-4d22271a-19c4-434b-8fb1-59ea67ee0c31.gif)

## Arena y Muro
![Muro](https://user-images.githubusercontent.com/96871746/227695496-4441dc4c-4ae9-4909-b8e7-5617928784dc.gif)
