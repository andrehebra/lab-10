#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Trie structure
struct Trie
{	
    int flag;
    struct Trie* next[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *pTrie = malloc(sizeof(struct Trie));

    for (int i = 0; i < 26; i++) {
        pTrie->next[i] = NULL;
    }

	pTrie->flag = 0;

    return pTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{

    int currentChar;

    while (*word != '\0') {

        currentChar = *word;

		if (pTrie->next[*word - 65] == NULL) {
			struct Trie *newTrie = createTrie();
			pTrie->next[*word - 65] = newTrie;
			pTrie = pTrie->next[*word - 65];
		} else {
			pTrie = pTrie->next[*word - 65];
		}

        word++;
    }

	pTrie->flag += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	int count = 0;

	while (*word != '\0') {

		if (pTrie == NULL) {
			return 0;
		}

		pTrie = pTrie->next[*word - 65];

		word++;
	}
	

	count = pTrie->flag;

	return count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	if (pTrie == NULL) {
		return NULL;
	}

	for (int i = 0; i < 26; i++) {
		deallocateTrie(pTrie->next[i]);
	}

	free(pTrie);

	return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{

    FILE *f = fopen(filename, "r");

	int numWords;

	fscanf(f, "%d", &numWords);

	
	char *tempPtr = *pInWords;
	char wordHolder[1000];
	int wordLength;

	for (int i = 0; i < numWords; i++) {

		
		fscanf(f, "%s", wordHolder);
		wordLength = strlen(wordHolder);

		char *tempHolder = malloc(sizeof(char) * wordLength + 1);

		strcpy(tempHolder, wordHolder);

		tempPtr = tempHolder;

		pInWords[i] = tempPtr;

		tempPtr++;
		
	}
	

	return numWords;

}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}