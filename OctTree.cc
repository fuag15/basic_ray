#include "OctTree.h"
#include <float.h>
#include <iostream>
#include <istream>
//#include <cstdlib>

using namespace std;

OctTree::OctTree(int depth, std::vector<Object*> &objs)
{
	gotHere = 0;
	debugRuns = 1;
	OctTreeNode* cursor;
	Point maxBound, minBound;
	start.is_start = 1;
	start.is_leaf = 0;
	start.has_objects = 0;
	Object*const* begin = &objs[0];
	Object*const* end = &objs[0]+objs.size();
	while (begin != end)
	{
		(*begin++)->getBounds(start.bbox);
	}
	
	Point newMin = Point((start.bbox.getMin().x() * 1.1), (start.bbox.getMin().y() * 1.1), (start.bbox.getMin().z()*1.1));
	Point newMax = Point((start.bbox.getMax().x() * 1.1), (start.bbox.getMax().y() * 1.1), (start.bbox.getMax().z() * 1.1));
	start.bbox.extend(newMin);
	start.bbox.extend(newMax);
	//start.bbox.extend(Point(1, 1, 1));
	//start.bbox.extend(Point(-1, -1, -1));
	
	//start.bbox.extend(Point(10, 10, 10));
	//start.bbox.extend(Point(-10,-10,-10));
	
	//cerr << "X: " << start.bbox.getMin().x() << " Y: " << start.bbox.getMin().y() << " Z: " << start.bbox.getMin().z() << endl;
	//cerr << "X: " << start.bbox.getMax().x() << " Y: " << start.bbox.getMax().y() << " Z: " << start.bbox.getMax().z() << endl;
	///create depth of nodes
	initialize(&start, depth);
	
	
	
	
	begin = &objs[0];
	end = &objs[0]+objs.size();
	while (begin != end)
	{
		
		addObject(start, *(begin++));
		
	}
	
	Debug();
}

void OctTree::mergeList(std::vector<Object*> &src, std::vector<Object*> &dest)
{
	Object*const* beginSrc = &src[0];
	Object*const* endSrc = &src[0]+src.size();
	
	Object*const* beginDest = &dest[0];
	Object*const* endDest = &dest[0]+dest.size();
	
	if(dest.empty())
	{
		if(src.empty())
		{
			cerr << "shouldn't get here either" << endl;
			return;
		}
		else
		{
			while(beginSrc != endSrc)
			{
				dest.push_back(*beginSrc++);
			}
		}
	}
	else
	{
		while(beginSrc != endSrc)
		{
			while(beginDest != endDest)
			{
				if(*beginSrc != *beginDest)
				{
					dest.push_back(*beginSrc);
				}
				
				beginDest++;
			}
			beginSrc++;
		}
	}
}

