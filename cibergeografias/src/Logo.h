#pragma once

#include "ofMain.h"

class Logo : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		float lw;
		float lh;
		float pw;
		float ph;
		float lcw;
		float lch;
		float w;
		float h;
	
		ofVec3f a,b,c,d,a2,b2,c2,d2,e2,f2,g2,h2;
		ofImage photo;
		ofImage logoImg1 ,logoImg2 ,logoImg3;
		ofVboMesh tri1;
		ofVboMesh logo1,logo2,logo3,logo4,logo5,logo6;
		int xpos;

		ofEasyCam cam;
};
