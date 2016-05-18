//
//  questionMachine.h
//  QA1tryout
//
//  Created by Andrea Papenmeier on 08/05/16.
//
//

#ifndef __QA1tryout__questionMachine__
#define __QA1tryout__questionMachine__

#include "ofMain.h"
#include <stdio.h>
#include "normalisation.h"
#include "meaningMachine.h"

class QuestionMachine{
public:
    QuestionMachine();
    
    void draw();
    void checkInput(string input);
    bool checkForWord(string input, string word); // only needed for dummy checker
    string makeNice(string s);

    Normaliser normaliser;
    MeaningMachine meaningMachine;
    
private:
    ofTrueTypeFont font;
    
    string answer;
    string user_question;
    
    
};

#endif /* defined(__QA1tryout__questionMachine__) */
