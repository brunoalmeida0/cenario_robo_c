#include <stdio.h>
#include <stdlib.h>

#define LIMITE_INFERIOR 4
#define LIMITE_DIREITO 4

typedef struct{
    int posicaoX;
    int posicaoY;
} TPOSICAO;

struct TNO{ //estrutura auxiliar para a pilha
    TPOSICAO registro; //será onde os itens da pilha serão armazenados 
    struct TNO *prox; //Aponta para o item imediatamente abaixo, se não houver, aponta para NULL
};

typedef struct TNO *TPILHA; //define um ponteiro do tipo TNO chamado TPILHA

TPILHA inicializarPilha(){
     return NULL;    
}

void empilhar(TPOSICAO posicao, TPILHA *pPilha){

    struct TNO *novaPosicao; //variável para auxiliar na inserção de novos itens na pilha

    novaPosicao = (struct TNO *) malloc(sizeof(struct TNO));
    //define que novaPosicao será uma estrutura do tipo ponteiro para TNO, com mesmo tamanho alocado na memória
    novaPosicao->registro = posicao; //registro que está dentro de novaPosicao recebe a posição passada por parâmetro
    novaPosicao->prox = NULL; //prox que está dentro de novaPosição recebe NULL

    if(*pPilha == NULL){ //Se a pilha passada por parâmetro for nula, ela está sendo inicialziada
        (*pPilha) = novaPosicao;//e receberá o que foi definido como 'novaPosicao'
    } else { //Se já houver itens na pilha
        novaPosicao->prox = (*pPilha); //A pilha criada anteriormente irá para prox
        (*pPilha) = novaPosicao; //E o novo item é inserido na pilha
    }

}

void imprimePilha(TPILHA pPilha){
    
    TPILHA pilhaAux = pPilha;
    
    printf("Coordenadas de movimento do robô: \n");

    while(pilhaAux != NULL){
        printf("%i, ", pilhaAux->registro.posicaoX);
        printf("%i\n", pilhaAux->registro.posicaoY);
        pilhaAux = pilhaAux->prox;
    }

}

int Menu(){

    int opcao;

        printf("-----Menu-----\n\n");
        printf("1 - Visualiza sala\n");
        printf("2 - Posicionar robô\n");
        printf("3 - Mover para cima\n");
        printf("4 - Mover para direta\n");
        printf("5 - Mover para baixo\n");
        printf("6 - Mover para esquerda\n");
        printf("7 - Mostrar caminho\n");
        printf("9 - Sair\n\n");

        printf("Opção: ");
        scanf("%i", &opcao);

        return opcao;
    
}

void mostrarSala(TPOSICAO posicao){

    posicao.posicaoX -= 1;
    posicao.posicaoY -= 1;

    int i;
    int j;

    for(i = 0; i < LIMITE_DIREITO; i++){
        printf(" %i ", i+1);
    }

    printf("\n");

    for(i = 0; i < LIMITE_INFERIOR; i++){
        printf("%i", i+1);
        for(j = 0; j < LIMITE_DIREITO; j++){

            if((i == posicao.posicaoX) && (j == posicao.posicaoY)){
                printf(" x ");
            } else {
                printf(" . ");
            }

        }
        printf("\n");
    }

}

TPOSICAO moverCima(TPOSICAO posicao){
    TPOSICAO pAux;
    pAux = posicao;  
 
    if(pAux.posicaoX > 0){
        pAux.posicaoX--;
        mostrarSala(pAux);
    } else {
        printf("Não é possível mover o robô para cima.");
    }

    return pAux;
}

TPOSICAO moverDireita(TPOSICAO posicao){
    TPOSICAO pAux;
    pAux = posicao;

    if (pAux.posicaoY < LIMITE_DIREITO){
        pAux.posicaoY++;
        mostrarSala(pAux);
    } else {
        printf("Não é possível mover o robô para direita.");
    }

    return pAux;
}

TPOSICAO moverBaixo(TPOSICAO posicao){
    TPOSICAO pAux;
    pAux = posicao;
 
    if(pAux.posicaoX < LIMITE_INFERIOR){
        pAux.posicaoX++;
        mostrarSala(pAux);
    } else {
        printf("Não é possível mover o robô para baixo.");
    }

    return pAux;
}

TPOSICAO moverEsquerda(TPOSICAO posicao){
    TPOSICAO pAux;
    pAux = posicao;

    if (pAux.posicaoY > 0){
        pAux.posicaoY--;
        mostrarSala(pAux);
    } else {
        printf("Não é possível mover o robô para esquerda.");
    }

    return pAux;
}

int main(){

    int opcao, i, j;
    TPOSICAO posicao;
    TPILHA pilha;

    pilha = inicializarPilha();

    while(opcao != 9){

        opcao = Menu();


        switch(opcao){
                case 1:
                {
                    system("clear");
                    mostrarSala(posicao);
                } 
                break;

                case 2:
                {
                    system("clear");
                    printf("Digite as cordenadas da posicao do robo: ");
                    scanf("%i", &posicao.posicaoX);
                    scanf("%i", &posicao.posicaoY);    
                    empilhar(posicao, &pilha);                
                } 
                break;

                case 3:
                {
                    system("clear");
                    posicao = moverCima(posicao);

                    for(i = 0; i < LIMITE_DIREITO; i++){
                        for(j = 0; j < LIMITE_DIREITO; j++){
                            if((i == posicao.posicaoX) && (j == posicao.posicaoY)){
                                empilhar(posicao, &pilha);
                            }
                        }
                    }
                } 
                break;

                case 4:
                {
                    system("clear");
                    posicao = moverDireita(posicao);

                    for(i = 0; i < LIMITE_DIREITO; i++){
                        for(j = 0; j < LIMITE_DIREITO; j++){
                            if((i == posicao.posicaoX) && (j == posicao.posicaoY)){
                                empilhar(posicao, &pilha);
                            }
                        }
                    }
                } 
                break;

                case 5:
                {
                    system("clear");
                    posicao = moverBaixo(posicao);

                    for(i = 0; i < LIMITE_DIREITO; i++){
                        for(j = 0; j < LIMITE_DIREITO; j++){
                            if((i == posicao.posicaoX) && (j == posicao.posicaoY)){
                                empilhar(posicao, &pilha);
                            }
                        }
                    }
                } 
                break;

                case 6:
                {
                    system("clear");
                    posicao = moverEsquerda(posicao);

                    for(i = 0; i < LIMITE_DIREITO; i++){
                        for(j = 0; j < LIMITE_DIREITO; j++){
                            if((i == posicao.posicaoX) && (j == posicao.posicaoY)){
                                empilhar(posicao, &pilha);
                            }
                        }
                    }
                } 
                break;

                case 7:
                {
                    system("clear");
                    imprimePilha(pilha);
                } 
                break;

                default:
                {
                    printf("Comando inválido.");
                }
                break;
            }

        
        printf("\n\n");

    }

}