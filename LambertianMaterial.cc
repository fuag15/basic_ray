
#include "LambertianMaterial.h"
#include "HitRecord.h"
#include "Light.h"
#include "Point.h"
#include "Primitive.h"
#include "Ray.h"
#include "RenderContext.h"
#include "Scene.h"
#include "Vector.h"
#include "Math.h"
using namespace std;

LambertianMaterial::LambertianMaterial( const  Color& color, float Kd, float Ka, float Kr, float Ks)
  :color(color), Kd(Kd), Ka(Ka), Kr(Kr), Ks(Ks)
{
}

LambertianMaterial::~LambertianMaterial()
{
}

void LambertianMaterial::shadeRef(Color& result,RenderContext& context,
                               Ray& ray, HitRecord& hit, Color& atten, int depth)
{
	Scene* scene = context.getScene();
	Object* world = scene->getObject();
	Transformation trans;
	Color myResult;
	Color allReflect(0,0,0);
	Color reflected;
	// Ray hit something...
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
	
	for(int i = 0; i < 5; i++)
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

		trans = rotate_by(Angle, normOrig);
		Point finalTip = trans.applied_to(convertedNewTip);

		Vector newDirection = finalTip - Point(0,0,0);
		newDirection.normalize();
		
		Ray newRay(newOrigin, newDirection, ray.time());
		double cost = Dot(newDirection, normal);
		world -> intersect(newHit, context, newRay);
		if(newHit.getPrimitive())
		{
			newHit.getMaterial() -> shade(reflected, context, newRay, newHit, atten, depth + 1);
		}
		else
		{
			(scene->background)->getBackgroundColor(result, context, ray);
			return;
		}
		allReflect += reflected;
		
	}
	
	allReflect /= 5.0;
	
	//result = myResult;
	//Color influenceTest = Color(influence * cost * reflected.r(),influence * cost * reflected.g(),influence * cost * reflected.b());
// 		Color finalColor = Color(scale * reflected.r(),scale * reflected.g(),scale *  reflected.b());
// 		Color colorToMix = Color(invScale *  myResult.r(),invScale * myResult.g(),invScale * myResult.b());
	myResult = allReflect;
	result = myResult;
	return;
		
}


Point LambertianMaterial::sample_hemisphere()
{
	double seedx = rand_double();
	double seedy = rand_double();
// 	Vector w = Vector(0,0,1);
// 	Vector v = Vector(0,1,0);
// 	Vector u = Vector(1,0,0);
	double cos_phi = cos(2.0 * M_PI * seedx);
	double sin_phi = sin(2.0 * M_PI * seedx);
	double cos_theta = pow((1.0 - seedy), 1.0 / (Ks + 1.0));
	double sin_theta = sqrt(1.0 - (cos_theta * cos_theta));
	double pu = sin_theta * cos_phi;
	double pv = sin_theta * sin_phi;
	double pw = cos_theta;
	
	return Point(pu, pw, pv);
}

void LambertianMaterial::shade(Color& result, RenderContext& context,
                               Ray& ray, HitRecord& hit, Color& atten, int depth)
{
    Scene* scene = context.getScene();
    vector<Light*>& lights = scene->getLights();
  Point hitpos = ray.origin()+ray.direction()*hit.minT();
  Vector normal;
  hit.getPrimitive()->normal(normal, context, hitpos, ray, hit);
  double costheta = Dot(normal, ray.direction());
  if(costheta > 0)
    normal = -normal;

    Object* world = scene->getObject();

  Color light = scene->getAmbient()*Ka;

#if 0
  for(vector<Light*>:: _iterator iter = lights.begin(); iter != lights.end(); iter++){
#else
    Light* * begin = &lights[0];
    Light* * end = &lights[0]+lights.size();
    while(begin != end){
#endif
    Color light_color;
    Vector light_direction;
    double dist = (*begin++)->getLight(light_color, light_direction, context, hitpos);
    double cosphi = Dot(normal, light_direction);
    if(cosphi > 0){
      // Cast shadow rays...
      HitRecord shadowhit(dist);
      Ray shadowray(hitpos, light_direction, 0);
      world->intersect(shadowhit, context, shadowray);
      if(!shadowhit.getPrimitive())
        // No shadows...
        light += light_color*(Kd*cosphi);
    }
  }
  
  
  if(Kr > 0.2 && depth <= 0)
  {
	  Color ReflectedLight;
 	  shadeRef(ReflectedLight, context, ray, hit, atten, depth);
	  color = (result *(1.0 - Kr)) + (ReflectedLight * Kr);
// 	  // mix ref
  }
  result = light*color;
}
