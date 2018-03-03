#ifndef VIRAGO_BOX_H_
#define VIRAGO_BOX_H_

#include "Shapes.h"
#include "DMXListener.h"
#include "SFMLRenderer.h"
#include <memory>


namespace virago {

struct ViragoBoxOptions {
    unsigned int resX       = 1024;
    unsigned int resY       = 768;
    unsigned int fullscreen = false;
    unsigned int address    = 1;
    bool debug              = false;
};

class ViragoBox {
    public:
        explicit ViragoBox(const ViragoBoxOptions options);
        ~ViragoBox();

        void run();

    private:
        void initLogging(const bool debug);

        std::unique_ptr<DMXListener>  _dmx;
        std::unique_ptr<SFMLRenderer> _renderer;
};

}


#endif // VIRAGO_BOX_H_

