#include "SFMLLayout.hpp"

using namespace LAYOUT;


/* CLASS element */


void element::adjustSpriteX(sf::Sprite &sprite, float left, float width)
{
	if (sprite.getScale().x <= 0)
		sprite.setScale(1, sprite.getScale().y);
	sf::FloatRect sprRect = sprite.getGlobalBounds();
	sprite.scale(width / sprRect.width, 1);
	sprite.move(left - sprRect.left, 0);
}


void element::adjustSpriteY(sf::Sprite &sprite, float top, float height)
{
	if (sprite.getScale().y <= 0)
		sprite.setScale(sprite.getScale().x, 1);
	sf::FloatRect sprRect = sprite.getGlobalBounds();
	sprite.scale(1, height / sprRect.height);
	sprite.move(0, top - sprRect.top);
}


void element::cropSpriteX(sf::Sprite &sprite, float left, float width)
{
	sf::FloatRect sprRect = sprite.getGlobalBounds();
	sf::IntRect texRect = sprite.getTextureRect();

	if (sprRect.left < left)
	{
		// The sprite trespasses the left limit.
		float croppedSprX = left - sprRect.left;
		int croppedTexX = texRect.width * croppedSprX / sprRect.width;
		sprRect.left = left;
		sprRect.width -= croppedSprX;
		texRect.left += croppedTexX;
		texRect.width -= croppedTexX;
	}
	if (sprRect.left + sprRect.width > left + width)
	{
		// The sprite trespasses the right limit.
		float croppedSprX = sprRect.left + sprRect.width - left - width;
		int croppedTexX = texRect.width * croppedSprX / sprRect.width;
		sprRect.width -= croppedSprX;
		texRect.width -= croppedTexX;
	}

	if (texRect.width <= 0)
		texRect.width = 1;
	if (sprRect.width <= 0)
		sprRect.width = 0;
	sprite.setTextureRect(texRect);
	adjustSpriteX(sprite, sprRect.left, sprRect.width);
}


void element::cropSpriteY(sf::Sprite &sprite, float top, float height)
{
	sf::FloatRect sprRect = sprite.getGlobalBounds();
	sf::IntRect texRect = sprite.getTextureRect();

	if (sprRect.top < top)
	{
		// The sprite trespasses the top limit.
		float croppedSprY = top - sprRect.top;
		int croppedTexY = texRect.height * croppedSprY / sprRect.height;
		sprRect.top = top;
		sprRect.height -= croppedSprY;
		texRect.top += croppedTexY;
		texRect.height -= croppedTexY;
	}
	if (sprRect.top + sprRect.height > top + height)
	{
		// The sprite trespasses the bottom limit.
		float croppedSprY = sprRect.top + sprRect.height - top - height;
		int croppedTexY = texRect.height * croppedSprY / sprRect.height;
		sprRect.height -= croppedSprY;
		texRect.height -= croppedTexY;
	}

	if (texRect.height <= 0)
		texRect.height = 1;
	if (sprRect.height < 0)
		sprRect.height = 0;
	sprite.setTextureRect(texRect);
	adjustSpriteY(sprite, sprRect.top, sprRect.height);
}


