//
//  morse_translator.cpp
//  translator_morse
//
//  Created by Kyrylo Kastornov on 23.12.2023.
//
#include "../headers/morse_translator.hpp"

MorseTranslator::MorseTranslator()
{
    setMorseCode('A', ".-");
    setMorseCode('B', "-...");
    setMorseCode('C', "-.-.");
    setMorseCode('D', "-..");
    setMorseCode('E', ".");
    setMorseCode('F', "..-.");
    setMorseCode('G', "--.");
    setMorseCode('H', "....");
    setMorseCode('I', "..");
    setMorseCode('J', ".---");
    setMorseCode('K', "-.-");
    setMorseCode('L', ".-..");
    setMorseCode('M', "--");
    setMorseCode('N', "-.");
    setMorseCode('O', "---");
    setMorseCode('P', ".--.");
    setMorseCode('Q', "--.-");
    setMorseCode('R', ".-.");
    setMorseCode('S', "...");
    setMorseCode('T', "-");
    setMorseCode('U', "..-");
    setMorseCode('V', "...-");
    setMorseCode('W', ".--");
    setMorseCode('X', "-..-");
    setMorseCode('Y', "-.--");
    setMorseCode('Z', "--..");
}

void MorseTranslator::setMorseCode(char character, const std::string& morse)
{
    morseCodeMap[character] = morse;
}

std::string MorseTranslator::getMorseCode(char character) const
{
    auto it = morseCodeMap.find(character);
    return (it != morseCodeMap.end()) ? it->second : "";
}


std::string MorseTranslator::morseToEnglish(const std::string& morseCode)
{
    std::istringstream iss(morseCode);
    std::string token;
    std::string result;

    while (getline(iss, token, ' '))
    {
        auto it = std::find_if(morseCodeMap.begin(), morseCodeMap.end(),
                               [token](const auto& pair) { return pair.second == token; });

        if (it != morseCodeMap.end())
        {
            result += it->first;
        }
    }

    return result;
}

std::string MorseTranslator::englishToMorse(const std::string& englishText)
{
    std::string result;

    for (char ch : englishText)
    {
        if (std::isalpha(ch))
        {
            result += morseCodeMap[std::toupper(ch)] + ' ';
        }
        
        else if (ch == ' ')
        {
            result += "  ";
        }
    }

    return result.empty() ? result : result.substr(0, result.size() - 1);
}

bool MorseTranslator::isValidMorse(const std::string& morseCode) const
{
    return std::all_of(morseCode.begin(), morseCode.end(), [&](char ch)
    {
        if (ch == ' ' || ch == '.' || ch == '-')
        {
            return true;
        }

        auto it = morseCodeMap.find(std::toupper(ch));

        return it != morseCodeMap.end();
    });
}


bool MorseTranslator::isValidEnglish(const std::string& englishText) const
{
    return std::all_of(englishText.begin(), englishText.end(), [](char ch)
    {
        return std::isalpha(ch) || ch == ' ';
    });
}


void MorseTranslator::startTranslation()
{
    int choice;

    do
    {
        std::cout << "Що необхідно зробити?" << "\n";
        std::cout << "1. Кодувати." << "\n";
        std::cout << "2. Декодувати." << "\n";
        std::cout << "Введіть 1 або 2: ";

        while (!(std::cin >> choice) || (choice != 1 && choice != 2))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Будь ласка, введіть число 1 або 2.\n";
            std::cout << "Введіть 1 або 2: ";
        }

        std::cin.ignore();

        if (choice == 1)
        {
            std::string englishText;

            do
            {
                std::cout << "Введіть текст: ";
                std::getline(std::cin, englishText);

                if (isValidEnglish(englishText))
                {
                    std::string morseCode = englishToMorse(englishText);
                    std::cout << "Код Морзе: " << morseCode << "\n";
                    break;
                }
                
                else
                {
                    std::cout << "Введено неправильний текст. Будь ласка, введіть лише англійські літери та пробіли.\n";
                }
                
            } while (true);
        }
        
        else if (choice == 2)
        {
            std::string morseCode;

            do
            {
                std::cout << "Введіть код Морзе: ";
                std::getline(std::cin, morseCode);

                if (isValidMorse(morseCode))
                {
                    std::string englishText = morseToEnglish(morseCode);
                    std::cout << "Англійський текст: " << englishText << "\n";
                    break;
                }
                
                else
                {
                    std::cout << "Введено неправильний код Морзе. Будь ласка, введіть лише символи коду Морзе, тире, крапки та пробіли.\n";
                }
                
            } while (true);
        }

        std::cout << "Повторно скористатись перекладачем?" << "\n";
        std::cout << "1. Так." << "\n";
        std::cout << "2. Ні." << "\n";
        std::cout << "Введіть 1 або 2: ";

        while (!(std::cin >> choice) || (choice != 1 && choice != 2))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Будь ласка, введіть число 1 або 2.\n";
            std::cout << "Введіть 1 або 2: ";
        }

        std::cin.ignore();

    } while (choice == 1);
}
