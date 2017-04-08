#pragma once
#include <stdlib.h>
#include "matriz.h"
#include "estrutura.h"
#include "objeto.h"
#include "GL\glut.h"
#include <string>
#include <vector>

class fachada
{
public:
	vector<fachadaObjeto> objetos;
	vector<Light> luz;
	fachadaObjeto camera;
	Camera userCamera;
	Camera directorCamera;
	GLdouble directorOperations[4][4];
	int lightNumber;
	int selecObjeto;
public:
	fachada();
	~fachada();
	void loadObject(string filepath);																													//Carrega os objetos que estão guardado na variavel
	void renderObjetos();																																//Renderiza todos os objetos da cena
	void renderObjDiretor();																															
	void initDirector();																																
	void renderCamera();																																//Renderiza a câmera do objeto
	void criarLuz();																																	//Cria uma nova luz na cena
	void renderLuz();																																	//Renderiza todas asluzes
	void transCamera(GLdouble x, GLdouble y, GLdouble z);																							
	void rotCamera(GLdouble rot, GLdouble x, GLdouble y, GLdouble z);																					//Rotaciona câmera do usuario	
	void transObjeto(GLint selecObjeto, GLdouble x, GLdouble y, GLdouble z);																			//Translada o objeto selecionado
	void escalaObjeto(GLint selecObjeto, GLdouble scaleX, GLdouble scaleY, GLdouble scaleZ);															//Dimensiona o objeto selecionado
	void rotObjeto(GLint selecObjeto, GLdouble rot, GLdouble x, GLdouble y, GLdouble z);																//Rotaciona o objeto selecionado
	void transLuz(GLint selectedLight, GLdouble x, GLdouble y, GLdouble z);																				//Translada a luz selecionada
	void planoCartesiano(GLdouble densidade, GLdouble esquerda, GLdouble direita, GLdouble perto, GLdouble longe, GLdouble altura, GLdouble cor[4]);	//Cria o plano cartesiano da cena
	void chao(GLdouble tamanho, GLdouble altura);																										//Cria o terreno da cena
};
