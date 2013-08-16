#include <stdio.h>
#include <string.h>

char dict[10000][16];
char word[50][16];

int is_match(char dict[][16], int len, char *word)
{
	int i;
	for(i = 0; i < len; ++i) {
		if (strcmp(word, dict[i]) == 0) {
			printf("%s is correct\n", word);
			return 1;
		}
	}
	//  printf("%s:\n",word);
	return 0;
}

int is_delete_match(char dict[][16], int len, char *word)
{
	int i, count,k, flag;
	char *pdict, *pword;
	for(i = 0; i < len; ++i) {
		count = 0;
		if ( 1 == (strlen(word) - strlen(dict[i])) ){
			for(pdict=dict[i], pword=word; *pdict != '\0'; ++pdict, ++pword) {
				if (*pdict != *pword) {
					pword++;
					count++;
					k = i;
					if (*pdict != *pword) {
						count++;
						break;
					}
				}
				if (count == 0)
					k = i;
			}
			if (count <= 1) {
				printf("%s: %s\n", word, dict[k]);
				return 1;
			}
		}
	} 
	//   printf("%s:\n", word);
	return 0;
}

int is_replace_match(char dict[][16], int len, char *word)
{
	int i, count;
	char *pdict, *pword;
	for(i = 0; i < len; ++i) {
		count = 0;
		if ( 0 == (strlen(word) - strlen(dict[i])) ){
			for(pdict=dict[i], pword=word; *pdict != '\0'; ++pdict, ++pword) {
				if (*pdict != *pword) {
					count++;
				}
				if(count > 1)
					break;
			}
			if(count == 1) {
				printf("%s: %s\n", word, dict[i]); 
				return 1;
			}
		}
	} 
	//printf("%s:\n", word);
	return 0;
}

int is_add_match(char dict[][16], int len, char *word)
{
	int i, count,k, flag;
	char *pdict, *pword;
	for(i = 0; i < len; ++i) {
		count = 0;
		if ( 1 == ( strlen(dict[i]) - strlen(word) ) ){
			for(pdict=dict[i], pword=word; *pdict != '\0'; ++pdict, ++pword) {
				if (*pdict != *pword) {
					pdict++;
					count++;
					k = i;
					if (*pdict != *pword) {
						count++;
						break;
					}
				}
				if (count == 0)
					k = i;
			}
			if (count <= 1) {
				printf("%s: %s\n", word, dict[k]);
				return 1;
			}
		}
	} 
	//  printf("%s:\n", word);
	return 0;
}

int main()
{
	int dict_size, word_size;
	int i = 0;
	while (1) {
		scanf("%s", dict[i]);
		if (strcmp(dict[i], "#") == 0)
			break;
		i++;
	}
	dict_size = i - 1;
	i = 0;
	while(1) {
		scanf("%s", word[i]);
		if(strcmp(word[i], "#") == 0)
			break;
		i++;
	}
	word_size = i - 1;

	for (i = 0; i < word_size; ++i) {
		if (is_match(dict,dict_size,word[i]) == 1)
			continue;
		else if (is_replace_match(dict, dict_size, word[i]) == 1)
			continue;
		else if (is_delete_match(dict,dict_size,word[i]) == 1)
			continue;
		else if (is_add_match(dict,dict_size,word[i]) == 1)
			continue;
		else
			printf("%s:\n", word);
	}
	return 0;
}

