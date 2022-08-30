#include "Transform.h"



RedMagic::Transform::Transform()
{
	position_ = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_ = glm::vec3(1.0f, 1.0f, 1.0f);
}

RedMagic::Transform::Transform(float positionX, float positionY, float positionZ, float scaleX, float scaleY, float scaleZ)
{
	position_.x = positionX;
	position_.y = positionY;
	position_.z = positionZ;
	scale_.x = scaleX;
	scale_.y = scaleY;
	scale_.z = scaleZ;
}

RedMagic::Transform::Transform(glm::vec3 position, glm::vec3 scale)
{
	position_ = position;
	scale_ = scale;
}


RedMagic::Transform::Transform::~Transform()
{
}

void RedMagic::Transform::Initialize(glm::vec3 position, glm::vec3 scale) {
	position_ = position;
	scale_ = scale;
}

void RedMagic::Transform::Initialize(float positionX, float positionY, float positionZ, float scaleX, float scaleY, float scaleZ) {
	position_.x = positionX;
	position_.y = positionY;
	position_.z = positionZ;
	scale_.x = scaleX;
	scale_.y = scaleY;
	scale_.z = scaleZ;
}

void RedMagic::Transform::Cleanup() {

}

void RedMagic::Transform::Update(double dt) {

}

void RedMagic::Transform::SetPosition(float positionX, float positionY, float positionZ) {
	position_.x = positionX;
	position_.y = positionY;
	position_.z = positionZ;
}

void RedMagic::Transform::SetPosition(glm::vec3 position) {
	position_ = position;
}

void RedMagic::Transform::SetPositionX(float x) {
	position_.x = x;
}

void RedMagic::Transform::SetPositionY(float y) {
	position_.y = y;
}

void RedMagic::Transform::SetPositionZ(float z) {
	position_.z = z;
}

void RedMagic::Transform::SetScale(float width, float height, float depth) {
	scale_.x = width;
	scale_.y = height;
	scale_.z = depth;

}

void RedMagic::Transform::SetScale(glm::vec3 scale) {
	scale_ = scale;
}

void RedMagic::Transform::SetWidth(float width) {
	scale_.x = width;
}

void RedMagic::Transform::SetHeight(float height){
	scale_.y = height;
}

void RedMagic::Transform::SetDepth(float depth) {
	scale_.z = depth;
}

bool RedMagic::Transform::isInside(float x, float y) {
	if (x <= position_.x + (scale_.x / 2) && x >= position_.x - (scale_.x / 2) && y <= position_.y + (scale_.y / 2) && y >= position_.y - (scale_.y / 2)) {
		return true;
	}
	return false;
}