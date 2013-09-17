#include "Particles.h"

//--------------------------------------------------------------
void Particles::setup(){
	//float eY = ofRandom( -(ofGetHeight()/2), ofGetHeight()/2);
	//float eX = ofRandom( -(ofGetWidth()/2), ofGetWidth()/2);
	emitter.setup(ofVec3f(0,0,0));
}

//--------------------------------------------------------------
void Particles::update(){
	counter++;
}

//--------------------------------------------------------------
void Particles::draw(int marc){
	int m = marc;
	if (counter%50 == 0){
		emitter.addImages(m);
	}
	emitter.runImages();
	if (counter%2 == 0){
			emitter.addLetters();
		}
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
