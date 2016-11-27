#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 26
typedef struct trienode{
	struct trienode *children[MAX];
	bool isleaf;
}trienode;
trienode* get_node(){
	trienode *t=(trienode*)malloc(sizeof(trienode));
	int i;
	for(i=0;i<MAX;i++)
	t->children[i]=NULL;
	t->isleaf=false;
	return t;
}
void insert(trienode* root,char* key){
	int n=strlen(key),i;
	for(i=0;i<n;i++){
		int index=key[i]-'a';
		if(!root->children[index])
		root->children[index]=get_node();
		root=root->children[index];
	}
	root->isleaf=true;
}
bool search(trienode* root,char* key){
	int n=strlen(key),i;
	for(i=0;i<n;i++){
		int index=key[i]-'a';
		if(!root->children[index])
		return false;
		root=root->children[index];
	}
	return (root&&root->isleaf);
}
bool freenode(trienode* r){
	int i;
	for(i=0;i<MAX;i++){
		if(r->children[i])
		return false;
	}
	return true;
}
bool del_key(trienode* root,int i,char* key){
	if(root){
		if(i==strlen(key)){
			if(root->isleaf)
		    root->isleaf=false;
		    if(freenode(root))
		    return true;
		    return false;
	    }
	    else{
		    int index=key[i]-'a';
		    if(del_key(root->children[index],i+1,key)){
			    free(root->children[index]);
		        root->children[index]=NULL;
		        return (!root->isleaf&&freenode(root));
	        }
        }
    }
    return false;
}
int main(){
	char keys[][8]={"she","sells","shore","the","by","sheer"};
	int i;
	trienode* root=get_node();
	for(i=0;i<8;i++)
	insert(root,keys[i]);
	bool x=del_key(root,0,keys[0]);
	printf("%s-deleted\n",keys[0]);
	printf("%s-%s\n","she",search(root,"she")?"present in trie":"not present in trie");
	return 0;
}
