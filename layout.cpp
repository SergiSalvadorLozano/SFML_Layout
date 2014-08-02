#include "layout.hpp"

using namespace LAYOUT;


/* CLASS baseElement */


int baseElement::idGenerator = 0;


baseElement::baseElement(std::string name, float contentPosX, float contentPosY,
	float contentWidth, float contentHeight, float slotPosX, float slotPosY,
	float slotWidth, float slotHeight, int alignmentX, int alignmentY,
	int depth, bool visible, bool contentVisible,
	void (*onContentClick)(std::map<std::string, std::string>&),
	void (*onSlotClick)(std::map<std::string, std::string>&),
	void (*onContentHover)(std::map<std::string, std::string>&),
	void (*onSlotHover)(std::map<std::string, std::string>&))
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

	id = idGenerator ++;
	this->name = name;
	parentLayout = 0;
	slotNumber = -1;
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
	this->contentVisible = contentVisible;
	this->onContentClick = onContentClick;
	this->onSlotClick = onSlotClick;
	this->onContentHover = onContentHover;
	this->onSlotHover = onSlotHover;
	align();
}


baseElement::~baseElement()
{
}


int baseElement::get_id()
{
	return id;
}


std::string baseElement::get_name()
{
	return name;
}


baseFreeLayout* baseElement::get_parent_layout()
{
	return parentLayout;
}


int baseElement::get_slot_number()
{
	return slotNumber;
}


float baseElement::get_content_position_x()
{
	return contentPosX;
}


float baseElement::get_content_position_y()
{
	return contentPosY;
}


float baseElement::get_content_width()
{
	return contentWidth;
}


float baseElement::get_content_height()
{
	return contentHeight;
}


float baseElement::get_slot_position_x()
{
	return contentPosX;
}


float baseElement::get_slot_position_y()
{
	return contentPosY;
}


float baseElement::get_slot_width()
{
	return contentWidth;
}


float baseElement::get_slot_height()
{
	return contentHeight;
}


int baseElement::get_alignment_x()
{
	return alignmentX;
}


int baseElement::get_alignment_y()
{
	return alignmentY;
}


int baseElement::get_depth()
{
	return depth;
}


bool baseElement::get_visibility()
{
	return visible;
}


bool baseElement::get_content_visibility()
{
	return contentVisible;
}


void baseElement::set_name(std::string name)
{
	this->name = name;
}


void baseElement::set_content_position(float contentPosX, float contentPosY)
{
	this->contentPosX = contentPosX;
	this->contentPosY = contentPosY;
}


void baseElement::set_content_size(float contentWidth, float contentHeight)
{
	if (contentWidth >= 0)
		this->contentWidth = contentWidth;
	if (contentHeight >= 0)
		this->contentHeight = contentHeight;
	align();
}


void baseElement::set_slot_position(float slotPosX, float slotPosY)
{
	this->slotPosX = slotPosX;
	this->slotPosY = slotPosY;
	align();
}


void baseElement::set_slot_size(float slotWidth, float slotHeight)
{
	if (slotWidth >= 0)
		this->slotWidth = slotWidth;
	if (slotHeight >= 0)
		this->slotHeight = slotHeight;
	align();
}


void baseElement::match_content_to_slot()
{
	set_content_position(slotPosX, slotPosY);
	set_content_size(slotWidth, slotHeight);
}


void baseElement::r_match_content_to_slot()
{
	match_content_to_slot();
}


void baseElement::match_slot_to_content()
{
	set_slot_position(contentPosX, contentPosY);
	set_slot_size(contentWidth, contentHeight);
}


void baseElement::r_match_slot_to_content()
{
	match_slot_to_content();
}


void baseElement::set_alignment_x(int alignmentX)
{
	if (alignmentX == ALIGNMENT::none || alignmentX == ALIGNMENT::left ||
		alignmentX == ALIGNMENT::right || alignmentX == ALIGNMENT::center)
		this->alignmentX = alignmentX;
}


void baseElement::set_alignment_y(int alignmentY)
{
	if (alignmentY == ALIGNMENT::none || alignmentY == ALIGNMENT::top ||
		alignmentY == ALIGNMENT::bottom || alignmentY == ALIGNMENT::center)
		this->alignmentY = alignmentY;
}


