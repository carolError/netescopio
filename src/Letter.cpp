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
	vel.set(ofRandom(-0.5,0.5),ofRandom(-1,0.5),ofRandom(-0.5,0.5));
	acc.set(0,-1,0);
	angle = ofRandom(-20,20);
	//aVelocity = 0;
	//aAcceleration = 0;
	tam = (int)ofRandom(0,32);
	tamScale = tam/48.;
	col = ofRandom(200);
	life = 510;
	//car = letra[(int)ofRandom(sizeof(letra))];
	wordMesh = &_wordMesh;
	fontTexture = &_fontTexture;
}

void Letter::applyForce(ofVec3f force){
    ofVec3f f = force / mass;
	acc += f;
}

void Letter::update(){
    vel += acc;
    loc += vel;
    //aAcceleration = acc.y / 10.0;
    //aVelocity += aAcceleration;
    //angle += aVelocity;
    acc.set(0,0,0);
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

