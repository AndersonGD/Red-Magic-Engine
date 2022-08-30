#include "GameObject.h"

namespace RedMagic {

	GameObject::GameObject()
	{
		is_initialized_ = false;
		joints_ = new vector<b2Joint*>;
		components_to_remove_ = new vector<int>;

		components_to_add_ = new vector<Part*>;
		components_ = new map<int, Part*>;

		scripts_ = new map<int, Script*>;

		active_ = true;

		//Initialize();
	}


	GameObject::~GameObject()
	{
		for (auto it = components_->begin(); it != components_->end(); it++) {
			it->second->Cleanup();
		}
	}

	void GameObject::Detach(int key){
		components_to_remove_->push_back(key);
	}

	void GameObject::RemovePart(int key)
	{
		if (components_->find(key) != components_->end())
		{
			Part* removed_part = components_->find(key)->second;
			removed_part->Cleanup();
			components_->erase(key);
		}
		else
		{
			std::string message = "Entity: Detach failed.  Cannot be found Part with key id "
				+ key;
		}
	}

	void GameObject::Initialize()
	{
		is_initialized_ = true;

		for (auto it = components_->begin(); it != components_->end(); it++)
		{
			it->second->Initialize();
		}
	}

	void GameObject::Update(double dt)
	{
		for (auto it = components_->begin(); it != components_->end(); it++)
		{
			if (it->second->is_active())
			{
				it->second->Update(dt);
			}
		}

		while (!components_to_remove_->empty())
		{
			RemovePart(components_to_remove_->back());
			components_to_remove_->pop_back();
		}

		while (!components_to_add_->empty())
		{
			AttachComponent(components_to_add_->back());
			components_to_add_->pop_back();
		}
	}

	void GameObject::createDistanceJoint(GameObject* objectToConnect, glm::vec2 anchor, glm::vec2 anchorToConnect, bool collideConnect) {
		b2DistanceJointDef dJointDef;
		b2DistanceJoint* dJoint;

		b2Vec2 anchorA = Resources::getInstance()->convertGlm2ToB2Vec2(anchor);
		b2Vec2 anchorB = Resources::getInstance()->convertGlm2ToB2Vec2(anchorToConnect);

		b2Body* mainBody = this->GetComponent<RigidBody2D>()->GetBody();

		dJointDef.Initialize(mainBody, objectToConnect->GetComponent<RigidBody2D>()->GetBody(), anchorA, anchorB);
		dJointDef.collideConnected = collideConnect;
		dJoint = (b2DistanceJoint*)mainBody->GetWorld()->CreateJoint(&dJointDef);

		joints_->push_back(dJoint);
		Part* sp = this->GetComponent<Part>();
	}

	void GameObject::createRevoluteJoint(GameObject* objectToConnect, glm::vec2 anchor, bool collideConnect, bool enableLimit, int lowerAngle, int upperAngle, bool enableMotor, float maxMotorTorque, float motorSpeed) {
		b2RevoluteJointDef rJointDef;
		b2RevoluteJoint* rJoint;

		b2Vec2 anchorA = Resources::getInstance()->convertGlm2ToB2Vec2(anchor);

		b2Body* mainBody = this->GetComponent<RigidBody2D>()->GetBody();

		rJointDef.Initialize(mainBody, objectToConnect->GetComponent<RigidBody2D>()->GetBody(), anchorA);
		rJointDef.collideConnected = collideConnect;

		//Para limitar o angulo
		rJointDef.lowerAngle = Resources::getInstance()->degreesToRadians(lowerAngle);
		rJointDef.upperAngle = Resources::getInstance()->degreesToRadians(upperAngle);
		rJointDef.enableLimit = enableLimit;

		//Para criar um motor
		rJointDef.maxMotorTorque = maxMotorTorque; //N*m
		rJointDef.motorSpeed = motorSpeed; //radianos por segundo 
		rJointDef.enableMotor = enableMotor;

		rJoint = (b2RevoluteJoint*)mainBody->GetWorld()->CreateJoint(&rJointDef);

		joints_->push_back(rJoint);
	}

	void GameObject::createPrismaticJoint(GameObject* objectToConnect, glm::vec2 anchor, float magnitude, float angle, bool collideConnect, bool enableLimit, float lowerTranslation, float upperTranslation, bool enableMotor, float maxMotorForce, float motorSpeed) {
		b2Vec2 axis(0, 1);
		//Para definir um outro eixo (em termos de um vetor normalizado)
		axis = Resources::getInstance()->calcComponentsOfVector(magnitude, angle);

		b2Vec2 anchorA = Resources::getInstance()->convertGlm2ToB2Vec2(anchor);

		b2Body* mainBody = this->GetComponent<RigidBody2D>()->GetBody();

		b2PrismaticJointDef pJointDef;
		b2PrismaticJoint* pJoint;

		pJointDef.Initialize(mainBody, objectToConnect->GetComponent<RigidBody2D>()->GetBody(), anchorA, axis);
		pJointDef.collideConnected = collideConnect;

		//Para limitar a translação
		pJointDef.lowerTranslation = lowerTranslation;
		pJointDef.upperTranslation = upperTranslation;
		pJointDef.enableLimit = enableLimit;

		//Para criar um motor
		pJointDef.maxMotorForce = maxMotorForce; //N
		pJointDef.motorSpeed = motorSpeed; //metros por segundo 
		pJointDef.enableMotor = enableMotor;

		pJoint = (b2PrismaticJoint*)mainBody->GetWorld()->CreateJoint(&pJointDef);

		joints_->push_back(pJoint);
	}

