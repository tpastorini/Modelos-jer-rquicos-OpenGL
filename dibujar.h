#include <GL/glut.h>
#include <vector>
#include <vertex.h>

void Dibujar_puntos(vector<_vertex3f> vertices, float r, float g, float b);


void Dibujar_ajedrez(vector<_vertex3f> vertices, vector<_vertex3i> triangulos, float r, float g, float b);


void Dibujar_alambre(vector<_vertex3f> vertices, vector<_vertex2i> lados, float r, float g, float b);


void Dibujar_solido(vector<_vertex3f> vertices, vector<_vertex3i> triangulos, float r, float g, float b);


void Dibujar_objeto(char modo, vector<_vertex3f> vertices, vector<_vertex3i> triangulos, vector<_vertex2i> lados, float r, float g, float b);


