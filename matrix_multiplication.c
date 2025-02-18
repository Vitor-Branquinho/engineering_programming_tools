#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int *data;
    int size;
    int capacity;
} List;

void init_list(List *list, int capacity){
    list->data = (int *) malloc (capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
}

void append(List *list, float value) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (int *) realloc(list->data, list->capacity * sizeof(int));
    }
    list->data[list->size++] = value;
}

float** dynamic_allocation(int lines, int columns){
    float** matrix;
    matrix = (float **) malloc (lines * sizeof(float *));

    for(int i = 0; i < lines; i++){
        matrix[i] = (float *) malloc (columns * sizeof(float));
    }

    return matrix;
}

void PrintingFinal_Matrix(float **matrix, int lines, int columns){
    for (int i = 0; i < lines; i++){
        printf("[ ");
        for (int j = 0; j < columns; j++){
            printf("%.2f ", matrix[i][j]);
        }
        printf("]\n");
    }
}

void PrintingMid_Matrix(float **matrix, int lines, int columns, int number_reference_l, int number_referecence_c){
    for (int i = 0; i < lines; i++){
        printf("[ ");

        for (int j = 0; j < columns; j++){ 
            if(i < number_reference_l){
                printf("%.2f ", matrix[i][j]);
            } else if(i == number_reference_l && j <= number_referecence_c){
                printf("%.2f ", matrix[i][j]);
            } else {
                printf("     ");
            }
        }

        printf("]\n");
    }
}

float **Matrix_Multiplication(float **matrix1,float **matrix2, int lines1, int columns1, int lines2, int columns2){
    float **resulting_matrix = dynamic_allocation(lines1, columns2);

        for (int i = 0; i < lines1; i++){
            for (int j = 0; j < columns2; j++){
                float resulting_element = 0;

                for (int k = 0; k < lines2; k++){
                    resulting_element += matrix1[i][k] * matrix2[k][j];
                }

                resulting_matrix[i][j] = resulting_element;
            }
        }

        return resulting_matrix;
}

int main(){

    printf("MATRIX MULTIPLICATION CALCULATOR.\n\n");

    List list_mlines = {NULL, 0, 1};
    List list_mcolumns = {NULL, 0 , 1};

    init_list(&list_mlines, 3);
    init_list(&list_mcolumns, 3);
    
    int lines, columns, quantity;

    float **matrix_1;
    float **matrix_2;

    int i = 0;

    while(i < 2)
    {
        printf("Enter the number of lines of the matrix %d: ", i + 1);
        scanf("%d", &lines);
        printf("Enter the number of columns of the matrix %d: ", i + 1);
        scanf("%d", &columns);
        
        append(&list_mlines, lines);
        append(&list_mcolumns, columns);

        i++;
    }

    matrix_1 = dynamic_allocation(list_mlines.data[0], list_mcolumns.data[0]);
    matrix_2 = dynamic_allocation(list_mlines.data[1], list_mcolumns.data[1]);

    for(int i = 0; i < list_mlines.data[0]; i++){
            for (int j = 0; j < list_mcolumns.data[0]; j++){
                float matrix_value;

                printf("\nEnter the value of line %d and column %d of the matrix 1: ", i + 1, j + 1);
                scanf("%f", &matrix_value);
                matrix_1[i][j] = matrix_value;

                PrintingMid_Matrix(matrix_1, list_mlines.data[0], list_mcolumns.data[0], i, j);
            }
        }

    for(int i = 0; i < list_mlines.data[1]; i++){
        for (int j = 0; j < list_mcolumns.data[1]; j++){
            float matrix_value;

            printf("\nEnter the value of line %d and column %d of the matrix 2: ", i + 1, j + 1);
            scanf("%f", &matrix_value);
            matrix_2[i][j] = matrix_value;

            PrintingMid_Matrix(matrix_2, list_mlines.data[1], list_mcolumns.data[1], i, j);
        }
    }

    printf("Matrix 1 (%d x %d):\n", list_mlines.data[0], list_mcolumns.data[0]);
    PrintingFinal_Matrix(matrix_1, list_mlines.data[0], list_mcolumns.data[0]);
    printf("\nMatrix 2 (%d x %d):\n", list_mlines.data[1], list_mcolumns.data[1]);
    PrintingFinal_Matrix(matrix_2, list_mlines.data[1], list_mcolumns.data[1]);

    if (list_mcolumns.data[0] != list_mlines.data[1]){
        printf("\nThe multiplication can not be done between these matrices (verify them or the order).\n");

        return 1;

    } else {
        printf("\nThe multiplication between these two matrices is:\n");
        float **Multiplication = Matrix_Multiplication(matrix_1, matrix_2, list_mlines.data[0], list_mcolumns.data[0], list_mlines.data[1], list_mcolumns.data[1]);
        PrintingFinal_Matrix(Multiplication, list_mlines.data[0], list_mcolumns.data[1]);

        free(Multiplication);
    }

    free(matrix_1);
    free(matrix_2);
    
    return 0;
}