#ifndef VIRAGO_BOX_H_
#define VIRAGO_BOX_H_


namespace virago {

class ViragoBox {
    public:
        ViragoBox();
        ~ViragoBox();

        void run();

    private:
        void initLogging(const bool debug);
};

}


#endif // VIRAGO_BOX_H_

