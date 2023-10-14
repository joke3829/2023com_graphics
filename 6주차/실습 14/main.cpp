#include "Filetobuf.h"
#include "Mesh.h"

void make_vertexShaders();		// vertexShader ���� �Լ�
void make_fragmentShaders();	// fragmentShader �����Լ�
GLuint make_shaderProgram();	// ���� ���̴� ���α׷� �����Լ�

void LineBuffer();
void Keyboard(unsigned char, int, int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
GLuint shaderProgramID;			// ���̴� ���α׷� �̸�
GLuint vertexShader;			// vertexShader ��ü
GLuint fragmentShader;			// fragment ��ü
GLuint Line_vao[2], Line_vbo[4];

float Line_x[6] = { -1, 0, 0, 1,0,0 };
float Line_x_color[6]{ 1,0,0,1,0,0 };

float Line_y[6] = { 0, -1, 0 , 0, 1, 0};
float Line_y_color[6]{ 0,1,0, 0,1,0 };


Mesh pyramid;
Mesh Cube;

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
	glGenVertexArrays(2, Line_vao);
	glGenBuffers(4, Line_vbo);
	LineBuffer();
	pyramid.Initialize(&shaderProgramID, "pyramid.obj");
	Cube.Initialize(&shaderProgramID, "cube.obj");
	pyramid.Scale(0.05);
	pyramid.Rotate(10.0, 1.0, 0.0, 0.0);
	pyramid.Rotate(10.0, 0.0, 1.0, 0.0);
	pyramid.Move(0.5, 0.0, 0.0);

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
	//glEnable(GL_CULL_FACE);
	glm::mat4 start_trans = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "transform"), 1, GL_FALSE, glm::value_ptr(start_trans));
	glBindVertexArray(Line_vao[0]);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(Line_vao[1]);
	glDrawArrays(GL_LINES, 0, 2);
	pyramid.Draw();
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

}

void LineBuffer()
{
	glBindVertexArray(Line_vao[0]);

	glBindBuffer(GL_ARRAY_BUFFER, Line_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Line_x), Line_x, GL_STATIC_DRAW);
	unsigned int loc = glGetAttribLocation(shaderProgramID, "vPos");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);

	glBindBuffer(GL_ARRAY_BUFFER, Line_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Line_x_color), Line_x_color, GL_STATIC_DRAW);
	loc = glGetAttribLocation(shaderProgramID, "vColor");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);

	glBindVertexArray(Line_vao[1]);

	glBindBuffer(GL_ARRAY_BUFFER, Line_vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Line_y), Line_y, GL_STATIC_DRAW);
	loc = glGetAttribLocation(shaderProgramID, "vPos");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);

	glBindBuffer(GL_ARRAY_BUFFER, Line_vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Line_y_color), Line_y_color, GL_STATIC_DRAW);
	loc = glGetAttribLocation(shaderProgramID, "vColor");
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(loc);
}