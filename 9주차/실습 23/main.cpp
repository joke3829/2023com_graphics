#include "Filetobuf.h"
#include "Projection.h"
#include "Mesh.h"
#include "Camera.h"
#include "Mouse.h"
#include "Wall.h"
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

Wall wall[4];
Mesh ball[5];
Mesh box[3];

glm::mat4 world_rotate(1.0f);

void main(int argc, char** argv)
{
	width = height = 800;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 23");					// ������ ����(������ �̸�)

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
	//glEnable(GL_CULL_FACE);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "world_rotate"), 1, GL_FALSE, glm::value_ptr(world_rotate));
	for (Wall& w : wall)
		w.Draw();

	for (Mesh& b : ball)
		b.Draw();

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