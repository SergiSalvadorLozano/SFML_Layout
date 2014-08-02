#include "SFMLLayout.hpp"

using namespace SFML_LAYOUT;


/* CLASS SFMLBase */

void SFMLBase::adjustSpriteX(sf::Sprite* sprite, float left, float width)
{
	if (sprite->getScale().x <= 0)
		sprite->setScale(1, sprite->getScale().y);
	sf::FloatRect sprRect = sprite->getGlobalBounds();
	sprite->scale(width / sprRect.width, 1);
	sprite->move(left - sprRect.left, 0);
}


void SFMLBase::adjustSpriteY(sf::Sprite* sprite, float top, float height)
{
	if (sprite->getScale().y <= 0)
		sprite->setScale(sprite->getScale().x, 1);
	sf::FloatRect sprRect = sprite->getGlobalBounds();
	sprite->scale(1, height / sprRect.height);
	sprite->move(0, top - sprRect.top);
}


void SFMLBase::cropSpriteX(sf::Sprite* sprite, float left, float width)
{
	sf::FloatRect sprRect = sprite->getGlobalBounds();
	sf::IntRect texRect = sprite->getTextureRect();

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
	sprite->setTextureRect(texRect);
	adjustSpriteX(sprite, sprRect.left, sprRect.width);
}


void SFMLBase::cropSpriteY(sf::Sprite* sprite, float top, float height)
{
	sf::FloatRect sprRect = sprite->getGlobalBounds();
	sf::IntRect texRect = sprite->getTextureRect();

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
	if (sprRect.height <= 0)
		sprRect.height = 0;
	sprite->setTextureRect(texRect);
	adjustSpriteY(sprite, sprRect.top, sprRect.height);
}


void SFMLBase::drawRepeatedSprite(sf::RenderWindow* window,
	sf::Sprite* sourceSprite, float framePosX, float framePosY,
	float frameWidth, float frameHeight)
{
	sf::Sprite sprite(*sourceSprite);
	sf::FloatRect srcRect = sourceSprite->getGlobalBounds();
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
			window->draw(sprite);
		}
	float fullSprRight = posX, fullSprBottom = posY;

	// If necessary, cropped sprites are drawn alongside the frame borders.
	if (fullSprLeft > framePosX)
	{
		// Left column.
		sf::Sprite sprite(sprite);
		sprite.setPosition(fullSprLeft - width, 0);
		cropSpriteX(&sprite, framePosX, fullSprLeft - framePosX);
		for (posY = fullSprTop ; posY < fullSprBottom ; posY += height)
		{
			sprite.setPosition(framePosX, posY);
			window->draw(sprite);
		}
		if (fullSprTop > framePosY)
		{
			// Top-left corner.
			sf::Sprite sprite(sprite);
			sprite.setPosition(framePosX, fullSprTop - height);
			cropSpriteY(&sprite, framePosY, fullSprTop - framePosY);
			window->draw(sprite);
		}
		if (fullSprTop > framePosY)
		{
			// Bottom-left corner.
			sf::Sprite sprite(sprite);
			sprite.setPosition(framePosX, fullSprBottom);
			cropSpriteY(&sprite, fullSprBottom, framePosY + frameHeight
				- fullSprBottom);
			window->draw(sprite);
		}
	}
	if (fullSprRight < framePosX + frameWidth)
	{
		// Right column.
		sf::Sprite sprite(sprite);
		sprite.setPosition(fullSprRight, 0);
		cropSpriteX(&sprite, fullSprRight, framePosX + frameWidth
			- fullSprRight);
		for (posY = fullSprTop ; posY < fullSprBottom ; posY += height)
		{
			sprite.setPosition(fullSprRight, posY);
			window->draw(sprite);
		}
		if (fullSprTop > framePosY)
		{
			// Top-right corner.
			sf::Sprite sprite(sprite);
			sprite.setPosition(fullSprRight, fullSprTop - height);
			cropSpriteY(&sprite, framePosY, fullSprTop - framePosY);
			window->draw(sprite);
		}
		if (fullSprTop > framePosY)
		{
			// Bottom-right corner.
			sf::Sprite sprite(sprite);
			sprite.setPosition(fullSprRight, fullSprBottom);
			cropSpriteY(&sprite, fullSprBottom, framePosY + frameHeight
				- fullSprBottom);
			window->draw(sprite);
		}
	}
	if (fullSprTop > framePosY)
	{
		// Top row.
		sf::Sprite sprite(sprite);
		sprite.setPosition(0, fullSprTop - height);
		cropSpriteY(&sprite, framePosY, fullSprTop - framePosY);
		for (posX = fullSprLeft ; posX < fullSprRight ; posX += width)
		{
			sprite.setPosition(posX, framePosY);
			window->draw(sprite);
		}
	}
	if (fullSprBottom < framePosY + frameHeight)
	{
		// Bottom row.
		sf::Sprite sprite(sprite);
		sprite.setPosition(0, fullSprBottom);
		cropSpriteY(&sprite, fullSprBottom, framePosY + frameHeight
			- fullSprBottom);
		for (posX = fullSprLeft ; posX < fullSprRight ; posX += width)
		{
			sprite.setPosition(posX, fullSprBottom);
			window->draw(sprite);
		}
	}
}


