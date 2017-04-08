#include "Main.h"
#include "util.h"
#include <math.h>
#include <Windows.h>
#include <math.h>

// OpenCV includes
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <ctype.h>

using namespace cv;
#define HISTOGRAM_img false
#define HISTOGRAM_vd false

#define GAUSSIAN_img false
#define GAUSSIAN_vd false
#define GAUSSIAN_Size 3


//Caminhos da imagem e do vídeo
string caminhoIMG = "Resources\\pgim.jpg";
string caminhoVideo = "Resources\\pg.mp4";

float chaoParede = 8;

//inicializadores
GLfloat mouse_x, mouse_y;

//constantes
const double translateCameraConst = .1;
const double rotateCameraConst = 0.03;
const double rotateCameraMouseConst = 0.003;

bool buffer[250];

double frustrumTop, frustrumBottom, frustrumLeft, frustrumRight;
double g_Width, g_Height;
double zfar = 100.0f;
double znear = 0.1f;
GLdouble fovy = 45;

double focalDistance = 1;
double mousex, mousey;
double deltax, deltay;
dMatrix KMdMatrix(4, dVector(4));
dMatrix projM = dMatrix(4, dVector(4));
dMatrix extM = dMatrix(4, dVector(4));
dMatrix intrM = dMatrix(4, dVector(4));

GLfloat  K[9], projMatrix[16], extrinsic[16], intrisic[16];

dMatrix Ext = dMatrix(4, dVector(4));

void Encerrar()
{
	exit(1);
}


int frames = 0;
float times = 0;
float timebase = 0;

void printFPS(){
	frames++;
	times = glutGet(GLUT_ELAPSED_TIME);
	if (times - timebase > 1000) {
		printf("FPS: %4.2lf\n",
			(double)frames*1000.0 / ((double)(times - timebase)));
		timebase = times;
		frames = 0;
	}
}



Mat	cameraImage, originalGrayTexture, originalColorTexture,
keypointsImage, descriptor1, descriptor2, img_matches,
cameraGrayImage, laplacianCamera;

VideoCapture vid(caminhoVideo);
vector<KeyPoint> cameraKeypoints, imageKeypoints;
vector<Point3d>	features3D;
vector<Point2d>	features2D;

FlannBasedMatcher matcher;
vector<DMatch>	matches, goodMatches;

SiftFeatureDetector	siftDetector;
SiftDescriptorExtractor siftExtractor;

OrbFeatureDetector	orbDetector;
OrbDescriptorExtractor orbExtractor;

SurfFeatureDetector	surfDetector(1000);
SurfDescriptorExtractor	surfExtractor;


std::time_t result = std::time(nullptr);
std::time_t one_second = std::time(nullptr);


//To find the object
std::vector<Point2f> obj;
std::vector<Point2f> scene;
Mat homography;
std::vector<Point2f> obj_corners(4);
std::vector<Point2f> scene_corners(4);
Mat H;
Point2f TL, TR, BL, BR;
float ZTL, ZTR, ZBL, ZBR;
string windows1 = "Capturando";
//When we equalize the histogram, the feature detection works worse than in normal lighting situations
//However when the scene changes the lighting, equalize the histogram makes the feature detection works better

Mat textureGrayTemp, cameraGrayTemp;



