#include <check.h>
#include <string.h>

#include "s21_matrix.h"

void s21_matrix_creator(matrix_t *A, double increase) {
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++, increase++) {
            A->matrix[i][j] = increase;
        }
    }
}

START_TEST(s21_eq_matrix_test) {
        matrix_t test1;
        matrix_t test2;
        s21_create_matrix(5, 5, &test1);
        s21_create_matrix(5, 5, &test2);
        s21_matrix_creator(&test1, 1.0);
        s21_matrix_creator(&test2, 1.0);
        ck_assert_int_eq(s21_eq_matrix(&test1, &test2), SUCCESS);
        s21_remove_matrix(&test1);
        s21_remove_matrix(&test2);
}
END_TEST

START_TEST(s21_eq_matrix_test_2) {
    matrix_t test1;
    matrix_t test2;
    s21_create_matrix(5, 5, &test1);
    s21_create_matrix(1, 5, &test2);
    s21_matrix_creator(&test1, 1.0);
    s21_matrix_creator(&test2, 1.0);
    ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
    s21_remove_matrix(&test1);
    s21_remove_matrix(&test2);
}
END_TEST

START_TEST(s21_eq_matrix_test_3) {
    matrix_t test1;
    matrix_t test2;
    s21_create_matrix(5, 5, &test1);
    s21_create_matrix(5, 5, &test2);
    s21_matrix_creator(&test1, 1.0);
    s21_matrix_creator(&test2, 2.0);
    ck_assert_int_eq(s21_eq_matrix(&test1, &test2), FAILURE);
    s21_remove_matrix(&test1);
    s21_remove_matrix(&test2);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
    matrix_t test1;
    matrix_t test2;
    matrix_t result_by_func;
    s21_create_matrix(2, 2, &test1);
    s21_create_matrix(2, 2, &test2);
    s21_matrix_creator(&test1, 1.0);
    s21_matrix_creator(&test2, 1.0);
    s21_sum_matrix(&test1, &test2, &result_by_func);
    matrix_t result_by_hands;
    s21_create_matrix(2, 2, &result_by_hands);
    result_by_hands.matrix[0][0] = 2.;
    result_by_hands.matrix[0][1] = 4.;
    result_by_hands.matrix[1][0] = 6.;
    result_by_hands.matrix[1][1] = 8.;
    ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
    s21_remove_matrix(&test1);
    s21_remove_matrix(&test2);
    s21_remove_matrix(&result_by_func);
    s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
    matrix_t test1;
    matrix_t test2;
    matrix_t result_by_func;
    s21_create_matrix(2, 2, &test1);
    s21_create_matrix(2, 2, &test2);
    s21_matrix_creator(&test1, 1.0);
    s21_matrix_creator(&test2, 1.0);
    s21_sub_matrix(&test1, &test2, &result_by_func);
    matrix_t result_by_hands;
    s21_create_matrix(2, 2, &result_by_hands);
    result_by_hands.matrix[0][0] = 0.;
    result_by_hands.matrix[0][1] = 0.;
    result_by_hands.matrix[1][0] = 0.;
    result_by_hands.matrix[1][1] = 0.;
    ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
    s21_remove_matrix(&test1);
    s21_remove_matrix(&test2);
    s21_remove_matrix(&result_by_func);
    s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_mult_number_test) {
    matrix_t test1;
    matrix_t result_by_func;
    s21_create_matrix(3, 3, &test1);
    s21_matrix_creator(&test1, 1.0);
    double number = 2;
    s21_mult_number(&test1, number, &result_by_func);
    matrix_t result_by_hands;
    s21_create_matrix(3, 3, &result_by_hands);
    result_by_hands.matrix[0][0] = 2.;
    result_by_hands.matrix[0][1] = 4.;
    result_by_hands.matrix[0][2] = 6.;
    result_by_hands.matrix[1][0] = 8.;
    result_by_hands.matrix[1][1] = 10.;
    result_by_hands.matrix[1][2] = 12.;
    result_by_hands.matrix[2][0] = 14.;
    result_by_hands.matrix[2][1] = 16.;
    result_by_hands.matrix[2][2] = 18.;
    ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
    s21_remove_matrix(&test1);
    s21_remove_matrix(&result_by_func);
    s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_mult_matrix_test) {
    matrix_t test1;
    matrix_t test2;
    matrix_t result_by_func;
    s21_create_matrix(3, 3, &test1);
    s21_create_matrix(3, 3, &test2);
    s21_matrix_creator(&test1, 1.0);
    s21_matrix_creator(&test2, 2.0);
    s21_mult_matrix(&test1, &test2, &result_by_func);
    matrix_t result_by_hands;
    s21_create_matrix(3, 3, &result_by_hands);
    result_by_hands.matrix[0][0] = 36.;
    result_by_hands.matrix[0][1] = 42.;
    result_by_hands.matrix[0][2] = 48.;
    result_by_hands.matrix[1][0] = 81.;
    result_by_hands.matrix[1][1] = 96.;
    result_by_hands.matrix[1][2] = 111.;
    result_by_hands.matrix[2][0] = 126.;
    result_by_hands.matrix[2][1] = 150.;
    result_by_hands.matrix[2][2] = 174.;
    ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
    s21_remove_matrix(&test1);
    s21_remove_matrix(&test2);
    s21_remove_matrix(&result_by_func);
    s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_transpose_test) {
    matrix_t test1;
    matrix_t result_by_func;
    s21_create_matrix(3, 3, &test1);
    s21_matrix_creator(&test1, 1.0);
    s21_transpose(&test1, &result_by_func);
    matrix_t result_by_hands;
    s21_create_matrix(3, 3, &result_by_hands);
    result_by_hands.matrix[0][0] = 1.;
    result_by_hands.matrix[0][1] = 4.;
    result_by_hands.matrix[0][2] = 7.;
    result_by_hands.matrix[1][0] = 2.;
    result_by_hands.matrix[1][1] = 5.;
    result_by_hands.matrix[1][2] = 8.;
    result_by_hands.matrix[2][0] = 3.;
    result_by_hands.matrix[2][1] = 6.;
    result_by_hands.matrix[2][2] = 9.;
    ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
    s21_remove_matrix(&test1);
    s21_remove_matrix(&result_by_func);
    s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_calc_complements_test) {
    matrix_t test, result_by_hands, result_by_func;
    s21_create_matrix(3, 3, &test);
    test.matrix[0][0] = 1;
    test.matrix[0][1] = 2;
    test.matrix[0][2] = 3;
    test.matrix[1][0] = 0;
    test.matrix[1][1] = 4;
    test.matrix[1][2] = 2;
    test.matrix[2][0] = 5;
    test.matrix[2][1] = 2;
    test.matrix[2][2] = 1;
    s21_calc_complements(&test, &result_by_func);
    s21_create_matrix(3, 3, &result_by_hands);
    result_by_hands.matrix[0][0] = 0;
    result_by_hands.matrix[0][1] = 10;
    result_by_hands.matrix[0][2] = -20;
    result_by_hands.matrix[1][0] = 4;
    result_by_hands.matrix[1][1] = -14;
    result_by_hands.matrix[1][2] = 8;
    result_by_hands.matrix[2][0] = -8;
    result_by_hands.matrix[2][1] = -2;
    result_by_hands.matrix[2][2] = 4;
    ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
    s21_remove_matrix(&test);
    s21_remove_matrix(&result_by_hands);
    s21_remove_matrix(&result_by_func);
}
END_TEST

