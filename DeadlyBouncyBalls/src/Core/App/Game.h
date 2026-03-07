#ifndef GAME_H
#define GAME_H

#include "Core/Assets/GameAssets.h"  
#include "Core/Rendering/Renderer.h"
#include "Core/Systems/Input/InputSystem.h"
#include "Screens/Screen.h"

class Game
{
	public:
		Game();

		void run();

		template<typename ScreenType, typename... Arguments>
		void switchScreen(Arguments&&... arguments);

		const GameAssets& getAssets() const;
		Renderer& getRenderer();
		const InputSystem& getInputSystem() const;

	private:
		Renderer renderer;
		GameAssets assets;
		InputSystem inputSystem;

		std::unique_ptr<Screen> currentScreen;
};

#include "Core/App/Game.inl"
#endif // !GAME_H

