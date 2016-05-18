//
//  autocorrect.h
//  QA1tryout
//
//  Created by Andrea Papenmeier on 09/05/16.
//
//

#ifndef __QA1tryout__autocorrect__
#define __QA1tryout__autocorrect__

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

#include "ofMain.h"

class Autocorrect{
public: 
    Autocorrect();
    
    // new variables
    string word, similars;
    string dictionary[99799]; // number needs to be inserted manually!
    int dictionary_l = ARRAY_SIZE(dictionary);
    string numbers[65]; // number needs to be inserted manually!
    int numbers_l = ARRAY_SIZE(numbers);
    int alpha_indices[27]; // = 26 characters in alphabet
    int alpha_l = ARRAY_SIZE(alpha_indices);
    
    // new functions
    int levenshtein(string s, string t);
    int word_in_string(string s);
    string find_similars(string word);
    string find_similars_for_switches(string word);
    void get_dictionary();
    void get_numbers();
    int get_index(char c);
    int get_next_index(char c);
    string spell_check(string word);
    bool check_number(string word);
    
};

#endif /* defined(__QA1tryout__autocorrect__) */
