#include <rt/integrators/recraytrace.h>
#include <rt/intersection.h>
#include <rt/lights/light.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>


//float OFFSET = 0.0001f;

namespace rt {

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */
    //TODO: continue... need to change it to recursion.
    float offset =  0.0001f;
    RGBColor totalRadiance = RGBColor::rep(0.0f);
    RGBColor emission, reflectance, intensity;
    Intersection intersection = world->scene->intersect(ray);
    if(intersection){
        emission = intersection.solid->material->getEmission(intersection.local(), intersection.normal(), -ray.d);
        totalRadiance = totalRadiance + emission;
        for(int i = 0; i < world->light.size(); i++){
            LightHit lightHit = world->light[i]->getLightHit(intersection.hitPoint());
            //Shift the ray origin towards it's direction by an offset, to avoid self intersection
            Ray shadowRay(intersection.hitPoint() + intersection.normal() * offset, lightHit.direction);
            if(dot(intersection.normal(), shadowRay.d) > 0.0f){
                Intersection shaIntersec = world->scene->intersect(shadowRay, lightHit.distance);
                //If no intersection of shadow ray, or the intersection distnace greater than distance to light source, update radiance
                if(!shaIntersec){
                    intensity = world->light[i]->getIntensity(lightHit);
                    Vector t = cross(lightHit.direction,intersection.normal());
                    emission = intersection.solid->material->getEmission(intersection.local(), intersection.normal(), -ray.d);
                    reflectance = intersection.solid->material->getReflectance(intersection.local(), intersection.normal(),  -ray.d, -shadowRay.d);
                    totalRadiance = totalRadiance + intensity * reflectance;
                }
            }
        }
    }

    return totalRadiance;
}

}