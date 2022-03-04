#include "avatar.h"
#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "transform3D.h"

void Avatar::setStartingPos(glm::vec3 pos) {
	h_startingPos = pos;
}

void Avatar::setHealth() {
	h_health --;
}

void Avatar::setPlayerPos(glm::vec3 x) {
	h_playerPos = x;
}

void Avatar::setPlayerMatrix() {
	
	if ((h_radX > 1.57079632679f) || ((h_radX > -1.57079632679f) && (h_radX < 0)))
	{
		bbX =   diag * sin(h_radX - 1.57079632679f + 0.261714f);
		bbZ = diag * cos(h_radX - 1.57079632679f + 0.261714f) + 0.3f * sin(h_radX - 1.57079632679f);
		
	}
	else {
		bbZ = diag * abs(sin(h_radX + 0.261714f));
		bbX = 1.12f * abs(cos(h_radX)) - diag * abs(cos(h_radX + 0.261714f));
		if (bbX <= 0.15f) {
			bbX = 0.15f;
		}
	}
	
	h_bb = glm::mat4(1) * transform3D::Translate(h_startingPos.x, 0.6625f, h_startingPos.z) *
		transform3D::Scale(bbX, 1.325f, bbZ);

	h_head = glm::mat4(1)*
		transform3D::Translate(h_startingPos.x, 1.175f, h_startingPos.z) *
		transform3D::RotateOY(h_radX) *
		transform3D::Scale(0.15f, 0.15f, 0.15f);
	h_body = glm::mat4(1) *
		transform3D::Translate(h_startingPos.x, 0.85f, h_startingPos.z) *
		transform3D::RotateOY(h_radX) *
		transform3D::Scale(0.3f, 0.5f, 0.15f);

	h_larm = glm::mat4(1) *
		transform3D::Translate(h_startingPos.x, 0.95f, h_startingPos.z) *
		transform3D::RotateOY(h_radX) *
		transform3D::Translate(-0.215f, 0.0f, 0.0f) *
		transform3D::Scale(0.13f, 0.3f, 0.13f);
	h_rarm = glm::mat4(1) *
		transform3D::Translate(h_startingPos.x, 0.95f, h_startingPos.z) *
		transform3D::RotateOY(h_radX) *
		transform3D::Translate(0.215f, 0.0f, 0.0f)*
		transform3D::Scale(0.13f, 0.3f, 0.13f);
	h_rhand = glm::mat4(1) *
		transform3D::Translate(h_startingPos.x, 0.737f, h_startingPos.z) *
		transform3D::RotateOY(h_radX) *
		transform3D::Translate(0.215f, 0.0f, 0.0f) *
		transform3D::Scale(0.125f, 0.125f, 0.125f);
	h_lhand = glm::mat4(1) *
		transform3D::Translate(h_startingPos.x, 0.737f, h_startingPos.z) *
		transform3D::RotateOY(h_radX) *
		transform3D::Translate(- 0.215f, 0.0f, 0.0f) *
		transform3D::Scale(0.125f, 0.125f, 0.125f);
	h_lleg = glm::mat4(1) *
		transform3D::Translate(h_startingPos.x , 0.3f, h_startingPos.z) *
		transform3D::RotateOY(h_radX) *
		transform3D::Translate(- 0.085f, 0.0f, 0.0f) *
		transform3D::Scale(0.13f, 0.6f, 0.15f);
	h_rleg = glm::mat4(1) *
		transform3D::Translate(h_startingPos.x, 0.3f, h_startingPos.z) *
		transform3D::RotateOY(h_radX) *
		transform3D::Translate(0.085f, 0.0f, 0.0f) *
		transform3D::Scale(0.13f, 0.6f, 0.15f);
}

void Avatar::setRad(float x, float y, float z) {
	h_radX = x;
	h_radY = y;
	h_radZ = z;
}
