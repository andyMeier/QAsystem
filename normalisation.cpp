//
//  normalisation.cpp
//  QA1tryout
//
//  Created by Andrea Papenmeier on 17/05/16.
//
//

#include "normalisation.h"

Normaliser::Normaliser(){
    
}


//--------------------------------------------------------------
// returns a normalised string version of the input phrase
string Normaliser::normalise(string phrase){
    
    // get rid of linebreaks
    phrase = deleteLineBreaks(phrase);
    
    /*
    // not necessary because of conversion to vector!
    // delete punctuation ***needs to go before deleting the blanc spaces!***
    phrase = deletePunctuation(phrase);
    
    // delete unneccessary blanc spaces
    phrase = deleteBlancSpaces(phrase);
    */
    
    // convert to lower letters
    phrase = convertToLower(phrase);
    
    // convert to vector
    // automatically discards all punctuation and blanc spaces!
    vector<string> words = convertToVector(phrase);
    
    // iterate through whole phrase, per word
    for (int i = 0; i < words.size(); i++){
        
        // get current word
        string word = words[i];
        
        // do nothing if it is a number ?!
        // spell checker ***per word***, for non-numbers:
        if (checkIfNumber(word)) words[i] = spellchecker.spell_check(word);
        
    }
    
    return (convertToString(words));
    
}

//--------------------------------------------------------------
// returns vector with each element being one word of the phrase
// automatically discards all punctuation and blanc spaces!
vector<string> Normaliser::convertToVector(string phrase){
    string word;
    vector<string> words;
    
    for (stringstream s(phrase); s >> word; ){
        words.push_back(word);
    }
    
    return words;
}

//--------------------------------------------------------------
// puts a phrase as a vector back into a string with simple separation with blanc spaces
string Normaliser::convertToString(vector<string> phrase){
    
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
string Normaliser::deleteLineBreaks(string phrase){
    
    string linebreak = "\n";
    while (phrase.find(linebreak) < phrase.length()){
        phrase.replace(phrase.find(linebreak),linebreak.length(),"");
    }
    
    return phrase;
    
}

//--------------------------------------------------------------
// replaces all punctuation signs by blanc spaces
string Normaliser::deletePunctuation(string phrase){
    
    int lenght = phrase.length();
    for (int i = 0; i<lenght; i++){
        char curr_c = phrase.at(i);
        if (isPunctuation(curr_c)) phrase.replace(i, 1, " ");
    }
    
    return phrase;
    
}

//--------------------------------------------------------------
// deletes unneccessary blanc spaces (--> exactly one space between two words, no space at beginning / end of phrase)
string Normaliser::deleteBlancSpaces(string phrase){
    
    // needed?
    
}

//--------------------------------------------------------------
string Normaliser::convertToLower(string phrase){
    
    transform(phrase.begin(), phrase.end(), phrase.begin(), ::tolower);
    return phrase;

}

//--------------------------------------------------------------
// returns true if the input word is a written number
bool Normaliser::checkIfNumber(string word){
    
    bool found = false;
    spellchecker.check_number(word);
    
    if (found){
        return true;
    }else{
        return false;
    }
}

//--------------------------------------------------------------
// returns true if input character is a punctuation sign
bool Normaliser::isPunctuation(char c){
    
    if ( (c>32 && c<48) || (c>57 && c<65) || (c>90 && c<97) || (c>122 && c<127) ){
        return true;
    }else{
        return false;
    }
    
}