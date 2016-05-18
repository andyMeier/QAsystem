//
//  autocorrect.cpp
//  QA1tryout
//
//  Created by Andrea Papenmeier on 09/05/16.
//
//

#include "autocorrect.h"

Autocorrect::Autocorrect(){
    
    // get dictionary: fills global dictionary list
    get_dictionary();
    get_numbers();
    
    
}

//--------------------------------------------------------------
string Autocorrect::spell_check(string word){
    
    // check boundary cases:
    // empty strings
    if (word.empty()==0){
        // get all similar words
        similars = "";
        similars = find_similars(word);
        
        // after checking whole dictionary:
        
        // if string of similars is empty: take word as written by user
        // otherwise: if only one word in string, take that one
        // if multiple words in string: SOUNDEX code??????
        switch(word_in_string(similars)){
            case 0:
                // return word as written by user
                return word;
                break;
            case 1:
                // return word in string
                return similars;
                break;
            default:
                // word_in_string always can only return positive numbers
                // here: more than one similar word
                // perform more steps: SOUNDEX code, swapping?
                string swapped_similars = find_similars_for_switches(word);
                int amount = word_in_string(swapped_similars);
                
                switch (amount){
                    case 0:
                        // return word as written by user
                        return word;
                        break;
                    case 1:
                        // return word in string
                        return swapped_similars;
                        break;
                    default:
                        // if more than one word found ?????
                        return word;
                        break;
                }
        }
    }


}

//--------------------------------------------------------------
void Autocorrect::get_dictionary(){
    
    string line = "";
    ifstream dict;
    
    // new dictionary (without 's)
    dict.open("/Users/andreapapenmeier/Documents/of_v0.8.4_osx_release/apps/myApps/QA1tryout/src/dict/en-dict.txt");
    if (dict.fail()) {
        cout << "Input file opening failed.\n";
        exit(0);
    }
    
    for (int counter = 0; counter < dictionary_l; counter ++){
        // get next line from dictionary
        getline(dict, line);
        ////if (!line.empty()) line = line.erase(line.length()-1, string::npos);
        dictionary[counter] = line;
        //if(counter==0)cout << counter << " " << dictionary[counter] << endl;
    }
    dict.close();
    
    // construct alphabetic character-start-lookup table
    int alpha_counter = 1;
    
    // always starts with a
    alpha_indices[0] = 0;
    string curr_c = "a";
    
    for (int i = 1; i<dictionary_l; i++){
        // get first character, make sure it is a lower case letter
        char line_front_c = dictionary[i].at(0);
        line_front_c = tolower(line_front_c);
        string line_front = ofToString(line_front_c);
        //cout << i << " " << dictionary[i] << " " << line_front << " " << curr_c << " " << curr_c.compare(line_front) << endl;
        // compare first character with current character in alphabetic order
        if (curr_c.compare(line_front) == (-1)){
            // if character change to next character in alphabet
            curr_c = line_front;
            alpha_indices[alpha_counter] = i;
            alpha_counter++;
        }
    }
    // add ending index as well, so that we can easily calculate the amount of words with a specific front
    alpha_indices[26] = dictionary_l-1;
}

//--------------------------------------------------------------
void Autocorrect::get_numbers(){
    
    string line = "";
    ifstream nbr;
    const char* nbr_dict = "/Users/andreapapenmeier/Documents/of_v0.8.4_osx_release/apps/myApps/Levenshtein/src/dict/nbr.txt";
    
    // open stream
    nbr.open(nbr_dict);
    if (nbr.fail()) {
        cout << "Input file opening failed.\n";
        exit(0);
    }
    
    // fill array
    for (int i = 0; i<numbers_l; i++){
        getline(nbr, line);
        numbers[i] = line;
    }
    
    // close stream
    nbr.close();
    
}

//--------------------------------------------------------------
string Autocorrect::find_similars_for_switches(string word){
    
    int l = word.length();
    string similars_f = "";
    int ld_min = 3;
    int ld_thresh = 2;
    bool found = false;
    
    for (int i = 0; i<l; i++){
        string word_copy = word;
        
        // swap characters at current position
        if (i<(l-1)) {
            char c = word_copy.at(i);
            word_copy.replace(i, 1, ofToString(word_copy.at(i+1)));
            word_copy.replace(i+1, 1, ofToString(c));
        }else{
            // for last one check again the initial word (because only words with same front were considered in the first run)
            word_copy = word;
        }
        
        // now check dictionary again
        // stop if word found
        for (int it = 0; it < dictionary_l; ++it){
            if (!found){
                // get next word in dictionary
                string line = dictionary[it];
                
                // calculate Levenshtein distance
                int ld = levenshtein(word_copy, line);
                
                if (ld == 0){
                    // if similar word found, matching 100%
                    similars_f = line;
                    found = true;
                    break;
                }else if (ld < ld_min && ld <= ld_thresh){
                    // if word is found with a smaller LD than found before
                    similars_f = line;
                    ld_min = ld;
                }else if (ld == ld_min && similars_f.empty() && ld <= ld_thresh){
                    // if word with similar LD distance is found
                    similars_f = line;
                    ld_min = ld;
                }else if (ld == ld_min && !similars_f.empty() && ld <= ld_thresh){
                    // if equal LDs and already words in similar: append word to string
                    // ! separate words with comma --> word_in_string checks amount of commas + 1 !
                    similars_f.append(",");
                    similars_f.append(ofToString(line));
                }
            }
        }
    }
    
    return similars_f;
    
}