void OctTree::initialize(OctTreeNode* cursor, int countdown) /// CHECKED
{
	//cerr << cursor->bbox.getMin() << endl;
	//cerr << cursor->bbox.getMax() << endl;
	//cerr << endl;
	cursor->is_leaf = 1;
	if(countdown == 0)
	{
		return;
	}
	cursor->is_leaf = 0;
	//cerr << countdown << endl;
	Point maxBound, minBound, newMax, newMin;
	minBound = cursor->bbox.getMin();
	maxBound = cursor->bbox.getMax();
	//cerr << cursor->bbox.getMin() << endl;
	//cerr << cursor->bbox.getMax() << endl;
	//cerr << "-----" << endl;
	
	double width;
	double height;
	double depth;
	
	//cerr << maxBound.x() << endl;
	//cerr << minBound.x() << endl;
// 	if((maxBound.x() > 0) && (minBound.x() < 0))
// 	{
// 		width = maxBound.x() - minBound.x();
// 	}
// 	else if((maxBound.x() > 0) && (minBound.x() > 0))
// 	{
// 		width = maxBound.x() - minBound.x();
// 	}
// 	else // thier both less than 0
// 	{
// 		width = 
// 	}
	
	//cerr << width << endl;
	width = fabs(maxBound.x() - minBound.x());
	height = fabs(maxBound.y() - minBound.y());
	depth = fabs(maxBound.z() - minBound.z());
	//width *= 1.1;
	//height *= 1.1;
	//depth *= 1.1;
	double halfWidth = (width/2.);//*1.001;
	double halfHeight = (height/2.);//*1.001;
	double halfDepth = (depth/2.);//*1.001;
	double negDepth = minBound.z()*1.01;
	double negWidth = minBound.x()*1.01;
	double negHeight = minBound.y()*1.01;
// 	maxBound.x() = maxBound.x()*1.01;
// 	maxBound.y() = maxBound.y()*1.01;
// 	maxBound.z() = maxBound.z()*1.01;
// 	minBound.x() = minBound.x()*1.01;
// 	minBound.y() = minBound.y()*1.01;
// 	minBound.z() = minBound.z()*1.01;
	
	cursor->TF = new OctTreeNode;
// 	newMax = minBound + Vector(width, height, depth);
	newMax = maxBound;
	newMin = maxBound + Vector(-halfWidth, -halfHeight, -halfDepth);
// 	newMin = Point((maxBound.x()-(halfWidth)), (maxBound.y()-(halfHeight)), (maxBound.z()-(halfDepth)));
	cursor->TF->bbox.extend(newMax);
	cursor->TF->bbox.extend(newMin);
	cursor->TF->is_leaf = 1;
	cursor->TF->has_objects = 0;
	cursor->TF->parent = cursor;
	cursor->TF->is_start = 0;
	
	cursor->BB = new OctTreeNode;
/*	newMin = maxBound + Vector(-width, -height, -depth);*/
// 	cursor->BB->bbox.extend(minBound);
// 	cursor->BB->bbox.extend(newMin);
	newMin = minBound;
	newMax = minBound + Vector(halfWidth, halfHeight, halfDepth);
	cursor->BB->bbox.extend(newMax);	
	cursor->BB->bbox.extend(newMin);
	cursor->BB->is_leaf = 1;
	cursor->BB->has_objects = 0;
	cursor->BB->parent = cursor;
	cursor->BB->is_start = 0;
	
	cursor->TR = new OctTreeNode;
// 	newMax = minBound + Vector(width, height, halfDepth);
 	newMax = maxBound + Vector(0,0,-(halfDepth));
// 	newMax = Point(maxBound.x(), maxBound.y(), (maxBound.z()-halfDepth));
// 	newMin = maxBound + Vector(-(halfWidth), -(halfHeight), -depth);
	newMin = minBound + Vector(halfWidth, halfHeight, 0);
// 	newMin = Point(maxBound.x()-halfWidth, maxBound.y()-halfHeight, minBound.z());
	cursor->TR->bbox.extend(newMax);
	cursor->TR->bbox.extend(newMin);
	cursor->TR->is_leaf = 1;
	cursor->TR->has_objects = 0;
	cursor->TR->parent = cursor;
	cursor->TR->is_start = 0;
	
	cursor->TL = new OctTreeNode;
// 	newMax = Point(maxBound.x()-halfWidth, maxBound.y(), maxBound.z());
// 	newMax = minBound + Vector(halfWidth, height, depth);
	newMax = maxBound + Vector(-(halfWidth),0, 0);
	newMin = minBound + Vector(0, halfHeight, halfDepth);
// 	newMin = maxBound + Vector(-width, -(halfHeight), -(halfDepth));
// 	newMin = Point(minBound.x(), maxBound.y()-halfHeight, maxBound.z()-halfDepth);
	cursor->TL->bbox.extend(newMax);
	cursor->TL->bbox.extend(newMin);
	cursor->TL->is_leaf = 1;
	cursor->TL->has_objects = 0;
	cursor->TL->parent = cursor;
	cursor->TL->is_start = 0;
	
	cursor->TB = new OctTreeNode;
// 	newMax = Point(maxBound.x()-halfWidth, maxBound.y(), maxBound.z()-halfDepth); 
// 	newMax = minBound + Vector(halfWidth, height, halfDepth);
	newMax = maxBound + Vector(-(halfWidth),0, -(halfDepth));
// 	newMin = maxBound + Vector(-width, -(halfHeight), -depth);
	newMin = minBound + Vector(0, halfHeight, 0);
// 	newMin = Point(minBound.x(), maxBound.y()-halfHeight, minBound.z());
	cursor->TB->bbox.extend(newMax);
	cursor->TB->bbox.extend(newMin);
	cursor->TB->is_leaf = 1;
	cursor->TB->has_objects = 0;
	cursor->TB->parent = cursor;
	cursor->TB->is_start = 0;
	
	cursor->BF = new OctTreeNode;
// 	newMax = Point(maxBound.x(), maxBound.y()-halfHeight, maxBound.z());
// 	newMax = minBound + Vector(width, halfHeight, depth);
	newMax = maxBound + Vector(0,-(halfHeight), 0);
// 	newMin = Point(maxBound.x()-halfWidth, minBound.y(), maxBound.z()-halfDepth);
// 	newMin = maxBound + Vector(-(halfWidth), -height, -(halfDepth));
	newMin = minBound + Vector(halfWidth, 0, halfDepth);
	cursor->BF->bbox.extend(newMax);
	cursor->BF->bbox.extend(newMin);
	cursor->BF->is_leaf = 1;
	cursor->BF->has_objects = 0;
	cursor->BF->parent = cursor;
	cursor->BF->is_start = 0;
	
	cursor->BR = new OctTreeNode;
// 	newMax = Point(maxBound.x(), maxBound.y()-halfHeight, maxBound.z()-halfDepth);
// 	newMax = minBound + Vector(width, halfHeight, halfDepth);
	newMax = maxBound + Vector(0, -halfHeight, -halfDepth);
// 	newMax = maxBound + Vector(0,-(halfHeight), -(halfDepth));
// 	newMin = Point(maxBound.x()-halfWidth, minBound.y(), minBound.z());
	newMin = minBound + Vector(halfWidth, 0, 0);
// 	newMin = maxBound + Vector(-(halfWidth), -height, -depth);
	cursor->BR->bbox.extend(newMax);
	cursor->BR->bbox.extend(newMin);
	cursor->BR->is_leaf = 1;
	cursor->BR->has_objects = 0;
	cursor->BR->parent = cursor;
	cursor->BR->is_start = 0;
	
	cursor->BL = new OctTreeNode;
// 	newMax = Point(maxBound.x()-halfWidth, maxBound.y()-halfHeight, maxBound.z());
// 	newMax = minBound + Vector(halfWidth, halfHeight, depth);
	newMax = maxBound + Vector(-(halfWidth),-(halfHeight), 0);
// 	newMax = Point(minBound.x(), minBound.y(), maxBound.z()-halfHeight);
	newMin = minBound + Vector(0, 0, halfDepth);
// 	newMin = maxBound + Vector(-width, -height, -(halfHeight));
	cursor->BL->bbox.extend(newMax);
	cursor->BL->bbox.extend(newMin);
	cursor->BL->is_leaf = 1;
	cursor->BL->has_objects = 0;
	cursor->BL->parent = cursor;
	cursor->BL->is_start = 0;
	
	//cerr << "made 8 sub quadrants" << endl;
	
	initialize(cursor->TF, (countdown-1));
	initialize(cursor->TL, (countdown-1));
	initialize(cursor->TR, (countdown-1));
	initialize(cursor->TB, (countdown-1));
	initialize(cursor->BF, (countdown-1));
	initialize(cursor->BR, (countdown-1));
	initialize(cursor->BL, (countdown-1));
	initialize(cursor->BB, (countdown-1));
	
}

