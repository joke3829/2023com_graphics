#include "Filetobuf.h"
#include "Floor.h"
#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")

void make_vertexShaders();		// vertexShader 생성 함수
void make_fragmentShaders();	// fragmentShader 생성함수
GLuint make_shaderProgram();	// 최종 셰이더 프로그램 생성함수

void Keyboard(unsigned char, int, int);
void KeyboardUp(unsigned char, int, int);
void Special(int, int, int);
void SpecialUp(int, int, int);
void TimerF(int);

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int width, height;
bool move_w, move_a, move_s, move_d;
bool y_rot, Y_rot, z_move, Z_move;

bool falling;
bool press_f;
int falling_count, f_count;
int robot_num, ro_count;

GLuint shaderProgramID;			// 셰이더 프로그램 이름
GLuint vertexShader;			// vertexShader 객체
GLuint fragmentShader;			// fragment 객체


Camera camera;
Projection proj;

//Robot robot;
std::vector<Robot> r;
Floor myfloor;

Mesh bridge[8];
Mesh cylinder[4];

void main(int argc, char** argv)
{
	robot_num = 1;
	ro_count = 0;
	width = height = 800;
	falling = true;
	press_f = false;
	move_w = move_a = move_s = move_d = false;
	y_rot = Y_rot = z_move = Z_move = false;
	//윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);				// 윈도우의 위치 지정
	glutInitWindowSize(width, height);					// 윈도우의 크기 지정
	glutCreateWindow("실습 24");					// 윈도우 생성(윈도우 이름)

	//GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)						//glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	shaderProgramID = make_shaderProgram();			// 셰이더 프로그램 만들기

	camera.Initialize(&shaderProgramID);
	proj.Initialize(&shaderProgramID);

	{
		Robot robot1, robot2, robot3, robot4;
		r.push_back(robot1);
		r.push_back(robot2);
		r.push_back(robot3);
		r.push_back(robot4);
	}
	for (int i = 0; i < r.size(); ++i) {
		if(0 == i)
			r[i].Initialize(&shaderProgramID, 0);
		else
			r[i].Initialize(&shaderProgramID, 1);
	}
	myfloor.Initialize(&shaderProgramID);

	for (int i = 0; i < 8; ++i) {
		bridge[i].Initialize(&shaderProgramID, "cube.obj");
		bridge[i].Init_texture("n_art.png", 1024, 1024);
		bridge[i].init_scale(0.2);
	}
	bridge[0].Move(glm::vec3(-7, 1, -7));
	bridge[1].Move(glm::vec3(-7, 3, -7));
	bridge[2].Move(glm::vec3(-7, 5, -7));
	bridge[3].Move(glm::vec3(-5, 5, -7));
	bridge[4].Move(glm::vec3(-3, 5, -7));
	bridge[5].Move(glm::vec3(-1, 5, -7));
	bridge[6].Move(glm::vec3(-1, 3, -7));
	bridge[7].Move(glm::vec3(-1, 1, -7));

	for (int i = 0; i < 4; ++i) {
		cylinder[i].Initialize(&shaderProgramID, "cylinder.obj");
		cylinder[i].Init_texture("default.png", 1024, 1024);
	}
	cylinder[0].Move(glm::vec3(-9, 0, -9));
	cylinder[1].Move(glm::vec3(9, 0, -9));
	cylinder[2].Move(glm::vec3(-9, 0, 9));
	cylinder[3].Move(glm::vec3(9, 0, 9));

	glutDisplayFunc(drawScene);						// 출력 함수의 지정
	glutReshapeFunc(Reshape);						// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(Special);
	glutSpecialUpFunc(SpecialUp);
	glutTimerFunc(50, TimerF, 0);
	glutMainLoop();									// 이벤트 처리 시작
}

GLvoid drawScene()									// 콜백 함수: 그리기 콜백 함수
{
	glUseProgram(shaderProgramID);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(int i = 0 ; i < robot_num; ++i)
		r[i].Draw();
	for (Mesh& c : cylinder)
		c.Draw();
	myfloor.Draw();
	for (Mesh& b : bridge)
		b.Draw();


	glutSwapBuffers();								// 화면에 출력하기
}

