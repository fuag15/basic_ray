
#ifndef Material_h
#define Material_h

class Color;
class HitRecord;
class Ray;
class RenderContext;

class Material {
 public:
  Material();
  virtual ~Material();

  virtual void preprocess();
  virtual void shade(Color& result, RenderContext& context, Ray& ray,
                     HitRecord& hit, Color& atten, int depth) = 0;

 private:
  Material(const Material&);
  Material& operator=(const Material&);
};

#endif

