#pragma once

#include "ofMain.h"
#include "ofxLibRocket.h"
//#include "ofxTrueTypeFontUC.h"

class LabelNetescopio : public ofBaseApp{

	public:
		LabelNetescopio();
		void setup(int idLabel);

		void update();
		void draw();

		void showDescription();
		void hideDescription();

		void start();

		void tabla();

		static ofImage G1;
		static ofImage G2;
		static ofxLibRocket * libRocket;
		static ofTrueTypeFont font;
		static ofTrueTypeFont font2;
		//static ofxTrueTypeFontUC font2;
		//static ofxTrueTypeFontUC font;
	private:
		string title;
		string subtitle;
		string author;
		string texto;
		string description;
		ofImage image;
		ofColor bgColor;
		ofColor colTitle;
		bool inter;
		int loopG;
		ofFile templateNetescopio;
		bool imgFrame;
		float x ;
		float y ;
		float ancho;
		float alto;

		ofImage * img;
		float scale;
		int startMillis;
		
		ofxLibRocketDocument* doc;

		
		
};
