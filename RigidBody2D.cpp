#include "RigidBody2D.h"



RedMagic::RigidBody2D::RigidBody2D()
{
}

RedMagic::RigidBody2D::RigidBody2D(b2World* world, b2BodyType bodyType, Transform* transform) {
	fixtures_ = new vector<b2Fixture*>;
	transform_ = transform;

	b2BodyDef bodydef;
	bodydef.type = bodyType;
	bodydef.position.Set(transform_->position_.x, transform_->position_.y);
	body_ = world->CreateBody(&bodydef);

	mass_ = 5.0f;
	density_ = mass_ / (transform_->GetHeight() * transform_->GetWidth());
	friction_ = 0.5f;
	restitution_ = 0.5f;
	body_->SetUserData(this);
}

RedMagic::RigidBody2D::~RigidBody2D()
{
}

void RedMagic::RigidBody2D::Cleanup() {
	//delete body
	//delete fixtures
}

void RedMagic::RigidBody2D::Update(double dt) {
	//atualizar a informação fisica para o transform do game object
	transform_->position_.x = body_->GetPosition().x;
	transform_->position_.y = body_->GetPosition().y;
}

void RedMagic::RigidBody2D::Initialize(b2World* world, b2BodyType bodyType, Transform* transform) {
	fixtures_ = new vector<b2Fixture*>;
	transform_ = transform;

	b2BodyDef bodydef;
	bodydef.type = bodyType;
	bodydef.position.Set(transform_->position_.x, transform_->position_.y);
	body_ = world->CreateBody(&bodydef);

	density_ = 10.0f;
	mass_ = 3.0f;
	friction_ = 0.3f;
	restitution_ = 0.2f;
}

void RedMagic::RigidBody2D::SetBoxCollider(float width, float height) {
	b2Fixture *fixture;

	b2PolygonShape shape;
	shape.SetAsBox(width /2 , height / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = mass_ / (width*height);
	fixtureDef.friction = friction_;
	fixtureDef.restitution = restitution_;

	fixture = body_->CreateFixture(&fixtureDef);
	
	//replace fixture
	body_->DestroyFixture(fixtures_->back());
	fixtures_->pop_back();

	fixtures_->push_back(fixture);
}

void RedMagic::RigidBody2D::SetPolygonCollider(glm::vec2 *points) {
	b2Fixture *fixture;

	b2PolygonShape shape;

	b2Vec2 *p;
	p = new b2Vec2[points->length()];

	for (int i = 0; i < points->length(); i++) {
		p[i].x = points[i].x;
		p[i].y = points[i].y;
	}

	shape.Set(p, p->Length());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = density_;
	fixtureDef.friction = friction_;
	fixtureDef.restitution = restitution_;
	fixture = body_->CreateFixture(&fixtureDef);

	//replace fixture
	body_->DestroyFixture(fixtures_->back());
	fixtures_->pop_back();

	fixtures_->push_back(fixture);
}

void RedMagic::RigidBody2D::SetCircleCollider(float radius) {
	b2Fixture *fixture;

	b2CircleShape shape;
	//shape.m_p.Set(position.x, position.y); ???
	shape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = density_;
	fixtureDef.friction = friction_;
	fixtureDef.restitution = restitution_;
	fixture = body_->CreateFixture(&fixtureDef);
	
	//replace fixture
	body_->DestroyFixture(fixtures_->back());
	fixtures_->pop_back();

	fixtures_->push_back(fixture);
}

void RedMagic::RigidBody2D::AddBoxCollider(float width, float height) {
	b2Fixture *fixture;

	b2PolygonShape shape;
	shape.SetAsBox(width / 2, height / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = mass_ / (width*height);
	fixtureDef.friction = friction_;
	fixtureDef.restitution = restitution_;

	fixture = body_->CreateFixture(&fixtureDef);

	fixtures_->push_back(fixture);
}

void RedMagic::RigidBody2D::AddPolygonCollider(glm::vec2 *points) {
	b2Fixture *fixture;

	b2PolygonShape shape;

	//b2Vec2 *p = Resources::getInstance()->convertGlm2ToB2Vec2(points);

	//shape.Set(p, p->Length());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = density_;
	fixtureDef.friction = friction_;
	fixtureDef.restitution = restitution_;
	fixture = body_->CreateFixture(&fixtureDef);

	fixtures_->push_back(fixture);
}

void RedMagic::RigidBody2D::AddCircleCollider(float radius) {
	b2Fixture *fixture;

	b2CircleShape shape;
	//shape.m_p.Set(position.x, position.y); ???
	shape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = density_;
	fixtureDef.friction = friction_;
	fixtureDef.restitution = restitution_;
	fixture = body_->CreateFixture(&fixtureDef);

	fixtures_->push_back(fixture);
}