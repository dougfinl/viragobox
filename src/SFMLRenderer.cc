#include "SFMLRenderer.h"


namespace virago {

SFMLRenderer::SFMLRenderer() {
}

SFMLRenderer::~SFMLRenderer() {
}

void SFMLRenderer::start() {
    _window.create(sf::VideoMode(800, 600), "Virago Rear Projection Renderer");

    return this->runLoop();
}

void SFMLRenderer::stop() {
}

void SFMLRenderer::runLoop() {
    while (_window.isOpen()) {
        sf::Event event;

        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }

        _window.clear(sf::Color::Black);

        sf::RectangleShape rect(sf::Vector2f(120, 50));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(10);
        rect.setOutlineColor(sf::Color(250, 150, 100));
        _window.draw(rect);

        _window.display();
    }
}

} // namespace virago

