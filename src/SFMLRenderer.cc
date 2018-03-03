#include "SFMLRenderer.h"
#include <boost/log/trivial.hpp>
#include <algorithm>


namespace virago {

SFMLRenderer::SFMLRenderer() {
    _rectangle = {
        1.0,
        Position{100, 100},
        Dimensions{10, 10},
        RGBColor{255, 255, 255},
        2
    };
}

SFMLRenderer::~SFMLRenderer() {
}

void SFMLRenderer::start() {
    _window.create(sf::VideoMode(800, 600), "Virago Rear Projection Renderer");

    return this->runLoop();
}

void SFMLRenderer::stop() {
}

void SFMLRenderer::updateRectangleFromPercentages(float intens, float posX, float posY, float width, float height, float r, float g, float b, float line) {
    const auto renderWidth  = _window.getSize().x;
    const auto renderHeight = _window.getSize().y;
    const auto maxRenderDim = std::max(renderWidth, renderHeight);

    _rectangle.pos.x = renderWidth/2 + renderWidth*(posX-0.5);
    _rectangle.pos.y = renderHeight/2 - renderHeight*(posY-0.5);

    _rectangle.size.width  = maxRenderDim * width;
    _rectangle.size.height = maxRenderDim * height;

    _rectangle.color.r = intens * r * 255;
    _rectangle.color.g = intens * g * 255;
    _rectangle.color.b = intens * b * 255;

    _rectangle.lineThickness = line * 20;

    BOOST_LOG_TRIVIAL(trace) << "(" << _rectangle.color.r << "," << _rectangle.color.g << "," << _rectangle.color.b << ")";
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

        sf::RectangleShape rect;
        rect.setOrigin(_rectangle.size.width/2, _rectangle.size.height/2);
        rect.setPosition(sf::Vector2f(_rectangle.pos.x, _rectangle.pos.y));
        rect.setSize(sf::Vector2f(_rectangle.size.width, _rectangle.size.height));
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color(_rectangle.color.r, _rectangle.color.g, _rectangle.color.b));
        rect.setOutlineThickness(_rectangle.lineThickness);

        _window.draw(rect);

        _window.display();
    }
}

} // namespace virago

