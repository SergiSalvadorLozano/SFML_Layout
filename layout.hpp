/*
|------------------------------------------------------------------------------|
|                                  LAYOUT.HPP                                  |
|------------------------------------------------------------------------------|
| - Header file with the declarations of the classes and methods implemented   |
| in the source file 'layout.cpp'.                                             |
| - This part of the code corresponds to the base classes containing most of   |
| the logic and functionality independent from specific graphic libraries.     |
|------------------------------------------------------------------------------|
| AUTHOR: Sergi Salvador Lozano.                                               |
| FIRST CREATED: 2014/06/01.                                                   |
| LAST UPDATED: 2014/08/07.                                                    |
|------------------------------------------------------------------------------|
*/


#ifndef LAYOUT_HPP
#define LAYOUT_HPP

#include <vector>
#include <list>
#include <string>
#include <map>


namespace LAYOUT
{
	/*
	- Possible values for the alignment attributes in the element class.
	*/
	namespace ALIGNMENT
	{
		/*
		- Possible value for 'alignmentX' and 'alignmentY'.
		- Content position is unrestricted in that axis.
		*/
		const int none = 0;
		
		/*
		- Possible value for 'alignmentX'.
		- The left content limit must coincide with the left slot limit.
		*/
		const int left = 1;
		
		/*
		- Possible value for 'alignmentX'.
		- The right content limit must coincide with the right slot limit.
		*/
		const int right = 2;

		/*
		- Possible value for 'alignmentY'.
		- The top content limit must coincide with the top slot limit.
		*/
		const int top = 3;
		
		/*
		- Possible value for 'alignmentY'.
		- The bottom content limit must coincide with the bottom slot limit.
		*/
		const int bottom = 4;
		
		/*
		- Possible value for 'alignmentX' and 'alignmentY'.
		- Content limits must keep the same distance to their respective slot
		limits on that axis.
		*/
		const int center = 5;

		/*
		- Valid argument for some methods that change elements' alignment.
		- It causes alignment on that axis to remain unchanged.
		*/
		const int keep = 6;
	};


	/*
	- Incomplete declarations. Needed in class 'baseElement' (declared first).
	*/
	class baseFreeLayout;
	class event;


	/*
	- An element that can be part of a layout.
	- An element can only be part of one layout (and only once).
	- Elements can (should) have content. To be defined in derived classes.
	- Elements can fit in slots (the sapce a layout reserves for them).
	- Content is allowed to fall outside of slot limits. It's up to derived
	classes to manage that appropriately.
	- This class shouldn't be instanced, but serve as a base for other classes.
	*/
	class baseElement
	{
	protected:

		/*
		- Keeps count of the number of instanced elements, and is used to
		provide them with unique ids upon initialisation.
		*/
		static int idGenerator;

		/*
		- Number which uniquely identifies the element.
		- It's automatically assigned and can't be modified.
		*/
		int id;

		/*
		- The name of the element.
		- If not specified, it's initialised to the empty string.
		*/
		std::string name;

		/*
		- Pointer to the parent layout.
		- Used in order to prevent the element from being added to muliple
		layouts (or multiple times to the same layout).
		*/
		baseFreeLayout *parentLayout;

		/*
		- Slot where the element is located in the parent layout.
		- If there's no parent layout, its value is -1.
		*/
		int slotNumber;

		/*
		- The position of the content's top-left corner on the X axis.
		*/
		float contentPosX;

		/*
		- The position of the content's top-left corner on the Y axis.
		*/
		float contentPosY;

		/*
		- The size of the content on the X axis.
		- Can't be negative.
		*/
		float contentWidth;

		/*
		- The size of the content on the Y axis.
		- Can't be negative.
		*/
		float contentHeight;

		/*
		- The position of the content's top-left corner on the X axis.
		*/
		float slotPosX;

		/*
		- The position of the content's top-left corner on the Y axis.
		*/
		float slotPosY;

		/*
		- The size of the content on the X axis.
		- Can't be negative.
		*/
		float slotWidth;

		/*
		- The size of the content on the Y axis.
		- Can't be negative.
		*/
		float slotHeight;

