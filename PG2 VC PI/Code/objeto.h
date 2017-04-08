#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <gl\glut.h>
#include "matriz.h"
#include "estrutura.h"
using namespace std;

class fachadaObjeto
{
public:
	vector<Point3D> vertice, normais, textura;
	vector<Face> faces;
	GLfloat cor[3];													
	GLdouble objectOperations[4][4];
	GLdouble objectScale[4][4];
	GLdouble xPosition, yPosition, zPosition, rotacX, rotacY, rotacZ;
	Face scanFace(char buffer[256]);
	fachadaObjeto();
	~fachadaObjeto();
	void loadObject(string filepath);									//Carrega os objetos que estão guardado na variavel
	void renderObj();													//Renderiza os objetos carregados
	void renderObjMultMatrix(GLdouble matrixOperations[4][4]);			//Renderiza e mult as coordenadas dos objetos
	void renderLinhas();												//Renderiza as linhas do objeto
	bool faceType(char buffer[256]);									//Checa se a face está escrita em f x y z, f v/vt/vn ou f v//vn
	void calcNormais(char buffer[256], Face faceSaida);					//Calcula as normais do objeto
	void vectorProduct(Point3D saida, Point3D vetor1, Point3D vetor2);	//Calcula o produto vetorial
};
