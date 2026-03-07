#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Drawable
{
	public:
		AnimatedSprite(const sf::Texture& texture, int rowIndex,
			const sf::Vector2i& frameSize, 
			int frameCount, float frameDuration);

		void update(float deltaTime);

		void setPosition(const sf::Vector2f& position);
		void setRotation(float angle);
		void setScale(const sf::Vector2f& scale); 
		void setOrigin(const sf::Vector2f& origin);

		const sf::Vector2f& getPosition() const;
		sf::FloatRect getLocalBounds() const;

		void reset();
		
	private:
		sf::Sprite sprite;

		int rowIndex;

		sf::Vector2i frameSize;
		int frameCount;
		int currentFrame;

		float frameDuration;
		float elapsedTime;

		bool isPlaying;

		void updateTextureRect();

		void draw(sf::RenderTarget& target,
			sf::RenderStates states) const override;
};

#endif // !ANIMATED_SPRITE_H