void SFMLBase::drawBackground(sf::RenderWindow* window, float slotPositionX,
	float slotPositionY, float slotWidth, float slotHeight)
{
	if (window && background && background->getTexture() && backgroundVisible)
	{
		sf::Sprite finalBackground(*background);

		// The sprite is configured on the X axis.
		if (backgroundModeX == BACKGROUND::adjust)
			adjustSpriteX(&finalBackground, slotPositionX, slotWidth);
		else
		{
			sf::FloatRect sprRect = finalBackground.getGlobalBounds();
			if (backgroundAlignmentX == LAYOUT::ALIGNMENT::left)
				sprRect.left = slotPositionX;
			else if (backgroundAlignmentX == LAYOUT::ALIGNMENT::right)
				sprRect.left = slotPositionX + slotWidth - sprRect.width;
			else if (backgroundAlignmentX == LAYOUT::ALIGNMENT::center)
				sprRect.left = slotPositionX + (slotWidth - sprRect.width) / 2;
			finalBackground.setPosition(sprRect.left, sprRect.top);

			if (backgroundModeX == BACKGROUND::crop)
				cropSpriteX(&finalBackground, slotPositionX, slotWidth);
		}

		// The sprite is configured on the Y axis.
		if (backgroundModeY == BACKGROUND::adjust)
			adjustSpriteY(&finalBackground, slotPositionY, slotHeight);
		else
		{
			sf::FloatRect sprRect = finalBackground.getGlobalBounds();
			if (backgroundAlignmentY == LAYOUT::ALIGNMENT::top)
				sprRect.top = slotPositionY;
			else if (backgroundAlignmentY == LAYOUT::ALIGNMENT::bottom)
				sprRect.top = slotPositionY + slotHeight - sprRect.height;
			else if (backgroundAlignmentY == LAYOUT::ALIGNMENT::center)
				sprRect.top = slotPositionY + (slotHeight - sprRect.height) / 2;
			finalBackground.setPosition(sprRect.left, sprRect.top);

			if (backgroundModeY == BACKGROUND::crop)
				cropSpriteY(&finalBackground, slotPositionY, slotHeight);
		}

		// The sprite is drawn.
		sf::FloatRect sprRect = background->getGlobalBounds();
		if (backgroundModeX == BACKGROUND::repeat &&
			backgroundModeY == BACKGROUND::repeat)
			drawRepeatedSprite(window, &finalBackground, slotPositionX,
				slotPositionY, slotWidth, slotHeight);
		else if (backgroundModeX == BACKGROUND::repeat)
			drawRepeatedSprite(window, &finalBackground, slotPositionX,
				sprRect.top, slotWidth, sprRect.height);
		else if (backgroundModeY == BACKGROUND::repeat)
			drawRepeatedSprite(window, &finalBackground, sprRect.left,
				slotPositionY, sprRect.width, slotHeight);
		else
			window->draw(finalBackground);
	}
}


SFMLBase::SFMLBase(sf::RenderWindow* defaultWindow, sf::Sprite* background,
	int backgroundModeX, int backgroundModeY, int backgroundAlignmentX,
	int backgroundAlignmentY, bool backgroundVisible)
{
	if (backgroundModeX != BACKGROUND::full &&
		backgroundModeX != BACKGROUND::crop &&
		backgroundModeX != BACKGROUND::adjust &&
		backgroundModeX != BACKGROUND::repeat)
		backgroundModeX = BACKGROUND::adjust;
	if (backgroundModeY != BACKGROUND::full &&
		backgroundModeY != BACKGROUND::crop &&
		backgroundModeY != BACKGROUND::adjust &&
		backgroundModeY != BACKGROUND::repeat)
		backgroundModeY = BACKGROUND::adjust;
	if (backgroundAlignmentX != LAYOUT::ALIGNMENT::left &&
		backgroundAlignmentX != LAYOUT::ALIGNMENT::right &&
		backgroundAlignmentX != LAYOUT::ALIGNMENT::center)
		backgroundAlignmentX = LAYOUT::ALIGNMENT::left;
	if (backgroundAlignmentY != LAYOUT::ALIGNMENT::top &&
		backgroundAlignmentY != LAYOUT::ALIGNMENT::bottom &&
		backgroundAlignmentY != LAYOUT::ALIGNMENT::center)
		backgroundAlignmentY = LAYOUT::ALIGNMENT::left;

	this->defaultWindow = defaultWindow;
	this->background = background;
	this->backgroundModeX = backgroundModeX;
	this->backgroundModeY = backgroundModeY;
	this->backgroundAlignmentX = backgroundAlignmentX;
	this->backgroundAlignmentY = backgroundAlignmentY;
	this->backgroundVisible = backgroundVisible;
}


