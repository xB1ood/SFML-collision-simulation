#include "Simulation.h"

void Simulation::creatureCollision()
{
	if (this->creature.getPosition().x >= this->window->getSize().x - this->creature.getSize().x || this->creature.getPosition().x <= 0.f) {
		
		this->move_creature.x *= -1;

	}
	if (this->creature.getPosition().y >= this->window->getSize().y - this->creature.getSize().y || this->creature.getPosition().y <= 0.f) {
		
		this->move_creature.y *= -1;

	}

	
	
	float mouseXpos = static_cast<float>(sf::Mouse::getPosition(*this->window).x);
	float mouseYpos = static_cast<float>(sf::Mouse::getPosition(*this->window).y);



	bool isColl = false;
	//Checks for collision
	if
		(this->racket.getPosition().x + this->racket.getSize().x >= this->creature.getPosition().x
			&& this->racket.getPosition().x <= this->creature.getPosition().x + this->creature.getSize().x
			&& this->racket.getPosition().y + this->racket.getSize().y >= this->creature.getPosition().y
			&& this->racket.getPosition().y <= this->creature.getPosition().y + this->creature.getSize().y) 
	{
		isColl = true;
	}
		

	//Move creature relatively to the mouse
	if (isColl) {

		if (this->racket.getPosition().x+this->racket.getSize().x <= this->creature.getPosition().x)
			this->creature.setPosition(this->creature.getPosition().x + 1, this->creature.getPosition().y);

		else if(this->racket.getPosition().x >= this->creature.getPosition().x + this->creature.getSize().x)
			this->creature.setPosition(this->creature.getPosition().x - 1, this->creature.getPosition().y);

		if(this->racket.getPosition().y + this->racket.getSize().y <= this->creature.getPosition().y)
			this->creature.setPosition(this->creature.getPosition().x , this->creature.getPosition().y + 1);
		
		else if(this->racket.getPosition().y >= this->creature.getPosition().y + this->creature.getSize().y)
			this->creature.setPosition(this->creature.getPosition().x, this->creature.getPosition().y - 1);
	}

	//Stop racket from entering the area of creature







}

Simulation::Simulation()
{
	this->window->setFramerateLimit(144);
	std::string ans;
	//Ask for skip settings
	std::cout << "Change settings?(Y/N): ";
	std::cin >> ans;
	if (ans == "Y" || ans == "y")
		this->skipSettings = true;

	//Initializing creature, racket and etc.
	if (!this->skipSettings)
		this->initObjects();
	else
		this->settings();




}

Simulation::~Simulation()
{

	delete this->window;


}

bool Simulation::isWindowOpen()
{
	return this->window->isOpen();
}

void Simulation::pullEvents()
{

	while (this->window->pollEvent(this->ev)) {
		
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Key::Escape) {
				this->window->close();
			}
			break;
		}
			



	}



}

void Simulation::update()
{
	//Get some info
	std::cout << "Mouse X: " << sf::Mouse::getPosition(*this->window).x << "\tMouse Y: " << sf::Mouse::getPosition(*this->window).y << std::endl;
	std::cout << "Move_creature(x): " << abs(this->move_creature.x) << " Move_creature(y): " << abs(this->move_creature.y) << std::endl;
	std::cout << "Creature posX: " << this->creature.getPosition().x << "  Creature posY: " << this->creature.getPosition().y << std::endl;
	std::cout << "Racket posX: " << this->racket.getPosition().x << "  Racket posY: " << this->racket.getPosition().y << std::endl;



	//Object actions
	this->creatureMove();
	this->grabRacket();


	

}

void Simulation::initObjects()
{
	//Initialize creature
	this->creature.setFillColor(sf::Color::White);
	this->creature.setSize(sf::Vector2f(100.f, 100.f));
	this->creature.setPosition(400.f - this->creature.getSize().x/2, 300.f - this->creature.getSize().y/2);

	//Initizlize racket
	this->racket.setFillColor(sf::Color::Blue);
	this->racket.setSize(sf::Vector2f(50.f,50.f));
	this->racket.setPosition(static_cast<float>(sf::Mouse::getPosition(*this->window).x-25),static_cast<float>(sf::Mouse::getPosition(*this->window).y-25));

	

}

void Simulation::creatureMove()
{


	//Reduce speed frame by frame to base
	this->reduceCreatureSpeed();


	//Moving creature
	this->creature.move(this->move_creature);


	//Collision
	this->creatureCollision();
	

}

void Simulation::reduceCreatureSpeed()
{
	

	
}

void Simulation::grabRacket()
{

	//Grab racket on center
	this->racket.setPosition(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*this->window).x)-(this->racket.getSize().x/2), static_cast<float>(sf::Mouse::getPosition(*this->window).y) - (this->racket.getSize().y / 2)));

	//Collision with window's borders
	this->racketWindowBorderCollision();

	//Collision with creature
	
	this->RacketCreature_collision();
	




}

