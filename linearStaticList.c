#include <stdio.h>
#include <windows.h>
#include <locale.h>

#define MAX 5
#define false 0
#define true 1

int shouldRun = 1;

typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
    char nome[30];
} REGISTRO;

typedef struct {
    REGISTRO A[MAX];
    int nroElem;
} LISTA;

void inicializaLista(LISTA *l) {
    l->nroElem = 0;
}

int tamanho(LISTA *l) {
    return l->nroElem;
}

void imprimirLista(LISTA *l) {
    int i;
    printf("\n\nLista [ ");
    for (i = 0; i < l->nroElem; i++)
        printf("{ %d, %s } ", l->A[i].chave, l->A[i].nome);
    printf("]\n");
}

int buscaSequencial(LISTA *l, TIPOCHAVE ch) {
    int i = 0;
    while (i < l->nroElem) {
        if (ch == l->A[i].chave) return i;
        else i++;
    }
    return -1;
}

bool inserirPosicaoLista(LISTA *l, REGISTRO reg, int i) {
    int j;
    if ((l->nroElem == MAX) || (i < 0) || (i > l->nroElem)) {
        return false;
    }
    for (j = l->nroElem; j > i; j--) l->A[j] = l->A[j - 1];
    l->A[i] = reg;
    l->nroElem++;
    return true;
}

bool inserirFinalLista(LISTA *l, REGISTRO reg) {
    if (l->nroElem == MAX) return false;
    l->A[l->nroElem] = reg;
    l->nroElem = l->nroElem + 1;
    return true;
}

bool excluiElementoLista(TIPOCHAVE ch, LISTA *l) {
    int pos, j;
    pos = buscaSequencial(l, ch);
    if (pos == -1) return false;
    for (j = pos; j < l->nroElem; j++) l->A[j] = l->A[j + 1];
    l->nroElem--;
    return true;
}

void reinicializaLista(LISTA *l) {
    l->nroElem = 0;
}

void deleteInList(LISTA *list) {
    int key = 0;
    printf("\n\nDigite uma chave para exclusão: ");
    scanf(" %d", &key);
    if (excluiElementoLista(key, list))
        printf("Item com a chave %d excluído com sucesso!", key);
    else
        printf("Erro ao excluir o item informado.");
}

void searchInList(LISTA *list) {
    int key = 0;
    printf("\n\nDigite uma chave para busca: ");
    scanf(" %d", &key);

    int foundKey = buscaSequencial(list, key);
    if (foundKey >= 0)
        printf("\nItem { %d, %s } encontrado na posição %d", list->A[foundKey].chave, list->A[foundKey].nome, foundKey);
    else
        printf("\nItem não encontrado.");
}

void insertEnd(LISTA *list) {
    REGISTRO reg;

    printf("\n\nInsira uma chave: ");
    scanf(" %d", &reg.chave);
    printf("\nInsira um nome: ");
    scanf(" %[^\n]", reg.nome);

    if (buscaSequencial(list, reg.chave) >= 0) {
        printf("\n\nRegistro com esta chave já existe.");
        return;
    }

    if (inserirFinalLista(list, reg))
        printf("\n\nRegistro inserido na lista com sucesso!");
    else
        printf("\n\nLista cheia.");
}

void insertIntoPosition(LISTA *list) {
    REGISTRO reg;
    int position = 0;

    printf("\n\nInsira uma chave: ");
    scanf("%d", &reg.chave);
    printf("\nInsira um nome: ");
    scanf(" %[^\n]", reg.nome);
    printf("\nInsira a posição que deseja inserir este item: ");
    scanf("%d", &position);

    if (buscaSequencial(list, reg.chave) >= 0) {
        printf("\n\nRegistro com esta chave já existe.");
        return;
    }

    if (inserirPosicaoLista(list, reg, position))
        printf("\n\nRegistro inserido na lista com sucesso!");
    else
        printf("\n\nLista cheia.");
}


void renderMainMenu(LISTA *list) {
    printf("\n\n1- Inserir no final\n");
    printf("2- Inserir na posição\n");
    printf("3- Excluir\n");
    printf("4- Listar\n");
    printf("5- Tamanho da lista\n");
    printf("6- Consulta\n");
    printf("7- Reinicializar\n");
    printf("0- Finalizar");

    int option = 0;
    printf("\n\nDigite uma das opções acima: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            insertEnd(list);
            break;
        case 2:
            insertIntoPosition(list);
            break;
        case 3:
            deleteInList(list);
            break;
        case 4:
            imprimirLista(list);
            break;
        case 5:
            printf("\n\nTamanho da lista: %d", tamanho(list));
            Sleep(500);
            break;
        case 6:
            searchInList(list);
            break;
        case 7:
            reinicializaLista(list);
            printf("\n\nLista reiniciada.");
            break;
        default:
            shouldRun = 0;
            printf("\nFinalizando programa...");
            Sleep(500);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    LISTA l;
    inicializaLista(&l);
    while (shouldRun == 1) {
        renderMainMenu(&l);
    }

    return 0;
}