void OctTree::addObject(OctTreeNode &node, Object* obj) ///CHECKED
{
	//cerr << "got here" << endl;
	BoundingBox bbox;
	///add object into apropriate leafs!
	if(node.is_leaf)
	{
// 		cerr << "GOT TO BOTTOM" << endl;
		node.has_objects = true;
		node.objects.push_back(obj);
		//zcerr << node.objects.size() << endl;
		return;
	}
	//box is in this quadrant TF
	if(obj->intersectBox(node.TF->bbox))
	{
// 		cerr << "TF has object" << endl;
		node.has_objects = true;
		addObject(*node.TF, obj);
	}
	
	//box is in this quadrant TL
	if(obj->intersectBox(node.TL->bbox))
	{
// 		cerr << "TL has object" << endl;
		node.has_objects = true;
		addObject(*node.TL, obj);
	}
	
	//box is in this quadrant TR
	if(obj->intersectBox(node.TR->bbox))
	{
// 		cerr << "TR has object" << endl;
		node.has_objects = true;
		addObject(*node.TR, obj);
	}
	
	//box in this quadrant TB
	if(obj->intersectBox(node.TB->bbox))
	{
// 		cerr << "TB has object" << endl;
		node.has_objects = true;
		addObject(*node.TB, obj);
	}
	
	//box in this quadrant BF
	if(obj->intersectBox(node.BF->bbox))
	{
// 		cerr << "BF has object" << endl;
		node.has_objects = true;
		addObject(*node.BF, obj);
	}
	
	//box in this quadrant BL
	if(obj->intersectBox(node.BL->bbox))
	{
// 		cerr << "BL has object" << endl;
		node.has_objects = true;
		addObject(*node.BL, obj);
	}
	
	//box in this quadrant BR
	if(obj->intersectBox(node.BR->bbox))
	{
// 		cerr << "BR has object" << endl;
		node.has_objects = true;
		addObject(*node.BR, obj);
	}
	
	//box in this quadrant BB
	if(obj->intersectBox(node.BB->bbox))
	{
// 		cerr << "BB has object" << endl;
		node.has_objects = true;
		addObject(*node.BB, obj);
	}
}

