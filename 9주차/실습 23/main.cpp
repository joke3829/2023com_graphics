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
void TimerF(int);
void Motion(int, int);

void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
int start_x, start_y;

GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Camera camera;
Projection proj;

Wall wall[4];
Wall back;
Mesh ball[5];
Mesh box[3];

int num_wall;

float wor_rot;

glm::mat4 world_rotate(1.0f);

void main(int argc, char** argv)
{
	wor_rot = 0;
	num_wall = 4;
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

	wall[3].Rotate(90, glm::vec3(1, 0, 0)); wall[3].Move(glm::vec3(0, -10, 0));
	wall[0].Rotate(-90, glm::vec3(0, 1, 0)); wall[0].Move(glm::vec3(-10, 0, 0));
	wall[1].Rotate(-90, glm::vec3(1, 0, 0)); wall[1].Move(glm::vec3(0, 10, 0));
	wall[2].Rotate(90, glm::vec3(0, 1, 0)); wall[2].Move(glm::vec3(10, 0, 0));

	back.Initialize(&shaderProgramID, 0.9, 0.9, 0.9, 0);
	back.Move(glm::vec3(0, 0, -10));
	for (Mesh& b : ball) {
		b.Initialize(&shaderProgramID, "Hsphere.obj");
		b.setScale(0.2);
		b.setCur_loc();
	}

	for (Mesh& b : box) {
		b.Initialize(&shaderProgramID, "cube.obj");
	}
	box[0].setScale(0.2); box[1].setScale(0.25); box[2].setScale(0.3);
	box[0].setCur_loc(glm::vec3(0, 0, 2)); box[2].setCur_loc(glm::vec3(0, 0, -3));

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, TimerF, 1);
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glUseProgram(shaderProgramID);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	world_rotate = glm::mat4(1.0f);
	world_rotate = glm::rotate(world_rotate, glm::radians(wor_rot), glm::vec3(0, 0, 1));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "world_rotate"), 1, GL_FALSE, glm::value_ptr(world_rotate));
	for (int i = 0; i < num_wall; ++i)
		wall[i].Draw();

	back.Draw();

	for (Mesh& b : ball)
		b.Draw();

	for (Mesh& b : box)
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
	case 'y':
		camera.y_move(4);
		break;
	case 'Y':
		camera.y_move(6);
		break;
	case 'o':
	case 'O':
		if (4 == num_wall)
			num_wall = 3;
		else
			num_wall = 4;
		break;
	case 'b':
	case 'B':
		for (int i = 0; i < 5; ++i)
			ball[i].setCur_loc();
		break;
	}
	glutPostRedisplay();
}

void TimerF(int value)
{
	for (Mesh& b : ball)
		b.anime();

	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < num_wall; ++j) {
			if (wall[j].crash_check(ball[i], 0)) {
				if (0 == j)
					ball[i].setRight(true);
				else if (1 == j)
					ball[i].setUp(false);
				else if (2 == j)
					ball[i].setRight(false);
				else if (3 == j)
					ball[i].setUp(true);
			}
		}
	}

	for (int i = 0; i < 3; ++i) {
		box[i].falling(2);
		box[i].b_move(wor_rot);
		if (num_wall == 4 && wall[3].crash_check(box[i], 1)) {
			box[i].falling(8);
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50, TimerF, 1);
}

void Motion(int x, int y)
{
	if (start_x > x) {
		if(wor_rot < 60)
			wor_rot += 0.1;
	}
	else if (start_x < x) {
		if (wor_rot > -60)
			wor_rot -= 0.1;
	}
	start_x = x;
	start_y = y;
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		start_x = x; start_y = y;
	}
	glutPostRedisplay();
}