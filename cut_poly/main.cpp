#include "Filetobuf.h"
#include "Mouse.h"
#include "Poly.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void Mouse(int, int, int, int);
void Motion(int, int);
void TimerF(int);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height, produce_count;
int background_color;
float speed;

bool view_poly;
bool activate_cut;
bool view_route;

GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Cutter cutter;
Bucket bucket;

std::vector<Poly> p;

void main(int argc, char** argv)
{
	background_color = 0;
	produce_count = 0;
	width = height = 800;
	activate_cut = false;
	view_poly = true;
	view_route = false;
	speed = 0.01;
	//������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);				// �������� ��ġ ����
	glutInitWindowSize(width, height);					// �������� ũ�� ����
	glutCreateWindow("���� �ڸ���");					// ������ ����(������ �̸�)

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

	cutter.initialize(&shaderProgramID);
	bucket.Initialize(&shaderProgramID);
	

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(50, TimerF, 0);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glUseProgram(shaderProgramID);
	switch (background_color) {
	case 0:
		glClearColor(0.0f, 0.45f, 0.5f, 1.0f);
		break;
	case 1:
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 2:
		glClearColor(0.2f, 0.8f, 1.0f, 1.0f);
		break;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	if (activate_cut)
		cutter.Draw();

	bucket.Draw();
	
	for (int i = 0; i < p.size(); ++i) {
		p[i].setView(view_poly, view_route);
		p[i].Draw();
	}

	glutSwapBuffers();								// ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)						// �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	width = w;
	height = h;
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
	case 'q':
	case 'Q':
		glutLeaveMainLoop();
		break;
	case 'l':
	case 'L':
		if (view_poly)
			view_poly = false;
		else
			view_poly = true;
		break;
	case 'r':
	case 'R':
		if (view_route)
			view_route = false;
		else
			view_route = true;
		break;
	case '+':
		if(speed < 0.5)
			speed += 0.002;
		break;
	case '-':
		if(speed > 0.004)
			speed -= 0.002;
		break;
	case '1':					// ���� �ٲٱ�
		background_color = 0;
		break;
	case '2':
		background_color = 1;
		break;
	case '3':
		background_color = 2;
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT && state == GLUT_DOWN) {
		cutter.startPos(x_conversion(x, width), y_conversion(y, height));
		cutter.endPos(x_conversion(x, width), y_conversion(y, height));
		activate_cut = true;
	}
	if (button == GLUT_LEFT && state == GLUT_UP) {
		activate_cut = false;
		int poly_num = p.size();
		for (int i = 0; i < poly_num; ++i) {
			if (p[i].check_cut(cutter.return_start(), cutter.return_end())) {
				p.push_back(Poly(&shaderProgramID, p[i].return_L(), p[i].return_color(), p[i].return_loc(), 4));
				p[p.size() - 1].Initialize();
				p.push_back(Poly(&shaderProgramID, p[i].return_R(), p[i].return_color(), p[i].return_loc(), 6));
				p[p.size() - 1].Initialize();
				p[i].deleteBuffer();
				p.erase(p.begin() + i);
				i--;
				poly_num--;
				continue;
			}
		}
	}
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	if (activate_cut) {
		cutter.endPos(x_conversion(x, width), y_conversion(y, height));
	}
	glutPostRedisplay();
}

void TimerF(int value)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution uid(0, 4);
	produce_count += 1;
	if (produce_count >= 60) {
		p.push_back(Poly(&shaderProgramID, uid(dre)));
		p[p.size() - 1].Initialize();
		produce_count = 0;
		std::cout << p.size() << std::endl;
	}
	int rect_num = p.size();
	for (int i = 0; i < rect_num; ++i) {
		if (not p[i].check_put()) {
			p[i].setSpeed(speed);
			p[i].Move(p[i].move_xy());
			p[i].crash_check(bucket);
			if (p[i].return_t() >= 1) {
				p[i].deleteBuffer();
				p.erase(p.begin() + i);
				i--;
				rect_num -= 1;
				continue;
			}
		}
		else {
			p[i].Move(bucket.return_move());
		}

	}
	bucket.Move();
	glutPostRedisplay();
	glutTimerFunc(50, TimerF, 0);
}