void baseElement::set_alignment(int alignmentX, int alignmentY)
{
	if (alignmentX == ALIGNMENT::none || alignmentX == ALIGNMENT::left ||
		alignmentX == ALIGNMENT::right || alignmentX == ALIGNMENT::center)
		this->alignmentX = alignmentX;
	if (alignmentY == ALIGNMENT::none || alignmentY == ALIGNMENT::top ||
		alignmentY == ALIGNMENT::bottom || alignmentY == ALIGNMENT::center)
		this->alignmentY = alignmentY;
}


void baseElement::align()
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


void baseElement::r_align()
{
	align();
}


void baseElement::align(int alignmentX, int alignmentY)
{
	set_alignment(alignmentX, alignmentY);
	align();
}


void baseElement::r_align(int alignmentX, int alignmentY)
{
	align(alignmentX, alignmentY);
}


void baseElement::set_depth(int depth)
{
	this->depth = depth;
}


void baseElement::set_visibility(bool visible)
{
	this->visible = visible;
}


void baseElement::set_content_visibility(bool contentVisible)
{
	this->contentVisible = contentVisible;
}


void baseElement::copy(baseElement &element)
{
	element.name = name;
	element.contentPosX = contentPosX;
	element.contentPosY = contentPosY;
	element.contentWidth = contentWidth;
	element.contentHeight = contentHeight;
	element.slotPosX = slotPosX;
	element.slotPosY = slotPosY;
	element.slotWidth = slotWidth;
	element.slotHeight = slotHeight;
	element.alignmentX = alignmentX;
	element.alignmentY = alignmentY;
	element.depth = depth;
	element.visible = visible;
	element.contentVisible = contentVisible;
	element.onContentClick = onContentClick;
	element.onSlotClick = onSlotClick;
	element.onContentHover = onContentHover;
	element.onSlotHover = onSlotHover;
}


void baseElement::r_copy(baseElement &element)
{
	baseElement::copy(element);
}


void baseElement::r_delete()
{
	delete this;
}


void baseElement::draw()
{
	if (contentVisible)
		drawContent();
}


/* CLASS elementHandler */


elementHandler::elementHandler()
{
}


elementHandler::elementHandler(elementHandler &handler)
{
	idMap = handler.idMap;
}


elementHandler::~elementHandler()
{
}


std::map<int, baseElement*> elementHandler::get_map()
{
	return idMap;
}


void elementHandler::copy(elementHandler &handler)
{
	handler.idMap = idMap;
}


baseElement* elementHandler::find_element(int elementId)
{
	baseElement *e = 0;
	std::map<int, baseElement*>::iterator it = idMap.find(elementId);
	if (it != idMap.end())
		e = it->second;
	return e;
}


baseElement* elementHandler::find_element(std::string elementName)
{
	for (std::map<int, baseElement*>::iterator it = idMap.begin() ;
		it != idMap.end() ; it ++)
	{
		if (it->second->get_name() == elementName)
			return it->second;
	}
	return 0;
}


void elementHandler::add_element(baseElement &element)
{
	idMap.insert(std::pair<int, baseElement*>(element.get_id(), &element));
}


void elementHandler::r_add_element(baseElement &element)
{
	idMap.insert(std::pair<int, baseElement*>(element.get_id(), &element));
	if (baseFreeLayout *layout = dynamic_cast<baseFreeLayout*>(&element))
	{
		std::vector<baseElement*> elements = layout->get_elements();
		for (int i = 0 ; i < elements.size() ; i ++)
			if (elements[i])
				r_add_element(*elements[i]);
	}
}


void elementHandler::remove_element(baseElement &element)
{
	idMap.erase(element.get_id());
}


void elementHandler::r_remove_element(baseElement &element)
{
	idMap.erase(element.get_id());
	if (baseFreeLayout *layout = dynamic_cast<baseFreeLayout*>(&element))
	{
		std::vector<baseElement*> elements = layout->get_elements();
		for (int i = 0 ; i < elements.size() ; i ++)
			if (elements[i])
				r_remove_element(*elements[i]);
	}
}


