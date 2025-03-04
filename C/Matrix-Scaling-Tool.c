#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    float *data;
    int size;
} Vector_def;

typedef struct{
    float **data;
    int lines;
    int columns;
} Matrix_def;

typedef struct{
    char *letter;
    int size;
    int capacity;
} Variable_List;

typedef struct{
    int *index;
    int size;
    int capacity;
} Index_List;

float* VectorMalloc(int size){
    float* Vector;

    Vector = (float *) malloc (size * sizeof(float));
    return Vector;
}

float** MatrixMalloc(int lines, int columns){
    float **Matrix;

    Matrix = (float **) malloc (lines * sizeof(float *));
    for (int i = 0; i < lines; i++){
        Matrix[i] = (float *) malloc (columns * sizeof(float));
    }

    return Matrix;
}

void init_list(Variable_List *Var_List){
    Var_List->capacity = 26;
    Var_List->letter = (char *) malloc (Var_List->capacity * sizeof(char));
    Var_List->size = 0;
}

void append(Variable_List *Var_List, char Variable){
    Var_List->letter[Var_List->size++] = Variable;
}

void append_index(Index_List *Index_list, int num_line) {
    Index_list->index[Index_list->size++] = num_line;  
}

void PrintingMatrix(float **Matrix, int lines, int columns) {
    for (int i = 0; i < lines; i++) {
        printf("[ ");
        for (int j = 0; j < columns; j++) {
            printf("%.2f ", Matrix[i][j]);
        }
        printf("]\n");
    }
}

void Scaling_Matrix(float **Matrix, float **Result_Matrix, int lines, int columns) {
    for (int index = 0; index < lines; index++) {
        if (Matrix[index][index] != 1 && Matrix[index][index] != 0) {
            float factor = Matrix[index][index];
            for (int j = 0; j < columns; j++) {
                Matrix[index][j] /= factor;
            }
            Result_Matrix[index][0] /= factor;

            printf("\nThe line %d was divided by a factor = %.2f\n", index + 1, factor);
        }

        for (int i = 0; i < lines; i++) {
            if (index == i || Matrix[i][index] == 0) {
                continue;
            } else {
                float mult_factor = Matrix[i][index];

                for (int j = 0; j < columns; j++) {
                    Matrix[i][j] = Matrix[i][j] - (Matrix[index][j] * mult_factor);
                }
                Result_Matrix[i][0] = Result_Matrix[i][0] - (Result_Matrix[index][0] * mult_factor);

                printf("\nThe line %d was multiplied by a factor = %.2f and subtracted from the line %d\n", index + 1, mult_factor, i + 1);
            }
        }

        printf("\nThis is the coefficients matrix:\n");
    
        PrintingMatrix(Matrix, lines, columns);

        printf("\nThis is the results matrix:\n");

        for (int i = 0; i < lines; i++) {
            printf("[ %.2f ] \n", Result_Matrix[i][0]);
        }
    }
}

bool Verifying_Contradiction(float **Matrix, float **Result_Matrix, int lines, int columns){
    int index = 0;
    bool contradiction = false;

    while (index < lines) {

        for (int i = 0; i < lines; i++) {
            int equal_terms = 0;

            if (i == index) {
                continue;
            } else {
                for (int j = 0; j < columns; j++) {
                    if (Matrix[index][j] == Matrix[i][j]) {
                        equal_terms++;
                    }
                }

                if (equal_terms == columns && Result_Matrix[index][0] != Result_Matrix[i][0]){
                    contradiction = true;
                }
            }
        }

        index++;
    }

    return contradiction;
}

