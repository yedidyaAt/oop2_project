#include "Game.h"

#include "KeyboardStrategy.h"
#include "AIStrategy.h"

#include "DisplaySettings.h"
#include "ResourceManager.h"
#include "Factory.h"
#include "ObjectSizes.h"

#include <iostream>


#include "LevelManager.h"


Game::Game() :
	m_window(sf::VideoMode(sf::Vector2u{ display::WINDOW_WIDTH,display::WINDOW_HIEGHT }), "FACK FACE"),
	m_timeLeft(0.f),
	m_frameCount(0),
	m_timeAccumulated(0),
	m_car(std::make_unique<Car>(
		ResourceManager::getInstance().getTexture(Objects::PLAYER_CAR),
		sf::Vector2f{},
		objectSizes::playerCar::WIDTH,
		sf::degrees(90),
		std::make_unique<KeyboardStrategy>())
	)
{
	m_window.setFramerateLimit(60);

	LevelData lD = m_loader.getData("resources/levels/level_01.json");

	for (const auto& objData : lD.m_objects)
	{
		m_objects.emplace_back(factory::create(objData));
	}

}

void Game::run()
{

	LevelManager{ m_window, std::move(m_objects), std::move(m_car) }.run();


	m_clock.restart();

	sf::Color roudColor(40, 40, 40);

	while (m_window.isOpen())
	{
		sf::Time time = m_clock.restart();

		m_timeLeft = time.asSeconds();

		m_timeAccumulated += m_timeLeft;
		m_frameCount++;

		if (m_timeAccumulated > 1)
		{
			std::cout <<  "FPS: " << m_frameCount << std::endl;
			m_timeAccumulated = 0;
			m_frameCount			= 0;
		}

		while (const auto event = m_window.pollEvent())
		{
			event->visit([&](auto event) {handle(event);});
		}

		m_window.clear(sf::Color::White);

		m_window.display();
	}

}

void Game::handle(sf::Event::Closed& /*closed*/)
{
	m_window.close();
}