		/*
		- How the content is to be positioned inside the slot on the X axis.
		- Valid values are 'ALIGNMENT::none', 'ALIGNMENT::left',
		'ALIGNMENT::right', and 'ALIGNMENT::center'.
		*/
		int alignmentX;

		/*
		- How the content is to be positioned inside the slot on the Y axis.
		- Valid values are 'ALIGNMENT::none', 'ALIGNMENT::top',
		'ALIGNMENT::bottom', and 'ALIGNMENT::center'.
		*/
		int alignmentY;

		/*
		- Depth of the element relative to other elements in the same layout.
		- Elements with higher depth will be drawn first (and may be partially
		or totally occluded by other elements).
		- This attribute is taken into account when drawing a layout.
		*/
		int depth;

		/*
		- A 'false' value prevents the whole element from being displayed.
		- This attribute takes precedence over other visibility ones.
		- This attribute is taken into account when drawing a layout.
		*/
		bool visible;

		/*
		- A 'false' value prevents the element's content from being displayed.
		- Only relevant if 'visible' is 'true'.
		*/
		bool contentVisible;

		/*
		- Draws the element's content.
		- MUST be defined in instantiable derived classes.
		*/
		virtual void drawContent() = 0;

		/*
		- Map of events associated to the element, each identified by a string.
		*/
		std::map<std::string, event*> events;

	public:

		/*
		- Default constructor.
		*/
		baseElement(std::string name = "", float contentPosX = 0,
			float contentPosY = 0, float contentWidth = 0,
			float contentHeight = 0, float slotPosX = 0, float slotPosY = 0,
			float slotWidth = 0, float slotHeight = 0,
			int alignmentX = ALIGNMENT::none, int alignmentY = ALIGNMENT::none,
			int depth = 0, bool visible = true, bool contentVisible = true,
			std::map<std::string, event*> &events =
			std::map<std::string, event*>::map<std::string, event*>());
		
		/*
		- Default destructor.
		*/
		virtual ~baseElement();

		/*
		- Returns the value of the attribute 'id'.
		*/
		int get_id();

		/*
		- Returns the value of the attribute 'name'.
		*/
		std::string get_name();

		/*
		- Returns the value of the attribute 'parentLayout'.
		*/
		baseFreeLayout* get_parent_layout();

		/*
		- Returns the value of the attribute 'slotNumber'.
		*/
		int get_slot_number();
		
		/*
		- Returns the value of the attribute 'contentPosX'.
		*/
		float get_content_position_x();
		
		/*
		- Returns the value of the attribute 'contentPosY'.
		*/
		float get_content_position_y();
		
		/*
		- Returns the value of the attribute 'contentWidth'.
		*/
		float get_content_width();
		
		/*
		- Returns the value of the attribute 'contentHeight'.
		*/
		float get_content_height();
		
		/*
		- Returns the value of the attribute 'slotPosX'.
		*/
		float get_slot_position_x();
		
		/*
		- Returns the value of the attribute 'slotPosY'.
		*/
		float get_slot_position_y();
		
		/*
		- Returns the value of the attribute 'slotWidth'.
		*/
		float get_slot_width();
		
		/*
		- Returns the value of the attribute 'slotHeight'.
		*/
		float get_slot_height();

		/*
		- Returns the value of the attribute 'alignmentX'.
		*/
		int get_alignment_x();

		/*
		- Returns the value of the attribute 'alignmentY'.
		*/
		int get_alignment_y();

		/*
		- Returns the value of the attribute 'depth'.
		*/
		int get_depth();

		/*
		- Returns the value of the attribute 'visible'.
		*/
		bool get_visibility();

		/*
		- Returns the value of the the attribute 'contentVisible'.
		*/
		bool get_content_visibility();

		/*
		- Returns a reference to the whole map of events for the element.
		*/
		std::map<std::string, event*>& get_events();

		/*
		- Returns a pointer to the event associated to a given name.
		- If there is none, the return value is 0.
		*/
		event* find_event(std::string eventName);

		/*
		- Sets the attribute 'name'.
		*/
		void set_name(std::string name);

