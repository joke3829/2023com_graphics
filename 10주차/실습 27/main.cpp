#include "Filetobuf.h"
#include "Projection.h"
#include "Mesh.h"
#include "Camera.h"
//#include "Light.h"
#include "LightBox.h"
#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;

GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Camera camera;
Projection proj;

Mesh crane[2];
Mesh m_floor;

LightBox light;

glm::vec3 loca(0.0);

void main(int argc, char** argv)
{
	width = height = 800;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 26");					// ������ ����(������ �̸�)

	//GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	shaderProgramID = make_shaderProgram();			// ���̴� ���α׷� �����

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

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
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


	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)						// �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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
	make_vertexShaders();							// vertexShader �����
	make_fragmentShaders();							// �����׸�Ʈ ���̴� �����
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