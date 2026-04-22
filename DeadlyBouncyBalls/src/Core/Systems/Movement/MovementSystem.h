#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

class Player;
struct Input;

class MovementSystem
{
	public:
		void apply(Player& player,
			const Input& Input,
			float deltaTime);
};

#endif // ! MOVEMENT_SYSTEM_H

