#include "Filetobuf.h"
#include "Wall.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void KeyboardUp(unsigned char, int, int);
void TimerF(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
bool open;
bool move_w, move_a, move_s, move_d;
bool y_rot, Y_rot, z_move, Z_move;

GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü


Camera camera;
Projection proj;

Robot robot;

Wall wall[5], door[2];

void main(int argc, char** argv)
{
	width = height = 800;
	open = false;
	move_w = move_a = move_s = move_d =  false;
	y_rot = Y_rot = z_move = Z_move = false;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("�ǽ� 22");					// ������ ����(������ �̸�)

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

	std::default_random_engine dre;
	std::uniform_real_distribution<float> urd(0.0, 0.9);
	for (Wall& w : wall) {
		w.Initialize(&shaderProgramID, urd(dre), urd(dre), urd(dre), 0);
	}
	wall[0].Rotate(90, glm::vec3(1, 0, 0));
	wall[1].Rotate(90, glm::vec3(0, 1, 0)); wall[1].Move(glm::vec3(-10, 10, 0));
	wall[2].Move(glm::vec3(0, 10, -10));
	wall[3].Rotate(90, glm::vec3(0, 1, 0)); wall[3].Move(glm::vec3(10, 10, 0));
	wall[4].Rotate(90, glm::vec3(1, 0, 0)); wall[4].Move(glm::vec3(0, 20, 0));

	door[0].Initialize(&shaderProgramID, urd(dre), urd(dre), urd(dre), 1);
	door[1].Initialize(&shaderProgramID, urd(dre), urd(dre), urd(dre), 2);
	door[0].Move(glm::vec3(-5, 10, 10));
	door[1].Move(glm::vec3(5, 10, 10));

	robot.Initialize(&shaderProgramID);

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutTimerFunc(50, TimerF, 0);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glUseProgram(shaderProgramID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	for (Wall w : wall)
		w.Draw();
	for (Wall w : door)
		w.Draw();

	robot.Draw();

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
	case 'o':
	case 'O':
		if (open)
			open = false;
		else
			open = true;
		break;
	case 'w':
		move_w = true;
		break;
	case 'a':
		move_a = true;
		break;
	case 's':
		move_s = true;
		break;
	case 'd':
		move_d = true;
		break;
	case 'z':
		z_move = true;
		break;
	case 'Z':
		Z_move = true;
		break;
	case 'y':
		y_rot = true;
		break;
	case 'Y':
		Y_rot = true;
		break;
	case 'x':
		camera.Move(4);
		break;
	case 'X':
		camera.Move(6);
		break;
	case '+':
		robot.speed_control('+');
		break;
	case '-':
		robot.speed_control('-');
		break;
	}
	glutPostRedisplay();
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		move_w = false;
		break;
	case 'a':
		move_a = false;
		break;
	case 's':
		move_s = false;
		break;
	case 'd':
		move_d = false;
		break;
	case 'z':
		z_move = false;
		break;
	case 'Z':
		Z_move = false;
		break;
	case 'y':
		y_rot = false;
		break;
	case 'Y':
		Y_rot = false;
		break;
	}
	glutPostRedisplay();
}

void TimerF(int value)
{
	if (open) {
		door[0].Open(4);
		door[1].Open(4);
	}
	else {
		door[0].Open(6);
		door[1].Open(6);
	}
	if (move_w) {
		robot.Move(8);
	}
	if (move_a)
		robot.Rotate(4);
	if (move_s)
		robot.Move(2);
	if (move_d)
		robot.Rotate(6);
	if (move_w || move_a || move_s || move_d)
		robot.arm_legAni();
	else
		robot.stand_ani();
	if (z_move)
		camera.dis_plus(8);
	if (Z_move)
		camera.dis_plus(2);
	if (y_rot)
		camera.rotate_pos(4);
	if (Y_rot)
		camera.rotate_pos(6);
	glutPostRedisplay();
	glutTimerFunc(50, TimerF, 0);
}