void element::drawRepeatedSprite(sf::Sprite &sourceSprite,
	float framePosX, float framePosY, float frameWidth, float frameHeight)
{
	sf::Sprite sprite(sourceSprite);
	sf::FloatRect srcRect = sourceSprite.getGlobalBounds();
	float posX, posY, width = srcRect.width, height = srcRect.height;

	// First the non-cropped sprites are drawn.
	// The top-left corner of that tesselation is calculated.
	for (posX = srcRect.left ; posX - width >= framePosX ; posX -= width);
	for (posY = srcRect.top ; posY - height >= framePosY ; posY -= height);
	float fullSprLeft = posX, fullSprTop = posY;

	// The sprite is repeatedly drawn without trespassing the frame.
	for ( ; posX + width <= framePosX + frameWidth ; posX += width)
		for (posY = fullSprTop ; posY + height <= framePosY + frameHeight ;
			posY += height)
		{
			sprite.setPosition(posX, posY);
			drawingWindow->draw(sprite);
		}
	float fullSprRight = posX, fullSprBottom = posY;

	// If necessary, cropped sprites are drawn alongside the frame borders.
	if (fullSprLeft > framePosX)
	{
		// Left column.
		sf::Sprite sprite(sprite);
		sprite.setPosition(fullSprLeft - width, 0);
		cropSpriteX(sprite, framePosX, fullSprLeft - framePosX);
		for (posY = fullSprTop ; posY < fullSprBottom ; posY += height)
		{
			sprite.setPosition(framePosX, posY);
			drawingWindow->draw(sprite);
		}
		if (fullSprTop > framePosY)
		{
			// Top-left corner.
			sf::Sprite sprite(sprite);
			sprite.setPosition(framePosX, fullSprTop - height);
			cropSpriteY(sprite, framePosY, fullSprTop - framePosY);
			drawingWindow->draw(sprite);
		}
		if (fullSprTop > framePosY)
		{
			// Bottom-left corner.
			sf::Sprite sprite(sprite);
			sprite.setPosition(framePosX, fullSprBottom);
			cropSpriteY(sprite, fullSprBottom, framePosY + frameHeight
				- fullSprBottom);
			drawingWindow->draw(sprite);
		}
	}
	if (fullSprRight < framePosX + frameWidth)
	{
		// Right column.
		sf::Sprite sprite(sprite);
		sprite.setPosition(fullSprRight, 0);
		cropSpriteX(sprite, fullSprRight, framePosX + frameWidth
			- fullSprRight);
		for (posY = fullSprTop ; posY < fullSprBottom ; posY += height)
		{
			sprite.setPosition(fullSprRight, posY);
			drawingWindow->draw(sprite);
		}
		if (fullSprTop > framePosY)
		{
			// Top-right corner.
			sf::Sprite sprite(sprite);
			sprite.setPosition(fullSprRight, fullSprTop - height);
			cropSpriteY(sprite, framePosY, fullSprTop - framePosY);
			drawingWindow->draw(sprite);
		}
		if (fullSprTop > framePosY)
		{
			// Bottom-right corner.
			sf::Sprite sprite(sprite);
			sprite.setPosition(fullSprRight, fullSprBottom);
			cropSpriteY(sprite, fullSprBottom, framePosY + frameHeight
				- fullSprBottom);
			drawingWindow->draw(sprite);
		}
	}
	if (fullSprTop > framePosY)
	{
		// Top row.
		sf::Sprite sprite(sprite);
		sprite.setPosition(0, fullSprTop - height);
		cropSpriteY(sprite, framePosY, fullSprTop - framePosY);
		for (posX = fullSprLeft ; posX < fullSprRight ; posX += width)
		{
			sprite.setPosition(posX, framePosY);
			drawingWindow->draw(sprite);
		}
	}
	if (fullSprBottom < framePosY + frameHeight)
	{
		// Bottom row.
		sf::Sprite sprite(sprite);
		sprite.setPosition(0, fullSprBottom);
		cropSpriteY(sprite, fullSprBottom, framePosY + frameHeight
			- fullSprBottom);
		for (posX = fullSprLeft ; posX < fullSprRight ; posX += width)
		{
			sprite.setPosition(posX, fullSprBottom);
			drawingWindow->draw(sprite);
		}
	}
}


