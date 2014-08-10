/*
|------------------------------------------------------------------------------|
|                                SFMLLAYOUT.HPP                                |
|------------------------------------------------------------------------------|
| - Header file with the declarations of the classes and methods implemented   |
| in the source file 'SFMLLayout.cpp'.                                         |
| - This part of the code corresponds to those classes reliant on components   |
|  imported from SFML.                                                         |
|------------------------------------------------------------------------------|
| AUTHOR: Sergi Salvador Lozano.                                               |
| FIRST CREATED: 2014/06/01.                                                   |
| LAST UPDATED: 2014/08/10.                                                    |
|------------------------------------------------------------------------------|
*/


#ifndef SFML_LAYOUT_HPP
#define SFML_LAYOUT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "layout.hpp"


namespace LAYOUT
{

	/*
	- Possible values for sprites' drawing modes.
	- All three are viable options for both axis.
	*/
	enum DRAWMODE
	{
		/*
		- The sprite will be drawn in its original scale, but will be cropped
		if it exceeds the slot.
		*/
		crop,

		/*
		- The size of the sprite will be adjusted so that it fills the slot
		exactly.
		*/
		adjust,

		/*
		- The sprite will be drawn in its original scale consecutively as many
		times as it takes to fill the slot.
		- Alignment is relevant, as the grid will take the position of the
		sprite as a reference.
		- Border rows and columns will be cropped if they trespass slot limits.
		*/
		repeat
	};


	/*
	- Base element expanded with SMFL-specific attributes and methods.
	- It adds a window to draw on, a background sprite, and other attributes and
	methods related to them.
	- This class shouldn't be instanced, but serve as a base for other classes.
	*/
	class element : public virtual baseElement
	{
	protected:

		/*
		- The window where the element will be drawn.
		*/
		sf::RenderWindow* drawingWindow;

		/*
		- This sprite will be drawn before the element's content, on the slot
		frame, according to the specified mode.
		- A background sprite MUST NOT have a rotation component.
		*/
		sf::Sprite* background;

		/*
		- Determines how the background will be drawn on the X axis.
		- Valid values are 'crop', 'adjust', and 'repeat'.
		*/
		DRAWMODE backgroundModeX;

		/*
		- Determines how the background will be drawn on the Y axis.
		- Valid values are 'crop', 'adjust', and 'repeat'.
		*/
		DRAWMODE backgroundModeY;

		/*
		- Determines the X alignment of the background in the slot.
		- Valid values are 'left', 'right', and 'center'.
		*/
		ALIGNMENT backgroundAlignmentX;

		/*
		- Determines the Y alignment of the background in the slot.
		- Valid values are 'top', 'bottom', and 'center'.
		*/
		ALIGNMENT backgroundAlignmentY;

		/*
		- A 'false' value prevents the background from being displayed.
		*/
		bool backgroundVisible;

		/*
		- A 'false' value prevents the content from being displayed.
		*/
		bool contentVisible;

		/*
		- Adjusts the position and size of a sprite on the X axis.
		- The sprite MUSTN'T have a rotation component.
		*/
		void adjustSpriteX(sf::Sprite &sprite, float left, float width);

		/*
		- Adjusts the position and size of a sprite on the Y axis.
		- The sprite MUSTN'T have a rotation component.
		*/
		void adjustSpriteY(sf::Sprite &sprite, float top, float height);

		/*
		- Crops a sprite on the X axis so it fits within the given space.
		- The sprite MUSTN'T have a rotation component.
		*/
		void cropSpriteX(sf::Sprite &sprite, float left, float width);

		/*
		- Crops a sprite on the Y axis so it fits within the given space.
		- The sprite MUSTN'T have a rotation component.
		*/
		void cropSpriteY(sf::Sprite &sprite, float top, float height);

		/*
		- Repeatedly draws the given sprite covering the specified rectangle.
		- The initial position of the sprite is used as origin for the
		tesselation (this means the sprite will be drawn once there, and it will
		determine the position of the other repetitions).
		- The sprite will be cropped at the borders and corners if needed.
		- The sprite MUST be positioned in its entirety within the rectangle.
		- The sprite MUSTN'T have a rotation component.
		*/
		void drawRepeatedSprite(sf::Sprite &sourceSprite, float framePosX,
			float framePosY, float frameWidth, float frameHeight);

		/*
		- Draws the given sprite inside the given frame, according to the
		value of the given drawing mode and alignment attributes.
		*/
		void drawSprite(sf::Sprite &sprite, float framePosX, float framePosY,
			float frameWidth, float frameHeight, DRAWMODE drawModeX,
			DRAWMODE drawModeY, ALIGNMENT alignmentX, ALIGNMENT alignmentY);

