#include <GL/glut.h>
#include <vector>
#include <vertex.h>
#include <objetos.h>

/*
	Métodos con los movimientos del objeto jerárquico.
*/


/* Métodos para dibujar piezas Android */
void Dibujar_Android(char modo, Objeto3D esfera_ojos, Objeto3D esfera_cabeza, Objeto3D cilindro);

void dibujar_cabeza(char modo, Objeto3D esfera_cabeza);

void dibujar_ojoDerecho(char modo, Objeto3D esfera_ojos);
void dibujar_ojoIzquierdo(char modo, Objeto3D esfera_ojos);

void dibujar_antenaDerecha(char modo, Objeto3D cilindro);
void dibujar_antenaIzquierda(char modo, Objeto3D cilindro);

void dibujar_torso(char modo, Objeto3D cilindro);

void dibujar_brazoDerecho(char modo, Objeto3D cilindro);
void dibujar_brazoIzquierdo(char modo, Objeto3D cilindro);

void dibujar_piernaDerecha(char modo, Objeto3D cilindro);
void dibujar_piernaIzquierda(char modo, Objeto3D cilindro);

/* ---------------------------*/
	
void DERECHA_girarCabeza();
void IZQUIERDA_girarCabeza();

void DERECHA_girarCintura();
void IZQUIERDA_girarCintura();

void DERECHA_moverAntena_izq();
void IZQUIERDA_moverAntena_izq();

void estirarAntenas();
void recogerAntenas();

void DERECHA_moverAntena_dcha();
void IZQUIERDA_moverAntena_dcha();

void ARRIBA_moverBrazo_izq();
void ABAJO_moverBrazo_izq();

void ARRIBA_moverBrazo_dcho();
void ABAJO_moverBrazo_dcho();
