/***************************************************
*	Desarrolladora: Tatiana Pastorini
*	Grado en Ingeniería Informática, UGR, ETSIIT.
*	Práctica 3. Modelos jerárquicos.
***************************************************/

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <dibujar.h>
#include <dibujarAndroid.h>

// tamaño de los ejes
const int AXIS_SIZE = 50000;

char modo = 'S';	// modo por defecto
int objeto = 5;		// objeto por defecto

// Los parámetros indican el tipo de objeto a dibujar
Objeto3D piramide(1);		// Me creo la pirámide
Objeto3D cubo(2);			// Me creo el cubo
Objeto3D figura_ply(3);		// Cargo el archivo PLY
Objeto3D revolucion(4);		// Hago la revolución
Objeto3D esfera_cabeza(5);	// Esfera para la cabeza (la divido en initialize())
Objeto3D esfera_ojos(5);	// Esfera para los ojos
Objeto3D cilindro(6);		// Cilindro para el torso, los brazos y las piernas
//Objeto3D tetraedro(4);	// Me creo eltetraedro


// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determinan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

void clear_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection(){			
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer(){
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis(){
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1,0,0);
	glVertex3f(-AXIS_SIZE,0,0);
	glVertex3f(AXIS_SIZE,0,0);
	// eje Y, color verde
	glColor3f(0,1,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,AXIS_SIZE,0);
	// eje Z, color azul
	glColor3f(0,0,1);
	glVertex3f(0,0,-AXIS_SIZE);
	glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}


//***************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects(){

	switch(objeto){
		case 1:		// Dibujo la pirámide
			Dibujar_objeto(modo, piramide.getVertices(), piramide.getTriangulos(), piramide.getLados(),1,1,0);
			break;
		case 2:		// Dibujo el cubo
			Dibujar_objeto(modo, cubo.getVertices(), cubo.getTriangulos(), cubo.getLados(),1,1,0);
			break;
		case 3:		// Dibujo el objeto PLY
			Dibujar_objeto(modo, figura_ply.getVertices(), figura_ply.getTriangulos(), figura_ply.getLados(),1,1,0);
			break;
		case 4: 	// Creo el objeto por revolución
			Dibujar_objeto(modo, revolucion.getVertices(), revolucion.getTriangulos(), revolucion.getLados(),1,1,0);
			break;
		case 5:		// Dibujo el objeto jerárquico Android
			Dibujar_Android(modo,esfera_ojos, esfera_cabeza, cilindro);
			break;
	}
}


//***************************************************************************
//
//***************************************************************************

void draw_scene(void){
	clear_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1){
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y){

	cout << "Tecla pulsada -> " << Tecla1 << endl;

	switch(toupper(Tecla1)){
		case 'Q':
			exit(0);
			break;
		case 'P':			
			modo = 'P';		// modo punto
			break;
		case 'L':
			modo = 'L';		// modo alambre
			break;
		case 'A':
			modo = 'A';		// modo ajedrez
			break;
		case 'S':
			modo = 'S';		// modo solido
			break;
		case '1':	
			objeto = 1; 	// dibujar piramide
			break;
		case '2':	
			objeto = 2; 	// dibujar cubo
			break;
		case '3':
			objeto = 3;		// dibujar ply
			break;
		case '4':
			objeto = 4;		// generar revolución
			break;
		case '5':
			objeto = 5;		// generar objeto jerárquico
			break;
		case 'X':
			DERECHA_girarCabeza();			// Gira la cabeza a la derecha
			break;
		case 'Z':
			IZQUIERDA_girarCabeza();		// Gira la cabeza a la izquierda
			break;
		case 'I':
			estirarAntenas();				// Estirar las antenas
			break;
		case 'U':
			recogerAntenas();				// Encoger las antenas
			break;
		case 'V':
			DERECHA_moverAntena_izq();		// Mover antena izquierda a la derecha
			break;
		case 'C':
			IZQUIERDA_moverAntena_izq();	// Mover antena izquierda a la izquierda
			break;
		case 'N':
			DERECHA_moverAntena_dcha();		// Mover antena derecha a la derecha
			break;
		case 'B':
			IZQUIERDA_moverAntena_dcha();	// Mover antena derecha a la izquierda
			break;
		case 'F':
			DERECHA_girarCintura();			// Mover cintura a la derecha
			break;
		case 'D':
			IZQUIERDA_girarCintura();		// Mover cintura a la izquierda
			break;
		case 'H':
			ARRIBA_moverBrazo_izq();		// Subir brazo izquierdo
			break;
		case 'G':
			ABAJO_moverBrazo_izq();			// Bajar brazo izquierdo
			break;
		case 'K':
			ARRIBA_moverBrazo_dcho();		// Subir brazo derecho
			break;
		case 'J':
			ABAJO_moverBrazo_dcho();		// Bajar brazo derecho
			break;
	}

	glutPostRedisplay();

}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y){

	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}

	glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void){

	// parto la esfera para la cabeza Android
	esfera_cabeza.partirEsfera();

	// se inicalizan la ventana y los planos de corte
	Window_width=0.5;
	Window_height=0.5;
	Front_plane=1;
	Back_plane=1000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=4*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv){

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(UI_window_width,UI_window_height);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("Práctica 3");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);

	// funcion de inicialización
	initialize();

	// inicio del bucle de eventos
	glutMainLoop();

	return 0;
}