void element::drawSprite(sf::Sprite &sprite, float framePosX, float framePosY,
	float frameWidth, float frameHeight, int drawModeX, int drawModeY,
	int alignmentX, int alignmentY)
{
	if (drawingWindow && sprite.getTexture())
	{
		sf::Sprite finalSprite(sprite);

		// The sprite is configured on the X axis.
		if (drawModeX == DRAW::adjust)
			adjustSpriteX(finalSprite, framePosX, frameWidth);
		else
		{
			sf::FloatRect sprRect = finalSprite.getGlobalBounds();
			if (alignmentX == ALIGNMENT::left)
				sprRect.left = framePosX;
			else if (alignmentX == ALIGNMENT::right)
				sprRect.left = framePosX + frameWidth - sprRect.width;
			else if (alignmentX == ALIGNMENT::center)
				sprRect.left = framePosX + (frameWidth - sprRect.width) / 2;
			finalSprite.setPosition(sprRect.left, sprRect.top);

			cropSpriteX(finalSprite, framePosX, frameWidth);
		}

		// The sprite is configured on the Y axis.
		if (drawModeY == DRAW::adjust)
			adjustSpriteY(finalSprite, framePosY, frameHeight);
		else
		{
			sf::FloatRect sprRect = finalSprite.getGlobalBounds();
			if (alignmentY == ALIGNMENT::top)
				sprRect.top = framePosY;
			else if (alignmentY == ALIGNMENT::bottom)
				sprRect.top = framePosY + frameHeight - sprRect.height;
			else if (alignmentY == ALIGNMENT::center)
				sprRect.top = framePosY + (frameHeight - sprRect.height) / 2;
			finalSprite.setPosition(sprRect.left, sprRect.top);

			cropSpriteY(finalSprite, framePosY, frameHeight);
		}

		// The sprite is drawn.
		sf::FloatRect sprRect = finalSprite.getGlobalBounds();
		if (drawModeX == DRAW::repeat &&
			drawModeY == DRAW::repeat)
			drawRepeatedSprite(finalSprite, framePosX, framePosY, frameWidth,
				frameHeight);
		else if (drawModeX == DRAW::repeat)
			drawRepeatedSprite(finalSprite, framePosX, sprRect.top, frameWidth,
				sprRect.height);
		else if (drawModeY == DRAW::repeat)
			drawRepeatedSprite(finalSprite, sprRect.left, framePosY,
				sprRect.width, frameHeight);
		else
			drawingWindow->draw(finalSprite);
	}
}


element::element(sf::RenderWindow* drawingWindow, sf::Sprite* background,
	int backgroundModeX, int backgroundModeY, int backgroundAlignmentX,
	int backgroundAlignmentY, bool backgroundVisible)
{
	if (backgroundModeX != DRAW::crop && backgroundModeX != DRAW::adjust &&
		backgroundModeX != DRAW::repeat)
		backgroundModeX = DRAW::adjust;
	if (backgroundModeY != DRAW::crop && backgroundModeY != DRAW::adjust &&
		backgroundModeY != DRAW::repeat)
		backgroundModeY = DRAW::adjust;
	if (backgroundAlignmentX != ALIGNMENT::left &&
		backgroundAlignmentX != ALIGNMENT::right &&
		backgroundAlignmentX != ALIGNMENT::center)
		backgroundAlignmentX = ALIGNMENT::left;
	if (backgroundAlignmentY != ALIGNMENT::top &&
		backgroundAlignmentY != ALIGNMENT::bottom &&
		backgroundAlignmentY != ALIGNMENT::center)
		backgroundAlignmentY = ALIGNMENT::top;

	this->drawingWindow = drawingWindow;
	this->background = background;
	this->backgroundModeX = backgroundModeX;
	this->backgroundModeY = backgroundModeY;
	this->backgroundAlignmentX = backgroundAlignmentX;
	this->backgroundAlignmentY = backgroundAlignmentY;
	this->backgroundVisible = backgroundVisible;
}


element::~element()
{
}


sf::RenderWindow* element::get_drawing_window()
{
	return drawingWindow;
}


sf::Sprite* element::get_background()
{
	return background;
}


int element::get_background_mode_x()
{
	return backgroundModeX;
}


int element::get_background_mode_y()
{
	return backgroundModeY;
}


int element::get_background_alignment_x()
{
	return backgroundAlignmentX;
}


int element::get_background_alignment_y()
{
	return backgroundAlignmentY;
}


bool element::get_background_visibility()
{
	return backgroundVisible;
}


void element::set_drawing_window(sf::RenderWindow &drawingWindow)
{
	this->drawingWindow = &drawingWindow;
}


void element::r_set_drawing_window(sf::RenderWindow &drawingWindow)
{
	set_drawing_window(drawingWindow);
}


void element::set_background(sf::Sprite &background)
{
	this->background = &background;
}


void element::set_background_mode_x(int backgroundModeX)
{
	if (backgroundModeX == DRAW::crop || backgroundModeX == DRAW::adjust ||
		backgroundModeX == DRAW::repeat)
		this->backgroundModeX = backgroundModeX;
}


void element::set_background_mode_y(int backgroundModeY)
{
	if (backgroundModeY == DRAW::crop || backgroundModeY == DRAW::adjust ||
		backgroundModeY == DRAW::repeat)
		this->backgroundModeY = backgroundModeY;
}


