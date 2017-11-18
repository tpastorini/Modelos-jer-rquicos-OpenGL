/***************************************************
*	Desarrolladora: Tatiana Pastorini
*	Grado en Ingeniería Informática, UGR, ETSIIT.
*	Práctica 3. Modelos jerárquicos.
***************************************************/

#include <objetos.h>
#include <cmath>

using namespace std;

/*
*	Constructor por parámetros.
*	@param obj indica el objeto a crear.
*	1 = Pirámide
*	2 = Cubo
*	3 = Tetraedro
*	4 = Perfil del peón
*	5 = PLY de la esfera
*	6 = Cilindro
*/
Objeto3D::Objeto3D(const int obj){

	switch(obj){
		case 1:
			CrearPiramide(1);	// Creo la pirámide
			break;
		case 2:
			CrearCubo(1);		// Creo el cubo
			break;
		case 3:
			CrearObjetoConPLY("/media/tatiana/DATA/IG/Prácticas/practica2/read_ply/ant.ply");		// Cargo el ply correspondiente a la hormiga
			break;
		case 4:
			CrearObjetoConPLY("/media/tatiana/DATA/IG/Prácticas/practica2/read_ply/perfil_st.ply");	// Cargo el ply correspondiente al perfil del peón
			Revolucion(50);			// Genero por revolución el peón
			break;
		case 5:
			CrearObjetoConPLY("/media/tatiana/DATA/IG/Prácticas/practica3/p3/sphere.ply");			// Cargo el ply correspondiente a la hormiga
			break;
		case 6:
			CrearCilindro();		// Creo el cilindro para los brazos, las piernas y el torso del Android
			Revolucion(50);			// Genero por revolución el cilindro
			break;
	}
}

/*
*	Método que divide en dos la esfera.
*/
void Objeto3D::partirEsfera(){
	vector<_vertex3f> mitad;
	mitad.resize(vertices.size());

	for(int i=0; i<vertices.size(); i++){
		if(i < 241){
			mitad[i].x = vertices[i].x;
			mitad[i].y = vertices[i].y;
			mitad[i].z = vertices[i].z;
		}
	}

	vertices = mitad;	
}


void Objeto3D::CrearCilindro(){

	vertices.resize(4);
	
	// tapa superior
	vertices[0].x = 0.0;	vertices[1].x = 0.5;
	vertices[0].y = 0.5;	vertices[1].y = 0.5;
	vertices[0].z = 0.0;	vertices[1].z = 0.0;

							// tapa inferior
	vertices[2].x = 0.5;	vertices[3].x = 0.0;
	vertices[2].y = -0.5;	vertices[3].y = -0.5;
	vertices[2].z = 0.0;	vertices[3].z = 0.0;
}


// Le paso el número de veces que voy a rotar cada punto
void Objeto3D::Revolucion(int veces){

	vector<_vertex3f> vertices_auxiliares = vertices;   // Vertices finales le hago una copia antes de transformarlos

	float angulo = (2*M_PI)/veces;
	_vertex3f aux;
	_vertex3i cara;

  	for(int i=0; i<veces; i++){ // Todas las veces que tengo que rotar un mismo punto

	    for(int j=0; j<vertices_auxiliares.size(); j++){
	      	_vertex3f a = vertices_auxiliares[j];
	     	aux = aplicarTransformacionVertice_Y(angulo,a);
	     	vertices.push_back(aux);
	     	vertices_auxiliares[j] = aux;   // guardo el nuevo vertice para usarlo al calcular otro nuevo
	    }

	    // recorro los perfiles para ir uniéndolos y formando las caras

	    unsigned int inicioPerfil, finPerfil;
	    inicioPerfil = i * vertices_auxiliares.size();
	    finPerfil = inicioPerfil + vertices_auxiliares.size();

	    for (unsigned int i = inicioPerfil+1, j = finPerfil+1; i < finPerfil; i++, j++){

			cara._0=i-1;
			cara._1=j-1;
			cara._2=j;
			triangulos.push_back(cara);

			cara._0=i-1;
			cara._1=j;
			cara._2=i;
			triangulos.push_back(cara);
	    			
	    }
	}

    if (vertices.front().x){ // si la coord X=0, x toca el eje Y y por tanto no necesita tapa
		// Agregamos el punto central, aunque no es necesario porque solo pintamos las caras
		_vertex3f centro;
		_vertex3i inferior;
		centro.x=0.0;
		centro.y=vertices.front().y;
		centro.z=0.0;
		vertices.push_back(centro);

		for (int cnt = 0; cnt < veces; cnt++){
			int perfilactual = cnt * vertices_auxiliares.size();
			int siguientePerfil = perfilactual + vertices_auxiliares.size();
			inferior._0=vertices.size()-1;
			inferior._1=siguientePerfil;
			inferior._2=perfilactual;
			triangulos.push_back(inferior);
		}
    }

    if (vertices[vertices_auxiliares.size()-1].x){
     	//Añadimos el punto central de arriba

     	_vertex3f centro1;
    	_vertex3i superior;

     	centro1.x=0.0;
     	centro1.y=vertices[vertices_auxiliares.size()-1].y;
     	centro1.z=0.0;
     	vertices.push_back(centro1);

     	//Añadimos las caras de la tapa superior

		for (int cnt =0; cnt < veces; cnt++){
			int perfilactual = (cnt+1) * vertices_auxiliares.size()-1;
			int siguientePerfil = perfilactual + vertices_auxiliares.size();
			superior._0=vertices.size()-1;
			superior._1=perfilactual;
			superior._2=siguientePerfil;
			triangulos.push_back(superior);
		}
	}

   	rellenarLados();
}


