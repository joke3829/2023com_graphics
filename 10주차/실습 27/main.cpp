#include "Filetobuf.h"
#include "Projection.h"
#include "Mesh.h"
#include "Camera.h"
//#include "Light.h"
#include "LightBox.h"
#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수

void Keyboard(unsigned char, int, int);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;

GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

Camera camera;
Projection proj;

Mesh crane[2];
Mesh m_floor;

LightBox light;

glm::vec3 loca(0.0);

void main(int argc, char** argv)
{
	width = height = 800;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 26");					// 윈도우 생성(윈도우 이름)

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

	camera.Initialize(&shaderProgramID);
	proj.Initialize(&shaderProgramID);

	light.Initialize(&shaderProgramID, "cube.obj");

	crane[0].Initialize(&shaderProgramID, "cube.obj", 0);
	crane[0].init_position(0, 5, 0);
	crane[1].Initialize(&shaderProgramID, "cube.obj", 1);
	crane[1].init_scale(0.8);
	crane[1].init_position(0, 12, 0);
	m_floor.Initialize(&shaderProgramID, "cube.obj", 2);
	m_floor.init_scale(10);
	m_floor.init_position(0, -50, 0);

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glUseProgram(shaderProgramID);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	light.Draw();
	m_floor.Draw();
	for (int i = 0; i < 2; ++i)
		crane[i].Draw();


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
	case 'r':
		camera.y_rotate_timer(4);
		break;
	case 'R':
		camera.y_rotate_timer(6);
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'c':
		light.change_color();
		break;
	case 'y':
		light.Rotate(6);
		break;
	case 'w':
		loca.z += 1;
		for (int i = 0; i < 2; ++i)
			crane[i].Move(loca);
		break;
	case 'a':
		loca.x += 1;
		for (int i = 0; i < 2; ++i)
			crane[i].Move(loca);
		break;
	case 's':
		loca.z -= 1;
		for (int i = 0; i < 2; ++i)
			crane[i].Move(loca);
		break;
	case 'd':
		loca.x -= 1;
		for (int i = 0; i < 2; ++i)
			crane[i].Move(loca);
		break;
	case 'o':
		for (int i = 0; i < 2; ++i)
			crane[i].Rotate();
		break;
	case 'z':
		camera.z_move(8);
		break;
	case 'Z':
		camera.z_move(2);
		break;
	case 'x':
		camera.x_move(4);
		break;
	case 'X':
		camera.x_move(6);
		break;
	case 'm':
		light.Lever();
		break;
	}
	glutPostRedisplay();
}