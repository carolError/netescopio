/*
 *  Emitter.h
 *  netescopio_antesala
 *
 *  Created by Lain on 31/08/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#include "ofMain.h"
#include "Letter.h"
#include "Image.h"
#include <list>

class Emitter{

public:
	
	list<Letter>letters;
	list<Image>images;
	vector<ofVboMesh> words;
	ofVec3f g;
	ofTrueTypeFont font[4];
	ofImage img[24];
	ofVec3f origin;
	void setup(ofVec3f location);
	void runImages();
	void runLetters();
	void addImages();
	void addLetters();
};
