ifndef CCX
  CCX = g++
endif

minefield: Mine.cpp Minefield.cpp Object.cpp ObjectManager.cpp Random.cpp 
	$(CCX) -o minefield -g -std=c++11 Mine.cpp Minefield.cpp Object.cpp ObjectManager.cpp Random.cpp -I. -lpthread  -Wall
