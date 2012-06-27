
#include "Plane.h"
#include "HitRecord.h"
#include "BoundingBox.h"
#include "Math.h"
#include "Ray.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Plane::Plane(Material* material, const Vector& normal, const Point& point, double w)
  : Primitive(material), n(normal)
{
  orig = point;
  width = w;
  n.normalize();
  d = Dot(n, point);
}

bool Plane::intersectBox(BoundingBox& bbox) const
{
	BoundingBox objectBox;
	getBounds(objectBox);

	return objectBox.boxCheck(bbox);
}

Plane::Plane() : Primitive(new LambertianMaterial(Color(1.0,1.0,1.0), 0.6, 0.3, 0.0, 1000.0))
{
}

Plane::~Plane()
{
}

void Plane::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
  double denom = Dot(n, ray.direction());
  if(Abs(denom) > 1.e-6){
    double t = (d-Dot(n, ray.origin()))/denom;
    hit.hit(t, this, matl);
  }
}

void Plane::normal(Vector& normal, const RenderContext&,
                   const Point&, const Ray&, const HitRecord&) const
{
  normal = n;
}

void Plane::getBounds(BoundingBox& bbox) const
{
  bbox.extend(Point(orig.x()+width, orig.y()+.02, orig.z()+width));
  bbox.extend(Point(orig.x()-width, orig.y()-.02, orig.z()-width));
}

