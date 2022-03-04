#include "tile.h"
#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "lab_m1/tema2/transform3D.h"


Tile::Tile(glm::mat4 matrix)
{
	h_matrix = matrix;
}

Tile::Tile() {}

void Tile::setMatrix(float x, float y, float z)
{
	h_matrix = glm::mat4(1) * transform3D::Translate(x, y, z) *
		transform3D::Scale(2.0f, 0.1f, 2.0f);
}