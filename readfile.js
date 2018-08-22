#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2) {
		fprintf(stderr, "Provide a file to read! USAGE: ./readfile filename\n");
		exit(1);
	}

	// get a pointer to the filename
	FILE *fp;
	char line[2000];

	// you are going to open the file using fopen()
	if((fp = fopen(argv[1], "r")) == NULL){
		// something wrong so we tell the user
		fprintf(stderr, "We can not open the \n");
		exit(2);
	}
	// loop through the file reading the contents using fgets
	while(fgets(line, sizeof line, fp) != NULL){
		char *endchar;

		unsigned char opcode = strtol(line, &endchar, 2);

		// ignore empty lines
		if(endchar == line) {
			continue;
		}

		printf("%u\n", opcode);
	}

	return 0;
}
