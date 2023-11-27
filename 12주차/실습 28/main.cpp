#include "Camera.h"
#include "Projection.h"
#include "Filetobuf.h"
#include "LightBox.h"
#include "Mesh.h"
#include "Sierpinski.h"

#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수

void Keyboard(unsigned char, int, int);
void Timer(int);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
int depth;
bool snowing;

GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

Camera camera;
Projection proj;
LightBox light;

Mesh ball[3];
Mesh m_floor;

Mesh snow[100];

Sier ss[4];

void main(int argc, char** argv)
{
	snowing = false;
	width = height = 800;
	depth = 0;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 28");					// 윈도우 생성(윈도우 이름)

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

	std::mt19937 dre;
	std::uniform_int_distribution uid(-20, 20);
	for (Mesh& m : snow) {
		m.Initialize(&shaderProgramID, "Hsphere.obj", 3);
		m.init_scale(0.1);
		m.Move(glm::vec3(uid(dre), 50, uid(dre)));
	}

	for (int i = 0; i < 3; ++i) {
		ball[i].Initialize(&shaderProgramID, "Hsphere.obj", i);
	}
	ball[0].init_scale(0.5);
	ball[0].init_position(0, 0, 15);

	ball[1].init_scale(0.7);
	ball[1].init_position(0, 0, 15);

	ball[2].init_scale(0.3);
	ball[2].init_position(15, 0, 0);

	std::vector<glm::vec3> t_pos;
	t_pos.push_back(glm::vec3(-20, 0, -20));
	t_pos.push_back(glm::vec3(-20, 0, 20));
	t_pos.push_back(glm::vec3(20, 0, 20));
	t_pos.push_back(glm::vec3(-20, 0, -20));
	t_pos.push_back(glm::vec3(20, 0, 20));
	t_pos.push_back(glm::vec3(20, 0, -20));
	m_floor.Initialize(&shaderProgramID, t_pos, 4, 0.3, 0.3, 0.3);

	for (int i = 0; i < 4; ++i) {
		ss[i].Initialize(&shaderProgramID, i);
	}

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(17, Timer, 0);
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

	ss[0].sierpinski(glm::vec3(0, 10, 0), glm::vec3(-10, 0, -10), glm::vec3(-10, 0, 10), depth);
	ss[1].sierpinski(glm::vec3(0, 10, 0), glm::vec3(-10, 0, 10), glm::vec3(10, 0, 10), depth);
	ss[2].sierpinski(glm::vec3(0, 10, 0), glm::vec3(10, 0, 10), glm::vec3(10, 0, -10), depth);
	ss[3].sierpinski(glm::vec3(0, 10, 0), glm::vec3(10, 0, -10), glm::vec3(-10, 0, -10), depth);

	for (Mesh& d : ball)
		d.Draw();

	for (Mesh& d : snow)
		d.Draw();

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
	case '0':
		depth = 0;
		break;
	case '1':
		depth = 1;
		break;
	case '2':
		depth = 2;
		break;
	case '3':
		depth = 3;
		break;
	case '4':
		depth = 4;
		break;
	case '5':
		depth = 5;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'n':
		light.Move(6);
		break;
	case 'f':
		light.Move(4);
		break;
	case 's':
		if (snowing) {
			snowing = false;
			for (Mesh& d : snow)
				d.snowing(8);
		}
		else
			snowing = true;
		break;
	case 'r':
		light.Rotate(6);
		break;
	case '+':
		light.lightPower('+');
		break;
	case '-':
		light.lightPower('-');
		break;
	case 'm':
		light.Lever();
		break;
	case 'c':
		light.change_color();
		break;
	case 'p':
		light.push_pdd();
		break;
	}
	glutPostRedisplay();
}

void Timer(int value)
{
	if(snowing){
		for (Mesh& d : snow)
			d.snowing(2);
	}

	ball[0].x_rot();
	ball[1].y_rot();
	ball[2].z_rot();

	glutPostRedisplay();
	glutTimerFunc(17, Timer, 0);
}