#pragma once

/* creates and controls the fog of war coverage */
class fowTile {

public:
	// Constructors and Destructors
	fowTile();
	~fowTile();

	// Main methods
	void clear();

	// Setters and getters
	unsigned short* getBits() { return m_bits; }
	void setBits(unsigned short* bit) { m_bits = bit; }

private:
	// Private variables
	unsigned short*  m_bits;
	// private methods
};