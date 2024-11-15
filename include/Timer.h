//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef TIMER_H
#define TIMER_H
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"

class Timer {
public:
    explicit Timer(sf::Time startTime);

    void Start();

    void Pause();

    void Reset();

    [[nodiscard]] sf::Time GetRemainingTime() const;

    [[nodiscard]] bool IsFinished() const;

private:
    sf::Clock m_clock;
    sf::Time m_startTime;
    sf::Time m_remainingTime;
    bool m_running;
};


#endif //TIMER_H