void Simulation::racketWindowBorderCollision()
{

	if (this->racket.getPosition().x <= 0.f && this->racket.getPosition().y >= this->video.height - this->racket.getSize().y)
		this->racket.setPosition(0.f, this->video.height - this->racket.getSize().y);
	else if (this->racket.getPosition().x >= this->video.width - this->racket.getSize().x && this->racket.getPosition().y <= 0.f)
		this->racket.setPosition(this->video.width - this->racket.getSize().x, 0.f);
	else if (this->racket.getPosition().x <= 0.f && this->racket.getPosition().y <= 0.f)
		this->racket.setPosition(0.f, 0.f);
	else if (this->racket.getPosition().x >= this->video.width - this->racket.getSize().x && this->racket.getPosition().y >= this->video.height - this->racket.getSize().y)
		this->racket.setPosition(this->video.width - this->racket.getSize().x, this->video.height - this->racket.getSize().y);
	else
	{
		if (this->racket.getPosition().x <= 0.f)
			this->racket.setPosition(0.f, static_cast<float>(sf::Mouse::getPosition(*this->window).y) - (this->racket.getSize().y / 2));
		else if (this->racket.getPosition().x >= this->video.width - this->racket.getSize().x)
			this->racket.setPosition(this->video.width - this->racket.getSize().x, static_cast<float>(sf::Mouse::getPosition(*this->window).y) - (this->racket.getSize().y / 2));


		if (this->racket.getPosition().y <= 0.f)
			this->racket.setPosition(static_cast<float>(sf::Mouse::getPosition(*this->window).x) - (this->racket.getSize().x / 2), 0.f);
		else if (this->racket.getPosition().y >= this->video.height - this->racket.getSize().y)
			this->racket.setPosition(static_cast<float>(sf::Mouse::getPosition(*this->window).x) - (this->racket.getSize().x / 2), this->video.height - this->racket.getSize().y);
	}



}

void Simulation::RacketCreature_collision()
{

	//Left side
	if (this->racket.getPosition().x + this->racket.getSize().x >= this->creature.getPosition().x
		&& this->racket.getPosition().x + this->racket.getSize().x <= this->creature.getPosition().x + (this->creature.getSize().x / 2)
		&& this->racket.getPosition().y >= this->creature.getPosition().y - this->racket.getSize().y
		&& this->racket.getPosition().y + this->racket.getSize().y <= this->creature.getPosition().y + this->creature.getSize().y + this->racket.getSize().y)
		this->racket.setPosition(this->creature.getPosition().x - this->racket.getSize().x, this->racket.getPosition().y);


	//Right side
	else if (this->racket.getPosition().x <= this->creature.getPosition().x + this->creature.getSize().x
		&& this->racket.getPosition().x >= this->creature.getPosition().x + (this->creature.getSize().x / 2)
		&& this->racket.getPosition().y >= this->creature.getPosition().y - this->racket.getSize().y
		&& this->racket.getPosition().y + this->racket.getSize().y <= this->creature.getPosition().y + this->creature.getSize().y + this->racket.getSize().y)
		this->racket.setPosition(this->creature.getPosition().x + this->creature.getSize().x, this->racket.getPosition().y);

	//Upper side
	if (this->racket.getPosition().y + this->racket.getSize().y >= this->creature.getPosition().y
		&& this->racket.getPosition().y + this->racket.getSize().y <= this->creature.getPosition().y + (this->creature.getSize().y / 2)
		&& this->racket.getPosition().x >= this->creature.getPosition().x - this->racket.getSize().x
		&& this->racket.getPosition().x + this->racket.getSize().x <= this->creature.getPosition().x + this->creature.getSize().x + this->racket.getSize().x)
		this->racket.setPosition(this->racket.getPosition().x, this->creature.getPosition().y - this->racket.getSize().y);

	//Down side
	else if (this->racket.getPosition().y <= this->creature.getPosition().y + this->creature.getSize().y
		&& this->racket.getPosition().y >= this->creature.getPosition().y + (this->creature.getSize().y / 2)
		&& this->racket.getPosition().x >= this->creature.getPosition().x - this->racket.getSize().x
		&& this->racket.getPosition().x <= this->creature.getPosition().x + this->creature.getSize().x)
		this->racket.setPosition(this->racket.getPosition().x, this->creature.getPosition().y + this->creature.getSize().y);

}



void Simulation::render()
{
	this->window->clear(sf::Color::Black);
	this->window->draw(this->creature);
	this->window->draw(this->racket);
	this->window->display();
}

void Simulation::settings()
{
	sf::Vector2f size;


	//Creature settings

	std::cout << "Creature size(width,height): " << std::endl;
	std::cin >> size.x >> size.y;
	this->creature.setSize(size);

	//Racket settings
	
	std::cout << "Racket size(width,height): " << std::endl;
	std::cin >> size.x >> size.y;
	this->racket.setSize(size);
	

	this->creature.setFillColor(sf::Color::White);
	this->creature.setPosition(400.f - this->creature.getSize().x / 2, 300.f - this->creature.getSize().y / 2);
	this->racket.setFillColor(sf::Color::Blue);
	this->racket.setPosition(static_cast<float>(sf::Mouse::getPosition(*this->window).x - 25), static_cast<float>(sf::Mouse::getPosition(*this->window).y - 25));
}








