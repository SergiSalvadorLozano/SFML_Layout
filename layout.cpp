#include "layout.hpp"
#include <iostream>

using namespace LAYOUT;


/* CLASS element */


element::element(float contentPosX, float contentPosY, float contentWidth,
	float contentHeight, float slotPosX, float slotPosY, float slotWidth,
	float slotHeight, int alignmentX, int alignmentY, int depth, bool visible)
{
	if (contentWidth < 0)
		contentWidth = 0;
	if (contentHeight < 0)
		contentHeight = 0;
	if (slotWidth < 0)
		slotWidth = 0;
	if (slotHeight < 0)
		slotHeight = 0;
	if (alignmentX != ALIGNMENT::none && alignmentX != ALIGNMENT::left &&
		alignmentX != ALIGNMENT::right && alignmentX != ALIGNMENT::center)
		alignmentX = ALIGNMENT::none;
	if (alignmentY != ALIGNMENT::none && alignmentY != ALIGNMENT::top &&
		alignmentY != ALIGNMENT::bottom && alignmentY != ALIGNMENT::center)
		alignmentY = ALIGNMENT::none;

	this->contentPosX = contentPosX;
	this->contentPosY = contentPosY;
	this->contentWidth = contentWidth;
	this->contentHeight = contentHeight;
	this->slotPosX = slotPosX;
	this->slotPosY = slotPosY;
	this->slotWidth = slotWidth;
	this->slotHeight = slotHeight;
	this->alignmentX = alignmentX;
	this->alignmentY = alignmentY;
	this->depth = depth;
	this->visible = visible;
	align();
}


element::~element()
{
}


float element::get_content_position_x()
{
	return contentPosX;
}


float element::get_content_position_y()
{
	return contentPosY;
}


float element::get_content_width()
{
	return contentWidth;
}


float element::get_content_height()
{
	return contentHeight;
}


float element::get_slot_position_x()
{
	return contentPosX;
}


float element::get_slot_position_y()
{
	return contentPosY;
}


float element::get_slot_width()
{
	return contentWidth;
}


float element::get_slot_height()
{
	return contentHeight;
}


int element::get_alignment_x()
{
	return alignmentX;
}


int element::get_alignment_y()
{
	return alignmentY;
}


int element::get_depth()
{
	return depth;
}


bool element::get_visibility()
{
	return visible;
}


void element::set_content_position(float contentPosX, float contentPosY)
{
	this->contentPosX = contentPosX;
	this->contentPosY = contentPosY;
}


void element::set_content_size(float contentWidth, float contentHeight)
{
	if (contentWidth >= 0)
		this->contentWidth = contentWidth;
	if (contentHeight >= 0)
		this->contentHeight = contentHeight;
	align();
}


void element::set_slot_position(float slotPosX, float slotPosY)
{
	this->slotPosX = slotPosX;
	this->slotPosY = slotPosY;
	align();
}


void element::set_slot_size(float slotWidth, float slotHeight)
{
	if (slotWidth >= 0)
		this->slotWidth = slotWidth;
	if (slotHeight >= 0)
		this->slotHeight = slotHeight;
	align();
}


void element::match_content_to_slot()
{
	set_content_position(slotPosX, slotPosY);
	set_content_size(slotWidth, slotHeight);
}


void element::match_slot_to_content()
{
	set_slot_position(contentPosX, contentPosY);
	set_slot_size(contentWidth, contentHeight);
}


void element::set_alignment(int alignmentX, int alignmentY)
{
	if (alignmentX == ALIGNMENT::none || alignmentX == ALIGNMENT::left ||
		alignmentX == ALIGNMENT::right || alignmentX == ALIGNMENT::center)
		this->alignmentX = alignmentX;
	if (alignmentY == ALIGNMENT::none || alignmentY == ALIGNMENT::top ||
		alignmentY == ALIGNMENT::bottom || alignmentY == ALIGNMENT::center)
		this->alignmentY = alignmentY;
}