void element::set_background_mode(int backgroundModeX, int backgroundModeY)
{
	if (backgroundModeX == DRAW::crop || backgroundModeX == DRAW::adjust ||
		backgroundModeX == DRAW::repeat)
		this->backgroundModeX = backgroundModeX;
	if (backgroundModeY == DRAW::crop || backgroundModeY == DRAW::adjust ||
		backgroundModeY == DRAW::repeat)
		this->backgroundModeY = backgroundModeY;
}


void element::set_background_alignment_x(int backgroundAlignmentX)
{
	if (backgroundAlignmentX == ALIGNMENT::left ||
		backgroundAlignmentX == ALIGNMENT::right ||
		backgroundAlignmentX == ALIGNMENT::center)
		this->backgroundAlignmentX = backgroundAlignmentX;
}


void element::set_background_alignment_y(int backgroundAlignmentY)
{
	if (backgroundAlignmentY == ALIGNMENT::top ||
		backgroundAlignmentY == ALIGNMENT::bottom ||
		backgroundAlignmentY == ALIGNMENT::center)
		this->backgroundAlignmentY = backgroundAlignmentY;
}


void element::set_background_alignment(int backgroundAlignmentX,
	int backgroundAlignmentY)
{
	if (backgroundAlignmentX == ALIGNMENT::left ||
		backgroundAlignmentX == ALIGNMENT::right ||
		backgroundAlignmentX == ALIGNMENT::center)
		this->backgroundAlignmentX = backgroundAlignmentX;
	if (backgroundAlignmentY == ALIGNMENT::top ||
		backgroundAlignmentY == ALIGNMENT::bottom ||
		backgroundAlignmentY == ALIGNMENT::center)
		this->backgroundAlignmentY = backgroundAlignmentY;
}


void element::set_background_visibility(bool backgroundVisible)
{
	this->backgroundVisible = backgroundVisible;
}


void element::copy(element &element)
{
	baseElement::copy(element);
	element.drawingWindow = drawingWindow;
	element.background = background;
	element.backgroundModeX = backgroundModeX;
	element.backgroundModeY = backgroundModeY;
	element.backgroundAlignmentX = backgroundAlignmentX;
	element.backgroundAlignmentY = backgroundAlignmentY;
	element.backgroundVisible = backgroundVisible;
}


void element::r_copy(element &element)
{
	element::copy(element);
}


void element::draw()
{
	if (drawingWindow)
	{
		if (backgroundVisible && background)
			drawSprite(*background, slotPosX, slotPosY, slotWidth, slotHeight,
				backgroundModeX, backgroundModeY, backgroundAlignmentX,
				backgroundAlignmentY);
		baseElement::draw();
	}
}


/* CLASS spriteElement */


void spriteElement::drawContent()
{
	if (content)
	{
		drawSprite(*content, contentPosX, contentPosY, contentWidth,
			contentHeight, spriteModeX, spriteModeY, spriteAlignmentX,
			spriteAlignmentY);
	}
}


spriteElement::spriteElement(sf::Sprite* content, std::string name,
	float contentPosX, float contentPosY, float contentWidth,
	float contentHeight, float slotPosX, float slotPosY, float slotWidth,
	float slotHeight, int alignmentX, int alignmentY, int depth, bool visible,
	bool contentVisible,
	void (*onContentClick)(std::map<std::string, std::string>&),
	void (*onSlotClick)(std::map<std::string, std::string>&),
	void (*onContentHover)(std::map<std::string, std::string>&),
	void (*onSlotHover)(std::map<std::string, std::string>&),
	sf::RenderWindow* drawingWindow, sf::Sprite* background,
	int backgroundModeX, int backgroundModeY, int backgroundAlignmentX,
	int backgroundAlignmentY, bool backgroundVisible, int spriteModeX,
	int spriteModeY, int spriteAlignmentX, int spriteAlignmentY)
	// The constructor of 'element' is called in order to initialise its
	// attributes.
	: element(drawingWindow, background, backgroundModeX, backgroundModeY,
	backgroundAlignmentX, backgroundAlignmentY, backgroundVisible),
	// 'element' inherits from 'baseElement' virtually, so its constructor must
	// also be called here (or it wouldn't be called).
	baseElement(name, contentPosX, contentPosY, contentWidth,
	contentHeight, slotPosX, slotPosY, slotWidth, slotHeight, alignmentX,
	alignmentY, depth, visible, contentVisible, onContentClick, onSlotClick,
	onContentHover, onSlotHover)
{
	if (spriteModeX != DRAW::crop && spriteModeX != DRAW::adjust &&
		spriteModeX != DRAW::repeat)
		spriteModeX = DRAW::adjust;
	if (spriteModeY != DRAW::crop && spriteModeY != DRAW::adjust &&
		spriteModeY != DRAW::repeat)
		spriteModeY = DRAW::adjust;
	if (spriteAlignmentX != ALIGNMENT::left &&
		spriteAlignmentX != ALIGNMENT::right &&
		spriteAlignmentX != ALIGNMENT::center)
		spriteAlignmentX = ALIGNMENT::left;
	if (spriteAlignmentY != ALIGNMENT::top &&
		spriteAlignmentY != ALIGNMENT::bottom &&
		spriteAlignmentY != ALIGNMENT::center)
		spriteAlignmentY = ALIGNMENT::top;

	this->content = content;
	this->spriteModeX = spriteModeX;
	this->spriteModeY = spriteModeY;
	this->spriteAlignmentX = spriteAlignmentX;
	this->spriteAlignmentY = spriteAlignmentY;
}


