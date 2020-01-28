#pragma once

#include "SFML/Graphics.hpp"

#include <memory>
#include <optional>

class IScene;

class Game final
{
public:
	~Game() = default;

	Game(const Game&) = delete;
	Game(Game&&) noexcept = delete;
	
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) noexcept = delete;

	static Game& instance();

	[[nodiscard]] const sf::RenderWindow& window() const noexcept;

	void set_new_scene(std::unique_ptr<IScene> new_scene);
	void process_pending_scene();
	
	void main_loop();

private:
	Game();
	void internal_main_loop();

	sf::RenderWindow window_;
	
	std::unique_ptr<IScene> current_scene_;
	std::optional<std::unique_ptr<IScene>> pending_scene_;
};