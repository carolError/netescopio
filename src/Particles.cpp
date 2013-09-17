#include "Particles.h"

//--------------------------------------------------------------
void Particles::setup(int _numImage){
	//float eY = ofRandom( -(ofGetHeight()/2), ofGetHeight()/2);
	//float eX = ofRandom( -(ofGetWidth()/2), ofGetWidth()/2);
	emitter.setup(ofVec3f(0,0,0));
	numImage = _numImage;
	countSecImg = ofGetElapsedTimef();
	countSecLet = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void Particles::update(){
	if (ofGetElapsedTimef() - countSecImg >= 3. ){
		emitter.addImages(numImage);
		countSecImg = ofGetElapsedTimef();
	}
	if (ofGetElapsedTimef() - countSecLet >= 0.5 ){
		emitter.addLetters();
		countSecLet = ofGetElapsedTimef();
	}
}

//--------------------------------------------------------------
void Particles::draw(){
	emitter.runImages();
	emitter.runLetters();
}

//--------------------------------------------------------------
void Particles::keyPressed(int key){

}

//--------------------------------------------------------------
void Particles::keyReleased(int key){

}

//--------------------------------------------------------------
void Particles::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Particles::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Particles::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Particles::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Particles::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Particles::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Particles::dragEvent(ofDragInfo dragInfo){

}
