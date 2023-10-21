#include "Filetobuf.h"
#include "ortho.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void Keyboard(unsigned char, int, int);
void y_rotating(int);
void t_rotate(int);
void f_rotate(int);
void s_move(int);
void b_scale(int);
void Timer_fold(int);
void r_func(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height, r_count;
bool r_timer;
bool culling, push_y, push_t, push_f, push_s, push_b, push_p;
bool view_shape;
bool fold;
GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü

Line Line_x(0);
Line Line_y(1);
Line Line_z(2);

Camera camera;
Projection proj;
Ortho ort;
Cube cube;
Pyramid pyramid;

void main(int argc, char** argv)
{
	r_count = 0;
	push_y = push_t = push_f = push_s = push_b = push_p = r_timer = false;
	culling = view_shape = fold = true;
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
	Line_x.Initialize(&shaderProgramID);
	Line_y.Initialize(&shaderProgramID);
	Line_z.Initialize(&shaderProgramID);

	Line_x.Update_scale(10); Line_y.Update_scale(10); Line_z.Update_scale(10);

	cube.Initialize(&shaderProgramID);
	pyramid.Initialize(&shaderProgramID);

	camera.Initialize(&shaderProgramID);
	proj.Initialize(&shaderProgramID);
	ort.Initialize(&shaderProgramID);

	glutDisplayFunc(drawScene);						// ��� �Լ��� ����
	glutTimerFunc(100, f_rotate, 2);
	glutTimerFunc(100, s_move, 3);
	glutTimerFunc(100, b_scale, 4);
	glutTimerFunc(100, Timer_fold, 5);
	glutReshapeFunc(Reshape);						// �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(Keyboard);
	glutMainLoop();									// �̺�Ʈ ó�� ����
}

GLvoid drawScene()									// �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glUseProgram(shaderProgramID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (culling)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	Line_x.Draw();
	Line_y.Draw();
	Line_z.Draw();

	if (view_shape)
		cube.Draw();
	else
		pyramid.Draw();

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
	case 'h':
		if (culling)
			culling = false;
		else
			culling = true;
		break;
	case 'y':
		if (push_y)
			push_y = false;
		else {
			push_y = true;
			glutTimerFunc(100, y_rotating, 0);
		}
		break;
	case 't':
		if (push_t)
			push_t = false;
		else {
			push_t = true;
			glutTimerFunc(100, t_rotate, 1);
		}
		break;
	case 'f':
		if (push_f)
			push_f = false;
		else
			push_f = true;
		break;
	case 's':
		if (push_s)
			push_s = false;
		else
			push_s = true;
		break;
	case 'b':
		if (push_b)
			push_b = false;
		else
			push_b = true;
		break;
	case 'c':
		if (view_shape)
			view_shape = false;
		else
			view_shape = true;
		break;
	case 'o':
		pyramid.change_tri_state(false);
		if (fold) {
			fold = false;
			pyramid.change_tri_bool(fold);
		}
		else {
			fold = true;
			pyramid.change_tri_bool(fold);
		}
		break;
	case 'p':
		if (push_p) {
			push_p = false;
			ort.OuttoVS();
		}
		else {
			proj.OuttoVS();
			push_p = true;
		}
		break;
	case 'r':
		r_count = 0;
		r_timer = true;
		pyramid.change_tri_state(true);
		if (fold) {
			fold = false;
			glutTimerFunc(100, r_func, 6);
		}
		else {
			fold = true;
			glutTimerFunc(100, r_func, 6);
		}
		break;
	}
	glutPostRedisplay();
}

void y_rotating(int value) 
{
	camera.y_rotate_timer();
	glutPostRedisplay();
	if (push_y)
		glutTimerFunc(100, y_rotating, 0);
}

void t_rotate(int value)
{
	cube.t_rotate();
	glutPostRedisplay();
	if (push_t)
		glutTimerFunc(100, t_rotate, 1);
}

void f_rotate(int value)
{
	cube.f_rotate(push_f);
	glutPostRedisplay();
	glutTimerFunc(100, f_rotate, 2);
}

void s_move(int value)
{
	cube.s_move(push_s);
	glutPostRedisplay();
	glutTimerFunc(100, s_move, 3);
}

void b_scale(int value)
{
	cube.b_scale(push_b);
	glutPostRedisplay();
	glutTimerFunc(100, b_scale, 4);
}

void Timer_fold(int value)
{	
	pyramid.fold_timer();
	glutPostRedisplay();
	glutTimerFunc(100, Timer_fold, 5);
}

void r_func(int value)
{
	pyramid.change_tri_bool(fold, 0);
	r_count++;
	if(r_count >= 12)
		pyramid.change_tri_bool(fold, 1);
	if(r_count >= 24)
		pyramid.change_tri_bool(fold, 2);
	if (r_count >= 36) {
		r_timer = false;
		pyramid.change_tri_bool(fold, 3);
	}
	glutPostRedisplay();
	if (r_timer)
		glutTimerFunc(100, r_func, 6);
}