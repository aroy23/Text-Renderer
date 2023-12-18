#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <sstream>
#include <streambuf>
#include <cassert>
using namespace std;
int render(int lineLength, istream& inf, ostream& outf);
bool hasSpecialCharacter(char poop[]);
bool hasHyphen(char word[]);
void separateHyphen(char word[]);
void shiftToHyphen(char shiftString[], int num);
void testRender(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue)
{
    istringstream iss(input);
    ostringstream oss;
    ostringstream dummy;
    streambuf* origCout = cout.rdbuf(dummy.rdbuf());
    int retval = render(lineLength, iss, oss);
    cout.rdbuf(origCout);
    if ( ! dummy.str().empty())
        cerr << "WROTE TO COUT INSTEAD OF THIRD PARAMETER FOR: " << input << endl;
    else if (retval != expectedReturnValue)
        cerr << "WRONG RETURN VALUE FOR: " << input << endl;
    else if (retval == 2)
    {
        if ( ! oss.str().empty())
            cerr << "WROTE OUTPUT WHEN LINELENGTH IS " << lineLength << endl;
    }
    else if (oss.str() != expectedOutput)
        cerr << "WRONG RESULT FOR: " << input << endl;
}

int main()
{
    //    //1. Tests leading and trailing spaces as well as multiple spaces, new lines, and tabs between words to make sure whitespace is eliminated
    //    testRender(7, "   This\n\t\tis a\ntest   \t\n    ", "This is\na test\n", 0);
    //    //2. Tests normal paragraph break
    //    testRender(5, "Hi @P@ hi", "Hi\n\nhi\n", 0);
    //    //3. Tests that a trailing paragraph break will not create new lines
    //    testRender(8, "This is a test @P@", "This is\na test\n", 0);
    //    //4. Tests that consecutive paragraph breaks only result in on break being activated
    //    testRender(5, "Hi- @P@ @P@ @P@ hi-", "Hi-\n\nhi-\n", 0);
    //    //5. Tests that function returns 2 if line length is less than 1
    //    testRender(0, "hi", "hi\n", 2);
    //    //6. Tests that function with a line length greater than 250
    //    testRender(300, ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .", ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .\n", 0);
    //    //7. Tests that if a word is longer than line length then function splits across lines and returns 1
    //    testRender(6, "Testing", "Testin\ng\n", 1);
    //    //8. Tests that if two words are longer than line length are in a row then they split lines correctly with word portions filling up as much as they can on each line by themselves
    //    testRender(6, "Testing Testing", "Testin\ng\nTestin\ng\n", 1);
    //    //9. Tests if two words fit on line length then a space separates both words
    //    testRender(20, "Testing Testing", "Testing Testing\n", 0);
    //    //10. Tests a short word that fits on line length starts with a space when following a word that goes over line length
    //    testRender(6, "Testing hi", "Testin\ng hi\n", 1);
    //    //11. Tests that when the last character of an output word is a special character, (., ?, !, :) the following word is separated by two blanks
    //    testRender(15, "Testing! hey", "Testing!  hey\n", 0);
    //    //12. Tests that when the file is empty, then nothing is changed in the file and 0 is returned
    //    testRender(10, "", "", 0);
    //    //13. Tests when a hyphenated word fits on line length, then word portions are not split up
    //    testRender(10, "so-called", "so-called\n", 0);
    //    //14. Tests when a hyphenated word does not fit on line length then word portions are split up correctly by word portions using hyphen rules
    //    testRender(5, "so-called", "so-\ncalle\nd\n", 1);
    //    //15. Tests that a word with multiple hyphens in a row, leading hyphens, and trailing hyphens is split up correctly by word portions using hyphen rules
    //    testRender(3, "-I-love--CS-31-", "-I-\nlov\ne--\nCS-\n31-\n", 1);
    //    //16. Tests word with only hyphens
    //    testRender(6, "--------------", "------\n------\n--\n", 0);
    //    //17. Tests input with multiple hyphenated words and regular words seperated by spaces to make sure normal world behavior and hyphenated word behavior works together corrrectly
    //    testRender(8, "Hey- computerscienc--e thirtyone is -SUPER-- Fun--", "Hey-\ncomputer\nscienc--\ne\nthirtyon\ne is -\nSUPER--\nFun--\n", 1);
    //    //18. Tests if a leading paragraph break will not create a new line
    //    testRender(10, "@P@ cat", "cat\n", 0);
    //    //19. Tests if a word will enter a new line when it is too big for line length following another word
    //    testRender(5, "cat cat", "cat\ncat\n", 0);
    //    //20. Tests if a word will enter a new line when it is too big for line length following a special double space character in another word
    //    testRender(5, "cat. cat", "cat.\ncat\n", 0);
    //    //21. Tests if a words will split with spaces when hyphenated words are following each other
    //    testRender(5, "a-a -a-a-aa-", "a-a -\na-a-\naa-\n", 0);
    //    //22. Tests if the only word in the input ends in a double space character then no spaces are outputted
    //    testRender(10, "computer.", "computer.\n", 0);
    //    //23. Tests that a paragraph break wont work when not followed by whitespace before and after
    //    testRender(10, "P@P@P", "P@P@P\n", 0);
    //    //24. Tests paragraph break on a new line
    //    testRender(10, "cat.\n@P@\ncat", "cat.\n\ncat\n", 0);
    //    //25. Tests consecutive leading paragraph breaks and consecutive trailing paragraph breaks
    //    testRender(10, "@P@ @P@ @P@ cat @P@ @P@ @P@", "cat\n", 0);
    //    //26. Tests if only thing in file is paragraph break output should be empty
    //    testRender(10, "@P@", "", 0);
    //    //27. Tests if only thing in file is consecutive paragraph breaks output should be empty
    //    testRender(10, "@P@ @P@", "", 0);
    //    cerr << "Tests complete" << endl;
    ifstream infile("/Users/arnav/Desktop/data.txt");
    int returnCode = render(20, infile, cout);
    cout << "Return code is " << returnCode << endl;
}

