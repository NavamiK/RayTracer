#include <rt/cameras/orthographic.h>
#include <rt/ray.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
{
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->scaleX = scaleX / 2;
    this->scaleY = scaleY / 2;
    this->spanX = cross(forward, up).normalize();
    //this->spanY = cross(forward, spanX).normalize(); this computation for the exact images in A01
    this->spanY = cross(spanX, forward).normalize(); 
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
    Vector d;
    x = x * scaleX;
    y = y * scaleY;
    Point center_ray_origin  = center + x * spanX + y * spanY;
    Ray primaryRay(center_ray_origin, forward);
    return primaryRay;
}

}
