#ifdef LINUX
#include <ncurses.h>
#define OS 0
#else
#include <conio.h>
#define OS 1
#endif

#include <stdio.h>
#include <malloc.h>

char* getInput(int** len){
	/*
	This function reads in input from the command line (in windows) until return key is hit.
	It then changes the given int** len to hold the length of the character array, and also
	returns the character array.

	Call:
	    char* buf;
	    int* len;
	    buf = getInput(&len);
	    printf("Entered %d chars, chars = %s", *len, buf);
	*/
	int i;
	int size;
	int size_adj;
	char* buf;
	char* tmp_buf;

	size = 20;
	size_adj = 5;

	// Allocate memory to buffer
	// Store buffer size
	buf = (char *)malloc(size * sizeof(char));

	i = 0;

	// Windows code
	if (OS == 1){
		printf("Running on Windows\n");
		while ((buf[i++] = _getch()) != '\r'){
			if (i == size){
				// reallocate char.
				tmp_buf = (char *)malloc(size * sizeof(char));
				for (int j = 0; j < i; j++){
					tmp_buf[j] = buf[j];
				}
				free(buf);
				size += size_adj;
				buf = (char *)malloc(size * sizeof(char));
				for (int j = 0; j < i; j++){
					buf[j] = tmp_buf[j];
				}
				free(tmp_buf);
			}
		}
	} else{
		// LINUX code
		printf("Running on LINUX\n");
		while (1){
			buf[i] = getch();
			if (buf[i] == "\n") break;
			i += 1;
			if (i == size){
				// reallocate char.
				tmp_buf = (char *)malloc(size * sizeof(char));
				for (int j = 0; j < i; j++){
					tmp_buf[j] = buf[j];
				}
				free(buf);
				size += size_adj;
				buf = (char *)malloc(size * sizeof(char));
				for (int j = 0; j < i; j++){
					buf[j] = tmp_buf[j];
				}
				free(tmp_buf);
			}
		}
	}

	// Reallocate to only store just the right amount
	size = i - 1;
	buf = realloc(buf, size * sizeof(char));
	buf[size] = '\0';
	
	*len = &size;
	return buf;
}

int main(){
    int* len;
	char* buf;
    buf = getInput(&len);
    printf("Entered %d chars, chars = %s", *len, buf);
	return 0;
}