/*
 *  Letter.h
 *  netescopio_antesala
 *
 *  Created by Lain on 31/08/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"

class Letter{

public:
	
	ofVec3f loc;
	ofVec3f vel;
	ofVec3f acc;
	float angle;
	float aVelocity;
	float aAcceleration;
	float x;
	float y;
	float mass;
	float col;
	int life;
	float lifeColor;
	string car;
	
	ofVboMesh * wordMesh;
	ofTexture * fontTexture;
	int tam;
	float tamScale;

	void setup(float m, ofVec3f l, ofVboMesh& wordMesh,ofTexture& fontTexture);
	void applyForce(ofVec3f force);
	void update();
	void display();
	
	bool finished();



};