void element::align()
{
	float newContentPosX = contentPosX;
	float newContentPosY = contentPosY;

	if (alignmentX == ALIGNMENT::left)
		newContentPosX = slotPosX;
	else if (alignmentX == ALIGNMENT::right)
		newContentPosX = slotPosX + slotWidth - contentWidth;
	else if (alignmentX == ALIGNMENT::center)
		newContentPosX = slotPosX + (slotWidth - contentWidth) / 2;

	if (alignmentY == ALIGNMENT::top)
		newContentPosY = slotPosY;
	else if (alignmentY == ALIGNMENT::bottom)
		newContentPosY = slotPosY + slotHeight - contentHeight;
	else if (alignmentY == ALIGNMENT::center)
		newContentPosY = slotPosY + (slotHeight - contentHeight) / 2;

	set_content_position(newContentPosX, newContentPosY);
}


void element::align(int alignmentX, int alignmentY)
{
	set_alignment(alignmentX, alignmentY);
	align();
}


void element::set_depth(int depth)
{
	this->depth = depth;
}


void element::set_visibility(bool visible)
{
	this->visible = visible;
}


element* element::copy()
{
	element* newElement = new element();
	copy(newElement);
	return newElement;
}


element* element::copy_in_cascade()
{
	element* newElement = new element();
	copy_in_cascade(newElement);
	return newElement;
}


void element::copy(element* newElement)
{
	if (newElement)
	{
		newElement->contentPosX = contentPosX;
		newElement->contentPosY = contentPosY;
		newElement->contentWidth = contentWidth;
		newElement->contentHeight = contentHeight;
		newElement->slotPosX = slotPosX;
		newElement->slotPosY = slotPosY;
		newElement->slotWidth = slotWidth;
		newElement->slotHeight = slotHeight;
		newElement->alignmentX = alignmentX;
		newElement->alignmentY = alignmentY;
		newElement->depth = depth;
		newElement->visible = visible;
	}
}


void element::copy_in_cascade(element* newElement)
{
	element::copy(newElement);
}


void element::delete_in_cascade()
{
	delete this;
}


void element::draw()
{
	std::cout << "CONTENT POSITION: X: " << contentPosX << ", Y: " << contentPosY << "." << std::endl;
	std::cout << "CONTENT SIZE: WIDTH: " << contentWidth << ", HEIGHT: " << contentHeight << "." << std::endl;
	std::cout << "SLOT POSITION: X: " << slotPosX << ", Y: " << slotPosY << "." << std::endl;
	std::cout << "SLOT SIZE: WIDTH: " << slotWidth << ", HEIGHT: " << slotHeight << "." << std::endl;
	std::cout << "ALIGNMENT: X: " << alignmentX << ", Y: " << alignmentY << "." << std::endl;
	std::cout << "DEPTH: " << depth << "." << std::endl;
}


/* CLASS freeLayout */


void freeLayout::resizeArrays(int newArraySize)
{
	if (newArraySize > 0){
		element** newElementsArray = new element* [newArraySize];
		for (int i = 0 ; i < arraySize ; i ++)
			newElementsArray[i] = elementsArray[i];
		for (int i = arraySize ; i < newArraySize ; i ++)
			newElementsArray[i] = 0;
		delete [] elementsArray;
		elementsArray = newElementsArray;
		arraySize = newArraySize;
	}
}


void freeLayout::recalculateSlot(int slot, element *element)
{
}


void freeLayout::recalculateSlots()
{
	for (int i = 0 ; i < numberOfSlots && i < arraySize ; i ++)
		if (elementsArray[i])
			recalculateSlot(i, elementsArray[i]);
}


freeLayout::freeLayout(float contentPosX, float contentPosY, float contentWidth,
	float contentHeight, float slotPosX, float slotPosY, float slotWidth,
	float slotHeight, int alignmentX, int alignmentY, int depth, bool visible,
	int defaultAlignmentX, int defaultAlignmentY, bool defaultDisplay,
	int numberOfSlots)
	: element(contentPosX, contentPosY, contentWidth, contentHeight, slotPosX,
	slotPosY, slotWidth, slotHeight, alignmentX, alignmentY, depth, visible)
{
	this->defaultAlignmentX = defaultAlignmentX;
	this->defaultAlignmentY = defaultAlignmentY;
	this->defaultDisplay = defaultDisplay;
	if (defaultDisplay || numberOfSlots < 0)
		this->numberOfSlots = 0;
	else
		this->numberOfSlots = numberOfSlots;
	elementCount = 0;
	arraySize = 1;
	lowestEmptySlot = 0;
	highestFullSlot = -1;
	elementsArray = new element* [arraySize];
	for (int i = 0 ; i < arraySize ; i ++)
		elementsArray[i] = 0;
}


