/*
 *  Image.h
 *  netescopio_antesala
 *
 *  Created by Lain on 31/08/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"

class Image{

public:
	
	ofVec3f loc;
	ofVec3f vel;
	ofVec3f acc;
	float angle;
	float aVelocity;
	float aAcceleration;
	int tamX,tamY;
	float randX,newY;
	float aRat;
	float x;
	float y;
	float mass;
	float col;
	int life;
	int tam;
	ofImage * img;

	void setup(float m, ofVec3f l, ofImage& img_);
	void applyForce(ofVec3f force);
	void update();
	void display();
	bool finished();
	float transformAspectRatio_Y(float _arX);
};
