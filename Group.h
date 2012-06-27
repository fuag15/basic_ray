
#ifndef Group_h
#define Group_h

#include "Object.h"
#include "OctTree.h"
#include <vector>

class Group : public Object {
 public:
  Group(double depth);
  virtual ~Group();

  void addObject(Object* object);
  virtual void preprocess();
  virtual void getBounds(BoundingBox& bbox) const;
  virtual bool intersectBox(BoundingBox& bbox) const;
  virtual void intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const;

 protected:
  std::vector<Object*> objects;
  //OctTree* tree;
  double depth;

 private:
  Group(const Group&);
  Group& operator=(const Group&);
};

#endif

