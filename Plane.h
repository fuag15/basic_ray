
#ifndef Plane_h
#define Plane_h

#include "Vector.h"
#include "Primitive.h"
#include "HitRecord.h"
#include "RenderContext.h"
//class HitRecord;
class Point;
//class RenderContext;

class Plane : public Primitive {
 public:
  Plane(Material* material, const Vector& n, const Point& point, double w);
  Plane();
  virtual ~Plane();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point & hitpos, const Ray& ray, const HitRecord& hit) const;

  virtual bool intersectBox(BoundingBox& bbox) const;
  Plane& operator=(const Plane&);
 public:
  Point orig;
  Vector n;
 private:
  Plane(const Plane&);
  double width;
  
  double d;
};

#endif

