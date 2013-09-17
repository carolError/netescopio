#include "Logo.h"

void Logo::setup(){
	cam.setVFlip(true);
	photo.loadImage("ruidoLogo.png");
	logoImg1.loadImage("log1.png");
	logoImg2.loadImage("log2.png");
	logoImg3.loadImage("log3.png");
	
	lw = logoImg1.width;
	lh = logoImg1.height;
	pw = photo.width;
	ph = photo.height;
	lcw = lw*.5;
	lch = lh*.5;
	w=photo.width/2.0;
	h=photo.height/2.0;

	
	a2.set(0,lh);
	b2.set(255,lh);
	c2.set(508,lh);
	d2.set(lw,lh);
	e2.set(lw,0);
	f2.set(644,0);
	g2.set(391,0);
	h2.set(0,0);
	
	a.set(0,0);
	b.set(10,0);
	c.set(10,10);
	d.set(0,10);
	xpos =0;
	
    //color c = photo.get(x,y);
    //fill(255,0,0);
	for(int x=0; x<photo.width; x+=10){
		for(int y=0; y<photo.height; y+=10){
			//tri1.Stroke();
			//tri.fill(255);
			//colorMode(HSB,1000);
			ofColor col = photo.getColor(x,y);
			float z = col.getBrightness()/255.;
			//print(z + "\n");
			tri1.addVertex(ofVec3f(x+a.x - w,y+a.y - h,z));
			tri1.addVertex(ofVec3f(x+b.x - w,y+b.y - h,z));
			tri1.addVertex(ofVec3f(x+c.x - w,y+c.y - h,z));
			
			tri1.addTexCoord(ofVec2f((x+a.x)/pw,(y+a.y)/ph));
			tri1.addTexCoord(ofVec2f((x+b.x)/pw,(y+b.y)/ph));
			tri1.addTexCoord(ofVec2f((x+c.x)/pw,(y+c.y)/ph));
			//tri2.noStroke();
			//tri.fill(255);
			float z2 = col.getBrightness()*2;
			tri1.addVertex(ofVec3f(x+a.x - w,y+a.y - h,z2));
			tri1.addVertex(ofVec3f(x+c.x - w,y+c.y - h,z2));
			tri1.addVertex(ofVec3f(x+d.x - w,y+d.y - h,z2));
			
			tri1.addTexCoord(ofVec2f((x+a.x)/pw,(y+a.y)/ph));
			tri1.addTexCoord(ofVec2f((x+c.x)/pw,(y+c.y)/ph));
			tri1.addTexCoord(ofVec2f((x+d.x)/pw,(y+d.y)/ph));
		}
	}
    
    float offsetX = 0;//w-centroliw;
    float offsetY = 0;//h-centrolih;

    //mesh1
    float varZ1 = -1500 - ofRandom(0,100);
    /*float varZ1=0;
    float varZ2=varZ1;
    float varZ3=varZ1;
    float varZ4=varZ1;
    float varZ5=varZ1;
    float varZ6=varZ1;*/
    logo1.addVertex(ofVec3f(offsetX+a2.x - lcw, offsetY+a2.y - lch, varZ1));
    logo1.addVertex(ofVec3f(offsetX+b2.x - lcw, offsetY+b2.y - lch, varZ1));
    logo1.addVertex(ofVec3f(offsetX+g2.x - lcw, offsetY+g2.y - lch, varZ1));
    //text1
	logo1.addTexCoord(ofVec2f((a2.x)/lw, (a2.y)/lh));
	logo1.addTexCoord(ofVec2f((b2.x)/lw, (b2.y)/lh));
	logo1.addTexCoord(ofVec2f((g2.x)/lw, (g2.y)/lh));
    //mesh2
    logo2.addVertex(ofVec3f(offsetX+a2.x - lcw, offsetY+a2.y - lch, varZ1));
    logo2.addVertex(ofVec3f(offsetX+g2.x - lcw, offsetY+g2.y - lch, varZ1));
    logo2.addVertex(ofVec3f(offsetX+h2.x - lcw, offsetY+h2.y - lch, varZ1));
    //text2
	logo2.addTexCoord(ofVec2f((a2.x)/lw, (a2.y)/lh));
	logo2.addTexCoord(ofVec2f((g2.x)/lw, (g2.y)/lh));
	logo2.addTexCoord(ofVec2f((h2.x)/lw, (h2.y)/lh));

	//mesh3
	float varZ2 = -1500 - ofRandom(100,200);
    logo3.addVertex(ofVec3f(offsetX+b2.x - lcw, offsetY+b2.y - lch, varZ2));
    logo3.addVertex(ofVec3f(offsetX+c2.x - lcw, offsetY+c2.y - lch, varZ2));
    logo3.addVertex(ofVec3f(offsetX+f2.x - lcw, offsetY+f2.y - lch, varZ2));
	//text3
	logo3.addTexCoord(ofVec2f((b2.x)/lw, (b2.y)/lh));
	logo3.addTexCoord(ofVec2f((c2.x)/lw, (c2.y)/lh));
	logo3.addTexCoord(ofVec2f((f2.x)/lw, (f2.y)/lh));
    //mesh4
    logo4.addVertex(ofVec3f(offsetX+b2.x - lcw, offsetY+b2.y - lch, varZ2));
    logo4.addVertex(ofVec3f(offsetX+f2.x - lcw, offsetY+f2.y - lch, varZ2));
    logo4.addVertex(ofVec3f(offsetX+g2.x - lcw, offsetY+g2.y - lch, varZ2));
    //text4
	logo4.addTexCoord(ofVec2f((b2.x)/lw, (b2.y)/lh));
	logo4.addTexCoord(ofVec2f((f2.x)/lw, (f2.y)/lh));
	logo4.addTexCoord(ofVec2f((g2.x)/lw, (g2.y)/lh));

    //mesh5
	float varZ3 = -1500 - ofRandom(200,300);
    logo5.addVertex(ofVec3f(offsetX+c2.x - lcw, offsetY+c2.y - lch, varZ3));
    logo5.addVertex(ofVec3f(offsetX+d2.x - lcw, offsetY+d2.y - lch, varZ3));
    logo5.addVertex(ofVec3f(offsetX+e2.x - lcw, offsetY+e2.y - lch, varZ3));
    //text5
	logo5.addTexCoord(ofVec2f((c2.x)/lw, (c2.y)/lh));
	logo5.addTexCoord(ofVec2f((d2.x)/lw, (d2.y)/lh));
	logo5.addTexCoord(ofVec2f((e2.x)/lw, (e2.y)/lh));
    //mesh6
    logo6.addVertex(ofVec3f(offsetX+c2.x - lcw, offsetY+c2.y - lch, varZ3));
    logo6.addVertex(ofVec3f(offsetX+e2.x - lcw, offsetY+e2.y - lch, varZ3));
    logo6.addVertex(ofVec3f(offsetX+f2.x - lcw, offsetY+f2.y - lch, varZ3));
    //text6
	logo6.addTexCoord(ofVec2f((c2.x)/lw, (c2.y)/lh));
	logo6.addTexCoord(ofVec2f((e2.x)/lw, (e2.y)/lh));
	logo6.addTexCoord(ofVec2f((f2.x)/lw, (f2.y)/lh));

}

//--------------------------------------------------------------
void Logo::update(){

}

//--------------------------------------------------------------
void Logo::draw(){

	ofScale(1/lw*0.5,1/lw*0.5,1/lw*0.5);
	ofPushMatrix();
	//ofRotateY(180);
	ofScale(15,15,15);
	photo.bind();
	tri1.draw();
	photo.unbind();
	ofPopMatrix();
	
	ofPushMatrix();
	ofRotateY(180);
	ofScale(13,13,13);
	logoImg1.bind();
	logo1.draw();
	logo2.draw();
	logoImg1.unbind();

	logoImg2.bind();
	logo3.draw();
	logo4.draw();
	logoImg2.unbind();

	logoImg3.bind();
	logo5.draw();
	logo6.draw();
	logoImg3.unbind();
	ofPopMatrix();



}

//--------------------------------------------------------------
void Logo::keyPressed(int key){

}

//--------------------------------------------------------------
void Logo::keyReleased(int key){

}

//--------------------------------------------------------------
void Logo::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Logo::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Logo::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Logo::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Logo::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Logo::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Logo::dragEvent(ofDragInfo dragInfo){

}
