#ifndef LAYOUT_HPP
#define LAYOUT_HPP

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
	- An element that can be part of a layout.
	- Elements can (should) have content. To be defined in derived classes.
	- Elements can fit in slots (the sapce a layout reserves for them).
	- Content is allowed to fall outside of slot limits. It's up to derived
	classes to manage that appropriately.
	*/
	class element
	{
	protected:

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
		*/
		int depth;

		/*
		- A 'false' value prevents the element from being displayed.
		- Even if 'true', the element may still be hidden due to other factors.
		*/
		bool visible;

	public:

		/*
		- Default constructor.
		*/
		element(float contentPosX = 0, float contentPosY = 0,
			float contentWidth = 0, float contentHeight = 0, float slotPosX = 0,
			float slotPosY = 0, float slotWidth = 0, float slotHeight = 0,
			int alignmentX = ALIGNMENT::none, int alignmentY = ALIGNMENT::none,
			int depth = 0, bool visible = true);
		
		/*
		- Default destructor.
		*/
		virtual ~element();
		
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
		- Returns the attribute 'visible'.
		*/
		bool get_visibility();

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
		- Updates the slot's size and position to match the content's.
		*/
		void match_slot_to_content();

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
		- Sets both alignment attributes and calls the 'align()' method.
		- Invalid values align the content according to the existing alignment.
		*/
		void align(int alignmentX, int alignmentY);

		/*
		- Sets the attribute 'depth'.
		*/
		void set_depth(int depth);

		/*
		- Sets the attribute 'visible'.
		*/
		void set_visibility(bool visible);
		
		/*
		- Creates a copy of the current element in a new instance.
		- Should be replicated in derived classes for their type.
		*/
		element* copy();
		
		/*
		- Creates a copy of the current element in a new instance.
		- Should be replicated in derived classes for their type.
		*/
		element* copy_in_cascade();
		
		/*
		- Makes the received element into a copy of the current element.
		- Should be replicated in derived classes for their type.
		*/
		void copy(element* newElement);
		
		/*
		- Makes the received element into a copy of the current element.
		- Should be replicated in derived classes for their type.
		*/
		void copy_in_cascade(element* newElement);
		
		/*
		- Calls the default destructor.
		- Can be redefined in derived classes.
		*/
		virtual void delete_in_cascade();

		/*
		- Does nothing.
		- Can be redefined in derived classes.
		*/
		virtual void draw();
	};
	
	
	/*
	- A layout (a series of slots where elements can be allocated).
	- The position and size of slots in a free layout are not restricted by
	those of the layout's content, or their number. Slots can overlap.
	- By default, newly added elements keep their alignment values.
	*/
	class freeLayout : public element
	{
	protected:

		/*
		- Number of slots in the layout.
		- Can't be negative.
		- Most types of layout use it to distribute the space among slots.
		- Elements in equal or higher slot positions won't be displayed.
		*/
		int numberOfSlots;

		/*
		- Size of the array 'elementsArray'.
		- Not tied to 'numberOfSlots' attribute, as elements can exist in higher
		slots than the size of the displayable layout.
		*/
		int arraySize;
		
		/*
		- Number of elements inside the layout (or number of full slots).
		- Can be bigger than 'numberOfSlots' if there are full slots above it.
		*/
		int elementCount;
		
		/*
		- Position of the lowest empty slot in the layout.
		- Technically, the first null position in 'elementsArray'.
		- If a layout has no elements, its value is 0.
		*/
		int lowestEmptySlot;
		
		/*
		- Position of the highest full slot in the layout.
		- Technically, the last non-null position in 'elementsArray'.
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
		- Activation status of the default display mode.
		- The default display draws elements up to the highest full slot.
		*/
		bool defaultDisplay;
		
		/*
		- Array storing the pointers to all the elements inside the layout.
		*/
		element** elementsArray;
		
		/*
		- Creates a new 'elementsArray' with the specified size, and copies the
		existing elements into it.
		- Generally called for incrementing it, to avoid losing references.
		- Can be redefined in derived classes.
		*/
		virtual void resizeArrays(int newArraySize);

		/*
		- Recalculates the position and size of an element's slot given its
		slot number in the layout.
		- In this case (free layout) it does nothing.
		- Can be redefined in derived classes.
		*/
		virtual void recalculateSlot(int slot, element *element);

		/*
		- Recalculates the slot position and size of every element inside the
		layout up to 'numberOfSlots' - 1.
		*/
		void recalculateSlots();

	public:

		/*
		- Default constructor.
		- The layout is initially empty and 'elementsArray' has size 1.
		*/
		freeLayout(float contentPosX = 0, float contentPosY = 0,
			float contentWidth = 0, float contentHeight = 0, float slotPosX = 0,
			float slotPosY = 0, float slotWidth = 0, float slotHeight = 0,
			int alignmentX = ALIGNMENT::none, int alignmentY = ALIGNMENT::none,
			int depth = 0, bool visible = true,
			int defaultAlignmentX = ALIGNMENT::left,
			int defaultAlignmentY = ALIGNMENT::top, bool defaultDisplay = true,
			int numberOfSlots = 0);

		/*
		- Default destructor.
		*/
		virtual ~freeLayout();

		/*
		- Returns the value of the attribute 'numberOfSlots'.
		*/
		int get_number_of_slots();

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
		- Returns the value of the attribute 'defaultDisplay'.
		*/
		bool get_default_display();
		
		/*
		- Returns 'true' if the given slot (a position in 'elementsArray') has
		an element, or 'false' if it's empty.
		*/
		bool is_slot_full(int slot);
		
		/*
		- Returns a pointer to the element in the specified slot, or null if
		it's empty.
		*/
		element* get_element(int slot);
		
		/*
		- Returns the element in the slot by the given position (or null if there
		is none), and removes it from the layout.
		*/
		element* extract_element(int slot);

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
		- Sets the default alignment of the layout for both axis.
		*/
		void set_default_alignment(int defaultAlignmentX,
			int defaultAlignmentY);
		
		/*
		- Sets the attribute 'numberOfSlots'.
		- Only works if the default display mode is off.
		- If the value changes, position and size of slots inside the layout are
		recalculated (relevant for derived classes).
		*/
		virtual void set_number_of_slots(int numberOfSlots);
		
		/*
		- Sets the attribute 'defaultDisplay'.
		- Turning on the default display mode will also modify the layout's number of
		slots appropriately.
		*/
		void set_default_display(bool slotsDisplayed);

		/*
		- Aligns every element inside the layout according to its attributes.
		*/
		void align_all_elements();

		/*
		- Aligns every element inside the layout according to the parameters.
		*/
		void align_all_elements(int alignmentX, int alignmentY);
		
		/*
		- Creates a copy of the current layout in a new instance.
		- Elements inside are not copied, and both layouts share the same
		references. This can cause unexpected bahaviours if one of the two is
		modified or deleted in cascade afterwards.
		- Should be replicated in derived classes for their type.
		*/
		freeLayout* copy();
		
		/*
		- Creates a copy of the current layout in a new instance.
		- Elements inside are also recursively copied, which makes them safe to
		modify, but the memory must later be freed separately.
		- Should be replicated in derived classes for their type.
		*/
		freeLayout* copy_in_cascade();
		
		/*
		- Makes 'newLayout' into a copy of the current layout.
		- Elements inside are not copied, and both layouts share the same
		references. This can cause unexpected bahaviours if one of the two is
		modified or deleted in cascade afterwards.
		- Should be replicated in derived classes for their type.
		*/
		void copy(freeLayout* newLayout);
		
		/*
		- Makes 'newLayout' into a copy of the current layout.
		- Elements inside are also recursively copied, which makes them safe to
		modify, but the memory must later be freed separately.
		- Should be replicated in derived classes for their type.
		*/
		void copy_in_cascade(freeLayout* newLayout);
		
		/*
		- Adds a given element to the layout at the lowest free slot.
		- If the slot is full, the old element is removed (but not deleted).
		- If the slot is higher than 'arraySize', the array is resized.
		*/
		void add_element(element* newElement);
		
		/*
		- Adds a given element to the layout at the specified slot.
		- If the slot is full, the old element is removed (but not deleted).
		- If the slot is higher than 'arraySize', the array is resized.
		- Can be redefined in derived classes.
		*/
		void add_element(element* newElement, int slot);
		
		/*
		- Removes an element from the layout at the specified slot.
		- This doesn't delete the element, just the layout's reference to it.
		*/
		void remove_element(int slot);
		
		/*
		- Removes and deletes an element from the layout at the specified slot.
		- Only to be called if the element won't be used again.
		*/
		void delete_element(int slot);
		
		/*
		- Removes an element from the layout, and recursively deletes it and all
		elements inside it (if any), at the specified slot.
		- Only to be called if the element (as well as those inside it) won't be
		used again.
		*/
		void delete_element_in_cascade(int slot);
		
		/*
		- Recursively deletes the layout and all elements elements inside it.
		- Only to be called if the layout (and inside elements) won't be used
		again.
		- Can be redefined in derived classes.
		*/
		virtual void delete_in_cascade();

		/*
		- Calls the 'draw' method of every element in the layout below 'size'.
		- This includes non-visible elements, which should be handled inside
		their classes' draw methods.
		- Elements are drawn in order of greater to lesser depth.
		- Can be redefined in derived classes.
		*/
		virtual void draw();
	};


	/*
	- A layout (a series of slots where elements can be allocated).
	- Elements in an horizontal layout are drawn from left to right.
	- Slots up to 'numberOfSlots' - 1 are assigned proportional horizontal
	space, and vertical space equal to the height of the layout's content.
	- By default, newly added elements change their alignment to top-left.
	*/
	class horizontalLayout : public freeLayout
	{
	protected:

		/*
		- Recalculates the position and size of an element's slot given its
		slot number in the layout.
		*/
		void recalculateSlot(int slot, element *element);

	public:

		/*
		- Default constructor.
		*/
		horizontalLayout(float contentPosX = 0, float contentPosY = 0,
			float contentWidth = 0, float contentHeight = 0, float slotPosX = 0,
			float slotPosY = 0, float slotWidth = 0, float slotHeight = 0,
			int alignmentX = ALIGNMENT::none, int alignmentY = ALIGNMENT::none,
			int depth = 0, bool visible = true,
			int defaultAlignmentX = ALIGNMENT::left,
			int defaultAlignmentY = ALIGNMENT::top, bool defaultDisplay = true,
			int numberOfSlots = 0);

		/*
		- Default destructor.
		*/
		virtual ~horizontalLayout();

		/*
		- Creates a copy of the current layout in a new instance.
		- Elements inside are not copied, and both layouts share the same
		references. This can cause unexpected bahaviours if one of the two is
		modified or deleted in cascade afterwards.
		- Should be redefined in derived classes.
		*/
		horizontalLayout* copy();
		
		/*
		- Creates a copy of the current layout in a new instance.
		- Elements inside are also recursively copied, which makes them safe to
		modify, but the memory must later be freed separately.
		- Should be redefined in derived classes.
		*/
		horizontalLayout* copy_in_cascade();
		
		/*
		- Makes 'newLayout' into a copy of the current layout.
		- Elements inside are not copied, and both layouts share the same
		references. This can cause unexpected bahaviours if one of the two is
		modified or deleted in cascade afterwards.
		- Should be redefined in derived classes.
		*/
		void copy(horizontalLayout* newLayout);
		
		/*
		- Makes 'newLayout' into a copy of the current layout.
		- Elements inside are also recursively copied, which makes them safe to
		modify, but the memory must later be freed separately.
		- Should be redefined in derived classes.
		*/
		void copy_in_cascade(horizontalLayout* newLayout);
	};

	
	/*
	- A layout (a series of slots where elements can be allocated).
	- Elements in a vertical layout are drawn from top to bottom.
	- Slots up to 'numberOfSlots' - 1 are assigned proportional vertical space,
	and horizontal space equal to the width of the layout's content.
	- By default, newly added elements change their alignment to top-left.
	*/
	class verticalLayout : public freeLayout
	{
	protected:

		/*
		- Recalculates the position and size of an element's slot given its
		slot number in the layout.
		*/
		void recalculateSlot(int slot, element *element);

	public:

		/*
		- Default constructor.
		*/
		verticalLayout(float contentPosX = 0, float contentPosY = 0,
			float contentWidth = 0, float contentHeight = 0, float slotPosX = 0,
			float slotPosY = 0, float slotWidth = 0, float slotHeight = 0,
			int alignmentX = ALIGNMENT::none, int alignmentY = ALIGNMENT::none,
			int depth = 0, bool visible = true,
			int defaultAlignmentX = ALIGNMENT::left,
			int defaultAlignmentY = ALIGNMENT::top, bool defaultDisplay = true,
			int numberOfSlots = 0);

		/*
		- Default destructor.
		*/
		~verticalLayout();

		/*
		- Creates a copy of the current layout in a new instance.
		- Elements inside are not copied, and both layouts share the same
		references. This can cause unexpected bahaviours if one of the two is
		modified or deleted in cascade afterwards.
		- Should be redefined in derived classes.
		*/
		verticalLayout* copy();
		
		/*
		- Creates a copy of the current layout in a new instance.
		- Elements inside are also recursively copied, which makes them safe to
		modify, but the memory must later be freed separately.
		- Should be redefined in derived classes.
		*/
		verticalLayout* copy_in_cascade();
		
		/*
		- Makes 'newLayout' into a copy of the current layout.
		- Elements inside are not copied, and both layouts share the same
		references. This can cause unexpected bahaviours if one of the two is
		modified or deleted in cascade afterwards.
		- Should be redefined in derived classes.
		*/
		void copy(verticalLayout* newLayout);
		
		/*
		- Makes 'newLayout' into a copy of the current layout.
		- Elements inside are also recursively copied, which makes them safe to
		modify, but the memory must later be freed separately.
		- Should be redefined in derived classes.
		*/
		void copy_in_cascade(verticalLayout* newLayout);
	};


	/*
	- A layout (a series of slots where elements can be allocated).
	- Elements in a table layout are drawn from left to right until a row is
	full, then start a new row from top to bottom.
	- The width of the layout's content is distributed equally between the slots
	in each row, so does its height with the slots in each column.
	- By default, newly added elements change their alignment to top-left.
	- A table layout doesn't have default display mode. The number of rows and
	colums must be specified.
	*/
	class tableLayout : public freeLayout
	{
	private:

		/*
		- The method for turning on the default alignment is hidden.
		*/
		using freeLayout::set_default_display;

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
		slot number in the layout.
		*/
		void recalculateSlot(int slot, element *element);

	public:

		/*
		- Default constructor.
		*/
		tableLayout(float contentPosX = 0, float contentPosY = 0,
			float contentWidth = 0, float contentHeight = 0, float slotPosX = 0,
			float slotPosY = 0, float slotWidth = 0, float slotHeight = 0,
			int alignmentX = ALIGNMENT::none, int alignmentY = ALIGNMENT::none,
			int depth = 0, bool visible = true,
			int defaultAlignmentX = ALIGNMENT::left,
			int defaultAlignmentY = ALIGNMENT::top,  int numberOfRows = 0,
			int numberOfColumns = 0);

		/*
		- Default destructor.
		*/
		~tableLayout();

		/*
		- Returns the value of the attribute 'numberOfRows'.
		*/
		int get_number_of_rows();

		/*
		- Returns the value of the attribute 'numberOfColumns'.
		*/
		int get_number_of_columns();

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
		- If any value changes, position and size of slots inside the layout are
		recalculated.
		- This method hides the inherited 'set_number_of_slots()'.
		*/
		void set_number_of_slots(int numberOfRows, int numberOfColumns);

		/*
		- Creates a copy of the current layout in a new instance.
		- Elements inside are not copied, and both layouts share the same
		references. This can cause unexpected bahaviours if one of the two is
		modified or deleted in cascade afterwards.
		- Should be redefined in derived classes.
		*/
		tableLayout* copy();
		
		/*
		- Creates a copy of the current layout in a new instance.
		- Elements inside are also recursively copied, which makes them safe to
		modify, but the memory must later be freed separately.
		- Should be redefined in derived classes.
		*/
		tableLayout* copy_in_cascade();
		
		/*
		- Makes 'newLayout' into a copy of the current layout.
		- Elements inside are not copied, and both layouts share the same
		references. This can cause unexpected bahaviours if one of the two is
		modified or deleted in cascade afterwards.
		- Should be redefined in derived classes.
		*/
		void copy(tableLayout* newLayout);
		
		/*
		- Makes 'newLayout' into a copy of the current layout.
		- Elements inside are also recursively copied, which makes them safe to
		modify, but the memory must later be freed separately.
		- Should be redefined in derived classes.
		*/
		void copy_in_cascade(tableLayout* newLayout);
	};


};

#endif

