#ifndef SFML_RENDERER_H_
#define SFML_RENDERER_H_

#include <SFML/Graphics.hpp>


namespace virago {

class SFMLRenderer {
    public:
        SFMLRenderer();
        ~SFMLRenderer();

        void start();
        void stop();

    private:
        void runLoop();

        sf::RenderWindow _window;
};

} // namespace virago


#endif // SFML_RENDERER_H_

