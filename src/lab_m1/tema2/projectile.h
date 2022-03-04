#ifndef TEMA2_PROJECTILE_H
#define TEMA2_PROJECTILE_H

#include "utils/gl_utils.h"
#include "components/simple_scene.h"

class Projectile {
private:
	glm::vec3 h_trajectory;
	bool h_spawn = true;
	glm::vec3 h_initialPos;
	float h_airTime = 0;
	float h_cooldown = 0.5f;
	float h_speed;
	glm::mat4 h_modelMatrix;
	float h_angle1;
	float translateX = 0;
	float translateY = 0;
	float translateZ = 0;
	glm::vec3 realPos;

public:
	Projectile(glm::vec3 trajectory, bool spawn, glm::vec3 initialPos, float airTime,
		float cooldown, float speed, glm::mat4 modelMatrix, float angle1);

	Projectile();

	glm::vec3 getTrajectory()
	{
		return h_trajectory;
	}

	bool getSpawn()
	{
		return h_spawn;
	}

	glm::vec3 getInitialPos()
	{
		return h_initialPos;
	}

	float getAirTime()
	{
		return h_airTime;
	}

	float getCoolDown()
	{
		return h_cooldown;
	}

	float getSpeed()
	{
		return h_speed;
	}

	glm::mat4 getModelMatrix()
	{
		return h_modelMatrix;
	}

	float getAngle()
	{
		return h_angle1;
	}

	glm::vec3 getRealPos()
	{
		return realPos;
	}


	void setAirTime(float deltaTimeSeconds);

	void setSpeed(float deltaTimeSeconds);

	void setSpawn(bool spawn);

	void setInitialPos(glm::vec3 x);

	void setTrajectory(glm::vec3 x);

	void setTranslate(float deltaTimeSeconds);

	void setModelMatrix();

	void setRealPos();

};


#endif //TEMA2_PROJECTILE_H