// Devuelve la transformación del vertice V en el eje X
_vertex3f Objeto3D::aplicarTransformacionVertice_X(float angulo, _vertex3f v){
	_vertex3f nuevoPunto;

	nuevoPunto.x = cos(angulo)*v.x + sin(angulo)*v.z;
	nuevoPunto.y = v.y;
	nuevoPunto.z = -sin(angulo)*v.x + cos(angulo)*v.z;

   return nuevoPunto;
}


// Devuelve la transformación del vertice V en el eje Y
_vertex3f Objeto3D::aplicarTransformacionVertice_Y(float angulo, _vertex3f v){
	_vertex3f nuevoPunto;

	nuevoPunto.x = cos(angulo)*v.x + sin(angulo)*v.z;
	nuevoPunto.y = v.y;
	nuevoPunto.z = -sin(angulo)*v.x + cos(angulo)*v.z;

   return nuevoPunto;
}


// Devuelve la transformación del vertice V en el eje Z
_vertex3f Objeto3D::aplicarTransformacionVertice_Z(float angulo, _vertex3f v){
	_vertex3f nuevoPunto;

	nuevoPunto.x = cos(angulo)*v.x -sin(angulo)*v.y;
	nuevoPunto.y = sin(angulo)*v.x + cos(angulo)*v.y;
	nuevoPunto.z = v.z;

	return nuevoPunto;
}


void Objeto3D::CrearPiramide(float lado){
	// Relleno los vértices, los triángulos que conforman una cara y las líneas
	vertices.resize(5);
	triangulos.resize(6);
	lados.resize(9);
	colores.resize(5);

	vertices[0].x = -lado;		vertices[1].x = lado;
	vertices[0].y = -lado;		vertices[1].y = -lado;
	vertices[0].z = lado;		vertices[1].z = lado;

	vertices[2].x = lado;		vertices[3].x = -lado;
	vertices[2].y = -lado;		vertices[3].y = -lado;
	vertices[2].z = -lado;		vertices[3].z = -lado;

	vertices[4].x = 0;
	vertices[4].y = lado;
	vertices[4].z = 0;

	
	triangulos[0]._0 = 0;		triangulos[1]._0 = 3;
	triangulos[0]._1 = 1;		triangulos[1]._1 = 0;
	triangulos[0]._2 = 4;		triangulos[1]._2 = 4;

	triangulos[2]._0 = 3;		triangulos[3]._0 = 2;
	triangulos[2]._1 = 2;		triangulos[3]._1 = 1;
	triangulos[2]._2 = 4;		triangulos[3]._2 = 4;

	triangulos[4]._0 = 3;		triangulos[5]._0 = 3;
	triangulos[4]._1 = 1;		triangulos[5]._1 = 2;
	triangulos[4]._2 = 0;		triangulos[5]._2 = 1;


	lados[0]._0 = 0;	lados[1]._0 = 1;
	lados[0]._1 = 1;	lados[1]._1 = 2;

	lados[2]._0 = 2;	lados[3]._0 = 3;
	lados[2]._1 = 3;	lados[3]._1 = 0;

	lados[4]._0 = 0;	lados[5]._0 = 1;
	lados[4]._1 = 4;	lados[5]._1 = 4;

	lados[6]._0 = 2;	lados[7]._0 = 3;
	lados[6]._1 = 4;	lados[7]._1 = 4;

	lados[8]._0 = 3;
	lados[8]._1 = 1;

	

	colores[0].r = 1;	colores[1].r = 0;
	colores[0].g = 0;	colores[1].g = 0.5;
	colores[0].b = 1;	colores[1].b = 0.5;

	colores[2].r = 1;	colores[3].r = 0;
	colores[2].g = 1;	colores[3].g = 0;
	colores[2].b = 0;	colores[3].b = 0;

	colores[4].r = 0.1;
	colores[4].g = 0.9;
	colores[4].b = 0.8;
}


