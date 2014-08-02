#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SFMLLayout.hpp"


/*
- Incomplete declarations for wrappers. More about this later.
*/
void change_eye_wrapper(std::map<std::string, std::string> &argMap);
void show_dot_wrapper(std::map<std::string, std::string> &argMap);
void close_window_wrapper(std::map<std::string, std::string> &argMap);


/*
- This class will store and manage all layout elements and sprites.
*/
class layoutExample
{
	// Number of the currently displayed eye sprite (0-3).
	int eyeNumber;

	// Drawing window.
	sf::RenderWindow *window;

	// Layout element handler.
	LAYOUT::elementHandler handler;

	// Layout elements.
	LAYOUT::horizontalLayout outerLayout;
	LAYOUT::verticalLayout innerLeftLayout;
	LAYOUT::freeLayout prevLayout;
	LAYOUT::freeLayout nextLayout;
	LAYOUT::spriteElement prevTextElement;
	LAYOUT::spriteElement nextTextElement;
	LAYOUT::spriteElement prevDotElement;
	LAYOUT::spriteElement nextDotElement;
	LAYOUT::spriteElement quitElement;
	LAYOUT::spriteElement eyeElement;

	// Textures.
	sf::Texture eyeTextures[4];
	sf::Texture blueDotTexture;
	sf::Texture prevTextTexture;
	sf::Texture nextTextTexture;
	sf::Texture quitTexture;
	sf::Texture backgroundTexture;

	// Sprites.
	sf::Sprite eyeSprites[4];
	sf::Sprite blueDotSprite;
	sf::Sprite prevTextSprite;
	sf::Sprite nextTextSprite;
	sf::Sprite quitSprite;
	sf::Sprite backgroundSprite;

public:

	/*
	- Constructor. Most of the work is done during initialisation.
	*/
	layoutExample(sf::RenderWindow &window)
	{
		this->window = &window;

		// Textures are loaded from image files.
		eyeTextures[0].loadFromFile("Assets\\eye-gray.png");
		eyeTextures[1].loadFromFile("Assets\\eye-blue.png");
		eyeTextures[2].loadFromFile("Assets\\eye-green.png");
		eyeTextures[3].loadFromFile("Assets\\eye-brown.png");
		blueDotTexture.loadFromFile("Assets\\blue-dot.png");
		prevTextTexture.loadFromFile("Assets\\previous.png");
		nextTextTexture.loadFromFile("Assets\\next.png");
		quitTexture.loadFromFile("Assets\\quit.png");
		backgroundTexture.loadFromFile("Assets\\background.png");

		// Sprites are assigned their corresponding textures.
		for (int i = 0 ; i < 4 ; i ++)
			eyeSprites[i].setTexture(eyeTextures[i]);
		blueDotSprite.setTexture(blueDotTexture);
		prevTextSprite.setTexture(prevTextTexture);
		nextTextSprite.setTexture(nextTextTexture);
		quitSprite.setTexture(quitTexture);
		backgroundSprite.setTexture(backgroundTexture);

		// All layouts are properly hierarchised and configured.
		outerLayout.set_slot_size(800, 600);
		outerLayout.set_default_alignment(LAYOUT::ALIGNMENT::center,
			LAYOUT::ALIGNMENT::center);
		outerLayout.match_content_to_slot();
		outerLayout.add_element(innerLeftLayout);
		outerLayout.add_element(eyeElement);

		innerLeftLayout.set_content_size(300, 400);
		innerLeftLayout.add_element(prevLayout);
		innerLeftLayout.add_element(nextLayout);
		innerLeftLayout.add_element(quitElement);

		prevLayout.match_content_to_slot();
		prevLayout.add_element(prevDotElement);
		prevLayout.add_element(prevTextElement);
		
		prevDotElement.set_content(blueDotSprite);
		prevDotElement.set_slot_position(prevLayout.get_content_position_x(),
			prevLayout.get_content_position_y());
		prevDotElement.set_slot_size(prevLayout.get_content_width() / 4,
			prevLayout.get_content_height());
		prevDotElement.set_content_size(30, 30);

		prevTextElement.set_sprite_mode(LAYOUT::DRAW::crop, LAYOUT::DRAW::crop);
		prevTextElement.set_sprite_alignment_y(LAYOUT::ALIGNMENT::center);
		prevTextElement.align(LAYOUT::ALIGNMENT::left,
			LAYOUT::ALIGNMENT::keep);
		prevTextElement.set_slot_position(prevLayout.get_content_position_x()
			+ prevLayout.get_content_width() / 4,
			prevLayout.get_content_position_y());
		prevTextElement.set_slot_size(prevLayout.get_content_width() * 3 / 4,
			prevLayout.get_content_height());
		prevTextElement.match_content_to_slot();
		prevTextElement.set_content(prevTextSprite);

		nextLayout.match_content_to_slot();
		nextLayout.add_element(nextDotElement);
		nextLayout.add_element(nextTextElement);
		
		nextDotElement.set_content(blueDotSprite);
		nextDotElement.set_slot_position(nextLayout.get_content_position_x(),
			nextLayout.get_content_position_y());
		nextDotElement.set_slot_size(nextLayout.get_content_width() / 4,
			nextLayout.get_content_height());
		nextDotElement.set_content_size(30, 30);

		nextTextElement.set_sprite_mode(LAYOUT::DRAW::crop, LAYOUT::DRAW::crop);
		nextTextElement.set_sprite_alignment_y(LAYOUT::ALIGNMENT::center);
		nextTextElement.align(LAYOUT::ALIGNMENT::left,
			LAYOUT::ALIGNMENT::keep);
		nextTextElement.set_slot_position(nextLayout.get_content_position_x()
			+ nextLayout.get_content_width() / 4,
			nextLayout.get_content_position_y());
		nextTextElement.set_slot_size(nextLayout.get_content_width() * 3 / 4,
			nextLayout.get_content_height());
		nextTextElement.match_content_to_slot();
		nextTextElement.set_content(nextTextSprite);

		quitElement.set_content(quitSprite);
		quitElement.set_content_size(40, 40);

		eyeElement.set_content_size(350, 350);
		eyeElement.set_alignment(LAYOUT::ALIGNMENT::center,
			LAYOUT::ALIGNMENT::center);
		eyeElement.set_background(backgroundSprite);
		eyeElement.set_background_alignment(LAYOUT::ALIGNMENT::center,
			LAYOUT::ALIGNMENT::center);
		eyeElement.set_background_mode(LAYOUT::DRAW::repeat,
			LAYOUT::DRAW::repeat);
		eyeElement.set_content(eyeSprites[0]);

		outerLayout.r_align();
		outerLayout.r_set_drawing_window(window);

		// Some elements are assigned on click and/or on hover functionality.
		prevTextElement.onSlotClick = &change_eye_wrapper;
		prevTextElement.onSlotClickArgs["move"] = "-1";
		nextTextElement.onSlotClick = &change_eye_wrapper;
		nextTextElement.onSlotClickArgs["move"] = "1";
		prevTextElement.onSlotHover = &show_dot_wrapper;
		prevTextElement.onSlotHoverArgs["dot"] = "prev";
		nextTextElement.onSlotHover = &show_dot_wrapper;
		nextTextElement.onSlotHoverArgs["dot"] = "next";
		quitElement.onContentClick = &close_window_wrapper;

		// Adding them to a handler will make handling those events easier.
		handler.add_element(prevTextElement);
		handler.add_element(nextTextElement);
		handler.add_element(quitElement);
	}

