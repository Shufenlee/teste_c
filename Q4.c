#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Check if the first list is exhausted; return 1: exhausted, 0: otherwise

int CheckListExhausted(int* arryFirst, int posFirst, int lenFirst, int* arrySecond, int posSecond, int lenSecond,
                       int** pResult, int* pCount)
{
    int* result = *pResult;

    if (posFirst >= lenFirst)     // if the list is exhausted
    {
        // copy the rest of another list

        if (posSecond < lenSecond)
        {
            for (; posSecond < lenSecond; posSecond++ )
            {
                result[(*pCount)++] = *(arrySecond + posSecond);
            }
        }
        return 1;
    }
    return 0;
}

// Merge arry1 and arry2
//
// pResult: pointer to the result array
// pCount:  pointer to the size of the result array

void Merge2Lists(int* arry1, int len1, int* arry2, int len2, int** pResult, int* pCount)
{
    int pos1 = 0, pos2 = 0;
    int* result = *pResult;
    int value1, value2;

    while (1)
    {
        // first list exhausted
        if (1 == CheckListExhausted(arry1, pos1, len1, arry2, pos2, len2, pResult, pCount))
        {
            break;
        }

        // second list exhausted
        if (1 == CheckListExhausted(arry2, pos2, len2, arry1, pos1, len1, pResult, pCount))
        {
            break;
        }

        value1 = *(arry1 + pos1);   // get element from array 1
        value2 = *(arry2 + pos2);	// get element from array 2

        if (value1 == value2)		// insert elements of both arrays
        {
            pos1++;
            result[(*pCount)++] = value1;
            pos2++;
            result[(*pCount)++] = value2;
        }
        else if (value1 < value2)    // insert element of array 1
        {
            pos1++;
            result[(*pCount)++] = value1;
        }
        else						// insert element of array 2
        {
            pos2++;
            result[(*pCount)++] = value2;
        }
    }
}

struct ListNode
{
    int* array;
    int size;
};

int GetTotalNumOfListArray(struct ListNode** listas, int listasSize)
{
    int num = 0;
    int i = 0;
    struct ListNode* pListas = *listas;

    for (i = 0; i < listasSize; i++)
    {
        num += pListas[i].size;
    }

    return num;
}

// Check if the list size is 0 or 1; return 1: size is 0 or 1, 0: otherwise

int CheckEqualOrLessThan_1_List(int listasSize, struct ListNode* pListas, struct ListNode** ppRes)
{
    struct ListNode* pRes = *ppRes;
    int i = 0;

    if (listasSize == 0)
    {
        pRes->size = 0;
        return 1;
    }

    if (listasSize == 1)
    {
        pRes->size = pListas[0].size;
        pRes->array = malloc(sizeof(int) * pRes->size);
        for (i = 0; i < pRes->size; i++)
        {
            pRes->array[i] = pListas[0].array[i];
        }

        return 1;
    }

    return 0;
}


// ** returned buffer SHOULD be freed !!

struct ListNode* mergeKListas(struct ListNode** listas, int listasSize)
{
    struct ListNode* pListas = *listas;
    int num = GetTotalNumOfListArray(listas, listasSize);

    struct ListNode* pRes = (struct ListNode*)malloc(sizeof(struct ListNode));

    // candidate 1 to merge
    int*  candidate   = malloc(sizeof(int) * num);
    int   count_can   = 0;
    int*  pCandidate  = &candidate[0];
    int** ppCandidate = &pCandidate;

    // merging result
    int*  result    = malloc(sizeof(int) * num);
    int   count_res = 0;
    int*  pResult   = &result[0];
    int** ppResult  = &pResult;

    int i = 0, j = 0;

    // check list size
    if (1 == CheckEqualOrLessThan_1_List(listasSize, pListas, &pRes))
    {
        return pRes;
    }

    // init candidate 1 as the first list
    count_can = pListas[0].size;
    for (i = 0; i < count_can; i++)
    {
        candidate[i] = pListas[0].array[i];
    }

    // start to merge
    for (i = 1; i < listasSize; i++)
    {
        Merge2Lists(candidate, count_can, pListas[i].array, pListas[i].size, ppResult, &count_res);

        // copy the result to candidate
        if (i != listasSize - 1)
        {
            count_can = count_res;
            count_res = 0;

            for (j = 0; j < count_can; j++)
            {
                candidate[j] = result[j];
            }
        }
    }

