	//float xDist;
	//float yDist;
	//xDist = abs(target->getX() - pathVector[currentPath]->getLocation()->getX());
	//yDist = abs(target->getY() - pathVector[currentPath]->getLocation()->getY());
	//xNegative = 1;
	//yNegative = 1;
	//if((target->getX() - location.getX()) < 0) {
	//	xNegative = -1;
	//}
	//if((target->getY() - location.getY()) < 0) {
	//	yNegative = -1;
	//};
	//float totalDist = xDist + yDist;
	//if(totalDist > 0) {
	//	setDirection((xDist/totalDist)*xNegative,(yDist/totalDist)*yNegative);
	//}
//}

//bool unit::collision(float x, float y) {
//	control* ctrl = control::getInstance();
//	rectangle compareRect(new point2d(x*100,y*100),new point2d(x*100+size->getX(),y*100+size->getY()));
//	rectangle* rect;
//	for(int a=0;a<ctrl->getPlayerControl()->getUnits().size();a++) {
//		if(ctrl->getPlayerControl()->getUnits()[a]->getUnitId() == getUnitId()) { continue; }
//		rect = new rectangle(new point2d(ctrl->getPlayerControl()->getUnits()[a]->getPosition().getX()*100,ctrl->getPlayerControl()->getUnits()[a]->getPosition().getY()*100),
//			new point2d(ctrl->getPlayerControl()->getUnits()[a]->getPosition().getX()*100+ctrl->getPlayerControl()->getUnits()[a]->getSize()->getX(),
//			ctrl->getPlayerControl()->getUnits()[a]->getPosition().getY()*100+ctrl->getPlayerControl()->getUnits()[a]->getSize()->getY()));
//		if(rect->isOverLap(compareRect)) {
//			if(ctrl->getPlayerControl()->getUnits()[a]->colour != colour) {
//				ctrl->getPlayerControl()->getUnits()[a]->hit(damage);
//			}
//			return true;
//			
//		}
//	}
//	for(int a=0;a<ctrl->getPlayerControl()->getBuildings().size();a++) {
//		if(ctrl->getPlayerControl()->getBuildings()[a]->getUnitId() == getUnitId()) { continue; }
//		rect = new rectangle(new point2d(ctrl->getPlayerControl()->getBuildings()[a]->getPosition().getX()*100,ctrl->getPlayerControl()->getBuildings()[a]->getPosition().getY()*100),
//			new point2d(ctrl->getPlayerControl()->getBuildings()[a]->getPosition().getX()*100+ctrl->getPlayerControl()->getBuildings()[a]->getSize()->getX(),
//			ctrl->getPlayerControl()->getBuildings()[a]->getPosition().getY()*100+ctrl->getPlayerControl()->getBuildings()[a]->getSize()->getY()));
//		if(rect->isOverLap(compareRect)) {
//			if(ctrl->getPlayerControl()->getBuildings()[a]->getColour() != colour) {
//				ctrl->getPlayerControl()->getBuildings()[a]->hit(damage);
//			}
//			return true;
//			
//		}
//	}
//	vector<playerControl*> ai = ctrl->getAIControl();
//	for(int n=0;n<ai.size();n++) {
//		for(int a=0;a<ai[n]->getUnits().size();a++) {
//			if(ai[n]->getUnits()[a]->getUnitId() == getUnitId()) { continue; }
//			rect = new rectangle(new point2d(ai[n]->getUnits()[a]->getPosition().getX()*100,ai[n]->getUnits()[a]->getPosition().getY()*100),
//				new point2d(ai[n]->getUnits()[a]->getPosition().getX()*100+ctrl->getPlayerControl()->getUnits()[a]->getSize()->getX(),
//				ai[n]->getUnits()[a]->getPosition().getY()*100+ctrl->getPlayerControl()->getUnits()[a]->getSize()->getY()));
//			if(rect->isOverLap(compareRect)) {
//				if(ai[n]->getUnits()[a]->colour != colour) {
//					ai[n]->getUnits()[a]->hit(damage);
//				}
//				return true;
//				
//			}
//		}
//		for(int a=0;a<ai[n]->getBuildings().size();a++) {
//			if(ai[n]->getBuildings()[a]->getUnitId() == getUnitId()) { continue; }
//			rect = new rectangle(new point2d(ai[n]->getBuildings()[a]->getPosition().getX()*100,ai[n]->getBuildings()[a]->getPosition().getY()*100),
//				new point2d(ai[n]->getBuildings()[a]->getPosition().getX()*100+ctrl->getPlayerControl()->getBuildings()[a]->getSize()->getX(),
//				ai[n]->getBuildings()[a]->getPosition().getY()*100+ctrl->getPlayerControl()->getBuildings()[a]->getSize()->getY()));
//			if(rect->isOverLap(compareRect)) {
//				if(ai[n]->getBuildings()[a]->getColour() != colour) {
//					ai[n]->getBuildings()[a]->hit(damage);
//				}
//				return true;
//			}
//		}
//	}
//	return false;
//}