SFMLBase::~SFMLBase()
{
}


sf::RenderWindow* SFMLBase::get_default_window()
{
	return defaultWindow;
}


sf::Sprite* SFMLBase::get_background()
{
	return background;
}


int SFMLBase::get_background_mode_x()
{
	return backgroundModeX;
}


int SFMLBase::get_background_mode_y()
{
	return backgroundModeY;
}


int SFMLBase::get_background_alignment_x()
{
	return backgroundAlignmentX;
}


int SFMLBase::get_background_alignment_y()
{
	return backgroundAlignmentY;
}


bool SFMLBase::get_background_visibility()
{
	return backgroundVisible;
}


void SFMLBase::set_default_window(sf::RenderWindow* defaultWindow)
{
	this->defaultWindow = defaultWindow;
}


void SFMLBase::set_background(sf::Sprite* background)
{
	this->background = background;
}


void SFMLBase::set_background_mode_x(int backgroundModeX)
{
	if (backgroundModeX == BACKGROUND::full ||
		backgroundModeX == BACKGROUND::crop ||
		backgroundModeX == BACKGROUND::adjust ||
		backgroundModeX == BACKGROUND::repeat)
		this->backgroundModeX = backgroundModeX;
}


void SFMLBase::set_background_mode_y(int backgroundModeY)
{
	if (backgroundModeY == BACKGROUND::full ||
		backgroundModeY == BACKGROUND::crop ||
		backgroundModeY == BACKGROUND::adjust ||
		backgroundModeY == BACKGROUND::repeat)
		this->backgroundModeY = backgroundModeY;
}


void SFMLBase::set_background_mode(int backgroundModeX, int backgroundModeY)
{
	if (backgroundModeX == BACKGROUND::full ||
		backgroundModeX == BACKGROUND::crop ||
		backgroundModeX == BACKGROUND::adjust ||
		backgroundModeX == BACKGROUND::repeat)
		this->backgroundModeX = backgroundModeX;
	if (backgroundModeY == BACKGROUND::full ||
		backgroundModeY == BACKGROUND::crop ||
		backgroundModeY == BACKGROUND::adjust ||
		backgroundModeY == BACKGROUND::repeat)
		this->backgroundModeY = backgroundModeY;
}


void SFMLBase::set_background_alignment_x(int backgroundAlignmentX)
{
	if (backgroundAlignmentX == LAYOUT::ALIGNMENT::left ||
		backgroundAlignmentX == LAYOUT::ALIGNMENT::right ||
		backgroundAlignmentX == LAYOUT::ALIGNMENT::center)
		this->backgroundAlignmentX = backgroundAlignmentX;
}


void SFMLBase::set_background_alignment_y(int backgroundAlignmentY)
{
	if (backgroundAlignmentY == LAYOUT::ALIGNMENT::top ||
		backgroundAlignmentY == LAYOUT::ALIGNMENT::bottom ||
		backgroundAlignmentY == LAYOUT::ALIGNMENT::center)
		this->backgroundAlignmentY = backgroundAlignmentY;
}


void SFMLBase::set_background_alignment(int backgroundAlignmentX,
	int backgroundAlignmentY)
{
	if (backgroundAlignmentX == LAYOUT::ALIGNMENT::left ||
		backgroundAlignmentX == LAYOUT::ALIGNMENT::right ||
		backgroundAlignmentX == LAYOUT::ALIGNMENT::center)
		this->backgroundAlignmentX = backgroundAlignmentX;
	if (backgroundAlignmentY == LAYOUT::ALIGNMENT::top ||
		backgroundAlignmentY == LAYOUT::ALIGNMENT::bottom ||
		backgroundAlignmentY == LAYOUT::ALIGNMENT::center)
		this->backgroundAlignmentY = backgroundAlignmentY;
}


void SFMLBase::set_background_visibility(bool backgroundVisible)
{
	this->backgroundVisible = backgroundVisible;
}


void SFMLBase::copy(SFMLBase* newSFMLBase)
{
	if (newSFMLBase)
	{
		newSFMLBase->defaultWindow = defaultWindow;
		newSFMLBase->background = background;
		newSFMLBase->backgroundModeX = backgroundModeX;
		newSFMLBase->backgroundModeY = backgroundModeY;
		newSFMLBase->backgroundAlignmentX = backgroundAlignmentX;
		newSFMLBase->backgroundAlignmentY = backgroundAlignmentY;
		newSFMLBase->backgroundVisible = backgroundVisible;
	}
}