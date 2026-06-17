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

struct StarCollected
{
	std::size_t starIndex;
};

#endif // !GAME_EVENTS_h

