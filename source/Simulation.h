#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <random>


class Simulation
{
private:
	//Variables
	bool skipSettings = false;
	
	

	sf::VideoMode video{ 800,600 };
	sf::RenderWindow* window = new sf::RenderWindow(video, "Simulation", sf::Style::Close | sf::Style::Titlebar);
	sf::Event ev;

	//Objects
	sf::RectangleShape creature;
	sf::Vector2f move_creature{0.f,0.f};

	sf::RectangleShape racket;
	



	void creatureCollision();

	//Moving
	void creatureMove();
	void reduceCreatureSpeed();
	void grabRacket();
	void racketWindowBorderCollision();
	void RacketCreature_collision();

public:
	//Intialize some variables
	Simulation();

	//Clear memory(pointers)
	~Simulation();

	//Is window open or not 
	bool isWindowOpen();
	
	//Function that pulling and cheking some events in variable (ev) 
	void pullEvents();

	//Update some data (as example moving positions of enemy or moving some objects)
	void update();

	//Initialization
	void initObjects();

	//Render(draw and display) some object, as example (window.draw(enemy))
	void render();

	//Ask for settings
	void settings();




};

