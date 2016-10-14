

#ifndef ERRORCHECK_H
#define ERRORCHECK_H

//returns the length of a c_string minus the NULL char
int str_len(char *);

//returns false at the first instance of a char that is not 0 - 9
bool is_num(char *);

bool is_1_2(char *);
bool is_1_3(char *);
bool is_1_4(char *);

#endif