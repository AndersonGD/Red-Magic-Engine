#ifndef REDMAGIC_TRANSFORM_H
#define REDMAGIC_TRANSFORM_H

#include "Part.h"
#include <glm\glm.hpp>

namespace RedMagic {

	class Transform : public Part
	{
	protected:
		//RigidBody2D
		glm::vec3 position_;
		glm::vec3 scale_;
		//rotation
	public:
		Transform();
		Transform(float positionX, float positionY, float positionZ, float scaleX, float scaleY, float scaleZ);
		Transform(glm::vec3 position, glm::vec3 scale);
		~Transform();

		void Initialize(float positionX, float positionY, float positionZ, float scaleX, float scaleY, float scaleZ);
		void Initialize(glm::vec3 position, glm::vec3 scale);
		void Cleanup();
		void Update(double dt);

		void SetPosition(float positionX, float positionY, float positionZ);
		void SetPosition(glm::vec3 position);
		void SetPositionX(float x);
		void SetPositionY(float y);
		void SetPositionZ(float z);

		glm::vec3 GetPosition() { return position_; }
		float GetPositionX() { return position_.x; }
		float GetPositionY() { return position_.y; }
		float GetPositionZ() { return position_.z; }

		void SetScale(float width, float height, float depth);
		void SetScale(glm::vec3 scale);
		void SetWidth(float width);
		void SetHeight(float height);
		void SetDepth(float depth);

		glm::vec3 GetScale() { return scale_; }
		float GetWidth() { return scale_.x; }
		float GetHeight() { return scale_.y; }
		float GetDepth() { return scale_.z; }

		bool isInside(float x, float y);



		friend class Sprite;
		friend class RigidBody2D;

	};
}
#endif
