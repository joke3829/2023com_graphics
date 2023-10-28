#include "Filetobuf.h"
#include "Wall.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void KeyboardUp(unsigned char, int, int);
void Special(int, int, int);
void SpecialUp(int, int, int);
void TimerF(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
bool open;
bool move_w[2], move_a[2], move_s[2], move_d[2];
bool y_rot, Y_rot, z_move, Z_move;

bool falling[2];
int falling_count[2];

GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü


Camera camera;
Projection proj;

Robot robot;
Robot enemy;

Wall wall[5], door[2];

Mesh obstacle[3];

void main(int argc, char** argv)
{
	width = height = 800;
	falling[0] = true;
	falling[1] = true;
	open = false;
	move_w[0] = move_a[0] = move_s[0] = move_d[0] = false;
	move_w[1] = move_a[1] = move_s[1] = move_d[1] = false;
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

	std::cout << "==========================================" << std::endl;
	std::cout << "o: ���� ����/ �ݱ�" << std::endl;
	std::cout << "w, a, s, d: �÷��̾�1 �̵�" << std::endl;
	std::cout << "g: �÷��̾�1 ����" << std::endl;
	std::cout << "ȭ��ǥ Ű: �÷��̾�2 �̵�" << std::endl;
	std::cout << ".: �÷��̾�1 ����" << std::endl;
	std::cout << "i: �ʱ�ȭ" << std::endl;
	std::cout << "��븦 ��Ƽ� �����߷� ������!" << std::endl;
	std::cout << "==========================================" << std::endl;

	camera.Initialize(&shaderProgramID);
	proj.Initialize(&shaderProgramID);

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd(0.0, 0.9);
	std::uniform_int_distribution<int> uid(-8, 8);
	for (Wall& w : wall) {
		w.Initialize(&shaderProgramID, urd(dre), urd(dre), urd(dre), 0);
	}
	wall[0].Rotate(90, glm::vec3(1, 0, 0));
	wall[1].Rotate(-90, glm::vec3(0, 1, 0)); wall[1].Move(glm::vec3(-10, 10, 0));
	wall[2].Rotate(180, glm::vec3(0, 1, 0)); wall[2].Move(glm::vec3(0, 10, -10));
	wall[3].Rotate(90, glm::vec3(0, 1, 0)); wall[3].Move(glm::vec3(10, 10, 0));
	wall[4].Rotate(-90, glm::vec3(1, 0, 0)); wall[4].Move(glm::vec3(0, 20, 0));

	door[0].Initialize(&shaderProgramID, urd(dre), urd(dre), urd(dre), 1);
	door[1].Initialize(&shaderProgramID, urd(dre), urd(dre), urd(dre), 2);
	door[0].Move(glm::vec3(-5, 10, 10));
	door[1].Move(glm::vec3(5, 10, 10));

	robot.Initialize(&shaderProgramID);
	enemy.Initialize(&shaderProgramID);
	enemy.Trans_init(glm::vec3(5, 0, 0));

	for (Mesh& o : obstacle) {
		o.Initialize(&shaderProgramID, "cube.obj");
		o.init_position(0, 5, 0);
		o.init_scale(0.28);
		o.Move(glm::vec3(uid(dre), 0, uid(dre)));
	}

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(Special);
	glutSpecialUpFunc(SpecialUp);
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
	enemy.Draw();

	for (Mesh o : obstacle)
		o.Draw();

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
		wall[1].crash_check(robot);
		break;
	case 'w':
		move_w[0] = true;
		break;
	case 'a':
		move_a[0] = true;
		break;
	case 's':
		move_s[0] = true;
		break;
	case 'd':
		move_d[0] = true;
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
		enemy.speed_control('+');
		break;
	case '-':
		robot.speed_control('-');
		enemy.speed_control('-');
		break;
	case 'g':
		if (falling[0]) {
			falling[0] = false;
			falling_count[0] = 0;
		}
		break;
	case '.':
		if (falling[1]) {
			falling[1] = false;
			falling_count[1] = 0;
		}
		break;
	case 'i':
		robot.Trans_init(glm::vec3(0, 0, 0));
		enemy.Trans_init(glm::vec3(5, 0, 0));
		break;
	}
	glutPostRedisplay();
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		move_w[0] = false;
		break;
	case 'a':
		move_a[0] = false;
		break;
	case 's':
		move_s[0] = false;
		break;
	case 'd':
		move_d[0] = false;
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
	// �÷��̾� 1 ����
	if (robot.state_check()) {
		if (move_w[0]) {
			robot.Move(8);
			for (int i = 1; i < 4; ++i) {
				if (wall[i].crash_check(robot)) {
					robot.Move(2);
					robot.angle_change(wall[i].reflect_vector(robot));
					break;
				}
			}
			for (int i = 0; i < 3; ++i) {
				if (robot.check_crash(obstacle[i])) {
					robot.Move(2);
					break;
				}
			}
		}
		if (move_a[0])
			robot.Rotate(4);
		if (move_s[0]) {
			robot.Move(2);
			for (int i = 1; i < 4; ++i) {
				if (wall[i].crash_check(robot)) {
					robot.Move(8);
					break;
				}
			}
			for (int i = 0; i < 3; ++i) {
				if (robot.check_crash(obstacle[i])) {
					robot.Move(8);
					break;
				}
			}
		}
		if (move_d[0])
			robot.Rotate(6);
		if (move_w[0] || move_a[0] || move_s[0] || move_d[0])
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

		if (falling[0]) {
			robot.fallen(2);
			if (wall[0].crash_check(robot))
				robot.fallen(5);
			for (int i = 0; i < 3; ++i) {
				if (robot.check_crash(obstacle[i]))
					robot.fallen(5);
			}
		}
		else {
			if (falling_count[0] >= 7) {
				robot.fallen(2);
				if (wall[0].crash_check(robot)) {
					robot.fallen(5);
					falling[0] = true;
				}
				for (int i = 0; i < 3; ++i) {
					if (robot.check_crash(obstacle[i])) {
						robot.fallen(5);
						falling[0] = true;
					}
				}
				if (robot.check_crash(enemy)) {
					enemy.death();
				}
			}
			else {
				robot.fallen(8);
				falling_count[0] += 1;
			}
		}
	}
	// 2p �÷��̾�
	if (enemy.state_check()) {
		if (move_w[1]) {
			enemy.Move(8);
			for (int i = 1; i < 4; ++i) {
				if (wall[i].crash_check(enemy)) {
					enemy.Move(2);
					enemy.angle_change(wall[i].reflect_vector(enemy));
					break;
				}
			}
			for (int i = 0; i < 3; ++i) {
				if (enemy.check_crash(obstacle[i])) {
					enemy.Move(2);
					break;
				}
			}
		}
		if (move_a[1])
			enemy.Rotate(4);
		if (move_s[1]) {
			enemy.Move(2);
			for (int i = 1; i < 4; ++i) {
				if (wall[i].crash_check(enemy)) {
					enemy.Move(8);
					break;
				}
			}
			for (int i = 0; i < 3; ++i) {
				if (enemy.check_crash(obstacle[i])) {
					enemy.Move(8);
					break;
				}
			}
		}
		if (move_d[1])
			enemy.Rotate(6);
		if (move_w[1] || move_a[1] || move_s[1] || move_d[1])
			enemy.arm_legAni();
		else
			enemy.stand_ani();

		if (falling[1]) {
			enemy.fallen(2);
			if (wall[0].crash_check(enemy))
				enemy.fallen(5);
			for (int i = 0; i < 3; ++i) {
				if (enemy.check_crash(obstacle[i]))
					enemy.fallen(5);
			}
		}
		else {
			if (falling_count[1] >= 7) {
				enemy.fallen(2);
				if (wall[0].crash_check(enemy)) {
					enemy.fallen(5);
					falling[1] = true;
				}
				for (int i = 0; i < 3; ++i) {
					if (enemy.check_crash(obstacle[i])) {
						enemy.fallen(5);
						falling[1] = true;
					}
				}
				if (enemy.check_crash(robot)) {
					robot.death();
				}
			}
			else {
				enemy.fallen(8);
				falling_count[1] += 1;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(50, TimerF, 0);
}


void Special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		move_a[1] = true;
		break;
	case GLUT_KEY_RIGHT:
		move_d[1] = true;
		break;
	case GLUT_KEY_UP:
		move_w[1] = true;
		break;
	case GLUT_KEY_DOWN:
		move_s[1] = true;
		break;
	}
	glutPostRedisplay();
}

void SpecialUp(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		move_a[1] = false;
		break;
	case GLUT_KEY_RIGHT:
		move_d[1] = false;
		break;
	case GLUT_KEY_UP:
		move_w[1] = false;
		break;
	case GLUT_KEY_DOWN:
		move_s[1] = false;
		break;
	}
	glutPostRedisplay();
}