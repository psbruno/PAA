#include <stdio.h>
 
#include <stdlib.h>
 
typedef struct{
    int NP;//numero do participante
    int PI;// participante de interesse
    struct TParticipante *pPI;//ponteiro do participante de interesse ( x interessado em y )
    struct TParticipante *prox;
    int flagLoop;// marca os participantes que já foram analisados em um loop
    int flag;// -1 == nao analisado (sera analisado em iteracoes futuras), 0 == n faz parte de S, 1== faz parte de S
}TParticipante;
 
 
 
 
 
 
 
void encadeia(TParticipante *P, int n){
    int i=0;
    for(i=0;i<n-1;i++)
        P[i].prox=&P[i+1];
    P[i].prox=NULL;
 
}
 
void MapeaInteresse(TParticipante *Participantes,int n){
    int i=0;
    for(i=0;i<n;i++)
        Participantes[i].pPI = &Participantes[Participantes[i].PI-1];
}
 
void entrada(TParticipante *Participantes, int n){
    int i;
    
    for(i=0;i<n;i++){
        scanf("%d %d", &Participantes[i].NP,&Participantes[i].PI);
        Participantes[i].flag=-1;
        Participantes[i].flagLoop=0;
 
    }
}
int PossivelLoop(TParticipante *Inicial,TParticipante *Ponta,int n_iteracao, int max_its){

    if(n_iteracao==max_its)//não pode ter mais iteracoes do que pessoas
        return 0;
    if(Ponta->flag==1 || Inicial->flag== 1 )// vê se a pessoa já está em algum loop
        return 0;



    if(Inicial->NP==Ponta->NP){// fechou o loop
        Inicial->flag = 1;
        Ponta->flag=1;
        return 1;
    }else if(Ponta->flagLoop!=0){//nao tem loop
        return 0;
    }else{//pode existir loop, continua conferindo
        TParticipante *prox = Ponta->pPI;
        Ponta->flagLoop=1;
 
        Ponta->flag= PossivelLoop(Inicial,Ponta->pPI, n_iteracao+1, max_its);
        Ponta->flagLoop=0;
        return Ponta->flag;
    }
}
 
 
 
int main(){

        int n;
        scanf("%d", &n);
        TParticipante *Participantes = (TParticipante*) malloc (n*sizeof(TParticipante));
        entrada(Participantes,n);
        encadeia(Participantes,n);
        MapeaInteresse(Participantes,n);
 
 
        int i;
        for(i=0;i<n;i++){
            if(Participantes[i].flag!=1){
                //printf("foi no %d\n", Participantes[i].NP);
                PossivelLoop(&Participantes[i],Participantes[i].pPI,1,n-i);
            }
 
            if(Participantes[i].flag == 1)
                printf("%d ", Participantes[i].NP);
        }

        return 0;

}
 
/*
Tentativas de implementações anteriores; 

void DEADCriaLoops(TParticipante *iesimo, TParticipante *raiz){
    if(iesimo->flag==1)
        return;
 
    TParticipante *aux = iesimo;
    while(aux->NP!=raiz->NP){
        printf("%d ", aux->NP);
        aux->flag=1;
        aux=aux->pPI;
    }
//    printf("%d ", aux->NP);
    aux->flag=1;
}
 
 
 
int DEADbacktracking(TParticipante *A, TParticipante *K){
    printf("backtrack em %d %d\n",A->NP,K->NP);
    if(A == NULL || A->flag == 1){
        return 0;
    }
 
    if(A->NP == K->NP){//fechou loop; subconjunto
        TParticipante *aux;
        printf("ok");
        A->flag=1;
        for(aux=A->pPI;aux->NP!=A->NP;aux=aux->pPI){//marca o loop
            aux->flag=1;
        }
        printf("ok2\n");
        return 1;
    }
    TParticipante *aux= K;

    if(A->NP>A->PI)// no meio do loop
        backtracking(A->pPI, K);
 
 
    while(aux!=NULL){
        aux=aux->prox;
        backtracking(aux->pPI, aux);
 
    }
    return;
 
}
 
 //prox pode ser útil
void DEADsubset(TParticipante *An, TParticipante *Fixo){
    if(An->flag==1 || Fixo->flag==1)//  estamos vendo valores que já pertencem a algum subconjunto
        return;
    printf("________________________________%d %d \n",Fixo->NP,An->NP);
    if(Fixo->NP < An->NP){//n fechou loop
        subset(An->pPI, Fixo->pPI);
        return;
    }
    TParticipante *aux=Fixo->pPI;
    while(aux!=Fixo){
            if(aux->flag==1)
                return;
        
        aux->flag=1;
        printf("-%d ", aux->NP);
        aux=aux->pPI;
    }
    
    aux->flag=1;
    printf("%d %d", aux->NP, Fixo->NP);
    printf("\n");
    while(Fixo->prox!=NULL){
        Fixo=Fixo->prox;
        printf("%d \n",Fixo->NP );
        subset(Fixo->pPI,Fixo);
    }
}*/
 
