#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(point3 cen, double r) : center(cen), radius(r) {};

        virtual bool Hit(
            const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    public:
        point3 center;
        double radius;
};

bool Sphere::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    
    Vec3 oc = r.origin() - center;

    double a = r.direction().length_squared();
    double halfB = dot(oc, r.direction());
    double c = oc.length_squared() - radius*radius;

    double discriminant = halfB*halfB - a*c;
    
    if (discriminant < 0) 
        return false;
    
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    
    double root = ( -halfB - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-halfB + sqrtd) / a;
        
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    
    Vec3 outwardNormal = (rec.p - center) / radius;
    rec.SetFaceNormal(r, outwardNormal);
    
    return true;
}

#endif