		/*
		- Sets the attributes 'contentPosX' and 'contentPosY'.
		- Can be redefined in derived classes.
		*/
		virtual void set_content_position(float contentPosX, float contentPosY);

		/*
		- Sets the attributes 'contentWidth' and 'contentHeight'.
		- Aligns the content inside the slot.
		- Can be redefined in derived classes.
		*/
		virtual void set_content_size(float contentWidth, float contentHeight);

		/*
		- Sets the attributes 'slotPosX' and 'slotPosY'.
		- Aligns the content inside the slot.
		- Can be redefined in derived classes.
		*/
		virtual void set_slot_position(float slotPosX, float slotPosY);

		/*
		- Sets the attributes 'slotWidth' and 'slotHeight'.
		- Aligns the content inside the slot.
		- Can be redefined in derived classes.
		*/
		virtual void set_slot_size(float slotWidth, float slotHeight);

		/*
		- Updates the content's size and position to match the slot's.
		*/
		void match_content_to_slot();

		/*
		- Calls 'match_content_to_slot()'.
		- Can be redefined in derived classes.
		*/
		virtual void r_match_content_to_slot();

		/*
		- Updates the slot's size and position to match the content's.
		*/
		void match_slot_to_content();

		/*
		- Calls 'match_slot_to_content()'.
		- Can be redefined in derived classes.
		*/
		virtual void r_match_slot_to_content();

		/*
		- Sets the attribute 'alignmentX'.
		- Invalid values leave it unchanged.
		*/
		void set_alignment_x(int alignmentX);

		/*
		- Sets the attribute 'alignmentY'.
		- Invalid values leave it unchanged.
		*/
		void set_alignment_y(int alignmentY);

		/*
		- Sets both alignment attributes.
		- Invalid values leave alignment on that axis unchanged.
		*/
		void set_alignment(int alignmentX, int alignmentY);

		/*
		- Sets the position of the content inside the slot according to
		the current value of 'alignmentX' and 'alignmentY'.
		*/
		void align();

		/*
		- Calls 'align()'.
		- Can be redefined in derived classes.
		*/
		virtual void r_align();

		/*
		- Sets both alignment attributes and calls the 'align()' method.
		- Invalid values align the content according to the existing alignment.
		*/
		void align(int alignmentX, int alignmentY);

		/*
		- Calls 'align(alignmentX, alignmentY)'.
		- Can be redefined in derived classes.
		*/
		virtual void r_align(int alignmentX, int alignmentY);

		/*
		- Sets the attribute 'depth'.
		*/
		void set_depth(int depth);

		/*
		- Sets the attribute 'visible'.
		*/
		void set_visibility(bool visible);

		/*
		- Sets the attribute 'contentVisible'.
		*/
		void set_content_visibility(bool contentVisible);

		/*
		- Sets the attribute 'events' as a copy of the given map.
		*/
		void set_events(std::map<std::string, event*> &events);

		/*
		- Adds an event under the given name.
		- If there is already one, it is overwritten.
		*/
		void add_event(std::string eventName, event &e);

		/*
		- Removes from the element the event under the given name (if any).
		*/
		void remove_event(std::string eventName);

		/*
		- Creates a copy of the current element in a new instance.
		- MUST be defined in instantiable derived classes for their type.
		*/
		virtual baseElement* clone() = 0;
		
		/*
		- Creates a recursive copy of the current element in a new instance.
		- MUST be defined in instantiable derived classes for their type.
		*/
		virtual baseElement* r_clone() = 0;

		/*
		- Makes the received element into a copy of the current element.
		- Can be redefined in derived classes.
		*/
		virtual void copy(baseElement &newElement);
		
		/*
		- Makes the received element into a copy of the current element.
		- Can be redefined in derived classes.
		*/
		virtual void r_copy(baseElement &newElement);
		
		/*
		- Calls the default destructor.
		- Can be redefined in derived classes.
		*/
		virtual void r_delete();

		/*
		- Calls 'drawContent' if the content is set visible.
		- Can be redefined in derived classes.
		*/
		virtual void draw();

		/*
		- Methods 'r_copy', 'add_element' and 'remove_element' from
		'baseFreeLayout' need to modify the attributes 'parentLayout' and
		'slotNumber'.
		*/
		friend class baseFreeLayout;
	};


	/*
	- Groups elements together.
	- Allows storage, retrieval, and simultaneous event handling.
	*/
	class elementHandler
	{
	protected:

		/*
		- Map storing the elements, with their id as the key.
		- There can be no repeated elements.
		*/
		std::map<int, baseElement*> idMap;

	public:

		/*
		- Default constructor.
		*/
		elementHandler();

		/*
		- Copy constructor.
		- The new handler contains pointers to the same elements as the source.
		*/
		elementHandler(elementHandler &handler);

		/*
		- Default destructor.
		*/
		~elementHandler();

		/*
		- Returns a copy of 'idMap'.
		*/
		std::map<int, baseElement*> get_map();

		/*
		- Makes the received handler into a copy of the current handler.
		- The received one contains pointers to the same elements as the source.
		*/
		void copy(elementHandler &handler);

		/*
		- Returns a pointer to the element in the handler with the given id.
		- If no element with that id is found, the return value is 0.
		*/
		baseElement* find_element(int elementId);

		/*
		- Returns a pointer to the element in the handler with the given name.
		- If no element with that name is found, the return value is 0.
		*/
		baseElement* find_element(std::string elementName);

		/*
		- Adds the given element to the handler.
		*/
		void add_element(baseElement &element);

		/*
		- Recursively adds to the handler the layout and every element in it.
		*/
		void r_add_element(baseElement &element);

		/*
		- Removes from the handler the given element (if present).
		*/
		void remove_element(baseElement &element);

		/*
		- Removes from the handler the given element (if present).
		- If the element is a layout, every element inside it is also
		recursively removed.
		*/
		void r_remove_element(baseElement &element);

		/*
		- For all elements in the handler, activates the events identified by a
		given string.
		- New maps of arguments for condition and effect methods can be
		provided, in which case they will be added to the default maps.
		- If an argument is provided under the same string that an existing
		default argument, the new one overwrites the default one.
		*/
		void activate_events(std::string eventName,
			std::map<std::string, void*> &conditionArgs =
			std::map<std::string, void*>::map<std::string, void*>(),
			std::map<std::string, void*> &effectArgs =
			std::map<std::string, void*>::map<std::string, void*>());
	};
	

	/*
	- An event. An association of a condition and an effect.
	*/
	class event
	{
	protected:

		/*
		- Type redefinitions for pointers to functions.
		- These redefinitions make it easier to manage the types while using
		them in method arguments or return values.
		*/
		typedef bool (*eventConditionType)(std::map<std::string, void*>&);
		typedef void (*eventEffectType)(std::map<std::string, void*>&);

		/*
		- A method implementing the condition to decide if the event effect
		should be triggered.
		- Without a condition, the effect (if any) will always be triggered
		upon activation.
		*/
		eventConditionType eventCondition;
		
		/*
		- A method implementing the effect of the event.
		- Without an effect, nothing will be triggered upon activation.
		*/
		eventEffectType eventEffect;

		/*
		- The set of arguments passed on by default to the condition function.
		*/
		std::map<std::string, void*> defaultConditionArgs;

		/*
		- The set of arguments passed on by default to the effect function.
		*/
		std::map<std::string, void*> defaultEffectArgs;

	public:

		/*
		- Default constructor.
		*/
		event(eventConditionType eventCondition = 0,
			eventEffectType eventEffect = 0,
			std::map<std::string, void*> &defaultConditionArgs =
			std::map<std::string, void*>::map<std::string, void*>(),
			std::map<std::string, void*> &defaultEffectArgs =
			std::map<std::string, void*>::map<std::string, void*>());

		/*
		- Returns a pointer to the event condition function.
		*/
		eventConditionType get_event_condition();

		/*
		- Returns a pointer to the event effect function..
		*/
		eventEffectType get_event_effect();

		/*
		- Returns a reference to the attribute 'defaultConditionArgs'.
		*/
		std::map<std::string, void*>& get_default_condition_args();

