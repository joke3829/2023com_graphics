#include "Filetobuf.h"
#include "Floor.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void KeyboardUp(unsigned char, int, int);
void TimerF(int);

bool control_mode;
bool c_w, c_a, c_d, c_s;
bool camera_w, camera_a, camera_s, camera_d, camera_i, camera_j, camera_k, camera_l;
bool m_rot, M_rot, b_move, B_move, f_rot, F_rot;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;

GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Line line[3] = { {0}, {1}, {2} };
Floor bottom_floor;

Camera camera;
Projection proj;

Crane crane;

void main(int argc, char** argv)
{
	width = height = 800;
	control_mode = false;
	c_w = c_a = c_s = c_d = false;
	camera_w =  camera_a = camera_s = camera_d = camera_i = camera_j = camera_k = camera_l = false;
	m_rot = M_rot = b_move = B_move = f_rot = F_rot = false;
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

	bottom_floor.Initialize(&shaderProgramID);

	for (Line& l : line)
		l.Initialize(&shaderProgramID);
	
	crane.Initialize(&shaderProgramID);

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
	glEnable(GL_CULL_FACE);

	bottom_floor.Draw();
	for (Line l : line)
		l.Draw();

	crane.Draw();
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
	if (control_mode) {
		switch (key) {
		case 'c':
			camera.Control_init();
			control_mode = false;
			break;
		case 'w':
		case 'W':
			c_w = true;
			break;
		case 's':
		case 'S':
			c_s = true;
			break;
		case 'a':
		case 'A':
			c_a = true;
			break;
		case 'd':
		case 'D':
			c_d = true;
			break;
		}
	}
	else {
		switch (key) {
		case 'i':
			camera_i = true;
			break;
		case 'j':
			camera_j = true;
			break;
		case 'k':
			camera_k = true;
			break;
		case 'l':
			camera_l = true;
			break;
		case 'w':
			camera_w = true;
			break;
		case 'a':
			camera_a = true;
			break;
		case 's':
			camera_s = true;
			break;
		case 'd':
			camera_d = true;
			break;
		case 'c':
			camera.Control_camera(crane.loc_return(), crane.angle_return());
			control_mode = true;
			break;
		}
	}
	if (key == 'q' || key =='Q')
		glutLeaveMainLoop();
	if (key == 'm')
		m_rot = true;
	if (key == 'M')
		M_rot = true;
	if (key == 'b')
		b_move = true;
	if (key == 'B')
		B_move = true;
	if (key == 'f')
		f_rot = true;
	if (key == 'F')
		F_rot = true;
	glutPostRedisplay();
}

void KeyboardUp(unsigned char key, int x, int y)
{
	if (control_mode) {
		switch (key) {
		case 'w':
		case 'W':
			c_w = false;
			break;
		case 's':
		case 'S':
			c_s = false;
			break;
		case 'a':
		case 'A':
			c_a = false;
			break;
		case 'd':
		case 'D':
			c_d = false;
			break;
		}
	}
	else {
		switch (key) {
		case 'i':
			camera_i = false;
			break;
		case 'j':
			camera_j = false;
			break;
		case 'k':
			camera_k = false;
			break;
		case 'l':
			camera_l = false;
			break;
		case 'w':
			camera_w = false;
			break;
		case 'a':
			camera_a = false;
			break;
		case 's':
			camera_s = false;
			break;
		case 'd':
			camera_d = false;
			break;
		}
	}
	if (key == 'm')
		m_rot = false;
	if (key == 'M')
		M_rot = false;
	if (key == 'b')
		b_move = false;
	if (key == 'B')
		B_move = false;
	if (key == 'f')
		f_rot = false;
	if (key == 'F')
		F_rot = false;
	glutPostRedisplay();
}

void TimerF(int value)
{

	if (c_a) {
		crane.rotate(4);
		camera.Control_camera(crane.loc_return(), crane.angle_return());
	}
	if (c_d) {
		crane.rotate(6);
		camera.Control_camera(crane.loc_return(), crane.angle_return());
	}
	if (c_w) {
		crane.Move(8);
		camera.Control_camera(crane.loc_return(), crane.angle_return());
	}
	if (c_s) {
		crane.Move(8);
		camera.Control_camera(crane.loc_return(), crane.angle_return());
	}
	if (camera_w)
		camera.Move(8);
	if (camera_a)
		camera.Move(4);
	if (camera_s)
		camera.Move(2);
	if (camera_d)
		camera.Move(6);
	if (camera_i)
		camera.Direcion_Move(8);
	if (camera_j)
		camera.Direcion_Move(4);
	if (camera_k)
		camera.Direcion_Move(2);
	if (camera_l)
		camera.Direcion_Move(6);
	if (m_rot)
		crane.head_rotate(4);
	if (M_rot)
		crane.head_rotate(6);
	if (b_move)
		crane.x_Move(4);
	if (B_move)
		crane.x_Move(6);
	if (f_rot)
		crane.front_ani(4);
	if (F_rot)
		crane.front_ani(6);
	glutPostRedisplay();
	glutTimerFunc(50, TimerF, 0);
}