//--------------------------------------------------------------
string Autocorrect::find_similars(string word){
    
    string similars_f = "";
    int ld_min = 3;
    int ld_thresh = 2;
    
    char c = word.at(0);
    
    int it_begin = alpha_indices[get_index(c)];
    int it_end = alpha_indices[get_next_index(c)];
    
    for (int it = it_begin; it < it_end; ++it){
        
        // get next word in dictionary
        string line = dictionary[it];
        // calculate Levenshtein distance
        int ld = levenshtein(word, line);
        
        if (ld == 0){
            // if similar word found, matching 100%
            similars_f = line;
            break;
        }else if (ld < ld_min && ld <= ld_thresh){
            // if word is found with a smaller LD than found before
            similars_f = line;
            ld_min = ld;
        }else if (ld == ld_min && similars_f.empty() && ld <= ld_thresh){
            // if word with similar LD distance is found
            similars_f = line;
            ld_min = ld;
        }else if (ld == ld_min && !similars_f.empty() && ld <= ld_thresh){
            // if equal LDs and already words in similar: append word to string
            // ! separate words with comma --> word_in_string checks amount of commas + 1 !
            similars_f.append(",");
            similars_f.append(ofToString(line));
        }
    }
    return similars_f;
}

//--------------------------------------------------------------
int Autocorrect::word_in_string(string s){
    
    // counter = amount of matching words in string
    // returns counter > 0 for more than one word
    string s_copy = s;
    int counter = 0;
    while (s_copy.find(',') <= s_copy.length()) {
        s_copy = s_copy.substr( (s_copy.find(',')+1), string::npos );
        counter ++;
    }
    
    // if string is not empty: add an extra counter step to compensate for the first added element
    if (!s.empty()) counter ++;
    
    return counter;
    
}

//--------------------------------------------------------------
bool Autocorrect::check_number(string word){
    
    bool found = false;
    // compare words
    for (int i = 0; i<numbers_l; i++){
        if (numbers[i]==word) found = true;
    }
    
    if (found){
        return true;
    }else{
        return false;
    }
    
}

//--------------------------------------------------------------
int Autocorrect::levenshtein(string s, string t){
    int n = s.length();
    int m = t.length();
    
    if (n == 0){
        return m;
    }else if (m == 0){
        return n;
    }else{
        
        int matrix[m+1][n+1];
        
        // catch some exceptions
        for (int i = 0; i<=n; i++){
            matrix[0][i] = i;
        }
        for (int i = 0; i<=m; i++){
            matrix[i][0] = i;
        }
        
        // levenshtein algorithm
        for (int i = 1; i<=n; i++){
            for (int j = 1; j<=m; j++){
                
                int cost = 0;
                if (s.at(i-1) == t.at(j-1)){
                    cost = 0;
                }else{
                    cost = 1;
                }
                
                int a = matrix[j-1][i]+1;
                int b = matrix[j][i-1]+1;
                int c = matrix[j-1][i-1]+cost;
                int result = min (c, min(a, b));
                
                matrix[j][i] = result;
            }
        }
        return matrix[m][n];
    }
}

//--------------------------------------------------------------
int Autocorrect::get_index(char c){
    
    switch (c){
        case 'a':
            return 0;
            break;
        case 'b':
            return 1;
            break;
        case 'c':
            return 2;
            break;
        case 'd':
            return 3;
            break;
        case 'e':
            return 4;
            break;
        case 'f':
            return 5;
            break;
        case 'g':
            return 6;
            break;
        case 'h':
            return 7;
            break;
        case 'i':
            return 8;
            break;
        case 'j':
            return 9;
            break;
        case 'k':
            return 10;
            break;
        case 'l':
            return 11;
            break;
        case 'm':
            return 12;
            break;
        case 'n':
            return 13;
            break;
        case 'o':
            return 14;
            break;
        case 'p':
            return 15;
            break;
        case 'q':
            return 16;
            break;
        case 'r':
            return 17;
            break;
        case 's':
            return 18;
            break;
        case 't':
            return 19;
            break;
        case 'u':
            return 20;
            break;
        case 'v':
            return 21;
            break;
        case 'w':
            return 22;
            break;
        case 'x':
            return 23;
            break;
        case 'y':
            return 24;
            break;
        case 'z':
            return 25;
            break;
        default:
            return -1;
            break;
    }
    
}

//--------------------------------------------------------------
int Autocorrect::get_next_index(char c){
    
    switch (c){
        case 'a':
            return 1;
            break;
        case 'b':
            return 2;
            break;
        case 'c':
            return 3;
            break;
        case 'd':
            return 4;
            break;
        case 'e':
            return 5;
            break;
        case 'f':
            return 6;
            break;
        case 'g':
            return 7;
            break;
        case 'h':
            return 8;
            break;
        case 'i':
            return 9;
            break;
        case 'j':
            return 10;
            break;
        case 'k':
            return 11;
            break;
        case 'l':
            return 12;
            break;
        case 'm':
            return 13;
            break;
        case 'n':
            return 14;
            break;
        case 'o':
            return 15;
            break;
        case 'p':
            return 16;
            break;
        case 'q':
            return 17;
            break;
        case 'r':
            return 18;
            break;
        case 's':
            return 19;
            break;
        case 't':
            return 20;
            break;
        case 'u':
            return 21;
            break;
        case 'v':
            return 22;
            break;
        case 'w':
            return 23;
            break;
        case 'x':
            return 24;
            break;
        case 'y':
            return 25;
            break;
        case 'z':
            return 26;
            break;
        default:
            return -1;
            break;
    }
    
}