		/*
		- Returns a reference to the attribute 'defaultEffectArgs'.
		*/
		std::map<std::string, void*>& get_default_effect_args();

		/*
		- Sets the pointer to the event condition function.
		*/
		void set_event_condition(eventConditionType eventCondition);

		/*
		- Sets the pointer to the event effect function.
		*/
		void set_event_effect(eventEffectType eventEffect);

		/*
		- Sets the attribute 'defaultConditionArgs' as a copy of the given map.
		*/
		void set_default_condition_args(
			std::map<std::string, void*> &defaultConditionArgs);

		/*
		- Sets the attribute 'defaultEffectArgs' as a copy of the given map.
		*/
		void set_default_effect_args(
			std::map<std::string, void*> &defaultEffectArgs);

		/*
		- Adds an argument to the default condition map.
		- If there is already an argument with that name, it's overwritten.
		*/
		void add_default_condition_argument(std::string argName,
			void *argValue);

		/*
		- Adds an argument to the default effect map.
		- If there is already an argument with that name, it's overwritten.
		*/
		void add_default_effect_argument(std::string argName, void *argValue);

		/*
		- If it exists, removes the argument with the given name from the
		default condition map.
		*/
		void remove_default_condition_argument(std::string argName);

		/*
		- If it exists, removes the argument with the given name from the
		default effect map.
		*/
		void remove_default_effect_argument(std::string argName);

		/*
		- Checks that the codition is fulfilled, and if so activates the effect.
		- The method receives up to two argument maps, to be passed on to the
		condition and effect methods respectively.
		*/
		void activate(std::map<std::string, void*> &conditionArgs =
			std::map<std::string, void*>::map<std::string, void*>(),
			std::map<std::string, void*> &effectArgs =
			std::map<std::string, void*>::map<std::string, void*>());
	};

	
	/*
	- A layout (a series of slots where elements can be allocated).
	- The position and size of slots in a free layout are not restricted by
	the bounds of the layout content. Slots can overlap.
	- By default, newly added elements keep their content bounds and alignment.
	- This class shouldn't be instanced, but serve as a base for other classes.
	*/
	class baseFreeLayout : public virtual baseElement
	{
	protected:
		
		/*
		- Vector storing the pointers to all the elements inside the layout.
		- Its size is the size of the layout (number of available slots).
		*/
		std::vector<baseElement*> elements;

		/*
		- Number of elements inside the layout (or number of full slots).
		- Always less than or equal to the size of the layout.
		*/
		int elementCount;
		
		/*
		- Position of the lowest empty slot in the 'elements' vector.
		- Technically, the first null position in 'elements'.
		- If a layout has no elements, its value is 0.
		*/
		int lowestEmptySlot;
		
		/*
		- Position of the highest full slot in the 'elements' vector.
		- Technically, the last non-null position in 'elements'.
		- If a layout has no elements, its value is -1.
		*/
		int highestFullSlot;

		/*
		- Alignment on X of newly added elements will be changed to this value.
		- Valid values are 'ALIGNMENT::none', 'ALIGNMENT::left',
		'ALIGNMENT::right', 'ALIGNMENT::center', and 'ALIGNMENT::keep'.
		- 'ALIGNMENT::keep' causes newly added elements to retain their values.
		*/
		int defaultAlignmentX;

		/*
		- Alignment on Y of newly added elements will be changed to this value.
		- Valid values are 'ALIGNMENT::none', 'ALIGNMENT::top',
		'ALIGNMENT::bottom', 'ALIGNMENT::center', and 'ALIGNMENT::keep'.
		- 'ALIGNMENT::keep' causes newly added elements to retain their values.
		*/
		int defaultAlignmentY;
		
		/*
		- If 'true', adding elements in slots greater than the layout's size
		will cause the layout to be resized to fit them.
		- If 'false', those elements cannot be added.
		*/
		bool elastic;

		/*
		- Recalculates the position and size of an element's slot given its
		position inside the 'elements' vector.
		- In this case (free layout) it does nothing.
		- Can be redefined in derived classes.
		*/
		virtual void recalculateSlotBounds(baseElement &element);

