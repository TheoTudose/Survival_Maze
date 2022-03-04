#ifndef TEMA2_CROSSHAIR_H
#define TEMA2_CROSSHAIR_H
#pragma once
#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "transform3D.h"


class Crosshair {
private:
	glm::vec3 pos;
	glm::mat4 hor;
	glm::mat4 vert;
	float radX = 0;
	float radY = 0;
	float radZ = 0;
public:
	glm::vec3 getPos() {
		return pos;
	}
	glm::mat4 getHor() {
		return hor;
	}
	glm::mat4 getVert() {
		return vert;
	}

	void setPos(glm::vec3 x);

	void setCrosshairMatrix();

	void setRad(float x, float y, float z);
};


#endif //TEMA2_CROSSHAIR_H
