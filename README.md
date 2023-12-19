An implementation of a text render function that takes three arguments an and outputs a rendered body of text. Input lines must be limited to 250 characters for the function to work properly. 

**The parameters for the function are:**
 
  - an int with the desired maximum line length

  - an already-opened input source will be read from

  - an already-opened output destination which will be written to

**Sample call of the function render:**

  - int render(int lineLength, istream& inf, ostream& outf);

  - Returns if 0 rendering is successful

  - Returns 1 if any input word portion (defined below) is longer than the maximum line length 

  - Returns 2 if the desired maximum line length is less than 1

**Rendering Rules that the function conforms to when processing text**

  - A word is a sequence of non-whitespace characters not immediately preceded or followed by a non-whitespace character.

  - A word can be viewed as a sequence of one or more word portions. The first word portion in a word starts at the start of the word; subsequent word portions in a word start just after the last character of the previous word portion. The last character of a word portion is the first hyphen at or after the start of that word portion, or the end of the word if there is no hyphen after the start of that word portion.

1. Word portions will be maximized to fit on an output line, giving “ragged-right” effect

2. Words in an output line are normally separated by one blank. However, if the last character of an output word is a period, question mark, exclamation point, or colon, it is separated from any following word on that output line by two blanks. The last word on an output line is not followed by any blanks. The first word portion on an output line is not be preceded by any blanks. Blanks do not appear on an output line within any word. The last line of output ends with a newline, and there are no output lines (not even empty ones) after the last word of the last paragraph. For example, if the last word in the input is bye, then the last four characters the function will write are 'b'  'y'  'e'  '\n'. That does not produce an empty last line.

3. If a word portion is longer than the line length, as much as will fit will be on an output line by itself. The rest of that word portion will begin the next output line (and, of course, is subject to similar splitting if it's too long). If this situation ever occurs, the function continues rendering, but it eventually returns 1 instead of 0 to the caller. Notice that this is the only situation where a word is can be split across lines other than at a hyphen.

4. The input word @P@ is not processed as a word according to the above rules; instead, it indicates a paragraph break. The first word in the input following a paragraph break is the first word of a new paragraph in the output. If a paragraph has already been output, the new paragraph is separated from the one that precedes it by an empty line (i.e., a line with no characters other than the terminating newline). The very first output paragraph is never preceded by an empty line. The very last output paragraph is never followed by an empty line. Two or more consecutive @P@ words in the input are treated as just one paragraph break.

5. If no words are found in the input then 0 is returned to the caller

**This program is intentionally written without the use of any std::string objects**

**This Project Was Created as a Project for CS 31 at UCLA During the Fall 2023 Quarter**
