//Atandra Mahalder
//07/29/2020
//Rudimentary text predictor which predicts the next letter of a 
//partially typed word based on frequency of the prefix seen

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
 int freq;
 int prefix;
 int next_max[26];
 struct node *letters[26];
}node;

node *create(){
 node *newnode = malloc(sizeof(node));
 newnode->prefix = 0;
 newnode->freq = 0;
 for(int i=0;i<26;++i){
    newnode->next_max[i] = 0;
    newnode->letters[i] = NULL;
 }
 return newnode;
}

node *insert(node *root, char *word, int f){
 if(!root) root = create();
 if(!word[0]){
    root->freq+=f;
    return root;
 }
 root->prefix = 1;
 root->next_max[word[0]-'a']+=f;
 root->letters[word[0]-'a'] = insert(root->letters[word[0]-'a'], word+1, f);
 return root;
}

char *search(node *root, char *word){
 if(!root) return NULL;
 if(!word[0]){
    if(root->prefix){
        int k=1, m=0;
        char *s = calloc(27, sizeof(char));
        s[0]='a';
        for(int i=1;i<26;++i){
            if(root->next_max[i]==root->next_max[m]) s[k++] = 'a'+i;
            else if(root->next_max[i]>root->next_max[m]){
                s[0] = 'a'+i;
                k=1;
                m=i;
            }
        }
        s[k]='\0';
        return s;
    }else return NULL;
 }
 return search(root->letters[word[0]-'a'], word+1);
}

void destroy(node *root){
 if(root){
    for(int i=0;i<26;++i) destroy(root->letters[i]);
    free(root);
 }
}

int main(){
 node *dict = NULL;
 int n, c; scanf("%d", &n);
 char *word = calloc(2000001, sizeof(char));
 while(n--){
    //entering system command, 1 to enter word in the system and 2 to predict the next possible letter in a prefix
    //in case of 1 enter the word followed by frequency
    //in case of 2, just enter the prefix		
    scanf("%d", &c); 	 
    if(c==1){
        scanf("%s", word);
        int f; scanf("%d", &f);
        dict = insert(dict, word, f);
    }else{  
        scanf("%s", word);
        char *s = search(dict, word);
        if(s){
            printf("%s\n", s);
            free(s);
        }else printf("unknown word\n");
    }
 }
 free(word);
 destroy(dict);
 return 0;
}
