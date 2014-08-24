#include "sprite.h"
#include "SOIL.h"
#include "control.h"
#include "collision.h"

sprite::sprite() {
	show = true;
	movable = false;
	h3d = 20;
	changed = true;
	size = new point2d(100,100);

}

string sprite::update() {
	return "alive";
}

void sprite::hit(int damage) {

}

void sprite::setup() {

}

void sprite::useBuild(string name) {

}

void sprite::createDisplayList() {
	list = glGenLists(1);
	float tmp;
	if(movable == false) {
		tmp = h3d;
	}
	else {
		tmp = 0;
	}
	glNewList(list,GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0 );
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, size->getY() + tmp, 0 );
			glTexCoord2f(1.0f, 1.0f); glVertex3f(size->getX(), size->getY() + tmp, 0 );
			glTexCoord2f(1.0f, 0.0f); glVertex3f(size->getX(), 0, 0 );
		glEnd();
	glEndList();
}

void sprite::updateTiles() {
	control* ctrl = control::getInstance();
	vector<point2d*> tmpTiles = collision::testCollision(point2d(location.getX() + velocity->getX(),location.getY() + velocity->getY()),getSize(),damage,unitId,colour);
	for(int a=0;a<tiles.size();a++) {
		ctrl->getColTree()->removeSpriteInTile(this);
	}
	tiles = tmpTiles;
	ctrl->getColTree()->addSpriteToTile(this);
}

void sprite::build() {
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glCallList(list);
}


void sprite::createTexture(GLuint tex,string img) {
	texture[0] = tex;
	setImage(img);
}

void sprite::setDirection(float xIn, float yIn) { 
	direction->setX(xIn);
	direction->setY(yIn);
}
void sprite::setSize(float xIn, float yIn) { 
	size->setX(xIn);
	size->setY(yIn);
}
void sprite::setVelocity(float xIn, float yIn) { 
	velocity->setX(xIn);
	velocity->setY(yIn);
}
void sprite::setPosition(float xIn, float yIn) { 
	location.setX(xIn);
	location.setY(yIn);
}

bool sprite::getEndPath() {
	return true;
}