/*
void DEADpintaLoop(TParticipante *A, TParticipante *K){
    printf("-----> Analisando o %d: ", A->NP);
    if(K->flag==1 || K->flag == -1){
        printf("FLAG DE QUEM ELE SE INTERESSOU (%d): %d, return\n", K->NP, K->flag);
        A->flag=-1;
        return;
    }
    if(A->NP < K->NP){
        printf("%d JA FOI ANALISADO!! RETORNANDO\n", A->NP);
        return;
    }
    printf("Vai pintar a partir do %d (flag do %d = %d ) \n", K->NP, K->NP,K->flag);
    TParticipante *aux=K;
    while(aux!=A){
        printf("                Pintando %d \n", aux->NP);
        if(aux->flag==1)
            return;
        aux=aux->pPI;
    }
    while(aux!=A){
        printf("                Pintando %d \n", aux->NP);
        aux->flag=1;
        aux=aux->pPI;
    }
        printf("                Pintando %d e retornando\n", aux->NP);
    aux->flag=1;
}
 
void xxxSubSet(TParticipante *A){
 
    printf(" Loop do %d: ", A->NP);
    if(A->flag!=1){
        printf("Flag not 1\n");
        if(A->NP<A->PI)
            SubSet(A->pPI);
        else
            pintaLoop(A,A->pPI);
    }
 
    printf("voltou no loop do %d, indo pro proximo \n", A->NP);
        if(A->prox!=NULL)
            SubSet(A->prox);

    
    
}
 
==============Solução recursiva (custo mt grande)
//-2 == não analisado
//-1 == em análise
//0 == não faz parte de subconjunto
//1 == faz parte do subconjunto
 
void AnalisaLoop(TParticipante *A){
    TParticipante *first,*I = A->pPI;
    while(I!=A){
        //printf("%d ", I->NP);
        I->flag=1;
        I=I->pPI;
    }
 
    //printf("%d\n\n\n\n\n",I->NP);
 
    I->flag=1;
    first = I->pPI;
    I=A->pPI;
 
 
    if(first->flag==-1)
        first->flag=0;
        
    while(I!=first){
        first->flag=0;
        first=first->pPI;
    }
}
void subset(TParticipante *A, TParticipante *I){
    //printf("Analisando o interesse de %d -  %d, %d\n", A->NP, I->NP, I->flag );
    if(I->flag >=0 ){// Pessoa de interesse já analisada
      //  printf("-----------%d %d\n", A->NP, I->flag);
        A->flag=0;// A pessoa não fará parte de subconjunto
        return;
    }

    if(A->flag==-2){//Participante já analisado??
        A->flag=-1;
        if(A->NP < I->NP){//se o atual se interessa por alguem de índice maior
            subset(A->pPI,I->pPI);//analisa o próximo
        }else{        //loop
            AnalisaLoop(A);
            return;
        }
    }
    if(A->flag==-1){
     //   printf("flag zuada -> %d ",A->NP );
        A->flag=0;
    }
}*/
 
 
