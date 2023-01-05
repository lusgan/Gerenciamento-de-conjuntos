#include <stdio.h>
#include <stdlib.h>
#define M 8
#define N 10

int menu();
int eh_vazio(int linha[]);
void inserir_dados_no_conjunto(int conjunto[]);
void uniao_De_Conjunto(int A[],int B[],int conjunto_A_Ser_Formado[]);
int pertence_ao_conjunto (int numero, int conjunto[]);
void interseccao_De_Conjunto(int A[], int B[], int conjunto_A_Ser_Formado[]);
void removerConjunto(int conjunto[]);
int tamanho_do_array(int A[]);

int main(){
    int valor_do_menu;
    int numero_de_conjuntos=0;
    int matriz[M][N];

    //criando matriz formada somente por zeros.
    for (int i = 0; i<M; i++){
        for (int j = 0; j<N; j++){
            matriz[i][j]=0;
        }
    }


    do{
        valor_do_menu = menu();
        printf("\n");

        if (valor_do_menu==1){
            if(numero_de_conjuntos==M){
                printf("Ja atingiu o numero maximo de conjuntos.");
                printf("\n");
            }
            else{
                numero_de_conjuntos+=1;
            }
        }

        else if (valor_do_menu==7){
            printf("Ha %d conjuntos:\n",numero_de_conjuntos);
            for (int i = 0; i<numero_de_conjuntos;i++){
                if (eh_vazio(matriz[i])==0){
                    printf("%d: vazio",i);
                }
                else{
                    printf("%d: ",i);
                    for (int j = 0; j< N;j++){
                        if(matriz[i][j]!=0){
                            printf("%d ",matriz[i][j]);
                        }
                    }
                }
                printf("\n");
            }
        }printf("\n");

        if (valor_do_menu==2){
                int conjunto;
                printf("Digite o numero do conjunto a ser alterado:");
                scanf("%d",&conjunto);
                if(0<=conjunto && conjunto<numero_de_conjuntos){
                    inserir_dados_no_conjunto(matriz[conjunto]);
                }
                else{
                    printf("Esse conjunto não existe");
                }
                printf("\n\n");
        }

        else if(valor_do_menu==4){
            if(numero_de_conjuntos<M){
                int primeiroConjunto,segundoConjunto;
                //numero_de_conjuntos+=1;
                printf("Diga os conjuntos a serem unidos:");
                scanf("%d %d",&primeiroConjunto,&segundoConjunto);
                if(primeiroConjunto<numero_de_conjuntos && segundoConjunto<numero_de_conjuntos){
                    numero_de_conjuntos+=1;
                    uniao_De_Conjunto(matriz[primeiroConjunto],matriz[segundoConjunto],matriz[numero_de_conjuntos-1]);
                }
                else if(primeiroConjunto>=numero_de_conjuntos-1 || segundoConjunto>=numero_de_conjuntos-1){
                    printf("Um dos conjuntos ainda nao existe\n\n");
                }
            }
            else if(numero_de_conjuntos==M){
                printf("Numero de conjuntos atingiu valor maximo, precisa remover um conjunto\n\n");
            }
        }

        else if(valor_do_menu==5){
            int primeiroConjunto,segundoConjunto;
            printf("Diga os conjuntos a serem interseccionados:");
            scanf("%d %d",&primeiroConjunto,&segundoConjunto);
            if(primeiroConjunto<numero_de_conjuntos && segundoConjunto<numero_de_conjuntos){
                numero_de_conjuntos+=1;
                interseccao_De_Conjunto(matriz[primeiroConjunto],matriz[segundoConjunto],matriz[numero_de_conjuntos-1]);
            }
            else if(primeiroConjunto>=numero_de_conjuntos || segundoConjunto>=numero_de_conjuntos){
                printf("Um dos conjuntos ainda n existe\n\n");
            }
        }

        else if(valor_do_menu==8){
            int valor_de_busca;
            int erro = 1;
            printf("Insira o valor que deseja encontrar: ");
            scanf("%d",&valor_de_busca);
            printf("\nConjuntos que contem o valor %d: ",valor_de_busca);
            for(int i = 0; i<numero_de_conjuntos;i++){
                if(pertence_ao_conjunto(valor_de_busca,matriz[i])==0){
                    printf("%d ",i);
                    erro = 0;
                }
            }
            if(erro==1){
                printf("Nenhum conjunto possui esse valor");
            }
            printf("\n\n");
        }

        else if(valor_do_menu==6){
            int conjunto_a_ser_mostrado;
            printf("Digite o valor do conjunto a ser mostrado: ");
            scanf("%d",&conjunto_a_ser_mostrado);
            printf("\nConjunto %d: ",conjunto_a_ser_mostrado);

            for(int i = 0; i<N; i++){
                if(matriz[conjunto_a_ser_mostrado][i]!=0){
                    printf("%d ",matriz[conjunto_a_ser_mostrado][i]);
                }
                else{
                    printf("Conjunto nao existe.");
                    break;
                }
            }
            printf("\n\n");
        }

        else if(valor_do_menu==3){
            int conjunto_a_ser_removido;
            printf("Digite o conjunto a ser removido: ");
            scanf("%d",&conjunto_a_ser_removido);
            removerConjunto(matriz[conjunto_a_ser_removido]);

            for( int i = conjunto_a_ser_removido; i<numero_de_conjuntos;i++){
                for(int j =0; j<N;j++){
                    matriz[i][j]=matriz[i+1][j];
                }
            }
            numero_de_conjuntos--;
        }
    }while (valor_do_menu!=9);
    return 0;
}