int main(){
    printf("Please, put all the equations with the variables in the same order. If the variables is not present in the equation, evidentiate that with a 0 before the variable. Thank you!\n\n");

    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    int num_equations, num_variables;

    Variable_List variable_list = {NULL, 0, 26};
    float **coefficients_matrix;
    float **results_matrix;

    init_list(&variable_list);

    printf("Enter the number of equations in the system: ");
    scanf("%d", &num_equations);
    getchar();

    char **equations = (char **) malloc (num_equations * sizeof(char *));

    for (int i = 0; i < num_equations; i++){
        char equation[30];

        printf("\nEnter the equation %d (use only one letter per variable): ", i + 1);
        fgets(equation, sizeof(equation), stdin);

        equation[strcspn(equation, "\n")] = 0;

        equations[i] = (char *) malloc (strlen(equation) * sizeof(char));
        strcpy(equations[i], equation);

        for (int index = 0; index < strlen(equation); index++) {
            bool variable_exists = false;

            for (int number = 0; number < variable_list.size; number++) {
                if (equation[index] == variable_list.letter[number]) {
                    variable_exists = true;
                }
            }

            if (variable_exists) {
                continue;
            } else {
                for (int letter = 0; letter < 26; letter++) {
                    if (equation[index] == alphabet[letter]) {
                        append(&variable_list, equation[index]);
                    }
                }
            }
        }

        num_variables = variable_list.size;

        char *ptr = equation;

        while (*ptr) {
            if (isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))) {
                float coeff = strtof(ptr, &ptr);

            } else {
                ptr++; 
            }
        }
    }

    printf("\nThe following equations were entered:\n");
    for (int item = 0; item < num_equations; item++) {
        printf("%s\n", equations[item]);
    }

    coefficients_matrix = MatrixMalloc(num_equations, num_variables);
    results_matrix = MatrixMalloc(num_equations, 1);

    for (int i = 0; i < num_equations; i++) {
        char *ptr = equations[i];
        int var_index = 0;         
    
        while (*ptr) {
            if (*ptr == '=') {  
                ptr++;
                results_matrix[i][0] = strtof(ptr, &ptr);
                break;
            } 
            else if (isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))) {
                if (var_index < num_variables) {
                    coefficients_matrix[i][var_index] = strtof(ptr, &ptr);
                    var_index++;
                }
            } 
            else {
                ptr++;
            }
        }
    }

    if (num_variables > num_equations) {
        printf("\nThe system has infinite solutions.\n");
        return 1;
    } else {
        printf("\n\nThis is the coefficients matrix:\n");

        PrintingMatrix(coefficients_matrix, num_equations, num_variables);

        printf("\nThis is the results matrix:\n");

        for (int i = 0; i < num_equations; i++) {
            printf("[ %.2f ] \n", results_matrix[i][0]);
        }

        bool possible = true, scale = false;

        for (int i = 0; i < num_equations; i++) {
            if (coefficients_matrix[i][0] != 1 && coefficients_matrix[i][0] != 0) {
                float factor = coefficients_matrix[i][0];
                for (int j = 0; j < num_variables; j++) {
                    coefficients_matrix[i][j] /= factor;
                }
                results_matrix[i][0] /= factor;
                scale = true;
            }
        }

        if (scale) {
            printf("\nThe matrix was scaled.\n\nThis is the coefficients matrix:\n");

            PrintingMatrix(coefficients_matrix, num_equations, num_variables);

            printf("\nThis is the results matrix:\n");

            for (int i = 0; i < num_equations; i++) {
                printf("[ %.2f ] \n", results_matrix[i][0]);
            }
        }

        bool system_contradiction = Verifying_Contradiction(coefficients_matrix, results_matrix, num_equations, num_variables);

        if (system_contradiction) {
            printf("\nThe system has no solutions.\n");
            return 1;
        }

        int index = 0, rep_lines = 0;
        Index_List index_list = {NULL, 0, num_equations - 1};

        index_list.index = (int *) malloc (index_list.capacity * sizeof(int));

        while (index < num_equations) {
            for (int i = index; i < num_equations; i++) {
                int equal_terms = 0;

                if (i == index) {
                    continue;
                } else {
                    for (int j = 0; j < num_variables; j++) {
                        if (coefficients_matrix[index][j] == coefficients_matrix[i][j] && results_matrix[index][0] == results_matrix[i][0]) {
                            equal_terms++;
                        }
                    }
                }

                if (equal_terms == num_variables) {
                    rep_lines++;

                    append_index(&index_list, i);
                }
            }

            index++;
        }

        rep_lines = index_list.size;

        float **verified_matrix = MatrixMalloc(num_equations - rep_lines, num_variables);
        float **verified_results = MatrixMalloc(num_equations - rep_lines, 1);

        if (index_list.size != 0) {
            if (index_list.size == 1) {
                printf("The line %d was removed since it is repeated.\n\n", index_list.index[0] + 1);
            } else {
                printf("The lines ");
                for (int i = 0; i < index_list.size; i++) {
                    printf("%d ", index_list.index[i] + 1);
                }
                printf("were removed since they are repeated.\n\n");
            }

            for (int i = 0; i < num_equations - rep_lines; i++) {
                bool present = false;

                for (int item = 0; item < index_list.size; item++) {
                    if (i == index_list.index[item]) {
                        present = true;
                    }
                }

                if (!present) {
                    for (int j = 0; j < num_variables; j++) {
                        verified_matrix[i][j] = coefficients_matrix[i][j];
                        verified_results[i][0] = results_matrix[i][0];
                    }
                }
            }

            printf("Debbuging - Verified matrix:\n");
            PrintingMatrix(verified_matrix, num_equations - rep_lines, num_variables);
            printf("\nDebbuging - Verified results:\n");
            for (int i = 0; i < num_equations - rep_lines; i++) {
                printf("[ %.2f ] \n", verified_results[i][0]);
            }

            if ((num_equations - rep_lines) < num_variables){
                printf("\nThe system has infinite solutions.\n");
    
                return 1;
    
            } else if ((num_equations - rep_lines) > num_variables){
                printf("\nThe system has no solutions.\n");
    
                return 1;
                
            } else {
                printf("\nThe system has a unique solution.\n");
            }
        } else {
            if (num_equations == num_variables) {
                printf("\nThe system has a unique solution.\n");
            } else {
                printf("\nThe system has infinite solutions.\n");

                return 1;
            }
        }

        if (index_list.size != 0) {
            printf("Scaling...\n");
            Scaling_Matrix(verified_matrix, verified_results, num_equations - rep_lines, num_variables);

            printf("\n\nThen, the solution for the system is:\n");

            for (int item = 0; item < num_variables; item++) {
                printf("%c = %.2f\n", variable_list.letter[item], verified_results[item][0]);
            }

        } else {
            printf("Scaling...\n");
            Scaling_Matrix(coefficients_matrix, results_matrix, num_equations, num_variables);

            printf("\n\nThen, the solution for the system is:\n");

            for (int item = 0; item < num_variables; item++) {
                printf("%c = %.2f\n", variable_list.letter[item], results_matrix[item][0]);
            }
        }
    


    free(index_list.index);
    free(verified_matrix);
    free(verified_results);
    }

    free(variable_list.letter);
    free(equations);

    free(coefficients_matrix);
    free(results_matrix);

    return 0;
}