freeLayout::~freeLayout()
{
	delete [] elementsArray;
}


int freeLayout::get_number_of_slots()
{
	return numberOfSlots;
}


int freeLayout::get_element_count()
{
	return elementCount;
}


int freeLayout::get_lowest_empty_slot()
{
	return lowestEmptySlot;
}


int freeLayout::get_highest_full_slot()
{
	return highestFullSlot;
}


int freeLayout::get_default_alignment_x()
{
	return defaultAlignmentX;
}


int freeLayout::get_default_alignment_y()
{
	return defaultAlignmentY;
}


bool freeLayout::get_default_display()
{
	return defaultDisplay;
}


bool freeLayout::is_slot_full(int slot)
{
	bool b = false;
	if (slot >= 0 && slot < arraySize)
		b = (elementsArray[slot] != 0);
	return b;
}


element* freeLayout::get_element(int slot)
{
	element* e = 0;
	if (slot >= 0 && slot < arraySize)
		e = elementsArray[slot];
	return e;
}


void freeLayout::draw()
{
	element::draw();
	std::cout << "DEFAULT ALIGNMENT: X: " << defaultAlignmentX << ", Y: "
		<< defaultAlignmentY << "." << std::endl;
	std::cout << "DEFAULT DISPLAY: " << defaultDisplay << ". NUMBER OF SLOTS: "
		<< numberOfSlots << "." << std::endl;
	std::cout << "ELEMENT COUNT: " << elementCount << std::endl;
	std::cout << "LOWEST_FREE_SLOT: " << lowestEmptySlot <<
		". HIGHEST FULL SLOT: " << highestFullSlot << "." << std::endl;

	std::cout << "{" << std::endl << std::endl;

	// First the interval of depths is calculated.
	int minDepth = std::numeric_limits<int>::max();
	int maxDepth = std::numeric_limits<int>::min();
	for (int i = 0 ; i < numberOfSlots && i < arraySize ; i ++)
		if (elementsArray[i] && elementsArray[i]->get_visibility())
		{
			if (elementsArray[i]->get_depth() < minDepth)
				minDepth = elementsArray[i]->get_depth();
			if (elementsArray[i]->get_depth() > maxDepth)
				maxDepth = elementsArray[i]->get_depth();
		}

	// Elements are drawn in iterations, from greater to lesser depth.
	for (int i = maxDepth ; i >= minDepth ; i --)
		for (int j = 0 ; j < numberOfSlots && j < arraySize ; j ++)
			if (elementsArray[j] && elementsArray[j]->get_depth() == i &&
				elementsArray[j]->get_visibility())
				{
					elementsArray[j]->draw();
					std::cout << std::endl;
				}

	std::cout << "}" << std::endl;
}


element* freeLayout::extract_element(int slot)
{
	element* e = 0;
	if (slot >=0 && slot < arraySize && elementsArray[slot])
	{
		e = elementsArray[slot];
		remove_element(slot);
	}
	return e;
}


void freeLayout::set_content_position(float contentPosX, float contentPosY)
{
	element::set_content_position(contentPosX, contentPosY);
	recalculateSlots();
}


void freeLayout::set_content_size(float contentWidth, float contentHeight)
{
	element::set_content_size(contentWidth, contentHeight);
	recalculateSlots();
}


void freeLayout::set_default_alignment(int defaultAlignmentX,
	int defaultAlignmentY)
{
	if (defaultAlignmentX == ALIGNMENT::none ||
		defaultAlignmentX == ALIGNMENT::left ||
		defaultAlignmentX == ALIGNMENT::right ||
		defaultAlignmentX == ALIGNMENT::center ||
		defaultAlignmentX == ALIGNMENT::keep)
		this->defaultAlignmentX = defaultAlignmentX;
	if (defaultAlignmentY == ALIGNMENT::none ||
		defaultAlignmentY == ALIGNMENT::top ||
		defaultAlignmentY == ALIGNMENT::bottom ||
		defaultAlignmentY == ALIGNMENT::center ||
		defaultAlignmentY == ALIGNMENT::keep)
		this->defaultAlignmentY = defaultAlignmentY;
}