spriteElement::spriteElement(spriteElement& element)
{
	element.spriteElement::copy(*this);
}

		
spriteElement::~spriteElement()
{
}

		
sf::Sprite* spriteElement::get_content()
{
	return content;
}


int spriteElement::get_sprite_mode_x()
{
	return spriteModeX;
}


int spriteElement::get_sprite_mode_y()
{
	return spriteModeY;
}


int spriteElement::get_sprite_alignment_x()
{
	return spriteAlignmentX;
}


int spriteElement::get_sprite_alignment_y()
{
	return spriteAlignmentY;
}

		
void spriteElement::set_content(sf::Sprite &content)
{
	this->content = &content;
}


void spriteElement::set_sprite_mode_x(int spriteModeX)
{
	if (spriteModeX == DRAW::crop || spriteModeX == DRAW::adjust ||
		spriteModeX == DRAW::repeat)
		this->spriteModeX = spriteModeX;
}


void spriteElement::set_sprite_mode_y(int spriteModeY)
{
	if (spriteModeY == DRAW::crop || spriteModeY == DRAW::adjust ||
		spriteModeY == DRAW::repeat)
		this->spriteModeY = spriteModeY;
}


void spriteElement::set_sprite_mode(int spriteModeX, int spriteModeY)
{
	if (spriteModeX == DRAW::crop || spriteModeX == DRAW::adjust ||
		spriteModeX == DRAW::repeat)
		this->spriteModeX = spriteModeX;
	if (spriteModeY == DRAW::crop || spriteModeY == DRAW::adjust ||
		spriteModeY == DRAW::repeat)
		this->spriteModeY = spriteModeY;
}


void spriteElement::set_sprite_alignment_x(int spriteAlignmentX)
{
	if (spriteAlignmentX == ALIGNMENT::left ||
		spriteAlignmentX == ALIGNMENT::right ||
		spriteAlignmentX == ALIGNMENT::center)
		this->spriteAlignmentX = spriteAlignmentX;
}


void spriteElement::set_sprite_alignment_y(int spriteAlignmentY)
{
	if (spriteAlignmentY == ALIGNMENT::top ||
		spriteAlignmentY == ALIGNMENT::bottom ||
		spriteAlignmentY == ALIGNMENT::center)
		this->spriteAlignmentY = spriteAlignmentY;
}


void spriteElement::set_sprite_alignment(int spriteAlignmentX,
	int spriteAlignmentY)
{
	if (spriteAlignmentX == ALIGNMENT::left ||
		spriteAlignmentX == ALIGNMENT::right ||
		spriteAlignmentX == ALIGNMENT::center)
		this->spriteAlignmentX = spriteAlignmentX;
	if (spriteAlignmentY == ALIGNMENT::top ||
		spriteAlignmentY == ALIGNMENT::bottom ||
		spriteAlignmentY == ALIGNMENT::center)
		this->spriteAlignmentY = spriteAlignmentY;
}


spriteElement* spriteElement::clone()
{
	spriteElement *newElement = new spriteElement();
	copy(*newElement);
	return newElement;
}
		

spriteElement* spriteElement::r_clone()
{
	spriteElement *newElement = new spriteElement();
	r_copy(*newElement);
	return newElement;
}


