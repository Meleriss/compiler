#include "ListChild.h"

ListChild *chinit() {
    ListChild *ListChildren;
    ListChildren = (ListChild*)malloc(sizeof(ListChild));
    ListChildren->next = NULL;
    ListChildren->Node = NULL;
    return ListChildren;
}

ListChild *addChild(ListChild *List, AST *Node) {
    if (List->Node == NULL) {
        List->Node = Node;
        return List;
    } else {
        ListChild *List2;
        List2 = (ListChild*)malloc(sizeof(ListChild));
        List->next = List2;
        List->Node = Node;
        List2->next = NULL;
        return List2;
    }
    return NULL;
}
