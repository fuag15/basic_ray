
#ifndef Ray_h
#define Ray_h

#include "Point.h"
#include "Vector.h"

class Ray {
 public:
  Ray() {
  }
  Ray(const Point& origin, const Vector& direction, double time)
    : org(origin), dir(direction), t(time) {
  }
    
  ~Ray() {
  }
  Ray(const Ray& copy)
    : org(copy.org), dir(copy.dir), t(copy.t) {
  }
  Ray& operator=(const Ray& copy) {
    org = copy.org;
    dir = copy.dir;
    t = copy.t;
    return *this;
  }

  const Point& origin() const {
    return org;
  }
  const Vector& direction() const {
    return dir;
  }
  const double time() const {
    return t;
  }
 private:
   Point org;
   Vector dir;
   double t;
};

#endif
