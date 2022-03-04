#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "lab_m1/tema2/transform3D.h"
#include "lab_m1/tema2/wall.h"

Wall::Wall(glm::vec3 color, float length, float height,
	glm::vec3 pos, glm::vec3 size, float centerX,
	float centerY, float centerZ, glm::mat4 modelMatrix) {
	h_color = color;
	h_length = length;
	h_height = height;
	h_pos = pos;
	h_size = size;
	h_centerX = centerX;
	h_centerY = centerY;
	h_centerZ = centerZ;
	h_modelMatrix = modelMatrix;
}

Wall::Wall() {}

void Wall::setPos(float x, float y, float z)
{
	h_pos = glm::vec3(x - 20.f, y, z - 20.f);
}

void Wall::setSize(float x, float y, float z)
{
	h_size = glm::vec3(x, y, z);
}

void Wall::setModelMatrix()
{
	h_modelMatrix = glm::mat4(1) * transform3D::Translate(h_pos.x, h_pos.y, h_pos.z) *
		transform3D::Scale(h_length, h_height, h_length);
}