void elementHandler::click(float cursorPosX, float cursorPosY)
{

	for (std::map<int, baseElement*>::iterator it = idMap.begin() ;
		it != idMap.end() ; it ++)
	{
		baseElement* elem = it->second;
		if (cursorPosX >= elem->get_slot_position_x() &&
			cursorPosY >= elem->get_slot_position_y() &&
			cursorPosX <= elem->get_slot_position_x() + elem->get_slot_width()
			&& cursorPosY <= elem->get_slot_position_y() +
			elem->get_slot_height() && elem->onSlotClick)
		{
			// Mouse cursor is within the slot bounds.
			elem->onSlotClickArgs["cursorPosX"] = std::to_string(cursorPosX);
			elem->onSlotClickArgs["cursorPosY"] = std::to_string(cursorPosY);
			elem->onSlotClick(elem->onSlotClickArgs);
		}
		if (cursorPosX >= elem->get_content_position_x() &&
			cursorPosY >= elem->get_content_position_y() &&
			cursorPosX <= elem->get_content_position_x() +
			elem->get_content_width() && cursorPosY <=
			elem->get_content_position_y() + elem->get_content_height()
			&& elem->onContentClick)
		{
			// Mouse cursor is within the content bounds.
			elem->onContentClickArgs["cursorPosX"] = std::to_string(cursorPosX);
			elem->onContentClickArgs["cursorPosY"] = std::to_string(cursorPosY);
			elem->onContentClick(elem->onContentClickArgs);
		}
	}
}


void elementHandler::hover(float cursorPosX, float cursorPosY)
{
	for (std::map<int, baseElement*>::iterator it = idMap.begin() ;
		it != idMap.end() ; it ++)
	{
		baseElement* elem = it->second;
		if (cursorPosX >= elem->get_slot_position_x() &&
			cursorPosY >= elem->get_slot_position_y() &&
			cursorPosX <= elem->get_slot_position_x() + elem->get_slot_width()
			&& cursorPosY <= elem->get_slot_position_y() +
			elem->get_slot_height() && elem->onSlotHover)
		{
			// Mouse cursor is within the slot bounds.
			elem->onSlotHoverArgs["cursorPosX"] = std::to_string(cursorPosX);
			elem->onSlotHoverArgs["cursorPosY"] = std::to_string(cursorPosY);
			elem->onSlotHover(elem->onSlotHoverArgs);
		}
		if (cursorPosX >= elem->get_content_position_x() &&
			cursorPosY >= elem->get_content_position_y() &&
			cursorPosX <= elem->get_content_position_x() +
			elem->get_content_width() && cursorPosY <=
			elem->get_content_position_y() + elem->get_content_height()
			&& elem->onContentHover)
		{
			// Mouse cursor is within the content bounds.
			elem->onContentHoverArgs["cursorPosX"] = std::to_string(cursorPosX);
			elem->onContentHoverArgs["cursorPosY"] = std::to_string(cursorPosY);
			elem->onContentHover(elem->onContentHoverArgs);
		}
	}
}


/* CLASS baseFreeLayout */


void baseFreeLayout::drawContent()
{
	// First the interval of depths is calculated.
	int minDepth = std::numeric_limits<int>::max();
	int maxDepth = std::numeric_limits<int>::min();
	for (int i = 0 ; i < elements.size() ; i ++)
		if (elements[i] && elements[i]->get_visibility())
		{
			if (elements[i]->get_depth() < minDepth)
				minDepth = elements[i]->get_depth();
			if (elements[i]->get_depth() > maxDepth)
				maxDepth = elements[i]->get_depth();
		}

	// Elements are drawn in iterations, from greater to lesser depth.
	for (int i = maxDepth ; i >= minDepth ; i --)
		for (int j = 0 ; j < elements.size() ; j ++)
			if (elements[j] && elements[j]->get_depth() == i &&
				elements[j]->get_visibility())
					elements[j]->draw();
}


void baseFreeLayout::recalculateSlotBounds(baseElement &element)
{
}


void baseFreeLayout::recalculateAllSlotBounds()
{
	for (int i = 0 ; i < elements.size() ; i ++)
		if (elements[i])
			recalculateSlotBounds(*elements[i]);
}


baseFreeLayout::baseFreeLayout(int size, int defaultAlignmentX,
	int defaultAlignmentY, bool elastic)
{
	if (size < 0)
		size = 0;
	elements.resize(size);
	this->defaultAlignmentX = defaultAlignmentX;
	this->defaultAlignmentY = defaultAlignmentY;
	this->elastic = elastic;
	lowestEmptySlot = 0;
	highestFullSlot = -1;
}


baseFreeLayout::~baseFreeLayout()
{
}


int baseFreeLayout::get_size()
{
	return elements.size();
}