	public:

		/*
		- Default constructor.
		*/
		element(sf::RenderWindow* drawingWindow = 0, sf::Sprite* background = 0,
			DRAWMODE backgroundModeX = adjust,
			DRAWMODE backgroundModeY = adjust,
			ALIGNMENT backgroundAlignmentX = left,
			ALIGNMENT backgroundAlignmentY = top,
			bool backgroundVisible = true);

		/*
		- Default destructor.
		*/
		~element();

		/*
		- Returns the value of the attribute 'defaultWindow'.
		*/
		sf::RenderWindow* get_drawing_window();

		/*
		- Returns the value of the attribute 'background'.
		*/
		sf::Sprite* get_background();

		/*
		- Returns the value of the attribute 'backgroundModeX'.
		*/
		DRAWMODE get_background_mode_x();

		/*
		- Returns the value of the attribute 'backgroundModeY'.
		*/
		DRAWMODE get_background_mode_y();

		/*
		- Returns the value of the attribute 'backgroundAlignmentX'.
		*/
		ALIGNMENT get_background_alignment_x();

		/*
		- Returns the value of the attribute 'backgroundAlignmentY'.
		*/
		ALIGNMENT get_background_alignment_y();

		/*
		- Returns the attribute 'backgroundVisible'.
		*/
		bool get_background_visibility();

		/*
		- Sets the attribute 'defaultWindow'.
		*/
		void set_drawing_window(sf::RenderWindow &drawingtWindow);

		/*
		- Calls 'set_drawing_window(drawingtWindow)'.
		- Can be redefined in derived classes.
		*/
		virtual void r_set_drawing_window(sf::RenderWindow &drawingtWindow);

		/*
		- Sets the attribute 'background'.
		*/
		void set_background(sf::Sprite &background);

		/*
		- Sets the attribute 'backgroundModeX'.
		*/
		void set_background_mode_x(DRAWMODE backgroundModeX);

		/*
		- Sets the attribute 'backgroundModeY'.
		*/
		void set_background_mode_y(DRAWMODE backgroundModeY);

		/*
		- Sets both background mode attributes.
		*/
		void set_background_mode(DRAWMODE backgroundModeX,
			DRAWMODE backgroundModeY);

		/*
		- Sets the attribute 'backgroundAlignmentX'.
		*/
		void set_background_alignment_x(ALIGNMENT backgroundAlignmentX);

		/*
		- Sets the attribute 'backgroundAlignmentY'.
		*/
		void set_background_alignment_y(ALIGNMENT backgroundAlignmentY);

		/*
		- Sets both background alignment attributes.
		*/
		void set_background_alignment(ALIGNMENT backgroundAlignmentX,
			ALIGNMENT backgroundAlignmentY);

		/*
		- Sets the attribute 'backgroundVisible'.
		*/
		void set_background_visibility(bool backgroundVisible);

		/*
		- Copies the current element's attributes into the received one.
		- Can be redefined in derived classes.
		*/
		void copy(element &element);

		/*
		- Copies the current element's attributes into the received one.
		- Can be redefined in derived classes.
		*/
		void r_copy(element &element);

		/*
		- Draws the element's background and content in the drawing window.
		*/
		void draw();
	};


	/*
	- An element of a layout with SFML properties, encapsulating an SFML sprite.
	- Destroying this element won't destroy the sprite in it.
	- By copying this element (even in cascade) it's the reference to the sprite
	that will be replicated, not the sprite itself.
	*/
	class spriteElement : public element
	{
	protected:

		/*
		- A sprite which constitutes the element's content.
		*/
		sf::Sprite *content;

		/*
		- Determines how the sprite will be drawn on the X axis.
		- Valid values are 'crop', 'adjust', and 'repeat'.
		*/
		DRAWMODE spriteModeX;

		/*
		- Determines how the sprite will be drawn on the Y axis.
		- Valid values are 'crop', 'adjust', and 'repeat'.
		*/
		DRAWMODE spriteModeY;

		/*
		- Determines the alignment in X of the sprite inside the content space.
		- Valid values are 'left', 'right', and 'center'.
		*/
		ALIGNMENT spriteAlignmentX;

		/*
		- Determines the alignment in Y of the sprite inside the content space.
		- Valid values are 'top', 'bottom', and 'center'.
		*/
		ALIGNMENT spriteAlignmentY;

		/*
		- Draws the content sprite in the drawing window.
		*/
		void drawContent();

	public:

