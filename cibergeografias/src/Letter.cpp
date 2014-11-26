/*
 *  Letter.cpp
 *  netescopio_antesala
 *
 *  Created by Lain on 31/08/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Letter.h"
/*
 * 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',
	'q','r','s','t','u','v','x', 'w','x','y','z','1','2','3','4','5','6','7','8','9',
 */

void Letter::setup(float m, ofVec3f l, ofVboMesh& _wordMesh,ofTexture& _fontTexture){
	
	mass = m;
	loc = l;
	vel.set(ofRandom(-10,20),ofRandom(0,-150),ofRandom(-10,20));
	acc.set(0,-2,0);
	angle = ofRandom(-20,20);
	//aVelocity = 0;
	//aAcceleration = 0;
	tam = (int)ofRandom(0,50);
	tamScale = tam/48.;
	col = ofRandom(255);
	life = 510;
	lifeColor = 510;
	//car = letra[(int)ofRandom(sizeof(letra))];
	wordMesh = &_wordMesh;
	fontTexture = &_fontTexture;
}

void Letter::applyForce(ofVec3f force){
    ofVec3f f = force / mass;
	acc += f;
}

void Letter::update(){
    vel += acc *ofGetLastFrameTime();
    loc += vel *ofGetLastFrameTime();
    //aAcceleration = acc.y / 10.0;
    //aVelocity += aAcceleration;
    //angle += aVelocity;
    acc.set(0,0,0);
    lifeColor -= 0.3;
    if (lifeColor <100){
    	lifeColor--;
    }
    life--;
}

bool Letter::finished(){
    if (life < 0.0){
		return true;
    } else {
		return false;
    }
}

void Letter::display(){
    ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetColor(col,col,col,life*.5);
	ofPushMatrix();
	ofTranslate(loc);
	//float grad = ofRadToDeg(angle);
	ofRotateX(-90);
	ofRotate(angle);
	//cout << tam << endl ;
	//cout << tamScale <<endl;
	ofScale(tamScale,tamScale,tamScale);
	fontTexture->bind();
	wordMesh->draw();
	fontTexture->unbind();
	ofPopMatrix();
	ofSetRectMode(OF_RECTMODE_CORNER);
}

