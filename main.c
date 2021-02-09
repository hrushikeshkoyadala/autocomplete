#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INDEX(c) ((int)c - 97)

typedef struct node
{
    struct node *children[26];
    char is_end;
} node;

node* new_node()
{
    node *to_return = (node *)malloc(sizeof(node));
    
    for (int i = 0; i < 26; i++)
        to_return->children[i] = NULL;
    to_return->is_end = '\0';

    return to_return;
}

void insert_word(node *at_tree, char *word)
{
    node *current = at_tree;
    while (*word)
    {
        if (current->children[INDEX(*word)] == NULL)
            current->children[INDEX(*word)] = new_node();
    
        current = current->children[INDEX(*word)];
        word++;
    }
    current->is_end = '1';
}

void dfs_print(node *n, char *prefix, int prefix_index)
{
    printf("!!  %s   !!\n", prefix);
    if (n->is_end)
        printf("%s\n", prefix);

    for (int i = 0; i < 26; i++)
    {
        if (n->children[i] != NULL)
        {
            prefix[prefix_index++] = (char)(i + 97);
            dfs_print(n->children[i], prefix, prefix_index);
        }
    }
}


void print_suggestions(node *at_tree, char *word)
{
    if (at_tree->children[INDEX(*word)] == NULL)
        return;

    char prefix[50];
    memset(prefix, 0, sizeof(char) * 50);
    int prefix_index = 0;

    while (*word && at_tree->children[INDEX(*word)] != NULL)
    {  
        prefix[prefix_index++] = *word;
        at_tree = at_tree->children[INDEX(*word)];
        word++;
    }

    if (*word)
        return;

    dfs_print(at_tree, prefix, prefix_index);
}

node* gen_at_tree(FILE *vocabulary)
{
    char word[50];
    memset(word, 0, sizeof(char) * 50);
    node *root = new_node();

    while ((fscanf(vocabulary, "%s", word)) != EOF)
    {
        insert_word(root, word);
    }

    return root;
}

int main()
{
    FILE *vocabulary = fopen("/Users/hrushi/Desktop/Programs/autocomplete/words.txt", "r");
    node *tree = gen_at_tree(vocabulary);
    print_suggestions(tree, "p");
    fclose(vocabulary);
    return 0;
}