/*
 *  Image.cpp
 *  netescopio_antesala
 *
 *  Created by Lain on 31/08/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Image.h"

void Image::setup(float m, ofVec3f l, ofImage& img_){
	
	mass = m;
	loc = l;
	vel.set(ofRandom(-10,20),ofRandom(0,-150),ofRandom(-10,20));
	acc.set(0,-2,0);
	angle = ofRandom(-20,20);
	//aVelocity = 0;
	//aAcceleration = 0;

	col = ofRandom(200);
	life = 510;
	lifeColor = 0;
	img=&img_;
	tamX = img->width;
	tamY = img->height;
	randX = ofRandom(15,tamX);
	aRat = float (tamX) / float(tamY);
	newY = randX/aRat;
	time1 = ofGetElapsedTimef();
}

void Image::applyForce(ofVec3f force){
    ofVec3f f = force / mass;
	acc += f;
}

void Image::update(){
    vel += acc*ofGetLastFrameTime();
    loc += vel*ofGetLastFrameTime();
    //cout << acc.y << endl;
    //aAcceleration = acc.y / 10.0;
    //aVelocity += aAcceleration;
    //angle += aVelocity;
    acc.set(0.,0.,0.);
    time2 = ofGetElapsedTimef() - time1;
    lifeColor += time2;
    if (lifeColor>=255){
    	lifeColor -= 0.3*time2;
    	if(lifeColor <= 250){
    		lifeColor -= time2;
    	}
    }
    time2 = 0;
    life--;
}

bool Image::finished(){
    if (life < 0.0){
		return true;
    } else {
		return false;
    }
}

void Image::display(){
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofPushMatrix();
	ofTranslate(loc);
	//float grad = ofRadToDeg(angle);
	//cout << grad << endl;

	ofRotateX(-90);
	ofRotate(angle);
	//ofRotate(angle);

	ofSetColor(255, lifeColor);
	//cout << tam << endl;
	//ofScale(tam,tam,tam);
	cout << randX << endl;
	cout << newY << endl;
	cout << aRat << endl;
	cout << "---" << endl;
	ofScale(1.5,1.5);
	img->draw(0,0,randX,newY);
	ofPopMatrix();
	ofSetRectMode(OF_RECTMODE_CORNER);
}


