#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Trie {
    int count;
    struct Trie *children[26];
};

struct Trie* createTrie();

void insert(struct Trie *pTrie, char *word){
    if (pTrie == NULL || word == NULL){
        return;
    }
        
    struct Trie* curr = malloc(sizeof(struct Trie));
    curr = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL){
            curr->children[index] = createTrie();
        }
        curr = curr->children[index];
    }

    curr->count++;

}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    }
    struct Trie *curr = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

struct Trie *createTrie()
{
    struct Trie *newTrie = malloc(sizeof(struct Trie));

    return newTrie;

}
// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    
    FILE* inFile = fopen(filename, "r");
    if (inFile == NULL){
        return -1;
    }
    int numWords = 0;
    
    char word[256];

        while (fscanf(inFile, "%s", word) != EOF && numWords < 256)
		{
            
			pInWords[numWords] = malloc(sizeof(char) * strlen(word) +1);
            //printf("%s ", word);
			strcpy(pInWords[numWords], word);
            //printf("%s ", pInWords[i]);
            numWords++;
		}
        /*for (i = 0; i < numWords; i++){
            printf("%s ", pInWords[i]);
        }*/
        

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