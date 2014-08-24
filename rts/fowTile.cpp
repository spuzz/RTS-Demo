#include "fowTile.h"

fowTile::fowTile() {
	m_bits = new unsigned short();
	*m_bits = 511;
}

fowTile::~fowTile() {

}

void fowTile::clear() {
	*m_bits = 511;
}