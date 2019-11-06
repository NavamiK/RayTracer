#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection SimpleGroup::intersect( const Ray& ray, float previousBestDistance) const {
    /* TODO */ 
    Intersection nearestIntersection = Intersection::failure();
    Intersection currentIntersection;
    for (auto iter = primitives.begin(); iter != primitives.end(); ++iter){
        currentIntersection = (*iter)->intersect(ray, previousBestDistance);
        if(currentIntersection){
            nearestIntersection = currentIntersection;
            previousBestDistance = nearestIntersection.distance;
        }
    }
    return nearestIntersection;
}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    /* TODO */ 
    primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