	/*
	- Called at every frame in order to draw the layout.
	*/
	void draw()
	{
		// Drawing a layout recursively draws all elements inside it.
		outerLayout.draw();
	}

	/*
	- Resets the attributes appropriately before processing each frame.
	*/
	void reset()
	{
		// Blue dots are made invisible.
		prevDotElement.set_content_visibility(false);
		nextDotElement.set_content_visibility(false);
	}

	/*
	- Changes the eye sprite.
	*/
	void change_eye(std::map<std::string, std::string> &argMap)
	{
		if (argMap["move"] == "1" || argMap["move"] == "-1")
		{
			eyeNumber += std::stoi(argMap["move"]);
			if (eyeNumber < 0)
				eyeNumber = 3;
			else if (eyeNumber > 3)
				eyeNumber = 0;
			eyeElement.set_content(eyeSprites[eyeNumber]);
		}
	}

	/*
	- Shows a blue dot.
	*/
	void show_dot(std::map<std::string, std::string> &argMap)
	{
		if (argMap["dot"] == "prev")
			prevDotElement.set_content_visibility(true);
		else if (argMap["dot"] == "next")
			nextDotElement.set_content_visibility(true);
	}

	/*
	- Closes the main drawing window.
	*/
	void close_window()
	{
		window->close();
	}

	/*
	- Tells the handler to process on click events.
	*/
	void click(float cursorPosX, float cursorPosY)
	{
		handler.click(cursorPosX, cursorPosY);
	}

	/*
	- Tells the handler to process on hover events.
	*/
	void hover(float cursorPosX, float cursorPosY)
	{
		handler.hover(cursorPosX, cursorPosY);
	}
};


/*
- For handling events, layout elements can only be directly assigned generic
functions.
- In order to assign class methods, it's necessary to either make those methods
static, or to use global wrappers, plus a global pointer to a class instance.
- This situation is described in greater detail in C++ FAQ 33.1 and 33.2
(http://www.parashift.com/c++-faq-lite/fnptr-vs-memfnptr-types.html).
*/
layoutExample *example_gp;

void change_eye_wrapper(std::map<std::string, std::string> &argMap)
{
	example_gp->change_eye(argMap);
}

void show_dot_wrapper(std::map<std::string, std::string> &argMap)
{
	example_gp->show_dot(argMap);
}

void close_window_wrapper(std::map<std::string, std::string> &argMap)
{
	example_gp->close_window();
}


/*
- Main function. Drives the flow of the execution.
*/
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Layout Example");
	layoutExample example(window);
	example_gp = &example;

	while (window.isOpen())
	{
		// Reset before processing a frame.
		example.reset();

		// Event processing.
		// It's usually advisable to process hover events before click ones.
		// This way if one effect overrides the other, the click event prevails.
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		example.hover(float(mousePos.x), float(mousePos.y));
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
				example.click(float(mousePos.x), float(mousePos.y));
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// The frame is drawn on the main window.
		window.clear(sf::Color::Black);
		example.draw();
		window.display();
	}
}