void spriteElement::copy(spriteElement &newElement)
{
	element::copy(newElement);
	newElement.content = content;
}
		

void spriteElement::r_copy(spriteElement &newElement)
{
	element::r_copy(newElement);
	newElement.content = content;
}


/* CLASS freeLayout */


freeLayout::freeLayout(std::string name, float contentPosX, float contentPosY,
	float contentWidth, float contentHeight, float slotPosX, float slotPosY,
	float slotWidth, float slotHeight, int alignmentX, int alignmentY,
	int depth, bool visible, bool contentVisible,
	void (*onContentClick)(std::map<std::string, std::string>&),
	void (*onSlotClick)(std::map<std::string, std::string>&),
	void (*onContentHover)(std::map<std::string, std::string>&),
	void (*onSlotHover)(std::map<std::string, std::string>&),
	int size, int defaultAlignmentX, int defaultAlignmentY, bool elastic,
	sf::RenderWindow* drawingWindow, sf::Sprite* background,
	int backgroundModeX, int backgroundModeY, int backgroundAlignmentX,
	int backgroundAlignmentY, bool backgroundVisible)
	// The constructor of 'baseFreeLayout' is called in order to to initialise
	// its attributes.
	: baseFreeLayout(size, defaultAlignmentX, defaultAlignmentY, elastic),
	// The constructor of 'element' is called in order to to initialise its
	// attributes.
	element(drawingWindow, background, backgroundModeX, backgroundModeY,
	backgroundAlignmentX, backgroundAlignmentY, backgroundVisible),
	// 'baseFreeLayout' and 'element' inherit from 'baseElement' virtually, so
	// its constructor must also be called here (or it wouldn't be called).
	baseElement(name, contentPosX, contentPosY, contentWidth, contentHeight,
	slotPosX, slotPosY, slotWidth, slotHeight, alignmentX, alignmentY, depth,
	visible, contentVisible, onContentClick, onSlotClick, onContentHover,
	onSlotHover)
{
}


freeLayout::freeLayout(freeLayout &layout)
{
	layout.freeLayout::copy(*this);
}

		
freeLayout::~freeLayout()
{
}


element* freeLayout::get_element(int slot)
{
	return dynamic_cast<element*>(baseFreeLayout::get_element(slot));
}


void freeLayout::r_set_drawing_window(sf::RenderWindow &drawingWindow)
{
	this->drawingWindow = &drawingWindow; 
	for (int i = 0 ; i < elements.size() ; i ++)
		if (elements[i])
		{
			// All instances are 'element', but pointers are to 'baseElement'.
			element* elem = dynamic_cast<element*>(elements[i]);
			elem->r_set_drawing_window(drawingWindow);
		}
}


freeLayout* freeLayout::clone()
{
	freeLayout *newLayout = new freeLayout();
	copy(*newLayout);
	return newLayout;
}
		

freeLayout* freeLayout::r_clone()
{
	freeLayout *newLayout = new freeLayout();
	r_copy(*newLayout);
	return newLayout;
}
		

void freeLayout::copy(freeLayout &layout)
{
	baseFreeLayout::copy(layout);
	element::copy(layout);
}
		

void freeLayout::r_copy(freeLayout &layout)
{
	baseFreeLayout::r_copy(layout);
	element::r_copy(layout);
}


element* freeLayout::find_element(int elementId)
{
	return dynamic_cast<element*>(baseFreeLayout::find_element(elementId));
}


element* freeLayout::find_element(std::string elementName)
{
	return dynamic_cast<element*>(baseFreeLayout::find_element(elementName));
}


void freeLayout::add_element(element &element)
{
	baseFreeLayout::add_element(element, lowestEmptySlot);
}


void freeLayout::add_element(element &element, int slot)
{
	baseFreeLayout::add_element(element, slot);
}


element* freeLayout::remove_element(int slot)
{
	return dynamic_cast<element*>(baseFreeLayout::remove_element(slot));
}


void freeLayout::remove_element(element &element)
{
	baseFreeLayout::remove_element(element);
}


/* CLASS horizontalLayout */


