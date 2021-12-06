#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

// container d'un object qui peut être hit

struct HitRecord {
    point3 p;
    Vec3 normal;
    double t;
    bool frontFace;

    inline void SetFaceNormal(const Ray& r, const Vec3& outwardNormal){
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal :-outwardNormal;
    }
};

class Hittable {
    public:
        virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif