#include "Filetobuf.h"
#include "Line.h"

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

Mesh tetrah;
Mesh Cube;
Line Line_x(0);
Line Line_y(1);

void main(int argc, char** argv)
{
	width = height = 800;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 14");					// ������ ����(������ �̸�)

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

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
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