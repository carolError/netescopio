#include "testApp.h"

#ifdef TARGET_ANDROID
#include "ofxAndroidVideoGrabber.h"
#endif

void drawMarker(float size, const ofColor & color, float direction=1){
	ofDrawAxis(size);
	ofPushMatrix();
		ofTranslate(0,size*0.5*direction,0);
		ofFill();
		ofSetColor(color,50);
		ofBox(size);
		ofNoFill();
		ofSetColor(color);
		ofBox(size);
	ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::setup(){
	//ofSetVerticalSync(false);
	ofDisableArbTex();
#ifndef TARGET_ANDROID
	grabber.setDeviceID(1);
#endif
	//initialize camera
	grabber.initGrabber(640,480);
	thresImg.allocate(grabber.getWidth(),grabber.getHeight(),OF_IMAGE_GRAYSCALE);

#ifdef TARGET_ANDROID
	//set orientation to portrait if it is an android device
	ofSetOrientation(OF_ORIENTATION_90_RIGHT);
	//ofxAndroidVideoGrabber * androidGrabber = (ofxAndroidVideoGrabber *)grabber.getGrabber().get();
	//androidGrabber->setAutoFocus(true);
#endif

	// AR setup
	//real size of the markers (printed) in centimeters
	markerSize = 0.15;
	string boardName = "boardLogo.yml";
	aruco.setup("intrinsics.int", grabber.getWidth(), grabber.getHeight(), boardName, markerSize);
	thresPix.allocate(grabber.getWidth(), grabber.getHeight(),OF_IMAGE_GRAYSCALE);
	thresTex.allocate(grabber.getWidth(), grabber.getHeight(),GL_LUMINANCE);

	aruco.setThresholdParams(25,7);

	/*gui.setup();
	gui.add(param1.set("thres param1",aruco.getThresholdParam1(),0,100));
	gui.add(param2.set("thres param2",aruco.getThresholdParam2(),0,100));*/

	//param1.addListener(this,&testApp::paramChanged);

	/*ofPixels pix;
	aruco.getBoardImage(pix);
	//ofSaveImage(pix,"board.png");
	//thresTex.allocate(pix);
	//thresTex.loadData(pix);*/

	LabelNetescopio::G1.loadImage("01.png");
	LabelNetescopio::G2.loadImage("02.png");
	LabelNetescopio::font.loadFont("FreeSans.ttf",18,true,true,true);
	//load the demo document
	LabelNetescopio::libRocket = new ofxLibRocket;
	LabelNetescopio::libRocket->loadFont("FreeSans.ttf");
	LabelNetescopio::libRocket->setup();
	UIElementScroll::registerWithlibRocket();


	descBg.loadImage("baseDescripcion.jpg");

	ofFile labelsIds("labels.txt");
    while(labelsIds.good()){

    	int idLabel;
    	labelsIds >> idLabel;
		ofLogNotice() << "opening id: " << idLabel << endl;
		labels[idLabel].setup(idLabel);
	}
    state = AR;

	ofSetColor(0,0,0);
	ofEnableAlphaBlending();
	ofBackground(0);


	// setup particles
	logoId = 905;
	logo.setup();
	//TODO: this is an id from a label, use a different one
	//logoId = 125;

	particles[985].setup(0);
	particles[904].setup(1);
	particles[903].setup(2);
	particles[900].setup(3);
	particles[51].setup(4);
	particles[22].setup(5);


}

void testApp::paramChanged(int & p){
	/*if(param2%2==0) param2+=1;
	if(param1%2==0) param1+=1;
	aruco.setThresholdParams(param1,param2);*/
}

//--------------------------------------------------------------
void testApp::update(){
	hasLabels = false;
	if(state==AR){
		grabber.update();
		if (grabber.isFrameNew()){
			//unsigned long long time = ofGetElapsedTimeMillis();
			aruco.detectBoard(grabber.getPixelsRef());
			//cout << ofGetElapsedTimeMillis() - time << endl;
			//aruco.getThresholdImage(thresPix);

			/*aruco.getThresholdImage(thresImg);
			thresImg.update();*/
		}

		if(aruco.getBoardProbability()>.03){
			logo.update();
		}

		set<int> newIds;

		for(int i=0;i<aruco.getNumMarkers();i++){
			int currentId = aruco.getMarkers()[i].idMarker;
			if(particles.find(currentId)!=particles.end()){
				particles[currentId].update();
			}else if(labels.find(currentId)!=labels.end()){
				hasLabels = true;

				if(lastSeenMarker.find(aruco.getMarkers()[i].idMarker)==lastSeenMarker.end()){
					//cout << "found " << aruco.getMarkers()[i].id << endl;
					labels[aruco.getMarkers()[i].idMarker].start();
				}
				newIds.insert(aruco.getMarkers()[i].idMarker);
				labels[aruco.getMarkers()[i].idMarker].update();
			}
		}
		lastSeenMarker = newIds;

		if(aruco.getNumMarkers()){
			descId = aruco.getMarkers()[0].idMarker;
		}


	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	if(state==AR){
		int width = ofGetHeight()*4./3.;
		int x = (ofGetWidth()-width)/2.;
		grabber.draw(x,0,width,ofGetHeight());


		//thresTex.loadData(thresPix);
		//thresTex.draw(0,0,320,240);
		ofPushView();
		ofViewport(x,0,width,ofGetHeight());

		ofEnableAlphaBlending();
		if(aruco.getBoardProbability()>.03){
			aruco.beginBoard();
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofRotate(-90,1,0,0);
			//ofRect(0,0,markerSize,markerSize);
			ofSetRectMode(OF_RECTMODE_CORNER);

			ofScale(markerSize,markerSize,markerSize);
			logo.draw();
			aruco.end();
		}

		for(int i=0;i<aruco.getNumMarkers();i++){
			int currentId = aruco.getMarkers()[i].idMarker;
			//cout << currentId << endl;
			//cout << "---" << endl;
			aruco.begin(i);

			if(particles.find(currentId)!=particles.end()){

				ofSetColor(ofColor::red);
				ofLine(ofVec3f(-markerSize/2.,0,0),ofVec3f(-markerSize/2.,10,0));
				ofLine(ofVec3f(markerSize/2.,0,0),ofVec3f(markerSize/2.,10,0));
				ofSetColor(255);
				ofScale(-1./ofGetHeight(),-1./ofGetHeight(),1./ofGetHeight());
				particles[currentId].draw();
			}else if(labels.find(currentId)!=labels.end()){
				ofRotate(90,1,0,0);
				ofScale(-1./ofGetHeight(),-1./ofGetHeight(),1./ofGetHeight());
				labels[aruco.getMarkers()[i].idMarker].draw();
			}
			aruco.end();
		}
		ofPopView();

		if(hasLabels){
			displayBoton();
		}
	}else{
		descBg.draw(0,0,ofGetWidth(),ofGetHeight());
		displayBoton();
	}

	/*if(bMousePressed ){
		ofSetColor(255);
		ofCircle(mx,my,15);
	}*/
	ofSetColor(255);
	ofDrawBitmapString("frameRate:" + ofToString(ofGetFrameRate()),10,10);
	//ofDrawBitmapStringHighlight("scale:" + ofToString(scale,3),10,ofGetHeight()-80);

	//thresImg.draw(0,0);
}

void testApp::pause(){
	std::exit(0);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if(hasLabels && !button.inside(x,y)){
		scale = ofMap(float(x)/float(ofGetWidth()),0,1,.25,1);
		/*aruco::BoardConfiguration & boardConfig = aruco.getBoardConfig();
		for (int y=0;y<boardConfig._markersId.cols;y++)
			for (int xx=0;xx<boardConfig._markersId.rows;xx++) {
				labels[boardConfig._markersId.at<int>(xx,y)].scale = scale;
			}*/
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int _button){
	if(hasLabels || state==Description){
		bMousePressed = true;
		mx = x; my = y;
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int _button){
	//ofLogNotice()<< "mouse released";
	bMousePressed = false;
	if((hasLabels  || state==Description) && button.inside(mx,my) && button.inside(x,y)){
		ofLogNotice()<< "mouse inside";
		if(state == Description){
			#ifdef TARGET_ANDROID
				ofSetOrientation(OF_ORIENTATION_90_RIGHT);
			#endif
			state = AR;
			labels[descId].hideDescription();
		}else{
			#ifdef TARGET_ANDROID
				ofSetOrientation(OF_ORIENTATION_DEFAULT);
			#endif
			state = Description;
			labels[descId].showDescription();
		}
	}else{
		//ofLogNotice()<< "mouse not inside";
	}

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
void testApp::displayBoton(){
	/*button.set(ofGetWidth()-220,ofGetHeight()-220,160,160);
	plusV.set(ofGetWidth()-220+160/2-10,ofGetHeight()-220+20,20,120);
	plusH.set(ofGetWidth()-220+20,ofGetHeight()-220+160/2-10,120,20);*/
	float w = ofGetWidth();
	float h = ofGetHeight();
	float x_boton = w*.70;
	float y_boton = h*.10;
	float w_boton = w*.19;
	float h_boton = w*.19;
	float w_barra_H = w_boton*.8;
	float h_barra_H = w_boton*.2;
	float x_barra_H = x_boton + ((w_boton - w_barra_H)/2);
	float y_barra_H= y_boton + ((h_boton - h_barra_H)/2);
	float w_barra_V = w_boton*.2;
	float h_barra_V = w_boton*.8;
	float x_barra_V = x_boton + ((w_boton/2)-(w_barra_V/2));
	float y_barra_V= y_boton + ((h_boton - h_barra_V)/2);
	//ofSetRectMode(OF_RECTMODE_CENTER);
	button.set(x_boton , y_boton , w_boton , h_boton);
	plusV.set(x_barra_V, y_barra_V , w_barra_V , h_barra_V);
	plusH.set(x_barra_H, y_barra_H , w_barra_H , h_barra_H);
	//ofSetRectMode(OF_RECTMODE_CORNER);
	ofSetHexColor(0xef037f);
	ofRect(button);
	ofSetColor(255);
	ofRect(plusH);

	if(state==AR){
		ofRect(plusV);
	}
}