void freeLayout::align_all_elements()
{
	for (int i = 0 ; i < arraySize ; i ++)
		if (elementsArray[i])
			elementsArray[i]->align();
}


void freeLayout::align_all_elements(int alignmentX, int alignmentY)
{
	for (int i = 0 ; i < arraySize ; i ++)
		if (elementsArray[i])
			elementsArray[i]->align(alignmentX, alignmentY);
}


freeLayout* freeLayout::copy()
{
	freeLayout* newLayout = new freeLayout();
	copy(newLayout);
	return newLayout;
}


freeLayout* freeLayout::copy_in_cascade()
{
	freeLayout* newLayout = new freeLayout();
	copy_in_cascade(newLayout);
	return newLayout;
}


void freeLayout::copy(freeLayout* newLayout)
{
	if (newLayout)
	{
		element::copy(dynamic_cast<element*>(newLayout));
		newLayout->freeLayout::resizeArrays(arraySize);
		for (int i = 0 ; i < arraySize ; i ++)
			newLayout->elementsArray[i] = elementsArray[i];
		newLayout->numberOfSlots = numberOfSlots;
		newLayout->elementCount = elementCount;
		newLayout->highestFullSlot = highestFullSlot;
		newLayout->lowestEmptySlot = lowestEmptySlot;
		newLayout->defaultAlignmentX = defaultAlignmentX;
		newLayout->defaultAlignmentY = defaultAlignmentY;
		newLayout->defaultDisplay = defaultDisplay;
	}
}


void freeLayout::copy_in_cascade(freeLayout* newLayout)
{
	if (newLayout)
	{
		element::copy_in_cascade(dynamic_cast<element*>(newLayout));
		newLayout->freeLayout::resizeArrays(arraySize);
		for (int i = 0 ; i < arraySize ; i ++)
			if (elementsArray[i])
			{
				element* elementCopy = elementsArray[i]->copy_in_cascade();
				newLayout->elementsArray[i] = elementCopy;
			}
		newLayout->numberOfSlots = numberOfSlots;
		newLayout->elementCount = elementCount;
		newLayout->highestFullSlot = highestFullSlot;
		newLayout->lowestEmptySlot = lowestEmptySlot;
		newLayout->defaultAlignmentX = defaultAlignmentX;
		newLayout->defaultAlignmentY = defaultAlignmentY;
		newLayout->defaultDisplay = defaultDisplay;
	}
}


void freeLayout::set_number_of_slots(int numberOfSlots)
{
	if (!defaultDisplay)
	{
		if (numberOfSlots >= 0)
			this->numberOfSlots = numberOfSlots;
		else
			this->numberOfSlots = 0;
		recalculateSlots();
	}
}


void freeLayout::set_default_display(bool defaultDisplay)
{
	if (defaultDisplay && !this->defaultDisplay)
	{
		numberOfSlots = highestFullSlot + 1;
		recalculateSlots();
	}
	this->defaultDisplay = defaultDisplay;
}


void freeLayout::add_element(element* newElement)
{
	add_element(newElement, lowestEmptySlot);
}


void freeLayout::add_element(element* newElement, int slot)
{
	if (slot >= arraySize)
	{
		int newArraySize;
		for (newArraySize = arraySize ; newArraySize <= slot ;
			newArraySize *= 2);
		resizeArrays(newArraySize);
	}
	if (slot >= 0 && newElement)
	{
		if (defaultAlignmentX != ALIGNMENT::keep)
			newElement->set_alignment(defaultAlignmentX, ALIGNMENT::keep);
		if (defaultAlignmentY != ALIGNMENT::keep)
			newElement->set_alignment(ALIGNMENT::keep, defaultAlignmentY);
		if (!elementsArray[slot])
			elementCount ++;
		elementsArray[slot] = newElement;
		while (lowestEmptySlot < arraySize && elementsArray[lowestEmptySlot])
			lowestEmptySlot ++;
		if (slot <= highestFullSlot || !defaultDisplay)
			// There won't be a global recalculation of the layout's slots.
			recalculateSlot(slot, newElement);
		if (slot > highestFullSlot)
		{
			highestFullSlot = slot;
			if (defaultDisplay)
			{
				// Slots of all elements will be recalculated.
				numberOfSlots = slot + 1;
				recalculateSlots();
			}
		}
	}
}


