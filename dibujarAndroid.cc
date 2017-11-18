/***************************************************
*	Desarrolladora: Tatiana Pastorini
*	Grado en Ingeniería Informática, UGR, ETSIIT.
*	Práctica 3. Modelos jerárquicos.
***************************************************/

#include <iostream>
#include <dibujar.h>
#include <dibujarAndroid.h>

using namespace std;

/*******************************************************/
/* Variables que controlan los movimientos del Android */
/*******************************************************/

int mover_antena_izq = 0;
int mover_antena_dcha = 0;
int mover_cabeza = 0;
int mover_torso = 0;
int mover_brazo_izq = 0;
int mover_brazo_dcho = 0;
float escalar_antenas = 0.0;

/*
*	Método que construye el objeto jerárquico Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param esfera_ojos, esfera que representará los ojos.
*	@param esfera_cabeza, media esfera que representará la cabeza.
*	@param cilindro, cilindro que representará brazos, torso y piernas.
*/
void Dibujar_Android(char modo, Objeto3D esfera_ojos, Objeto3D esfera_cabeza, Objeto3D cilindro){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(0,0.6,0);									// CENTRAR EL ANDROID 

		glPushMatrix();
			glRotatef(mover_torso,0,1,0);						// MOVER TORSO
			glPushMatrix();
				glRotatef(mover_cabeza,0,1,0);					// MOVER LA CABEZA
				dibujar_ojoDerecho(modo, esfera_ojos);			// OJO DERECHO ANDROID
				dibujar_ojoIzquierdo(modo, esfera_ojos);		// OJO IZQUIERDO ANDROID

				glPushMatrix();
					glRotatef(mover_antena_dcha,0,0,1);			// MOVER ANTENA DERECHA
					dibujar_antenaDerecha(modo, cilindro);		// ANTENA DERECHA ANDROID
				glPopMatrix();

				glPushMatrix();
					glRotatef(mover_antena_izq,0,0,1);			// MOVER ANTENA IZQUIERDA
					dibujar_antenaIzquierda(modo, cilindro);	// ANTENA IZQUIERDA ANDROID
				glPopMatrix();

				dibujar_cabeza(modo, esfera_cabeza);			// CABEZA ANDROID
			glPopMatrix();

			dibujar_torso(modo, cilindro);						// TORSO ANDROID

			dibujar_brazoDerecho(modo, cilindro);				// BRAZO DERECHO ANDROID
			dibujar_brazoIzquierdo(modo, cilindro);				// BRAZO IZQUIERDO ANDROID

		glPopMatrix();
	
		dibujar_piernaDerecha(modo, cilindro);					// PIERNA DERECHA ANDROID
		dibujar_piernaIzquierda(modo, cilindro);				// PIERNA IZQUIERDA ANDROID
	glPopMatrix();
}

/*
*	Método que pinta la cabeza del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param esfera_cabeza, media esfera que representará la cabeza.
*/
void dibujar_cabeza(char modo,Objeto3D esfera_cabeza){
	glPushMatrix();
		glTranslatef(0,0.06,0);
		glScalef(0.005,0.005,0.005);
		glRotatef(90,1,0,0);
		Dibujar_objeto(modo, esfera_cabeza.getVertices(), esfera_cabeza.getTriangulos(), esfera_cabeza.getLados(),0,0.8,0);
	glPopMatrix();
}

/*
*	Método que pinta el ojo derecho del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param esfera_ojos, esfera para el ojo derecho.
*/
void dibujar_ojoDerecho(char modo,Objeto3D esfera_ojos){
	glPushMatrix();
		glTranslatef(0.2,0.3,0.55);
		glScalef(0.0003,0.0003,0.0003);
		glRotatef(15,0,1,0);
		glRotatef(150,1,0,0);
		Dibujar_objeto(modo, esfera_ojos.getVertices(), esfera_ojos.getTriangulos(), esfera_ojos.getLados(),0.98,0.98,0.98);
	glPopMatrix();
}

