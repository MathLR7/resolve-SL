#include <stdio.h>
#include <stdlib.h>

void enterMatrixA(float *matrixA, float *matrixAcopy, int matrixLenght){                //scaneia a matriz A
    
    printf("\nForneca abaixo os valores(elemento a elemento) para a matriz A:\n");

    for(int i=0;i<matrixLenght;i++){
        for(int j=0;j<matrixLenght;j++){
            scanf("%f", &matrixA[i*matrixLenght+j]);
            fflush(stdin);
            matrixAcopy[i*matrixLenght+j]=matrixA[i*matrixLenght+j];
        }
    }
    for(int i=0;i<matrixLenght;i++){
        printf("\n");
        for(int j=0;j<matrixLenght;j++){
            printf("%.2f ", matrixA[i*matrixLenght+j]);
        }
    }
}

void enterVectorB(float *vectorB, float *vectorBcopy, int matrixLenght){                //scaneia o vetor B
    
    printf("\nForneca abaixo os valores(elemento a elemento) para o vetor B:\n");

    for(int i=0;i<matrixLenght;i++){
        scanf("%f", &vectorB[i]);
        fflush(stdin);
        vectorBcopy[i]=vectorB[i];
    }

    for(int i=0;i<matrixLenght;i++){
        printf("\n");
        printf("%.2f ", vectorB[i]);
    }
}

void enterData(float *matrixA, float *matrixAcopy, float *vectorB, float *vectorBcopy, int matrixLenght){   //faz o chamamento das entradas de dados da matriz e do vetor    
    
    enterMatrixA((float*) matrixA, (float*) matrixAcopy,  matrixLenght);

    int check=1;
    while(check==1){
        printf("\n\nSe deseja repreencher a matriz A, digite 1, caso deseje continuar digite outra coisa:\n");
        scanf("%d", &check);
        fflush(stdin);
        if(check==1){
            enterMatrixA((float*) matrixA, (float*) matrixAcopy,  matrixLenght);
        }
    }

    enterVectorB(vectorB, vectorBcopy, matrixLenght);

    int check2=1;
    while(check2==1){
        printf("\n\nSe deseja repreencher o vetor B, digite 1, caso deseje continuar digite outra coisa:\n");
        scanf("%d", &check2);
        fflush(stdin);
        if(check2==1){
            enterVectorB(vectorB, vectorBcopy, matrixLenght);
        }
    }

}

void printData(float *matrixA, float *vectorB, int matrixLenght){   //mostra a matriz e o vetor 

    for(int i=0;i<matrixLenght;i++){
        printf("\n| ");
        for(int j=0;j<matrixLenght;j++){
            printf("%.2f ", matrixA[i*matrixLenght+j]);
        }
        printf("| | x%d | ", i);
        if(i==matrixLenght/2){
                printf("=");
            }
            else{
                printf(" ");
            }
        printf(" | %.2f |\n", vectorB[i]);
    }
}

float absoluteValue(float number){                                  //retorna modulo(valor absoluto) de um float
    if(number<0){
        return (-number);
    }  
    else return number;
}