int menu(){
    int menu;
    printf("1. Criar um novo conjunto vazio\n");
    printf("2. Inserir dados em um conjunto\n");
    printf("3. Remover um conjunto\n");
    printf("4. Fazer a uniao entre dois conjuntos\n");
    printf("5. Fazer a interseccao entre dois conjuntos\n");
    printf("6. Mostrar um conjunto, dado o seu indice\n");
    printf("7. Mostrar todos os conjuntos\n");
    printf("8. Buscar por um valor\n");
    printf("9. Sair do programa.\n");
    scanf("%d",&menu);
    return menu;

}

int eh_vazio( int linha[]){
    int soma_dos_elementos = 0;
    for (int i = 0; i<N; i++){
        soma_dos_elementos+=linha[i];
    }
    if (soma_dos_elementos==0){
        return 0;
    }
    else {
        return 1;
    }
}

void inserir_dados_no_conjunto(int conjunto[]){
    if(pertence_ao_conjunto(0,conjunto)==0){
        int valor_inserido = -1;
        int quantidade = 0;

        for(int i = 0; i<N;i++){
            if (conjunto[i]==0){
                quantidade=i;
                break;
            }
        }

        while(valor_inserido!=0 && quantidade<N){
            scanf("%d",&valor_inserido);
            if(pertence_ao_conjunto(valor_inserido,conjunto)==1){
            conjunto[quantidade]=valor_inserido;
            quantidade++;
            }
        }

        if(quantidade==N){
            printf("Numero max atingido");
        }
    }
    else{
        printf("Conjunto ja esta cheio");
    }

}

int pertence_ao_conjunto(int numero,int conjunto[]){
    for (int i =0; i<N;i++){
        if(numero==conjunto[i]){
            return 0;
        }
    }
    return 1;
}

void uniao_De_Conjunto(int A[],int B[],int conjunto_A_Ser_Formado[]){
    int len_A = tamanho_do_array(A);
    int len_B = tamanho_do_array(B);
    if(len_A<N){
        int aux;
        for (int i = 0; i<N;i++){
            conjunto_A_Ser_Formado[i]=A[i];
            if(conjunto_A_Ser_Formado[i]!=0){
                aux =i;
            }
        }
        for(int j = 0; j<N;j++){
            if(pertence_ao_conjunto(B[j],conjunto_A_Ser_Formado)==1){
                conjunto_A_Ser_Formado[aux+1]=B[j];
                aux+=1;
            }
        }
    }
    if(tamanho_do_array(conjunto_A_Ser_Formado)>N){
        printf("Tamanho dos vetores excede capacidade maxima\n");
    }

}

void interseccao_De_Conjunto(int A[], int B[], int conjunto_A_Ser_Formado[]){
    int aux = 0;
    for (int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
            if(A[i]==B[j]){
                conjunto_A_Ser_Formado[aux]=A[i];
                aux++;
            }
        }
    }
}

void removerConjunto(int conjunto[]){
    for (int i = 0; i<N; i++){
        conjunto[i]=0;
    }
}

int tamanho_do_array(int A[]){
    int i;
    for(i = 0; A[i]==0;i++);
    return i;
}
