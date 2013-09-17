#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxAruco.h"
//#include "ofxPanel.h"void pause();
#include "LabelNetescopio.h"
#include "Particles.h"
#include "Logo.h"

#ifdef TARGET_ANDROID
#include "ofxAndroid.h"
class testApp : public ofxAndroidApp{
#else
class testApp : public ofBaseApp{
#endif
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

		void paramChanged(int & p);

		void pause();
		void displayBoton();
		ofxAruco aruco;
		float markerSize;
		ofVideoGrabber grabber;
		ofPixels thresPix;
		ofTexture thresTex;
		//ofxPanel gui;
		//ofxParameter<int> param1,param2;

		set<int> lastSeenMarker;
		map<int,LabelNetescopio> labels;
		map<int,Particles> particles;
		int logoId;
		float scale;

		ofRectangle button;
		ofRectangle plusV;
		ofRectangle plusH;
		enum State{
			AR,
			Description
		}state ;
		int descId;

		bool bMousePressed;
		int mx,my;
		bool hasLabels;

		Logo logo;
		ofImage thresImg;
		ofImage descBg;
};

#endif	

