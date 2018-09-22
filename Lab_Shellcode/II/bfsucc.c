#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool IsPasswordValid(void);
int main(void) {
    bool PWverify;

	puts("Enter your password:");
	PWverify = IsPasswordValid();
	if (!PWverify) {
		puts("Wrong!! Wrong!! Wrong!!");
		return -1;
	}
	else {
        puts("Welcome. Your password is correct.");
        system("gedit");
	}
	return 0;
}

bool IsPasswordValid(void) {
	char Password[12];

	gets(Password);
	if (!strcmp(Password, "secure pro"))
		return(true);
	else return(false);
}
