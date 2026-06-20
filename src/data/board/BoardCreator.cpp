#include "BoardCreator.h"

#include "Loader.h"
#include "LevelData.h"
#include "Factory.h"

Board BoardCreator::getBoard(const std::string& path)
{
	LevelData leveldata = Loader().getData(path);
	Board board;

	for (const auto& objDes : leveldata.m_objects)
	{
		board.m_staticObjects.push_back(factory::create(objDes));
	}

	return board;
}