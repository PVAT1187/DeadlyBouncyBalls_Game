#ifndef AIMING_SYSTEM_H
#define AIMING_SYSTEM_H

class Player;
struct Input;

class AimingSystem
{
	public:
		void apply(Player& player,
			const Input& input,
			float deltaTime);

	private:
		void update(Player& player, float deltaTime);
};

#endif // !AIMING_SYSTEM_H