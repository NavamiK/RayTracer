#include <rt/solids/cylinder.h>
#include <cmath>

namespace rt{
    Cylinder::Cylinder(float radius, float yMin, float yMax, rt::CoordMapper *texMapper, rt::Material *material) {
        this->radius = radius;
        this->yMin = yMin;
        this->yMax = yMax;
        this->texMapper = texMapper;
        this->material = material;
    }

    Intersection Cylinder::intersect(const rt::Ray &ray, float previousBestDistance) const {
        // logic from pbrt book.
        float a = ray.d.x * ray.d.x + ray.d.z * ray.d.z;
        float b = 2.f * (ray.d.x * ray.o.x + ray.d.z * ray.o.z);
        float c = (ray.o.x * ray.o.x) + (ray.o.z * ray.o.z) - radius * radius;

        //solve qaudratic equation for t.
        float discriminant = b * b - 4.f * a * c;
        if(discriminant < 0){
            return Intersection::failure();
        }

        float t0 = (-b - sqrt(discriminant)) / (2.f * a);
        float t1 = (-b + sqrt(discriminant)) / (2.f * a);
        float distance;

        //TODO: switch from t0 to t1 later.
        float pd = previousBestDistance;
        if(t0 > pd  || t1 < 0.f){
            return Intersection::failure();
        }

        distance = t0;
        if(distance <= 0.f){
            distance = t1;
            if(distance > pd) 
                return Intersection::failure();
        }

        Point hitPoint = ray.getPoint(distance);

        //refine hit points.
        float hitRadius = sqrt(hitPoint.x * hitPoint.x + hitPoint.z * hitPoint.z);
        hitPoint.x *= radius/hitRadius;
        hitPoint.z *= radius/hitRadius;
        float phi = atan2(hitPoint.z, hitPoint.x);
        if(phi < 0) phi = phi + 2.f * pi;

        // Test cylinder intersection against clipping parameters
        if (hitPoint.y < yMin || hitPoint.y > yMax) {
            if (distance == t1) return Intersection::failure();
            distance = t1;
            if (t1 > pd) return Intersection::failure();
            // Compute cylinder hit point and $\phi$
            hitPoint = ray.getPoint(distance);

            // Refine cylinder intersection point
//            float hitRad = std::sqrt(hitPoint.x * hitPoint.x + hitPoint.z * hitPoint.z);
//            hitPoint.x *= radius / hitRad;
//            hitPoint.z *= radius / hitRad;
//            phi = std::atan2(hitPoint.z, hitPoint.x);
//            if (phi < 0) phi += 2 * pi;

            if (hitPoint.y < yMin || hitPoint.y > yMax) return Intersection::failure();
        }

        // normal idea taken here:
        //https://stackoverflow.com/questions/36266357/how-can-i-compute-normal-on-the-surface-of-a-cylinder
        Vector normal = (hitPoint - Point(0.f, hitPoint.y, 0.f)).normalize();

        //TODO: I should have to calculate the parametric version ofthe points. do later.
        Intersection intersection(distance, ray, this, normal, hitPoint);

        return intersection;

    }

    BBox Cylinder::getBounds() const {
        NOT_IMPLEMENTED;
//        Point pMin(-radius, -radius, yMin);
//        Point pMax(radius, radius, yMax);
//        return (BBox(pMin, pMax));
    }

    float Cylinder::getArea() const {
        NOT_IMPLEMENTED;
        //similar to width*height.
       // return (yMax - yMin) * radius * phiMax;
    }

    Solid::Sample Cylinder::sample() const {
        NOT_IMPLEMENTED;
    }
};