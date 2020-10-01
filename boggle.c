//Atandra Mahalder
//07/18/2020
//Rudimentary word-finding program which finds total words in a 4x4 grid based on a pre-fed dictionary
//Dictionary is a file with a number n on top representing number of words, followed by n space seperated strings

#include<stdio.h>
#include<stdlib.h>

typedef struct trie_node{
 int isWord, numWords;
 struct trie_node *nextletter[26];
}trie_node;

trie_node *new_node(){
 trie_node *new_trie = malloc(sizeof(trie_node));
 new_trie->isWord = 0;
 new_trie->numWords = 0;
 for(int i=0;i<26;++i) new_trie->nextletter[i] = NULL;
 return new_trie;
}

trie_node *insert(trie_node* root, char *word){
 if(!root) root = new_node();
 if(word[0]=='\0'){
    root->isWord = 1;
    return root;
 }
 root->nextletter[word[0]-'a'] = insert(root->nextletter[word[0]-'a'], word+1);
 root->numWords++;
 return root;
}

int check(trie_node *root, char *word){
 if(!root) return 0;
 if(word[0]=='\0'){
    if(root->isWord) return 1;
    else return 0;
 }
 return check(root->nextletter[word[0]-'a'], word+1);
}

void destroy(trie_node *root){
 if(root){
    for(int i=0;i<26;++i) destroy(root->nextletter[i]);
    free(root);
 }
}

int prefix(trie_node *root, char *word){
 if(!root) return 0;
 if(word[0]=='\0') return root->numWords;
 return prefix(root->nextletter[word[0]-'a'], word+1);
}
void print(trie_node *root, char *word, int k){
 if(!root) return;
 if(root->isWord){
    word[k]='\0';
    printf("%s\n", word);
 }
 for(int i=0;i<26;++i){
    word[k] = (char)('a'+i);
    print(root->nextletter[i], word, k+1);
 }
}

trie_node *dict = NULL;
int used[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
char grid[4][4];

void find_words(int i, int j, char *word, int k){
 word[k] = grid[i][j];
 word[k+1] = '\0';
 used[i][j] = 1;
 if(check(dict, word) && k>=2){
     printf("%s\n", word);
 }
 int dx[] = {-1,0,1};
 int dy[] = {-1,0,1};
 if(prefix(dict, word)){
     for(int x=0;x<3;++x)
         for(int y=0;y<3;++y)
             if(i+dx[x]>=0 && i+dx[x]<4 && j+dy[y]>=0 && j+dy[y]<4 && !used[i+dx[x]][j+dy[y]]){
                 find_words(i+dx[x], j+dy[y], word, k+1);
             }
 }
 used[i][j]=0;
}

int main(){
 //feed dictionary into the system
 FILE *fptr = fopen("dictionary.txt", "r");
 int n; fscanf(fptr, "%d", &n);
 char word[17];
 for(int i=0;i<n;++i){
    fscanf(fptr, "%s", word);
    dict = insert(dict, word);
 }
 fclose(fptr);
 
 //Enter number of games
 scanf("%d", &n);
 for(int t=1;t<=n;++t){
    
    //enter description of the game (4x4 grid of words, not space seperated)
    for(int i=0;i<4;++i){
        scanf(" ");
        for(int j=0;j<4;++j) scanf("%c", &grid[i][j]);
    }

    //print out total words found in the grid for this game 	
    printf("Words for Game #%d:\n", t);
    for(int i=0;i<4;++i) for(int j=0;j<4;++j) find_words(i, j, word, 0);
    printf("\n");
 }

 destroy(dict);
 return 0;
}
