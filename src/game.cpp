#include "game.h"

#include "mainscene.h"

#include <cassert>
#include <atomic>

Game::Game() :
	window_{ sf::VideoMode(600, 800), "SFML works!" }
{
	window_.setFramerateLimit(60);
}

Game& Game::instance()
{
	static Game game{};
	return game;
}

const sf::RenderWindow& Game::window() const noexcept
{
	return window_;
}

void Game::set_new_scene(std::unique_ptr<IScene> new_scene)
{
	pending_scene_ = std::move(new_scene);
}

void Game::process_pending_scene()
{
	if (pending_scene_)
	{
		current_scene_ = std::move(pending_scene_.value());
		pending_scene_ = std::nullopt;
	}
}

void Game::main_loop()
{
	// Making sure main_loop is called only once
	// std::call_once won't work here, since we are not returning from the main_loop until end.	
	static std::atomic_bool called{ false };
	if (!called.exchange(true))
	{
		internal_main_loop();
	}
	else
	{
		throw std::runtime_error{ "main_loop called more than once" };	
	}
}

void Game::internal_main_loop()
{
	set_new_scene(std::make_unique<MainScene>());
	
	sf::Clock delta_clock;
	while (window_.isOpen())
	{
		process_pending_scene();
		
		const auto delta_time = delta_clock.restart();

		sf::Event event{};
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window_.close();
			}

			if (current_scene_)
			{
				current_scene_->process_event(event);
			}
		}

		if (current_scene_)
		{
			current_scene_->update(delta_time.asSeconds());
			current_scene_->render(window_);
		}
	}
}