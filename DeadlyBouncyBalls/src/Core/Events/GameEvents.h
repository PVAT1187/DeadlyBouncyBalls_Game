#ifndef GAME_EVENTS_H
#define GAME_EVENTS_H

#include <cstddef>

struct PlayerHit {};

struct BallHit 
{
	std::size_t ballIndex;
};

struct BulletHit 
{
	std::size_t bulletIndex;
};

#endif // !GAME_EVENTS_h

