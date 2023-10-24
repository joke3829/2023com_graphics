
#include "Planet.h"

void Planet::Initialize(GLuint* shaderProgram, float r)
{
	shader = shaderProgram;
	planet.Initialize(shader, "sphere.obj", 0.1, 0);
	satellite.Initialize(shader, "sphere.obj", 0.05, 1.5);
	orbit.Initialize(shader, 1.5);

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd_speed(0.01, 0.05);

	speed = urd_speed(dre);
	rad = 0;
	move_dis = glm::vec3(5 * glm::cos(rad), 0, 5 * glm::sin(rad));
	Move();

}

void Planet::Draw()
{
	planet.Draw();
	satellite.Draw();
	orbit.Draw();
}

void Planet::Move()
{
	planet.Move(move_dis.x, move_dis.y, move_dis.z);
	satellite.Move(move_dis.x, move_dis.y, move_dis.z);
	orbit.Move(move_dis.x, move_dis.y, move_dis.z);
}

void Planet::anime()
{
	rad += speed;
	move_dis = glm::vec3(5 * glm::cos(rad), 0, 5 * glm::sin(rad));
	Move();
	satellite.Rotate_world();
}

void Planet::decide_world(float rr, float x, float y, float z)
{
	glm::mat4 temp = glm::mat4(1.0f);
	temp = glm::rotate(temp, glm::radians(rr), glm::vec3(x, y, z));
	planet.decide_world(rr, x, y, z);
	satellite.decide_world(rr, x, y, z);
	orbit.decide(rr, x, y, z);
}

void Planet::change_solid(bool flag)
{
	planet.change_solid(flag);
	satellite.change_solid(flag);
}