		/*
		- Calls 'recalculateSlotBounds' for every element in the layout.
		*/
		void recalculateAllSlotBounds();

		/*
		- Calls the 'draw' method of every element in the layout.
		- Non-visible elements are excluded.
		- Elements are drawn in order of greater to lesser depth.
		*/
		void drawContent();

	public:

		/*
		- Default constructor.
		- The layout is initially empty.
		*/
		baseFreeLayout(int size = 0, int defaultAlignmentX = ALIGNMENT::left,
			int defaultAlignmentY = ALIGNMENT::top, bool elastic = true);

		/*
		- Default destructor.
		*/
		virtual ~baseFreeLayout();

		/*
		- Returns the size of the layout (i.e. that of the 'elements' vector).
		*/
		int get_size();

		/*
		- Returns the value of the attribute 'elementCount'.
		*/
		int get_element_count();
		
		/*
		- Returns the value of the attribute 'lowestEmptySlot'.
		*/
		int get_lowest_empty_slot();
		
		/*
		- Returns the value of the attribute 'highestFullSlot'.
		*/
		int get_highest_full_slot();
		
		/*
		- Returns the value of the attribute 'defaultAlignmentX'.
		*/
		int get_default_alignment_x();

		/*
		- Returns the value of the attribute 'defaultAlignmentY'.
		*/
		int get_default_alignment_y();

		/*
		- Returns the value of the attribute 'elastic'.
		*/
		bool get_elasticity();
		
		/*
		- Returns 'true' if the given slot (a position in 'elements') has
		an element, or 'false' if it's empty.
		*/
		bool is_slot_full(int slotNumber);
		
		/*
		- Returns a pointer to the element in the specified slot, or null if
		it's empty.
		- Can be redefined in derived classes.
		*/
		virtual baseElement* get_element(int slotNumber);

		/*
		- Returns a copy of the 'elements' vector.
		*/
		std::vector<baseElement*> get_elements();

		/*
		- Changes the position of the layout's content.
		- Position and size of slots inside the layout are recalculated
		(relevant for derived classes).
		*/
		void set_content_position(float contentPosX, float contentPosY);

		/*
		- Changes the size of the layout's content.
		- Position and size of slots inside the layout are recalculated
		(relevant for derived classes).
		*/
		void set_content_size(float contentWidth, float contentHeight);
		
		/*
		- Resizes the layout (i.e. resizes the 'elements' vector).
		- If the value changes, position and size of slots inside the layout are
		recalculated (relevant for derived classes).
		*/
		virtual void set_size(int size);

		/*
		- Sets the attribute 'defaultAlignmentX'.
		- Invalid values leave it unchanged.
		*/
		void set_default_alignment_x(int defaultAlignmentX);

		/*
		- Sets the attribute 'defaultAlignmentY'.
		- Invalid values leave it unchanged.
		*/
		void set_default_alignment_y(int defaultAlignmentY);

		/*
		- Sets the default alignment of the layout for both axis.
		*/
		void set_default_alignment(int defaultAlignmentX,
			int defaultAlignmentY);
		
		/*
		- Sets the attribute 'elastic'.
		*/
		void set_elasticity(bool elasticity);

		/*
		- Recursively changes content position and size of every element inside
		the layout, so they exactly match those of their slot.
		*/
		void r_match_content_to_slot();

		/*
		- Recursively changes slot position and size of every element inside
		the layout, so they exactly match those of their slot.
		*/
		void r_match_slot_to_content();

		/*
		- Recursively aligns the layout and every element inside it in
		accordance to their attributes.
		*/
		void r_align();

		/*
		- Recursively aligns the layout and every element inside it in
		accordance to the parameters.
		*/
		void r_align(int alignmentX, int alignmentY);
		
		/*
		- Copies the current layout's attributes into the received one.
		- Elements inside are not copied (the layout keeps its elements if any).
		- Can be redefined in derived classes.
		*/
		virtual void copy(baseFreeLayout &layout);
		
		/*
		- Copies the current layout's attributes into the received one.
		- Elements inside are also recursively cloned. Any existing pointers in
		the received layout are lost.
		- Can be redefined in derived classes.
		*/
		virtual void r_copy(baseFreeLayout &layout);

