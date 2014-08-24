#pragma once

#include <stdlib.h>			// Header File For Standard Library
#include <math.h>			// Ma#include "tile.h"th Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <string>
#include <vector>
#include "point2d.h"

using namespace std;

template <class T>
class binaryHeap
{
public:
	// constructors
	binaryHeap(); 


	// main methods
	void addElement();
	void getFront();
	void removeElement();
	void changeElement();

	// setters and getters
	vector<T> getHeap();

private:
	vector<T> heap;
};

template <class T> binaryHeap<T>::binaryHeap() {
	
}

template <class T> void binaryHeap<T>::getFront() {

}

template <class T> void binaryHeap<T>::removeElement() {

}

template <class T> void binaryHeap<T>::addElement() {

}


template <class T> void binaryHeap<T>::changeElement() {
	
}

template <class T> vector<T> binaryHeap<T>::getHeap() { 
	return heap; 
}
