//
//  meaningMachine.h
//  QA1tryout
//
//  Created by Andrea Papenmeier on 18/05/16.
//
//

#ifndef __QA1tryout__meaningMachine__
#define __QA1tryout__meaningMachine__

#include <stdio.h>
#include "ofMain.h"
#include "stemming/english_stem.h"

class MeaningMachine{
    
public:
    MeaningMachine();
    
    string stemming(string word);
    string stemmingPhrase(string phrase);
    vector<string> convertToVector(string phrase);
    string convertToString(vector<string> phrase);
};

#endif /* defined(__QA1tryout__meaningMachine__) */