int baseFreeLayout::get_element_count()
{
	return elementCount;
}


int baseFreeLayout::get_lowest_empty_slot()
{
	return lowestEmptySlot;
}


int baseFreeLayout::get_highest_full_slot()
{
	return highestFullSlot;
}


int baseFreeLayout::get_default_alignment_x()
{
	return defaultAlignmentX;
}


int baseFreeLayout::get_default_alignment_y()
{
	return defaultAlignmentY;
}


bool baseFreeLayout::get_elasticity()
{
	return elastic;
}


bool baseFreeLayout::is_slot_full(int slotNumber)
{
	bool b = false;
	if (slotNumber >= 0 && slotNumber < elements.size())
		b = (elements[slotNumber] != 0);
	return b;
}


baseElement* baseFreeLayout::get_element(int slotNumber)
{
	baseElement* e = 0;
	if (slotNumber >= 0 && slotNumber < elements.size())
		e = elements[slotNumber];
	return e;
}


std::vector<baseElement*> baseFreeLayout::get_elements()
{
	return elements;
}


void baseFreeLayout::set_content_position(float contentPosX, float contentPosY)
{
	baseElement::set_content_position(contentPosX, contentPosY);
	recalculateAllSlotBounds();
}


void baseFreeLayout::set_content_size(float contentWidth, float contentHeight)
{
	baseElement::set_content_size(contentWidth, contentHeight);
	recalculateAllSlotBounds();
}


void baseFreeLayout::r_match_content_to_slot()
{
	match_content_to_slot();
	for (int i = 0 ; i < elements.size() ; i ++)
		if (elements[i])
			elements[i]->r_match_content_to_slot();
}


void baseFreeLayout::r_match_slot_to_content()
{
	match_slot_to_content();
	for (int i = 0 ; i < elements.size() ; i ++)
		if (elements[i])
			elements[i]->r_match_slot_to_content();
}


void baseFreeLayout::set_default_alignment_x(int defaultAlignmentX)
{
	if (defaultAlignmentX == ALIGNMENT::none ||
		defaultAlignmentX == ALIGNMENT::left ||
		defaultAlignmentX == ALIGNMENT::right ||
		defaultAlignmentX == ALIGNMENT::center ||
		defaultAlignmentX == ALIGNMENT::keep)
		this->defaultAlignmentX = defaultAlignmentX;
}


void baseFreeLayout::set_default_alignment_y(int defaultAlignmentY)
{
	if (defaultAlignmentY == ALIGNMENT::none ||
		defaultAlignmentY == ALIGNMENT::top ||
		defaultAlignmentY == ALIGNMENT::bottom ||
		defaultAlignmentY == ALIGNMENT::center ||
		defaultAlignmentY == ALIGNMENT::keep)
		this->defaultAlignmentY = defaultAlignmentY;
}


