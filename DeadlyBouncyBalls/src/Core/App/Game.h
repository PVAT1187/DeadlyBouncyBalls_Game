#ifndef GAME_H
#define GAME_H

#include "Core/Assets/GameAssets.h"  
#include "Core/Rendering/Renderer.h"
#include "Core/Input/InputCollector/InputCollector.h"
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
		const InputCollector& getInputCollector() const;

	private:
		Renderer renderer;
		GameAssets assets;
		InputCollector inputCollector;

		std::unique_ptr<Screen> currentScreen;
};

#include "Core/App/Game.inl"
#endif // !GAME_H

