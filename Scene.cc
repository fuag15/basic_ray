
#include "Scene.h"
#include "Background.h"
#include "Camera.h"
#include "HitRecord.h"
#include "Image.h"
#include "Light.h"
#include "Material.h"
#include "Math.h"
#include "Object.h"
#include "Ray.h"
#include "RenderContext.h"
#include <float.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

void Scene::shade(Color& result, RenderContext& context,
                               Ray& ray, HitRecord& hit, Color& atten, int depth)
{
	Transformation trans;
	Color myResult;
	Color allReflect(0,0,0);
	Color reflected;
	if(depth >= 1)
	{
		///END RECURSION
		if(hit.getPrimitive()){
			// Ray hit something...
			Material* matl = hit.getMaterial();
			matl->shade(result, context, ray, hit, atten, 0);
		} else {
			background->getBackgroundColor(result, context, ray);
		}
		return;
	}
	if(hit.getPrimitive()){
		// Ray hit something...
		Material* matl = hit.getMaterial();
		matl->shade(myResult, context, ray, hit, atten, 0);
		
		
		Point hitPos = ray.origin() + (ray.direction() * hit.minT());
		Point newOrigin = hitPos;
		HitRecord newHit(DBL_MAX);
		Vector normal;
		hit.getPrimitive()->normal(normal, context, hitPos, ray, hit);
		double Angle = Dot(normal, Vector(0,1,0));
		Angle /= normal.length();
		Angle = acos(Angle);
		
		Angle /= 2.0 * M_PI;
		Angle *= 360.0;
		Vector normOrig = Cross(normal, Vector(0.0083,1.003,0.0083));
		normOrig.normalize();
		trans = rotate_by(Angle, normOrig);
		Point tip = Point(0,0,0) + normal;
		Point convertedTip = trans.applied_to(tip);
		
		if(convertedTip.y() <= 0.0)
		{
			Angle = -Angle;
			trans = rotate_by(Angle, normOrig);
			convertedTip = trans.applied_to(tip);
		}
		
		for(int i = 0; i < 10; i++)
		{
			Point newDir = sample_hemisphere();
			Vector randVec = newDir - Point(0,0,0);
			Vector normNew = Cross( Vector(0.0083,1.003,0.0083), randVec);
			double AngleNew = Dot(Vector(0,1,0), randVec);
			AngleNew /= randVec.length();
			AngleNew = acos(AngleNew);
			AngleNew /= 2.0 * M_PI;
			AngleNew *= 360.0;
			normNew.normalize();
			trans = rotate_by(AngleNew, normNew);
			//Point newTip = Point(0,0,0) + randVec;
			Point convertedNewTip = trans.applied_to(convertedTip);
			
			if(convertedNewTip.y() <= 0.0)
			{
				AngleNew = -AngleNew;
				trans = rotate_by(AngleNew, normNew);
				convertedNewTip = trans.applied_to(convertedTip);
			}

			trans = rotate_by(-Angle, normOrig);
			Point finalTip = trans.applied_to(convertedNewTip);

			Vector newDirection = finalTip - Point(0,0,0);
			newDirection.normalize();
			
			Ray newRay(newOrigin, newDirection, ray.time());
			double cost = Dot(newDirection, normal);
			reflected;
			object -> intersect(newHit, context, newRay);
			shade(reflected, context, newRay, newHit, atten, depth + 1);
			Point nextHit = newRay.origin() + (newRay.direction() * newHit.minT());
			Vector dVec = nextHit - hitPos;
			double distance = dVec.length();
			double influence = distance / 8.0;
			if(influence > 1.0)
			{
				influence = 1.0;
			}
			
			influence = 1.0 - influence;
			
			allReflect += Color(influence * cost * reflected.r(),influence * cost * reflected.g(),influence * cost * reflected.b());
		}
		
		allReflect /= 10.0;
		
		//result = myResult;
		//Color influenceTest = Color(influence * cost * reflected.r(),influence * cost * reflected.g(),influence * cost * reflected.b());
// 		Color finalColor = Color(scale * reflected.r(),scale * reflected.g(),scale *  reflected.b());
// 		Color colorToMix = Color(invScale *  myResult.r(),invScale * myResult.g(),invScale * myResult.b());
		double scale = 0.3;
		myResult = myResult + allReflect;
		//result = myResult;
		result = myResult;
		// my result = this
		return;
		
	} else {
		background->getBackgroundColor(result, context, ray);
		return;
	}
		
}

