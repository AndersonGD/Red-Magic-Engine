#ifndef REDMAGIC_RIGIDBODY2D_H
#define REDMAGIC_RIGIDBODY2D_H

#include "Transform.h"
#include <Box2D\Box2D.h>
#include <vector>

namespace RedMagic {

	class RigidBody2D : public Part
	{
	private:
		b2Body* body_;
		Transform *transform_;
		vector<b2Fixture*> *fixtures_;
		float density_;
		float mass_;
		float friction_;
		float restitution_;
	public:
		RigidBody2D();
		RigidBody2D(b2World* world, b2BodyType bodyType, Transform* transform);
		~RigidBody2D();

		void Initialize(b2World* world, b2BodyType bodyType, Transform* transform);
		virtual void Cleanup();
		virtual void Update(double dt);

		//Setting colliders will get the basic attribute stats, you can customize then with Set's before you set the Collider
		//You change the collider of your object whenever you want it with this Set
		void SetBoxCollider(float width, float height);
		//Setting colliders will get the basic attribute stats, you can customize then with Set's before you set the Collider
		//You change the collider of your object whenever you want it with this Set
		void SetPolygonCollider(glm::vec2 *points);
		//Setting colliders will get the basic attribute stats, you can customize then with Set's before you set the Collider
		//You change the collider of your object whenever you want it with this Set
		void SetCircleCollider(float radius);

		//Adding colliders wont remove the previous collider
		void AddBoxCollider(float width, float height);
		//Adding colliders wont remove the previous collider
		void AddPolygonCollider(glm::vec2 *points);
		//Adding colliders wont remove the previous collider
		void AddCircleCollider(float radius);

		void SetDensity(float density) { density_ = density; }
		void SetMass(float mass) { mass_ = mass; }
		void SetFriction(float friction) { friction_ = friction; }
		void setRestitution(float restitution) { restitution_ = restitution; }

		float GetDensity() { return density_; }
		float GetMass() { return mass_; }
		float GetFriction() { return friction_; }
		float GetRestitution() { return restitution_; }

		b2Body* GetBody() { return body_; }
		Transform* GetTransform() { return transform_; }
		b2Fixture* GetFixture(int id) { return fixtures_->at(id); }
		vector<b2Fixture*>* GetAllFixtures() { return fixtures_; }
	};
}
#endif
