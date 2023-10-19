#include "Filetobuf.h"
#include "Cube.h"

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수

void Keyboard(unsigned char, int, int);
void y_rotating(int);
void t_rotate(int);
void f_rotate(int);
void s_move(int);
void b_scale(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
bool culling, push_y, push_t, push_f, push_s, push_b;
GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체

Line Line_x(0);
Line Line_y(1);
Line Line_z(2);

Camera camera;
Projection proj;
Cube cube;

void main(int argc, char** argv)
{
	push_y = push_t = push_f = push_s = push_b = false;
	culling = true;
	width = height = 800;
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
	Line_x.Initialize(&shaderProgramID);
	Line_y.Initialize(&shaderProgramID);
	Line_z.Initialize(&shaderProgramID);

	Line_x.Update_scale(10); Line_y.Update_scale(10); Line_z.Update_scale(10);

	cube.Initialize(&shaderProgramID);

	camera.Initialize(&shaderProgramID);
	proj.Initialize(&shaderProgramID);

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutTimerFunc(100, f_rotate, 2);
	glutTimerFunc(100, s_move, 3);
	glutTimerFunc(100, b_scale, 4);
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glUseProgram(shaderProgramID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (culling)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	Line_x.Draw();
	Line_y.Draw();
	Line_z.Draw();

	cube.Draw();

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
	case 'h':
		if (culling)
			culling = false;
		else
			culling = true;
		break;
	case 'y':
		if (push_y)
			push_y = false;
		else {
			push_y = true;
			glutTimerFunc(100, y_rotating, 0);
		}
		break;
	case 't':
		if (push_t)
			push_t = false;
		else {
			push_t = true;
			glutTimerFunc(100, t_rotate, 1);
		}
		break;
	case 'f':
		if (push_f)
			push_f = false;
		else
			push_f = true;
		break;
	case 's':
		if (push_s)
			push_s = false;
		else
			push_s = true;
		break;
	case 'b':
		if (push_b)
			push_b = false;
		else
			push_b = true;
		break;
	}
	glutPostRedisplay();
}

void y_rotating(int value) 
{
	camera.y_rotate_timer();
	glutPostRedisplay();
	if (push_y)
		glutTimerFunc(100, y_rotating, 0);
}

void t_rotate(int value)
{
	cube.t_rotate();
	glutPostRedisplay();
	if (push_t)
		glutTimerFunc(100, t_rotate, 1);
}

void f_rotate(int value)
{
	cube.f_rotate(push_f);
	glutPostRedisplay();
	glutTimerFunc(100, f_rotate, 2);
}

void s_move(int value)
{
	cube.s_move(push_s);
	glutPostRedisplay();
	glutTimerFunc(100, s_move, 3);
}

void b_scale(int value)
{
	cube.b_scale(push_b);
	glutPostRedisplay();
	glutTimerFunc(100, b_scale, 4);
}