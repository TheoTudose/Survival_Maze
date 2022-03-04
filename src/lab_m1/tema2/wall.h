#ifndef TEMA2_WALL_H
#define TEMA2_WALL_H
#pragma once
#include "utils/gl_utils.h"
#include "components/simple_scene.h"


class Wall {
private:
	glm::vec3 h_color = glm::vec3(0.000f, 0.808f, 0.820f);
	float h_length = 2;
	float h_height = 2;
	glm::vec3 h_pos;
	glm::vec3 h_size;
	float h_centerX;
	float h_centerY;
	float h_centerZ;
	glm::mat4 h_modelMatrix;

public:
	Wall(glm::vec3 color, float length, float height,
		glm::vec3 pos, glm::vec3 size, float centerX,
		float centerY, float centerZ, glm::mat4 modelMatrix);

	Wall();

	glm::vec3 getColor()
	{
		return h_color;
	}

	glm::vec3 getPos()
	{
		return h_pos;
	}

	float getLength() {
		return h_length;
	}

	float getHeight() {
		return h_height;
	}

	glm::vec3 getSize()
	{
		return h_size;
	}

	float getCenterX()
	{
		return h_centerX;
	}

	float getCenterY()
	{
		return h_centerY;
	}

	float getCenterZ()
	{
		return h_centerY;
	}

	glm::mat4 getModelMatrix()
	{
		return h_modelMatrix;
	}

	void setPos(float x, float y, float z);

	void setSize(float x, float y, float z);

	void setModelMatrix();
};


#endif //TEMA2_WALL_H
