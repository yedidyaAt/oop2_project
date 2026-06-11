#include "Game.h"
#include "DisplaySettings.h"
#include "KeyboardStrategy.h"
#include "AIStrategy.h"

#include "Wall.h"

#include <iostream>

Game::Game() :
	m_window(sf::VideoMode(sf::Vector2u{ display::WINDOW_WIDTH,display::WINDOW_HIEGHT }), "FACK FACE"),
	m_car(std::make_unique<KeyboardStrategy>()),
	m_carAI(std::make_unique<AIStrategy>()),
	m_frameCount(0),
	m_timeAccumulated(0)
{
	m_window.setFramerateLimit(60);
}

void Game::run()
{
	m_clock.restart();
	sf::Texture t;
	
	if (!t.loadFromFile("fack.png"))
	{
		throw std::runtime_error("not found png");
	}

	Wall wallObj(t,{0.f,0.f});

	while (m_window.isOpen())
	{
		m_timeLeft = m_clock.restart().asSeconds();

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

		m_car.update(m_timeLeft);
		m_carAI.update(m_timeLeft);

		m_window.clear();
		m_window.draw(wallObj);
		m_window.draw(m_car);
		m_window.draw(m_carAI);
		m_window.display();
	}

}

void Game::handle(sf::Event::Closed& closed)
{
	m_window.close();
}

