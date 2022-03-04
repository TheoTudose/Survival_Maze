#ifndef TEMA2_AVATAR_H
#define TEMA2_AVATAR_H
#pragma once
#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "transform3D.h"

class Avatar {
private:
	int h_health = 3;
	glm::vec3 h_playerPos;
	glm::mat4 h_head;
	glm::mat4 h_body;
	glm::mat4 h_larm;
	glm::mat4 h_rarm;
	glm::mat4 h_lhand;
	glm::mat4 h_rhand;
	glm::mat4 h_lleg;
	glm::mat4 h_rleg;
	glm::mat4 h_bb;
	glm::vec3 h_startingPos;
	float bbX = 0;
	float bbZ = 0;
	float diag = 0.5797413f;
	float h_radX = 0;
	float h_radY = 0;
	float h_radZ = 0;
	float x = 0;

public:

	glm::vec3 getStartingPos() {
		return h_startingPos;
	}

	int getHealth() {
		return h_health;
	}

	glm::vec3 getPlayerPos() {
		return h_playerPos;
	}

	glm::mat4 getHead() {
		return h_head;
	}

	glm::mat4 getBody() {
		return h_body;
	}

	glm::mat4 getLArm() {
		return h_larm;
	}

	glm::mat4 getRArm() {
		return h_rarm;
	}

	glm::mat4 getLHand() {
		return h_lhand;
	}

	glm::mat4 getRHand() {
		return h_rhand;
	}

	glm::mat4 getLLeg() {
		return h_lleg;
	}

	glm::mat4 getRLeg() {
		return h_rleg;
	}

	glm::mat4 getBB() {
		return h_bb;
	}

	float getBbX() {
		return bbX;
	}
	float getBbZ() {
		return bbZ;
	}
	float getRadX() {
		return h_radX;
	}

	float getRadY() {
		return h_radY;
	}

	float getRadZ() {
		return h_radZ;
	}


	void setStartingPos(glm::vec3 pos);

	void setHealth();

	void setPlayerPos(glm::vec3 x);

	void setPlayerMatrix();
	
	void setRad(float x, float y, float z);

};


#endif //TEMA2_AVATAR_H
