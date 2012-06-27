
#include "DOFCamera.h"
#include "Ray.h"
#include "Math.h"
#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

DOFCamera::DOFCamera(const Point& eye, const Point& lookat, const Vector& up,
                             double hfov, double radius, double viewd, double focalp)
  : eye(eye), lookat(lookat), up(up), hfov(hfov), lens_radius(radius), d(viewd), f(focalp)
{
	srand( (unsigned)time( NULL ) );
}

DOFCamera::~DOFCamera()
{
}

void DOFCamera::preprocess(double aspect_ratio)
{
  Vector temp;
  lookdir = lookat-eye;
  lookdir.normalize();
  u = Cross(lookdir, up);
  v = Cross(u, lookdir);
  double ulen = tan(hfov/2.*M_PI/180.);
  u.normalize();
  u *= ulen;
  double vlen = ulen/aspect_ratio;
  v.normalize(); 
  v *= vlen;
  viewPoint = eye + (lookdir*d);
  focalPoint = viewPoint + (lookdir*f);
}

void DOFCamera::makeRay(Ray& ray, const RenderContext& context, double x, double y, double t) const
{
	
	double theta = (M_PI*2.0)*rand_double();
	
	double lensRad = sqrt(rand_double());
	
	double sx = (lens_radius*lensRad)*cos(theta);
	double ty = (lens_radius*lensRad)*sin(theta);
	
	double ratio = (f+d)/d;
	Point focusPoint = focalPoint + (u*(x*ratio)) + (v*(y*ratio));
	Point lensPoint = eye + u*sx + v*ty;
	
	Vector direction = focusPoint - lensPoint;
		
	direction.normalize();
	ray = Ray(lensPoint, direction, t);
}