void freeLayout::remove_element(int slot)
{
	if (slot >=0 && slot < arraySize && elementsArray[slot])
	{
		elementsArray[slot] = 0;
		elementCount --;
		if (slot < lowestEmptySlot)
			lowestEmptySlot = slot;
		while (highestFullSlot >= 0 && !elementsArray[highestFullSlot])
			highestFullSlot --;
		if (slot > highestFullSlot && defaultDisplay)
		{
			// The removed element was in the highest full slot.
			numberOfSlots = highestFullSlot + 1;
			recalculateSlots();
		}
	}
}


void freeLayout::delete_element(int slot)
{
	if (slot >=0 && slot < arraySize && elementsArray[slot])
	{
		delete elementsArray[slot];
		remove_element(slot);
	}
}


void freeLayout::delete_element_in_cascade(int slot)
{
	if (slot >=0 && slot < arraySize && elementsArray[slot])
	{
		elementsArray[slot]->delete_in_cascade();
		remove_element(slot);
	}
}


void freeLayout::delete_in_cascade()
{
	for (int i = 0 ; i < arraySize ; i ++)
		if (elementsArray[i])
			elementsArray[i]->delete_in_cascade();
	delete this;
}


/* CLASS horizontalLayout */


void horizontalLayout::recalculateSlot(int slot, element* element)
{
	float slotsWidth = contentWidth / numberOfSlots;
	element->set_slot_position(contentPosX + slot * slotsWidth, contentPosY);
	element->set_slot_size(slotsWidth, contentHeight);
}


horizontalLayout::horizontalLayout(float contentPosX, float contentPosY,
	float contentWidth, float contentHeight, float slotPosX, float slotPosY,
	float slotWidth, float slotHeight, int alignmentX, int alignmentY,
	int depth, bool visible, int defaultAlignmentX, int defaultAlignmentY,
	bool defaultDisplay, int numberOfSlots)
	: freeLayout(contentPosX, contentPosY, contentWidth, contentHeight,
	slotPosX, slotPosY, slotWidth, slotHeight, alignmentX, alignmentY,
	depth, visible, defaultAlignmentX, defaultAlignmentY, defaultDisplay,
	numberOfSlots)
{
}


horizontalLayout::~horizontalLayout()
{
}


horizontalLayout* horizontalLayout::copy()
{
	horizontalLayout* newLayout = new horizontalLayout();
	copy(newLayout);
	return newLayout;
}


horizontalLayout* horizontalLayout::copy_in_cascade()
{
	horizontalLayout* newLayout = new horizontalLayout();
	copy_in_cascade(newLayout);
	return newLayout;
}


void horizontalLayout::copy(horizontalLayout* newLayout)
{
	freeLayout::copy(dynamic_cast<freeLayout*>(newLayout));
}


void horizontalLayout::copy_in_cascade(horizontalLayout* newLayout)
{
	freeLayout::copy_in_cascade(dynamic_cast<freeLayout*>(newLayout));
}


/* CLASS verticalLayout */


void verticalLayout::recalculateSlot(int slot, element* element)
{
	float slotsHeight = contentHeight / numberOfSlots; 
	element->set_slot_position(contentPosX, contentPosY + slot * slotsHeight);
	element->set_slot_size(contentWidth, slotsHeight);
}


verticalLayout::verticalLayout(float contentPosX, float contentPosY,
	float contentWidth, float contentHeight, float slotPosX, float slotPosY,
	float slotWidth, float slotHeight, int alignmentX, int alignmentY,
	int depth, bool visible, int defaultAlignmentX, int defaultAlignmentY,
	bool defaultDisplay, int numberOfSlots)
	: freeLayout(contentPosX, contentPosY, contentWidth, contentHeight,
	slotPosX, slotPosY, slotWidth, slotHeight, alignmentX, alignmentY,
	depth, visible, defaultAlignmentX, defaultAlignmentY, defaultDisplay,
	numberOfSlots)
{
}