void OctTree::getObjectsHit(HitRecord& hit, const RenderContext& context, const Ray& ray, std::vector<Object*> &dest)
{
	Point current;
	///make sure first point is in boxxes!!!
	HitRecord hitT(DBL_MAX);
	//if((ray.direction().x() == -0.0529509) && (ray.direction().y() == -0.147316) && (ray.direction().z() == -0.987671))
	//{
	//	cerr << "GOT IT" << endl;
	//}
	if(start.bbox.pointCheck(ray.origin()))
	{
		//cerr << "got a ray in the box" << endl;
		//cerr << ray.origin() << endl;
		getObjectsHitHelper(start, ray, ray.origin(), dest);
		return;
		//exit(1);
	}
	else if(start.bbox.intersect(hitT, context, ray))
	{
		//cerr << "got a ray that intersects the box" << endl;
		//cerr << hitT.minT() << endl;
		//cerr << "DBL_MAX" << DBL_MAX << endl;
		//cerr << (ray.origin() + (ray.direction()*(hit.minT()))) << endl;
		//cerr << ray.origin() << endl;
		//exit( 1);
		current = ray.origin() + (ray.direction()*(hitT.minT()*1.01));
		//if(ray.direction().x() <= -0.13 && ray.direction().y() <= -0.13)
		//{
		//	cerr << current << endl;
		//	if(debugRuns <= 0)
		//	{
		//		exit(1);
		//	}
		//	debugRuns--;
		//}
		//cerr << current << endl;
		//cerr << start.bbox.getMin() << endl;
		//cerr << start.bbox.getMax() << endl;
		
// 		while(!start.bbox.pointCheck(current))
// 		{
// 			//cerr << ray.origin() << endl;
// 			//cerr << ray.direction() << endl;
 			//cerr << current << endl;
// 			cerr << "death" << endl;
// 			//exit(1);
// 			break;
// 			//current += ray.direction()*.02;
// 			//cerr << current << endl;
// 			
// 			if(start.bbox.pointCheck(current))
// 			{
// 				//exit(1);
// 			}
// 		}
		//exit(1);
// 		if( start.bbox.pointCheck(current))
// 		{
// 			//cerr << (ray.origin() + (ray.direction()*(hit.minT()))) << endl;
// // 			cerr << "so good" << endl;
// 			//exit(1);
// 			
// 		}
		getObjectsHitHelper(start, ray, current, dest);
	}
	else
	{
		//cerr << "Got a ray that did not intersect" << endl;
	}
	return;
	
}

