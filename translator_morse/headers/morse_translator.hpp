//
//  morse_translator.hpp
//  translator_morse
//
//  Created by Kyrylo Kastornov on 23.12.2023.
//

#ifndef morse_translator_hpp
#define morse_translator_hpp

#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

class MorseTranslator
{
public:
    MorseTranslator();

    void setMorseCode(char character, const std::string& morse);
    std::string getMorseCode(char character) const;

    void startTranslation();

private:
    std::map<char, std::string> morseCodeMap;

    std::string morseToEnglish(const std::string& morseCode);
    std::string englishToMorse(const std::string& englishText);

    bool isValidMorse(const std::string& morseCode) const;
    bool isValidEnglish(const std::string& englishText) const;
};

#endif /* morse_translator_hpp */