horizontalLayout::horizontalLayout(std::string name, float contentPosX,
	float contentPosY, float contentWidth, float contentHeight, float slotPosX,
	float slotPosY, float slotWidth, float slotHeight, int alignmentX,
	int alignmentY, int depth, bool visible, bool contentVisible,
	void (*onContentClick)(std::map<std::string, std::string>&),
	void (*onSlotClick)(std::map<std::string, std::string>&),
	void (*onContentHover)(std::map<std::string, std::string>&),
	void (*onSlotHover)(std::map<std::string, std::string>&),
	int size, int defaultAlignmentX, int defaultAlignmentY, bool elastic,
	sf::RenderWindow* drawingWindow, sf::Sprite* background,
	int backgroundModeX, int backgroundModeY, int backgroundAlignmentX,
	int backgroundAlignmentY, bool backgroundVisible)
	// The constructor of 'freeLayout' is called in order to initialise its
	// attributes.
	: freeLayout(name, contentPosX, contentPosY, contentWidth,
	contentHeight, slotPosX, slotPosY, slotWidth, slotHeight, alignmentX,
	alignmentY, depth, visible, contentVisible, onContentClick, onSlotClick,
	onContentHover, onSlotHover, size, defaultAlignmentX, defaultAlignmentY,
	elastic, drawingWindow, background, backgroundModeX, backgroundModeY,
	backgroundAlignmentX, backgroundAlignmentY, backgroundVisible),
	// 'freeLayout' and 'baseHorizontalLayout' inherit from 'baseFreeLayout'
	// virtually, so its constructor must also be called here (or it wouldn't be
	// called).
	baseFreeLayout(size, defaultAlignmentX, defaultAlignmentY, elastic),
	// 'freeLayout' and 'baseFreeLayout' inherit from 'baseElement' virtually,
	// so its constructor must also be called here (or it wouldn't be called).
	baseElement(name, contentPosX, contentPosY, contentWidth, contentHeight,
	slotPosX, slotPosY, slotWidth, slotHeight, alignmentX, alignmentY, depth,
	visible, contentVisible, onContentClick, onSlotClick, onContentHover,
	onSlotHover)
{
}


horizontalLayout::horizontalLayout(horizontalLayout &layout)
{
	layout.horizontalLayout::copy(*this);
}

		
horizontalLayout::~horizontalLayout()
{
}


horizontalLayout* horizontalLayout::clone()
{
	horizontalLayout *newLayout = new horizontalLayout();
	copy(*newLayout);
	return newLayout;
}
		

horizontalLayout* horizontalLayout::r_clone()
{
	horizontalLayout* newLayout = new horizontalLayout();
	r_copy(*newLayout);
	return newLayout;
}


/* CLASS verticalLayout */


verticalLayout::verticalLayout(std::string name, float contentPosX,
	float contentPosY, float contentWidth, float contentHeight, float slotPosX,
	float slotPosY, float slotWidth, float slotHeight, int alignmentX,
	int alignmentY, int depth, bool visible, bool contentVisible,
	void (*onContentClick)(std::map<std::string, std::string>&),
	void (*onSlotClick)(std::map<std::string, std::string>&),
	void (*onContentHover)(std::map<std::string, std::string>&),
	void (*onSlotHover)(std::map<std::string, std::string>&),
	int size, int defaultAlignmentX, int defaultAlignmentY, bool elastic,
	sf::RenderWindow* drawingWindow, sf::Sprite* background,
	int backgroundModeX, int backgroundModeY, int backgroundAlignmentX,
	int backgroundAlignmentY, bool backgroundVisible)
	// The constructor of 'freeLayout' is called in order to initialise its
	// attributes.
	: freeLayout(name, contentPosX, contentPosY, contentWidth,
	contentHeight, slotPosX, slotPosY, slotWidth, slotHeight, alignmentX,
	alignmentY, depth, visible, contentVisible, onContentClick, onSlotClick,
	onContentHover, onSlotHover, size, defaultAlignmentX, defaultAlignmentY,
	elastic, drawingWindow, background, backgroundModeX, backgroundModeY,
	backgroundAlignmentX, backgroundAlignmentY, backgroundVisible),
	// 'freeLayout' and 'baseVerticalLayout' inherit from 'baseFreeLayout'
	// virtually, so its constructor must also be called here (or it wouldn't be
	// called).
	baseFreeLayout(size, defaultAlignmentX, defaultAlignmentY, elastic),
	// 'freeLayout' and 'baseFreeLayout' inherit from 'baseElement' virtually,
	// so its constructor must also be called here (or it wouldn't be called).
	baseElement(name, contentPosX, contentPosY, contentWidth, contentHeight,
	slotPosX, slotPosY, slotWidth, slotHeight, alignmentX, alignmentY, depth,
	visible, contentVisible, onContentClick, onSlotClick, onContentHover,
	onSlotHover)
{
}