// void MovingSphere::normal(Vector& normal,   RenderContext&,   Point& hitpos,
//                       Ray& ray,   HitRecord& hit)  

//  Color TracePath(Ray r,depth) {
//    if(depth == MaxDepth)
//      return Black;  // bounced enough times
// 
//    r.FindNearestObject();
//    if(r.hitSomething == false)
//      return Black;  // nothing was hit
// 
//    Material m = r.thingHit->material;
//    Color emittance = m.emittance;
// 
//    // pick a random direction from here and keep going
//    Ray newRay;
//    newRay.origin = r.pointWhereObjWasHit;
//    newRay.direction = RandomUnitVectorInHemisphereOf(r.normalWhereObjWasHit);
//    float cost = DotProduct(newRay.direction, r.normalWhereObjWasHit);
// 
//    Color BRDF = m.reflectance/PI;
//    float scale = 1.0*PI;
//    Color reflected = TracePath(newRay,depth+1);
// 
//    // return emittance + ( BRDF * scale * cost * reflected );
//    return emittance + ( BRDF * scale * reflected );
//  }


Point Scene::sample_hemisphere()
{
	double seedx = rand_double();
	double seedy = rand_double();
// 	Vector w = Vector(0,0,1);
// 	Vector v = Vector(0,1,0);
// 	Vector u = Vector(1,0,0);
	double cos_phi = cos(2.0 * M_PI * seedx);
	double sin_phi = sin(2.0 * M_PI * seedx);
	double cos_theta = pow((1.0 - seedy), 1.0 / (10 + 1.0));
	double sin_theta = sqrt(1.0 - (cos_theta * cos_theta));
	double pu = sin_theta * cos_phi;
	double pv = sin_theta * sin_phi;
	double pw = cos_theta;
	
	return Point(pu, pw, pv);
}

// xd = x
// yd = 1.0 - y
// zd = z;
// 
// unitSpaceV = normal.x + xd, normal.y + yd, normal.z + zd
// 
// offsetVec = uSV.x + rV.x, uSV.y + (1.0 - rV.y), usV.z + rV.z)
// 
// normal = oV.x - xd, oV.y -yd, oV.z - zd;!!!


Scene::Scene()
{
  srand( (unsigned)time( NULL ) );
  object = 0;
  background = 0;
  camera = 0;
  ambient = Color(0, 0, 0);
  image = 0;
  minAttenuation = 0;
  sampleSize = 16.;
  shutterTime = 2.;
  subSampleSize = sqrt(sampleSize);
  DoubleJitterSetup();
}

Scene::~Scene()
{
  delete object;
  delete background;
  delete camera;
  delete image;
  for(int i=0;i<static_cast<int>(lights.size());i++){
    Light* light = lights[i];
    delete light;
  }
}

void Scene::preprocess()
{
  background->preprocess();
  for(int i=0;i<static_cast<int>(lights.size());i++){
    Light* light = lights[i];
    light->preprocess();
  }
  double aspect_ratio = image->aspect_ratio();
  camera->preprocess(aspect_ratio);
  object->preprocess();
}

void Scene::setShutterTime(double st)
{
	shutterTime = st;
	DoubleJitterSetup();
}

void Scene::setSampleSize(double ss) 
{
	  sampleSize = ss;
	  subSampleSize = sqrt(ss);
	  DoubleJitterSetup();
}

void Scene::DoubleJitterSetup()
{
	double base = (((double)subSampleSize)/((double)sampleSize));
	for(int i=0;i<subSampleSize;i++)//x
	{
		for(int j=0;j<subSampleSize;j++)//y
		{
			subPixelX[(j*subSampleSize)+i]=(((double)i)/((double)sampleSize))+(rand_double()/((double)sampleSize)) + (base*((double)j));
			subPixelY[(j*subSampleSize)+i]=(((double)j)/((double)sampleSize))+(rand_double()/((double)sampleSize)) + (base*((double)i));
			subPixelT[(j*subSampleSize)+i]=rand_double_range(shutterTime);
		}
	}
	
// 	for(int i=0;i<sampleSize;i++)
// 	{
// 		subPixelT[i] = rand_double_range(shutterTime);
// 	}
	
	DoubleJitterSwap();
}

