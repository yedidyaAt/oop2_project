#pragma once

#include <vector>
#include <memory>

#include "GameObject.h"

struct Board
{
	std::vector<std::unique_ptr<GameObject>> m_staticObjects;
	std::unique_ptr<GameObject> m_car;

};