verticalLayout::verticalLayout(verticalLayout &layout)
{
	layout.verticalLayout::copy(*this);
}

		
verticalLayout::~verticalLayout()
{
}


verticalLayout* verticalLayout::clone()
{
	verticalLayout *newLayout = new verticalLayout();
	copy(*newLayout);
	return newLayout;
}
		

verticalLayout* verticalLayout::r_clone()
{
	verticalLayout *newLayout = new verticalLayout();
	r_copy(*newLayout);
	return newLayout;
}


/* CLASS tableLayout */


tableLayout::tableLayout(std::string name, float contentPosX,
	float contentPosY, float contentWidth, float contentHeight, float slotPosX,
	float slotPosY, float slotWidth, float slotHeight, int alignmentX,
	int alignmentY, int depth, bool visible, bool contentVisible,
	void (*onContentClick)(std::map<std::string, std::string>&),
	void (*onSlotClick)(std::map<std::string, std::string>&),
	void (*onContentHover)(std::map<std::string, std::string>&),
	void (*onSlotHover)(std::map<std::string, std::string>&),
	int numberOfRows, int numberOfColumns, int defaultAlignmentX, 
	int defaultAlignmentY, sf::RenderWindow* drawingWindow,
	sf::Sprite* background, int backgroundModeX, int backgroundModeY,
	int backgroundAlignmentX, int backgroundAlignmentY, bool backgroundVisible)
	// The constructor of 'baseTableLayout' is called in order to initialise its
	// attributes.
	: baseTableLayout(numberOfRows, numberOfColumns),
	// The constructor of 'freeLayout' is called in order to initialise its
	// attributes.
	freeLayout(name, contentPosX, contentPosY, contentWidth,
	contentHeight, slotPosX, slotPosY, slotWidth, slotHeight, alignmentX,
	alignmentY, depth, visible, contentVisible, onContentClick, onSlotClick,
	onContentHover, onSlotHover, numberOfRows * numberOfColumns,
	defaultAlignmentX, defaultAlignmentY, false, drawingWindow, background,
	backgroundModeX, backgroundModeY, backgroundAlignmentX,
	backgroundAlignmentY, backgroundVisible),
	// 'freeLayout' and 'baseTableLayout' inherit from 'baseFreeLayout'
	// virtually, so its constructor must also be called here (or it wouldn't be
	// called).
	baseFreeLayout(numberOfRows * numberOfColumns, defaultAlignmentX,
	defaultAlignmentY, false),
	// 'freeLayout' and 'baseFreeLayout' inherit from 'baseElement' virtually,
	// so its constructor must also be called here (or it wouldn't be called).
	baseElement(name, contentPosX, contentPosY, contentWidth, contentHeight,
	slotPosX, slotPosY, slotWidth, slotHeight, alignmentX, alignmentY, depth,
	visible, contentVisible, onContentClick, onSlotClick, onContentHover,
	onSlotHover)
{
}


tableLayout::tableLayout(tableLayout &layout)
{
	layout.tableLayout::copy(*this);
}

		
tableLayout::~tableLayout()
{
}


element* tableLayout::get_element(int row, int column)
{
	return dynamic_cast<element*>(baseTableLayout::get_element(row, column));
}


tableLayout* tableLayout::clone()
{
	tableLayout *newLayout = new tableLayout();
	copy(*newLayout);
	return newLayout;
}
		

tableLayout* tableLayout::r_clone()
{
	tableLayout* newLayout = new tableLayout();
	r_copy(*newLayout);
	return newLayout;
}


void tableLayout::copy(tableLayout &layout)
{
	baseTableLayout::copy(layout);
	freeLayout::copy(layout);
}


void tableLayout::r_copy(tableLayout &layout)
{
	baseTableLayout::r_copy(layout);
	freeLayout::copy(layout);
}


void tableLayout::add_element(element &element, int row, int column)
{
	baseTableLayout::add_element(element, row, column);
}


element* tableLayout::remove_element(int row, int column)
{
	return dynamic_cast<element*>(
		baseTableLayout::remove_element(row, column));
}