START_TEST(s21_determinant_test) {
    matrix_t test, result_by_hands;
    s21_create_matrix(3, 3, &test);
    s21_create_matrix(3, 3, &result_by_hands);
    s21_matrix_creator(&test, 10);
    result_by_hands.matrix[0][0] = 7.5;
    result_by_hands.matrix[0][1] = 2.1;
    result_by_hands.matrix[0][2] = 3.4;
    result_by_hands.matrix[1][0] = 4.4;
    result_by_hands.matrix[1][1] = 5.5;
    result_by_hands.matrix[1][2] = 6.6;
    result_by_hands.matrix[2][0] = 7.8;
    result_by_hands.matrix[2][1] = 9.2;
    result_by_hands.matrix[2][2] = 0.3;
    double result, result_2;
    s21_determinant(&test, &result);
    s21_determinant(&result_by_hands, &result_2);
    double result_check, result_check2;
    result_check = 0.0;
    result_check2 = -345.917;
    ck_assert_ldouble_eq_tol(result, result_check, 1e-7);
    ck_assert_ldouble_eq_tol(result_2, result_check2, 1e-7);
    s21_remove_matrix(&test);
    s21_remove_matrix(&result_by_hands);
}
END_TEST

START_TEST(s21_determinant_test_2) {
    matrix_t matrix;
    double result = 0;
    s21_create_matrix(4, 4, &matrix);
    s21_fill_matrix(&matrix, 1);
    int ret = s21_determinant(&matrix, &result);
    ck_assert_int_eq(ret, 0);
    s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_inverse_matrix_test) {
    matrix_t test, result_by_hands, result_by_func;
    s21_create_matrix(3, 3, &test);
    test.matrix[0][0] = 2;
    test.matrix[0][1] = 4;
    test.matrix[0][2] = 10;
    test.matrix[1][0] = 10;
    test.matrix[1][1] = 8;
    test.matrix[1][2] = 6;
    test.matrix[2][0] = 10;
    test.matrix[2][1] = 6;
    test.matrix[2][2] = 12;
    s21_create_matrix(3, 3, &result_by_hands);
    result_by_hands.matrix[0][0] = -0.1875;
    result_by_hands.matrix[0][1] = -0.0375;
    result_by_hands.matrix[0][2] = 0.175;
    result_by_hands.matrix[1][0] = 0.1875;
    result_by_hands.matrix[1][1] = 0.2375;
    result_by_hands.matrix[1][2] = -0.275;
    result_by_hands.matrix[2][0] = 0.0625;
    result_by_hands.matrix[2][1] = -0.0875;
    result_by_hands.matrix[2][2] = 0.075;
    s21_inverse_matrix(&test, &result_by_func);
    ck_assert_int_eq(s21_eq_matrix(&result_by_func, &result_by_hands), SUCCESS);
    s21_remove_matrix(&test);
    s21_remove_matrix(&result_by_hands);
    s21_remove_matrix(&result_by_func);
}
END_TEST

