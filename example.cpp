/*
|------------------------------------------------------------------------------|
|                                 EXAMPLE.CPP                                  |
|------------------------------------------------------------------------------|
| - This program is intended to demonstrate the usage and functionality of     |
| some of the classes and methods implemented by the "SFML_Layout" libraries.  |
| - The intended behaviour consists of a simple sprite viewer. 'Previous' and  |
| 'Next' buttons allow switching between a list of image sprites, with an 'X'  |
| button which closes the window and quits the program.                        |
| - The sources for the borrowed textures used in this example can be found in |
| the text file "Assets/image_source.txt".                                     |
| - When loading sprite textures, this program uses Windows paths. If you are  |
| executing this in a different system you should change them appropriately    |
| (lines 100-108).                                                             |
|------------------------------------------------------------------------------|
| AUTHOR: Sergi Salvador Lozano.                                               |
| FIRST CREATED: 2014/06/01.                                                   |
| LAST UPDATED: 2014/08/07.                                                    |
|------------------------------------------------------------------------------|
*/


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SFMLLayout.hpp"


/*
- Incomplete declarations for wrappers. More about this later.
*/
void change_eye_wrapper(std::map<std::string, void*> &args);
void show_dot_wrapper(std::map<std::string, void*> &args);
void close_window_wrapper(std::map<std::string, void*> &args);


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

	// Events.
	LAYOUT::event onPrevClick;
	LAYOUT::event onNextClick;
	LAYOUT::event onQuitClick;
	LAYOUT::event onPrevHover;
	LAYOUT::event onNextHover;

	// Default arguments for event methods.
	int arg1, arg2;
	std::string arg3, arg4;

public:

	/*
	- Constructor. Most of the work is done during initialisation.
	*/
	layoutExample(sf::RenderWindow &window)
	{
		this->window = &window;

		// Textures are loaded from image files.
		// The following paths are formatted with Windows file systems in mind.
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

		// Some elements are assigned event-driven functionality.
		prevTextElement.add_event("onClick", onPrevClick);
		prevTextElement.add_event("onHover", onPrevHover);
		nextTextElement.add_event("onClick", onNextClick);
		nextTextElement.add_event("onHover", onNextHover);
		quitElement.add_event("onClick", onQuitClick);

		// Adding them to a handler will make handling those events easier.
		handler.add_element(prevTextElement);
		handler.add_element(nextTextElement);
		handler.add_element(quitElement);

		// Events are provided with condition and effect methods, and default
		// arguments that will be passed on to them when activated.
		onPrevClick.set_event_condition(LAYOUT::position_inside_slot_frame);
		onPrevClick.set_event_effect(change_eye_wrapper);
		onPrevClick.add_default_condition_argument(
			"element", static_cast<LAYOUT::baseElement*>(&prevTextElement));
		onPrevClick.add_default_effect_argument("move", &(arg1 = -1));

		onNextClick.set_event_condition(LAYOUT::position_inside_slot_frame);
		onNextClick.set_event_effect(change_eye_wrapper);
		onNextClick.add_default_condition_argument(
			"element", static_cast<LAYOUT::baseElement*>(&nextTextElement));
		onNextClick.add_default_effect_argument("move", &(arg2 = 1));

		onPrevHover.set_event_condition(LAYOUT::position_inside_slot_frame);
		onPrevHover.set_event_effect(show_dot_wrapper);
		onPrevHover.add_default_condition_argument(
			"element", static_cast<LAYOUT::baseElement*>(&prevTextElement));
		onPrevHover.add_default_effect_argument("dot", &(arg3 = "prev"));

		onNextHover.set_event_condition(LAYOUT::position_inside_slot_frame);
		onNextHover.set_event_effect(show_dot_wrapper);
		onNextHover.add_default_condition_argument(
			"element", static_cast<LAYOUT::baseElement*>(&nextTextElement));
		onNextHover.add_default_effect_argument("dot", &(arg4 = "next"));

		onQuitClick.set_event_condition(LAYOUT::position_inside_content_frame);
		onQuitClick.set_event_effect(close_window_wrapper);
		onQuitClick.add_default_condition_argument(
			"element", static_cast<LAYOUT::baseElement*>(&quitElement));
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
	void change_eye(int move)
	{
		eyeNumber += move;
		if (eyeNumber < 0)
			eyeNumber = 3;
		else if (eyeNumber > 3)
			eyeNumber = 0;
		eyeElement.set_content(eyeSprites[eyeNumber]);
	}

	/*
	- Shows a blue dot left of either the "previous" or "next" sprites.
	*/
	void show_dot(std::string &dot)
	{
		if (dot == "prev")
			prevDotElement.set_content_visibility(true);
		else if (dot == "next")
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
		// While creating the events, we added to the conditions' default
		// arguments a pointer to the appropriate layout element.
		// The condition methods still require the cursor position, so
		// we can pass those arguments now to all "onClick" events.
		std::map<std::string, void*> condArgs;
		condArgs["posX"] = &cursorPosX;
		condArgs["posY"] = &cursorPosY;
		// 'activate_events' has an optional third argument for extra effect
		// arguments, but we don't need it now (default arguments are enough).
		handler.activate_events("onClick", condArgs);
	}

	/*
	- Tells the handler to process on hover events.
	*/
	void hover(float cursorPosX, float cursorPosY)
	{
		std::map<std::string, void*> condArgs;
		condArgs["posX"] = &cursorPosX;
		condArgs["posY"] = &cursorPosY;
		handler.activate_events("onHover", condArgs);
	}
};


/*
- When trying to handle event conditions and effects, only generic functions can
be directly assigned.
- In order to assign class methods, it's necessary to either make those methods
static, or to use global wrappers, plus a global pointer to a class instance.
- This situation is described in greater detail in C++ FAQ 33.1 and 33.2
(http://www.parashift.com/c++-faq-lite/fnptr-vs-memfnptr-types.html).
*/

/*
- Next there are the wrappers for all event effect methods.
- We can also use them for casting the required arguments to their original
type (from void*) before passing them on to the appropropriate class method.
- It's a good practice to make sure that the arguments with the names we want
exist in the map, but that can be omitted if we are certain that they are.
*/

layoutExample *example_gp;


void change_eye_wrapper(std::map<std::string, void*> &args)
{
	std::map<std::string, void*>::iterator it = args.find("move");
	if (it != args.end())
	{
		int *move = static_cast<int*>(it->second);
		example_gp->change_eye(*move);
	}
}


void show_dot_wrapper(std::map<std::string, void*> &args)
{
	std::map<std::string, void*>::iterator it = args.find("dot");
	if (it != args.end())
	{
		std::string *dot = static_cast<std::string*>(it->second);
		example_gp->show_dot(*dot);
	}
}


void close_window_wrapper(std::map<std::string, void*> &args)
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