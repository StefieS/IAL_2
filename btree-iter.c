/*
 * Binární vyhledávací strom — iterativní varianta
 *
 * S využitím datových typů ze souboru btree.h, zásobníku ze souboru stack.h
 * a připravených koster funkcí implementujte binární vyhledávací
 * strom bez použití rekurze.
 */

#include "../btree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializace stromu.
 *
 * Uživatel musí zajistit, že inicializace se nebude opakovaně volat nad
 * inicializovaným stromem. V opačném případě může dojít k úniku paměti (memory
 * leak). Protože neinicializovaný ukazatel má nedefinovanou hodnotu, není
 * možné toto detekovat ve funkci.b
 */
void bst_init(bst_node_t **tree)
{
  *tree = NULL;
}

/*
 * Vyhledání uzlu v stromu.
 *
 * V případě úspěchu vrátí funkce hodnotu true a do proměnné value zapíše
 * ukazatel na obsah daného uzlu. V opačném případě funkce vrátí hodnotu false a proměnná
 * value zůstává nezměněná.
 *
 * Funkci implementujte iterativně bez použité vlastních pomocných funkcí.
 */
bool bst_search(bst_node_t *tree, char key, bst_node_content_t **value)
{
    bst_node_t * buffer = tree;
    while(buffer != NULL ) {
      if (buffer->key == (int) key) {
        *value = &buffer->content;
         return true;
      }
      else if (buffer->key <key) {
        buffer = buffer->right;
      }
      else {
        buffer = buffer->left;
      }
    }
    return false;
 
}

/*
 * Vložení uzlu do stromu.
 *
 * Pokud uzel se zadaným klíče už ve stromu existuje, nahraďte jeho hodnotu.
 * Jinak vložte nový listový uzel.
 *
 * Výsledný strom musí splňovat podmínku vyhledávacího stromu — levý podstrom
 * uzlu obsahuje jenom menší klíče, pravý větší.
 *
 * Funkci implementujte iterativně bez použití vlastních pomocných funkcí.
 */
void bst_insert(bst_node_t **tree, char key, bst_node_content_t value)
{
    bst_node_t *current = *tree;
    bst_node_t *previous = NULL;
    while(current != NULL) {
      previous = current;
      if (current->key == (int) key) {
        if(current->content.value != NULL) {
        free((*tree)->content.value);
        }
        current->content = value;
        return;
      }
      else if (current->key < key) {
        current = current->right;
      }
      else {
        current = current->left;
      }
    }
    bst_node_t *new = (bst_node_t *)malloc(sizeof(bst_node_t));
    new->key =(int) key;
    new->content = value;
    new->left = NULL;
    new->right = NULL;

    if (previous == NULL) {
      *tree = new;
      return;
    }
    if (previous->key < new->key) {
      previous->right = new;
      return;
    }
    else {
      previous->left = new;
      return;
    }
}

/*
 * Pomocná funkce která nahradí uzel nejpravějším potomkem.
 *
 * Klíč a hodnota uzlu target budou nahrazené klíčem a hodnotou nejpravějšího
 * uzlu podstromu tree. Nejpravější potomek bude odstraněný. Funkce korektně
 * uvolní všechny alokované zdroje odstraněného uzlu.
 *
 * Funkce předpokládá, že hodnota tree není NULL.
 *
 * Tato pomocná funkce bude využita při implementaci funkce bst_delete.
 *
 * Funkci implementujte iterativně bez použití vlastních pomocných funkcí.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree)
{
  bst_node_t *current = *tree;
  bst_node_t *previous = NULL;
  while(current->right != NULL) {
    previous = current;
    current = current->right;
  }
  target->key = current->key;
  if (target->content.value != NULL) {
    free(target->content.value);
  }
  target->content = current->content;
  if (previous == NULL) {
    *tree = current->left;
  }
  else {
    previous->right = current->left;
  }
  free(current);
  
}

/*
 * Odstranění uzlu ze stromu.
 *
 * Pokud uzel se zadaným klíčem neexistuje, funkce nic nedělá.
 * Pokud má odstraněný uzel jeden podstrom, zdědí ho rodič odstraněného uzlu.
 * Pokud má odstraněný uzel oba podstromy, je nahrazený nejpravějším uzlem
 * levého podstromu. Nejpravější uzel nemusí být listem.
 *
 * Funkce korektně uvolní všechny alokované zdroje odstraněného uzlu.
 *
 * Funkci implementujte iterativně pomocí bst_replace_by_rightmost a bez
 * použití vlastních pomocných funkcí.
 */
void bst_delete(bst_node_t **tree, char key)
{
    bst_node_t *current = *tree;
    bst_node_t *previous = NULL;

    while (current != NULL && current->key != (int) key) {
        previous = current;
        if (current->key < (int)key) {
            current = current->right;
        } else {
            current = current->left;
        }
    }

    if (current == NULL) return;

    if (current->left == NULL && current->right == NULL) {
        if (previous == NULL) {  
            *tree = NULL;
        } else if (previous->left == current) {
            previous->left = NULL;
        } else {
            previous->right = NULL;
        }
        
        if (current->content.value != NULL) {
            free(current->content.value);
        }
        free(current);
        return;
    }

    
    if (current->left != NULL && current->right != NULL) {
        bst_replace_by_rightmost(current, &current->left);
    }
    else {
        bst_node_t *rightleft = (current->right == NULL) ? current->left : current->right;

        if (previous == NULL) {  
            *tree = rightleft;
        } else if (previous->left == current) {
            previous->left = rightleft;
          
        } else {
            previous->right = rightleft;
        }
        
        
        if (current->content.value != NULL) {
            free(current->content.value);
        }
        free(current);
        
    }
}