    // **** need to free the memory

    pRes->size = count_res;
    pRes->array = malloc(sizeof(int) * pRes->size);

    for (i = 0; i < pRes->size; i++)
    {
        pRes->array[i] = result[i];
    }

    free(candidate);
    free(result);

    return pRes;
}

void printList(struct ListNode* pList)
{
    int i = 0;

    printf("[");

    for (i = 0; i < pList->size; i++)
    {
        printf("%d", pList->array[i]);

        if (i != pList->size - 1)
        {
            printf(", ");
        }
    }

    printf("]");
}

// Take out the out most brace
// [[1,3,8],[1,3,6],[8,9]] -> [1,3,8],[1,3,6],[8,9]

char* RemoveOutMostBrace(char* str)
{
    char* pRet;

    char* s1 = strchr(str, '[');
    char* s2 = strrchr(str, ']');
    int len = (s2 - s1) - 1;   // len: after remove first '[' and last ']'

    // ** need to free memory
    pRet = malloc(sizeof(char) * (len + 1));
    memcpy(pRet, &s1[1], len);
    pRet[len] = 0x00;

    return pRet;
}

// Get the list string
// [[1,3,8],[1,3,6],[8,9]] -> 1,3,8
//                         -> 1,3,6
//                         -> 8,9

char* GetOneListString(char* str, int* nextPos)
{
    char* pRet;
    char* s1;
    char* s2;
    int len;

    s1 = strchr(str, '[');
    if (s1 == 0)
    {
        return 0;
    }

    s2 = strchr(str, ']');
    len = (s2 - s1) - 1;

    *nextPos = (s2 - str) + 1;

    // ** need to free memory
    pRet = malloc(sizeof(char) * (len + 1));
    memcpy(pRet, &s1[1], len);
    pRet[len] = 0x00;

    return pRet;
}

// By counting "[" - 1
int GetListNumFromString(char* str)
{
    int i = 0;
    int count = 0;
    for (i = 0; i < strlen(str) - 1; i++)
    {
        if (str[i] == '[')
        {
            count++;
        }
    }

    if (count > 2)
    {
        return count - 1;
    }

    return 0;
}

// By counting "," + 1
int GetListItemCount(char* str)
{
    int i = 0;
    int count = 0;
    for (i = 0; i < strlen(str) - 1; i++)
    {
        if (str[i] == ',')
        {
            count++;
        }
    }

    if (count >= 1)
    {
        return count + 1;
    }

    return 0;
}

void PushEachListToArray(char* sList, struct ListNode** ppList, int* pCount)
{
    struct ListNode* pList = *ppList;
    int count = GetListItemCount(sList);
    int i = 0;
    char* token;

    pList[*pCount - 1].size = count;
    pList[*pCount - 1].array = malloc(sizeof(int) * count);

    token = strtok(sList, ",");
    while( token != 0 )
    {
        pList[*pCount - 1].array[i++] = atoi(token);
        token = strtok(NULL, ",");
    }
}

void Parse(char* str, struct ListNode** ppList)
{
    int startPt = 0;
    int pos = 0;
    char* s = RemoveOutMostBrace(str);
    int count = 0;

    while (1)
    {
        char* sList = GetOneListString(&s[startPt], &pos);
        if (sList == 0)
        {
            break;
        }

        count++;
        PushEachListToArray(sList, ppList, &count);

        startPt += pos;
        free (sList);
    }

    free(s);
}

int main()
{

    char* str = "[[1,3,8],[1,3,6],[8,9]]";
    //char* str = "[ [ ] ]";
    //char* str = "[ ]";

    struct ListNode* plist = 0;
    struct ListNode* pRes;
    int i = 0;

    int listCount = GetListNumFromString(str);

	if (listCount != 0)
	{
		plist = malloc(sizeof(struct ListNode) * listCount);
		Parse(str, &plist);
	}

    pRes = mergeKListas(&plist, listCount);
    printList(pRes);

	// clean up

    if (pRes->size != 0)
    {
        free(pRes->array);
    }

	for (i = 0; i < listCount; i++)
	{
		if (plist[i].size != 0)
		{
			free (plist[i].array);
		}
	}

	if (plist != 0)
	{
		free (plist);
	}

    return 0;
}
