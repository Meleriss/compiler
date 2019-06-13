#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTAB_SIZE 71
#define HASHTAB_MUL 31

struct listnode {
    char *key;  //название идентиф
    int value;  //хэш-ключ
    int size;
    int offset;
    int baseType; //1 - переменная, 2 - массив, 3 - функция
    int type; //1 - инт, 2 - стринг
    int countElem;  //для массивов
    struct listnode *koll;  //для решения коллизий
    struct listnode *next;
};

struct idTable {
    struct listnode *hashtab[HASHTAB_SIZE];
    struct idTable *next;
    int level;
};


int hashtab_hash(char *key);
void hashtab_init(struct listnode **hashtab);
struct idTable *idTable_init(int level);
void hashtab_add(struct listnode **hashtab, char *key, int value, int baseType, int type);
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key);
void hashtab_delete(struct listnode **hashtab, char *key);

struct listnode *findInAllTable(struct idTable *table, char *key);

#endif