int render(int lineLength, istream& inf, ostream& outf)
{
    //returns 2 for a bad input of linelength
    if(lineLength < 1)
    {
        return 2;
    }
    //Used to print new break
    bool breaking = false;
    //used for shifting shiftLine in the instance of a hyphen
    char lineCopy[251];
    //hyphenCounter used to check which hyphen word needs to be shifted too
    int hyphenCounter = 0;
    //used to check if last word is hyphen for shifting string
    bool lastWordHyphen = false;
    //Used for shifting hyphenated words for strtok;
    char shiftLine[251];
    //checks for normal word
    bool normalWord = true;
    //used to store word portions of hyphenated word
    char hyphenWord[251];
    //empty file check
    bool notEmpty = false;
    //special character at end check
    bool charAtEnd = false;
    //if 1 needs to be returned when word gets split between lines
    bool return1 = false;
    //If word needs space on same line
    bool spaced = false;
    //C-String for paragraph break to compare
    char paragraphBreak[4] = "@P@";
    //C-String to store a line
    char line[251];
    //C-String used to split up words if they are longer than lineLength
    char wordTemp[251];
    char* word;
    char* wordHyphen;
    //Counter used to check if lineLength is being exceeded
    int lineCounter = 0;
    //Used to format the first word
    bool firstWord = true;
    //program experiences paragraph break
    bool hasBreaked = false;
    //firstBreak boolean to prevent against outputs of just empty lines given just one break in input
    bool firstBreak = false;
    //Keeps getting line till no more lines left
    while(inf.getline(line, 251))
    {
        hyphenCounter = 0;
        strcpy(shiftLine, line);
        strcpy(lineCopy, line);
        //stores word portion by elimating whitespace into word
        word = strtok(line, " \n\t");
        while(word != nullptr)
        {
            if(word != nullptr)
            {
                //processes words with hyphen that go over the line length
                if((hasHyphen(word) && (strlen(word) + lineCounter) > lineLength) || (normalWord == true && hasHyphen(word) && (strlen(word) + lineCounter + 1) > lineLength))
                {
                    firstBreak = false;
                    //determines how many hyphens word portion has so shiftToHyphen function can work properly
                    for(int i = 0; i < strlen(word); i++)
                    {
                        if(word[i] == '-')
                        {
                            hyphenCounter++;
                        }
                    }
                    //separating hyphenated word into word portions and copying one portion at a time into wordHyphen in a while loop
                    lastWordHyphen = true;
                    strcpy(hyphenWord, word);
                    separateHyphen(hyphenWord);
                    wordHyphen = strtok(hyphenWord, " \n\t");
                    while(wordHyphen != nullptr)
                    {
                        if(wordHyphen != nullptr)
                        {
                            notEmpty = true;
                            //Enters if first word portion on line
                            if(firstWord)
                            {
                                normalWord = false;
                                //Enters if first word portion of hyphen is shorter than lineLength
                                if(strlen(wordHyphen) + lineCounter <= lineLength)
                                {
                                    firstWord = false;
                                    outf << wordHyphen;
                                    lineCounter += strlen(wordHyphen);
                                }
                                //If first word portion is longer than linelength, wordportion gets split up between two lines
                                else if(strlen(wordHyphen) + lineCounter > lineLength)
                                {
                                    return1 = true;
                                    firstWord = false;
                                    strcpy(wordTemp, wordHyphen);
                                    int i;
                                    int j = 0;
                                    while(j != strlen(wordTemp))
                                    {
                                        for(i = 0; i < lineLength; i++)
                                        {
                                            if(j < strlen(wordTemp))
                                            {
                                                outf << wordTemp[j];
                                                j++;
                                                lineCounter++;
                                            }
                                        }
                                        if(j != strlen(wordTemp))
                                        {
                                            outf << '\n';
                                            lineCounter = 0;
                                        }
                                    }
                                }
                            }
                            //deals with everything thats not first word portion
                            else if(!firstWord)
                            {
                                if(breaking)
                                {
                                    outf << '\n' << '\n';
                                    breaking = false;
                                }
                                //double space needs to happen and word portion can fit on line
                                if(normalWord == true && charAtEnd == true && strlen(wordHyphen) + lineCounter + 2 <= lineLength)
                                {
                                    normalWord = false;
                                    //if not following break
                                    if(!hasBreaked)
                                    {
                                        outf << "  ";
                                        spaced = true;
                                    }
                                    //print word portion
                                    outf << wordHyphen;
                                    if(spaced)
                                    {
                                        lineCounter += strlen(wordHyphen) + 2;
                                    }
                                    else
                                    {
                                        lineCounter += strlen(wordHyphen);
                                    }
                                    spaced = false;
                                }
                                //if word portion plus space can fit on line then enter
                                else if(normalWord == true && strlen(wordHyphen) + lineCounter + 1 <= lineLength)
                                {
                                    normalWord = false;
                                    //if not following break
                                    if(!hasBreaked)
                                    {
                                        outf << " ";
                                        spaced = true;
                                    }
                                    //print word
                                    outf << wordHyphen;
                                    if(spaced)
                                    {
                                        lineCounter += strlen(wordHyphen) + 1;
                                    }
                                    else
                                    {
                                        lineCounter += strlen(wordHyphen);
                                    }
                                    spaced = false;
                                }
                                //if word portion plus space can't fit on line then enter
                                else if(normalWord == true && strlen(wordHyphen) + lineCounter + 1 > lineLength)
                                {
                                    normalWord = false;
                                    //if word portion by itself can fit on line
                                    if(strlen(wordHyphen) <= lineLength)
                                    {
                                        strcpy(wordTemp, wordHyphen);
                                        if(!hasBreaked)
                                        {
                                            outf << '\n';
                                            lineCounter = 0;
                                        }
                                        int i;
                                        for(i = 0; i < strlen(wordHyphen); i++)
                                        {
                                            outf << wordTemp[i];
                                            lineCounter += 1;
                                        }
                                        //if word portion needs to be split between lines to be fit
                                    }
                                    else if(strlen(wordHyphen) > lineLength)
                                    {
                                        return1 = true;
                                        strcpy(wordTemp, wordHyphen);
                                        if(!hasBreaked)
                                        {
                                            outf << '\n';
                                            lineCounter = 0;
                                        }
                                        int i;
                                        int j = 0;
                                        while(j != strlen(wordTemp))
                                        {
                                            for(i = 0; i < lineLength; i++)
                                            {
                                                if(j < strlen(wordTemp))
                                                {
                                                    outf << wordTemp[j];
                                                    j++;
                                                    lineCounter++;
                                                }
                                            }
                                            if(j != strlen(wordTemp))
                                            {
                                                outf << '\n';
                                                lineCounter = 0;
                                            }
                                        }
                                    }
                                }
                                //if word can fit on line then enter
                                else if(strlen(wordHyphen) + lineCounter <= lineLength)
                                {
                                    normalWord = false;
                                    outf << wordHyphen;
                                    lineCounter += strlen(wordHyphen);
                                }
                                //if word can't fit on line then enter
                                else if(strlen(wordHyphen) + lineCounter > lineLength)
                                {
                                    normalWord = false;
                                    //if word by itself can fit on line
                                    if(strlen(wordHyphen) <= lineLength)
                                    {
                                        strcpy(wordTemp, wordHyphen);
                                        if(!hasBreaked)
                                        {
                                            outf << '\n';
                                            lineCounter = 0;
                                        }
                                        int i;
                                        for(i = 0; i < strlen(wordTemp); i++)
                                        {
                                            outf << wordTemp[i];
                                            lineCounter += 1;
                                        }
                                    }
                                    //if word needs to be split between lines to be fit
                                    else if(strlen(wordHyphen) > lineLength)
                                    {
                                        normalWord = false;
                                        return1 = true;
                                        strcpy(wordTemp, wordHyphen);
                                        if(!hasBreaked)
                                        {
                                            outf << '\n';
                                            lineCounter = 0;
                                        }
                                        int i;
                                        int j = 0;
                                        while(j != strlen(wordTemp))
                                        {
                                            for(i = 0; i < lineLength; i++)
                                            {
                                                if(j < strlen(wordTemp))
                                                {
                                                    outf << wordTemp[j];
                                                    j++;
                                                    lineCounter++;
                                                }
                                            }
                                            if(j != strlen(wordTemp))
                                            {
                                                outf << '\n';
                                                lineCounter = 0;
                                            }
                                        }
                                    }
                                }
                            }
                            //if word doesn't equal a break enter
                            if(strcmp(wordHyphen, paragraphBreak) != 0)
                            {
                                hasBreaked = false;
                            }
                        }
                        //If has special characters at the end then set bool to true so double space behavior can activate accordingly
                        if(hasSpecialCharacter(wordHyphen))
                        {
                            charAtEnd = true;
                        }
                        else
                        {
                            charAtEnd = false;
                        }
                        wordHyphen = strtok(nullptr, " \n\t");
                    }
                    //sets normalWord to true so that spaces and double spaces can work normally if two or more hyphenated words in a row where to be in the input file
                    normalWord = true;
                }
                //processes everything else
                else
                {
                    firstBreak = false;
                    if(hasHyphen(word))
                    {
                        for(int i = 0; i < strlen(word); i++)
                        {
                            if(word[i] == '-')
                            {
                                hyphenCounter++;
                            }
                        }
                    }
                    normalWord = true;
                    notEmpty = true;
                    //parsgraph breaks
                    if(strcmp(word, paragraphBreak) == 0)
                    {
                        if(firstWord)
                        {
                            firstBreak = true;
                            lineCounter = 0;
                        }
                        if(!hasBreaked && !firstWord)
                        {
                            breaking = true;
                        }
                        hasBreaked = true;
                        lineCounter = 0;
                    }
                    //Enters if first word on line
                    else if(firstWord)
                    {
                        //Enters if first word is shorter than lineLength
                        if(strlen(word) + lineCounter <= lineLength)
                        {
                            firstWord = false;
                            outf << word;
                            lineCounter += strlen(word);
                        }
                        //If first word is longer than linelength, word gets split up between two lines
                        else if(strlen(word) + lineCounter > lineLength)
                        {
                            return1 = true;
                            firstWord = false;
                            strcpy(wordTemp, word);
                            int i;
                            int j = 0;
                            while(j != strlen(wordTemp))
                            {
                                for(i = 0; i < lineLength; i++)
                                {
                                    if(j < strlen(wordTemp))
                                    {
                                        outf << wordTemp[j];
                                        j++;
                                        lineCounter++;
                                    }
                                }
                                if(j != strlen(wordTemp))
                                {
                                    outf << '\n';
                                    lineCounter = 0;
                                }
                            }
                        }
                    }
                    //deals with everything thats not first word
                    else if(!firstWord)
                    {
                        if(breaking)
                        {
                            outf << '\n' << '\n';
                            breaking = false;
                        }
                        //double space needs to happen and word can fit on line
                        if(charAtEnd == true && strlen(word) + lineCounter + 2 <= lineLength)
                        {
                            //if not following break
                            if(!hasBreaked)
                            {
                                outf << "  ";
                                spaced = true;
                            }
                            //print word
                            outf << word;
                            if(spaced)
                            {
                                lineCounter += strlen(word) + 2;
                            }
                            else
                            {
                                lineCounter += strlen(word);
                            }
                            spaced = false;
                        }
                        //double space needs to happen and word can't fit on line
                        else if(charAtEnd == true && strlen(word) + lineCounter + 2 > lineLength)
                        {
                            firstWord = false;
                            strcpy(wordTemp, word);
                            if(!hasBreaked)
                            {
                                outf << '\n';
                                lineCounter = 0;
                            }
                            int i;
                            int j = 0;
                            while(j != strlen(wordTemp))
                            {
                                for(i = 0; i < lineLength; i++)
                                {
                                    if(j < strlen(wordTemp))
                                    {
                                        outf << wordTemp[j];
                                        j++;
                                        lineCounter++;
                                    }
                                }
                                if(j != strlen(wordTemp))
                                {
                                    return1 = true;
                                    outf << '\n';
                                    lineCounter = 0;
                                }
                            }
                        }
                        //if word plus space can fit on line then enter
                        else if(strlen(word) + lineCounter + 1 <= lineLength)
                        {
                            //if not following break
                            if(!hasBreaked)
                            {
                                outf << " ";
                                spaced = true;
                            }
                            //print word
                            outf << word;
                            if(spaced)
                            {
                                lineCounter += strlen(word) + 1;
                            }
                            else
                            {
                                lineCounter += strlen(word);
                            }
                            spaced = false;
                        }
                        //if word plus space can't fit on line then enter
                        else if(strlen(word) + lineCounter + 1 > lineLength)
                        {
                            //if word by itself can fit on line
                            if(strlen(word) <= lineLength)
                            {
                                strcpy(wordTemp, word);
                                if(!hasBreaked)
                                {
                                    outf << '\n';
                                    lineCounter = 0;
                                }
                                int i;
                                for(i = 0; i < strlen(wordTemp); i++)
                                {
                                    outf << wordTemp[i];
                                    lineCounter += 1;
                                }
                            }
                            //if word needs to be split between lines to be fit
                            else if(strlen(word) > lineLength)
                            {
                                return1 = true;
                                strcpy(wordTemp, word);
                                if(!hasBreaked)
                                {
                                    outf << '\n';
                                    lineCounter = 0;
                                }
                                int i;
                                int j = 0;
                                while(j != strlen(wordTemp))
                                {
                                    for(i = 0; i < lineLength; i++)
                                    {
                                        if(j < strlen(wordTemp))
                                        {
                                            outf << wordTemp[j];
                                            j++;
                                            lineCounter++;
                                        }
                                    }
                                    if(j != strlen(wordTemp))
                                    {
                                        outf << '\n';
                                        lineCounter = 0;
                                    }
                                }
                            }
                        }
                    }
                    //if word doesn't equal a break enter
                    if(strcmp(word, paragraphBreak) != 0)
                    {
                        hasBreaked = false;
                    }
                }
            }
            if(hasSpecialCharacter(word))
            {
                charAtEnd = true;
            }
            else
            {
                charAtEnd = false;
            }
            //since strtok cant process two strings at once, if the last word was a hyphen this if statement modifies the orginal line C String by deleting the words before the hyphenated word and reusing strtok with the shifted C String
            if(lastWordHyphen)
            {
                strcpy(shiftLine, lineCopy);
                shiftToHyphen(shiftLine, hyphenCounter);
                word = strtok(shiftLine, " \n\t");
                lastWordHyphen = false;
            }
            word = strtok(nullptr, " \n\t");
        }
    }
    //not empty
    if(notEmpty && !firstBreak)
    {
        outf << '\n';
    }
    //if word portion ever went over line length return 1
    if(return1)
    {
        return 1;
    }
    return 0;
}
//function used to check for special characters at the end such as ., ?, !, :
bool hasSpecialCharacter(char word[])
{
    int latestIndex = 0;;
    for(int i = 0; i < strlen(word); i++)
    {
        //if word has special character at index
        if(word[i] == '.' || word[i] == '?' || word[i] == '!' || word[i] == ':')
        {
            latestIndex = i;
        }
    }
    //if latestindex is the last char of string and it contains special char return true
    if(latestIndex == (strlen(word) - 1) && (word[latestIndex] == '.' || word[latestIndex] == '?' || word[latestIndex] == '!' || word[latestIndex] == ':'))
    {
        return true;
    }
    return false;
}
//function to check if word has a hyphen
bool hasHyphen(char word[])
{
    for(int i = 0; i < strlen(word); i++)
    {
        //if word contains hyphen at index return true
        if(word[i] == '-')
        {
            return true;
        }
    }
    return false;
}
//function used to separate word portions
void separateHyphen(char word[])
{
    char hyphenwords[251];
    int hyphenCounter = 0;
    //counts hyphens in word
    for(int i = 0; i < strlen(word); i++)
    {
        if(word[i] == '-')
        {
            hyphenCounter++;
        }
    }
    int j = 0;
    for(int i = 0; i < (int(strlen(word)) + hyphenCounter); i++)
    {
        //copies words normally from one string to another
        if(word[j] != '-')
        {
            hyphenwords[i] = word[j];
            j++;
        }
        //adds space to separate hyphenated word portions
        else
        {
            hyphenwords[i] = word[j];
            i++;
            j++;
            hyphenwords[i] = ' ';
        }
    }
    //adds null character and copies back to original string
    hyphenwords[int(strlen(word)) + hyphenCounter] = '\0';
    strcpy(word, hyphenwords);
}
//function used to shift hyphen word to first instance in string for strtok to work properly
void shiftToHyphen(char shiftString[], int num)
{
    bool first = false;
    bool second = false;
    int hIndex = -1;
    int hCount = 0;
    //Finds index of hyphen in the string
    for(int i = 0; shiftString[i] != '\0'; i++)
    {
        if(shiftString[i] == '-')
        {
            hCount++;
            if(hCount == num)
            {
                hIndex = i;
                break;
            }
        }
    }
    
    if(hIndex != -1)
    {
        //Finds the start of hyphenated word
        while(hIndex > 0 && shiftString[hIndex] != ' ')
        {
            hIndex--;
        }
        int i = 0;
        //Removes word before hyphen by setting the index accordingly
        if(hIndex > 0 && shiftString[hIndex] == ' ')
        {
            i = hIndex + 1;
            first = true;
        }
        else
        {
            i = hIndex;
            second = true;
        }
        int j = 0;
        //Loops to shift the string to accordingly after removed word
        if(first)
        {
            for(int i = hIndex + 1; shiftString[i] != '\0'; i++)
            {
                shiftString[j] = shiftString[i];
                j++;
            }
        }
        else if(second)
        {
            for(int i = hIndex; shiftString[i] != '\0'; i++)
            {
                shiftString[j] = shiftString[i];
                j++;
            }
        }
        shiftString[j] = '\0';
    }
}
