#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>

class AnimatedSprite : public sf::Drawable
{
	public:
		AnimatedSprite(const sf::Texture& texture, 
			int rowIndex,
			const sf::Vector2i& frameSize, 
			int frameCount, 
			float frameDuration,
			bool isLooping = true);

		void update(float deltaTime);

		void setPosition(const sf::Vector2f& position);
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
		bool isLooping;

		void updateTextureRect();

		void draw(sf::RenderTarget& target,
			sf::RenderStates states) const override;
};

#endif // !ANIMATED_SPRITE_H

