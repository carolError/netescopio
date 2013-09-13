#include "LabelNetescopio.h"
//#include "view.h"
ofImage LabelNetescopio::G1;
ofImage LabelNetescopio::G2;
ofTrueTypeFont LabelNetescopio::font;
ofxLibRocket * LabelNetescopio::libRocket;

LabelNetescopio::LabelNetescopio(){
	img = &G1;
	imgFrame = false;
}

void LabelNetescopio::setup(int idLabel){
	ofFile text(ofToString(idLabel)+".txt");

	if(text.getSize()){
		cout << "loading " << idLabel << endl;
		ofBuffer buffer(text);
		author = buffer.getFirstLine();
		title = buffer.getNextLine();
		subtitle = buffer.getNextLine();
		texto = author + "\n" + title + "\n" + subtitle + "\n";
		bgColor = ofColor::fromHex(ofHexToInt(buffer.getNextLine()));
		while(!buffer.isLastLine()){
			description +=  buffer.getNextLine()+"\n";
		}
		image.loadImage("img/"+ofToString(idLabel)+".jpg");
	}
	if(ofGetHeight()>ofGetWidth()){
		if (ofGetHeight() < 1200){
			templateNetescopio.open("netescopio_tel.html");
		} else {
			templateNetescopio.open("netescopio_tablet.html");
		}
	} else {
		if (ofGetWidth() < 1200){
			templateNetescopio.open("netescopio_tel.html");
		} else {
			templateNetescopio.open("netescopio_tablet.html");
		}
	}
	ofBuffer html(templateNetescopio);
	string htmlStr = html;
	ofStringReplace(htmlStr,"${author}",author);
	ofStringReplace(htmlStr,"${title}",title);
	ofStringReplace(htmlStr,"${subtitle}",subtitle);
	ofStringReplace(htmlStr,"${description}",description);

	doc = libRocket->loadDocumentFromMemory(htmlStr);
	doc->hide();
}

void LabelNetescopio::start(){
	scale = .25;
	inter = false;
	loopG = 0;
	x = 30;
	y = 30;
	ancho = 100;
	alto = 10;
	startMillis = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void LabelNetescopio::update(){

	if(loopG%30==0){
		imgFrame=!imgFrame;
		if(imgFrame){
			img = &G1;
		}else{
			img = &G2;
		}

	}
	loopG ++;
}

//--------------------------------------------------------------
void LabelNetescopio::draw(){
	//ofBackground(200);
	ofPushMatrix();
	ofScale(scale,scale,scale);
	ofTranslate(-G1.getWidth()*.5,-G1.getHeight()*.5);
	
	ofSetColor(255); 

	img->draw(0,0);
	
	//ofImage(img,0,0);
	tabla();
	if (inter){
		ofSetColor(255);
		image.draw(150,70);
		ofSetColor(0);
		font.drawString(texto, 150, 300);
	}
	ofPopMatrix();
}

void LabelNetescopio::showDescription(){
	doc->show();
}

void LabelNetescopio::hideDescription(){
	doc->hide();

}

void LabelNetescopio::tabla(){
	
	ofSetColor(bgColor);
	if(y>30) ofRect(30,30,550,y-30);
	ofRect(30,y,x-30,alto);
	/*for(int xx=0;xx<x;xx++){
	 rect(xx,y,ancho,alto);
	 }*/
	
	
	if(y<400){
		float time = (ofGetElapsedTimeMillis()-startMillis)/1000.;
		x=x+ancho*60*ofGetLastFrameTime()*time*time;
		if (x>550){
			y=y+alto*int(x/550);
			x=30+int(x)%550;
		}
	}else {
		x=580;
		inter = true;
	}


}
