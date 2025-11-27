#include "../include/StudentCard.hpp"
#include <cmath>

StudentCard::StudentCard(int id, const std::string& name, const sf::Font& font, sf::Vector2f startPos)
    : m_studentId(id), m_currentPos(startPos), m_targetPos(startPos) 
{
    // Configuration du rectangle
    m_shape.setSize(sf::Vector2f(120, 40));
    m_shape.setFillColor(sf::Color(100, 149, 237)); // Cornflower Blue
    m_shape.setOutlineThickness(2);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setPosition(m_currentPos);

    // Configuration du texte
    m_text.setFont(font);
    m_text.setString(name);
    m_text.setCharacterSize(18);
    m_text.setFillColor(sf::Color::White);

    // Centrage du texte
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    m_text.setPosition(m_currentPos.x + 60, m_currentPos.y + 20); // 60 = width/2, 20 = height/2
}

void StudentCard::update(float dt) {
    // Interpolation linéaire (Lerp) pour fluidifier le mouvement
    sf::Vector2f diff = m_targetPos - m_currentPos;
    
    // Si la distance est significative, on bouge
    if (std::abs(diff.x) > 0.5f || std::abs(diff.y) > 0.5f) {
        m_currentPos += diff * ANIMATION_SPEED * dt;
        m_shape.setPosition(m_currentPos);
        m_text.setPosition(m_currentPos.x + 60, m_currentPos.y + 20);
    }
}

void StudentCard::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
    window.draw(m_text);
}

void StudentCard::setTargetPosition(sf::Vector2f target) {
    m_targetPos = target;
}

sf::Vector2f StudentCard::getCenter() const {
    return sf::Vector2f(m_currentPos.x + 60, m_currentPos.y + 20);
}