void Objeto3D::CrearCubo(float lado){
	
	// Relleno los vértices
	vertices.resize(8);
	triangulos.resize(12);
	lados.resize(18);
	colores.resize(8);

	vertices[0].x = -lado;		vertices[1].x = lado;
	vertices[0].y = -lado;		vertices[1].y = -lado;
	vertices[0].z = -lado;		vertices[1].z = -lado;

	vertices[2].x = lado;		vertices[3].x = -lado;
	vertices[2].y = -lado;		vertices[3].y = -lado;
	vertices[2].z = lado;		vertices[3].z = lado;

	vertices[4].x = -lado;		vertices[5].x = lado;
	vertices[4].y = lado;		vertices[5].y = lado;
	vertices[4].z = -lado;		vertices[5].z = -lado;

	vertices[6].x = lado;		vertices[7].x = -lado;
	vertices[6].y = lado;		vertices[7].y = lado;
	vertices[6].z = lado;		vertices[7].z = lado;


	triangulos[0]._0 = 0;		triangulos[1]._0 = 0;
	triangulos[0]._1 = 1;		triangulos[1]._1 = 5;
	triangulos[0]._2 = 5;		triangulos[1]._2 = 4;

	triangulos[2]._0 = 2;		triangulos[3]._0 = 2;
	triangulos[2]._1 = 3;		triangulos[3]._1 = 7;
	triangulos[2]._2 = 7;		triangulos[3]._2 = 6;

	triangulos[4]._0 = 1;		triangulos[5]._0 = 1;
	triangulos[4]._1 = 2;		triangulos[5]._1 = 6;
	triangulos[4]._2 = 6;		triangulos[5]._2 = 5;

	triangulos[6]._0 = 0;		triangulos[7]._0 = 0;
	triangulos[6]._1 = 4;		triangulos[7]._1 = 7;
	triangulos[6]._2 = 7;		triangulos[7]._2 = 3;

	triangulos[8]._0 = 0;		triangulos[9]._0 = 0;
	triangulos[8]._1 = 1;		triangulos[9]._1 = 2;
	triangulos[8]._2 = 2;		triangulos[9]._2 = 3;

	triangulos[10]._0 = 4;		triangulos[11]._0 = 4;
	triangulos[10]._1 = 5;		triangulos[11]._1 = 6;
	triangulos[10]._2 = 6;		triangulos[11]._2 = 7;



	lados[0]._0 = 0;	lados[1]._0 = 0;
	lados[0]._1 = 1;	lados[1]._1 = 2;

	lados[2]._0 = 0;	lados[3]._0 = 0;
	lados[2]._1 = 3;	lados[3]._1 = 4;

	lados[4]._0 = 1;	lados[5]._0 = 1;
	lados[4]._1 = 4;	lados[5]._1 = 5;

	lados[6]._0 = 1;	lados[7]._0 = 1;
	lados[6]._1 = 6;	lados[7]._1 = 2;

	lados[8]._0 = 3;	lados[9]._0 = 3;
	lados[8]._1 = 4;	lados[9]._1 = 7;

	lados[10]._0 = 3;	lados[11]._0 = 5;
	lados[10]._1 = 6;	lados[11]._1 = 6;

	lados[12]._0 = 4;	lados[13]._0 = 4;
	lados[12]._1 = 5;	lados[13]._1 = 7;

	lados[14]._0 = 4;	lados[15]._0 = 6;
	lados[14]._1 = 6;	lados[15]._1 = 7;

	lados[16]._0 = 2;	lados[17]._0 = 2;
	lados[16]._1 = 3;	lados[17]._1 = 6;


	colores[0].r = 1;		colores[1].r = 0;
	colores[0].g = 0;		colores[1].g = 0.5;
	colores[0].b = 1;		colores[1].b = 0.5;

	colores[2].r = 1;		colores[3].r = 0;
	colores[2].g = 1;		colores[3].g = 0;
	colores[2].b = 0;		colores[3].b = 0;

	colores[4].r = 0.1;		colores[5].r = 0;
	colores[4].g = 0.9;		colores[5].g = 0;
	colores[4].b = 0.8;		colores[5].b = 1;

	colores[6].r = 1;		colores[7].r = 0.7;
	colores[6].g = 0.5;		colores[7].g = 0.6;
	colores[6].b = 0;		colores[7].b = 0;
}


