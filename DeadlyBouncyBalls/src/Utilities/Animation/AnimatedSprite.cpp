#include "Utilities/Animation/AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(
	const sf::Texture& texture, 
	int rowIndex,
	const sf::Vector2i& frameSize, 
	int frameCount, 
	float frameDuration,
	bool isLooping) :
	sprite(texture),
	rowIndex(rowIndex),
	frameSize(frameSize),
	frameCount(frameCount),
	currentFrame(0),
	frameDuration(frameDuration),
	elapsedTime(0.f),
	isPlaying(true),
	isLooping(isLooping)
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
			if (!isLooping)
				isPlaying = false;
		}

		updateTextureRect();
	}
}

void AnimatedSprite::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position);
}

void AnimatedSprite::setScale(const sf::Vector2f& scale)
{
	sprite.setScale(scale);
}

void AnimatedSprite::setOrigin(const sf::Vector2f& origin)
{
	sprite.setOrigin(origin);
}

const sf::Vector2f& AnimatedSprite::getPosition() const
{
	return sprite.getPosition();
}

sf::FloatRect AnimatedSprite::getLocalBounds() const
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
	sprite.setTextureRect(sf::IntRect(
		{ static_cast<int>(currentFrame * frameSize.x), 
		  static_cast<int>(rowIndex * frameSize.y) },
		{ frameSize.x, frameSize.y }
	));
}

void AnimatedSprite::draw(
	sf::RenderTarget& target,
	sf::RenderStates states) const
{
	target.draw(sprite, states);
}