void baseFreeLayout::set_default_alignment(int defaultAlignmentX,
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


void baseFreeLayout::r_align()
{
	align();
	for (int i = 0 ; i < elements.size() ; i ++)
		if (elements[i])
			elements[i]->r_align();
}


void baseFreeLayout::r_align(int alignmentX, int alignmentY)
{
	align(alignmentX, alignmentY);
	for (int i = 0 ; i < elements.size() ; i ++)
		if (elements[i])
			elements[i]->r_align(alignmentX, alignmentY);
}


void baseFreeLayout::copy(baseFreeLayout &layout)
{
	baseElement::copy(layout);
	layout.defaultAlignmentX = defaultAlignmentX;
	layout.defaultAlignmentY = defaultAlignmentY;
	layout.elastic = elastic;
	layout.recalculateAllSlotBounds();
}


void baseFreeLayout::r_copy(baseFreeLayout &layout)
{
	baseFreeLayout::copy(layout);
	layout.elements.resize(elements.size(), 0);
	for (int i = 0 ; i < elements.size() ; i ++)
		if (elements[i])
		{
			layout.elements[i] = elements[i]->r_clone();
			layout.elements[i]->parentLayout = &layout;
			layout.elements[i]->slotNumber = i;
		}
	layout.elementCount = elementCount;
	layout.highestFullSlot = highestFullSlot;
	layout.lowestEmptySlot = lowestEmptySlot;
}


void baseFreeLayout::set_size(int size)
{
	if (size >= 0)
	{
		elements.resize(size, 0);
		recalculateAllSlotBounds();
		if (highestFullSlot >= size)
			for (highestFullSlot = size - 1 ; highestFullSlot >= 0 &&
				!elements[highestFullSlot] ; highestFullSlot --);
	}
}


void baseFreeLayout::set_elasticity(bool elastic)
{
	this->elastic = elastic;
}


baseElement* baseFreeLayout::find_element(int elementId)
{
	baseElement *e = 0;
	for (int i = 0 ; i < elements.size() && !e ; i ++)
		if (elements[i])
			if (elements[i]->get_id() == elementId)
				e = elements[i];
			else if (baseFreeLayout *layout = dynamic_cast<baseFreeLayout*>(
				elements[i]))
				e = layout->find_element(elementId);
	return e;
}


baseElement* baseFreeLayout::find_element(std::string elementName)
{
	baseElement *e = 0;
	for (int i = 0 ; i < elements.size() && !e ; i ++)
		if (elements[i])
			if (elements[i]->get_name() == elementName)
				e = elements[i];
			else if (baseFreeLayout *layout = dynamic_cast<baseFreeLayout*>(
				elements[i]))
				e = layout->find_element(elementName);
	return e;
}


void baseFreeLayout::add_element(baseElement &element)
{
	add_element(element, lowestEmptySlot);
}


void baseFreeLayout::add_element(baseElement &element, int slotNumber)
{
	if (slotNumber >= 0 && !element.parentLayout &&
		(elastic || slotNumber < elements.size()))
	{
		// The size of an elastic layout's is expanded if necessary.
		if (slotNumber >= elements.size())
		{
			elements.resize(slotNumber + 1, 0);
			recalculateAllSlotBounds();
		}

		// The new element's slot and alignment are recalculated.
		// 'ALIGNMENT::keep' will leave the alignment in an axis unchanged.
		recalculateSlotBounds(element);
		element.set_alignment(defaultAlignmentX, defaultAlignmentY);
		if (baseFreeLayout *layout = dynamic_cast<baseFreeLayout*>(&element))
			layout->set_default_alignment(defaultAlignmentX, defaultAlignmentY);

		// The element is added to the slot.
		if (!elements[slotNumber])
			elementCount ++;
		elements[slotNumber] = &element;
		element.parentLayout = this;
		element.slotNumber = slotNumber;

		// The lowest empty slot and the highest full slot are recalculated.
		while (lowestEmptySlot < elements.size() && elements[lowestEmptySlot])
			lowestEmptySlot ++;
		if (slotNumber > highestFullSlot)
			highestFullSlot = slotNumber;
	}
}


baseElement* baseFreeLayout::remove_element(int slotNumber)
{
	baseElement *e = 0;
	if (slotNumber >=0 && slotNumber < elements.size() && elements[slotNumber])
	{
		e = elements[slotNumber];
		e->parentLayout = 0;
		e->slotNumber = -1;
		elements[slotNumber] = 0;
		elementCount --;
		if (slotNumber < lowestEmptySlot)
			lowestEmptySlot = slotNumber;
		while (highestFullSlot >= 0 && !elements[highestFullSlot])
			highestFullSlot --;
	}
	return e;
}


void baseFreeLayout::remove_element(baseElement &element)
{
	// We check thet the element is indeed in the layout.
	bool inLayout = false;
	for (baseFreeLayout *l = element.parentLayout ; l && !inLayout ;
		l = l->parentLayout)
		if (l == this)
			inLayout = true;
	// We remove the element.
	if (inLayout)
		element.parentLayout->remove_element(element.slotNumber);
}


void baseFreeLayout::r_delete()
{
	for (int i = 0 ; i < elements.size() ; i ++)
		if (elements[i])
			elements[i]->r_delete();
	delete this;
}


/* CLASS baseHorizontalLayout */


void baseHorizontalLayout::recalculateSlotBounds(baseElement &element)
{
	if (elements.size() > 0)
	{
		int slotNumber = element.get_slot_number();
		float slotsWidth = contentWidth / elements.size();
		element.set_slot_position(contentPosX + slotNumber * slotsWidth,
			contentPosY);
		element.set_slot_size(slotsWidth, contentHeight);
	}
}


baseHorizontalLayout::baseHorizontalLayout()
{
}


baseHorizontalLayout::~baseHorizontalLayout()
{
}


/* CLASS verticalLayout */


void baseVerticalLayout::recalculateSlotBounds(baseElement &element)
{
	if (elements.size() > 0)
	{
		int slotNumber = element.get_slot_number();
		float slotsHeight = contentHeight / elements.size(); 
		element.set_slot_position(contentPosX, contentPosY + slotNumber *
			slotsHeight);
		element.set_slot_size(contentWidth, slotsHeight);
	}
}


baseVerticalLayout::baseVerticalLayout()
{
}


baseVerticalLayout::~baseVerticalLayout()
{
}


/* CLASS tableLayout */


void baseTableLayout::recalculateSlotBounds(baseElement &element)
{
	if (numberOfRows > 0 && numberOfColumns > 0)
	{
		int slotNumber = element.get_slot_number();
		float slotsWidth = contentWidth / numberOfColumns;
		float slotsHeight = contentHeight / numberOfRows;
		int row = slotNumber / numberOfColumns;
		int column = slotNumber % numberOfColumns;
		element.set_slot_position(contentPosX + column * slotsWidth,
			contentPosY + row * slotsHeight);
		element.set_slot_size(slotsWidth, slotsHeight);
	}
}


baseTableLayout::baseTableLayout(int numberOfRows, int numberOfColumns)
{
	if (numberOfRows < 0)
		numberOfRows = 0;
	if (numberOfColumns < 0)
		numberOfColumns = 0;
	this->numberOfRows = numberOfRows;
	this->numberOfColumns = numberOfColumns;
}


baseTableLayout::~baseTableLayout()
{
}


bool baseTableLayout::is_slot_full(int row, int column)
{
	bool b = false;
	if (row >= 0 && column >= 0 && row < numberOfRows &&
		column < numberOfColumns)
		b = baseFreeLayout::is_slot_full(row * numberOfColumns + column);
	return b;
}


baseElement* baseTableLayout::get_element(int row, int column)
{
	baseElement* e = 0;
	if (row >= 0 && column >= 0 && row < numberOfRows &&
		column < numberOfColumns)
		e = baseFreeLayout::get_element(row * numberOfColumns + column);
	return e;
}


int baseTableLayout::get_number_of_rows()
{
	return numberOfRows;
}


int baseTableLayout::get_number_of_columns()
{
	return numberOfColumns;
}


void baseTableLayout::set_number_of_rows(int numberOfRows)
{
	if (numberOfRows >= 0 && numberOfRows != this->numberOfRows)
	{
		this->numberOfRows = numberOfRows;
		elements.resize(numberOfRows * numberOfColumns, 0);
		recalculateAllSlotBounds();
	}
}


void baseTableLayout::set_number_of_columns(int numberOfColumns)
{
	if (numberOfColumns >= 0 && numberOfColumns != this->numberOfColumns)
	{
		this->numberOfColumns = numberOfColumns;
		elements.resize(numberOfRows * numberOfColumns, 0);
		recalculateAllSlotBounds();
	}
}


void baseTableLayout::set_size(int numberOfRows, int numberOfColumns)
{
	if (numberOfRows >= 0 && numberOfColumns >= 0 && (numberOfRows !=
		this->numberOfRows || numberOfColumns != this->numberOfColumns))
	{
		this->numberOfRows = numberOfRows;
		this->numberOfColumns = numberOfColumns;
		elements.resize(numberOfRows * numberOfColumns, 0);
		recalculateAllSlotBounds();
	}
}


void baseTableLayout::copy(baseTableLayout &layout)
{
	baseFreeLayout::copy(layout);
	layout.numberOfRows = numberOfRows;
	layout.numberOfColumns = numberOfColumns;
}


void baseTableLayout::r_copy(baseTableLayout &layout)
{
	baseFreeLayout::r_copy(layout);
	layout.numberOfRows = numberOfRows;
	layout.numberOfColumns = numberOfColumns;
}


void baseTableLayout::add_element(baseElement &element, int row, int column)
{
	if (row >= 0 && column >= 0 && row < numberOfRows &&
		column < numberOfColumns)
		baseFreeLayout::add_element(element, row * numberOfColumns + column);
}


baseElement* baseTableLayout::remove_element(int row, int column)
{
	baseElement *e = 0;
	if (row >= 0 && column >= 0 && row < numberOfRows &&
		column < numberOfColumns)
		e = baseFreeLayout::remove_element(row * numberOfColumns + column);
	return e;
}