void OctTree::Debug()///CHECKED
{
	cerr << "Oct Tree Debug Starting" << endl;
	cout << "========================" << endl;
	cout << "========================" << endl;
	cout << "========================" << endl<< endl;
	DebugHelper(start, 1);
}

void OctTree::DebugHelper(OctTreeNode& cursor, int depth) ///CHECKED
{
	if(cursor.has_objects)
	{
		cout << "A node has been reached!" << endl;
		cout << "========================" << endl<< endl;
		printInfo(cursor);
		if(!cursor.is_leaf)
		{
			cerr << "TF" << endl;
			cerr << depth << endl;
			cerr << "---------------------------" << endl;
			printInfo(*cursor.TF);
			cerr << "TL" << endl;
			cerr << depth << endl;
			cerr << "---------------------------" << endl;
			printInfo(*cursor.TL);
			cerr << "TR" << endl;
			cerr << depth << endl;
			cerr << "---------------------------" << endl;
			printInfo(*cursor.TR);
			cerr << "TB" << endl;
			cerr << depth << endl;
			cerr << "---------------------------" << endl;
			printInfo(*cursor.TB);
			cerr << "BF" << endl;
			cerr << depth << endl;
			cerr << "---------------------------" << endl;
			printInfo(*cursor.BF);
			cerr << "BL" << endl;
			cerr << depth << endl;
			cerr << "---------------------------" << endl;
			printInfo(*cursor.BL);
			cerr << "BR" << endl;
			cerr << depth << endl;
			cerr << "---------------------------" << endl;
			printInfo(*cursor.BR);
			cerr << "BB" << endl;
			cerr << depth << endl;
			cerr << "---------------------------" << endl;
			printInfo(*cursor.BB);
			
			DebugHelper(*cursor.TF, depth+1);
			DebugHelper(*cursor.TL, depth+1);
			DebugHelper(*cursor.TR, depth+1);
			DebugHelper(*cursor.TB, depth+1);
			DebugHelper(*cursor.BF, depth+1);
			DebugHelper(*cursor.BL, depth+1);
			DebugHelper(*cursor.BR, depth+1);
			DebugHelper(*cursor.BB, depth+1);
		}
	}
}

void OctTree::printInfo(OctTreeNode& cursor)
{
	if(cursor.is_start)
	{
		cout << "The Node is a start!" << endl<< endl;
	}
	if(!cursor.has_objects)
	{
		cout << "THIS NO OBJECT?!" << endl<< endl;
	}
	if(cursor.is_leaf)
	{
		cout << "THIS NODE IS A LEAF" << endl<< endl;
	}
	cout << cursor.bbox.getMax() << endl;
	cout << cursor.bbox.getMin() << endl<< endl<< endl;
}

