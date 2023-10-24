#include "Filetobuf.h"
#include "Floor.h"

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수

void Keyboard(unsigned char, int, int);
void TimerF(int);

bool control_mode;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;

GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

Line line[3] = { {0}, {1}, {2} };
Floor bottom_floor;

Camera camera;
Projection proj;

Crane crane;

void main(int argc, char** argv)
{
	width = height = 800;
	control_mode = false;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 18");					// 윈도우 생성(윈도우 이름)

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

	bottom_floor.Initialize(&shaderProgramID);

	for (Line& l : line)
		l.Initialize(&shaderProgramID);
	
	crane.Initialize(&shaderProgramID);

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, TimerF, 0);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glUseProgram(shaderProgramID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	bottom_floor.Draw();
	for (Line l : line)
		l.Draw();

	crane.Draw();
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
	if (control_mode) {
		switch (key) {
		case 'c':
			camera.Control_init();
			control_mode = false;
			break;
		case 'w':
			break;
		case 's':
			break;
		case 'a':
			crane.rotate(4);
			camera.Control_camera(crane.loc_return(), crane.angle_return());
			break;
		case 'd':
			crane.rotate(6);
			camera.Control_camera(crane.loc_return(), crane.angle_return());
			break;
		}
	}
	else {
		switch (key) {
		case 'i':
			camera.Direcion_Move(8);
			break;
		case 'j':
			camera.Direcion_Move(4);
			break;
		case 'k':
			camera.Direcion_Move(2);
			break;
		case 'l':
			camera.Direcion_Move(6);
			break;
		case 'w':
			camera.Move(8);
			break;
		case 'a':
			camera.Move(4);
			break;
		case 's':
			camera.Move(2);
			break;
		case 'd':
			camera.Move(6);
			break;
		case 'c':
			camera.Control_camera(crane.loc_return(), crane.angle_return());
			control_mode = true;
			break;
		}
	}
	glutPostRedisplay();
}

void TimerF(int value)
{
	
	glutPostRedisplay();
	glutTimerFunc(50, TimerF, 0);
}