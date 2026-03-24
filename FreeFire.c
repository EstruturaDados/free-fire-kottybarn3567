#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

struct Item {
    char nome[50];
    char tipo[30];
    int quantidade;
};

struct Item mochila[MAX_ITENS];
int totalItens = 0;

void menu() {
    printf("\n=================================================\n");
    printf("              INVENTARIO BASICO\n");
    printf("1 - Adicionar Item\n");
    printf("2 - Remover Item\n");
    printf("3 - Listar Itens\n");
    printf("4 - Sair\n");
    printf("Escolha uma opcao: ");
}

int adicionarItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Maximo de %d itens.\n", MAX_ITENS);
        return 0;
    }
    
    printf("Nome do item: ");
    scanf(" %[^\n]s", mochila[totalItens].nome);
    
    printf("Tipo do item: ");
    scanf(" %[^\n]s", mochila[totalItens].tipo);
    
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    
    totalItens++;
    printf("Item adicionado com sucesso!\n");
    return 1;
}

int removerItem() {
    char nomeBusca[50];
    printf("Nome do item para remover: ");
    scanf(" %[^\n]s", nomeBusca);
    
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Remove movendo itens para frente
            for (int j = i; j < totalItens - 1; j++) {
                strcpy(mochila[j].nome, mochila[j+1].nome);
                strcpy(mochila[j].tipo, mochila[j+1].tipo);
                mochila[j].quantidade = mochila[j+1].quantidade;
            }
            totalItens--;
            printf("Item removido com sucesso!\n");
            return 1;
        }
    }
    printf("Item nao encontrado!\n");
    return 0;
}

void listarItens() {
    if (totalItens == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }
    
    printf("\n=========== INVENTARIO ATUAL ===========\n");
    printf("%-20s | %-15s | %8s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("%-20s | %-15s | %8d\n", 
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("========================================\n");
}

int main() {
    int opcao;
    
    do {
        menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                printf("Programa finalizado!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);
    
    return 0;
}
