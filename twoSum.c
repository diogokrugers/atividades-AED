#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    
    for (int i=0; i < numsSize; i++){
        for (int j= i + 1; j < numsSize; j++){
            if (nums[i] + nums[j] == target){
                int* indices = malloc(sizeof(int) * 2);

                indices[0] = i;
                indices[1] = j;

                *returnSize = 2;

                return indices;
            }
        }
    }
    return 0;
}

int main() {
    int nums[] = {2, 7, 11, 15};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int target = 9;
    int returnSize;

    int* result = twoSum(nums, numsSize, target, &returnSize);

    if (result != NULL) {
        printf("Indices found: [%d, %d]\n", result[0], result[1]);
        free(result);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}

// atualização 06/08/2025 -> esse nem era atividade, era só pra aprender