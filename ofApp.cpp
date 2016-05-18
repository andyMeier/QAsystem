#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60); // run at 60 fps
    ofBackground(150);
    
    // load fonts to display stuff
    font.loadFont("futura_book.otf", 12);
    titleFont.loadFont("futura_book.otf", 20);
    
    typing = "";
    display = "";

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(170);
    ofRect(10, 233, 480, 40); //input field
    ofRect(10, 283, 480, 210); // previous questions field
    
    ofSetColor(255);
    font.drawString(typing, 20, 250); // display current input
    font.drawString(display, 20, 300); // display previous question
    questionMachine.draw(); // display answer of QA system

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // if we didn't hit return, add the key to our string
    if(key != OF_KEY_RETURN){
        
        // some trickery: ignore the backspace key
        if(key != OF_KEY_BACKSPACE){
            char character = key;
            
            // REWORK: insert linebreak before beginning of current word
            // insert linebreak if line gets too long
            if (typing.length() == 45) typing.append("\n");
            
            // check that input does not get too long to display
            if (typing.length() <= 90) typing += character;
        }
        else{
            if(typing.size() > 0){
                typing.erase(typing.end() - 1);
            }
        }
        
    }
    // RETURN pressed: copy to last displayed questions, send to questionMachine.
    else{
        // send to questionMachine
        questionMachine.checkInput(typing);
        
        display.insert(0, "\n");
        display.insert(0, typing);
        
        typing = "";
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
