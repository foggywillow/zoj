#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
	char s[4100];
	int line;
	int offset;
	int i;
	int l = 0;
	char c;

	while (gets(s)) {
		offset = 0;
		line = strlen(s) / 16 + (strlen(s) % 16 == 0? 0:1);
		for (l = 0; l < line - 1; ++l) {
			printf("%04x: ", l<<4);
			for (i = offset; i < offset + 16; ++i) {
				c = s[i];
				if (isupper(c))
					s[i] = tolower(c);
				else if (islower(c))
					s[i] = toupper(c);
				printf("%2x",c);
				if (i % 2)
					printf(" ");
			}
			for (i = offset; i < offset + 16; ++i)
				printf("%c",s[i]);

			offset += 16;
			printf("\n");
		}

		printf("%04x: ", l<<4);
		for (i = offset; i < offset + 16; ++i){
			if (i < strlen(s)) {
				c = s[i];
				if (isupper(c))
					s[i] = tolower(c);
				else if (islower(c))
					s[i] = toupper(c);
				printf("%2x",c);
			}
			else {
				printf("  ");
			}

			if (i % 2)
				printf(" ");			
		}
		for (i = offset; i < strlen(s); ++i)
			printf("%c",s[i]);
		printf("\n");
	}

	return 0;
}