void processarObjetoSurf(){
	originalGrayTexture = imread(caminhoIMG, CV_LOAD_IMAGE_GRAYSCALE);
	originalColorTexture = imread(caminhoIMG, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
	if (HISTOGRAM_img){
		equalizeHist(originalGrayTexture, textureGrayTemp);
		textureGrayTemp.copyTo(originalGrayTexture);
	}
	
	if (GAUSSIAN_img){
		GaussianBlur(originalGrayTexture, textureGrayTemp, Size(GAUSSIAN_Size, GAUSSIAN_Size), 0);
		textureGrayTemp.copyTo(originalGrayTexture);
	}
	surfDetector.detect(originalColorTexture, imageKeypoints);
	surfExtractor.compute(originalColorTexture, imageKeypoints, descriptor1);
}

void processarCenaSurf(){
	vid >> cameraImage;

	if (cameraImage.data){
		cvtColor(cameraImage, cameraGrayImage, CV_RGB2GRAY);
		//cameraImage = imread("Resources/test.jpg", CV_LOAD_IMAGE_COLOR);
		if (HISTOGRAM_vd){
			equalizeHist(cameraGrayImage, cameraGrayTemp);
			cameraGrayTemp.copyTo(cameraGrayImage);
		}

		if (GAUSSIAN_vd){
			GaussianBlur(cameraGrayImage, cameraGrayTemp, Size(GAUSSIAN_Size, GAUSSIAN_Size), 0);
			cameraGrayTemp.copyTo(cameraGrayImage);
		}
		surfDetector.detect(cameraGrayImage, cameraKeypoints);
		surfExtractor.compute(cameraGrayImage, cameraKeypoints, descriptor2);
	}
}



void processarObjetoSIFT(){
	originalGrayTexture = imread(caminhoIMG, CV_LOAD_IMAGE_GRAYSCALE);
	originalColorTexture = imread(caminhoIMG, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
	if (HISTOGRAM_img){
		equalizeHist(originalGrayTexture, textureGrayTemp);
		textureGrayTemp.copyTo(originalGrayTexture);
	}

	if (GAUSSIAN_img){
		GaussianBlur(originalGrayTexture, textureGrayTemp, Size(GAUSSIAN_Size, GAUSSIAN_Size), 0);
		textureGrayTemp.copyTo(originalGrayTexture);
	}
	siftDetector.detect(originalColorTexture, imageKeypoints);
	siftExtractor.compute(originalColorTexture, imageKeypoints, descriptor1);
}

void processarCenaSIFT(){
vid >> cameraImage;
	if (cameraImage.data){
	cvtColor(cameraImage, cameraGrayImage, CV_RGB2GRAY);
	//cameraImage = imread("Resources/test.jpg", CV_LOAD_IMAGE_COLOR);
	if (HISTOGRAM_vd){
		equalizeHist(cameraGrayImage, cameraGrayTemp);
		cameraGrayTemp.copyTo(cameraGrayImage);
	}

	if (GAUSSIAN_vd){
		GaussianBlur(cameraGrayImage, cameraGrayTemp, Size(GAUSSIAN_Size, GAUSSIAN_Size), 0);
		cameraGrayTemp.copyTo(cameraGrayImage);
	}
	siftDetector.detect(cameraGrayImage, cameraKeypoints);
	siftExtractor.compute(cameraGrayImage, cameraKeypoints, descriptor2);
	}
}

void processarObjetoORB(){
	originalGrayTexture = imread(caminhoIMG, CV_LOAD_IMAGE_GRAYSCALE);
	originalColorTexture = imread(caminhoIMG, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
	if (HISTOGRAM_img){
		equalizeHist(originalGrayTexture, textureGrayTemp);
		textureGrayTemp.copyTo(originalGrayTexture);
	}

	if (GAUSSIAN_vd){
		GaussianBlur(originalGrayTexture, textureGrayTemp, Size(GAUSSIAN_Size, GAUSSIAN_Size), 0);
		textureGrayTemp.copyTo(originalGrayTexture);
	}
	orbDetector.detect(originalGrayTexture, imageKeypoints);
	orbExtractor.compute(originalGrayTexture, imageKeypoints, descriptor1);
}

void processarCenaORB(){
	vid >> cameraImage;

	if (cameraImage.data){
	cvtColor(cameraImage, cameraGrayImage, CV_RGB2GRAY);
	//cameraImage = imread("Resources/test.jpg", CV_LOAD_IMAGE_COLOR);
	if (HISTOGRAM_vd){
		equalizeHist(cameraGrayImage, cameraGrayTemp);
		cameraGrayTemp.copyTo(cameraGrayImage);
	}

	if (GAUSSIAN_vd){
		GaussianBlur(cameraGrayImage, cameraGrayTemp, Size(GAUSSIAN_Size, GAUSSIAN_Size), 0);
		cameraGrayTemp.copyTo(cameraGrayImage);
	}
	orbDetector.detect(cameraGrayImage, cameraKeypoints);
	orbExtractor.compute(cameraGrayImage, cameraKeypoints, descriptor2);
	}
}




void rastrear(){
	processarCenaSurf();

	matcher.match(descriptor1, descriptor2, matches);

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptor1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	std::vector< DMatch > good_matches;

	for (int i = 0; i < descriptor1.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}


	drawMatches(originalColorTexture, imageKeypoints, cameraImage, cameraKeypoints,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//-- Localize the object
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		obj.push_back(imageKeypoints[good_matches[i].queryIdx].pt);
		scene.push_back(cameraKeypoints[good_matches[i].trainIdx].pt);
	}

	H = findHomography(obj, scene, CV_RANSAC);



	//-- Get the corners from the image_1 ( the object to be "detected" )
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(originalColorTexture.cols, 0);
	obj_corners[2] = cvPoint(originalColorTexture.cols, originalColorTexture.rows); obj_corners[3] = cvPoint(0, originalColorTexture.rows);
	std::vector<Point2f> scene_corners(4);

	perspectiveTransform(obj_corners, scene_corners, H);

	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
	line(img_matches, scene_corners[0] + Point2f(originalColorTexture.cols, 0), scene_corners[1] + Point2f(originalColorTexture.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[1] + Point2f(originalColorTexture.cols, 0), scene_corners[2] + Point2f(originalColorTexture.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[2] + Point2f(originalColorTexture.cols, 0), scene_corners[3] + Point2f(originalColorTexture.cols, 0), Scalar(0, 255, 0), 4);
	line(img_matches, scene_corners[3] + Point2f(originalColorTexture.cols, 0), scene_corners[0] + Point2f(originalColorTexture.cols, 0), Scalar(0, 255, 0), 4);


	TR = scene_corners[1];
	BR = scene_corners[2];
	BL = scene_corners[3];
	TL = scene_corners[0];
	


	printFPS();
	//-- Show detected matches

	cameraKeypoints.clear();

}



void initCV()
{	//escolher qual algoritmo utilisar: Sift, Orb ou surf
	processarObjetoSurf();
}

void initialize()
{
	initCV();

	glClearColor(0.5f, 0.5f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);							// Enables Depth Testing
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	//inicializa a matriz extrinsica;
	Ext[0][0] = 1; Ext[1][1] = 1; Ext[2][2] = -1; Ext[3][3] = 1;
}

void cameraTranslate(double ctx, double cty, double ctz)
{
	Ext[0][3] += ctx;
	Ext[1][3] += cty;
	Ext[2][3] += ctz;
}

/*
angle em rad
*/
void cameraRotateY(double angle)
{
	dMatrix roty(4, dVector(4));
	dMatrix iNeg(4, dVector(4));

	roty[0][0] = cos(angle);
	roty[0][2] = sin(angle);
	roty[1][1] = 1;
	roty[2][0] = -sin(angle);
	roty[2][2] = cos(angle);
	roty[3][3] = 1;

	iNeg[0][0] = -1;
	iNeg[0][1] = 0;
	iNeg[0][2] = 0;
	iNeg[0][3] = 0;

	iNeg[1][0] = 0;
	iNeg[1][1] = -1;
	iNeg[1][2] = 0;
	iNeg[1][3] = 0;
	iNeg[2][0] = 0;

	iNeg[2][0] = 0;
	iNeg[2][1] = 0;
	iNeg[2][2] = -1;
	iNeg[2][3] = 0;

	iNeg[3][0] = 0;
	iNeg[3][1] = 0;
	iNeg[3][2] = 0;
	iNeg[3][3] = -1;

	dVector T(4);
	T[0] = Ext[0][3];
	T[1] = Ext[1][3];
	T[2] = Ext[2][3];
	T[3] = 1;

	dMatrix R = getRotationNN(Ext);
	dMatrix Rt = transpose(R);
	dVector C = multiplicacaoN1(Rt, T);
	C = multiplicacaoN1(iNeg, C);

	R = multiplicacaoNN(R, roty);
	T = multiplicacaoN1(R, C);
	T = multiplicacaoN1(iNeg, T);
	Ext = R;
	Ext[0][3] = T[0];
	Ext[1][3] = T[1];
	Ext[2][3] = T[2];
}



void normalizeCamera()
{
	double tx = Ext[0][3], ty = Ext[1][3], tz = Ext[2][3];

	Ext[0][3] = 0; Ext[1][3] = 0; Ext[2][3] = 0;

	for (int i = 0; i < 4; i++)
	{
		Ext[i] = normalize(Ext[i]);
	}

	Ext[0][3] = tx; Ext[1][3] = ty; Ext[2][3] = tz;
}

void myreshape(GLsizei w, GLsizei h)
{
	g_Width = w;
	g_Height = h;

	glViewport(0, 0, g_Width, g_Height);

	frustrumTop = tan(fovy * 3.14159 / 360) * 0.1;
	frustrumBottom = -frustrumTop;
	frustrumLeft = g_Width / g_Width * frustrumBottom;
	frustrumRight = g_Width / g_Height * frustrumTop;

	znear = 0.1f;
}

void drawGrid()
{
	glPushMatrix();

	glTranslatef(-(chaoParede / 2), 0, -(chaoParede / 2));

	glColor3f(0, 0, 0);

	glBegin(GL_LINES);

	for (int i = 0; i <= chaoParede; i++)
	{
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, chaoParede);
		glVertex3f(0, 0, i);
		glVertex3f(chaoParede, 0, i);
	};

	glEnd();

	glPopMatrix();

	glPushMatrix();

	glTranslatef(-(chaoParede / 2), 0, -(chaoParede / 2));

	glColor3f(0, 0, 0);

	glBegin(GL_LINES);

	for (int i = 0; i <= chaoParede; i++)
	{
		glVertex3f(i, 0, 0);
		glVertex3f(i, chaoParede, 0);
		glVertex3f(0, i, 0);
		glVertex3f(chaoParede, i, 0);
	};

	glEnd();

	glPopMatrix();

	
}

void updateCV()
{
	vid >> cameraImage;

	// loopzinho
	if (vid.get(CV_CAP_PROP_POS_FRAMES) == 500)
	{
		vid.set(CV_CAP_PROP_POS_FRAMES, 10);
	}

	rastrear();

	imshow("Casamento das features", img_matches);
}

// aqui o sistema de coordenadas da tela está variando de -1 a 1 no eixo x e y
void mydisplay()
{
	// OpenCV Processing

	updateCV();

	// End of OpenCV Processing

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, g_Width, g_Height);

	glFrustum(frustrumLeft, frustrumRight, frustrumBottom, frustrumTop, znear, zfar);

	glMatrixMode(GL_MODELVIEW);

	glClearColor(1, 1, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat extrinsic[16] =
	{
		Ext[0][0], Ext[1][0], Ext[2][0], Ext[3][0],
		Ext[0][1], Ext[1][1], Ext[2][1], Ext[3][1],
		Ext[0][2], Ext[1][2], Ext[2][2], Ext[3][2],
		Ext[0][3], Ext[1][3], Ext[2][3], Ext[3][3],
	};

	glMatrixMode(GL_MODELVIEW);

	glLoadMatrixf(extrinsic);

	glPushMatrix();

	glTranslatef(0, -(chaoParede / 2), 9);

	drawGrid();

	glPopMatrix();

	glColor3f(1, 0, 1);

	glPushMatrix();

	glTranslatef(-1, 1, 3);
	glRotatef(180, 0, 1, 0);
	glRotatef(180, 0, 0, 1);
	glBegin(GL_QUADS);

	glVertex3f(TL.x / 500, TL.y / 500, ZTL);
	glVertex3f(BL.x / 500, BL.y / 500, ZBL);
	glVertex3f(BR.x / 500, BR.y / 500, ZBR);
	glVertex3f(TR.x / 500, TR.y / 500, ZTR);

	glEnd();
	glPopMatrix();

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void handleKeyboardPressed(unsigned char key, int x, int y){
	buffer[(int)key] = true;
}

void handleKeyboardUp(unsigned char key, int x, int y){
	buffer[(int)key] = false;
}

void idleFunction()
{
	if (buffer[27] == true)//Encerrar com Esc
		Encerrar();
}








int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Objeto em 3D");
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutKeyboardUpFunc(handleKeyboardUp);
	glutKeyboardFunc(handleKeyboardPressed);
	glutIdleFunc(idleFunction);
	initialize();
	glutMainLoop();
	return 0;

}




