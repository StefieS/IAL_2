/*
 * Použití binárních vyhledávacích stromů.
 *
 * S využitím Vámi implementovaného binárního vyhledávacího stromu (soubory ../iter/btree.c a ../rec/btree.c)
 * implementujte triviální funkci letter_count. Všimněte si, že výstupní strom může být značně degradovaný 
 * (až na úroveň lineárního seznamu). Jako typ hodnoty v uzlu stromu využijte 'INTEGER'.
 * 
 */

#include "../btree.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Vypočítání frekvence výskytů znaků ve vstupním řetězci.
 * 
 * Funkce inicilializuje strom a následně zjistí počet výskytů znaků a-z (case insensitive), znaku 
 * mezery ' ', a ostatních znaků (ve stromu reprezentováno znakem podtržítka '_'). Výstup je v 
 * uložen ve stromu.
 * 
 * Například pro vstupní řetězec: "abBccc_ 123 *" bude strom po běhu funkce obsahovat:
 * 
 * key | value
 * 'a'     1
 * 'b'     2
 * 'c'     3
 * ' '     2
 * '_'     5
 * 
 * Pro implementaci si můžete v tomto souboru nadefinovat vlastní pomocné funkce.
*/

char toLower(char c) {
    int offset = 32;
    if (c >='A' && c <= 'Z') {
        return c + offset;
    }
    return c;
}

void increment_content(bst_node_content_t *content) {
    int *current_count = (int *)content->value;
    (*current_count)++;
}
bst_node_content_t createContent(int value) {
    bst_node_content_t result = {
    .type = INTEGER,
    .value = malloc(sizeof(int))
  };
  *((int*)(result.value)) = value;
  return result;
}
void letter_count(bst_node_t **tree, char *input) {
    bst_init(tree);
    
    for (int i = 0; input[i] != '\0'; i++) {
        char key;
        
        if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')) {
            key = toLower(input[i]);
        } else if (input[i] == ' ') {
            key = ' ';
        } else {
            key = '_';
        }
        
        bst_node_content_t *content = NULL;
        bool found = bst_search(*tree, key, &content);

        if (found) {

            increment_content(content);
        } else {
            
            bst_insert(tree, key, createContent(1));
        }
    }
}