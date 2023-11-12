#include "Filetobuf.h"
#include "Projection.h"
#include "Mesh.h"
#include "Camera.h"
#include "Mouse.h"
#include "Wall.h"
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

Wall wall[4];
Mesh ball[5];
Mesh box[3];

glm::mat4 world_rotate(1.0f);

void main(int argc, char** argv)
{
	width = height = 800;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 23");					// 윈도우 생성(윈도우 이름)

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

	for (int i = 0; i < 4; ++i)
		wall[i].Initialize(&shaderProgramID, 0.2 * (i + 1), 0.2 * (i + 1), 0.2 * (i + 1), 0);

	wall[0].Rotate(-90, glm::vec3(1, 0, 0)); wall[0].Move(glm::vec3(0, -10, 0));
	wall[1].Rotate(90, glm::vec3(0, 1, 0)); wall[1].Move(glm::vec3(-10, 0, 0));
	wall[2].Rotate(90, glm::vec3(1, 0, 0)); wall[2].Move(glm::vec3(0, 10, 0));
	wall[3].Rotate(-90, glm::vec3(0, 1, 0)); wall[3].Move(glm::vec3(10, 0, 0));

	for (Mesh& b : ball) {
		b.Initialize(&shaderProgramID, "Hsphere.obj");
		b.setScale(0.2);
	}

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
	//glEnable(GL_CULL_FACE);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "world_rotate"), 1, GL_FALSE, glm::value_ptr(world_rotate));
	for (Wall& w : wall)
		w.Draw();

	for (Mesh& b : ball)
		b.Draw();

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
	float cDis;
	switch (key) {
	case 'z':
		cDis = camera.getDistance();
		cDis += 1;
		camera.setDistance(cDis);
		break;
	case 'Z':
		cDis = camera.getDistance();
		cDis -= 1;
		camera.setDistance(cDis);
		break;
	}
	glutPostRedisplay();
}