		/*
		- Default constructor.
		*/
		spriteElement(sf::Sprite *content = 0, std::string name = "",
			float contentPosX = 0, float contentPosY = 0,
			float contentWidth = 0, float contentHeight = 0, float slotPosX = 0,
			float slotPosY = 0, float slotWidth = 0, float slotHeight = 0,
			ALIGNMENT alignmentX = none, ALIGNMENT alignmentY = none,
			int depth = 0, bool visible = true, bool contentVisible = true,
			std::map<std::string, event*> &events =
			std::map<std::string, event*>::map<std::string, event*>(),
			sf::RenderWindow* drawingWindow = 0, sf::Sprite* background = 0,
			DRAWMODE backgroundModeX = adjust,
			DRAWMODE backgroundModeY = adjust,
			ALIGNMENT backgroundAlignmentX = left,
			ALIGNMENT backgroundAlignmentY = top, bool backgroundVisible = true,
			DRAWMODE spriteModeX = adjust, DRAWMODE spriteModeY = adjust,
			ALIGNMENT spriteAlignmentX = left,
			ALIGNMENT spriteAlignmentY = top);

		/*
		- Copy constructor.
		*/
		spriteElement(spriteElement &element);

		/*
		- Default destructor.
		*/
		virtual ~spriteElement();

		/*
		- Returns the value of the attribute 'content'.
		*/
		sf::Sprite* get_content();

		/*
		- Returns the value of the attribute 'spriteModeX'.
		*/
		DRAWMODE get_sprite_mode_x();

		/*
		- Returns the value of the attribute 'spriteModeY'.
		*/
		DRAWMODE get_sprite_mode_y();

		/*
		- Returns the value of the attribute 'spriteAlignmentX'.
		*/
		ALIGNMENT get_sprite_alignment_x();

		/*
		- Returns the value of the attribute 'spriteAlignmentY'.
		*/
		ALIGNMENT get_sprite_alignment_y();

		/*
		- Sets the attribute 'content'.
		*/
		void set_content(sf::Sprite &content);

		/*
		- Sets the attribute 'spriteModeX'.
		*/
		void set_sprite_mode_x(DRAWMODE spriteModeX);

		/*
		- Sets the attribute 'spriteModeY'.
		*/
		void set_sprite_mode_y(DRAWMODE spriteModeY);

		/*
		- Sets both sprite mode attributes.
		*/
		void set_sprite_mode(DRAWMODE spriteModeX, DRAWMODE spriteModeY);

		/*
		- Sets the attribute 'spriteAlignmentX'.
		*/
		void set_sprite_alignment_x(ALIGNMENT spriteAlignmentX);

		/*
		- Sets the attribute 'spriteAlignmentY'.
		*/
		void set_sprite_alignment_y(ALIGNMENT spriteAlignmentY);

		/*
		- Sets both sprite alignment attributes.
		*/
		void set_sprite_alignment(ALIGNMENT spriteAlignmentX,
			ALIGNMENT spriteAlignmentY);

		/*
		- Creates a copy of the current element in a new instance.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual spriteElement* clone();
		
		/*
		- Creates a recursive copy of the current element in a new instance.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual spriteElement* r_clone();
		
		/*
		- Copies the current element's attributes into the received one.
		- Can be redefined in derived classes.
		*/
		virtual void copy(spriteElement &element);
		
		/*
		- Copies the current element's attributes into the received one.
		- Can be redefined in derived classes.
		*/
		virtual void r_copy(spriteElement &element);
	};


	/*
	- A free layout extended with SFML poperties.
	*/
	class freeLayout : public virtual baseFreeLayout, public element
	{
	public:

		/*
		- Default constructor.
		*/
		freeLayout(std::string name = "", float contentPosX = 0,
			float contentPosY = 0, float contentWidth = 0,
			float contentHeight = 0, float slotPosX = 0, float slotPosY = 0,
			float slotWidth = 0, float slotHeight = 0,
			ALIGNMENT alignmentX = none, ALIGNMENT alignmentY = none,
			int depth = 0, bool visible = true, bool contentVisible = true,
			std::map<std::string, event*> &events =
			std::map<std::string, event*>::map<std::string, event*>(),
			int size = 0, ALIGNMENT defaultAlignmentX = left,
			ALIGNMENT defaultAlignmentY = top, bool elastic = true,
			sf::RenderWindow* defaultWindow = 0, sf::Sprite* background = 0,
			DRAWMODE backgroundModeX = adjust,
			DRAWMODE backgroundModeY = adjust,
			ALIGNMENT backgroundAlignmentX = left,
			ALIGNMENT backgroundAlignmentY = top,
			bool backgroundVisible = true);

		/*
		- Copy constructor.
		*/
		freeLayout(freeLayout &layout);

