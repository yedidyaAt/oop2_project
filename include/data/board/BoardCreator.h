#pragma once

#include <string>

#include "Board.h"


class BoardCreator
{
public:
	BoardCreator() {};

	Board getBoard(const std::string& path);

private:

};
