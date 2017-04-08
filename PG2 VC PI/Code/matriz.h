#pragma once
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <GL\glut.h>
#include <cmath>
#include "estrutura.h"

class fachadaMatriz
{
public:
	fachadaMatriz();
	~fachadaMatriz();
	static void trans(GLdouble x, GLdouble y, GLdouble z, GLdouble matrixOperation[4][4]);
	static void rotX(GLdouble degree, GLdouble matrixOperation[4][4]);
	static void rotY(GLdouble degree, GLdouble matrixOperation[4][4]);
	static void rotZ(GLdouble degree, GLdouble matrixOperation[4][4]);
	static void rodrigues(Point3D axis, GLdouble degree, GLdouble matrixOperation[4][4]);
	static void trans(GLdouble matrixOut[4][4], GLdouble matrix[4][4]);
	static void identity(GLdouble matrix[4][4]);
	static void zero(GLdouble matrix[4][4]);
	static void multMatrix(GLdouble matrixOut[4][4], GLdouble matrix1[4][4], GLdouble matrix2[4][4]);
	static bool invert(const double m[4][4], double invOut[4][4]);
};

