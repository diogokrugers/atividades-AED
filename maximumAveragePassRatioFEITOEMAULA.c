#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int primeiro;
    int segundo;
} parValores;

typedef struct {
    double ratioAumento;
    parValores c;
} t_heapNodo;

/*
====================
PassRatioAumento
Calcula o aumento na porcentagem de aprovação de uma classe ao adicionar um aluno.
====================
*/
double PassRatioAumento(double pass, double total) {
    return (pass + 1) / (total + 1) - pass / total;
}

/*
====================
Compara
Compara dois nós do heap, ordenando-os de forma que o que possuir 
o maior aumento na porcentagem de aprovação vem primeiro.
====================
*/
int Compara(const void* a, const void* b) {
    t_heapNodo* elemento1 = (t_heapNodo*)a;
    t_heapNodo* elemento2 = (t_heapNodo*)b;
    
    if (elemento1->ratioAumento < elemento2->ratioAumento) return 1;
    if (elemento1->ratioAumento > elemento2->ratioAumento) return -1;
    
    return 0;//caso forem iguais
}

/*
====================
MaxAverageRatio //no leetcode o nome ficou como minúsculo pra poder rodar no main deles
Calcula a maior porcentagem de aprovação (dentre as classes) após
a adição de extraStudents a elas.
====================
*/
double MaxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    double somaPassRatio = 0;
    t_heapNodo *heap = (t_heapNodo*)malloc(classesSize * sizeof(t_heapNodo));
    int heapTamanho = 0;
    
    for (int i = 0; i < classesSize; ++i) {
        somaPassRatio += 1.0 * classes[i][0] / classes[i][1];
        heap[heapTamanho].ratioAumento = PassRatioAumento(classes[i][0], classes[i][1]);
        heap[heapTamanho].c.primeiro = classes[i][0];
        heap[heapTamanho].c.segundo = classes[i][1];
        heapTamanho++;
    }

    qsort(heap, heapTamanho, sizeof(t_heapNodo), Compara);

    while (extraStudents--) {
        t_heapNodo top = heap[0];
        somaPassRatio += top.ratioAumento;
        
        heap[0].ratioAumento = PassRatioAumento(top.c.primeiro + 1, top.c.segundo + 1);
        heap[0].c.primeiro = top.c.primeiro + 1;
        heap[0].c.segundo = top.c.segundo + 1;

        qsort(heap, heapTamanho, sizeof(t_heapNodo), Compara);
    }

    free(heap);
    return somaPassRatio / classesSize;
}

int main(){
    //exemplo 1 do leetcode
    int classesSize = 3;
    int classesColSize = 2;
    int extraStudents = 2;
    int classes[classesSize][classesColSize];

    classes[0][0] = 1;
    classes[0][1] = 2;
    classes[1][0] = 3;
    classes[1][1] = 5;
    classes[2][0] = 2;
    classes[2][1] = 2;

    //não consegui terminar o main a tempo em aula, fiz só as funções do leetcode

    double porcentagemAprovacao = MaxAverageRatio(classes, classesSize, &classesColSize, extraStudents);

    printf("A porcentagem de aprovação foi: %f", porcentagemAprovacao);

    return 0;

}