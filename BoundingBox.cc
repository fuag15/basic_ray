
#include "BoundingBox.h"
#include <float.h>

BoundingBox::BoundingBox()
{
  Color defColor(1.,0.,0.);
  default_material = new LambertianMaterial(defColor, 0.6f, 0.3f, 0.0f, 10000.0f);
  min = Point(DBL_MAX, DBL_MAX, DBL_MAX);
  max = Point(-DBL_MAX, -DBL_MAX, -DBL_MAX);
  x0 = new Plane(default_material, Vector(1, 0, 0), min, 1.0);
  x1 = new Plane(default_material, Vector(1, 0, 0), max, 1.0);
  y0 = new Plane(default_material, Vector(0, 1, 0), min, 1.0);
  y1 = new Plane(default_material, Vector(0, 1, 0), max, 1.0);
  z0 = new Plane(default_material, Vector(0, 0, 1), min, 1.0);
  z1 = new Plane(default_material, Vector(0, 0, 1), max, 1.0);
}

void BoundingBox::Reset()
{
  min = Point(DBL_MAX, DBL_MAX, DBL_MAX);
  max = Point(-DBL_MAX, -DBL_MAX, -DBL_MAX);
  delete x0;
  delete x1;
  delete y0;
  delete y1;
  delete z0;
  delete z1;
  x0 = new Plane(default_material, Vector(1, 0, 0), min, 1.0);
  x1 = new Plane(default_material, Vector(1, 0, 0), max, 1.0);
  y0 = new Plane(default_material, Vector(0, 1, 0), min, 1.0);
  y1 = new Plane(default_material, Vector(0, 1, 0), max, 1.0);
  z0 = new Plane(default_material, Vector(0, 0, 1), min, 1.0);
  z1 = new Plane(default_material, Vector(0, 0, 1), max, 1.0);
}

BoundingBox::~BoundingBox()
{
}

void BoundingBox::extend(const Point& p)
{
  min = Min(p, min);
  max = Max(p, max);
  delete x0;
  delete x1;
  delete y0;
  delete y1;
  delete z0;
  delete z1;
  x0 = new Plane(default_material, Vector(1, 0, 0), min, 1.0);
  x1 = new Plane(default_material, Vector(1, 0, 0), max, 1.0);
  y0 = new Plane(default_material, Vector(0, 1, 0), min, 1.0);
  y1 = new Plane(default_material, Vector(0, 1, 0), max, 1.0);
  z0 = new Plane(default_material, Vector(0, 0, 1), min, 1.0);
  z1 = new Plane(default_material, Vector(0, 0, 1), max, 1.0);
}

bool BoundingBox::pointCheck(const Point& origin) const
{
	if((origin.x() > (min.x())) && (origin.x() < (max.x())))
	{
		if((origin.y() > (min.y())) && (origin.y() < (max.y())))
		{
			if((origin.z() > (min.z())) && (origin.z() < (max.z())))
			{
				return true;
			}
		}
	}
	
	return false;
}

bool BoundingBox::boxCheck(BoundingBox& other) const
{
	Point A, B, C, D, E, F, G, H;
	Point a, b, c, d, e, f, g, h;
	Vector WIDTH(fabs(max.x() - min.x()), 0, 0);
	Vector HEIGHT(0, fabs(max.y() - min.y()), 0);
	Vector DEPTH(0, 0, fabs(max.z() - min.z()));
	Vector width(fabs(other.getMax().x() - other.getMin().x()), 0, 0);
	Vector height(0, fabs(other.getMax().y() - other.getMin().y()), 0);
	Vector depth(0, 0, fabs(other.getMax().z() - other.getMin().z()));
	
	A = max;
	B = max - WIDTH;
	C = max - HEIGHT;
	D = max - DEPTH;
	E = min + WIDTH;
	F = min + HEIGHT;
	G = min + DEPTH;
	H = min;
	
	a = other.getMax();
	b = other.getMax() - width;
	c = other.getMax() - height;
	d = other.getMax() - depth;
	e = other.getMin() + width;
	f = other.getMin() + height;
	g = other.getMin() + depth;
	h = other.getMin();
	
	if(other.pointCheck(A))
	{
		return true;
	}
	if(other.pointCheck(B))
	{
		return true;
	}
	if(other.pointCheck(C))
	{
		return true;
	}
	if(other.pointCheck(D))
	{
		return true;
	}
	if(other.pointCheck(E))
	{
		return true;
	}
	if(other.pointCheck(F))
	{
		return true;
	}
	if(other.pointCheck(G))
	{
		return true;
	}
	if(other.pointCheck(H))
	{
		return true;
	}
	if(pointCheck(a))
	{
		return true;
	}
	if(pointCheck(b))
	{
		return true;
	}
	if(pointCheck(c))
	{
		return true;
	}
	if(pointCheck(d))
	{
		return true;
	}
	if(pointCheck(e))
	{
		return true;
	}
	if(pointCheck(f))
	{
		return true;
	}
	if(pointCheck(g))
	{
		return true;
	}
	if(pointCheck(h))
	{
		return true;
	}
	//cerr << "no intersection!" << endl;
	//cerr << 
	return false;
}

