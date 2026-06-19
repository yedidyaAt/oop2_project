#include "LevelManager.h"

#include <utility>

#include "Collision.h"



#include <iostream>


LevelManager::LevelManager(sf::RenderWindow& window,
	std::vector<std::unique_ptr<GameObject>> objects,
	std::unique_ptr<GameObject> car) :
	m_window(window),
	m_objects(std::move(objects)),
  m_car(std::move(car))
{

}


void LevelManager::run()
{
	sf::Clock clock;

	while (m_window.isOpen())
	{
		sf::Time time = clock.restart();

		while (const auto event = m_window.pollEvent())
		{
			event->visit([&](auto event) {handle(event);});
		}

		update(time);

		m_window.clear(sf::Color::White);
		draw();
		m_window.display();
	}

}

void LevelManager::update(sf::Time time)
{
	m_car->update(time);

	checkConflict();
}

void LevelManager::checkConflict()
{
	for (const auto& obj : m_objects)
	{
		if (collision::overlaps(m_car->getCorners(), obj->getCorners()))
			std::cout << "got you son of a bitch" << std::endl;
	}
}

void LevelManager::draw()
{

	//sf::RectangleShape objS, carS;
	//for (const auto& obj : m_objects)
	//{
	//	sf::FloatRect objF(obj->getGlobalBounds());
	//	sf::FloatRect carF(m_car->getGlobalBounds());
	//
	//	objS.setFillColor(sf::Color::Black);
	//	objS.setOutlineColor(sf::Color::Blue);
	//	objS.setPosition(objF.position);
	//	objS.setSize(objF.size);
	//
	//	carS.setFillColor(sf::Color::Yellow);
	//	carS.setOutlineColor(sf::Color::Blue);
	//	carS.setPosition(carF.position);
	//	carS.setSize(carF.size);
	//
	//	m_window.draw(objS);
	//	m_window.draw(carS);
	//}

	// darw objects
	for (const auto& obj : m_objects)
	{
		m_window.draw(*obj);
	}

	// draw car
	m_window.draw(*m_car);
}

void LevelManager::handle(sf::Event::Closed& closed)
{
	m_window.close();
}
