#include "collisionGridNode.h"

collisionGridNode::collisionGridNode(int x, int y) {
	treeLoc = new point2d(x,y);
}

void collisionGridNode::clearPoints() {
	containedSprites.clear();
}

void collisionGridNode::addSpritePath(sprite* spr) {
	spritePaths.push_back(spr);
}

void collisionGridNode::addSprite(sprite* spr) {
	containedSprites.push_back(spr);
}

void collisionGridNode::addDeviatedPath(sprite* spr) {
	spritePaths.push_back(spr);
}

vector<sprite*> collisionGridNode::getSpritePaths() {
	return spritePaths;
}

vector<sprite*> collisionGridNode::getContainedSprites() {
	return containedSprites;
}

vector<sprite*> collisionGridNode::getDeviatedPaths() {
	return deviatedPaths;
}