	void GameObject::createPulleyJoint(GameObject* objectToConnect, glm::vec2 groundAnchorA, glm::vec2 groundAnchorB, glm::vec2 anchorA, glm::vec2 anchorB, float ratio, bool collideConnected) {
		b2PulleyJointDef puJointDef;
		b2PulleyJoint *puJoint;

		b2Vec2 groundAnchorAA = Resources::getInstance()->convertGlm2ToB2Vec2(groundAnchorA);
		b2Vec2 groundAnchorBB = Resources::getInstance()->convertGlm2ToB2Vec2(groundAnchorB);
		b2Vec2 anchorAA = Resources::getInstance()->convertGlm2ToB2Vec2(anchorA);
		b2Vec2 anchorAB = Resources::getInstance()->convertGlm2ToB2Vec2(anchorB);

		b2Body* mainBody = this->GetComponent<RigidBody2D>()->GetBody();

		puJointDef.Initialize(mainBody, objectToConnect->GetComponent<RigidBody2D>()->GetBody(), groundAnchorAA, groundAnchorBB, anchorAA, anchorAB, ratio);
		puJointDef.collideConnected = collideConnected;

		puJoint = (b2PulleyJoint*)mainBody->GetWorld()->CreateJoint(&puJointDef);

		joints_->push_back(puJoint);
	}

	void GameObject::createGearJoint(GameObject* objectToConnect, b2Joint *jointA, b2Joint *jointB, float ratio) {
		//Criação da junta de engrenagem
		b2GearJointDef gJointDef;
		b2GearJoint* gJoint;

		b2Body* mainBody = this->GetComponent<RigidBody2D>()->GetBody();

		gJointDef.bodyA = mainBody;
		gJointDef.bodyB = objectToConnect->GetComponent<RigidBody2D>()->GetBody();
		gJointDef.joint1 = jointA;
		gJointDef.joint2 = jointB;
		gJointDef.ratio = ratio;
		gJoint = (b2GearJoint*)mainBody->GetWorld()->CreateJoint(&gJointDef);

		joints_->push_back(gJoint);
	}

	void GameObject::createWheelJoint(GameObject* objectToConnect, glm::vec2 anchor, float magnitude, float angle, bool enableMotor, float maxMotorTorque, float motorSpeed, float dampingRatio) {
		//Criação das juntas de rodas
		b2WheelJointDef jd;
		b2WheelJoint *wJoint;

		b2Vec2 axis(0, 1);
		//Para definir um outro eixo (em termos de um vetor normalizado)
		axis = Resources::getInstance()->calcComponentsOfVector(magnitude, angle);

		b2Vec2 anchorA = Resources::getInstance()->convertGlm2ToB2Vec2(anchor);

		b2Body* mainBody = this->GetComponent<RigidBody2D>()->GetBody();

		jd.Initialize(mainBody, objectToConnect->GetComponent<RigidBody2D>()->GetBody(), anchorA, axis);
		jd.motorSpeed = motorSpeed;
		jd.maxMotorTorque = maxMotorTorque;
		jd.enableMotor = enableMotor;
		jd.dampingRatio = dampingRatio;
		wJoint = (b2WheelJoint*)mainBody->GetWorld()->CreateJoint(&jd);

		joints_->push_back(wJoint);
	}

	void GameObject::ApplyForce(int force, int angle, float posX, float posY) {
		b2Vec2 vetorForca;
		vetorForca = Resources::getInstance()->calcComponentsOfVector(force, angle);

		b2Vec2 pontoLocal, pontoGlobal;
		pontoLocal.x = posX;
		pontoLocal.y = posY;
		pontoGlobal = GetComponent<RigidBody2D>()->GetBody()->GetWorldPoint(pontoLocal);
		GetComponent<RigidBody2D>()->GetBody()->ApplyForce(vetorForca, pontoGlobal, true);
	}

	void GameObject::ApplyForceToCenter(int force, int angle) {
		b2Vec2 vetorForca;
		vetorForca = Resources::getInstance()->calcComponentsOfVector(force, angle);
		GetComponent<RigidBody2D>()->GetBody()->ApplyForceToCenter(vetorForca, true);
	}

	void GameObject::ApplyLinearImpulse(int force, int angle, float posX, float posY) {
		b2Vec2 vetorForca;
		vetorForca = Resources::getInstance()->calcComponentsOfVector(force, angle);

		b2Vec2 pontoLocal, pontoGlobal;
		pontoLocal.x = posX;
		pontoLocal.y = posY;
		pontoGlobal = GetComponent<RigidBody2D>()->GetBody()->GetWorldPoint(pontoLocal);
		GetComponent<RigidBody2D>()->GetBody()->ApplyLinearImpulse(vetorForca, pontoGlobal, true);
	}
}