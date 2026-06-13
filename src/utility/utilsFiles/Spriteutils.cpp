#include "Spriteutils.h"

void spriteutils::fitToSize(sf::Sprite& s, const sf::Vector2f& size)
{
	s.setScale(sf::Vector2f{
		size.x / static_cast<float>(s.getTexture().getSize().x),
		size.y / static_cast<float>(s.getTexture().getSize().y)
	});
}
