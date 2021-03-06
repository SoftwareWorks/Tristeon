﻿#include "Application.h"
#include "Scenes/SceneManager.h"

namespace Tristeon
{
	Application::~Application()
	{
		//Cleanup
#ifdef TRISTEON_EDITOR
		editor.reset();
#endif
		engine.reset();
	}

	void Application::init()
	{
		//Init engine
		engine = std::make_unique<Core::Engine>();
		engine->init();

		//Init editor
#ifdef TRISTEON_EDITOR
		editor = std::make_unique<Editor::TristeonEditor>();
		editor->init(engine.get());
#endif

		//Auto start game if we are running in release mode
#ifndef TRISTEON_EDITOR
		Scenes::SceneManager::loadScene(0);
		engine->startGame();
#endif

		engine->run();

	}
}