verticalLayout::~verticalLayout()
{
}


verticalLayout* verticalLayout::copy()
{
	verticalLayout* newLayout = new verticalLayout();
	copy(newLayout);
	return newLayout;
}


verticalLayout* verticalLayout::copy_in_cascade()
{
	verticalLayout* newLayout = new verticalLayout();
	copy_in_cascade(newLayout);
	return newLayout;
}


void verticalLayout::copy(verticalLayout* newLayout)
{
	freeLayout::copy(dynamic_cast<freeLayout*>(newLayout));
}


void verticalLayout::copy_in_cascade(verticalLayout* newLayout)
{
	freeLayout::copy_in_cascade(dynamic_cast<freeLayout*>(newLayout));
}


/* CLASS tableLayout */


void tableLayout::recalculateSlot(int slot, element* element)
{
	float slotsWidth = contentWidth / numberOfColumns;
	float slotsHeight = contentHeight / numberOfRows;
	int row = slot / numberOfRows;
	int column = slot % numberOfRows;
	element->set_slot_position(contentPosX + column * slotsWidth,
		contentPosY + row * slotsHeight);
	element->set_slot_size(slotsWidth, slotsHeight);
}


tableLayout::tableLayout(float contentPosX, float contentPosY,
	float contentWidth, float contentHeight, float slotPosX, float slotPosY,
	float slotWidth, float slotHeight, int alignmentX, int alignmentY,
	int depth, bool visible, int defaultAlignmentX, int defaultAlignmentY,
	int numberOfRows, int numberOfColumns)
	: freeLayout(contentPosX, contentPosY, contentWidth, contentHeight,
	slotPosX, slotPosY, slotWidth, slotHeight, alignmentX, alignmentY,
	depth, visible, defaultAlignmentX, defaultAlignmentY, false,
	numberOfRows * numberOfColumns)
{
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;
}


tableLayout::~tableLayout()
{
}


int tableLayout::get_number_of_rows()
{
	return numberOfRows;
}


int tableLayout::get_number_of_columns()
{
	return numberOfColumns;
}


void tableLayout::set_number_of_rows(int numberOfRows)
{
	if (numberOfRows >= 0)
	{
		numberOfSlots = numberOfRows * numberOfColumns;
		if (numberOfRows != this->numberOfRows)
			recalculateSlots();
		this->numberOfRows = numberOfRows;
	}
}


void tableLayout::set_number_of_columns(int numberOfColumns)
{
	if (numberOfColumns >= 0)
	{
		numberOfSlots = numberOfRows * numberOfColumns;
		if (numberOfColumns != this->numberOfColumns)
			recalculateSlots();
		this->numberOfColumns = numberOfColumns;
	}
}


void tableLayout::set_number_of_slots(int numberOfRows, int numberOfColumns)
{
	if (numberOfColumns >= 0)
	{
		numberOfSlots = numberOfRows * numberOfColumns;
		if (numberOfRows != this->numberOfRows ||
			numberOfColumns != this->numberOfColumns)
			recalculateSlots();
		this->numberOfRows = numberOfRows;
		this->numberOfColumns = numberOfColumns;
	}
}


tableLayout* tableLayout::copy()
{
	tableLayout* newLayout = new tableLayout();
	copy(newLayout);
	return newLayout;
}


tableLayout* tableLayout::copy_in_cascade()
{
	tableLayout* newLayout = new tableLayout();
	copy_in_cascade(newLayout);
	return newLayout;
}


void tableLayout::copy(tableLayout* newLayout)
{
	freeLayout::copy(dynamic_cast<freeLayout*>(newLayout));
	newLayout->numberOfRows = numberOfRows;
	newLayout->numberOfColumns = numberOfColumns;
}


void tableLayout::copy_in_cascade(tableLayout* newLayout)
{
	freeLayout::copy_in_cascade(dynamic_cast<freeLayout*>(newLayout));
	newLayout->numberOfRows = numberOfRows;
	newLayout->numberOfColumns = numberOfColumns;
}