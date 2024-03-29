
#ifndef HitRecord_h
#define HitRecord_h

#include <iostream>
#include <istream>
//#include <cstdlib>

using namespace std;

class Material;
class Primitive;
#define EPSILON (1.e-6)

class HitRecord {
 public:
  HitRecord(double max) {
    hitThing = 0;
    prim = 0;
    matl = 0;
    min = max;
  }
  ~HitRecord() {
  }
  bool hit(double t, const Primitive* hit_prim, Material* hit_matl) {
    if(t > EPSILON && t < min){
      min = t;
      prim = hit_prim;
      matl = hit_matl;
      hitThing = 1;
      return true;
    } else {
      return false;
    }
  }
  bool gotHit()
  {
	  return hitThing;
  }
  double minT() const {
    return min;
  }
  const Primitive* getPrimitive() const {
    return prim;
  }
  Material* getMaterial() {
    return matl;
  }
  template< typename T >
    T* getScratchpad()
  {
    char unnamed[ ( sizeof( T ) <= sizeof( scratchdata ) ) ? 1 : 0 ];
    return reinterpret_cast< T * >( scratchdata );
  }
  template< typename T >
    const T* getScratchpad() const
  {
    char unnamed[ ( sizeof( T ) <= sizeof( scratchdata ) ) ? 1 : 0 ];
    return reinterpret_cast< const T * >( scratchdata );
  }
 private:
  const Primitive* prim;
  Material* matl;
  double min;
  bool hitThing;

  char scratchdata[128];
};

#endif
