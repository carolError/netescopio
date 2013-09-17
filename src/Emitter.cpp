/*
 *  Emitter.cpp
 *  netescopio_antesala
 *
 *  Created by Lain on 31/08/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Emitter.h"

string letra[] = {"0","1","<avatar>","<cache>","<camuflaje>", "<copyright>",
		"<deriva>", "<desmontaje>", "<detournement>", "<hacking>","<interferencia>",
		"<laberinto>", "<lowtech>", "<metaversos>", "<remix>", "<resistencia>",
		"<sabotaje>", "<serendipia>", "<SPAM>","<tecnoadicciones>","<URL>",
		"<utopia>", "<vigilancia>", "<virulencia>", "<wiki>", "<2.0>"  };

void Emitter::setup(ofVec3f location){
	g.set(0,0,0);
	origin = location;
	
	//font[0].loadFont("BLANCH_CONDENSED.otf",48);
	//font[1].loadFont("Anonymous_Pro_Minus.ttf",48);
	font[0].loadFont("Akkurat-Mono.otf",25);
	font[1].loadFont("Akkurat-Mono.otf",48);
	//font[3].loadFont("Dosis-Medium.ttf",48);
	
	/*img[0].loadImage("avatar1.jpg");
	img[1].loadImage("avatar2.jpg");
	img[2].loadImage("avatar3.jpg");
	img[3].loadImage("avatar4.jpg");
	img[4].loadImage("avatar5.jpg");*/

	for (int i=0; i<23; i++){
		string fileName = "av/"+ofToString(i)+".jpg";
		img[i].loadImage(fileName);
		//cout << fileName << endl;
		//cout << "---" <<endl;
	}

	for(int i=0;i<2;i++){
		words.push_back(font[1].getStringMesh(letra[i],0,0));
	}

	for(int i=2;i<26;i++){
		words.push_back(font[0].getStringMesh(letra[i],0,0));
	}

}

void Emitter::addLetters(){
	Letter letter;

	float prob = ofRandom(1);
	if(prob<.9){
		letter.setup(ofRandom(0.5,2), origin, words[(int)ofRandom(2)],font[1].getFontTexture());
	}else{
		letter.setup(ofRandom(0.5,2), origin, words[(int)ofRandom(3,26)],font[0].getFontTexture());
	}

    letters.push_back(letter);
    
}

void Emitter::addImages(int m){
	Image image;
	int m_ = m;
	if (m_==0){
	image.setup(ofRandom(0.5,2), origin, img[(int)ofRandom(24)]);
    images.push_back(image);
	} else if(m_==1){
		image.setup(ofRandom(0.5,2), origin, img[7]);
	    images.push_back(image);

	} else if(m_==2){
			image.setup(ofRandom(0.5,2), origin, img[1]);
			images.push_back(image);

	} else if(m_==3){
		image.setup(ofRandom(0.5,2), origin, img[5]);
	    images.push_back(image);

	} else if(m_==4){
		image.setup(ofRandom(0.5,2), origin, img[10]);
	    images.push_back(image);

	} else if(m_==5){
		image.setup(ofRandom(0.5,2), origin, img[15]);
	    images.push_back(image);
	}
}

void Emitter::runLetters(){
	list<Letter>::iterator it;
    for(it = letters.begin(); it!=letters.end(); it++){
		it->applyForce(g);
		it->update();
		it->display();
        if (it->finished()){
        	list<Letter>::iterator itErase = it;
        	it--;
        	letters.erase(itErase);
        }
	}
    while(letters.size()>100){
    	letters.erase(letters.begin());
    }
}

void Emitter::runImages(){
	list<Image>::iterator it;
    for(it = images.begin(); it!=images.end(); it++){
		it->applyForce(g);
		it->update();
		it->display();
        if (it->finished()){
        	list<Image>::iterator itErase = it;
        	it--;
        	images.erase(itErase);
        }
	}
    while(images.size()>10){
    	images.erase(images.begin());
    }
}


