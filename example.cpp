//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <windows.h>
#include "SFMLLayout.hpp"

using namespace std;


//int count(int limit, mutex *mtx)
//{
//	sf::Clock clock;
//	for (int lastsec = 0 ; lastsec < limit ; )
//	{
//		if (clock.getElapsedTime().asSeconds() >= lastsec + 1)
//		{
//			lastsec ++;
//			mtx->lock();
//			cout << lastsec << " (" << clock.getElapsedTime().asMilliseconds() << ")" << endl;
//			mtx->unlock();
//
//		}
//	}
//    return 0;
//}




void setSpriteSize(sf::Sprite &sprite, float width, float height)
{
	float old_width = sprite.getGlobalBounds().width;
	float old_height = sprite.getGlobalBounds().height;
	sprite.setScale(width/old_width, height/old_height);
}



int main()
{
	//std::cout << "" << std::endl;

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		sf::Texture texture;
		texture.loadFromFile("C:\\Users\\Ninethousand\\Projects\\Project1\\Debug\\untitled.png");

		sf::Sprite sprite;
		sprite.setTexture(texture);

		/*sprite.setPosition(20,20);
		sprite.setScale(0,0);
		sf::FloatRect r = sprite.getGlobalBounds();
		std::cout << "X:" << r.left << " Y:" << r.top << std::endl;
		window.draw(sprite);*/
		
		SFML_LAYOUT::SFMLBase b;
		b.set_background(&sprite);
		b.set_background_mode(SFML_LAYOUT::BACKGROUND::repeat, SFML_LAYOUT::BACKGROUND::repeat);
		b.set_background_alignment(LAYOUT::ALIGNMENT::center, LAYOUT::ALIGNMENT::center);
		b.drawBackground(&window, 20, 20, 400, 400);

		window.display();
	}

}


	/*sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		sf::Texture texture;
		texture.loadFromFile("C:\\Users\\Ninethousand\\Projects\\Project1\\Debug\\bitmap.png");

		sf::Sprite sprite;
		sprite.setTexture(texture);
		setSpriteSize(sprite, 400, 400);
		window.draw(sprite);

		window.display();
	}*/
