//
// Created by theot on 08.12.2021.
//

#include "crosshair.h"
#include "utils/gl_utils.h"
#include "components/simple_scene.h"
#include "transform3D.h"

void Crosshair::setPos(glm::vec3 x) {
	pos = x;
}

void Crosshair::setRad(float x, float y, float z) {
	radX = x;
	radY = y;
	radZ = z;
}

void Crosshair::setCrosshairMatrix() {
	hor = glm::mat4(1) *
		transform3D::Translate(pos.x, pos.y, pos.z) *
		transform3D::Scale(0.04f, 0.01f, 0.001f);
	vert = glm::mat4(1) *
		transform3D::Translate(pos.x, pos.y, pos.z) *
		transform3D::Scale(0.01f, 0.04f, 0.001f);
}
