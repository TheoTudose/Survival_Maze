#ifndef TEMA2_ENEMY_H
#define TEMA2_ENEMY_H

#include "utils/gl_utils.h"
#include "components/simple_scene.h"

class Enemy {
private:
	glm::vec3 h_pos;
	int h_health = 1;
	float deathTimer = 3;
	glm::vec3 h_initialPos;
	glm::vec3 h_trajectory;
	float step = 0;
	glm::mat4 h_modelMatrix;
	glm::mat4 floorMatrix;

public:
	Enemy(glm::vec3 pos, int health, glm::vec3 initialPos, glm::vec3 trajectory, glm::mat4 modelMatrix);

	Enemy();

	glm::vec3 getPos()
	{
		return h_pos;
	}

	int getHealth()
	{
		return h_health;
	}

	float getDeathTimer()
	{
		return deathTimer;
	}

	glm::vec3 getInitialPos()
	{
		return h_initialPos;
	}

	glm::vec3 getTrajectory()
	{
		return h_trajectory;
	}

	glm::mat4 getModelMatrix()
	{
		return h_modelMatrix;
	}

	glm::mat4 getFloorMatrix()
	{
		return floorMatrix;
	}

	void setHealth(int health);

	void setInitialPos(float x, float y, float z);

	void setStep(float deltaTimeSeconds);

	void setDeathTimer(float deltaTimeSeconds);

	void setModelMatrix();

};


#endif //TEMA2_ENEMY_H
