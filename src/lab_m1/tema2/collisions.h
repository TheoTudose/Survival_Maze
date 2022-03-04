#pragma once
#include "avatar.h"
#include "wall.h"
#include "projectile.h"
#include "enemy.h"
#include "components/simple_scene.h"
#include "avatar.h"

namespace collisions
{

	enum Direction {
		BACKWARD,
		FORWARD,
		LEFT,
		RIGHT
	};
	
	Direction VectorDirection(glm::vec2 target);

	typedef std::tuple<bool, Direction, glm::vec2> Collision;
	
	bool CheckPrOCollision(std::vector<Projectile>::iterator i, std::vector<Wall>::iterator j);

	Collision CheckAWCollision(Avatar* player, std::vector<Wall>::iterator i);

	bool CheckPrECollision(std::vector<Projectile>::iterator one, std::vector<Enemy>::iterator two);

	bool CheckEPCollision(Avatar* one, std::vector<Enemy>::iterator two);
}