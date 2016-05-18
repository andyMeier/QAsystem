//
//  questionMachine.cpp
//  QA1tryout
//
//  Created by Andrea Papenmeier on 08/05/16.
//
//

#include "questionMachine.h"

QuestionMachine::QuestionMachine(){
    
    answer = "";
    
    // load fonts to display stuff
    font.loadFont("futura_book.otf", 12);
    
}

//--------------------------------------------------------------
void QuestionMachine::draw(){
    
    font.drawString("You asked:", 20, 20);
    font.drawString(user_question, 20, 50);
    
    font.drawString(answer, 20, 100);
    
}

//--------------------------------------------------------------
void QuestionMachine::checkInput(string input){
    
    // catch exceptions: empty strings etc
    if (input.empty()==0){
        
        // first normalise
        input = normaliser.normalise(input);
        
        // display normalised question in a "nice" way:
        user_question = makeNice(input);
        
        
        
        
        // now make more sophisticated shit
        
        // stemming
        
        
        // dummy checker
        if (checkForWord(input, "hello")){
            answer = "Hi, nice to meet you!";
        }else{
            answer = "Sorry, I don't understand.";
        }
    }
    
}

//--------------------------------------------------------------
// check if input contains word
// only needed for dummy checker
bool QuestionMachine::checkForWord(string input, string word){
    
    // check if specified word is in input string
    if (input.find(word) < input.length()) {
        return true;
    }else{
        return false;
    }
    

}

//--------------------------------------------------------------
// returns a "nice" version of the input s, with capital beginning and question mark at the end
string QuestionMachine::makeNice(string s){
    char front = s.at(0);
    if (!isupper(front)) {
        front = toupper(front);
        s.erase(0,1);
        s.insert(0, ofToString(front));
    }
    s += "?";
    return s;
}



