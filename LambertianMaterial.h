
#ifndef LambertianMaterial_h
#define LambertianMaterial_h

#include "Material.h"
#include "Color.h"
#include "Point.h"
#include "HitRecord.h"
#include "Vector.h"
#include "Transformation.h"
#include "Background.h"
#include <float.h>
#include <iostream>
#include <stdlib.h>

class LambertianMaterial : public Material {
 public:
  LambertianMaterial( const Color& color, float Kd, float Ka, float Kr, float Ks);
  virtual ~LambertianMaterial();

  virtual void shade(Color& result, RenderContext& context, Ray& ray,
                     HitRecord& hit, Color& atten, int depth);
		     
   void shadeRef(Color& result, RenderContext& context,
                               Ray& ray, HitRecord& hit, Color& atten, int depth);
			       
	Point sample_hemisphere();

 private:
  LambertianMaterial(  LambertianMaterial&);
  LambertianMaterial& operator=(  LambertianMaterial&);

  Color color;
  float Kd;
  float Ka;
  float Kr;
  float Ks;
};

#endif