void Scene::DoubleJitterSwap()
{
	int random;
	double temp;
	for(int i=0;i<sampleSize;i++){
		random = rand_int(sampleSize);
		temp = subPixelX[i];
		subPixelX[i] = subPixelX[random];
		subPixelX[random] = temp;
	}
	
	for(int i=0;i<sampleSize;i++){
		random = rand_int(sampleSize);
		temp = subPixelY[i];
		subPixelY[i] = subPixelY[random];
		subPixelY[random] = temp;
	}
	
	for(int i=0;i<sampleSize;i++){
		random = rand_int(sampleSize);
		temp = subPixelT[i];
		subPixelT[i] = subPixelT[random];
		subPixelT[random] = temp;
	}
}

void Scene::SetSampleWidth(double dx, double dy)
{
	for(int i=0;i<sampleSize;i++){
		subPixelX[i] = subPixelX[i]*dx;
		subPixelY[i] = subPixelY[i]*dy;
	}
}

void Scene::render()
{
  Color returnColor(0,0,0);
  if(!object || !background || !camera || !image){
    cerr << "Incomplete scene, cannot render!\n";
    exit(1);
  }
  int xres = image->getXresolution();
  int yres = image->getYresolution();
  RenderContext context(this);
  double dx = 2./xres;
  double xmin = -1. + dx/2.;
  double dy = 2./yres;
  double ymin = -1. + dy/2.;
  SetSampleWidth(dx, dy);
  Color atten(1,1,1);
  for(int i=0;i<yres;i++){
    //cerr << "y=" << i << '\n';
    double y = ymin + i*dy;
    for(int j=0;j<xres;j++){
      double x = xmin + j*dx;
      returnColor = Color(0,0,0);
      // replace this with 16*16 of theese!
      //cerr << "x=" << j << ", y=" << i << '\n';
      DoubleJitterSetup();
      SetSampleWidth(dx, dy);
     for(int k=0;k<sampleSize;k++){
	Ray ray;
	camera->makeRay(ray, context, x+subPixelX[k], y+subPixelY[k], subPixelT[k]);
	HitRecord hit(DBL_MAX);
	object->intersect(hit, context, ray);
	Color result;
// 	if(hit.getPrimitive()){
// 		// Ray hit something...
// 		  Material* matl = hit.getMaterial();
// 		matl->shade(result, context, ray, hit, atten, 0);
// 	} else {
// 		background->getBackgroundColor(result, context, ray);
// 	}
	shade(result, context, ray, hit, atten, 0);
	returnColor += result/(double)sampleSize;
     }
     
      
      //end repace replase set with the normalized 16!
      image->set(j, i, returnColor);
    }
  }
}

double Scene::traceRay(Color& result, RenderContext& context, Ray& ray, Color& atten, int depth)
{
  if(depth >= maxRayDepth || atten.maxComponent() < minAttenuation){
    result = Color(0, 0, 0);
    return 0;
  } else {
    HitRecord hit(DBL_MAX);
    object->intersect(hit, context, ray);
    if(hit.getPrimitive()){
      // Ray hit something...
      Material* matl = hit.getMaterial();
      matl->shade(result, context, ray, hit, atten, depth);
      return hit.minT();
    } else {
      background->getBackgroundColor(result, context, ray);
      return DBL_MAX;
    }
  }
}

double Scene::traceRay(Color& result,   RenderContext& context,   Object* obj,   Ray& ray,   Color& atten, int depth)  
{
  if(depth >= maxRayDepth || atten.maxComponent() < minAttenuation){
    result = Color(0, 0, 0);
    return 0;
  } else {
    HitRecord hit(DBL_MAX);
    obj->intersect(hit, context, ray);
    if(hit.getPrimitive()){
      // Ray hit something...
        Material* matl = hit.getMaterial();
      matl->shade(result, context, ray, hit, atten, depth);
      return hit.minT();
    } else {
      background->getBackgroundColor(result, context, ray);
      return DBL_MAX;
    }
  }
}