void Objeto3D::CrearTetraedro(float lado){
	vertices.resize(4);
	triangulos.resize(4);
	lados.resize(6);
	colores.resize(4);

	vertices[0].x = 0;			vertices[1].x = -lado;
	vertices[0].y = lado;		vertices[1].y = -lado;
	vertices[0].z = 0;			vertices[1].z = -lado;

	vertices[2].x = 0;			vertices[3].x = lado;
	vertices[2].y = -lado;		vertices[3].y = -lado;
	vertices[2].z = lado;		vertices[3].z = -lado;


	triangulos[0]._0 = 0;		triangulos[1]._0 = 1;
	triangulos[0]._1 = 1;		triangulos[1]._1 = 2;
	triangulos[0]._2 = 3;		triangulos[1]._2 = 3;

	triangulos[2]._0 = 0;		triangulos[3]._0 = 0;
	triangulos[2]._1 = 2;		triangulos[3]._1 = 1;
	triangulos[2]._2 = 3;		triangulos[3]._2 = 2;

	
	lados[0]._0 = 0;		lados[1]._0 = 0;
	lados[0]._1 = 1;		lados[1]._1 = 2;

	lados[2]._0 = 0;		lados[3]._0 = 1;
	lados[2]._1 = 3;		lados[3]._1 = 2;

	lados[4]._0 = 1;		lados[5]._0 = 2;
	lados[4]._1 = 3;		lados[5]._1 = 3;


	colores[0].r = 1;		colores[1].r = 0;
	colores[0].g = 0;		colores[1].g = 0.5;
	colores[0].b = 1;		colores[1].b = 0.5;

	colores[2].r = 1;		colores[3].r = 0;
	colores[2].g = 1;		colores[3].g = 0;
	colores[2].b = 0;		colores[3].b = 0;
}


void Objeto3D::CrearObjetoConPLY(char* nombreArchivo){
	_file_ply ply;

	// Vectores temporales para los vértices y triángulos
	vector<float> vertices_ply;
	vector<int> triangulos_ply;

	ply.open(nombreArchivo);	// abro el archivo ply
	ply.read(vertices_ply, triangulos_ply);		// leo los vértices y triángulos y los guardo
	ply.close();	// cierro el archivo

	// Ahora tengo que meter los vértices y triángulos recién guardados en unos vectores
	// pertenecientes a la clase "objetos", para luego poder tener los métodos de dibujo, etc

	vertices.resize(vertices_ply.size()/3);
	triangulos.resize(triangulos_ply.size()/3);

	rellenaVertices(vertices_ply);
	rellenaCaras(triangulos_ply);
	rellenarLados();
}


void Objeto3D::rellenaVertices(vector<float> &verticesPLY){
	int i=0;
	for(int j=0; j < verticesPLY.size(); j+=3){
		vertices[i].x = verticesPLY[j];
		vertices[i].y = verticesPLY[j+1];
		vertices[i].z = verticesPLY[j+2];

		i++;
	}
}


void Objeto3D::rellenaCaras(vector<int> &carasPLY){
	int i=0;
	for(int j=0; j < carasPLY.size(); j+=3){
		triangulos[i]._0 = carasPLY[j];
		triangulos[i]._1 = carasPLY[j+1];
		triangulos[i]._2 = carasPLY[j+2];

		i++;
	}
}


void Objeto3D::rellenarLados(){
    lados.resize(triangulos.size()*3);
    int j = 0;

    for (int i = 0; i < triangulos.size(); i++) {
        lados[j]._0 = triangulos[i]._0;
        lados[j++]._1 = triangulos[i]._1;

        lados[j]._0 = triangulos[i]._1;
        lados[j++]._1 = triangulos[i]._2;

        lados[j]._0 = triangulos[i]._2;
        lados[j++]._1 = triangulos[i]._0;
    }
}

/*
*	Método que devuelve los vértices del objeto.
*/
vector<_vertex3f> Objeto3D::getVertices(){
	return vertices;
}

/*
*	Método que devuelve los triángulos del objeto.
*/
vector<_vertex3i> Objeto3D::getTriangulos(){
	return triangulos;
}

/*
*	Método que devuelve los lados del objeto.
*/
vector<_vertex2i> Objeto3D::getLados(){
	return lados;
}

/*
*	Método que devuelve los colores de los vértices del objeto.
*/
vector<_vertex3f> Objeto3D::getColores(){
	return colores;
}