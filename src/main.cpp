#include<iostream>

#include "Game.h"
#include "ResourceManager.h"

int main() try{
  ResourceManager::getInstance().load();
  Game().run();

}
catch (const std::exception& e)
{
  std::cout << e.what() << std::endl;
}
