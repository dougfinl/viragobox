#include "SFMLRenderer.h"
#include <boost/log/trivial.hpp>
#include <algorithm>


namespace virago {

SFMLRenderer::SFMLRenderer(const unsigned int resX, const unsigned int resY, const bool fullscreen) :
        _resX(resX), _resY(resY), _fullscreen(fullscreen), _renderMode(NORMAL) {
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
    if (_fullscreen) {
        _window.create(sf::VideoMode(_resX, _resY), "ViragoBox", sf::Style::Fullscreen);
    } else {
        _window.create(sf::VideoMode(_resX, _resY), "ViragoBox", sf::Style::Titlebar);
    }

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

void SFMLRenderer::setRenderMode(RenderMode renderMode) {
    _renderMode = renderMode;
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

        if (_renderMode == NORMAL) {
            // Render the normal rectangle
            sf::RectangleShape rect;
            rect.setOrigin(_rectangle.size.width/2, _rectangle.size.height/2);
            rect.setPosition(sf::Vector2f(_rectangle.pos.x, _rectangle.pos.y));
            rect.setSize(sf::Vector2f(_rectangle.size.width, _rectangle.size.height));
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color(_rectangle.color.r, _rectangle.color.g, _rectangle.color.b));
            rect.setOutlineThickness(_rectangle.lineThickness);

            _window.draw(rect);
        } else if (_renderMode == TEST_GRID) {
            int windowWidth  = _window.getSize().x;
            int windowHeight = _window.getSize().y;

            // Extreme bounding box
            sf::RectangleShape bounds;
            bounds.setSize(sf::Vector2f(windowWidth-20, windowHeight-20));
            bounds.setPosition(sf::Vector2f(10, 10));
            bounds.setOutlineThickness(10);
            bounds.setFillColor(sf::Color::Transparent);
            bounds.setOutlineColor(sf::Color::Red);

            // Horizonal centre line
            sf::RectangleShape horiz;
            horiz.setSize(sf::Vector2f(windowWidth, 0));
            horiz.setPosition(sf::Vector2f(0, windowHeight/2));
            horiz.setOutlineThickness(5);
            horiz.setFillColor(sf::Color::Transparent);
            horiz.setOutlineColor(sf::Color::Red);

            // Vertical centre line
            sf::RectangleShape vert;
            vert.setSize(sf::Vector2f(0, windowHeight));
            vert.setPosition(sf::Vector2f(windowWidth/2, 0));
            vert.setOutlineThickness(5);
            vert.setFillColor(sf::Color::Transparent);
            vert.setOutlineColor(sf::Color::Red);

            // Centre circle
            int r = windowWidth/8;
            sf::CircleShape circ(r);
            circ.setPosition(sf::Vector2f(windowWidth/2-r, windowHeight/2-r));
            circ.setOutlineThickness(10);
            circ.setFillColor(sf::Color::Transparent);
            circ.setOutlineColor(sf::Color::Red);

            _window.draw(bounds);
            _window.draw(horiz);
            _window.draw(vert);
            _window.draw(circ);
        } else if (_renderMode == TEST_BARS) {
            int windowWidth7  = _window.getSize().x/7;
            int windowHeight = _window.getSize().y;

            sf::RectangleShape white;
            white.setFillColor(sf::Color::White);
            white.setSize(sf::Vector2f(windowWidth7, windowHeight));
            white.setPosition(sf::Vector2f(0, 0));
            
            sf::RectangleShape yellow;
            yellow.setFillColor(sf::Color::Yellow);
            yellow.setSize(sf::Vector2f(windowWidth7, windowHeight));
            yellow.setPosition(sf::Vector2f(windowWidth7, 0));

            sf::RectangleShape cyan;
            cyan.setFillColor(sf::Color::Cyan);
            cyan.setSize(sf::Vector2f(windowWidth7, windowHeight));
            cyan.setPosition(sf::Vector2f(windowWidth7*2, 0));

            sf::RectangleShape green;
            green.setFillColor(sf::Color::Green);
            green.setSize(sf::Vector2f(windowWidth7, windowHeight));
            green.setPosition(sf::Vector2f(windowWidth7*3, 0));

            sf::RectangleShape magenta;
            magenta.setFillColor(sf::Color::Magenta);
            magenta.setSize(sf::Vector2f(windowWidth7, windowHeight));
            magenta.setPosition(sf::Vector2f(windowWidth7*4, 0));

            sf::RectangleShape red;
            red.setFillColor(sf::Color::Red);
            red.setSize(sf::Vector2f(windowWidth7, windowHeight));
            red.setPosition(sf::Vector2f(windowWidth7*5, 0));

            sf::RectangleShape blue;
            blue.setFillColor(sf::Color::Blue);
            blue.setSize(sf::Vector2f(windowWidth7, windowHeight));
            blue.setPosition(sf::Vector2f(windowWidth7*6, 0));

            _window.draw(white);
            _window.draw(yellow);
            _window.draw(cyan);
            _window.draw(green);
            _window.draw(magenta);
            _window.draw(red);
            _window.draw(blue);
        }

        _window.display();
    }
}

} // namespace virago

