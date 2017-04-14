#define RAND_MAX 900
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <sstream>
//#include <Vector2.hpp>
using namespace sf;
using namespace std;

int main()
{
    Vector2<int> mouse_Position;
    Vector2<float> bullet_Position;
    Vector2<float> shape_Position;
    Vector2<float> target_Position;
    Vector2<float> ufo_bullet_Position;
    int m = 1, fire = 0, win = 0, time = 0, death = 0, phase = 0;
    RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
    sf::Font font;
    Texture ship;
    ship.loadFromFile("spaceship2.jpg", IntRect(0, 0, 215, 215));
    Texture blast;
    blast.loadFromFile("blast.jpg", IntRect(0, 0, 151, 151));
    Texture ufo;
    ufo.loadFromFile("ufo.jpg", IntRect(0, 0, 400, 400));
	font.loadFromFile("arial.ttf");
    Text text("Score: %d", font, win);
    text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
	text.setPosition(500, 30);
    RectangleShape shape(Vector2f(30,30));
    shape.rotate(90);
    CircleShape bullet(10.f);
    CircleShape ufo_bullet(10.f);
    RectangleShape target(Vector2f(40,40));
    shape.setPosition(30, 450);
    bullet.setPosition(0,0);
    ufo_bullet.setPosition(0,0);
    target.setPosition(900, 300);
    shape.setTexture(&ship);
    bullet.setTexture(&blast);
    ufo_bullet.setTexture(&blast);
    target.setTexture(&ufo);
    srand(5);
    window.setMouseCursorVisible(0);
    
    Text game_over("Game over. Press R to retry.", font);
    game_over.setCharacterSize(30);
	game_over.setStyle(sf::Text::Bold);
	game_over.setColor(sf::Color::Red);
	game_over.setPosition(500, 300);
    
    std::ostringstream playerScoreString;    // объявили переменную
	playerScoreString << win;		//занесли в нее число очков, то есть формируем строку
	text.setString("Score:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
	text.setPosition(500, 100);//задаем позицию текста, отступая от центра камеры

    while (window.isOpen())
    {
		mouse_Position = sf::Mouse::getPosition();
		ufo_bullet_Position = ufo_bullet.getPosition();
		shape.setPosition(mouse_Position.x, mouse_Position.y);
		target_Position = target.getPosition();
		bullet_Position = bullet.getPosition();
		if (bullet_Position.x >= 1000) fire = 0;
		if (ufo_bullet_Position.x <= 0) 
		{	
			ufo_bullet.setPosition(target_Position.x, target_Position.y);
			phase = rand();
		}
		//std::cout<<rand()%900<<"\n";
		
		Event event;
		if((ufo_bullet_Position.y >= (mouse_Position.y - 10))&&(abs(ufo_bullet_Position.x - mouse_Position.x) < 10)&&(ufo_bullet_Position.y <= (mouse_Position.y + 10))) 
		{
			death = 1;
		}
		if((bullet_Position.y >= (target_Position.y - 10))&&(abs(bullet_Position.x - target_Position.x) < 10)&&(bullet_Position.y <= (target_Position.y + 30))) 
		{
			win++;
			target.setPosition(target_Position.x,50 + rand()%500);
		}	
		//if (m >= 1000)
		//{
		//	shape.setPosition(0, 0);
		//	m = 0;
		//	fire = 0;
		//	bullet.setPosition(0, 0);
		//}
		//shape.move(0, 1);
		ufo_bullet.move(-3, sin((ufo_bullet_Position.x + phase)/100));
		target.move(0, sin(time/100));
		if(fire == 1) bullet.move(5, 0);
        while (window.pollEvent(event))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if(fire == 0)
				{
					fire = 1;
					bullet_Position = shape.getPosition();
					bullet.setPosition(bullet_Position.x, bullet_Position.y);
				}
			}
            if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Space))
			{
				if(fire == 0)
				{
					fire = 1;
					bullet_Position = shape.getPosition();
					bullet.setPosition(bullet_Position.x, bullet_Position.y);
				}	
			}
			if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::R) && (death == 1))
			{
				death = 0; 					
			}
			if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::W)) shape.move(0, -10);	
			if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::S)) shape.move(0, 10);	
			if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::D)) shape.move(10, 0);	
			if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::A)) shape.move(-10, 0);	
            if (event.type == Event::Closed)
                window.close();
        }
		time ++;
		
        window.clear();
			
		if(death == 0)	
		{	
			if(fire == 1) window.draw(bullet);
			window.draw(text);
			window.draw(shape);
			window.draw(target);
			window.draw(ufo_bullet);
		}	
        else window.draw(game_over);
        window.display();
    }

    return 0;
}