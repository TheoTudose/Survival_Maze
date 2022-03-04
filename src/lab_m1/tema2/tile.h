#ifndef TEMA2_TILE_H
#define TEMA2_TILE_H

#include "utils/gl_utils.h"
#include "components/simple_scene.h"

class Tile {
private:
	
	glm::mat4 h_matrix;

public:

	glm::mat4 getMatrix()
	{
		return h_matrix;
	}

	Tile(glm::mat4 matrix);

	Tile();

	void setMatrix(float x, float y, float z);
};


#endif //TEMA2_TILE_H
