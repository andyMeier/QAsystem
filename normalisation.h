//
//  normalisation.h
//  QA1tryout
//
//  Created by Andrea Papenmeier on 17/05/16.
//
//

#ifndef __QA1tryout__normalisation__
#define __QA1tryout__normalisation__

#include "ofMain.h"
#include "autocorrect.h"

class Normaliser{
    
public:
    Normaliser();
    
    string normalise(string phrase);
    vector<string> convertToVector(string phrase);
    string convertToString(vector<string> phrase);
    string deleteLineBreaks(string phrase);
    string deletePunctuation(string phrase);
    string deleteBlancSpaces(string phrase);
    string convertToLower(string phrase);
    
    bool checkIfNumber(string word);
    bool isPunctuation(char c);
    
    Autocorrect spellchecker;
    
};

#endif /* defined(__QA1tryout__normalisation__) */