		/*
		- Default destructor.
		*/
		virtual ~freeLayout();

		/*
		- Returns a pointer to the element in the specified slot, or null if
		it's empty.
		- It's a more concrete version of the same method in 'baseFreeLayout'
		(which returns a pointer to 'baseElement').
		*/
		element* get_element(int slot);

		/*
		- Recursively sets the received window as the drawing window for the
		layout and every element inside it.
		*/
		void r_set_drawing_window(sf::RenderWindow &drawingWindow);

		/*
		- Creates a copy of the current layout in a new instance.
		- The resulting layout has no elements.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual freeLayout* clone();
		
		/*
		- Creates a recursive copy of the current layout in a new instance.
		- The resulting layout contains clones of the elements in the base one.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual freeLayout* r_clone();
		
		/*
		- Copies the current layout's attributes into the received one.
		- Elements inside are not copied (the layout keeps its elements if any).
		- Can be redefined in derived classes.
		*/
		virtual void copy(freeLayout &layout);
		
		/*
		- Copies the current layout's attributes into the received one.
		- Elements inside are also recursively cloned. Any existing pointers in
		the received layout are lost.
		- Can be redefined in derived classes.
		*/
		virtual void r_copy(freeLayout &layout);

		/*
		- Returns a pointer to the element in the layout (or in a sublayout)
		with the given id.
		- It's a more concrete version of the same method in 'baseFreeLayout'
		(which returns a pointer to 'baseElement').
		*/
		element* find_element(int elementId);

		/*
		- Returns a pointer to the element in the layout (or in a sublayout)
		with the given name.
		- It's a more concrete version of the same method in 'baseFreeLayout'
		(which returns a pointer to 'baseElement').
		*/
		element* find_element(std::string elementName);

		/*
		- Adds a given element to the layout at the lowest free slot.
		- It's a more concrete version of the same method in 'baseFreeLayout'
		(which accepts any instance dervived from 'baseElement').
		*/
		void add_element(element &element);

		/*
		- Adds a given element to the layout at the specified slot.
		- It's a more concrete version of the same method in 'baseFreeLayout'
		(which accepts any instance dervived from 'baseElement').
		*/
		void add_element(element &element, int slot);

		/*
		- Removes an element from the layout at the given slot and returns it.
		- It's a more concrete version of the same method in 'baseFreeLayout'
		(which a pointer to 'baseElement').
		*/
		element* remove_element(int slot);

		/*
		- Removes an element from the layout (or from a sublayout), if present.
		- Can be redefined in derived classes.
		*/
		void remove_element(element &element);
	};


	/*
	- An horizontal layout extended with SFML poperties.
	*/
	class horizontalLayout : public baseHorizontalLayout, public freeLayout
	{
	public:

		/*
		- Default constructor.
		*/
		horizontalLayout(std::string name = "", float contentPosX = 0,
			float contentPosY = 0, float contentWidth = 0,
			float contentHeight = 0, float slotPosX = 0, float slotPosY = 0,
			float slotWidth = 0, float slotHeight = 0,
			ALIGNMENT alignmentX = none, ALIGNMENT alignmentY = none,
			int depth = 0, bool visible = true, bool contentVisible = true,
			std::map<std::string, event*> &events =
			std::map<std::string, event*>::map<std::string, event*>(),
			int size = 0, ALIGNMENT defaultAlignmentX = left,
			ALIGNMENT defaultAlignmentY = top, bool elastic = true,
			sf::RenderWindow* defaultWindow = 0, sf::Sprite* background = 0,
			DRAWMODE backgroundModeX = adjust,
			DRAWMODE backgroundModeY = adjust,
			ALIGNMENT backgroundAlignmentX = left,
			ALIGNMENT backgroundAlignmentY = top,
			bool backgroundVisible = true);

		/*
		- Copy constructor.
		*/
		horizontalLayout(horizontalLayout &layout);

		/*
		- Default destructor.
		*/
		virtual ~horizontalLayout();

		/*
		- Creates a copy of the current layout in a new instance.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual horizontalLayout* clone();
		
		/*
		- Creates a recursive copy of the current layout in a new instance.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual horizontalLayout* r_clone();
	};


	/*
	- A vertical layout extended with SFML poperties.
	*/
	class verticalLayout : public baseVerticalLayout, public freeLayout
	{
	public:

