#include "Solar_System.h"

void SolarSystem::Initialize(GLuint* shaderProgram)
{
	shader = shaderProgram;
	sun.Initialize(shader, "sphere.obj", 0.4, 0);
	for (int i = 0; i < 3; ++i) {
		planet[i].Initialize(shader, 5);
		orbit[i].Initialize(shader, 5);
	}
	planet[1].decide_world(45, 0, 0, 1);
	planet[2].decide_world(-45, 0, 0, 1);
	orbit[1].decide(45, 0, 0, 1);
	orbit[2].decide(-45, 0, 0, 1);
}

void SolarSystem::Draw()
{
	sun.Draw();
	for (int i = 0; i < 3; ++i) {
		planet[i].Draw();
		orbit[i].Draw();
	}
	
}
void SolarSystem::anime()
{
	for (Planet& p : planet)
		p.anime();
}

void SolarSystem::change_solid(bool flag)
{
	sun.change_solid(flag);
	for (Planet& p : planet)
		p.change_solid(flag);
}