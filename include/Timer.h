//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef TIMER_H
#define TIMER_H
#include <string>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"

class Timer : public sf::Drawable {
public:
    explicit Timer(sf::Time startTime);

    void Start();

    void Pause();

    void Update();

    void Reset();

    void SetPosition(sf::Vector2i position);

    [[nodiscard]] sf::Time GetRemainingTime() const;

    [[nodiscard]] std::string GetTimeFormatted() const;

    [[nodiscard]] bool IsFinished() const;

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Clock m_clock;
    sf::Time m_startTime;
    sf::Time m_remainingTime;
    bool m_running;

    sf::Font m_font;
    sf::Text m_text;
};


#endif //TIMER_H
