#ifndef CAMERA_H
#define CAMERA_H

#include "RTWeekend.h"

class Camera {
    public:
        Camera() {
            double aspectRatio = 16.0 / 9.0;
            double viewportHeight = 2.0;
            double viewportWidth = aspectRatio * viewportHeight;
            double focalLen = 1.0;

            origin = point3(0, 0, 0);
            horizontal = Vec3(viewportWidth, 0.0, 0.0);
            vertical = Vec3(0.0, viewportHeight, 0.0);
            lowerLeftCorner = origin - horizontal/2 - vertical/2 - Vec3(0,0, focalLen);
        }

        Ray GetRay(double u, double v) const {
            return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
        }

    private:
        point3 origin;
        point3 lowerLeftCorner;
        Vec3 horizontal;
        Vec3 vertical;
};
#endif