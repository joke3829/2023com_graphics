#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include "Filetobuf.h"
#include "Mouse.h"
#include "Line.h"

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수
void Mouse(int, int, int, int);
void Motion(int, int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
int grab_point;
bool p_grab; 
bool rect_grab;
float old_x, old_y, new_x, new_y;
GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

LINE_OBJ line_1(0), line_2(1);
LINE_OBJ Rect;

void main(int argc, char** argv)
{
	p_grab = false;
	rect_grab = false;
	grab_point = -1;
	width = 800;
	height = 600;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 13");					// 윈도우 생성(윈도우 이름)

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	line_1.Gen();
	line_2.Gen();
	Rect.Gen();
	shaderProgramID = make_shaderProgram();			// 셰이더 프로그램 만들기

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	line_1.InitBuffer();
	line_1.Draw_line();

	line_2.InitBuffer();
	line_2.Draw_line();

	Rect.InitBuffer();
	Rect.Draw();

	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void make_vertexShaders()
{
	GLchar* vertexSource;
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
}

void make_fragmentShaders()
{
	GLchar* fragmentSource;
	fragmentSource = filetobuf("fragment.glsl");
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

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		grab_point = Rect.Grab_point(x_conversion(x, width), y_conversion(y, height));
		if (grab_point >= 0 && grab_point <= 3) {
			p_grab = true;
		}
		else if (Rect.Mouse_Check(x_conversion(x, width), y_conversion(y, height))) {
			rect_grab = true;
			old_x = x_conversion(x, width);
			old_y = y_conversion(y, height);
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		p_grab = rect_grab = false;
	}
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	if (p_grab) {
		Rect.move_point(grab_point, x_conversion(x, width), y_conversion(y, height));
	}
	else if (rect_grab) {
		new_x = x_conversion(x, width);
		new_y = y_conversion(y, height);
		Rect.move_rect(new_x - old_x, new_y - old_y);
		old_x = new_x; old_y = new_y;
	}
	glutPostRedisplay();
}