Point OctTree::getNextIntersection(Point current, BoundingBox &bbox, const Vector& dir) ///CHECKED
{
	double multiAmount;
	double nextAmount;
	double point;
	double boxPoint;
	double direction;
	bool gotOne = 0;
	//if(gotHere == 2)
	//{
// 		cerr << bbox.getMax() << endl;
// 		cerr << bbox.getMin() << endl;
// 		cerr << current.x() << " " << current.y() << " " << current.z() << endl;
		
		//exit(1);
	//	gotHere = 3;
	//}
	//cerr << "==============" << endl;
	//cerr << current << endl;
	
// 	cerr << current << endl;
// 	cerr << dir << endl;
// 	cerr << bbox.getMax() << endl;
// 	cerr << bbox.getMin() << endl;
	
	if(dir.x() > 0.0)//going pos x
	{
		multiAmount = fabs((bbox.getMax().x() - current.x())/dir.x());
		gotOne = 1;
	}
	else if(dir.x() < 0.0)//going neg x
	{
		
		multiAmount = fabs((current.x() - bbox.getMin().x())/dir.x());
// 		cerr << "going neg x" << endl;
// 		cerr << "multiAmount = " << multiAmount << endl;
		gotOne = 1;
	}
	else
	{
		cerr << "fuck" << endl;
	}
	
// 	cerr << dir.y() << endl;
	
	if(dir.y() > 0.0)//going pos y
	{
		if(gotOne == 1)
		{
			nextAmount = fabs((bbox.getMax().y() - current.y())/dir.y());
			if(nextAmount < multiAmount)
			{
				multiAmount = nextAmount;
			}
			
		}
		else
		{
			multiAmount = fabs((bbox.getMax().y() - current.y())/dir.y());
			gotOne = 1;
		}
	}
	else if(dir.y() < 0.0)//going neg y
	{
// 		cerr << "got here 1" << endl;
		if(gotOne == 1)
		{
			nextAmount = fabs((current.y() - bbox.getMin().y())/dir.y());
			if(nextAmount < multiAmount)
			{
				multiAmount = nextAmount;
			}
// 			cerr << "going neg y" << endl;
// 			cerr << "multiAmount = " << multiAmount << endl;
		}
		else
		{
			multiAmount = fabs((current.y() - bbox.getMin().y())/dir.y());
// 			cerr << "going neg y" << endl;
// 			cerr << "multiAmount = " << multiAmount << endl;
			gotOne = 1;
		}
	}
	else
	{
		cerr << "fuck" << endl;
	}
	
	if(dir.z() > 0.0)//going pos z
	{
		if(gotOne == 1)
		{
			nextAmount = fabs((bbox.getMax().z() - current.z())/dir.z());
			if(nextAmount < multiAmount)
			{
				multiAmount = nextAmount;
			}
		}
		else
		{
			multiAmount = fabs((bbox.getMax().z() - current.z())/dir.z());
			gotOne = 1;
		}
	}
	else if(dir.z() < 0.0)//going neg z
	{
		if(gotOne == 1)
		{
// 			point = current.z();
// 			boxPoint = bbox.getMin().z();
// 			direction = dir.z();
// 			cerr << "Point = " << point << endl;
// 			cerr << "boxPoint = " << boxPoint << endl;
// 			cerr << "directio = " << direction << endl;
// 			cerr << (point - boxPoint) << endl;
// 			cerr << ((point - boxPoint)/direction) << endl;
// 			cerr << (((point - boxPoint)/direction)/-1.0) << endl;
			nextAmount = fabs((current.z() - bbox.getMin().z())/dir.z());
// 			cerr << nextAmount << endl;
			if(nextAmount < multiAmount)
			{
				multiAmount = nextAmount;
			}
// 			cerr << "going neg z" << endl;
// 			cerr << "multiAmount = " << multiAmount << endl;
		}
		else
		{
			multiAmount = fabs((current.z() - bbox.getMin().z())/dir.z());
			gotOne = 1;
		}
	}
	else
	{
		cerr << "fuck" << endl;
	}
	
// 	if(bbox.pointCheck(current + (dir*multiAmount) + (dir* .01)))
// 	{
// 		cerr << "Death" << endl;
// 		cerr << "max" << bbox.getMax() << endl;
// 		cerr << "min" << bbox.getMin() << endl;
// 		cerr << "start" << current << endl;
// 		cerr << "direction" << dir << endl;
// 		cerr << "after" << (current + (dir*multiAmount) + (dir* .01)) << endl;
// 		exit(1);
// 	}
	
	
// 	if(gotOne != 1)
// 	{
//  		cerr << "couldn't find a direction!" << endl;
// 		multiAmount = 0;
// 	}
// 	cerr << multiAmount << endl;
//  	cerr << current + (dir*multiAmount) + (dir*.01) << endl;
// // 	cerr << "=============================" << endl;
// 	exit(1);
	
	multiAmount = multiAmount * 1.1;
	return current + (dir*multiAmount) + (dir);
}

