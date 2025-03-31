#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 5
#define PLACA 8

// Definições de cores
#define RESET "\033[0m"
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"
#define CIANO "\033[36m"
#define BRANCO "\033[37m"

//Estrutura para representação do carro
typedef struct {
    char placa[PLACA];
    int manobras;
} Carro;

//Estrutura para representação da pilha no estacionamento
typedef struct {
    Carro carros[MAX];
    int topo;
} Pilha;

//Função para iniciar a pilha
void iniciarPilha(Pilha *ponteiro){
    ponteiro->topo = -1;
}

//Função que verifica se a pilha não está cheia
int verificarCheia(Pilha *ponteiro){
    return ponteiro->topo == MAX - 1;
}

//Função que verifica se a pilha não está vazia
int verificarVazia(Pilha *ponteiro){
    return ponteiro->topo == -1;
}

//Função para empilhar um carro
void empilhar(Pilha *ponteiro, Carro carro){
    if(!verificarCheia(ponteiro)){
        ponteiro->carros[++ponteiro->topo] = carro;
    }
}

//Função para desempilhar um carro
Carro desempilhar(Pilha *ponteiro){
    if(!verificarVazia(ponteiro)){
        return ponteiro->carros[ponteiro->topo--];
    }

    Carro vazio;
    strcpy(vazio.placa, "");
    return vazio;
}

//Função para processar a entrada de um carro
void entrada(Pilha *ponteiro, char *placa){
    if(verificarCheia(ponteiro)){
        printf(VERMELHO "Carro %s não entrou: Estacionamento cheio.\n" RESET, placa);
    }else{
        Carro carro;
        strcpy(carro.placa, placa);
        carro.manobras = 0;
        empilhar(ponteiro, carro);
        printf(VERDE "Carro %s entrou no estacionamento.\n" RESET, placa);
    }
}

//Função para processar a saída de um carro
void saida(Pilha *ponteiro, char *placa){
    Pilha temp;
    iniciarPilha(&temp);
    int encontrado = 0;
    Carro carro;

    //Procura o carro na pilha
    while(!verificarVazia(ponteiro)){
        carro = desempilhar(ponteiro);
        if(strcmp(carro.placa, placa) == 0){
            encontrado = 1;
            break;
        }else{
            carro.manobras++;
            empilhar(&temp, carro);
        }
    }

    if(!encontrado){
        printf(VERMELHO "Carro %s não está no estacionamento.\n" RESET, placa);
    }else{
        printf(VERDE "Carro %s saiu do estacionamento após %d manobras.\n" RESET, placa, carro.manobras);
    }

    //Recoloca os carros na pilha original
    while(!verificarVazia(&temp)){
        empilhar(ponteiro, desempilhar(&temp));
    }
}

//Função para listar as placas dos carros no estacionamento
void listarPlacas(Pilha *ponteiro){
    if(verificarVazia(ponteiro)){
        printf(AMARELO "Estacionamento vazio.\n" RESET);
    }else{
        printf(CIANO "Carros no estacionamento:\n" RESET);
        for(int i = 0; i <= ponteiro->topo; i++){
            printf("%s\n", ponteiro->carros[i].placa);
        }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    system("CLS");

    Pilha estacionamento;
    iniciarPilha(&estacionamento);

    char operacao;
    char placa[PLACA];

    printf(AZUL "-----------------------------------------\n" RESET);
    printf(MAGENTA "        Bem-vindo ao Estacionamento       \n" RESET);
    printf(AZUL "-----------------------------------------\n" RESET);
    
    while(1){
        printf("\n" AZUL "-----------------------------------------\n" RESET);
        printf(CIANO "Escolha uma operação:\n" RESET);
        printf(CIANO "[E] Entrada de carro\n" RESET);
        printf(CIANO "[S] Saída de carro\n" RESET);
        printf(CIANO "[L] Listar placas\n" RESET);
        printf(CIANO "[Q] Sair\n" RESET);
        printf(AZUL "-----------------------------------------\n" RESET);
        printf(CIANO "Digite a operação: " RESET);
        
        scanf(" %c", &operacao);
        
        if(operacao == 'Q' || operacao == 'q'){
            break;
        }
        
        switch (operacao) {
            case 'E':
            case 'e':
                printf("Digite a placa do carro: ");
                scanf("%s", placa);
                entrada(&estacionamento, placa);
                break;
            case 'S':
            case 's':
                printf("Digite a placa do carro: ");
                scanf("%s", placa);
                saida(&estacionamento, placa);
                break;
            case 'L':
            case 'l':
                listarPlacas(&estacionamento);
                break;
            default:
                printf(VERMELHO "Operação inválida. Tente novamente.\n" RESET);
                break;
        }
    }
    
    printf(AZUL "-----------------------------------------\n" RESET);
    printf(AMARELO "  Obrigado por usar nosso sistema!\n" RESET);
    printf(AZUL "-----------------------------------------\n" RESET);

    return 0;
}
