
#include "Sphere.h"
#include "MovingSphere.h"
#include "BoundingBox.h"
#include "HitRecord.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include <math.h>

MovingSphere::MovingSphere(Material* material, const Point& center, double radius, double speed, Vector direction)
  : Primitive(material), center(center), radius(radius), speed(speed), dir(direction)
{
  dir.normalize();
  inv_radius = 1./radius;
}

MovingSphere::~MovingSphere()
{
}

bool MovingSphere::intersectBox(BoundingBox& bbox) const
{
	BoundingBox objectBox;
	getBounds(objectBox);

	return objectBox.boxCheck(bbox);
}

void MovingSphere::getBounds(BoundingBox& bbox) const
{
  Vector diag(radius, radius, radius);
  bbox.extend(center+diag);
  bbox.extend(center-diag);
  bbox.extend((center+(dir*speed))+diag);
  bbox.extend((center+(dir*speed))-diag);
  //bbox.extend((center-(dir*speed))+diag);
  //bbox.extend((center-(dir*speed))-diag);
}

void MovingSphere::intersect(HitRecord& hit, const RenderContext&, const Ray& ray) const
{
  Vector O(ray.origin()-(center+(dir*(speed*ray.time()))));
  const Vector& V(ray.direction());
  double b = Dot(O, V);
  double c = Dot(O, O)-radius*radius;
  double disc = b*b-c;
  if(disc > 0){
    double sdisc = sqrt(disc);
    double root1 = (-b - sdisc);
    if(!hit.hit(root1, this, matl)){
      double root2 = (-b + sdisc);
      hit.hit(root2, this, matl);
    }
  }
}

void MovingSphere::normal(Vector& normal, const RenderContext&, const Point& hitpos,
                    const Ray& ray, const HitRecord& hit) const
{
  normal = (hitpos-(center+(dir*(speed*ray.time()))))*inv_radius;
}
