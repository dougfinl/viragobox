#ifndef SFML_RENDERER_H_
#define SFML_RENDERER_H_

#include "Shapes.h"
#include <SFML/Graphics.hpp>


namespace virago {

class SFMLRenderer {
    public:
        explicit SFMLRenderer(const unsigned int resX, const unsigned int resY, const bool fullscreen);
        ~SFMLRenderer();

        void start();
        void stop();

        void updateRectangleFromPercentages(float intens, float posX, float posY, float width, float height, float r, float g, float b, float line);
        void showAlignmentGrid(bool show=true);

    private:
        void runLoop();

        unsigned int     _resX;
        unsigned int     _resY;
        bool             _fullscreen;
        sf::RenderWindow _window;
        Rectangle        _rectangle;
        bool             _showAlignmentGrid;
};

} // namespace virago


#endif // SFML_RENDERER_H_

