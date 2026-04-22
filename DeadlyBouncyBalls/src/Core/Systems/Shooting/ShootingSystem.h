#ifndef SHOOTING_SYSTEM_H
#define SHOOTING_SYSTEM_H

class Player;
class BulletManager;
class ShootingComponent;
struct Input;

class ShootingSystem 
{
	public:
		void apply(Player& player,
			BulletManager& bulletManager,
			const Input& input,
			float deltaTime);
};

#endif // !SHOOTING_SYSTEM_H

