#include "collisionGrid.h"
#include "sprite.h"
#include "utilFuncs.h"
#include "collision.h"

collisionGrid::collisionGrid(int width, int height) {
	logging::log(logging::FINE,"Quad tree created");
	vector<collisionGridNode*>* quadNodeVector;
	collisionGridNode* node;
	for(int a = 0;a<width;a++) {
		quadNodeVector = new vector<collisionGridNode*>;
		for(int b = 0;b<height;b++) {
			node = new collisionGridNode(a,b);
			quadNodeVector->push_back(node);
		}

		tree.push_back(quadNodeVector);
	}
}


void collisionGrid::reset() {
	for(int a=0;a<tree.size();a++) {
		for(int b=0;b<tree[a]->size();b++) {
			tree[a]->at(b)->clearPoints();
		}
	}
}

// Simple diagnostic function
void collisionGrid::PrintGrid() {
	logging::log(logging::BASIC,"Printing collision grid diagnostic");
	for(int a=0;a<tree.size();a++) {
		for(int b=0;b<tree[0]->size();b++) {
			for(int c=0;c<tree[a]->at(b)->getContainedSprites().size();c++) {
				if(tree[a]->at(b)->getContainedSprites()[c]->getImage() == "dronered.png") {
					cout<< tree[a]->at(b)->getContainedSprites()[c]->getPosition().getX() << " " <<
						tree[a]->at(b)->getContainedSprites()[c]->getPosition().getY()<< endl;
					cout << a << " " <<
						b<<endl;
				}
			}
		}
	}
	logging::log(logging::BASIC,"End of collision grid diagnostic");
}

void collisionGrid::addPlayerSprites(playerControl* pc) {
	for(int a=0;a<pc->getUnits()->size();a++) {	
		rectangle rect(new point2d(pc->getUnits()->at(a)->getPosition().getX(),pc->getUnits()->at(a)->getPosition().getY()),
			new point2d(pc->getUnits()->at(a)->getPosition().getX()+(pc->getUnits()->at(a)->getSize()->getX()/100),
			pc->getUnits()->at(a)->getPosition().getY()+(pc->getUnits()->at(a)->getSize()->getY()/100)));
		vector<point2d*> tmp = collision::checkTiles(rect);
		for(int b=0;b<tmp.size();b++) {
			int x = tmp[b]->getX();
			int y = tmp[b]->getY();
			try {
				tree[x]->at(y)->addSprite(pc->getUnits()->at(a));
			}
			catch(exception e) {

			}
		}

	}

	for(int a=0;a<pc->getBuildings()->size();a++) {	

		rectangle rect(new point2d((int)pc->getBuildings()->at(a)->getPosition().getX(),(int)pc->getBuildings()->at(a)->getPosition().getY()),
			new point2d((int)pc->getBuildings()->at(a)->getPosition().getX()+((int)pc->getBuildings()->at(a)->getSize()->getX()/100),
			(int)pc->getBuildings()->at(a)->getPosition().getY()+((int)pc->getBuildings()->at(a)->getSize()->getY()/100)));
		vector<point2d*> tmp = collision::checkTiles(rect);
		for(int b=0;b<tmp.size();b++) {
			int x = tmp[b]->getX();
			int y = tmp[b]->getY();
			try {
				tree[x]->at(y)->addSprite(pc->getBuildings()->at(a));
			}
			catch(exception e) {

			}
		}
		//sprite* building = pc->getBuildings()->at(a);
		//int x = building->getPosition().getX();
		//int y = building->getPosition().getY();
		//tree[x]->at(y)->addSprite(building);
	}
}

void collisionGrid::addSpriteToTile(sprite* spr) {
	for(int a=0;a<spr->getTiles().size();a++) {
		tree[spr->getTiles()[a]->getX()]->at(spr->getTiles()[a]->getY())->addSprite(spr);
	}
}

void collisionGrid::removeSpriteInTile(sprite* spr) {
	for(int a=0;a<spr->getTiles().size();a++) {
		try {
			tree[spr->getTiles()[a]->getX()]->at(spr->getTiles()[a]->getY())->setContainedSprites(*utilFuncs::erase(&tree[spr->getTiles()[a]->getX()]->at(spr->getTiles()[a]->getY())->getContainedSprites(),spr));
		}catch (exception e) {
		}
	}

}