/*
 * Zrušení celého stromu.
 *
 * Po zrušení se celý strom bude nacházet ve stejném stavu jako po
 * inicializaci. Funkce korektně uvolní všechny alokované zdroje rušených
 * uzlů.
 *
 * Funkci implementujte iterativně s pomocí zásobníku a bez použití
 * vlastních pomocných funkcí.
 */
void bst_dispose(bst_node_t **tree)
{
  stack_bst_t stack;
  stack_bst_init(&stack);
  do {
    if (*tree == NULL) {
      if(!stack_bst_empty(&stack)) {
          *tree = stack_bst_top(&stack);
          stack_bst_pop(&stack);
      }
    }
    else {
      if ((*tree)->right != NULL) {
        stack_bst_push(&stack, (*tree)->right);
      }
      bst_node_t *buffer = *tree;
      *tree = (*tree)->left;
      if (buffer->content.value != NULL) {
        free(buffer->content.value);
      }
      free(buffer);
    }
  } while ((*tree != NULL) || (!stack_bst_empty(&stack)));
}

/*
 * Pomocná funkce pro iterativní preorder.
 *
 * Prochází po levé větvi k nejlevějšímu uzlu podstromu.
 * Nad zpracovanými uzly zavolá bst_add_node_to_items a uloží je do zásobníku uzlů.
 *
 * Funkci implementujte iterativně s pomocí zásobníku a bez použití
 * vlastních pomocných funkcí.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit, bst_items_t *items)
{
  while(tree != NULL) {
    stack_bst_push(to_visit, tree);
    bst_add_node_to_items(tree, items);
    tree = tree->left;
  }
}

/*
 * Preorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte iterativně pomocí funkce bst_leftmost_preorder a
 * zásobníku uzlů a bez použití vlastních pomocných funkcí.
 */
void bst_preorder(bst_node_t *tree, bst_items_t *items)
{
  stack_bst_t stack;
  stack_bst_init(&stack);
  bst_leftmost_preorder(tree, &stack, items);
  while (!stack_bst_empty(&stack)) {
    tree = stack_bst_top(&stack);
    stack_bst_pop(&stack);
    bst_leftmost_preorder(tree->right,&stack, items);
  }
}

/*
 * Pomocná funkce pro iterativní inorder.
 *
 * Prochází po levé větvi k nejlevějšímu uzlu podstromu a ukládá uzly do
 * zásobníku uzlů.
 *
 * Funkci implementujte iterativně s pomocí zásobníku a bez použití
 * vlastních pomocných funkcí.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit)
{
  
  while(tree != NULL) {
    stack_bst_push(to_visit, tree);
    tree = tree->left;
  }
}

/*
 * Inorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte iterativně pomocí funkce bst_leftmost_inorder a
 * zásobníku uzlů a bez použití vlastních pomocných funkcí.
 */
void bst_inorder(bst_node_t *tree, bst_items_t *items)
{
  stack_bst_t stack;
  stack_bst_init(&stack);
  bst_leftmost_inorder(tree, &stack);
  while(!stack_bst_empty(&stack)) {
    tree = stack_bst_top(&stack);
    stack_bst_pop(&stack);
    bst_add_node_to_items(tree, items);
    bst_leftmost_inorder(tree->right,&stack);
  }
}

/*
 * Pomocná funkce pro iterativní postorder.
 *
 * Prochází po levé větvi k nejlevějšímu uzlu podstromu a ukládá uzly do
 * zásobníku uzlů. Do zásobníku bool hodnot ukládá informaci, že uzel
 * byl navštíven poprvé.
 *
 * Funkci implementujte iterativně pomocí zásobníku uzlů a bool hodnot a bez použití
 * vlastních pomocných funkcí.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit,
                            stack_bool_t *first_visit)
{
  while(tree != NULL) {
    stack_bst_push(to_visit, tree);
    stack_bool_push(first_visit,true);
    tree = tree->left;
  }
}

/*
 * Postorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte iterativně pomocí funkce bst_leftmost_postorder a
 * zásobníku uzlů a bool hodnot a bez použití vlastních pomocných funkcí.
 */
void bst_postorder(bst_node_t *tree, bst_items_t *items)
{
  bool fromLeft = true;
  stack_bst_t stack;
  stack_bst_init(&stack);
  stack_bool_t boolStack;
  stack_bool_init(&boolStack);
  bst_leftmost_postorder(tree, &stack, &boolStack);
  while(!stack_bst_empty(&stack)) {
    tree = stack_bst_top(&stack);
    fromLeft = stack_bool_top(&boolStack);
    stack_bool_pop(&boolStack);
    if (fromLeft) {
      stack_bool_push(&boolStack, false);
      bst_leftmost_postorder(tree->right, &stack, &boolStack);
    }
    else {
      stack_bst_pop(&stack);     
      bst_add_node_to_items(tree, items);
    }
  }
} 
