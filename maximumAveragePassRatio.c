#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int pass;
    int total;
} t_Class;

typedef struct {
    double aumentoRatio;
    t_Class class;
} t_HeapNo;

//---------------------------------------------------------------------------------------------------------------------

/*
Troca
Troca dois nós de lugar do heap
*/
void Troca(t_HeapNo *a, t_HeapNo *b) {
    t_HeapNo temp = *a;
    *a = *b;
    *b = temp;
}

/*
OrganizaHeap
Organiza a heap de modo que o que o que possuir o maior
aumento assume o começo da heap
*/
void OrganizaHeap(t_HeapNo heap[], int size, int i) {
    int maiorAumento = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if ( esquerda < size && heap[esquerda].aumentoRatio > heap[maiorAumento].aumentoRatio )
        maiorAumento = esquerda;
    if ( direita < size && heap[direita].aumentoRatio > heap[maiorAumento].aumentoRatio )
        maiorAumento = direita;

    if ( maiorAumento != i ) {
        Troca(&heap[i], &heap[maiorAumento]);
        OrganizaHeap(heap, size, maiorAumento);
    }
}


/*
ConstroiHeap
Inicializa o heap pela primeira vez
*/
void ConstroiHeap(t_HeapNo heap[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        OrganizaHeap(heap, size, i);
}


/*
CalculaAumentoRatio
Calcula o ratio de aprovação caso um aluno extra seja adicionado
*/
double CalculaAumentoRatio(int pass, int total) {
    return ( (double) (pass + 1) / (total + 1)) - ( (double) pass / total);
}

/*
MaxAverageRatio
Retorna o maior ratio médio de aprovação após serem adicionado extraStudents.
*/
double MaxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    t_HeapNo *heap = malloc(sizeof(t_HeapNo) * classesSize);
    double totalRatio = 0;

    for (int i = 0; i < classesSize; i++) {
        int pass = classes[i][0];
        int total = classes[i][1];
        heap[i] = (t_HeapNo){
            .aumentoRatio = CalculaAumentoRatio(pass, total),
            .class = (t_Class){.pass = pass, .total = total}
        };
    }

    ConstroiHeap(heap, classesSize);

    while (extraStudents-- > 0) {
        
        t_HeapNo noMaiorAumento = heap[0];
        totalRatio += noMaiorAumento.aumentoRatio;

        // Atualiza a classe com o novo aluno
        noMaiorAumento.class.pass++;
        noMaiorAumento.class.total++;
        noMaiorAumento.aumentoRatio = CalculaAumentoRatio(noMaiorAumento.class.pass, noMaiorAumento.class.total);

        heap[0] = noMaiorAumento;
        OrganizaHeap(heap, classesSize, 0);
    }

    for (int i = 0; i < classesSize; i++) {
        totalRatio += (double)classes[i][0] / classes[i][1];
    }

    free(heap);
    return totalRatio / classesSize;
}

//---------------------------------------------------------------------------------------------------------------------

int main() {
    int classesSize = 3;
    int extraStudents = 2;
    int classesColSize[] = {2, 2, 2};
   
    int** classes = (int**)malloc(classesSize * sizeof(int*));
    classes[0] = (int[]) {1, 2};
    classes[1] = (int[]) {3, 5};
    classes[2] = (int[]) {2, 2};
   
    double result = MaxAverageRatio(classes, classesSize, classesColSize, extraStudents);
    printf("%.6f\n", result);
   
    free(classes);
    return 0;
}