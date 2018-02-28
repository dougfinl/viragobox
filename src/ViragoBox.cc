#include "ViragoBox.h"
#include "SFMLRenderer.h"


namespace virago {

ViragoBox::ViragoBox() {
}

ViragoBox::~ViragoBox() {
}

void ViragoBox::run() {
    SFMLRenderer r;
    r.start();
}

}

