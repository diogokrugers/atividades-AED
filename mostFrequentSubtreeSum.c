#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>


  //Definition for a binary tree node.
  struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };

/*
 Note: The returned array must be malloced, assume caller calls free().
*/

typedef struct TreeNode TreeNode;

/*
ContaNodos
Retorna a quantidade de nodos da árvore
*/
int ContaNodos(TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + ContaNodos(root->left) + ContaNodos(root->right);
}

/*
CalculaSoma
Calcula a soma da subárvore e armazena no array
*/
int CalculaSoma(TreeNode* root, int* somas, int* indice) {
   if (root == NULL) return 0;
     
   int leftSum = CalculaSoma(root->left, somas, indice);
   int rightSum = CalculaSoma(root->right, somas, indice);
   
   int soma = root->val + leftSum + rightSum;
   somas[(*indice)++] = soma;
   
   return soma;
}

/*
findFrequentTreeSum
Encontra a soma mais frequente de sub-árvore
*/
int* findFrequentTreeSum(TreeNode* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    
    int numNodos = ContaNodos(root);
    
    int* somas = (int*) malloc(numNodos * sizeof(int));
    int indice = 0;
    
    CalculaSoma(root, somas, &indice);
    
    for (int i = 0; i < numNodos; i++) {
        for (int j = i + 1; j < numNodos; j++) {
            if (somas[i] > somas[j]) {
                int temp = somas[i];
                somas[i] = somas[j];
                somas[j] = temp;
            }
        }
    }
     
    int maxFreq = 0;
    int freqAtual = 1;
    for (int i = 1; i < numNodos; i++) {
        if (somas[i] == somas[i-1]) {
            freqAtual++;
        } else {
            if (freqAtual > maxFreq) {
                maxFreq = freqAtual;
            }
            freqAtual = 1;
        }
    }
    
    if (freqAtual > maxFreq) {
        maxFreq = freqAtual;
    }
    
    int resultadoCount = 0;
    freqAtual = 1;
    for (int i = 1; i < numNodos; i++) {
        if (somas[i] == somas[i-1]) {
            freqAtual++;
        } else {
            if (freqAtual == maxFreq) {
                resultadoCount++;
            }
            freqAtual = 1;
        }
    }
     
    if (freqAtual == maxFreq) {
        resultadoCount++;
    }
    
    int* resultado = (int*)malloc(resultadoCount * sizeof(int));
    int resultadoIndice = 0;
    
    freqAtual = 1;
    for (int i = 1; i < numNodos; i++) {
        if (somas[i] == somas[i-1]) {
            freqAtual++;
        } else {
            if (freqAtual == maxFreq) {
                resultado[resultadoIndice++] = somas[i-1];
            }
            freqAtual = 1;
        }
    }
     
    if (freqAtual == maxFreq) {
        resultado[resultadoIndice++] = somas[numNodos-1];
    }
    
    *returnSize = resultadoCount;
    
    free(somas);
    
    return resultado;
}

/*
NovoNodo
Só pra criar os nodos da árvore
*/
TreeNode* NovoNodo(int valor){
    TreeNode* nodo = (TreeNode*) malloc(sizeof(TreeNode));
    nodo->val = valor;
    nodo->left = NULL;
    nodo->right = NULL;
    return nodo;
}

int main() {
    
    TreeNode* root = NovoNodo(5);
    root->left = NovoNodo(2);
    root->right = NovoNodo(-5);
    
    int returnSize;
    int* resultado = findFrequentTreeSum(root, &returnSize);
    
    printf("Saída: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", resultado[i]);
        if (i < returnSize - 1) {
            printf(",");
        }
    }
    printf("]\n");
    
    free(resultado);    
    
    free(root->left);
    free(root->right);
    free(root);
    
    return 0;
}