		/*
		- Returns a pointer to the element in the layout (or in a sublayout)
		with the given id.
		- If no element with that id is found, the return value is 0.
		- Can be redefined in derived classes.
		*/
		virtual baseElement* find_element(int elementId);

		/*
		- Returns a pointer to the element in the layout (or in a sublayout)
		with the given name.
		- If no element with that name is found, the return value is 0.
		- Can be redefined in derived classes.
		*/
		virtual baseElement* find_element(std::string elementName);
		
		/*
		- Adds a given element to the layout at the lowest free slot.
		- If the slot is full, the old element is removed (but not deleted).
		- If the element already has a parent layout, nothing happens.
		- Can be redefined in derived classes.
		*/
		virtual void add_element(baseElement &element);
		
		/*
		- Adds a given element to the layout at the specified slot.
		- If the slot is full, the old element is removed (but not deleted).
		- If the element already has a parent layout, nothing happens.
		- Can be redefined in derived classes.
		*/
		virtual void add_element(baseElement &element, int slotNumber);
		
		/*
		- Removes an element from the layout at the given slot and returns it.
		- This doesn't delete the element, just the layout's pointer to it.
		- Returns 0 if the slot is invalid, or if it's empty.
		- Can be redefined in derived classes.
		*/
		virtual baseElement* remove_element(int slotNumber);

		/*
		- Removes an element from the layout (or from a sublayout), if present.
		- Can be redefined in derived classes.
		*/
		virtual void remove_element(baseElement &element);
		
		/*
		- Recursively deletes the layout and every element inside it.
		*/
		void r_delete();
	};


	/*
	- A layout (a series of slots where elements can be allocated).
	- Elements in an horizontal layout are drawn from left to right.
	- Slots are assigned an equal share of horizontal space, and full vertical
	space (relative to the layout content's height and width).
	- By default, newly added elements change their alignment to top-left.
	- This class shouldn't be instanced, but serve as a base for other classes.
	*/
	class baseHorizontalLayout : public virtual baseFreeLayout
	{
	protected:

		/*
		- Recalculates the position and size of an element's slot given its
		position inside the 'elements' vector.
		*/
		void recalculateSlotBounds(baseElement &element);

	public:

		/*
		- Default constructor.
		*/
		baseHorizontalLayout();

		/*
		- Default destructor.
		*/
		virtual ~baseHorizontalLayout();
	};

	
	/*
	- A layout (a series of slots where elements can be allocated).
	- Elements in a vertical layout are drawn from top to bottom.
	- Slots are assigned an equal share of vertical space, and full horizontal
	space (relative to the layout content's width and height).
	- By default, newly added elements change their alignment to top-left.
	- This class shouldn't be instanced, but serve as a base for other classes.
	*/
	class baseVerticalLayout : public virtual baseFreeLayout
	{
	protected:

		/*
		- Recalculates the position and size of an element's slot given its
		position inside the 'elements' vector.
		*/
		void recalculateSlotBounds(baseElement &element);

	public:

		/*
		- Default constructor.
		*/
		baseVerticalLayout();

		/*
		- Default destructor.
		*/
		virtual ~baseVerticalLayout();
	};


	/*
	- A layout (a series of slots where elements can be allocated).
	- Elements in a table layout are positioned from left to right until a row
	is full, then start a new row from top to bottom.
	- The width of the layout's content is distributed equally between the slots
	in each row, so does its height with the slots in each column.
	- By default, newly added elements change their alignment to top-left.
	- A table layout can't be elastic.
	- This class shouldn't be instanced, but serve as a base for other classes.
	*/
	class baseTableLayout : public virtual baseFreeLayout
	{
	private:

		/*
		- The method for turning on elasticity is hidden.
		*/
		using baseFreeLayout::set_elasticity;

	protected:

		/*
		- The number of rows between which the content height will be divided
		(also the number of slots per column).
		- Can't be negative.
		*/
		int numberOfRows;

