#include<iostream>

#include "Game.h"

int main() try{
 
  Game().run();

}
catch (const std::exception& e)
{
  std::cout << e.what() << std::endl;
}
