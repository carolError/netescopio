#pragma once

#include "ofMain.h"
#include "Emitter.h"

class Particles : public ofBaseApp{

	public:
		void setup(int numImage);
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
		
		int counter;
		Emitter emitter;
		int numImage;
};
