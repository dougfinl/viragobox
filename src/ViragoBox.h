#ifndef VIRAGO_BOX_H_
#define VIRAGO_BOX_H_

#include "Shapes.h"
#include <memory>


namespace virago {

class ViragoBox {
    public:
        explicit ViragoBox(const unsigned int startAddress);
        ~ViragoBox();

        void run();

    private:
        void initLogging(const bool debug);

        std::shared_ptr<Rectangle> _rectangle;
        unsigned int _address;
};

}


#endif // VIRAGO_BOX_H_

