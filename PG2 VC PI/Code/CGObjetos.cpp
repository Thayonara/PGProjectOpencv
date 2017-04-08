#define _CRT_SECURE_NO_WARNINGS
#include "objeto.h"
fachadaObjeto::fachadaObjeto()
{
}
fachadaObjeto::~fachadaObjeto()
{
}
void fachadaObjeto::loadObject(string filepath){
	ifstream in(filepath);												//Abrindo o arquivo
	if (!in.is_open()){
		cout << "file not opened" << endl;
	}
	char buffer[256];
	float tempX, tempY, tempZ;
	while (!in.eof()){
		in.getline(buffer, 256);										//Ler a primeira linha
			if (buffer[0] == 'v' && buffer[1] == ' '){						//Se for um vertice então vai ser lido as primeiras coordenadas
			sscanf(buffer, "v %f %f %f", &tempX, &tempY, &tempZ);		
			Point3D temp;
			temp.x = tempX;
			temp.y = tempY;
			temp.z = tempZ;
			vertice.push_back(temp);									//Salva as coordenadas dos vértices no vetor de vertices
		}
		else if (buffer[0] == 'v' && buffer[1] == 'n'){					//Se for um vetor normal então vai ser lido o vetor normal
			sscanf(buffer, "vn %f %f %f", &tempX, &tempY, &tempZ);		
			Point3D temp;
			temp.x = tempX;
			temp.y = tempY;
			temp.z = tempZ;
			normais.push_back(temp);									//Salva o vetor normal no vetor de vertices
		}
		else if (buffer[0] == 'v' && buffer[1] == 't'){					//Se for um vetor de textura
		}
		else if (buffer[0] == 'f'){										//Se for uma face
			Face tempFace = scanFace(buffer);							
			faces.push_back(tempFace);
		}
	}
	fachadaMatriz::identity(objectOperations);
	fachadaMatriz::identity(objectScale);
}
void fachadaObjeto::renderObj(){
	cor[0] = 1;
	cor[1] = 0;
	cor[2] = 1;
	for (int j = 0; j < faces.size(); j++){
		glColor3f(cor[0], cor[1], cor[2]);
		GLfloat col[4] = { 1, 1, 1, 0 };
		GLfloat ambient[] = { cor[0], cor[1], cor[2], .0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glBegin(GL_POLYGON);
		for (int k = 0; k < faces[j].vertice.size(); k++){	//Chama todo vetor que faz "face[k]"
			Point3D aux;
			Point3D temp;
			if (normais.size() > 0){
				aux.x = objectOperations[0][0] * normais[(faces[j].normais[k] - 1)].x + objectOperations[0][1] * normais[(faces[j].normais[k] - 1)].y + objectOperations[0][2] * normais[(faces[j].normais[k] - 1)].z;
				aux.y = objectOperations[1][0] * normais[(faces[j].normais[k] - 1)].x + objectOperations[1][1] * normais[(faces[j].normais[k] - 1)].y + objectOperations[1][2] * normais[(faces[j].normais[k] - 1)].z;
				aux.z = objectOperations[2][0] * normais[(faces[j].normais[k] - 1)].x + objectOperations[2][1] * normais[(faces[j].normais[k] - 1)].y + objectOperations[2][2] * normais[(faces[j].normais[k] - 1)].z;
				glNormal3d(aux.x, aux.y, aux.z);
			}
			aux.x = objectScale[0][0] * vertice[(faces[j].vertice[k] - 1)].x + objectScale[0][1] * vertice[(faces[j].vertice[k] - 1)].y + objectScale[0][2] * vertice[(faces[j].vertice[k] - 1)].z + objectScale[0][3];
			aux.y = objectScale[1][0] * vertice[(faces[j].vertice[k] - 1)].x + objectScale[1][1] * vertice[(faces[j].vertice[k] - 1)].y + objectScale[1][2] * vertice[(faces[j].vertice[k] - 1)].z + objectScale[1][3];
			aux.z = objectScale[2][0] * vertice[(faces[j].vertice[k] - 1)].x + objectScale[2][1] * vertice[(faces[j].vertice[k] - 1)].y + objectScale[2][2] * vertice[(faces[j].vertice[k] - 1)].z + objectScale[2][3];
			temp.x = objectOperations[0][0] * aux.x + objectOperations[0][1] * aux.y + objectOperations[0][2] * aux.z + objectOperations[0][3];
			temp.y = objectOperations[1][0] * aux.x + objectOperations[1][1] * aux.y + objectOperations[1][2] * aux.z + objectOperations[1][3];
			temp.z = objectOperations[2][0] * aux.x + objectOperations[2][1] * aux.y + objectOperations[2][2] * aux.z + objectOperations[2][3];
			glVertex3d(temp.x, temp.y, temp.z);
		}
		glEnd();
	}
}
void fachadaObjeto::renderObjMultMatrix(GLdouble matrixOperations[4][4]){
	cor[0] = 1;
	cor[1] = 0;
	cor[2] = 1;
	for (int j = 0; j < faces.size(); j++){
		glColor3f(cor[0], cor[1], cor[2]);
		GLfloat col[4] = { 1, 1, 1, 0 };
		GLfloat ambient[] = { cor[0], cor[1], cor[2], .0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glBegin(GL_POLYGON);
		for (int k = 0; k < faces[j].vertice.size(); k++){
			Point3D aux, temp, last;
			if (normais.size() > 0){
				aux.x = objectOperations[0][0] * normais[(faces[j].normais[k] - 1)].x + objectOperations[0][1] * normais[(faces[j].normais[k] - 1)].y + objectOperations[0][2] * normais[(faces[j].normais[k] - 1)].z;
				aux.y = objectOperations[1][0] * normais[(faces[j].normais[k] - 1)].x + objectOperations[1][1] * normais[(faces[j].normais[k] - 1)].y + objectOperations[1][2] * normais[(faces[j].normais[k] - 1)].z;
				aux.z = objectOperations[2][0] * normais[(faces[j].normais[k] - 1)].x + objectOperations[2][1] * normais[(faces[j].normais[k] - 1)].y + objectOperations[2][2] * normais[(faces[j].normais[k] - 1)].z;
				glNormal3d(aux.x, aux.y, aux.z);
			}
			aux.x = objectScale[0][0] * vertice[(faces[j].vertice[k] - 1)].x + objectScale[0][1] * vertice[(faces[j].vertice[k] - 1)].y + objectScale[0][2] * vertice[(faces[j].vertice[k] - 1)].z + objectScale[0][3];
			aux.y = objectScale[1][0] * vertice[(faces[j].vertice[k] - 1)].x + objectScale[1][1] * vertice[(faces[j].vertice[k] - 1)].y + objectScale[1][2] * vertice[(faces[j].vertice[k] - 1)].z + objectScale[1][3];
			aux.z = objectScale[2][0] * vertice[(faces[j].vertice[k] - 1)].x + objectScale[2][1] * vertice[(faces[j].vertice[k] - 1)].y + objectScale[2][2] * vertice[(faces[j].vertice[k] - 1)].z + objectScale[2][3];
			temp.x = objectOperations[0][0] * aux.x + objectOperations[0][1] * aux.y + objectOperations[0][2] * aux.z + objectOperations[0][3];
			temp.y = objectOperations[1][0] * aux.x + objectOperations[1][1] * aux.y + objectOperations[1][2] * aux.z + objectOperations[1][3];
			temp.z = objectOperations[2][0] * aux.x + objectOperations[2][1] * aux.y + objectOperations[2][2] * aux.z + objectOperations[2][3];
			last.x = matrixOperations[0][0] * temp.x + matrixOperations[0][1] * temp.y + matrixOperations[0][2] * temp.z + matrixOperations[0][3];
			last.y = matrixOperations[1][0] * temp.x + matrixOperations[1][1] * temp.y + matrixOperations[1][2] * temp.z + matrixOperations[1][3];
			last.z = matrixOperations[2][0] * temp.x + matrixOperations[2][1] * temp.y + matrixOperations[2][2] * temp.z + matrixOperations[2][3];
			glVertex3d(last.x, last.y, last.z);
		}
		glEnd();
	}
}
void fachadaObjeto::renderLinhas(){
	cor[0] = 1;
	cor[1] = 1;
	cor[2] = 1;
	glDisable(GL_LIGHTING);
	for (int j = 0; j < faces.size(); j++){
		glColor3f(cor[0], cor[1], cor[2]);
		GLfloat ambient[] = { cor[0], cor[1], cor[2], .0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glBegin(GL_LINE_STRIP);
		glColor3f(1, 0, 0);
		for (int k = 0; k < faces[j].vertice.size(); k++){
			Point3D aux;
			Point3D temp;
			if (normais.size() > 0){
				aux.x = objectOperations[0][0] * normais[(faces[j].normais[k] - 1)].x + objectOperations[0][1] * normais[(faces[j].normais[k] - 1)].y + objectOperations[0][2] * normais[(faces[j].normais[k] - 1)].z;
				aux.y = objectOperations[1][0] * normais[(faces[j].normais[k] - 1)].x + objectOperations[1][1] * normais[(faces[j].normais[k] - 1)].y + objectOperations[1][2] * normais[(faces[j].normais[k] - 1)].z;
				aux.z = objectOperations[2][0] * normais[(faces[j].normais[k] - 1)].x + objectOperations[2][1] * normais[(faces[j].normais[k] - 1)].y + objectOperations[2][2] * normais[(faces[j].normais[k] - 1)].z;
				glNormal3d(aux.x, aux.y, aux.z);
			}
			aux.x = objectScale[0][0] * vertice[(faces[j].vertice[k] - 1)].x + objectScale[0][1] * vertice[(faces[j].vertice[k] - 1)].y + objectScale[0][2] * vertice[(faces[j].vertice[k] - 1)].z + objectScale[0][3];
			aux.y = objectScale[1][0] * vertice[(faces[j].vertice[k] - 1)].x + objectScale[1][1] * vertice[(faces[j].vertice[k] - 1)].y + objectScale[1][2] * vertice[(faces[j].vertice[k] - 1)].z + objectScale[1][3];
			aux.z = objectScale[2][0] * vertice[(faces[j].vertice[k] - 1)].x + objectScale[2][1] * vertice[(faces[j].vertice[k] - 1)].y + objectScale[2][2] * vertice[(faces[j].vertice[k] - 1)].z + objectScale[2][3];
			temp.x = objectOperations[0][0] * aux.x + objectOperations[0][1] * aux.y + objectOperations[0][2] * aux.z + objectOperations[0][3];
			temp.y = objectOperations[1][0] * aux.x + objectOperations[1][1] * aux.y + objectOperations[1][2] * aux.z + objectOperations[1][3];
			temp.z = objectOperations[2][0] * aux.x + objectOperations[2][1] * aux.y + objectOperations[2][2] * aux.z + objectOperations[2][3];
			glVertex3d(temp.x, temp.y, temp.z);
		}
		glEnd();
	}
	glEnable(GL_LIGHTING);
}
Face fachadaObjeto::scanFace(char buffer[256])
{
	Face faceOut;
	bool type1 = true, type2 = false, type3 = false;
	for (int i = 0; i < 255; i++){							//Checa o tipo da face
			if (buffer[i] == '/' && buffer[i + 1] == '/'){
			type3 = true;
			type1 = false;
			i = 256;
		}
		else if (buffer[i] == '/'){
			
			type2 = true;
			type1 = false;
			i = 256;
		}
	}
	char * face;
	face = strtok(buffer, " ");							 //"strtok" divide o char[]
	//"Lendo" a face:
	if (type1){
		while (face != NULL)
		{
			if (face[0] == 'f'){					
				face = strtok(NULL, " ");
			}
			else{										
				faceOut.vertice.push_back(stoi(face));	//String se torna inteiro

				face = strtok(NULL, " ");				//O parâmetro "NULL" faz com que a função guarde partes da ultima palavra que foi dividida com sucesso
			}
		}
		calcNormais(buffer, faceOut);
	}
	else if (type2){
		
		while (face != NULL)
		{
			if (face[0] == 'f'){
				face = strtok(NULL, " ");
			}
			else{
				int v, vt, vn;
				sscanf(face, "%d/%d/%d", &v, &vt, &vn);
				faceOut.vertice.push_back(v);
				faceOut.textura.push_back(vt);
				faceOut.normais.push_back(vn);
				face = strtok(NULL, " ");
			}
		}
	}
	else if (type3){
		while (face != NULL)
		{
			if (face[0] == 'f'){
				face = strtok(NULL, " ");
			}
			else{
				int v, vn;
				sscanf(face, "%d//%d", &v, &vn);
				faceOut.vertice.push_back(v);
				faceOut.normais.push_back(vn);
				face = strtok(NULL, " ");
			}
		}
	}
	return faceOut;
}
void fachadaObjeto::calcNormais(char buffer[256], Face faceOut){ 
	char * face;
	int v1, v2, v3, VI, VF;
	Point3D vector1, vector2, vectorOut;
	vectorOut.x = 0;
	vectorOut.y = 0;
	vectorOut.z = 0;
	face = strtok(buffer, " ");
	bool isLast = false;
	while (face != NULL)
	{
		if (face[0] == 'f'){
			face = strtok(NULL, " ");
			if (face != NULL){
				VI = stoi(face);
			}
		}
		else{
			v1 = stoi(face);
			face = strtok(NULL, " ");
			v2 = stoi(face);
			face = strtok(NULL, " ");
			v3 = stoi(face);
			face = strtok(NULL, " ");
			vector1.x = vertice[v2].x - vertice[v1].x;
			vector1.y = vertice[v2].y - vertice[v1].y;
			vector1.z = vertice[v2].z - vertice[v1].z;
			vector2.x = vertice[v3].x - vertice[v1].x;
			vector2.y = vertice[v3].y - vertice[v1].y;
			vector2.z = vertice[v3].z - vertice[v1].z;
			vectorProduct(vectorOut, vector1, vector2);
			normais.push_back(vectorOut);
			faceOut.normais.push_back(normais.size());
			vector1.x = vertice[v3].x - vertice[v2].x;
			vector1.y = vertice[v3].y - vertice[v2].y;
			vector1.z = vertice[v3].z - vertice[v2].z;
			vector2.x = vertice[v1].x - vertice[v2].x;
			vector2.y = vertice[v1].y - vertice[v2].y;
			vector2.z = vertice[v1].z - vertice[v2].z;
			vectorProduct(vectorOut, vector1, vector2);
			normais.push_back(vectorOut);
			faceOut.normais.push_back(normais.size());	
			vector1.x = vertice[v1].x - vertice[v3].x;
			vector1.y = vertice[v1].y - vertice[v3].y;
			vector1.z = vertice[v1].z - vertice[v3].z;
			vector2.x = vertice[v2].x - vertice[v3].x;
			vector2.y = vertice[v2].y - vertice[v3].y;
			vector2.z = vertice[v2].z - vertice[v3].z;
			vectorProduct(vectorOut, vector1, vector2);
			normais.push_back(vectorOut);
			faceOut.normais.push_back(normais.size());
		}
	}
}
void fachadaObjeto::vectorProduct(Point3D out, Point3D vector1, Point3D vector2){
	out.x = (vector1.y*vector2.z) - (vector1.z*vector2.y);
	out.y = (vector1.z*vector2.x) - (vector1.x*vector2.z);
	out.z = (vector1.x*vector2.y) - (vector1.y*vector2.x);
}