//
//  meaningMachine.cpp
//  QA1tryout
//
//  Created by Andrea Papenmeier on 18/05/16.
//
//

#include "meaningMachine.h"


MeaningMachine::MeaningMachine(){
    
    
    
}

//--------------------------------------------------------------
// returns stemmed version of a single word
string MeaningMachine::stemming(string word){
    
    // catch exception of empty word
    if (word.empty()==0){
        
        // convert from string to wstring
        std::wstring result;
        result.assign(word.begin(), word.end());
        
        // get stemmed word
        stemming::english_stem<> StemEnglish;
        StemEnglish(result);
        
        // convert from wstring to string
        word.assign(result.begin(), result.end());
        
    }
    
    return word;
    
}

//--------------------------------------------------------------
// returns stemmed version of a phrase
string MeaningMachine::stemmingPhrase(string phrase){
    
    // catch exception of empty phrase
    if (phrase.empty()==0){
        
        // convert to vector
        vector<string> words = convertToVector(phrase);
        
        // iterate through vector
        for (int i = 0; i < words.size(); i++){
            
            // get current word
            string word = words[i];
            
            // stemm each word
            words[i] = stemming(word);
        }
        
        // convert back to string
        
        
    }
    
    // return string - no matter if empty or not
    return phrase;
    
}

//--------------------------------------------------------------
// puts a phrase in a string into a vector where each element is one word
vector<string> MeaningMachine::convertToVector(string phrase){
    string word;
    vector<string> words;
    
    for (stringstream s(phrase); s >> word; ){
        words.push_back(word);
    }
    
    return words;
}

//--------------------------------------------------------------
// puts a phrase as a vector back into a string with simple separation with blanc spaces
string MeaningMachine::convertToString(vector<string> phrase){
    
    string new_phrase;
    
    for (int i = 0; i < phrase.size(); i++){
        
        string word = phrase[i];
        
        if (i == (phrase.size()-1) ){
            new_phrase.append(word);
        }else{
            new_phrase.append(word);
            new_phrase.append(" ");
        }
        
    }
    
    return new_phrase;
}

//--------------------------------------------------------------


    