//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../include/Timer.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "SFML/Graphics/RenderTarget.hpp"

Timer::Timer(const sf::Time startTime) : m_startTime(startTime), m_remainingTime(startTime), m_running(false) {
    if (!m_font.loadFromFile("../../assets/Fonts/SevenSegment.ttf")) {
        std::cerr << "Failed to load timer font" << std::endl;
    }

    m_text.setFont(m_font);
    m_text.setCharacterSize(32);
}

void Timer::Start() {
    if (!m_running) {
        m_running = true;
        m_clock.restart();
    }
}

void Timer::Pause() {
    if (m_running) {
        m_remainingTime -= m_clock.getElapsedTime();
        m_running = false;
    }
}

void Timer::Update() {
    m_text.setString(GetTimeFormatted());
    m_text.setFillColor(m_running ? sf::Color::Green : sf::Color::Red);
}


void Timer::Reset() {
    m_running = false;
    m_remainingTime = m_startTime;
}

void Timer::SetPosition(const sf::Vector2i position) {
    m_text.setPosition(sf::Vector2f(static_cast<float>(position.x), static_cast<float>(position.y)));
}

sf::Time Timer::GetRemainingTime() const {
    if (m_running) {
        return m_remainingTime - m_clock.getElapsedTime();
    }
    return m_remainingTime;
}

std::string Timer::GetTimeFormatted() const {
    const int secondsRemaining = static_cast<int>(GetRemainingTime().asSeconds());
    const int minutes = secondsRemaining / 60;
    const int seconds = secondsRemaining % 60;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":"
            << std::setfill('0') << std::setw(2) << seconds;

    return ss.str();
}


bool Timer::IsFinished() const {
    return GetRemainingTime() <= sf::Time::Zero;
}

void Timer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_text);
}
