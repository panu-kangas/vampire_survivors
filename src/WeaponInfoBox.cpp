#include "WeaponInfoBox.hpp"
#include "Game.h"
#include "Constants.h"

WeaponInfoBox::WeaponInfoBox(Game* gamePtr, std::vector<Weapon*> weaponVec) : 
		m_weaponVec(weaponVec),
		m_bgBox(gamePtr)
{
	std::vector<std::string> infoText = {"Weapons"};

	m_bgBox.initInfoBox(infoText, 23.f, sf::Color(242, 134, 39, 200));

	float padding = 20.0f;
	float gap = 10.0f;
	float bgSizeX = padding * 2 + m_weaponVec.size() * weaponAreaSize.x + (m_weaponVec.size() - 1) * gap;
	float bgSizeY = padding * 4 + weaponAreaSize.y;
	m_bgBox.setSize({bgSizeX, bgSizeY});
	m_bgBox.setPosition({ScreenWidth / 2 - m_bgBox.getSize().x / 2, 0});
	m_bgBox.centerText();

	sf::Vector2f renderPos;
	renderPos.x = m_bgBox.getPosition().x + padding;
	renderPos.y = m_bgBox.getPosition().y + m_bgBox.getSize().y * 0.4;
	for (int i = 0; i < m_weaponVec.size(); ++i)
	{
		WeaponInfoRenderer temp{gamePtr, m_weaponVec[i], renderPos};
		m_renderVec.push_back(temp);
		renderPos.x += weaponAreaSize.x + gap;
	}

}

void WeaponInfoBox::update(float deltaTime)
{
	for (auto& renderer : m_renderVec)
	{
		renderer.update(deltaTime);
	}
}


void WeaponInfoBox::render(sf::RenderTarget& target, sf::RenderStates states)
{
	m_bgBox.render(target, states);

	for (auto& renderer : m_renderVec)
	{
		renderer.render(target);
	}
}