int main() {
    Suite *suite = suite_create("S21_TESTS");
    SRunner *srunner = srunner_create(suite);

    TCase *s21_eq_matrix_case = tcase_create("s21_eq_matrix_case");
    suite_add_tcase(suite, s21_eq_matrix_case);
    tcase_add_test(s21_eq_matrix_case, s21_eq_matrix_test);

    TCase *s21_eq_matrix_2_case = tcase_create("s21_eq_matrix_2_case");
    suite_add_tcase(suite, s21_eq_matrix_2_case);
    tcase_add_test(s21_eq_matrix_2_case, s21_eq_matrix_test_2);

    TCase *s21_eq_matrix_3_case = tcase_create("s21_eq_matrix_3_case");
    suite_add_tcase(suite, s21_eq_matrix_3_case);
    tcase_add_test(s21_eq_matrix_3_case, s21_eq_matrix_test_3);

    TCase *s21_sum_matrix_test_case = tcase_create("s21_sum_matrix_test_case");
    suite_add_tcase(suite, s21_sum_matrix_test_case);
    tcase_add_test(s21_sum_matrix_test_case, s21_sum_matrix_test);

    TCase *s21_sub_matrix_test_case = tcase_create("s21_sub_matrix_test_case");
    suite_add_tcase(suite, s21_sub_matrix_test_case);
    tcase_add_test(s21_sub_matrix_test_case, s21_sub_matrix_test);

    TCase *s21_mult_number_test_case = tcase_create("s21_mult_number_test_case");
    suite_add_tcase(suite, s21_mult_number_test_case);
    tcase_add_test(s21_mult_number_test_case, s21_mult_number_test);

    TCase *s21_mult_matrix_test_case = tcase_create("s21_mult_matrix_test_case");
    suite_add_tcase(suite, s21_mult_matrix_test_case);
    tcase_add_test(s21_mult_matrix_test_case, s21_mult_matrix_test);

    TCase *s21_transpose_case = tcase_create("s21_transpose_case");
    suite_add_tcase(suite, s21_transpose_case);
    tcase_add_test(s21_transpose_case, s21_transpose_test);

    TCase *s21_calc_complements_case = tcase_create("s21_calc_complements_case");
    suite_add_tcase(suite, s21_calc_complements_case);
    tcase_add_test(s21_calc_complements_case, s21_calc_complements_test);

    TCase *s21_determinant_case = tcase_create("s21_determinant_case");
    suite_add_tcase(suite, s21_determinant_case);
    tcase_add_test(s21_determinant_case, s21_determinant_test);

    TCase *s21_determinant_case_2 = tcase_create("s21_determinant_case_2");
    suite_add_tcase(suite, s21_determinant_case_2);
    tcase_add_test(s21_determinant_case_2, s21_determinant_test_2);

    TCase *s21_inverse_matrix_case = tcase_create("s21_inverse_matrix_case");
    suite_add_tcase(suite, s21_inverse_matrix_case);
    tcase_add_test(s21_inverse_matrix_case, s21_inverse_matrix_test);

    srunner_run_all(srunner, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(srunner);
    srunner_free(srunner);
    return (number_failed == 0) ? 0 : 1;
}