void OctTree::getObjectsHitHelper(OctTreeNode &node, const Ray& ray, Point current, std::vector<Object*> &dest)
{
	
	
	if(node.is_leaf)/// we are at a leaf
	{
		/// calculate next ray posit
// 		if(node.is_start)/// if the leaf is the start return objects
// 		{
// 			cerr << "should never get here";
// 			return;
// 		}
// 		if(current.x() <= -0.1 && current.y() <= -0.1)
// 		{
// 			cerr << "YES IT WORKS NOW" << endl;
// 		}
		current = getNextIntersection(current, node.bbox, ray.direction());
		//if(start.bbox.pointCheck(current)) /// point is still in the world
		//{
			getObjectsHitHelper(*node.parent, ray, current, dest);
			//getObjectsHitHelper(*node.parent, ray, current, dest);
			
// 			begin = &node.objects[0];///add objects in here to list
// 			end = &node.objects[0] + node.objects.size();
// 			while (begin != end)
// 			{
// 				objs.push_back(*begin++);
// 			}
		//}
		if(node.has_objects)
		{
			mergeList(node.objects, dest);
		}
		return;
	}
	if(node.has_objects)/// not a leaf get rest of things
	{
		//cerr << "got here" << endl;
// 		cerr << current << endl;
// 		cerr << node.bbox.getMax() << endl;
// 		cerr << node.bbox.getMin() << endl;
// 
// 				cerr << "TF is " << endl;
// 				cerr << node.TF->bbox.getMax() << endl;
// 				cerr << node.TF->bbox.getMin() << endl;
// 				
// 				cerr << "TL is " << endl;
// 				cerr << node.TL->bbox.getMax() << endl;
// 				cerr << node.TL->bbox.getMin() << endl;
// 				
// 				cerr << "TR is " << endl;
// 				cerr << node.TR->bbox.getMax() << endl;
// 				cerr << node.TR->bbox.getMin() << endl;
// 				
// 				cerr << "TB is " << endl;
// 				cerr << node.TB->bbox.getMax() << endl;
// 				cerr << node.TB->bbox.getMin() << endl;
// 				
// 				cerr << "BF is " << endl;
// 				cerr << node.BF->bbox.getMax() << endl;
// 				cerr << node.BF->bbox.getMin() << endl;
// 				
// 				cerr << "BR is " << endl;
// 				cerr << node.BR->bbox.getMax() << endl;
// 				cerr << node.BR->bbox.getMin() << endl;
// 				
// 				cerr << "BL is " << endl;
// 				cerr << node.BL->bbox.getMax() << endl;
// 				cerr << node.BL->bbox.getMin() << endl;
// 				
// 				cerr << "BB is " << endl;
// 				cerr << node.BB->bbox.getMax() << endl;
// 				cerr << node.BB->bbox.getMin() << endl;

// 		if(gotHere == 2)
// 		{
// 			if(current.x() <= -0.1 && current.y() <= -0.1)
// 			{
// 				cerr << "got a point in neg quad" << endl;
// 				cerr << current.x() << " " << current.y() << " " << current.z() << endl;
// 				
// 				cerr << "TF is " << endl;
// 				cerr << node.TF->bbox.getMax() << endl;
// 				cerr << node.TF->bbox.getMin() << endl;
// 				
// 				cerr << "TL is " << endl;
// 				cerr << node.TL->bbox.getMax() << endl;
// 				cerr << node.TL->bbox.getMin() << endl;
// 				
// 				cerr << "TR is " << endl;
// 				cerr << node.TR->bbox.getMax() << endl;
// 				cerr << node.TR->bbox.getMin() << endl;
// 				
// 				cerr << "TB is " << endl;
// 				cerr << node.TB->bbox.getMax() << endl;
// 				cerr << node.TB->bbox.getMin() << endl;
// 				
// 				cerr << "BF is " << endl;
// 				cerr << node.BF->bbox.getMax() << endl;
// 				cerr << node.BF->bbox.getMin() << endl;
// 				
// 				cerr << "BR is " << endl;
// 				cerr << node.BR->bbox.getMax() << endl;
// 				cerr << node.BR->bbox.getMin() << endl;
// 				
// 				cerr << "BL is " << endl;
// 				cerr << node.BL->bbox.getMax() << endl;
// 				cerr << node.BL->bbox.getMin() << endl;
// 				
// 				cerr << "BB is " << endl;
// 				cerr << node.BB->bbox.getMax() << endl;
// 				cerr << node.BB->bbox.getMin() << endl;
// 				
// 				gotHere = 3;
// 			}
// 		}
		/*if(current.x() <= -0.35 && current.y() <= -0.35)
		{
			cerr << "and the box has objects" << endl;
		}*/
// 		cerr << "TF" << endl;
// 		cerr << node.TF->bbox.getMax() << endl;
// 		cerr << node.TF->bbox.getMin() << endl;
// 		cerr << endl;
// 		cerr << "BB" << endl;
// 		cerr << node.BB->bbox.getMax() << endl;
// 		cerr << node.BB->bbox.getMin() << endl;
// 		cerr << endl;
// 		cerr << endl;
// 		cerr << endl;
// 		cerr << endl;
// 		cerr << endl;
// 		cerr << endl;
		
		if(node.TF->bbox.pointCheck(current))
		{
// 			cerr << "TF" << endl;
// 			cerr << node.TF->bbox.getMax() << endl;
// 			cerr << node.TF->bbox.getMin() << endl;
			//cerr << "box is in this quadrant TF" << endl;
			getObjectsHitHelper(*node.TF, ray, current, dest);
		}
		else if(node.TL->bbox.pointCheck(current))
		{
// 			cerr << "TL" << endl;
// 			cerr << node.TL->bbox.getMax() << endl;
// 			cerr << node.TL->bbox.getMin() << endl;
			getObjectsHitHelper(*node.TL, ray, current, dest);
		}
		//box is in this quadrant TR
		else if(node.TR->bbox.pointCheck(current))
		{
// 			cerr << "TR" << endl;
// 			cerr << node.TR->bbox.getMax() << endl;
// 			cerr << node.TR->bbox.getMin() << endl;
			getObjectsHitHelper(*node.TR, ray, current, dest);
		}
		//box is in this quadrant TB
		else if(node.TB->bbox.pointCheck(current))
		{
// 			cerr << "TB" << endl;
// 			cerr << node.TB->bbox.getMax() << endl;
// 			cerr << node.TB->bbox.getMin() << endl;
			getObjectsHitHelper(*node.TB, ray, current, dest);
		}
		
		//box is in this quadrant BF
		else if(node.BF->bbox.pointCheck(current))
		{
			getObjectsHitHelper(*node.BF, ray, current, dest);
		}
		
		//box is in this quadrant BL
		else if(node.BL->bbox.pointCheck(current))
		{
// 			cerr << "BL" << endl;
// 			cerr << node.BL->bbox.getMax() << endl;
// 			cerr << node.BL->bbox.getMin() << endl;
// 			if(gotHere == 1)
// 			{
// 				if(current.x() <= -0.1 && current.y() <= -0.1)
// 				{
// 					cerr << "it got to BL" << endl;
// 					cerr << current.x() << " " << current.y() << " " << current.z() << endl;
// 					gotHere = 2;
// 				}
// 				//exit(1);
// 			}
			getObjectsHitHelper(*node.BL, ray, current, dest);
		}
		//box is in this quadrant BR
		else if(node.BR->bbox.pointCheck(current))
		{
// 			cerr << "BR" << endl;
// 			cerr << node.BR->bbox.getMax() << endl;
// 			cerr << node.BR->bbox.getMin() << endl;
			getObjectsHitHelper(*node.BR, ray, current, dest);
		}
		//box is in this quadrant BB
		else if(node.BB->bbox.pointCheck(current))
		{
// 			cerr << "BB" << endl;
// 			cerr << node.BB->bbox.getMax() << endl;
// 			cerr << node.BB->bbox.getMin() << endl;
			getObjectsHitHelper(*node.BB, ray, current, dest);
		}
		else if(!node.is_start)
		{
			getObjectsHitHelper(*node.parent, ray, current, dest);
		}
		
// 		exit(1);
	}
	else
	{
		//cerr << "got here man" << endl;
		if(node.bbox.pointCheck(current))
		{
			current = getNextIntersection(current, node.bbox, ray.direction());
		}
		//if(start.bbox.pointCheck(current)) /// point is still in the world
		//{
			getObjectsHitHelper(*node.parent, ray, current, dest);
		//}
		//else
		//{
			return;
		//}
	}
}

OctTree::~OctTree()
{
	
}