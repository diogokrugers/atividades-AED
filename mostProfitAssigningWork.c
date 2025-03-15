#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int difficulty;
    int profit;
} Job;

/*
====================
ComparaJobs
Faz as dificuldades dos jobs ficarem em ordem crescente no array de jobs
====================
*/
int ComparaJobs(const void* a, const void* b) {
    Job* jobA = (Job*)a;
    Job* jobB = (Job*)b;
    return jobA->difficulty - jobB->difficulty;
}

/*
====================
ComparaWorkers
Faz as habilidades dos workers ficarem em ordem crescente no array de workers
====================
*/
int ComparaWorkers(const void* a, const void* b) {
    return ( *(int*)a - *(int*)b );
}

/*
====================
maxProfitAssignment
Dado vários jobs (que serão guardados numa struct contendo sua difficulty e seu profit), 
cria um array de struct jobs e garante que todos seus elementos estão em ordem crescente.
Após fazer isso, pega um array de workers, alinha eles em ordem crescente de habilidade
e assinala os a jobs que estão de acordo com a sua hablidade. Retorna o lucro máximo/total,
que é alcançado somando o lucro de todos os workers.  
====================
*/
int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    
    //inicializa os elementos do array da struct jobs
    Job jobs[difficultySize];
    for (int i = 0; i < difficultySize; i++) {
        jobs[i].difficulty = difficulty[i];
        jobs[i].profit = profit[i];
    }
    
    qsort(jobs, difficultySize, sizeof(Job), ComparaJobs); // deixa as dificuldades dos trabalhos em ordem crescente
    
    // jobs mais dificeis terao profits maiores
    int maiorProfitJob = 0;
    for (int i = 0; i < difficultySize; i++) {
        if (jobs[i].profit > maiorProfitJob) {
            maiorProfitJob = jobs[i].profit;
        } else {
            jobs[i].profit = maiorProfitJob;
        }
    }
    
    qsort(worker, workerSize, sizeof(int), ComparaWorkers); // deixa os workers em ordem crescente de habilidade
    
    // coloca cada worker em um trabalho
    int lucroTotal = 0;
    int jobIndice = 0;
    
    for (int i = 0; i < workerSize; i++) {
        // encontra maior dificuldade que esse worker consegue
        while (jobIndice < difficultySize && jobs[jobIndice].difficulty <= worker[i]) {
            jobIndice++;
        }
        
        // garante que cada worker so pode 1 fazer um job
        if (jobIndice > 0) {
            lucroTotal += jobs[jobIndice - 1].profit;
        }
    }
    
    return lucroTotal;
}

int main(){

int difficultySize = 5;
int profitSize = 5;
int workerSize = 4;

int difficulty[5] = {2, 4, 6, 8, 10};
int profit[5] = {10, 20, 30, 40, 50};
int worker[4] = {4, 5, 6, 7};

int lucroTotal = maxProfitAssignment(difficulty, difficultySize, profit, profitSize, worker, workerSize);

printf("O lucro total foi: %d\n", lucroTotal);

return 0;
}