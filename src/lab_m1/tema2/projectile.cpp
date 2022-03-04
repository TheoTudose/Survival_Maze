#include "projectile.h"
#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "lab_m1/tema2/transform3D.h"
#include <iostream>

Projectile::Projectile(glm::vec3 trajectory, bool spawn, glm::vec3 initialPos, float airTime,
	float cooldown, float speed, glm::mat4 modelMatrix, float angle1)
{
	h_trajectory = trajectory;
	h_spawn = spawn;
	h_initialPos = initialPos;
	h_airTime = airTime;
	h_cooldown = cooldown;
	h_speed = speed;
	h_modelMatrix = modelMatrix;
	h_angle1 = angle1;
	
}
Projectile::Projectile() {}

void Projectile::setAirTime(float deltaTimeSeconds) {
	h_airTime += deltaTimeSeconds;
}

void Projectile::setSpeed(float deltaTimeSeconds) {
	h_speed = deltaTimeSeconds * 10;
}

void Projectile::setSpawn(bool spawn) {
	h_spawn = spawn;
}

void Projectile::setInitialPos(glm::vec3 pPos) {
	h_initialPos = glm::vec3 (pPos.x, 1.0f, pPos.z);
}

void Projectile::setTrajectory(glm::vec3 x) {
	
	h_trajectory = glm::normalize(x);
}

void Projectile::setTranslate(float deltaTimeSeconds) {
	translateX += h_trajectory.x * deltaTimeSeconds * 10;
	translateY += h_trajectory.y * deltaTimeSeconds * 10;
	translateZ += h_trajectory.z * deltaTimeSeconds * 10;
}

void Projectile::setModelMatrix() {
	h_modelMatrix = glm::mat4(1) *
		transform3D::Translate(h_initialPos.x + translateX, h_initialPos.y + translateY,
			h_initialPos.z + translateZ) *
		transform3D::Scale(0.2f, 0.2f, 0.2f);

}

void Projectile::setRealPos() {
	realPos = glm::vec3(h_initialPos.x + translateX,
		h_initialPos.y + translateY, h_initialPos.z + translateZ);
}
