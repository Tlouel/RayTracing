#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "Vec3.h"
#include "RTWeekend.h"


void WriteColor(std::ostream &out, color pixelColor, int samplesPerPixel){
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    //diviser la couleur par le nombre de samples.
    double scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    //ecrire la couleur
    out << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
}

#endif
