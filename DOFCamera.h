
#ifndef DOFCamera_h
#define DOFCamera_h

#include "Camera.h"
#include "Point.h"
#include "Vector.h"

class DOFCamera : public Camera {
 public:
  DOFCamera(const Point& eye, const Point& lookat, const Vector& up, double hfov, double radius, double viewd, double focalp);
  virtual ~DOFCamera();
  
  virtual void preprocess(double aspect_ratio);
  virtual void makeRay(Ray& ray, const RenderContext& context, double x, double y, double t) const;

 private:
  DOFCamera(const DOFCamera&);
  DOFCamera& operator=(const DOFCamera&);

  Point eye;
  Point viewPoint;
  Point focalPoint;
  Point lookat;
  Vector up;
  double hfov;

  double lens_radius;
  double d; //view plane distance
  double f; //focal plane distance
  Vector u;
  Vector v;
  Vector lookdir;
};

#endif

