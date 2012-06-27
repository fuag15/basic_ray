
#ifndef MovingSphere_h
#define MovingSphere_h

#include "Primitive.h"
#include "Sphere.h"
#include "Point.h"
#include "Vector.h"
class Ray;

class MovingSphere : public Primitive {
 public:
  MovingSphere(Material* material, const Point& center, double radius, double speed, Vector direction);
  virtual ~MovingSphere();

  virtual void getBounds(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;
  virtual bool intersectBox(BoundingBox& bbox) const;
  virtual void normal(Vector& normal, const RenderContext& context,
                      const Point& hitpos, const Ray& ray, const HitRecord& hit) const;
 protected:
  Point center;
  double radius;
  double inv_radius;
  double speed;
  Vector dir;
};

#endif
