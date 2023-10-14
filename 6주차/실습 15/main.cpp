#include "Filetobuf.h"
#include "Line.h"

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수

void Keyboard(unsigned char, int, int);
void SpecialKeyboard(int, int, int);
void TimerF_1(int);
void TimerF_2(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height, show_shape;
bool culling, rotate_x, rotate_y, xplus, yplus;
GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

Line Line_x(0);
Line Line_y(1);

Mesh cube;
Mesh pyramid;

void main(int argc, char** argv)
{
	rotate_x = rotate_y = false;
	culling = true;
	show_shape = 0;
	width = height = 800;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 15");					// 윈도우 생성(윈도우 이름)

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	shaderProgramID = make_shaderProgram();			// 셰이더 프로그램 만들기
	Line_x.Initialize(&shaderProgramID);
	Line_y.Initialize(&shaderProgramID);

	cube.Initialize(&shaderProgramID, "cube.obj");
	pyramid.Initialize(&shaderProgramID, "pyramid.obj");

	cube.Scale(0.07);
	pyramid.Scale(0.07);
	
	cube.Rotate(30, 1, 0, 0); cube.Rotate(-30, 0, 1, 0);
	pyramid.Rotate(30, 1, 0, 0); pyramid.Rotate(-30, 0, 1, 0);

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glUseProgram(shaderProgramID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (culling) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
	}

	Line_x.Draw();
	Line_y.Draw();

	switch (show_shape) {
	case 0:
		cube.Draw();
		break;
	case 1:
		pyramid.Draw();
		break;
	}
	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void make_vertexShaders()
{
	GLchar* vertexSource;
	vertexSource = filetobuf("VertexShader.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	fragmentSource = filetobuf("FragmentShader.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
}

GLuint make_shaderProgram()
{
	make_vertexShaders();							// vertexShader 만들기
	make_fragmentShaders();							// 프래그먼트 셰이더 만들기
	GLuint shaderID = glCreateProgram();

	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);

	glLinkProgram(shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderID);
	return shaderID;
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c':
		show_shape = 0;
		break;
	case 'p':
		show_shape = 1;
		break;
	case 'h':
		if (culling)
			culling = false;
		else
			culling = true;
		break;
	case 'w':
		cube.TransView(false);
		pyramid.TransView(false);
		break;
	case 'W':
		cube.TransView(true);
		pyramid.TransView(true);
		break;
	case 'x':
		xplus = true;
		if (not rotate_x) {
			rotate_x = true;
			glutTimerFunc(100, TimerF_1, 0);
		}
		break;
	case 'X':
		xplus = false;
		if (not rotate_x) {
			rotate_x = true;
			glutTimerFunc(100, TimerF_1, 0);
		}
		break;
	case 'y':
		yplus = true;
		if (not rotate_y) {
			rotate_y = true;
			glutTimerFunc(100, TimerF_2, 1);
		}
		break;
	case 'Y':
		yplus = false;
		if (not rotate_y) {
			rotate_y = true;
			glutTimerFunc(100, TimerF_2, 1);
		}
		break;
	case 's':
		rotate_x = rotate_y = false;
		cube.trans_Initialize();
		pyramid.trans_Initialize();
		cube.Rotate(30, 1, 0, 0); cube.Rotate(-30, 0, 1, 0);
		pyramid.Rotate(30, 1, 0, 0); pyramid.Rotate(-30, 0, 1, 0);
		break;
	}
	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
		cube.Move(-0.05, 0, 0);
		pyramid.Move(-0.05, 0, 0);
	}
	else if (key == GLUT_KEY_UP) {
		cube.Move(0, 0.05, 0);
		pyramid.Move(0, 0.05, 0);
	}
	else if (key == GLUT_KEY_RIGHT) {
		cube.Move(0.05, 0, 0);
		pyramid.Move(0.05, 0, 0);
	}
	else if (key == GLUT_KEY_DOWN) {
		cube.Move(0, -0.05, 0);
		pyramid.Move(0, -0.05, 0);
	}
	glutPostRedisplay();
}

void TimerF_1(int value)
{
	if (xplus) {
		cube.Rotate(10, 1, 0, 0);
		pyramid.Rotate(10, 1, 0, 0);
	}
	else {
		cube.Rotate(-10, 1, 0, 0);
		pyramid.Rotate(-10, 1, 0, 0);
	}
	glutPostRedisplay();
	if (rotate_x)
		glutTimerFunc(100, TimerF_1, 0);
}

void TimerF_2(int value)
{
	if (yplus) {
		cube.Rotate(10, 0, 1, 0);
		pyramid.Rotate(10, 0, 1, 0);
	}
	else {
		cube.Rotate(-10, 0, 1, 0);
		pyramid.Rotate(-10, 0, 1, 0);
	}
	glutPostRedisplay();
	if (rotate_y)
		glutTimerFunc(100, TimerF_2, 1);
}