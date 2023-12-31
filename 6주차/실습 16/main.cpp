#include "Filetobuf.h"
#include "Line.h"

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수

void Keyboard(unsigned char, int, int);
void TimerF_1(int);
void TimerF_2(int);
void TimerF_3(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
bool t1, t2, t3, xplus, yplus, rplus;
bool left_move, right_move, change_mesh;
GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

Line Line_x(0);
Line Line_y(1);
Line Line_z(2);

Mesh cone;
Mesh cube;
Mesh pyramid;
Mesh sphere;

void main(int argc, char** argv)
{
	left_move = right_move = true;
	t1 = t2 = t3 = xplus = yplus = rplus = change_mesh = false;
	width = height = 800;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 14");					// 윈도우 생성(윈도우 이름)

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
	Line_z.Initialize(&shaderProgramID);

	cone.Initialize(&shaderProgramID, "cone.obj");
	cube.Initialize(&shaderProgramID, "cube.obj");
	pyramid.Initialize(&shaderProgramID, "pyramid.obj");
	sphere.Initialize(&shaderProgramID, "sphere.obj");

	cone.Scale(0.02);
	cube.Scale(0.02);
	pyramid.Scale(0.02);
	sphere.Scale(0.02);

	cube.Rotate_world(-50, 0, 1, 0);
	cone.Rotate_world(-50, 0, 1, 0);
	pyramid.Rotate_world(-50, 0, 1, 0);
	sphere.Rotate_world(-50, 0, 1, 0);

	cube.Move(-0.5, 0, 0);
	cone.Move(0.5, 0, 0);
	pyramid.Move(-0.5, 0, 0);
	sphere.Move(0.5, 0, 0);


	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glUseProgram(shaderProgramID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	Line_x.Draw();
	Line_y.Draw();
	Line_z.Draw();

	if (change_mesh) {
		pyramid.Draw();
		sphere.Draw();
	}
	else {
		cone.Draw();
		cube.Draw();
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
	case 'x':
		xplus = true; 
		if (not t1) {
			t1 = true;
			glutTimerFunc(100, TimerF_1, 0);
		}
		break;
	case 'X':
		xplus = false;
		if (not t1) {
			t1 = true;
			glutTimerFunc(100, TimerF_1, 0);
		}
		break;
	case 'y':
		yplus = true;
		if (not t2) {
			t2 = true;
			glutTimerFunc(100, TimerF_2, 1);
		}
		break;
	case 'Y':
		yplus = false;
		if (not t2) {
			t2 = true;
			glutTimerFunc(100, TimerF_2, 1);
		}
		break;
	case '1':
		left_move = true;
		right_move = false;
		break;
	case '2':
		left_move = false;
		right_move = true;
		break;
	case '3':
		left_move = true;
		right_move = true;
		break;
	case 'r':
		rplus = true;
		if (not t3) {
			t3 = true;
			glutTimerFunc(100, TimerF_3, 2);
		}
		break;
	case 'R':
		rplus = false;
		if (not t3) {
			t3 = true;
			glutTimerFunc(100, TimerF_3, 2);
		}
		break;
	case 'c':
		if (change_mesh)
			change_mesh = false;
		else
			change_mesh = true;
		break;
	case 's':
		t1 = t2 = t3 = false;
		cube.T_format();
		cone.T_format();
		pyramid.T_format();
		sphere.T_format();
		break;
	}
	glutPostRedisplay();
}

void TimerF_1(int value) {
	if (xplus) {
		if (left_move) {
			cube.Rotate(10, 0, 1, 0);
			pyramid.Rotate(10, 0, 1, 0);
		}
		if (right_move) {
			cone.Rotate(10, 0, 1, 0);
			sphere.Rotate(10, 0, 1, 0);
		}
	}
	else {
		if (left_move) {
			cube.Rotate(-10, 0, 1, 0);
			pyramid.Rotate(-10, 0, 1, 0);
		}
		if (right_move) {
			cone.Rotate(-10, 0, 1, 0);
			sphere.Rotate(-10, 0, 1, 0);
		}
	}
	glutPostRedisplay();
	if (t1)
		glutTimerFunc(100, TimerF_1, 0);
}

void TimerF_2(int value)
{
	if (yplus) {
		if (left_move) {
			cube.Rotate(10, 1, 0, 0);
			pyramid.Rotate(10, 1, 0, 0);
		}
		if (right_move) {
			cone.Rotate(10, 1, 0, 0);
			sphere.Rotate(10, 1, 0, 0);
		}
	}
	else {
		if (left_move) {
			cube.Rotate(-10, 1, 0, 0);
			pyramid.Rotate(-10, 1, 0, 0);
		}
		if (right_move) {
			cone.Rotate(-10, 1, 0, 0);
			sphere.Rotate(-10, 1, 0, 0);
		}
	}
	glutPostRedisplay();
	if (t2)
		glutTimerFunc(100, TimerF_2, 1);
}

void TimerF_3(int value)
{
	if (rplus) {
		cube.Rotate_world(10, 0, 1, 0);
		cone.Rotate_world(10, 0, 1, 0);
		pyramid.Rotate_world(10, 0, 1, 0);
		sphere.Rotate_world(10, 0, 1, 0);
	}
	else {
		cube.Rotate_world(-10, 0, 1, 0);
		cone.Rotate_world(-10, 0, 1, 0);
		pyramid.Rotate_world(-10, 0, 1, 0);
		sphere.Rotate_world(-10, 0, 1, 0);
	}
	glutPostRedisplay();
	if (t3)
		glutTimerFunc(100, TimerF_3, 2);
}