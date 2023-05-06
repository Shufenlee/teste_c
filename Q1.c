#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Get sub-string by its starting position

char* GetSubStringByPos(char* str, int startPos)
{
    return str += startPos;
}

// Check if the string reversable; return 1: reversable, 0: otherwise

int Reversable(char* str, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        char a = *(str + i);    // start from left
        char b = *(str + (len - 1) - i);   // start from right

        if (a != b)
        {
            return 0;
        }
    }

    return 1;
}

// Print the result string

void printResult(char* str, int pos, int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
    {
        char c = *(str + pos + i);
        printf("%c", c);
    }
	printf("\n");
}

// Get Maximum reversable sub-string; return the length of the sub-string
//
//		str:      the testing string
//      len:      the length of the testing string
//		pStartPt: the starting position of the result string

int GetMaxReverseSubStr(char* str, int len, int* pStartPt)
{
    int j = len;
    for (j = len; j > 1; j--)   // try to get the length as longer as possible
    {
        int i = 0;
        for (i = 0; i + j <= len; i++)     // move the starting position
        {
            char* substr = GetSubStringByPos(str, i);
            int b = Reversable(substr, j);

            if (b == 1)
            {
                *pStartPt = i;
                return j;
            }
        }
    }
    return 0;

}

int ProcessFile(char* filename)
{
    FILE* fp;
	int line_size = 1024;
	char* line = malloc(line_size);

    fp = fopen("strings_01.txt", "r");
    if (!fp)
	{ 
		return 0;
	}

	while (fgets(line, line_size, fp) != 0)  
	{
		int startPt = 0;
		int len = GetMaxReverseSubStr(line, strlen(line), &startPt);
		printResult(line, startPt, len);
	}

	free(line); 
    fclose(fp);

	return 1;
}

int main()
{
	char* filename = "strings_01.txt";
	ProcessFile(filename);
    return 0;
}
