#include "Utilities/Animation/AnimatedSprite.h"

using namespace sf;

AnimatedSprite::AnimatedSprite(const Texture& texture, int rowIndex,
	const Vector2i& frameSize, int frameCount, float frameDuration) :
	sprite(texture),
	rowIndex(rowIndex),
	frameSize(frameSize),
	frameCount(frameCount),
	currentFrame(0),
	frameDuration(frameDuration),
	elapsedTime(0.f),
	isPlaying(false)
{
	updateTextureRect();
}

void AnimatedSprite::update(float deltaTime)
{
	if (!isPlaying || frameCount <= 1)
		return;

	elapsedTime += deltaTime;
	while (elapsedTime >= frameDuration)
	{
		elapsedTime -= frameDuration;

		++currentFrame;
		if (currentFrame >= frameCount)
		{
			currentFrame = 0;
			isPlaying = false;
		}

		updateTextureRect();
	}
}

void AnimatedSprite::setPosition(const Vector2f& position)
{
	sprite.setPosition(position);
}

void AnimatedSprite::setRotation(float angle)
{
	sprite.setRotation(degrees(angle));
}

void AnimatedSprite::setScale(const Vector2f& scale)
{
	sprite.setScale(scale);
}

void AnimatedSprite::setOrigin(const Vector2f& origin)
{
	sprite.setOrigin(origin);
}

const Vector2f& AnimatedSprite::getPosition() const
{
	return sprite.getPosition();
}

FloatRect AnimatedSprite::getLocalBounds() const
{
	return sprite.getLocalBounds();
}

void AnimatedSprite::reset()
{
	currentFrame = 0;
	elapsedTime = 0.f;
	isPlaying = true;
	updateTextureRect();
}

void AnimatedSprite::updateTextureRect()
{
	sprite.setTextureRect(IntRect(
		{ static_cast<int>(currentFrame * frameSize.x), 
		  static_cast<int>(rowIndex * frameSize.y) },
		{ frameSize.x, frameSize.y }
	));
}

void AnimatedSprite::draw(RenderTarget& target,
	RenderStates states) const
{
	target.draw(sprite, states);
}