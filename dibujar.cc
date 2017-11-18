/***************************************************
*	Desarrolladora: Tatiana Pastorini
*	Grado en Ingeniería Informática, UGR, ETSIIT.
*	Práctica 3. Modelos jerárquicos.
***************************************************/

#include <dibujar.h>
#include <iostream>

using namespace std;

/*
*	Fichero .cc que contiene los modos de visualización de un Objeto3D.
*	Los modos disponibles son: Modo sólido, modo ajedrez, modo línea o alambre y modo puntos de un objeto 3D.
*/

/*
*	Método que dibuja el objeto en modo puntos.
*	@param vertices, es el vector con los vértices del objeto.
*	@param r, indica el grado del color rojo.
*	@param g, indica el grado del color verde.
*	@param b, indica el grado del color azul.
*/
void Dibujar_puntos(vector<_vertex3f> vertices, float r, float g, float b){
	glPointSize(5);
	glBegin( GL_POINTS );
		for(unsigned int i=0; i<vertices.size(); i++){
			glColor3f(r,g,b);
			glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
		}
	glEnd();
}

/*
*	Método que dibuja el objeto en modo ajedrez.
*	@param vertices, es el vector con los vértices del objeto.
*	@param triangulos, es el vector con los triángulos que forman cada cara del objeto.
*	@param r, indica el grado del color rojo.
*	@param g, indica el grado del color verde.
*	@param b, indica el grado del color azul.
*/
void Dibujar_ajedrez(vector<_vertex3f> vertices, vector<_vertex3i> triangulos, float r, float g, float b){
	glBegin( GL_TRIANGLES );
		for(unsigned int i=0; i<triangulos.size(); i++){
			if(i%2 == 0){
				glColor3f(1,1,0.1);
			}
			else{
				glColor3f(0.4,0.4,1);
			}

			glVertex3f(vertices[triangulos[i]._0].x,vertices[triangulos[i]._0].y,vertices[triangulos[i]._0].z);
			glVertex3f(vertices[triangulos[i]._1].x,vertices[triangulos[i]._1].y,vertices[triangulos[i]._1].z);
			glVertex3f(vertices[triangulos[i]._2].x,vertices[triangulos[i]._2].y,vertices[triangulos[i]._2].z);
		}
	glEnd();
}

/*
*	Método que dibuja el objeto en modo línea o alambre.
*	@param vertices, es el vector con los vértices del objeto.
*	@param lados, es el vector con los lados que unen cada vértice con los demás.
*	@param r, indica el grado del color rojo.
*	@param g, indica el grado del color verde.
*	@param b, indica el grado del color azul.
*/
void Dibujar_alambre(vector<_vertex3f> vertices, vector<_vertex2i> lados, float r, float g, float b){
	glBegin( GL_LINES );
		for(unsigned int i=0; i<lados.size(); i++){
			glColor3f(r,g,b);
			glVertex3f(vertices[lados[i]._0].x,vertices[lados[i]._0].y,vertices[lados[i]._0].z);
			glVertex3f(vertices[lados[i]._1].x,vertices[lados[i]._1].y,vertices[lados[i]._1].z);
		}

	glEnd();
}

/*
*	Método que dibuja el objeto en modo sólido.
*	@param vertices, es el vector con los vértices del objeto.
*	@param triangulos, es el vector con los triángulos que forman cada cara del objeto.
*	@param r, indica el grado del color rojo.
*	@param g, indica el grado del color verde.
*	@param b, indica el grado del color azul.
*/
void Dibujar_solido(vector<_vertex3f> vertices, vector<_vertex3i> triangulos, float r, float g, float b){
	glBegin( GL_TRIANGLES );
		for(unsigned int i=0; i<triangulos.size(); i++){
			glColor3f(r,g,b);
			glVertex3f(vertices[triangulos[i]._0].x,vertices[triangulos[i]._0].y,vertices[triangulos[i]._0].z);
			glVertex3f(vertices[triangulos[i]._1].x,vertices[triangulos[i]._1].y,vertices[triangulos[i]._1].z);
			glVertex3f(vertices[triangulos[i]._2].x,vertices[triangulos[i]._2].y,vertices[triangulos[i]._2].z);
		}
	glEnd();
}

/*
*	Método de visualización de un objeto3D según el modo de dibujo.
*	@param modo, caracter que indica el modo de dibujo del objeto3D.
*	@param vertices, es el vector con los vértices del objeto.
*	@param triangulos, es el vector con los triángulos que forman cada cara del objeto.
*	@param lados, es el vector con los lados que unen cada vértice con los demás.
*	@param colores, es el vector con los colores para cada vértice.
*	@param r, indica el grado del color rojo.
*	@param g, indica el grado del color verde.
*	@param b, indica el grado del color azul.
*/
void Dibujar_objeto(char modo, vector<_vertex3f> vertices, vector<_vertex3i> triangulos, vector<_vertex2i> lados, float r, float g, float b){

	switch(modo){
		case 'P':
			Dibujar_puntos(vertices, r, g, b);
			break;
		case 'A':
			Dibujar_ajedrez(vertices, triangulos, r, g, b);
			break;
		case 'L':
			Dibujar_alambre(vertices, lados, r, g, b);
			break;
		case 'S':
			Dibujar_solido(vertices, triangulos, r, g, b);
			break;
	}
}