/// <summary>
/// name:Rachael McDdonald
/// @date May 2019
/// program: main code for astroid game


#include "Game.h"
#include <iostream>
#include "MyVector2.h"




/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	//setupFontAndText(); // load font 
	setupSprite(); // load texture
}

///
Game::~Game()
{
}



/// loop for game
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// process main events
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


///what happens when keys are pressed
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// update for game
void Game::update(sf::Time t_deltaTime)
{
	drawLine();

	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// drawing for square and rectangle
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_bernard);
	m_window.draw(m_patricia);
	m_window.draw(m_laser);
	m_window.display();
}

void Game::ProcessMouseReleaseEvents(sf::Event t_mouseEvent)
{
	m_laser.clear();

	if (sf::Mouse::Left == t_mouseEvent.mouseButton.button)
	{


		mouseClick = sf::Vector2f{ static_cast<float>(t_mouseEvent.mouseButton.x),static_cast<float>(t_mouseEvent.mouseButton.y) };
		lineEnd = mouseClick;
		float distanceValue = 0.0f;
		velocityLine();
		m_drawLine = true;

	}
	

}



void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
	
	}


	m_bernard.setPosition(0.0f, 575.0f); //location for sqaure
	m_bernard.setFillColor(sf::Color::Green);
	m_bernard.setSize(sf::Vector2f(800.0f, 50.0f));

	m_patricia.setPosition(375.0f, 525.0f); // location for rectangle
	m_patricia.setFillColor(sf::Color::Red);
	m_patricia.setSize(sf::Vector2f(50.0f, 50.0f));

}

	void Game::velocityLine() //calulations for velocity

	{
		vectorUnit = vectorUnitVector(lineEnd - lineStart);
		velocity = vectorUnit * 3.0f;
		lineEndCurrent = lineStart;

	}

	void Game::drawLine() //fo the line
	{

		if (m_drawLine == true)
		{
			m_laser.clear();

			sf::Vertex lineStartVertex(lineStart, sf::Color::Red);
			m_laser.append(lineStartVertex);

			lineEndCurrent += velocity;
			sf::Vertex lineEnd( lineEndCurrent, sf::Color::Red);
			m_laser.append(lineEnd);

		}

		if (vectorLength(lineEndCurrent - lineEnd) < 4.0f)
		{
			m_drawLine = false;
			m_laser.clear();

		}
	}
	
