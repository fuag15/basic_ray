
#ifndef BoundingBox_h
#define BoundingBox_h

#include "Point.h"
#include "Plane.h"
#include "LambertianMaterial.h"
#include "Vector.h"
#include "Ray.h"

class BoundingBox {
 public:
  BoundingBox();
  ~BoundingBox();

  void reset();
  void extend(const Point&);

  Point getMin() const {
    return min;
  }
  Point getMax() const {
    return max;
  }
  void Reset();
  
  bool intersect(HitRecord& hit, const RenderContext&, const Ray& ray) const;
  
  bool pointCheck(const Point& origin) const;
  bool boxCheck(BoundingBox& other) const;
 private:
  Point min, max;
  Plane *x0, *x1, *y0, *y1, *z0, *z1;
  LambertianMaterial *default_material;
};

#endif
