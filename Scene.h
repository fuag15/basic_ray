
#ifndef Scene_h
#define Scene_h

#include "Color.h"
#include <string>
#include <vector>
#include "Point.h"
#include "Math.h"
#include "HitRecord.h"
#include "Primitive.h"
#include "Transformation.h"

class Background;
class Camera;
class Color;
class Image;
class Light;
class Object;
class RenderContext;
class Ray;

class Scene {
 public:
  Scene();
  virtual ~Scene();

  inline Object* getObject()   {
    return object;
  }
  void setObject(Object* obj) {
    object = obj;
  }
  
  void shade(Color& result, RenderContext& context, Ray& ray, HitRecord& hit, Color& atten, int depth);
  
  Point sample_hemisphere();
  
  void setSampleSize(double ss);

  inline Background* getBackground()   {
    return background;
  }
  void setBackground(Background* bg) {
    background = bg;
  }

  inline Camera* getCamera()   {
    return camera;
  }
  void setCamera(Camera* cam) {
    camera = cam;
  }

  inline Image* getImage()   {
    return image;
  }
  void setImage(Image* im) {
    image = im;
  }

  void addLight(Light* light) {
    lights.push_back(light);
  }
    std::vector<Light*>& getLights()   {
    return lights;
  }

  Color getAmbient()   {
    return ambient;
  }
  void setAmbient(  Color& amb) {
    ambient = amb;
  }

  int getMaxRayDepth()   {
    return maxRayDepth;
  }
  void setMaxRayDepth(int rd) {
    maxRayDepth = rd;
  }
  double getMinAttenuation()   {
    return minAttenuation;
  }
  void setMinAttenuation(double atten) {
    minAttenuation = atten;
  }
  void SetSampleWidth(double dx, double dy);
  void DoubleJitterSwap();
  void DoubleJitterSetup();
  void setShutterTime(double st);
  void preprocess();
  void render();
  double traceRay(Color& result,   RenderContext& context,   Ray& ray,   Color& attenuation, int depth)  ;
  double traceRay(Color& result,   RenderContext& context,   Object* obj,   Ray& ray,   Color& attenuation, int depth)  ;

 public:
  Scene(  Scene&);
  Scene& operator=(  Scene&);

  Background* background;
  Camera* camera;
  Color ambient;
  Image* image;
  Object* object;
  std::vector<Light*> lights;
  int maxRayDepth;
  double minAttenuation;
  double subPixelX[4096];
  double subPixelY[4096];
  double subPixelT[4096];
  int sampleSize;
  int subSampleSize;
  double shutterTime;

};

#endif
