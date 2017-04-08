#include "matriz.h"
#include "fachada.h"
void fachadaMatriz::trans(GLdouble x, GLdouble y, GLdouble z, GLdouble matrixOperation[4][4]){
	matrixOperation[0][0] = 1;
	matrixOperation[0][1] = 0;
	matrixOperation[0][2] = 0;
	matrixOperation[0][3] = x;
	matrixOperation[1][0] = 0;
	matrixOperation[1][1] = 1;
	matrixOperation[1][2] = 0;
	matrixOperation[1][3] = y;
	matrixOperation[2][0] = 0;
	matrixOperation[2][1] = 0;
	matrixOperation[2][2] = 0;
	matrixOperation[2][3] = z;
	matrixOperation[3][0] = 0;
	matrixOperation[3][1] = 0;
	matrixOperation[3][2] = 0;
	matrixOperation[3][3] = 1;
}
void fachadaMatriz::rotX(GLdouble degree, GLdouble matrixOperation[4][4]){
	GLdouble senRotacao = sin(degree * M_PI / 180);
	GLdouble cosRotacao = cos(degree * M_PI / 180);
	matrixOperation[0][0] = 1;
	matrixOperation[0][1] = 0;
	matrixOperation[0][2] = 0;
	matrixOperation[0][3] = 0;
	matrixOperation[1][0] = 0;
	matrixOperation[1][1] = cosRotacao;
	matrixOperation[1][2] = -senRotacao;
	matrixOperation[1][3] = 0;
	matrixOperation[2][0] = 0;
	matrixOperation[2][1] = senRotacao;
	matrixOperation[2][2] = cosRotacao;
	matrixOperation[2][3] = 0;
	matrixOperation[3][0] = 0;
	matrixOperation[3][1] = 0;
	matrixOperation[3][2] = 0;
	matrixOperation[3][3] = 1;
}
void fachadaMatriz::rotY(GLdouble degree, GLdouble matrixOperation[4][4]){
	GLdouble senRotacao = sin(degree * M_PI / 180);
	GLdouble cosRotacao = cos(degree * M_PI / 180);
	matrixOperation[0][0] = cosRotacao;
	matrixOperation[0][1] = 0;
	matrixOperation[0][2] = senRotacao;
	matrixOperation[0][3] = 0;
	matrixOperation[1][0] = 0;
	matrixOperation[1][1] = 1;
	matrixOperation[1][2] = 0;
	matrixOperation[1][3] = 0;
	matrixOperation[2][0] = -senRotacao;
	matrixOperation[2][1] = 0;
	matrixOperation[2][2] = cosRotacao;
	matrixOperation[2][3] = 0;
	matrixOperation[3][0] = 0;
	matrixOperation[3][1] = 0;
	matrixOperation[3][2] = 0;
	matrixOperation[3][3] = 1;
}
void fachadaMatriz::rotZ(GLdouble degree, GLdouble matrixOperation[4][4]){
	GLdouble senRotacao = sin(degree * M_PI / 180);
	GLdouble cosRotacao = cos(degree * M_PI / 180);
	matrixOperation[0][0] = cosRotacao;
	matrixOperation[0][1] = -senRotacao;
	matrixOperation[0][2] = 0;
	matrixOperation[0][3] = 0;
	matrixOperation[1][0] = senRotacao;
	matrixOperation[1][1] = cosRotacao;
	matrixOperation[1][2] = 0;
	matrixOperation[1][3] = 0;
	matrixOperation[2][0] = 0;
	matrixOperation[2][1] = 0;
	matrixOperation[2][2] = 1;
	matrixOperation[2][3] = 0;
	matrixOperation[3][0] = 0;
	matrixOperation[3][1] = 0;
	matrixOperation[3][2] = 0;
	matrixOperation[3][3] = 1;
}
void fachadaMatriz::rodrigues(Point3D axis, GLdouble degree, GLdouble matrixOperation[4][4]){
	GLdouble senRotacao = sin(degree * M_PI / 180);
	GLdouble cosRotacao = cos(degree * M_PI / 180);
	matrixOperation[0][0] = cosRotacao + pow(axis.x, 2)*(1 - cosRotacao);
	matrixOperation[0][1] = axis.x * axis.y * (1 - cosRotacao) - axis.z * senRotacao;
	matrixOperation[0][2] = axis.y * senRotacao + axis.x * axis.z * (1 - cosRotacao);
	matrixOperation[0][3] = 0;
	matrixOperation[1][0] = axis.z * senRotacao + axis.x * axis.y * (1 - cosRotacao);
	matrixOperation[1][1] = cosRotacao + pow(axis.y, 2)*(1 - cosRotacao);
	matrixOperation[1][2] = -axis.x * senRotacao + axis.y * axis.z * (1 - cosRotacao);
	matrixOperation[1][3] = 0;
	matrixOperation[2][0] = -axis.y * senRotacao + axis.x * axis.z * (1 - cosRotacao);
	matrixOperation[2][1] = axis.x * senRotacao + axis.y * axis.z * (1 - cosRotacao);
	matrixOperation[2][2] = cosRotacao + pow(axis.z, 2)*(1 - cosRotacao);
	matrixOperation[2][3] = 0;
	matrixOperation[3][0] = 0;
	matrixOperation[3][1] = 0;
	matrixOperation[3][2] = 0;
	matrixOperation[3][3] = 1;
}
void fachadaMatriz::trans(GLdouble matrixOut[4][4], GLdouble matrix[4][4]){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			matrixOut[i][j] = matrix[j][i];
		}
	}
}
void fachadaMatriz::identity(GLdouble matrix[4][4]){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			matrix[i][j] = 0;
			if (i == j){
				matrix[i][j] = 1;
			}
		}
	}
}
void fachadaMatriz::zero(GLdouble matrix[4][4]){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			matrix[i][j] = 0;
		}
	}
}
void fachadaMatriz::multMatrix(GLdouble matrixOut[4][4], GLdouble matrix1[4][4], GLdouble matrix2[4][4]){
	zero(matrixOut);
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 4; k++){
				matrixOut[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}
bool fachadaMatriz::invert(const double m[4][4], double invOut[4][4])
{
	double inv[4][4], det;
	int i;
	inv[0][0] = m[1][1] * m[2][2] * m[3][3] -
		m[1][1] * m[2][3] * m[3][2] -
		m[2][1] * m[1][2] * m[3][3] +
		m[2][1] * m[1][3] * m[3][2] +
		m[3][1] * m[1][2] * m[2][3] -
		m[3][1] * m[1][3] * m[2][2];
	inv[1][0] = -m[1][0] * m[2][2] * m[3][3] +
		m[1][0] * m[2][3] * m[3][2] +
		m[2][0] * m[1][2] * m[3][3] -
		m[2][0] * m[1][3] * m[3][2] -
		m[3][0] * m[1][2] * m[2][3] +
		m[3][0] * m[1][3] * m[2][2];
	inv[2][0] = m[1][0] * m[2][1] * m[3][3] -
		m[1][0] * m[2][3] * m[3][1] -
		m[2][0] * m[1][1] * m[3][3] +
		m[2][0] * m[1][3] * m[3][1] +
		m[3][0] * m[1][1] * m[2][3] -
		m[3][0] * m[1][3] * m[2][1];
	inv[3][0] = 0;
	inv[0][1] = -m[0][1] * m[2][2] * m[3][3] +
		m[0][1] * m[2][3] * m[3][2] +
		m[2][1] * m[0][2] * m[3][3] -
		m[2][1] * m[0][3] * m[3][2] -
		m[3][1] * m[0][2] * m[2][3] +
		m[3][1] * m[0][3] * m[2][2];
	inv[1][1] = m[0][0] * m[2][2] * m[3][3] -
		m[0][0] * m[2][3] * m[3][2] -
		m[2][0] * m[0][2] * m[3][3] +
		m[2][0] * m[0][3] * m[3][2] +
		m[3][0] * m[0][2] * m[2][3] -
		m[3][0] * m[0][3] * m[2][2];
	inv[2][1] = -m[0][0] * m[2][1] * m[3][3] +
		m[0][0] * m[2][3] * m[3][1] +
		m[2][0] * m[0][1] * m[3][3] -
		m[2][0] * m[0][3] * m[3][1] -
		m[3][0] * m[0][1] * m[2][3] +
		m[3][0] * m[0][3] * m[2][1];
	inv[3][1] = 0;
	inv[0][2] = m[0][1] * m[1][2] * m[3][3] -
		m[0][1] * m[1][3] * m[3][2] -
		m[1][1] * m[0][2] * m[3][3] +
		m[1][1] * m[0][3] * m[3][2] +
		m[3][1] * m[0][2] * m[1][3] -
		m[3][1] * m[0][3] * m[1][2];
	inv[1][2] = -m[0][0] * m[1][2] * m[3][3] +
		m[0][0] * m[1][3] * m[3][2] +
		m[1][0] * m[0][2] * m[3][3] -
		m[1][0] * m[0][3] * m[3][2] -
		m[3][0] * m[0][2] * m[1][3] +
		m[3][0] * m[0][3] * m[1][2];
	inv[2][2] = m[0][0] * m[1][1] * m[3][3] -
		m[0][0] * m[1][3] * m[3][1] -
		m[1][0] * m[0][1] * m[3][3] +
		m[1][0] * m[0][3] * m[3][1] +
		m[3][0] * m[0][1] * m[1][3] -
		m[3][0] * m[0][3] * m[1][1];
	inv[3][2] = 0;
	inv[0][3] = 0;
	inv[1][3] = 0;
	inv[2][3] = 0;
	inv[3][3] = 1;
	det = m[0][0] * inv[0][0] + m[0][1] * inv[1][0] + m[0][2] * inv[2][0] + m[0][3] * inv[3][0];
	if (det == 0)
		return false;
		det = 1.0 / det;
	for (i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			invOut[i][j] = inv[i][j] * det;
		}
	}
	return true;
}