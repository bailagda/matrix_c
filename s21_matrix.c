#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int i = 0; A->rows > i; i++) {
            if (A->matrix[i]) {
                free(A->matrix[i]);
            }
        }
        free(A->matrix);
        A->matrix = NULL;
    }
    if (A->rows) {
        A->rows = 0;
    }
    if (A->columns) {
        A->columns = 0;
    }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int ret = 0;

    result->rows = rows;
    result->columns = columns;

    if (rows < 1 || columns < 1) {
        ret = 1;
    } else if (rows > 0 && columns > 0) {
        result->matrix = (double **)calloc(rows, sizeof(double *));

        for (int i = 0; i < rows; i++) {
            result->matrix[i] = (double *)calloc(columns, sizeof(double));
        }
    }

    return (ret);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int exit_code = SUCCESS;
    if (A->matrix != NULL && B->matrix != NULL) {
        if (A->rows == B->rows && A->columns == B->columns) {
            for (int i = 0; A->rows > i; i++) {
                for (int j = 0; A->columns > j; j++) {
                    if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.0000001) {
                         exit_code = FAILURE;
                         break;
                    }
                }
                if (exit_code == FAILURE) {break;}
            }
        } else {
            exit_code = FAILURE;
        }
    } else {
        exit_code = FAILURE;
    }
    return exit_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int exit_code = 0;
    s21_create_matrix(A->rows, A->columns, result);
    if (A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL &&
        A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
        if (A->rows == B->rows && A->columns == B->columns) {
            for (int i = 0; A->rows > i; i++) {
                for (int j = 0; A->columns > j; j++) {
                    result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                }
            }
        } else {
            exit_code = 2;
        }
    } else {
        exit_code = 1;
    }

    return exit_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int exit_code = 0;
    s21_create_matrix(A->rows, A->columns, result);
    if (A != NULL && A->matrix != NULL && B != NULL && B->matrix != NULL &&
        A->rows > 0 && B->rows > 0 && A->columns > 0 && B->columns > 0) {
        if (A->rows == B->rows && A->columns == B->columns) {
            for (int i = 0; A->rows > i; i++) {
                for (int j = 0; A->columns > j; j++) {
                    result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                }
            }
        } else {
            exit_code = 2;
        }
    } else {
        exit_code = 1;
    }
    return exit_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int exit_code = 0;
    s21_create_matrix(A->rows, A->columns, result);
    if (A->rows == result->rows && A->columns == result->columns) {
        for (int i = 0; A->rows > i; i++) {
            for (int j = 0; A->columns > j; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    } else {
        exit_code = 2;
    }
    return exit_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int exit_code = 0;
    if (A->columns == B->rows) {
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; A->rows > i; i++) {
            for (int t = 0; B->columns > t; t++) {
                for (int j = 0; A->columns > j; j++) {
                    result->matrix[i][t] += A->matrix[i][j]*B->matrix[j][t];
                }
            }
        }
    } else {
        exit_code = 2;
    }
    return exit_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int exit_code = 0;
    s21_create_matrix(A->columns, A->rows, result);
    if (A->columns < 1 && A->rows < 1) {
        exit_code = 2;
    } else {
        for (int i = 0; A->rows > i; i++) {
            for (int j = 0; A->columns > j; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    }
    return exit_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int exit_code = 0;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        if (A->rows == A->columns) {
        s21_create_matrix((A->rows), (A->columns), result);
            for (int i = 0; A->rows > i; i++) {
                for (int j = 0; A->columns > j; j++) {
                    double res = 0.0;
                    matrix_t minor = {0};
                    exit_code = s21_get_minor(i+1, j+1,  A, &minor);
                    if (!exit_code)
                        exit_code = s21_determinant(&minor, &res);
                    if (!exit_code)
                        result->matrix[i][j] = pow((-1), i + j) * res;
                    s21_remove_matrix(&minor);
                }
            }
        } else {
            exit_code = 1;
        }
    } else {
        exit_code = 1;
    }
    return exit_code;
}

double s21_help_determinant(matrix_t *A) {
    int ret = 0;
    double res = 0.0;
    if (A->rows == 2 && A->columns == 2) {
        res = s21_base_determinant(A);
    } else {
        for (int i = 0; i < A->rows; i++) {
            matrix_t M;
            ret = s21_get_minor(1, i + 1, A, &M);
            if (!ret)
                res += pow((-1), i) * A->matrix[0][i] * s21_help_determinant(&M);
            s21_remove_matrix(&M);
        }
    }
    return (res);
}

int s21_determinant(matrix_t *A, double *result) {
    int ret = 0;
    if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
        ret = 1;
    }
    if (A->rows == A->columns && !ret) {
        *result = A->matrix[0][0];
        if (A->rows > 1) {
            *result = s21_help_determinant(A);
        }
    } else {
        ret = 1;
    }
    return (ret);
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int exit_code = 0;
    double det = 0.0;
    if (A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0) {
        if (!exit_code) {
            exit_code = s21_determinant(A, &det);
            if ((fabs(det - 0) >= pow(10, -7)) && !exit_code) {
                matrix_t tmp_calc = {0};
                exit_code = s21_calc_complements(A, &tmp_calc);
                if (!exit_code) {
                    matrix_t tmp_transpose = {0};
                    exit_code = s21_transpose(&tmp_calc, &tmp_transpose);
                    if (!exit_code) {
                        s21_mult_number(&tmp_transpose, (1.0 / det), result);
                    }
                    s21_remove_matrix(&tmp_transpose);
                }
                s21_remove_matrix(&tmp_calc);
            }
        }
    } else {
        exit_code = 1;
    }
    return exit_code;
}

// ****SUPPORT functions****

double s21_base_determinant(matrix_t *tmp) {
    return (tmp->matrix[0][0]*tmp->matrix[1][1]) - (tmp->matrix[0][1]*tmp->matrix[1][0]);
}

int s21_get_minor(int row, int column, matrix_t *A, matrix_t *result) {
    int ret = 1;
    if (A->matrix != NULL) {
        ret = s21_create_matrix(A->rows - 1, A->columns - 1, result);
        if (!ret) {
            int k = 0;
            int z = 0;
            for (int i = 0; i < A->rows; i++) {
                k = i;
                if (k > row - 1) {k--;}
                for (int j = 0; j < A->columns; j++) {
                    z = j;
                    if (z > column - 1) {z--;}
                    if (i != (row - 1) && j != (column - 1))
                        result->matrix[k][z] = A->matrix[i][j];
                }
            }
        }
    }
    return (ret);
}

void s21_fill_matrix(matrix_t *a, double num) {
    for (int i = 0; a->rows > i; i++) {
        for (int j = 0; a->columns > j; j++) {
            a->matrix[i][j] = num;
            num += 1;
        }
    }
}

void s21_print_matrix(matrix_t *matrix) {
    for (int i = 0; matrix->rows > i; i++) {
        for (int j = 0; matrix->columns > j; j++) {
            printf("%8.6lf ", matrix->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
