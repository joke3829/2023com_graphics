#include "Filetobuf.h"
#include "Ortho.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void Special(int, int, int);
void TimerF(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
bool solid, per;

GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Camera camera;
Projection proj;
Ortho ortho;

SolarSystem solarSystem;

void main(int argc, char** argv)
{
	solid = per = true;
	width = height = 800;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 18");					// ������ ����(������ �̸�)

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
	ortho.Initialize(&shaderProgramID);

	solarSystem.Initialize(&shaderProgramID);

	glutTimerFunc(50, TimerF, 0);
	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glUseProgram(shaderProgramID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	solarSystem.Draw();

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
	case 'p':
		ortho.OuttoVS();
		break;
	case 'P':
		proj.OuttoVS();
		break;
	case 'm':
		solid = true;
		solarSystem.change_solid(solid);
		break;
	case 'M':
		solid = false;
		solarSystem.change_solid(solid);
		break;
	case ' ':
		camera.Vertical_Move(8);
		break;
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
	case 'y':
		camera.rota_ani(0);
		break;
	case 'Y':
		camera.rota_ani(1);
		break;
	case 'z':
		solarSystem.rotate_z(0);
		break;
	case 'Z':
		solarSystem.rotate_z(1);
		break;

	}
	glutPostRedisplay();
}

void Special(int key, int x, int y)
{
	if (key == GLUT_KEY_SHIFT_L)
		camera.Vertical_Move(2);
	glutPostRedisplay();
}

void TimerF(int value)
{
	solarSystem.anime();
	glutPostRedisplay();
	glutTimerFunc(50, TimerF, 0);
}