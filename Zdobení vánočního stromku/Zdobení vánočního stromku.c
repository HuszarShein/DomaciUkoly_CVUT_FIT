#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_BRANCHES             3
#define DECORATION_NONE          0
#define DECORATION_CANDLE        1
#define DECORATION_SPARKLER      2

typedef struct TNode {
  struct TNode* m_Parent;
  struct TNode* m_Branches[MAX_BRANCHES];
  int m_Decoration;
} TNODE;
#endif /* __PROGTEST__ */

TNODE* newNode(TNODE* parent) {
    TNODE* node = (TNODE*)malloc(sizeof(TNODE));
    node->m_Parent = parent;
    node->m_Decoration = DECORATION_NONE;
    node->m_Branches[0] = NULL;
    node->m_Branches[1] = NULL;
    node->m_Branches[2] = NULL;
    return node;
}

int easyToCatchFire(TNODE* root) {
    if (root != NULL) {
        if (root->m_Branches[0]) {
            if (root->m_Decoration == DECORATION_SPARKLER && root->m_Branches[0]->m_Decoration==DECORATION_CANDLE) {
                return 1;
            }
            if (root->m_Decoration == DECORATION_CANDLE && root->m_Branches[0]->m_Decoration==DECORATION_SPARKLER) {
                return 1;
            }
        }
        if (root->m_Branches[1]) {
            if (root->m_Decoration == DECORATION_SPARKLER && root->m_Branches[1]->m_Decoration==DECORATION_CANDLE) {
                return 1;
            }
            if (root->m_Decoration == DECORATION_CANDLE && root->m_Branches[1]->m_Decoration==DECORATION_SPARKLER) {
                return 1;
            }
        }
        if (root->m_Branches[2]) {
            if (root->m_Decoration == DECORATION_SPARKLER && root->m_Branches[2]->m_Decoration==DECORATION_CANDLE) {
                return 1;
            }
            if (root->m_Decoration == DECORATION_CANDLE && root->m_Branches[2]->m_Decoration==DECORATION_SPARKLER) {
                return 1;
            }
        }
        if (root->m_Branches[0] && root->m_Branches[1]) {
            if (root->m_Branches[0]->m_Decoration == DECORATION_SPARKLER && root->m_Branches[1]->m_Decoration == DECORATION_CANDLE) {
                return 1;
            }
            if (root->m_Branches[0]->m_Decoration == DECORATION_CANDLE && root->m_Branches[1]->m_Decoration == DECORATION_SPARKLER) {
                return 1;
            }
        }
        if (root->m_Branches[1] && root->m_Branches[2]) {
            if (root->m_Branches[1]->m_Decoration == DECORATION_SPARKLER && root->m_Branches[2]->m_Decoration == DECORATION_CANDLE) {
                return 1;
            }
            if (root->m_Branches[1]->m_Decoration == DECORATION_CANDLE && root->m_Branches[2]->m_Decoration == DECORATION_SPARKLER) {
                return 1;
            }
        }
        if(easyToCatchFire(root->m_Branches[0]) || easyToCatchFire(root->m_Branches[1]) || easyToCatchFire(root->m_Branches[2])) {
            return 1;
        }
    }
    return 0;
}

void destroyTree(TNODE* root) {
    if (root == NULL) return;
    destroyTree(root->m_Branches[0]);
    destroyTree(root->m_Branches[1]);
    destroyTree(root->m_Branches[2]);
    free(root);
}

int cutBranch(TNODE** root, const char* path) {
    if ((*root) == NULL) {
        return 0;
    }
    int result = 1;
    int len = strlen(path);
    if (len > 0) {
        char* newPath = (char*)malloc(sizeof(char)*len);
        for (int i = 0; i < len; i++) {
            newPath[i] = path[i+1];
        }
        char c = path[0];
        int idx = c  - '0';
        if (idx == 0 || idx == 1 || idx == 2) {
            if ((*root)->m_Branches[idx] == NULL) {
                free(newPath);
                return 0;
            }
            if (len > 1) {
                result = cutBranch(&(*root)->m_Branches[idx], newPath);
            } else {
                destroyTree((*root)->m_Branches[idx]);
                (*root)->m_Branches[idx] = NULL;
            }
        } else {
            result = 0;
        }
        free(newPath);
    } else {
        destroyTree(*root);
        *root = NULL;
    }
    return result;
}

int setDecoration(TNODE** root, const char* path, int decor) {
    int result = 1;
    if ((*root) == NULL) {
        (*root) = newNode(NULL);
    }
    int len = strlen(path);
    if (len > 0) {
        char* newPath = (char*)malloc(sizeof(char)*len);
        for (int i = 0; i < len; i++) {
            newPath[i] = path[i+1];
        }
        char c = path[0];
        int idx = c  - '0';
        if (idx == 0 || idx == 1 || idx == 2) {
            if ((*root)->m_Branches[idx] == NULL) {
                (*root)->m_Branches[idx] = newNode(*root);
            }
            if (len > 1) {
                result = setDecoration(&(*root)->m_Branches[idx], newPath, decor);
            } else {
                (*root)->m_Branches[idx]->m_Decoration = decor;
            }
        } else {
            result = 0;
        }
        free(newPath);
    } else {
        (*root)->m_Decoration = decor;
    }
    if (result == 0) {
        destroyTree(*root);
        *root = NULL;
    }
    return result;
}

int                main               ( void )
{
  TNODE * r;

  r = NULL;
  assert ( setDecoration ( &r, "000", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "001", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "002", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "1", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] != NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[1] -> m_Parent == r
           && r -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "01", DECORATION_NONE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] != NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[1] -> m_Parent == r
           && r -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] != NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[1] -> m_Parent == r
           && r -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "000", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "002", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "2", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[2] -> m_Parent == r
           && r -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "0001", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "000", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 1 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "012001", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "012002", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 1 );
  assert ( cutBranch ( &r, "0120" ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "0123", DECORATION_SPARKLER ) == 0 );
  assert ( r == NULL );
  assert ( cutBranch ( &r, "012" ) == 0 );
  assert ( r == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  destroyTree ( r ); 

  r = NULL;
  assert ( setDecoration ( &r, "012", DECORATION_SPARKLER ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( setDecoration ( &r, "011", DECORATION_CANDLE ) == 1 );
  assert ( r != NULL
           && r -> m_Parent == NULL
           && r -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] != NULL
           && r -> m_Branches[1] == NULL
           && r -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Parent == r
           && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Branches[2] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
           && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL );
  assert ( easyToCatchFire ( r ) == 1 );
  assert ( cutBranch ( &r, "" ) == 1 );
  assert ( r == NULL );
  assert ( easyToCatchFire ( r ) == 0 );
  assert ( cutBranch ( &r, "" ) == 0 );
  assert ( r == NULL );
  destroyTree ( r ); 

  return 0;
}

#ifndef __PROGTEST__

#endif /* __PROGTEST__ */