#pragma once

#include "scene.h"

class MainScene : public IScene
{
public:
	MainScene();
	~MainScene() override = default;

	void process_event(const sf::Event& event) override;
	void update(float delta_time) override;
	void render(sf::RenderWindow& target) override;
};
