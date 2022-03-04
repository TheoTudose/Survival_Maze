#include "enemy.h"
#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "lab_m1/tema2/transform3D.h"

Enemy::Enemy(glm::vec3 pos, int health, glm::vec3 initialPos, glm::vec3 trajectory, glm::mat4 modelMatrix)
{
	h_pos = pos;
	h_health = health;
	h_initialPos = initialPos;
	h_trajectory = trajectory;
	h_modelMatrix = modelMatrix;
}
Enemy::Enemy() {}

void Enemy::setHealth(int health)
{
	h_health = health;
}

void Enemy::setInitialPos(float x, float y, float z)
{
	h_initialPos = glm::vec3(x, y, z);
	floorMatrix = glm::mat4(1) * transform3D::Translate(x, -0.05f, z) * 
		transform3D::Scale(2.0f, 0.1f, 2.0f);
}

void Enemy::setStep(float deltaTimeSeconds)
{
	step += deltaTimeSeconds * 5;
}

void Enemy::setModelMatrix()
{
	h_modelMatrix = glm::mat4(1) * transform3D::Translate(h_initialPos.x, h_initialPos.y, h_initialPos.z) *
		transform3D::RotateOY(step) *
		transform3D::Translate(0.4f, 0.0f, 0.0f) *
		transform3D::Scale(0.8f, 0.8f, 0.8f);
	h_pos = h_modelMatrix * glm::vec4(glm::vec3(0), 1);
}

void Enemy::setDeathTimer(float deltaTimeSeconds)
{
	deathTimer -= deltaTimeSeconds;
}