GLvoid Reshape(int w, int h)						// 콜백 함수: 다시 그리기 콜백 함수
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
	make_vertexShaders();							// vertexShader 만들기
	make_fragmentShaders();							// 프래그먼트 셰이더 만들기
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
		r[0].speed_control('+');
		break;
	case '-':
		r[0].speed_control('-');
		break;
	case 'g':
		if (falling) {
			falling = false;
			falling_count = 0;
		}
		break;
	case 'i':
		r[0].Trans_init(glm::vec3(0, 0, 0));
		break;
	case 't':
		if (1 == robot_num)
			robot_num = 4;
		else
			robot_num = 1;
		break;
	case 'f':
		press_f = true;
		f_count = 0;
		break;
	case 'q':
		glutLeaveMainLoop();
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
	// 플레이어 1 조작
	if (r[0].state_check()) {
		if (move_w) {
			r[0].Move(8);
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					if (r[0].check_crash(myfloor.getMesh(i, j))) {
						r[0].Move(2);
						break;
					}
				}
			}
			for (int i = 0; i < 8; ++i) {
				if (r[0].check_crash(bridge[i])) {
					r[0].Move(2);
					break;
				}
			}
			for (int i = 0; i < 4; ++i) {
				if (r[0].check_crash(cylinder[i], 0)) {
					r[0].Move(2);
					break;
				}
			}
		}
		if (move_a)
			r[0].Rotate(4);
		if (move_s) {
			r[0].Move(2);
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					if (r[0].check_crash(myfloor.getMesh(i, j))) {
						r[0].Move(8);
						break;
					}
				}
			}
			for (int i = 0; i < 8; ++i) {
				if (r[0].check_crash(bridge[i])) {
					r[0].Move(8);
					break;
				}
			}
			for (int i = 0; i < 4; ++i) {
				if (r[0].check_crash(cylinder[i], 0)) {
					r[0].Move(8);
					break;
				}
			}
		}
		if (move_d)
			r[0].Rotate(6);
		if (move_w || move_a || move_s || move_d)
			r[0].arm_legAni();
		else
			r[0].stand_ani();
		if (z_move)
			camera.dis_plus(8);
		if (Z_move)
			camera.dis_plus(2);
		if (y_rot)
			camera.rotate_pos(4);
		if (Y_rot)
			camera.rotate_pos(6);

		if (falling) {
			r[0].fallen(2);
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					if (r[0].check_crash(myfloor.getMesh(i, j))) {
						if (myfloor.getMesh(i, j).getMoving()) {
							if (myfloor.getMesh(i, j).getDropcube())
								myfloor.getMesh(i, j).change_lever();
							else {
								if(myfloor.getMesh(i, j).return_loc().y > -1)
									myfloor.getMesh(i, j).Move(myfloor.getMesh(i, j).return_loc() - glm::vec3(0, 0.5, 0));
							}
						}
						r[0].fallen(5);
						break;
					}
				}
			}
			for (int i = 0; i < 8; ++i) {
				if (r[0].check_crash(bridge[i])) {
					r[0].fallen(5);
					break;
				}
			}
		}
		else {
			if (falling_count >= 7) {
				r[0].fallen(2);
				for (int i = 0; i < 10; ++i) {
					for (int j = 0; j < 10; ++j) {
						if (r[0].check_crash(myfloor.getMesh(i, j))) {
							r[0].fallen(5);
							falling = true;
							break;
						}
					}
				}
				for (int i = 0; i < 8; ++i) {
					if (r[0].check_crash(bridge[i])) {
						r[0].fallen(5);
						falling = true;
						break;
					}
				}
			}
			else {
				r[0].fallen(8);
				for (int i = 0; i < 8; ++i) {
					if (r[0].check_crash(bridge[i])) {
						r[0].fallen(2);
						falling = true;
						break;
					}
				}
				falling_count += 1;
			}
		}
	}

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (myfloor.getMesh(i, j).getLever()) {
				myfloor.getMesh(i, j).Move(myfloor.getMesh(i, j).return_loc() - glm::vec3(0, 0.5, 0));
			}
		}
	}
	if (not press_f) {
		ro_count++;
		if (ro_count >= 5) {
			for (int i = 3; i > 0; --i) {
				r[i].Move(r[i - 1].return_loc());
				r[i].Rotate(r[i - 1].return_rot());
			}
			ro_count = 0;
		}
	}
	else {
		if (f_count >= 10) {
			press_f = false;
		}
		else if (f_count >= 5) {
			for (int i = 1; i < 4; ++i) {
				r[i].Move(r[i].return_loc() - glm::vec3(0, 1, 0));
			}
		}
		else {
			for (int i = 1; i < 4; ++i) {
				r[i].Move(r[i].return_loc() + glm::vec3(0, 1, 0));
			}
		}
		f_count++;
	}
	glutPostRedisplay();
	glutTimerFunc(50, TimerF, 0);
}


void Special(int key, int x, int y)
{
	glutPostRedisplay();
}

void SpecialUp(int key, int x, int y)
{
	glutPostRedisplay();
}