bool BoundingBox::intersect(HitRecord& hit, const RenderContext& context, const Ray& ray) const
{
// 	bool regX, regY, regZ;
// 	regX = 1;
// 	regY = 1;
// 	regZ = 1;
// 	bool regEX, regEY, regEZ;
// 	regEX = 1;
// 	regEY = 1;
// 	regEZ = 1;
// 	bool regLX, regLY, regLZ;
// 	regLX = 1;
// 	regLY = 1;
// 	regLZ = 1;
	double ty0, ty1,tx0, tx1, tz0, tz1;
// 	Plane *hitPlaneA, *hitPlaneB;
// 	double tx_min, tx_max, ty_min, ty_max, tz_min, tz_max;
// 	double max_entering, min_leaving;
// 	
// 	HitRecord hitA(DBL_MAX);
// 	x0->intersect(hitA, context, ray);
// 	if(hitA.gotHit())
// 	{
// 		tx0 = hitA.minT();
// 	}
// 	
// 	HitRecord hitB(DBL_MAX);
// 	x1->intersect(hitB, context, ray);
// 	if(hitB.gotHit())
// 	{
// 		tx1 = hitB.minT();
// 	}
// 	
// 	if((hitA.gotHit()) && (!hitB.gotHit()))
// 	{
// 		if( ray.origin().x() <= max.x() && ray.origin().x() >= min.x() )
// 		{
// 			tx_max = tx0;
// 			///ray is leaving
// 			regEX = 0;
// 		}
// 		else
// 		{
// 			tx_min = tx0;
// 			regLX = 0;
// 			///ray is entering
// 		}
// 	}
// 	else if(!hitA.gotHit() && hitB.gotHit())
// 	{
// 		if( ray.origin().x() <= max.x() && ray.origin().x() >= min.x() )
// 		{
// 			tx_max = tx1;
// 			regEX = 0;
// 			///ray is leaving
// 		}
// 		else
// 		{
// 			tx_min = tx1;
// 			regLX = 0;
// 			///ray is entering
// 		}
// 	}
// 	else if(!hitA.gotHit() && !hitB.gotHit())
// 	{
// 		///discard ray planes!
// 		regEX = 0;
// 		regLX = 0;
// 		regX = 0;
// 	}
// 	else
// 	{
// 		///regard ray planes!
// 		//get max entering and min leaving for x
// 		if(tx0 < tx1)
// 		{
// 			tx_min = tx0;
// 			tx_max = tx1;
// 		}
// 		else
// 		{
// 			tx_min = tx1;
// 			tx_max = tx0;
// 		}
// 	}
// 	
// 	HitRecord hitC(DBL_MAX);
// 	y0->intersect(hitC, context, ray);
// 	if(hitC.gotHit())
// 	{
// 		ty0 = hitC.minT();
// 	}
// 	
// 	HitRecord hitD(DBL_MAX);
// 	y1->intersect(hitD, context, ray);
// 	if(hitD.gotHit())
// 	{
// 		ty1 = hitD.minT();
// 	}
// 	
// 	if(hitC.gotHit() && !hitD.gotHit())
// 	{
// 		if( ray.origin().y() <= max.y() && ray.origin().y() >= min.y() )
// 		{
// 			ty_max = ty0;
// 			///ray is leaving
// 			regEY = 0;
// 		}
// 		else
// 		{
// 			ty_min = ty0;
// 			regLY = 0;
// 			///ray is entering
// 		}
// 	}
// 	else if(!hitC.gotHit() && hitD.gotHit())
// 	{
// 		if( ray.origin().y() <= max.y() && ray.origin().y() >= min.y() )
// 		{
// 			ty_max = ty1;
// 			regEY = 0;
// 			///ray is leaving
// 		}
// 		else
// 		{
// 			ty_min = ty1;
// 			regLY = 0;
// 			///ray is entering
// 		}
// 	}
// 	else if(!hitC.gotHit() && !hitD.gotHit())
// 	{
// 		///discard ray planes!
// 		regEY = 0;
// 		regLY = 0;
// 		regY = 0;
// 	}
// 	else
// 	{
// 		///regard ray planes!
// 		//get max entering and min leaving for x
// 		if(ty0 < ty1)
// 		{
// 			ty_min = ty0;
// 			ty_max = ty1;
// 		}
// 		else
// 		{
// 			ty_min = ty1;
// 			ty_max = ty0;
// 		}
// 	}
// 	
// 	HitRecord hitE(DBL_MAX);
// 	z0->intersect(hitE, context, ray);
// 	if(hitE.gotHit())
// 	{
// 		tz0 = hitE.minT();
// 	}
// 	
// 	HitRecord hitF(DBL_MAX);
// 	z1->intersect(hitF, context, ray);
// 	if(hitF.gotHit())
// 	{
// 		tz1 = hitF.minT();
// 	}
// 	
// 	if(hitE.gotHit() && !hitF.gotHit())
// 	{
// 		if( ray.origin().z() <= max.z() && ray.origin().z() >= min.z() )
// 		{
// 			tz_max = tz0;
// 			///ray is leaving
// 			regEZ = 0;
// 		}
// 		else
// 		{
// 			tz_min = tz0;
// 			regLZ = 0;
// 			///ray is entering
// 		}
// 	}
// 	else if(!hitE.gotHit() && hitF.gotHit())
// 	{
// 		if( ray.origin().z() <= max.z() && ray.origin().z() >= min.z() )
// 		{
// 			tz_max = tz1;
// 			regEZ = 0;
// 			///ray is leaving
// 		}
// 		else
// 		{
// 			tz_min = tz1;
// 			regLZ = 0;
// 			///ray is entering
// 		}
// 	}
// 	else if(!hitE.gotHit() && !hitF.gotHit())
// 	{
// 		///discard ray planes!
// 		regEZ = 0;
// 		regLZ = 0;
// 		regZ = 0;
// 	}
// 	else
// 	{
// 		///regard ray planes!
// 		//get max entering and min leaving for x
// 		if(tz0 < tz1)
// 		{
// 			tz_min = tz0;
// 			tz_max = tz1;
// 		}
// 		else
// 		{
// 			tz_min = tz1;
// 			tz_max = tz0;
// 		}
// 	}
// 	
// 	//check for overlap is max of entering les than min of leaving?
// 	//largest entering t value
// 	max_entering = DBL_MIN;
// 	if(regX == 1)
// 	{
// 		if(regEX == 1)
// 		{
// 			if(tx_min > max_entering)
// 			{
// 				max_entering = tx_min;
// 				hitPlaneA = x0;
// 				hitPlaneB = x1;
// 			}
// 		}
// 	}
// 	
// 	if(regY == 1)
// 	{
// 		if(regEY == 1)
// 		{
// 			if(ty_min > max_entering)
// 			{
// 				max_entering = ty_min;
// 				hitPlaneA = y0;
// 				hitPlaneB = y1;
// 			}
// 		}
// 	}
// 	
// 	if(regZ == 1)
// 	{
// 		if(regEZ == 1)
// 		{
// 			if(tz_min > max_entering)
// 			{
// 				max_entering = tz_min;
// 				hitPlaneA = z0;
// 				hitPlaneB = z1;
// 			}
// 		}
// 	}
// 	
// 	//smallest leaving t value
// 	min_leaving = DBL_MAX;
// 	if(regX == 1)
// 	{
// 		if(regLX == 1)
// 		{
// 			if(tx_max < min_leaving)
// 			{
// 				min_leaving = tx_max;
// 			}
// 		}
// 	}
// 	if(regY == 1)
// 	{
// 		if(regLY == 1)
// 		{
// 			if(ty_max < min_leaving)
// 			{
// 				min_leaving = ty_max;
// 			}
// 		}
// 	}
// 	if(regZ == 1)
// 	{
// 		if(regLZ == 1)
// 		{
// 			if(tz_max < min_leaving)
// 			{
// 				min_leaving = tz_max;
// 			}
// 		}
// 	}
// 	
// 	if(max_entering < min_leaving); // && min_leaving > kEpsilon
// 	{
// 		hitPlaneA->intersect(hit, context, ray);
// 		hitPlaneB->intersect(hit, context, ray);
// 		return true;
// 	}
// 	return false;
	
	bool cx0, cx1, cy0, cy1, cz0, cz1;
	cx0 = false;
	cx1 = false;
	cy0 = false;
	cy1 = false;
	cz0 = false;
	cz1 = false;
	double DELTA = 0.01;
	HitRecord hitA(DBL_MAX);
	x0->intersect(hitA, context, ray);
	if(hitA.gotHit())
	{
		tx0 = hitA.minT();
		if( pointCheck(ray.origin() + (ray.direction() * (tx0*1.01))))
		{
			cx0 = true;
		}
	}
	
	HitRecord hitB(DBL_MAX);
	x1->intersect(hitB, context, ray);
	if(hitB.gotHit())
	{
		tx1 = hitB.minT();
		if( pointCheck(ray.origin() + (ray.direction() * (tx1*1.01))))
		{
			cx1 = true;
		}
	}
	
	HitRecord hitC(DBL_MAX);
	y0->intersect(hitC, context, ray);
	if(hitC.gotHit())
	{
		ty0 = hitC.minT();
		if( pointCheck(ray.origin() + (ray.direction() * (ty0*1.01))))
		{
			cy0 = true;
		}
	}
	
	HitRecord hitD(DBL_MAX);
	y1->intersect(hitD, context, ray);
	if(hitD.gotHit())
	{
		ty1 = hitD.minT();
		if( pointCheck(ray.origin() + (ray.direction() * (ty1*1.01))))
		{
			cy1 = true;
		}
	}
	
	HitRecord hitE(DBL_MAX);
	z0->intersect(hitE, context, ray);
	if(hitE.gotHit())
	{
		tz0 = hitE.minT();
		if( pointCheck(ray.origin() + (ray.direction() * (tz0*1.01))))
		{
			cz0 = true;
		}
	}
	
	HitRecord hitF(DBL_MAX);
	z1->intersect(hitF, context, ray);
	if(hitF.gotHit())
	{
		tz1 = hitF.minT();
		if( pointCheck(ray.origin() + (ray.direction() * (tz1*1.01))))
		{
			cz1 = true;
		}
	}
	
	double minimumHit = DBL_MAX;
	bool gotHit = false;
	int hitPlane;
	//0 = x1, 1 = x1, 2= y0, 3 = y1, 4 = z0, 5 = z1
	
	if(cx0 == true && tx0 < minimumHit)
	{
		minimumHit = tx0;
		gotHit = true;
		hitPlane = 0;
	}
	
	if(cx1 == true && tx1 < minimumHit)
	{
		minimumHit = tx1;
		gotHit = true;
		hitPlane = 1;
	}
	
	if(cy0 == true && ty0 < minimumHit)
	{
		minimumHit = ty0;
		gotHit = true;
		hitPlane = 2;
	}
	
	if(cy1 == true && ty1 < minimumHit)
	{
		minimumHit = ty1;
		gotHit = true;
		hitPlane = 3;
	}
	
	if(cz0 ==true && tz0 < minimumHit)
	{
		minimumHit = tz0;
		gotHit = true;
		hitPlane = 4;
	}
	
	if(cz1 ==true && tz1 < minimumHit)
	{
		minimumHit = tz1;
		gotHit = true;
		hitPlane = 5;
	}
	
	if(gotHit == true && minimumHit != DBL_MAX)
	{
		if(hitPlane == 0)
		{
			x0->intersect(hit, context, ray);
		}
		else if(hitPlane == 1)
		{
			x1->intersect(hit, context, ray);
		}
		else if(hitPlane == 2)
		{
			y0->intersect(hit, context, ray);
		}
		else if(hitPlane == 3)
		{
			y1->intersect(hit, context, ray);
		}
		else if(hitPlane == 4)
		{
			z0->intersect(hit, context, ray);
		}
		else if(hitPlane == 5)
		{
			z1->intersect(hit, context, ray);
		}
		else
		{
			cerr << "fuck this shit" << endl;
		}
		return true;
	}
	
	return false;
}