		/*
		- Default constructor.
		*/
		verticalLayout(std::string name = "", float contentPosX = 0,
			float contentPosY = 0, float contentWidth = 0,
			float contentHeight = 0, float slotPosX = 0, float slotPosY = 0,
			float slotWidth = 0, float slotHeight = 0,
			ALIGNMENT alignmentX = none, ALIGNMENT alignmentY = none,
			int depth = 0, bool visible = true, bool contentVisible = true,
			std::map<std::string, event*> &events =
			std::map<std::string, event*>::map<std::string, event*>(),
			int size = 0, ALIGNMENT defaultAlignmentX = left,
			ALIGNMENT defaultAlignmentY = top, bool elastic = true,
			sf::RenderWindow* defaultWindow = 0, sf::Sprite* background = 0,
			DRAWMODE backgroundModeX = adjust,
			DRAWMODE backgroundModeY = adjust,
			ALIGNMENT backgroundAlignmentX = left,
			ALIGNMENT backgroundAlignmentY = top,
			bool backgroundVisible = true);

		/*
		- Copy constructor.
		*/
		verticalLayout(verticalLayout &layout);

		/*
		- Default destructor.
		*/
		virtual ~verticalLayout();

		/*
		- Creates a copy of the current layout in a new instance.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual verticalLayout* clone();
		
		/*
		- Creates a recursive copy of the current layout in a new instance.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual verticalLayout* r_clone();
	};


	/*
	- A table layout extended with SFML poperties.
	*/
	class tableLayout : public baseTableLayout, public freeLayout
	{
	private:

		/*
		- The method for turning on elasticity is hidden.
		*/
		using baseFreeLayout::set_elasticity;

	public:

		/*
		- Default constructor.
		*/
		tableLayout(std::string name = "", float contentPosX = 0,
			float contentPosY = 0, float contentWidth = 0,
			float contentHeight = 0, float slotPosX = 0, float slotPosY = 0,
			float slotWidth = 0, float slotHeight = 0,
			ALIGNMENT alignmentX = none, ALIGNMENT alignmentY = none,
			int depth = 0, bool visible = true, bool contentVisible = true,
			std::map<std::string, event*> &events =
			std::map<std::string, event*>::map<std::string, event*>(),
			int numberOfRows = 0, int numberOfColumns = 0,
			ALIGNMENT defaultAlignmentX = left,
			ALIGNMENT defaultAlignmentY = top,
			sf::RenderWindow* defaultWindow = 0, sf::Sprite* background = 0,
			DRAWMODE backgroundModeX = adjust,
			DRAWMODE backgroundModeY = adjust,
			ALIGNMENT backgroundAlignmentX = left,
			ALIGNMENT backgroundAlignmentY = top,
			bool backgroundVisible = true);

		/*
		- Copy constructor.
		*/
		tableLayout(tableLayout &layout);

		/*
		- Default destructor.
		*/
		virtual ~tableLayout();

		/*
		- For the original overloads of 'is_slot_full'.
		*/
		using baseTableLayout::is_slot_full;

		/*
		- For the original overloads of 'get_element'.
		*/
		using freeLayout::get_element;

		/*
		- Calls 'get_element' translating row and column to slot number.
		- It's a more concrete version of the same method in 'baseTableLayout'
		(which returns a pointer to 'baseElement').
		*/
		element* get_element(int row, int column);

		/*
		- Sets the attributes 'numberOfRows' and 'numberOfColumns'.
		- Hides the method 'set_size(int size)' from 'freeLayout'.
		*/
		using baseTableLayout::set_size; 

		/*
		- Creates a copy of the current layout in a new instance.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual tableLayout* clone();
		
		/*
		- Creates a recursive copy of the current layout in a new instance.
		- MUST be redefined in instantiable derived classes for their type.
		*/
		virtual tableLayout* r_clone();

		/*
		- Copies the current layout's attributes into the received one.
		- Elements inside are not copied (the layout keeps its elements if any).
		- Can be redefined in derived classes.
		*/
		virtual void copy(tableLayout &layout);
		
		/*
		- Copies the current layout's attributes into the received one.
		- Elements inside are also recursively cloned. Any existing pointers in
		the received layout are lost.
		- Can be redefined in derived classes.
		*/
		virtual void r_copy(tableLayout &layout);

		/*
		- For the original overloads of 'add_element'.
		*/
		using freeLayout::add_element;

		/*
		- Calls 'add_element' translating row and column to slot number.
		- It's a more concrete version of the same method in 'baseTableLayout'
		(which accepts any instance dervived from 'baseElement').
		*/
		void add_element(element &element, int row, int column);

		/*
		- For the original overloads of 'remove_element'.
		*/
		using freeLayout::remove_element;

		/*
		- Calls 'remove_element' translating row and column to slot number.
		- It's a more concrete version of the same method in 'baseTableLayout'
		(which returns a pointer to 'baseElement').
		*/
		element* remove_element(int row, int column);
	};

};



#endif