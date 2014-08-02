#ifndef SFML_LAYOUT_HPP
#define SFML_LAYOUT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "layout.hpp"


namespace SFML_LAYOUT
{

	/*
	- Possible values for the background drawing mode.
	- All are viable options for both axis.
	*/
	namespace BACKGROUND
	{
		/*
		- The sprite will be fully drawn as is, even if it exceeds the slot.
		*/
		const int full = 0;

		/*
		- The sprite will be drawn in its original scale, but will be cropped
		if it exceeds the slot.
		*/
		const int crop = 1;

		/*
		- The size of the sprite will be adjusted so that it fills the slot
		exactly.
		*/
		const int adjust = 2;

		/*
		- The sprite will be drawn in its original scale consecutively as many
		times as it takes to fill the slot.
		- Last row and column will be cropped if they trespass slot borders.
		*/
		const int repeat = 3;
	};


	/*
	- Base class to expand elements with SMFL-specific attributes and methods.
	- It adds a default window to draw on, and a background sprite.
	*/
	class SFMLBase
	{
	protected:

		/*
		- If another one isn't speicifed when drawing an element, it will be
		drawn on this window.
		*/
		sf::RenderWindow* defaultWindow;

		/*
		- This sprite will be drawn before the element's content, on the slot
		frame, according to the specified mode.
		- A background sprite can't have a rotation, or it may malfunction.
		*/
		sf::Sprite* background;

		/*
		- Determines how the background will be drawn on the X axis.
		- Valid values are 'BACKGROUND::full', 'BACKGROUND::crop',
		'BACKGROUND::adjust', and 'BACKGROUND::repeat'.
		*/
		int backgroundModeX;

		/*
		- Determines how the background will be drawn on the Y axis.
		- Valid values are 'BACKGROUND::full', 'BACKGROUND::crop',
		'BACKGROUND::adjust', and 'BACKGROUND::repeat'.
		*/
		int backgroundModeY;

		/*
		- Determines the X alignment of the background in the slot.
		- Valid values are 'LAYOUT::ALIGNMENT::left',
		'LAYOUT::ALIGNMENT::right', and 'LAYOUT::ALIGNMENT::center'.
		*/
		int backgroundAlignmentX;

		/*
		- Determines the Y alignment of the background in the slot.
		- Valid values are 'LAYOUT::ALIGNMENT::top',
		'LAYOUT::ALIGNMENT::bottom', and 'LAYOUT::ALIGNMENT::center'.
		*/
		int backgroundAlignmentY;

		/*
		- A 'false' value prevents the background from being displayed.
		*/
		bool backgroundVisible;

		/*
		- Adjusts the position and size of a sprite on the X axis.
		*/
		void adjustSpriteX(sf::Sprite* sprite, float left, float width);

		/*
		- Adjusts the position and size of a sprite on the Y axis.
		*/
		void adjustSpriteY(sf::Sprite* sprite, float top, float height);

		/*
		- Crops a sprite on the X axis so it fits within the given space.
		*/
		void cropSpriteX(sf::Sprite* sprite, float left, float width);

		/*
		- Crops a sprite on the Y axis so it fits within the given space.
		*/
		void cropSpriteY(sf::Sprite* sprite, float top, float height);

		/*
		- Repeatedly draws the given sprite covering the specified rectangle.
		- The initial position of the sprite is used as origin for the
		tesselation (this means the sprite will be drawn once there, and it will
		determine the position of the other repetitions).
		- The sprite will be cropped at the borders and corners if needed.
		- This method assumes that the sprite is already inside the rectangle.
		*/
		void drawRepeatedSprite(sf::RenderWindow* window,
			sf::Sprite* sourceSprite, float framePosX, float framePosY,
			float frameWidth, float frameHeight);
	public:
		/*
		- Draws the background sprite according to current attribute values.
		*/
		void drawBackground(sf::RenderWindow* window, float slotPositionX,
			float slotPositionY, float slotWidth, float slotHeight);

	//public:

		/*
		- Default constructor.
		*/
		SFMLBase(sf::RenderWindow* defaultWindow = 0,
			sf::Sprite* background = 0,
			int backgroundModeX = BACKGROUND::adjust,
			int backgroundModeY = BACKGROUND::adjust,
			int backgroundAlignmentX = LAYOUT::ALIGNMENT::left,
			int backgroundAlignmentY = LAYOUT::ALIGNMENT::top,
			bool backgroundVisible = true);

		/*
		- Default destructor.
		*/
		~SFMLBase();

		/*
		- Returns the value of the attribute 'defaultWindow'.
		*/
		sf::RenderWindow* get_default_window();

		/*
		- Returns the value of the attribute 'background'.
		*/
		sf::Sprite* get_background();

		/*
		- Returns the value of the attribute 'backgroundModeX'.
		*/
		int get_background_mode_x();

		/*
		- Returns the value of the attribute 'backgroundModeY'.
		*/
		int get_background_mode_y();

		/*
		- Returns the value of the attribute 'backgroundAlignmentX'.
		*/
		int get_background_alignment_x();

		/*
		- Returns the value of the attribute 'backgroundAlignmentY'.
		*/
		int get_background_alignment_y();

		/*
		- Returns the attribute 'backgroundVisible'.
		*/
		bool get_background_visibility();

		/*
		- Sets the attribute 'defaultWindow'.
		*/
		void set_default_window(sf::RenderWindow* defaultWindow);

		/*
		- Sets the attribute 'background'.
		*/
		void set_background(sf::Sprite* background);

		/*
		- Sets the attribute 'backgroundModeX'.
		*/
		void set_background_mode_x(int backgroundModeX);

		/*
		- Sets the attribute 'backgroundModeY'.
		*/
		void set_background_mode_y(int backgroundModeY);

		/*
		- Sets both background mode attributes.
		*/
		void set_background_mode(int backgroundModeX, int backgroundModeY);

		/*
		- Sets the attribute 'backgroundAlignmentX'.
		*/
		void set_background_alignment_x(int backgroundAlignmentX);

		/*
		- Sets the attribute 'backgroundAlignmentY'.
		*/
		void set_background_alignment_y(int backgroundAlignmentY);

		/*
		- Sets both background alignment attributes.
		*/
		void set_background_alignment(int backgroundAlignmentX,
			int backgroundAlignmentY);

		/*
		- Sets the attribute 'backgroundVisible'.
		*/
		void set_background_visibility(bool backgroundVisible);

		/*
		- Copies the current SFMLBase attributes into the received instance.
		- Should be replicated in derived classes for their type.
		*/
		void copy(SFMLBase* newSFMLBase);
	};
};
		/*
		- 
		*/

#endif