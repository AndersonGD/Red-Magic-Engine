#ifndef REDMAGIC_PART_H
#define REDMAGIC_PART_H

#include <string>
using namespace std;

namespace RedMagic {

	class GameObject;

	class Part
	{
	private:
		bool is_active_;
		GameObject* gameObject_;
		string name_;
	public:
		Part() { is_active_ = true; }
		~Part() {}

		bool is_active() { return is_active_; }
		void set_is_active(bool is_active) { is_active_ = is_active; }
		void SetGameObject(GameObject* game_object) { gameObject_ = game_object; }
		void SetName(string name) { name_ = name; }

		GameObject* GetGameObject() { return gameObject_; }

		virtual void Initialize(){}
		virtual void Cleanup(){}
		virtual void Update(double dt){}
	};

	class Script : public Part {

	};
}
#endif
