#include "fachada.h"


fachada::fachada()
{
}
fachada::~fachada()
{
}
void fachada::loadObject(string filepath){
	fachadaObjeto temp;
	temp.loadObject(filepath);
	objetos.push_back(temp);
}
void fachada::renderObjetos(){
	for (GLint i = 0; i < objetos.size(); i++){
		objetos[i].renderObj();
		if (i == selecObjeto){
			objetos[i].renderLinhas();
		}
	}
}
void fachada::renderObjDiretor(){
	for (GLint i = 0; i < objetos.size(); i++){
		objetos[i].renderObj();
	}
	camera.renderObjMultMatrix(directorOperations);
}
void fachada::initDirector(){
	fachadaMatriz::identity(directorCamera.operations);
	GLdouble matrixY[4][4], matrixX[4][4], matrixDirectorRot[4][4], temp[4][4];
	fachadaMatriz::rotY(-90, matrixY);
	fachadaMatriz::rotX(30, matrixX);
	fachadaMatriz::multMatrix(directorCamera.operations, matrixX, matrixY);
	directorCamera.operations[0][3] = 0;
	directorCamera.operations[1][3] = 3;
	directorCamera.operations[2][3] = -25;
	directorCamera.operations[3][3] = 1;
	fachadaMatriz::identity(directorOperations);
}
void fachada::criarLuz(){
	bool newLight = false;
	Point4D temp;
	Point4D aux;
	if (lightNumber == 8){
		cout << "Max number of light sources" << endl;
	}
	else {
		cout << "Enter the light position: \nx = ";
		cin >> temp.x;
		cout << "y = ";
		cin >> temp.y;
		cout << "z = ";
		cin >> temp.z;
		cout << "w = ";
		cin >> temp.w;
		cout << endl;
		cout << "Enter the light color: \nR = ";
		cin >> aux.x;
		cout << "G = ";
		cin >> aux.y;
		cout << "B = ";
		cin >> aux.z;
		cout << "A = ";
		cin >> aux.w;
		cout << endl;
		float col[] = { (GLfloat)aux.x, (GLfloat)aux.y, (GLfloat)aux.z, (GLfloat)aux.w };
		switch (lightNumber){
		case 0:
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
			lightNumber++;
			newLight = true;
			break;
		case 1:
			glEnable(GL_LIGHT1);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, col);
			lightNumber++;
			newLight = true;
			break;
		case 2:
			glEnable(GL_LIGHT2);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, col);
			lightNumber++;
			newLight = true;
			break;
		case 3:
			glEnable(GL_LIGHT3);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, col);
			lightNumber++;
			newLight = true;
			break;
		case 4:
			glEnable(GL_LIGHT4);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, col);
			lightNumber++;
			newLight = true;
			break;
		case 5:
			glEnable(GL_LIGHT5);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, col);
			lightNumber++;
			newLight = true;
			break;
		case 6:
			glEnable(GL_LIGHT6);
			glLightfv(GL_LIGHT6, GL_DIFFUSE, col);
			lightNumber++;
			newLight = true;
			break;
		case 7:
			glEnable(GL_LIGHT7);
			glLightfv(GL_LIGHT7, GL_DIFFUSE, col);
			lightNumber++;
			newLight = true;
			break;
		}
	}

	if (newLight){
		Light light;
		light.cor = aux;
		light.position = temp;
		luz.push_back(light);
	}
}
void fachada::renderLuz(){
	GLint aux = -1;
	if (selecObjeto > objetos.size()-1){
		aux = selecObjeto - objetos.size();
	}
	if (lightNumber > 0){
		
		float pos[] = { luz[0].position.x, luz[0].position.y, luz[0].position.z, luz[0].position.w };
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
	}
	if (lightNumber > 1){
		
		float pos[] = { luz[1].position.x, luz[1].position.y, luz[1].position.z, luz[1].position.w };
		glLightfv(GL_LIGHT1, GL_POSITION, pos);
	}
	if (lightNumber > 2){
		
		float pos[] = { luz[2].position.x, luz[2].position.y, luz[2].position.z, luz[2].position.w };
		glLightfv(GL_LIGHT2, GL_POSITION, pos);
	}
	if (lightNumber > 3){
		
		float pos[] = { luz[3].position.x, luz[3].position.y, luz[3].position.z, luz[3].position.w };
		glLightfv(GL_LIGHT3, GL_POSITION, pos);
	}
	if (lightNumber > 4){
		
		float pos[] = { luz[4].position.x, luz[4].position.y, luz[4].position.z, luz[4].position.w };
		glLightfv(GL_LIGHT4, GL_POSITION, pos);
	}
	if (lightNumber > 5){
		
		float pos[] = { luz[5].position.x, luz[5].position.y, luz[5].position.z, luz[5].position.w };
		glLightfv(GL_LIGHT5, GL_POSITION, pos);
	}
	if (lightNumber > 6){
		
		float pos[] = { luz[6].position.x, luz[6].position.y, luz[6].position.z, luz[6].position.w };
		glLightfv(GL_LIGHT6, GL_POSITION, pos);
	}
	if (lightNumber > 7){

		float pos[] = { luz[7].position.x, luz[7].position.y, luz[7].position.z, luz[7].position.w };
		glLightfv(GL_LIGHT7, GL_POSITION, pos);
	}
}
void fachada::transCamera(GLdouble x, GLdouble y, GLdouble z){
	userCamera.operations[0][3] += x;
	userCamera.operations[1][3] += y;
	userCamera.operations[2][3] += z;
	directorOperations[0][3] -= x;
	directorOperations[1][3] -= y;
	directorOperations[2][3] -= z;
}
void fachada::rotCamera(GLdouble rot, GLdouble x, GLdouble y, GLdouble z){
	GLdouble matrixOperation[4][4], matrixOperation2[4][4];
	bool isOperation = false;
	if (x == 1){
		userCamera.rotacX += rot;
		if (userCamera.rotacX > 359){
			userCamera.rotacX = userCamera.rotacX - 359;
		}
		else if (userCamera.rotacX < 0){
			userCamera.rotacX = userCamera.rotacX + 359;
		}
		fachadaMatriz::rotX(rot, matrixOperation);
		isOperation = true;
	} 
	else if (y == 1){
		userCamera.rotacY += rot;
		if (userCamera.rotacY > 359){
			userCamera.rotacY = userCamera.rotacY - 359;
		}
		else if (userCamera.rotacY < 0){
			userCamera.rotacY = userCamera.rotacY + 359;
		}
		Point3D axis;
		axis.x = userCamera.operations[0][1];
		axis.y = userCamera.operations[1][1];
		axis.z = userCamera.operations[2][1];
		fachadaMatriz::rodrigues(axis, rot, matrixOperation);
		isOperation = true;
	}
	else if (z == 1){
		userCamera.rotacZ += rot;
		if (userCamera.rotacZ > 359){
			userCamera.rotacZ = userCamera.rotacZ - 359;
		}
		else if (userCamera.rotacZ < 0){
			userCamera.rotacZ = userCamera.rotacZ + 359;
		}
		fachadaMatriz::rotZ(rot, matrixOperation);
		isOperation = true;
	}
	if (isOperation){
		GLdouble temp[4][4];
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				temp[i][j] = userCamera.operations[i][j];
			}
		}
		fachadaMatriz::multMatrix(userCamera.operations, matrixOperation, temp);
	}	
}
void fachada::transObjeto(GLint selectedObject, GLdouble x, GLdouble y, GLdouble z){
		objetos[selectedObject].xPosition += x;
		objetos[selectedObject].yPosition += y;
		objetos[selectedObject].zPosition += z;
		objetos[selectedObject].objectOperations[0][3] = objetos[selectedObject].xPosition;
		objetos[selectedObject].objectOperations[1][3] = objetos[selectedObject].yPosition;
		objetos[selectedObject].objectOperations[2][3] = objetos[selectedObject].zPosition;
}
void fachada::escalaObjeto(GLint selectedObject, GLdouble scaleX, GLdouble scaleY, GLdouble scaleZ){
	objetos[selectedObject].objectScale[0][0] += scaleX;
	objetos[selectedObject].objectScale[1][1] += scaleY;
	objetos[selectedObject].objectScale[2][2] += scaleZ;
}
void fachada::rotObjeto(GLint selectedObject, GLdouble rot, GLdouble x, GLdouble y, GLdouble z){
	GLdouble matrixOperation[4][4];
	bool isOperation = false;
	if (x == 1){
		objetos[selectedObject].rotacX += rot;
		fachadaMatriz::rotX(rot, matrixOperation);
		isOperation = true;
	}
	else if (y == 1){
		objetos[selectedObject].rotacY += rot;
		fachadaMatriz::rotY(rot, matrixOperation);
		isOperation = true;
	}
	else if (z == 1){
		objetos[selectedObject].rotacZ += rot;
		fachadaMatriz::rotZ(rot, matrixOperation);
		isOperation = true;
	}
	if (isOperation){
		if (objetos[selectedObject].rotacX > 359){
			objetos[selectedObject].rotacX = 0;
		}
		else if (objetos[selectedObject].rotacX < 0){
			objetos[selectedObject].rotacX = 359;
		}
		if (objetos[selectedObject].rotacY > 359){
			objetos[selectedObject].rotacY = 0;
		}
		else if (objetos[selectedObject].rotacY < 0){
			objetos[selectedObject].rotacY = 359;
		}
		if (objetos[selectedObject].rotacZ > 359){
			objetos[selectedObject].rotacZ = 0;
		}
		else if (objetos[selectedObject].rotacZ < 0){
			objetos[selectedObject].rotacZ = 359;
		}
		GLdouble temp[4][4];
		fachadaMatriz::identity(temp);
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				temp[i][j] = objetos[selectedObject].objectOperations[i][j];
			}
		}
		fachadaMatriz::multMatrix(objetos[selectedObject].objectOperations, matrixOperation, temp);
		objetos[selectedObject].objectOperations[0][3] = objetos[selectedObject].xPosition;
		objetos[selectedObject].objectOperations[1][3] = objetos[selectedObject].yPosition;
		objetos[selectedObject].objectOperations[2][3] = objetos[selectedObject].zPosition;
		objetos[selectedObject].objectOperations[3][3] = 1;
	}
}
void fachada::transLuz(GLint selectedLight, GLdouble x, GLdouble y, GLdouble z){
	luz[selectedLight].position.x += x;
	luz[selectedLight].position.y += y;
	luz[selectedLight].position.z += z;
	cout << luz[selectedLight].position.y << endl;
}
void fachada::planoCartesiano(GLdouble density, GLdouble left, GLdouble right, GLdouble near, GLdouble far, GLdouble height, GLdouble color[4]){
	glDisable(GL_LIGHTING);
	GLdouble temp = left;
	glBegin(GL_LINES);
	while (left < right){
		glColor4d(color[0], color[1], color[2], color[3]);
		glVertex3d(left, height, near);
		left += density;
		glVertex3d(left, height, far);
		left += density;
	}
	glEnd();
	left = temp;
	glBegin(GL_LINES);
	while (near < far){
		glColor4d(color[0], color[1], color[2], color[3]);
		glVertex3d(left, height, near);
		near += density;
		glVertex3d(right, height, near);
		near += density;
	}
	glEnd();
	glEnable(GL_LIGHTING);
}
void fachada::chao(GLdouble size, GLdouble height){
}