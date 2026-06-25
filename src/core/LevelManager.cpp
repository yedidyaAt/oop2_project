#include "LevelManager.h"

#include <utility>

#include "Collision.h"
#include "ParkingRules.h"
#include "SoundManager.h"
#include "Sounds.h"
#include "Musics.h"


#include <iostream>


LevelManager::LevelManager(sf::RenderWindow& window, LevelData levelData) :
	m_window(window),
	m_car(std::move(levelData.m_car)),
	m_target(std::move(levelData.m_target)),
	m_blocksObj(std::move(levelData.m_blocksObj)),
	m_decalsObj(std::move(levelData.m_decalsObj)),
	m_state(LevelState::Playing),
	m_shapeMSG({200.f,200.f})
{
	//SoundManager::getInstance().playMusic(Musics::OPENING);
}

 
void LevelManager::run()
{
	sf::Color roudColor(40, 40, 40);

	sf::Clock clock;

	while (m_window.isOpen())
	{
		sf::Time time = clock.restart();

		while (const auto event = m_window.pollEvent())
		{
			event->visit([&](auto event) {handle(event);});
		}

		if(m_state == LevelState::Playing)
			update(time);

		m_window.clear(roudColor);
		draw();
		m_window.display();
	}

}

void LevelManager::update(sf::Time time)
{
	m_car->update(time);

	checkConflict();
	checkParking();
}

void LevelManager::checkConflict()
{
	for (const auto& obj : m_blocksObj)
	{
		if (collision::overlaps(m_car->getCorners(), obj->getCorners()))
		{
			SoundManager::getInstance().playEffectSound(Sounds::COLLISION);
			std::cout << "got you son of a bitch" << std::endl;
			m_shapeMSG.setFillColor(sf::Color::Blue);
			m_state = LevelState::LOST;
		}
	}
}
		

void LevelManager::checkParking()
{
	if (m_car->isStand() && parkingRules::isParked(*m_car, *m_target))
	{
		SoundManager::getInstance().playEffectSound(Sounds::END_OF_STAGE);
		std::cout << "his parking mader facker" << std::endl;
		m_shapeMSG.setFillColor(sf::Color::Green);
		m_state = LevelState::Won;
	}

}

void LevelManager::draw()
{

	//sf::RectangleShape objS, carS;
	//for (const auto& obj : m_blocksObj)
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
	for (const auto& obj : m_decalsObj)
	{
		m_window.draw(*obj);
	}

	for (const auto& obj : m_blocksObj)
	{
		m_window.draw(*obj);
	}

	// draw the parking spot
	m_window.draw(*m_target);

	// draw car
	m_window.draw(*m_car);

	if (m_state != LevelState::Playing)
		m_window.draw(m_shapeMSG);
}

void LevelManager::handle(sf::Event::Closed& /*closed*/)
{
	m_window.close();
}
