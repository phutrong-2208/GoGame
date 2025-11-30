#include "metaControls.hpp"
std :: string MetaControls :: encode(int x, int y){ 
    char character = (char)(x + 'A'); 
    if(character >= 'I') character++; 
    return character + std :: to_string(y + 1); 
} 
std :: pair<int, int> MetaControls :: decode(const std :: string &s){
    //for instance, s = "Q16"
    int x = s[0] - 'A' - (s[0] > 'I'); 
    int y = std :: stoi(s.substr(1)) - 1;
    return std :: make_pair(x, y); 
}