void solveProblem(float *matrixA, float *vectorB, int matrixLenght){
    float pivot;
    for(int k=0;k<matrixLenght;k++){                           // triangula a matriz
        pivot=matrixA[k*matrixLenght+k];
        int l_pivot=k;
        for(int i=k+1;i<matrixLenght;i++){
            if(absoluteValue(matrixA[i*matrixLenght+k])>absoluteValue(pivot)){
                pivot=matrixA[i*matrixLenght+k];
                l_pivot=i;
            }
        }
        
        if(pivot==0) break;                                   //sistema nao apresenta solucao unica, sai do loop
        if(l_pivot!=k){
            float troca;
            for(int j=0;j<matrixLenght;j++){
                troca=matrixA[k*matrixLenght+j];
                matrixA[k*matrixLenght+j]=matrixA[l_pivot*matrixLenght+j];
                matrixA[l_pivot*matrixLenght+j]=troca;
            }
            troca=vectorB[k];
            vectorB[k]=vectorB[l_pivot];
            vectorB[l_pivot]=troca;
        }
        
        for(int i=k+1;i<matrixLenght;i++){
            float m=matrixA[i*matrixLenght+k]/matrixA[k*matrixLenght+k];
            matrixA[i*matrixLenght+k]=0;
            for(int j=k+1;j<matrixLenght;j++){
                matrixA[i*matrixLenght+j]=matrixA[i*matrixLenght+j]-m*matrixA[k*matrixLenght+j];
            }
            vectorB[i]=vectorB[i]-m*vectorB[k];
        }
    } 

    if(pivot==0){                                              //sistema nao apresenta solucao unica, sai da funcao
        printf("\nO sistema nao apresenta solucao unica\n");
        return;
    }

    for(int i=matrixLenght-1;i>=0;i--){                        //substitui valores de modo a restarem apenas pivos de valor 1, mostrando assim os valores das variaveis
        float sum=0;
        float factor;
        for(int j=matrixLenght-1;j>=i;j--){
            if(i!=j){
                sum+=matrixA[i*matrixLenght+j]*vectorB[j];
                matrixA[i*matrixLenght+j]=0;
            }
            else{
                factor=matrixA[i*matrixLenght+j];
                matrixA[i*matrixLenght+j]=1;
            }
        }
        vectorB[i]-=sum;
        vectorB[i]=vectorB[i]/factor;
    }

    printData((float*) matrixA, vectorB, matrixLenght);

}

int optionScan(){                                                   //recebe a operacao desejada no menu
    int option;
    scanf("%d",&option); 
    fflush(stdin);
    return option;
}

int menu(float *matrixA, float *matrixAcopy, float *vectorB, float *vectorBcopy, int matrixLenght){         //apresenta o menu

    printf("\n\n1) Ler Matriz A e vetor b\n2) Imprimir na tela o sistema Ax=b\n3) Resolver sistema Ax = b\n4) Sair\n\n\nDigite o numero de uma opcao valida:"); 
    
    int option = 0;

    while(!(option>0 && option<5)){
        option=optionScan();
        switch (option){
            case 1:
                enterData((float*) matrixA,(float*) matrixAcopy, vectorB, vectorBcopy, matrixLenght);
                return 1;
            break;
        
            case 2:
                printData((float*) matrixAcopy, vectorBcopy, matrixLenght); //imprime a copia pois a matriz A e o vetor b serao alterados durante o programa
                return 1;
            break;

            case 3:
                solveProblem((float*) matrixA, vectorB, matrixLenght);
                return 1;
            break;

            case 4:
                return 0;
            break;

            default:
                printf("\nDigite um numero valido!\n");
                option = optionScan();
            break;
        }
    }

}

int main( int argc, char *argv[ ] ){

    int matrixLenght=atoi(argv[1]);                //passando o argumento obtido no prompt para int
         
    float matrixA[matrixLenght][matrixLenght];     //criando a matriz A e uma copia para visualizacao e entao preenchendo-as de forma que sejam nulas
    float matrixAcopy[matrixLenght][matrixLenght];
    for(int i=matrixLenght-1; i>=0; i--){
        for(int j=matrixLenght-1; j>=0; j--){
            matrixA[i][j]=0;
            matrixAcopy[i][j]=0;
        }
    }

    float vectorB[matrixLenght];                   //criando o vetor B e uma copia para visualização e entao preenchendo-os de forma que sejam nulos
    float vectorBcopy[matrixLenght];
    for(int i=matrixLenght-1; i>=0; i--){
        vectorB[i]=0;
        vectorBcopy[i]=0;
    }

    printf("\nBem vindo ao resolvedor de sistemas lineares 3000\n");

    int check=1; 
    while(check==1){
        check=menu((float*) matrixA,(float*) matrixAcopy, vectorB, vectorBcopy, matrixLenght); //necessaria conversao para referencia
    }
    
    return 0;
}