/*
*	Método que pinta el ojo izquierdo del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param esfera_ojos, esfera para el ojo derecho.
*/
void dibujar_ojoIzquierdo(char modo,Objeto3D esfera_ojos){
	glPushMatrix();
		glTranslatef(-0.2,0.3,0.55);
		glScalef(0.0003,0.0003,0.0003);
		glRotatef(-15,0,1,0);
		glRotatef(150,1,0,0);
		Dibujar_objeto(modo, esfera_ojos.getVertices(), esfera_ojos.getTriangulos(), esfera_ojos.getLados(),0.98,0.98,0.98);
	glPopMatrix();
}

/*
*	Método que pinta la antena derecha del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param cilindro, cilindro para la antena derecha.
*/
void dibujar_antenaDerecha(char modo,Objeto3D cilindro){
	glPushMatrix();
		glTranslatef(0.20,0.80+escalar_antenas/2,0);
		glRotatef(-15,0,0,1);
		glScalef(0.05,0.3+escalar_antenas,0.05);
		Dibujar_objeto(modo, cilindro.getVertices(), cilindro.getTriangulos(), cilindro.getLados(),0,0.8,0);
	glPopMatrix();
}

/*
*	Método que pinta la antena izquierda del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param cilindro, cilindro para la antena izquierda.
*/
void dibujar_antenaIzquierda(char modo,Objeto3D cilindro){
	glPushMatrix();
		glTranslatef(-0.20,0.80+escalar_antenas/2,0);
		glRotatef(15,0,0,1);
		glScalef(0.05,0.3+escalar_antenas,0.05);
		Dibujar_objeto(modo, cilindro.getVertices(), cilindro.getTriangulos(), cilindro.getLados(),0,0.8,0);
	glPopMatrix();
}

/*
*	Método que pinta el torso del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param cilindro, cilindro para el torso.
*/
void dibujar_torso(char modo,Objeto3D cilindro){
	glPushMatrix();
		glTranslatef(0,-0.7,0);
		glScalef(1.26,1.26,1.26);
		Dibujar_objeto(modo, cilindro.getVertices(), cilindro.getTriangulos(), cilindro.getLados(),0,0.8,0);
	glPopMatrix();
}

/*
*	Método que pinta el brazo derecho del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param cilindro, cilindro para el brazo derecho.
*/
void dibujar_brazoDerecho(char modo,Objeto3D cilindro){		// MODIFICACIÓN DEFENSA PRÁCTICA 3, partir el brazo en dos
	// PARTE ARRIBA DEL BRAZO
	glPushMatrix();
		glTranslatef(0.8,-0.15,0);
		glRotatef(mover_brazo_dcho,1,0,0);
		glTranslatef(0,-0.2,-0.1);
		glScalef(0.25,0.35,0.25);
		Dibujar_objeto(modo, cilindro.getVertices(), cilindro.getTriangulos(), cilindro.getLados(),0,0.8,0);
	glPopMatrix();

	// PARTE ABAJO DEL BRAZO
	glPushMatrix();
		glTranslatef(0.8,-0.15,0);
		glRotatef(mover_brazo_dcho,1,0,0);
		glTranslatef(0,-0.6,-0.1);
		glScalef(0.25,0.35,0.25);
		Dibujar_objeto(modo, cilindro.getVertices(), cilindro.getTriangulos(), cilindro.getLados(),0,0.8,0);
	glPopMatrix();
}

/*
*	Método que pinta el brazo izquierdo del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param cilindro, cilindro para el brazo izquierdo.
*/
void dibujar_brazoIzquierdo(char modo,Objeto3D cilindro){
	glPushMatrix();
		glTranslatef(-0.8,-0.15,0);
		glRotatef(mover_brazo_izq,1,0,0);
		glTranslatef(0,-0.4,-0.1);
		glScalef(0.25,0.8,0.25);
		Dibujar_objeto(modo, cilindro.getVertices(), cilindro.getTriangulos(), cilindro.getLados(),0,0.8,0);
	glPopMatrix();
}

