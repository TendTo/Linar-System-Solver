#include <check.h>
#include "gaussian_reduction.h"

START_TEST(test_Gaussian_reduction_pivot_3_int)
{
    double *x;
    double A[] = {1.0, 3.0, -4.0, 3.0, 1.0, 2.0, 0.0, -2.0, 3.0};
    double b[] = {1.0, -7.0, 1.0};
    double expected[] = {6.0, -11.0, -7.0};
    x = Gaussian_reduction_pivot(A, b, 3);
    ck_assert(compare_arr(x, expected, 3));
    free(x);
}
END_TEST

START_TEST(test_Gaussian_reduction_pivot_3_comma)
{
    double *x;
    double A[] = {1.0, 3.0, -4.0, 3.0, 1.0, 2.0, 4.0, -2.0, 3.0};
    double b[] = {1.0, -7.0, 5.0};
    double expected[] = {1.454545, -4.636364, -3.363636};
    x = Gaussian_reduction_pivot(A, b, 3);
    ck_assert(compare_arr(x, expected, 3));
    free(x);
}
END_TEST

START_TEST(test_Gaussian_reduction_pivot_5_comma)
{
    double *x;
    //             x    y    z    t    f
    double A[] = {2.0, 1.0, 0.0, 0.0, 0.0,
                  0.0, 0.0, 0.0, -3.0, 1.0,
                  -5.0, 1.0, -4.0, 5.0, -1.0,
                  1.0, 2.0, -1.0, 3.0, 1.0,
                  0.0, 0.0, 5.0, 0.0, 3.0};
    double b[] = {4.0, 2.0, 10.0, -2.0, 1.0};
    double expected[] = {-5.58519, 15.1704, 5.86667, -3.81481, -9.4444};
    x = Gaussian_reduction_pivot(A, b, 5);
    ck_assert(compare_arr(x, expected, 5));
    free(x);
}
END_TEST

START_TEST(test_Gaussian_reduction_no_pivot_3_int)
{
    double *x;
    double A[] = {1.0, 3.0, -4.0, 3.0, 1.0, 2.0, 0.0, -2.0, 3.0};
    double b[] = {1.0, -7.0, 1.0};
    double expected[] = {6.0, -11.0, -7.0};
    x = Gaussian_reduction_no_pivot(A, b, 3);
    ck_assert(compare_arr(x, expected, 3));
    free(x);
}
END_TEST

START_TEST(test_Gaussian_reduction_no_pivot_3_comma)
{
    double *x;
    double A[] = {1.0, 3.0, -4.0, 3.0, 1.0, 2.0, 4.0, -2.0, 3.0};
    double b[] = {1.0, -7.0, 5.0};
    double expected[] = {1.454545, -4.636364, -3.363636};
    x = Gaussian_reduction_no_pivot(A, b, 3);
    ck_assert(compare_arr(x, expected, 3));
    free(x);
}
END_TEST

START_TEST(test_Gaussian_reduction_no_pivot_5_comma)
{
    double *x;
    //             x    y    z    t    f
    double A[] = {2.0, 1.0, 0.0, 0.0, 0.0,
                  0.0, 0.0, 0.0, -3.0, 1.0,
                  -5.0, 1.0, -4.0, 5.0, -1.0,
                  1.0, 2.0, -1.0, 3.0, 1.0,
                  0.0, 0.0, 5.0, 0.0, 3.0};
    double b[] = {4.0, 2.0, 10.0, -2.0, 1.0};
    double expected[] = {-5.58519, 15.1704, 5.86667, -3.81481, -9.4444};
    x = Gaussian_reduction_no_pivot(A, b, 5);
    ck_assert(compare_arr(x, expected, 5));
    free(x);
}
END_TEST

// START_TEST(test_Gaussian_reduction_pivot_5_int)
// {
//     double *x;
//     //             x    y    z    t    f
//     double A[] = {5.0, 4.0, 3.0, 2.0, 1.0,
//                   6.0, 7.0, 8.0, 9.0, 10.0,
//                   11.0, 12.0, 13.0, 14.0, 15.0,
//                   16.0, 17.0, 18.0, 19.0, 20.0,
//                   21.0, 22.0, 23.0, 24.0, 25.0};
//     double b[] = {4.0, 2.0, 10.0, -2.0, 1.0};
//     double expected[] = {-5.58519, -15.1704, 5.86667, -3.81481, -9.4444};
//     x = Gaussian_reduction_pivot(A, b, 5);
//     ck_assert(compare_arr(x, expected, 5));
//     free(x);
// }
// END_TEST

Suite *gaussian_reduction_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("gaussian_reduction");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_Gaussian_reduction_pivot_3_int);
    tcase_add_test(tc_core, test_Gaussian_reduction_pivot_3_comma);
    tcase_add_test(tc_core, test_Gaussian_reduction_pivot_5_comma);
    tcase_add_test(tc_core, test_Gaussian_reduction_no_pivot_3_int);
    tcase_add_test(tc_core, test_Gaussian_reduction_no_pivot_3_comma);
    tcase_add_test(tc_core, test_Gaussian_reduction_no_pivot_5_comma);
    //tcase_add_test(tc_core, test_Gaussian_reduction_pivot_5_int);

    suite_add_tcase(s, tc_core);

    return s;
}