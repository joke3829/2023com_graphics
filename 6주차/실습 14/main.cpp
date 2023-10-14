#include "Filetobuf.h"
#include "Line.h"

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

Mesh tetrah;
Mesh Cube;
Line Line_x(0);
Line Line_y(1);

void main(int argc, char** argv)
{
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
	tetrah.Initialize(&shaderProgramID, "tetrah.obj", 0);
	Cube.Initialize(&shaderProgramID, "cube.obj", 1);
	tetrah.Scale(0.12);
	tetrah.Rotate(10.0, 1.0, 0.0, 0.0);
	tetrah.Rotate(10.0, 0.0, 1.0, 0.0);
	tetrah.Move(0.5, 0.0, 0.0);

	Cube.Scale(0.05);
	Cube.Rotate(10.0, 1.0, 0.0, 0.0);
	Cube.Rotate(10.0, 0.0, 1.0, 0.0);
	Cube.Move(-0.5, 0.0, 0.0);

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
	//glEnable(GL_CULL_FACE);

	Line_x.Draw();
	Line_y.Draw();
	tetrah.Draw();
	Cube.Draw();
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
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution uid_cube(0, 5);
	std::uniform_int_distribution uid_tetrah(0, 3);

	int num1, num2;

	switch (key) {
	case '1':
		Cube.change_visible(0);
		break;
	case '2':
		Cube.change_visible(1);
		break;
	case '3':
		Cube.change_visible(2);
		break;
	case '4':
		Cube.change_visible(3);
		break;
	case '5':
		Cube.change_visible(4);
		break;
	case '6':
		Cube.change_visible(5);
		break;
	case '7':
		tetrah.change_visible(0);
		break;
	case '8':
		tetrah.change_visible(1);
		break;
	case '9':
		tetrah.change_visible(2);
		break;
	case '0':
		tetrah.change_visible(3);
		break;
	case 'c':
		num1 = uid_cube(dre);
		num2 = uid_cube(dre);
		while (num1 == num2) {
			num2 = uid_cube(dre);
		}
		Cube.change_visible(false);
		Cube.change_visible(num1);
		Cube.change_visible(num2);
		break;
	case 't':
		num1 = uid_tetrah(dre);
		num2 = uid_tetrah(dre);
		while (num1 == num2) {
			num2 = uid_tetrah(dre);
		}
		tetrah.change_visible(false);
		tetrah.change_visible(num1);
		tetrah.change_visible(num2);
		break;
	case 'q':
		Cube.change_visible(false);
		tetrah.change_visible(false);
		break;
	}
	glutPostRedisplay();
}