/*
*	Método que pinta la pierna derecha del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param cilindro, cilindro para la pierna derecha.
*/
void dibujar_piernaDerecha(char modo,Objeto3D cilindro){
	glPushMatrix();
		glTranslatef(0.3,-1.60,0);
		glScalef(0.25,0.5,0.25);
		Dibujar_objeto(modo, cilindro.getVertices(), cilindro.getTriangulos(), cilindro.getLados(),0,0.8,0);
	glPopMatrix();
}

/*
*	Método que pinta la pierna izqueirda del Android.
*	@param modo, indica el modo de dibujo de la pieza.
*	@param cilindro, cilindro para la pierna izquierda.
*/
void dibujar_piernaIzquierda(char modo,Objeto3D cilindro){
	glPushMatrix();
		glTranslatef(-0.3,-1.60,0);
		glScalef(0.25,0.5,0.25);
		Dibujar_objeto(modo, cilindro.getVertices(), cilindro.getTriangulos(), cilindro.getLados(),0,0.8,0);
	glPopMatrix();
}

/*********************************************/
/* Métodos para movimiento de piezas Android */
/*********************************************/

/*
*	Método que gira a la derecha la cabeza hasta un ángulo de 30 grados.
*/
void DERECHA_girarCabeza(){
	if(mover_cabeza < 30)
		mover_cabeza++;
}

/*
*	Método que gira a la izquierda la cabeza hasta un ángulo de -30 grados.
*/
void IZQUIERDA_girarCabeza(){
	if(mover_cabeza > -30)
		mover_cabeza--;
}

/*
*	Método que gira a la derecha la cintura hasta un ángulo de 30 grados.
*/
void DERECHA_girarCintura(){
	if(mover_torso < 30)
		mover_torso++;
}

/*
*	Método que gira a la izquierda la cintura hasta un ángulo de -30 grados.
*/
void IZQUIERDA_girarCintura(){
	if(mover_torso > -30)
		mover_torso--;
}

/*
*	Método que mueve a la derecha la antena izquierda hasta un ángulo de -5 grados.
*/
void DERECHA_moverAntena_izq(){
	if(mover_antena_izq > -5)
		mover_antena_izq--;
}

/*
*	Método que mueve a la izquierda la antena izquierda hasta un ángulo de 5 grados.
*/
void IZQUIERDA_moverAntena_izq(){
	if(mover_antena_izq < 5)
		mover_antena_izq++;
}

/*
*	Método que mueve a la derecha la antena derecha hasta un ángulo de -5 grados.
*/
void DERECHA_moverAntena_dcha(){
	if(mover_antena_dcha > -5)
		mover_antena_dcha--;
}

/*
*	Método que mueve a la izquierda la antena derecha hasta un ángulo de 5 grados.
*/
void IZQUIERDA_moverAntena_dcha(){
	if(mover_antena_dcha < 5)
		mover_antena_dcha++;
}

/*
*	Método que sube el brazo izquiero hasta los -90 grados.
*/
void ARRIBA_moverBrazo_izq(){
	if(mover_brazo_izq > -90)
		mover_brazo_izq--;
}

/*
*	Método que baja el brazo izquiero hasta los 0 grados.
*/
void ABAJO_moverBrazo_izq(){
	if(mover_brazo_izq < 0)
		mover_brazo_izq++;
}

/*
*	Método que sube el brazo derecho hasta los -90 grados.
*/
void ARRIBA_moverBrazo_dcho(){
	if(mover_brazo_dcho > -90)
		mover_brazo_dcho--;
}

/*
*	Método que baja el brazo derecho hasta los 0 grados.
*/
void ABAJO_moverBrazo_dcho(){
	if(mover_brazo_dcho < 0)
		mover_brazo_dcho++;
}

/*
*	Método que estira las antenas hasta 0.2 en el eje Y, de 0.005 en 0.005.
*/
void estirarAntenas(){
	if(escalar_antenas < 0.2)
		escalar_antenas += 0.005;
}

/*
*	Método que recoge las antenas hasta el 0.0 en el eje Y, de 0.005 en 0.005.
*/
void recogerAntenas(){
	if(escalar_antenas > 0.0)
		escalar_antenas -= 0.005;
}