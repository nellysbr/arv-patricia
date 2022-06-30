/*

Trabalho final de estrutura de dados II - Árvore Patrícia

Referências 

Livro: Fundamentals of data structures in c : Horowitz, Ellis (2 edição).


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*declaração de variáveis globais */

int selecao;

/*Inicia uma nova trie*/

typedef struct partriciaArvore{
	char *bits;
	int bitnumber;
	int data;
	struct partriciaArvore *esq;
	struct partriciaArvore *dir;
	
	
}partriciaArvore;

/*Carrega as funções*/

partriciaArvore *bit(partriciaArvore *prox, int bitnum, char *k);
partriciaArvore *insert(partriciaArvore *t, char*bits, int data);
void searchbit(partriciaArvore *t, char *k);
partriciaArvore *search(partriciaArvore *t, char *k);
void printall(partriciaArvore *raiz, int bitnum);





/*Função que recebe o input do usuário para navegar nos menus */

int input (){
	int numero;
	scanf("%d", &numero);
	return (numero);
}


int main (){
	
	partriciaArvore *raiz = NULL;

	
	do {
	

		printf ("\n--------------------------\n\nSelecione a opcao desejada\n\n-------------------------\n\n");
	
		printf ("1 - Inserir dados \n");
		printf ("2 - Buscar dados \n");
		printf ("5 - Sair \n");
	
		printf ("\n\nDigite a opcao desejada: ");
		selecao = input();

	

		switch(selecao) {
			case 1 : {
				system("cls");
				int data;
				int number;
				
				char *bitnumber = (char*) malloc(sizeof(char) *number + 1);
				printf ("\nDigite a index do dado (bits): ");
				scanf("%s", bitnumber);
				printf ("\nDigite o dado que sera armazenado (apenas numeros): ");
                scanf("%d", &data);
                raiz = insert(raiz, bitnumber, data);
				
				break;
			}
			case 2 : {
				system("cls");
				int number;
				char *bitnumber = (char*)malloc(sizeof(char) *number + 1);
				printf ("\nDigite a index (bits) do dado que deseja encontrar: ");
                scanf("%s",bitnumber);
                searchbit(raiz, bitnumber);
				break;
			}	
	}
}


while (selecao != 5);

return 0;
	
}

partriciaArvore *bit(partriciaArvore *prox, int bitnum, char *k){
        bitnum = bitnum -1 ;
        char bit2[2];
        bit2[0] = k[bitnum];
        bit2[1] = '\0';

        if(strcmp(bit2, "1") == 0){
            return prox -> dir;
        }else if(strcmp(bit2, "0") == 0){
            return prox -> esq;
        }
        return NULL;
}
/*Procurar dado*/

partriciaArvore *search(partriciaArvore *t, char *k){
        if(t == NULL){
                return NULL;
        }
       partriciaArvore *current = t;
       partriciaArvore *prox = t -> esq;

        while(prox -> bitnumber > current -> bitnumber){
                current = prox;
                prox = bit(prox, prox -> bitnumber, k);
        }
        return prox;
}

/*Procurar pelo index (bits) */

void searchbit(partriciaArvore *t, char *k){
        printf("\n\nResultado da busca -> ");
        if(t == NULL){
                printf("Nao encontrado\n");
                return;
        }
        partriciaArvore *temp = search(t, k);
        if(strcmp(temp -> bits, k) ==0){
                printf("%d\n", temp -> data);
        }else{
                printf("Nao encontrado\n");
        }
}


/* Inserir dados Patricia */

partriciaArvore *insert(partriciaArvore *t, char*bits, int data){
        printf("Dado inserido -> ");
        if( t == NULL){
                t = (partriciaArvore*) malloc(sizeof(partriciaArvore));
                t -> bitnumber = 0;
                t -> data = data;
                t -> bits = bits;
                t -> esq = t;
                t -> dir = NULL;
                printf("%d\n", data);
                return t;
        }

        partriciaArvore *lastnode;
        lastnode = search(t, bits);
        if(strcmp(lastnode -> bits, bits)==0){
                printf("Ja existe um dado nesse index\n");
                return t;
        }


        int i;
        for(i = 0; bits[i] == lastnode -> bits[i]; i++);

        partriciaArvore *current = t -> esq;
        partriciaArvore *parent = t;
        while(current -> bitnumber > parent -> bitnumber && current -> bitnumber < i + 1){
                parent = current;
                current = bit(current, current -> bitnumber, bits);
        }
        partriciaArvore *newnode = (partriciaArvore*)malloc(sizeof(partriciaArvore));
        newnode -> bitnumber = i+1;
        newnode -> bits = bits;
        newnode -> data = data;
        char bit2[2];
        bit2[0] = newnode -> bits[i];
        bit2[1]='\0';

        if(strcmp(bit2, "1") == 0){
                newnode -> esq = current;
                newnode -> dir = newnode;
        }else{
                newnode -> esq = newnode;
                newnode -> dir = current;
        }

        if(current == parent->esq){
                parent -> esq = newnode;
        }else{
                parent -> dir = newnode;
        }
        printf("%d\n", newnode -> data);
        return t;
}