		/*
		- The number of columns between which the content width will be divided
		(also the number of slots per row).
		- Can't be negative.
		*/
		int numberOfColumns;

		/*
		- Recalculates the position and size of an element's slot given its
		position inside the 'elements' vector.
		*/
		void recalculateSlotBounds(baseElement &element);

	public:

		/*
		- Default constructor.
		*/
		baseTableLayout(int numberOfRows = 0, int numberOfColumns = 0);

		/*
		- Default destructor.
		*/
		virtual ~baseTableLayout();

		/*
		- Returns the value of the attribute 'numberOfRows'.
		*/
		int get_number_of_rows();

		/*
		- Returns the value of the attribute 'numberOfColumns'.
		*/
		int get_number_of_columns();

		/*
		- For the original overload of 'is_slot_full'.
		*/
		using baseFreeLayout::is_slot_full;

		/*
		- Calls 'is_slot_full' translating row and column to slot number.
		*/
		bool is_slot_full(int row, int column);
		
		/*
		- For the original overload of 'get_element'.
		*/
		using baseFreeLayout::get_element;

		/*
		- Calls 'get_element' translating row and column to slot number.
		- Can be redefined in derived classes.
		*/
		virtual baseElement* get_element(int row, int column);

		/*
		- Sets the attribute 'numberOfRows'.
		- If the value changes, position and size of slots inside the layout are
		recalculated.
		*/
		void set_number_of_rows(int numberOfRows);

		/*
		- Sets the attribute 'numberOfColumns'.
		- If the value changes, position and size of slots inside the layout are
		recalculated.
		*/
		void set_number_of_columns(int numberOfColumns);

		/*
		- Sets the attributes 'numberOfRows' and 'numberOfColumns'.
		- If one or both values change, position and size of slots inside the
		layout are recalculated.
		- Hides the method 'set_size(int size)' from 'freeLayout'.
		*/
		void set_size(int numberOfRows, int numberOfColumns);

		/*
		- Copies the current layout's attributes into the received one.
		- Elements inside are not copied (the layout keeps its elements if any).
		- Can be redefined in derived classes.
		*/
		virtual void copy(baseTableLayout &layout);
		
		/*
		- Copies the current layout's attributes into the received one.
		- Elements inside are also recursively cloned. Any existing pointers in
		the received layout are lost.
		- Can be redefined in derived classes.
		*/
		virtual void r_copy(baseTableLayout &layout);

		/*
		- For the original overloads of 'add_element'.
		*/
		using baseFreeLayout::add_element;

		/*
		- Calls 'add_element' translating row and column to slot number.
		- Can be redefined in derived classes.
		*/
		virtual void add_element(baseElement &element, int row, int column);

		/*
		- For the original overload of 'remove_element'.
		*/
		using baseFreeLayout::remove_element;

		/*
		- Calls 'remove_element' translating row and column to slot number.
		- Can be redefined in derived classes.
		*/
		virtual baseElement* remove_element(int row, int column);
	};


	/*
	- When trying to handle event conditions and effects, only generic functions
	can be directly assigned.
	- In order to assign class methods, it's necessary to either make those
	methods static, or to use global wrappers, plus a global pointer to a class
	instance.
	- This situation is described in greater detail in C++ FAQ 33.1 and 33.2
	(http://www.parashift.com/c++-faq-lite/fnptr-vs-memfnptr-types.html).
	*/

	/*
	- Next there are some generic functions commonly used as event conditions.
	*/

	/*
	- Returns true if the given position is within the element's content frame.
	- Required arguments ("argument_name" (argument_value_type): description):
		- "element" (baseElement*): the target element.
		- "posX" (float*): the target position on the X axis.
		- "posY" (float*): the target position on the Y axis.
	*/
	bool position_inside_content_frame(std::map<std::string, void*> &args);

	/*
	- Returns true if the given position is within the element's slot frame.
	- Required arguments ("argument_name" (argument_value_type): description):
		- "element" (baseElement*): the target element.
		- "posX" (float*): the target position on the X axis.
		- "posY" (float*): the target position on the Y axis.
	*/
	bool position_inside_slot_frame(std::map<std::string, void*> &args);

};


#endif

