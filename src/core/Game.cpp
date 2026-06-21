#include "Game.h"

#include "KeyboardStrategy.h"
#include "AIStrategy.h"

#include "DisplaySettings.h"
#include "ResourceManager.h"
#include "Factory.h"
#include "ObjectSizes.h"

#include <iostream>


#include "LevelBuilder.h"


Game::Game() :
	m_window(sf::VideoMode(sf::Vector2u{ display::WINDOW_WIDTH,display::WINDOW_HIEGHT }), "FACK FACE"),
	m_timeLeft(0.f),
	m_frameCount(0),
	m_timeAccumulated(0),
	m_levlelMangaer(m_window,std::move(LevelBuilder().buildLevel("resources/levels/level_01.json")))
{
	m_window.setFramerateLimit(60);

}

void Game::run()
{

	m_levlelMangaer.run();


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

		m_window.clear(roudColor);

		m_window.display();
	}

}

void Game::handle(sf::Event::Closed& /*closed*/)
{
	m_window.close();
}

