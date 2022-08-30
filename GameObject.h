#ifndef REDMAGIC_GAMEOBJECT_H
#define REDMAGIC_GAMEOBJECT_H

#include <map>
#include <iostream>
#include <typeinfo>
#include "RigidBody2D.h"
#include "Sprite.h"
#include "Resources.h"

namespace RedMagic {

	//base class of Game Objects
	class Entity {
	public:
		Entity(){}
		~Entity(){}

		virtual void Update(double dt) = 0;
	};

	//super class Game Object
	class GameObject : public Entity
	{
	private:
		//attributes
		string tag_;
		vector<b2Joint*> *joints_;
		bool active_;


		//basic game object attributes
		bool is_initialized_;
		map<int, Part*> *components_;
		vector<Part*> *components_to_add_;
		vector<int> *components_to_remove_;
		
		//experimental
		map<int, Script*> * scripts_;

		virtual void SetParent(Part* component) { component->SetGameObject(this); }

		//my game object attributes
		
		void Detach(int key);
		void RemovePart(int key);
	public:
		GameObject();
		~GameObject();

		//basic game object functions

		//verify if game object has some type of component
		template <class T>
		bool HasComponent() const {
			int key = typeid(T).hash_code();
			bool has_component = components_->find(key) != components_->end();
			return has_component;
		}

		//return point to the type of component the game object has
		template <class T>
		T* GetComponent() {
			T* component = 0;

			if (HasComponent<T>())
			{
				int key = typeid(T).hash_code();
				component = static_cast<T*>(components_->find(key)->second);
			}

			return component;
		}

		//add component to game object
		template <class X>
		void AttachComponent(X* component) {
			const bool isBase = is_base_of<Part, X>::value;

			if (isBase) {
				int key = typeid(*component).hash_code();

				//component = dynamic_cast<X*>(components_->find(key)->second);

				if (components_->find(key) == components_->end()) {
					components_->insert(make_pair(key,component));
					SetParent(component);
				}
			}
		}

		//replace component with another same component with different parameters maybe
		template <class X>
		void ReplaceComponent(X* component) {
			int key = typeid(*component).hash_code();
			component = dynamic_cast<X*>(components_->find(key)->second);
			if (components_->find(key) != components_->end())
			{
				Detach(key);
			}

			if (is_initialized_)
			{
				components_to_add_->push_back(component);
			}
			else
			{
				AttachComponent(component);
			}
		}

		//remove component
		template<class T>
		void DetachComponent() {
			if (HasPart<T>())
			{
				int key = typeid(T).hash_code();
				if (find(components_to_remove_.begin(), components_to_remove_.end(), key) == components_to_remove_.end())
				{
					Detach(key);
				}
			}
		}

		//experimental method
		//add script to game object
		template <class X>
		void AttachScript(X* component) {
			const bool isBase = is_base_of<Script, X>::value;

			if (isBase) {
				int key = typeid(*component).hash_code();

				if (scripts_->find(key) == scripts_->end()) {
					scripts_->insert(make_pair(key, component));
					SetParent(component);
				}
			}
		}

		//verify if game object has some type of component
		template <class T>
		bool HasScript() const {
			int key = typeid(T).hash_code();
			bool has_component = scripts_->find(key) != scripts_->end();
			return has_component;
		}

		//return point to the type of component the game object has
		template <class T>
		T* GetScript() {
			T* script = 0;

			if (HasComponent<T>())
			{
				int key = typeid(T).hash_code();
				script = static_cast<T*>(scripts_->find(key)->second);
			}

			return component;
		}

		map<int, Script*>* GetScripts() {
			return scripts_;
		}

		

		void Initialize();
		virtual void Update(double dt);

		//my game object functions
		void SetTag(string tag) { tag_ = tag; }
		string GetTag() { return tag_; }

		void SetActive(bool act) { active_ = act; }
		bool isActive() { return active_; }


		//physic functions
		void createDistanceJoint(GameObject* objectToConnect, glm::vec2 anchor, glm::vec2 anchorToConnect, bool collideConnect);
		void createRevoluteJoint(GameObject* objectToConnect, glm::vec2 anchor, bool collideConnect, bool enableLimit, int lowerAngle, int upperAngle, bool enableMotor, float maxMotorTorque, float motorSpeed);
		void createPrismaticJoint(GameObject* objectToConnect, glm::vec2 anchor, float magnitude, float angle, bool collideConnect, bool enableLimit, float lowerTranslation, float upperTranslation, bool enableMotor, float maxMotorTorque, float motorSpeed);
		void createPulleyJoint(GameObject* objectToConnect, glm::vec2 groundAnchorA, glm::vec2 groundAnchorB, glm::vec2 anchorA, glm::vec2 anchorB, float ratio, bool collideConnected);
		void createGearJoint(GameObject* objectToConnect, b2Joint *jointA, b2Joint *jointB, float ratio);
		void createWheelJoint(GameObject* objectToConnect, glm::vec2 anchor,float magnitude, float angle, bool enableMotor, float maxMotorForce, float motorSpeed, float dampingRatio);
		//weld joint
		//rope joint
		//friction joint

		//collision functions
		virtual void OnCollisionEnter(GameObject* object){}
		virtual void OnCollisionExit(GameObject* object){}

		//force
		void ApplyForce(int force, int angle, float posX, float posY);
		void ApplyForceToCenter(int force, int angle);
		void ApplyLinearImpulse(int force, int angle, float posX, float posY);
	};






	class RMContactListener : public b2ContactListener {

		void BeginContact(b2Contact* contact) {
			void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
			if (bodyUserData) {
				objectB1 = static_cast<RigidBody2D*>(bodyUserData)->GetGameObject();
				objectB1->OnCollisionEnter(objectB2);
			}
			//check if fixture B was a ball
			bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
			if (bodyUserData) {
				objectB2 = static_cast<RigidBody2D*>(bodyUserData)->GetGameObject();
				objectB2->OnCollisionEnter(objectB1);
			}
		}
		void EndContact(b2Contact* contact) {
			void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
			if (bodyUserData) {
				objectE1 = static_cast<RigidBody2D*>(bodyUserData)->GetGameObject();
				objectE1->OnCollisionEnter(objectE2);
			}
			//check if fixture B was a ball
			bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
			if (bodyUserData) {
				objectE2 = static_cast<RigidBody2D*>(bodyUserData)->GetGameObject();
				objectE2->OnCollisionEnter(objectE1);
			}
		}
	private:
		GameObject* objectB1;
		GameObject* objectB2;
		GameObject* objectE1;
		GameObject* objectE2;
	};
}
#endif
