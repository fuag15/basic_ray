
#include "Group.h"
#include "BoundingBox.h"
#include <iostream>
#include <istream>
using namespace std;

Group::Group(double d)
{
	depth = d;
}

Group::~Group()
{
}

void Group::addObject(Object* object)
{
  objects.push_back(object);
}

bool Group::intersectBox(BoundingBox& bbox) const
{
	BoundingBox objectBox;
	getBounds(objectBox);

	return objectBox.boxCheck(bbox);
}

void Group::preprocess()
{
  //tree = new OctTree(depth, objects);
  Object*const* begin = &objects[0];
  Object*const* end = &objects[0]+objects.size();
  while (begin != end)
    (*begin++)->preprocess();
}

void Group::getBounds(BoundingBox& bbox) const
{
  Object*const* begin = &objects[0];
  Object*const* end = &objects[0]+objects.size();
  while (begin != end)
    (*begin++)->getBounds(bbox);
}

void Group::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
  //std::vector<Object*> Hobjects;
  //tree->getObjectsHit(hit, context, ray, Hobjects);
  Object*const* begin = &objects[0];
  Object*const* end = &objects[0]+objects.size();
  //Object*const* begin = &objects[0];
  //Object*const* end = &objects[0]+objects.size();
//   if(begin == end)
//   {
//       //cerr << "Whoops" << endl;
//       //cerr << ray.origin() << endl;
//       cerr << ray.direction() << endl;
//       //exit(1);
//   }
  while (begin != end)
  {
    //cerr << "got an object" << endl;
    (*begin++)->intersect(hit, context, ray);
  }
}
