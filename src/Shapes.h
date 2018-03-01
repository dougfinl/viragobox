#ifndef SHAPES_H_
#define SHAPES_H_


namespace virago {

struct Position {
    unsigned int x;
    unsigned int y;
};

struct Dimensions {
    unsigned int width;
    unsigned int height;
};

struct RGBColor {
    unsigned int r;
    unsigned int g;
    unsigned int b;
};

struct Rectangle {
    float        intensity;
    Position     pos;
    Dimensions   size;
    RGBColor     color;
    unsigned int lineThickness;
};

} // namespace virago


#endif // SHAPES_H_
