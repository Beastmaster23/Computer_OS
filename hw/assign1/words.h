#ifndef HEADERFILE_WORDS
#define HEADERFILE_WORDS

char *ReadLineFile(FILE *infile);

char *ReadLine(void);

int count_words(char *str);

int count_words_in_file(char *filename);

#endif