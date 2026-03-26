#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10    

struct Item {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade;
};

struct Item mochila[MAX_ITENS];
int totalItens = 0;

void menu() {
    printf("\n=================================================\n");
    printf("              INVENTARIO BASICO\n");
    printf("1 - Adicionar Item\n");
    printf("2 - Remover Item\n");
    printf("3 - Listar Itens\n");
    printf("4 - Buscar Item por nome\n");
    printf("5 - Ordenar Itens\n");
    printf("6 - Buscar Binaria por Nome\n");
    printf("7 - Sair\n");
    printf("Escolha uma opcao: ");
}

// --------------------------------------------------------------------------------------

enum Criterio {POR_NOME, POR_TIPO, POR_PRIORIDADE};

bool ordenadoPorNome = false;

void insertionSort(enum Criterio crit) {
    int comparacoes = 0;

    for (int i = 1; i < totalItens; i++) {
        struct Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;

            bool deveMover = false;

            if (crit == POR_NOME && strcmp(mochila[j].nome, chave.nome) > 0) {
                deveMover = true;
            } else if (crit == POR_TIPO && strcmp(mochila[j].tipo, chave.tipo) > 0) {
                deveMover = true;
            } else if (crit == POR_PRIORIDADE && mochila[j].prioridade > chave.prioridade) {
                deveMover = true;
            } else break;

            if (deveMover) {
                mochila[j + 1] = mochila[j];
                j--;
            }

        }
        mochila[j + 1] = chave;
    }

    printf("Ordenado! %d comparacoes realizadas.\n", comparacoes);
}

// --------------------------------------------------------------------------------------

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

    printf("Prioridade: ");
    scanf("%d", &mochila[totalItens].prioridade);
    
    totalItens++;
    printf("Item adicionado com sucesso!\n");
    return 1;
}

// --------------------------------------------------------------------------------------

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

// --------------------------------------------------------------------------------------

void listarItens() {
    if (totalItens == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }
    
    printf("\n=========== INVENTARIO ATUAL ===========\n");
    printf("%-20s | %-15s | %8s | %5s\n", "NOME", "TIPO", "QUANTIDADE", "PRI");
    printf("------------------------------------------\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("%-20s | %-15s | %8d | %5d\n", 
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("========================================\n");
}

// --------------------------------------------------------------------------------------

void menuOrdenacao() {
    int crit;
    printf("\nOrdenar por:\n-Nome 2-Tipo 3-Prioridade: ");
    scanf("%d", &crit);

    if (crit == 1) {
        insertionSort(POR_NOME);
        ordenadoPorNome = true;
    } else if (crit == 2)  {
        insertionSort(POR_TIPO);
    } else if (crit == 3) {
        insertionSort(POR_PRIORIDADE);
    } else {
        printf("Opcao Invalida!\n");
    }
}

// --------------------------------------------------------------------------------------

int buscaItemPorNome() {    
    char nomeProc[50];
    printf("Qual é o nome do Item?\n");
    scanf(" %49[^\n]", nomeProc);

    bool encontrado = false;
    
    for (int i = 0; i < totalItens; i++) {

        if (strcmp(nomeProc, mochila[i].nome) == 0) {
            printf("\n=========== ITENS ENCONTRADOS ===========\n");
            printf("%-20s | %-15s | %8d\n", 
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
               encontrado = true;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado!\n", nomeProc);
    }

    return 0;
}

// --------------------------------------------------------------------------------------

void buscaBinariaNome() {
    if (!ordenadoPorNome) {
        printf("ERRO: A lista deve estar ordenada por NOME primeiro!\n");
        return;
    }
    
    char nomeProc[50];
    printf("Nome para busca binaria: ");
    scanf(" %49[^\n]", nomeProc);
    
    int inicio = 0, fim = totalItens - 1;
    bool encontrado = false;
    
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        
        if (strcmp(nomeProc, mochila[meio].nome) == 0) {
            printf("\n=========== ITEM ENCONTRADO ===========\n");
            printf("%-20s | %-15s | %8d | %5d\n", 
                   mochila[meio].nome, mochila[meio].tipo, 
                   mochila[meio].quantidade, mochila[meio].prioridade);
            encontrado = true;
            break;
        }
        else if (strcmp(nomeProc, mochila[meio].nome) < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    
    if (!encontrado) {
        printf("Item '%s' nao encontrado!\n", nomeProc);
    }
}

// --------------------------------------------------------------------------------------

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
                buscaItemPorNome();
                break;
            case 5:
                menuOrdenacao();
                break;
            case 6:
                buscaBinariaNome();
                break;
            case 7:
                printf("Programa finalizado!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 7);
    
    return 0;
}
