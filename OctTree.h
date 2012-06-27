#ifndef OctTree_h
#define OctTree_h

#include "Object.h"
#include "Ray.h"
#include "Point.h"
#include <vector>
#include "BoundingBox.h"

struct OctTreeNode{
	OctTreeNode* parent, *TR, *TL, *TF, *TB, *BB, *BL, *BR, *BF;
	std::vector<Object*> objects;
	bool has_objects;
	bool is_start;
	BoundingBox bbox;
	bool is_leaf;
};

class OctTree {
	public:
		void Debug();
		void DebugHelper(OctTreeNode& cursor, int depth);
		OctTree(int depth, std::vector<Object*> &objs);
		~OctTree();
		void printInfo(OctTreeNode& cursor);
		void initialize(OctTreeNode* cursor, int countdown);
		void mergeList(std::vector<Object*> &src, std::vector<Object*> &dest);
		OctTreeNode start;
		int depth;
		void getObjectsHitHelper(OctTreeNode &node, const Ray &ray, Point current, std::vector<Object*> &dest);
		void getObjectsHit(HitRecord& hit, const RenderContext& context, const Ray& ray, std::vector<Object*> &dest);
		Point getNextIntersection(Point current, BoundingBox &bbox, const Vector& dir);
		void addObject(OctTreeNode &node, Object* obj);
		int debugRuns;
		int gotHere;
};

#endif