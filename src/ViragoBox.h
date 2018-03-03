#ifndef VIRAGO_BOX_H_
#define VIRAGO_BOX_H_

#include "Shapes.h"


namespace virago {

class ViragoBox {
    public:
        explicit ViragoBox(const unsigned int startAddress);
        ~ViragoBox();

        void run();

    private:
        void initLogging(const bool debug);

        unsigned int _address;
};

}


#endif // VIRAGO_BOX_H_

