#include "vec3.h"
#include "interval.h"
#include "color.h"
#include <iostream>

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    // Writes color to console, correcting it using gamma correction.
    // Useful for render to file.

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Apply the linear to gamma transform.
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Write the translated [0,255] value of each color component.
    static const interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

color negative(color c){
    // Returns the negative of the color
    return color(1.0 - c.x(), 1.0 - c.y(), 1.0 - c.z());
}