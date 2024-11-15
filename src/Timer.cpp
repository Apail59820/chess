//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../include/Timer.h"

Timer::Timer(const sf::Time startTime) : m_startTime(startTime), m_remainingTime(startTime), m_running(false) {
    // CTOR
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

void Timer::Reset() {
    m_running = false;
    m_remainingTime = m_startTime;
}

sf::Time Timer::GetRemainingTime() const {
    if (m_running) {
        return m_remainingTime - m_clock.getElapsedTime();
    }
    return m_remainingTime;
}

bool Timer::IsFinished() const {
    return GetRemainingTime() <= sf::Time::Zero;
}
