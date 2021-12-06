#include <iostream>
#include <fstream>

#include "RTWeekend.h"
#include "HittableList.h"

#include "Sphere.h"
#include "Camera.h"
#include "Color.h"


color RayColor(const Ray& r, const Hittable& world, int depth) {
    HitRecord rec;

    if(depth <= 0)
    {
        return color(0,0,0);
    }

    if(world.Hit(r, 0.001, infinity, rec)){
        point3 target = rec.p + rec.normal + Random_unit_vector();
        
        return 0.5 * RayColor(Ray(rec.p, target - rec.p), world, depth - 1);
    }
   
    Vec3 unitDirection = UnitVector(r.direction());
    double t = 0.5*(unitDirection.y() + 1.0);
    
    return (1.0 - t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}
 

int main(){
    //IMAGE
    
    const double aspectRatio = 16.0/9.0;
    const int iWidth = 500;
    const int iHeight = (iWidth / aspectRatio);
    const int samplePerPixel = 100;
    const int max_depth = 50;

    //WORLD
    
    HittableList world;
    world.Add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.Add(make_shared<Sphere>(point3(0, -100.5, -1), 100.0));

    //CAMERA

    Camera camera;

    //RENDER

    std::ofstream output;
    output.open("output.ppm");

    output <<"P3\n" << iWidth << " " << iHeight << " \n255\n";

    for(int j = iHeight-1; j>=0; --j){
        
        std::cerr << "\rScanlines remaining (j) : " << j << " " << std::flush; 
        
        for (int i = 0; i < iWidth; ++i) {
            color pixelColor(0,0,0);
            
            for(int s = 0; s < samplePerPixel; s++){
               
               double u = (i + RandomDouble()) / (iWidth-1);
               double v = (j + RandomDouble()) / (iHeight-1);
               Ray r = camera.GetRay(u, v);
               pixelColor += RayColor(r, world, max_depth);
           }
           
           WriteColor(output, pixelColor, samplePerPixel);
        }
    } 
    
    output.close();
    std::cerr << "\nDone.\n";
   
    return 0 ;
}