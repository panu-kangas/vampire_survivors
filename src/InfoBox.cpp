#include "InfoBox.hpp"
#include "Game.h"


InfoBox::InfoBox(Game* gamePtr)
{
	m_pGame = gamePtr;
	m_font = gamePtr->getFont();
}

void InfoBox::setText(std::vector<std::string> texts)
{
	m_textVec = texts;

	size_t maxSize = 0;
	for (auto& text : m_textVec)
	{
		size_t textSize = text.size();
		if (textSize > maxSize)
			maxSize = textSize;
	}

	m_size.x = maxSize * (m_fontSize / 2);
	m_size.y = m_textVec.size() * m_lineHeight + 40.f;
}


void InfoBox::render(sf::RenderTarget& target, sf::RenderStates& states) const
{
	// Draw background box
    sf::RectangleShape background(m_size);
    background.setPosition(m_position);
    background.setFillColor(m_bgColor);
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(2.f);
    target.draw(background);

	// Prepare text
    if (!m_font)
        return;

	sf::Text text;
    text.setFont(*m_font);
    text.setCharacterSize(m_fontSize);
    text.setFillColor(sf::Color::White);

	int curRow = 0;
	for (auto& line : m_textVec)
	{
		text.setString(line);
		text.setPosition(m_position.x + 20.f, m_position.y + curRow * m_lineHeight + 10.f); // Padding
		target.draw(text);
		curRow++;
	}
}
