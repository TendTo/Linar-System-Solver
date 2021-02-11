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

START_TEST(test_Gaussian_reduction_pivot_10)
{
    double *x;
    double U[110];
    for (int i = 109; i >= 0; --i)
        U[i] = i * i - 2 * i - 1000 + i % 4 * 5 - i % 5 * i;
    double expected[] = {1.89524, -1.09934, 1.89551, 0.48337, -4.31887, -0.45298, 1.11972, -1.76043, -0.56855, 3.83117};
    x = Gaussian_reduction_pivot(U, NULL, 10);
    ck_assert(compare_arr(x, expected, 10));
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

START_TEST(test_Gaussian_reduction_no_pivot_10)
{
    double *x;
    double U[110];
    for (int i = 109; i >= 0; --i)
        U[i] = i * i - 2 * i - 1000 + i % 4 * 5 - i % 5 * i;
    double expected[] = {1.89524, -1.09934, 1.89551, 0.48337, -4.31887, -0.45298, 1.11972, -1.76043, -0.56855, 3.83117};
    x = Gaussian_reduction_no_pivot(U, NULL, 10);
    ck_assert(compare_arr(x, expected, 10));
    free(x);
}
END_TEST

START_TEST(test_Gaussian_reduction_no_pivot_gpu_3)
{
    double *x;
    double A[] = {1.0, 3.0, -4.0, 3.0, 1.0, 2.0, 0.0, -2.0, 3.0};
    double b[] = {1.0, -7.0, 1.0};
    double expected[] = {6.0, -11.0, -7.0};
    cl_status status;
    clCreateStatus(&status, "src/ocl/gaussian_reduction.ocl");
    x = Gaussian_reduction_no_pivot_gpu_naive(A, b, 3, &status);
    ck_assert(compare_arr(x, expected, 3));
    clFreeStatus(&status);
    free(x);
}
END_TEST

START_TEST(test_Gaussian_reduction_no_pivot_gpu_10)
{
    double *x;
    double U[110];
    for (int i = 109; i >= 0; --i)
        U[i] = i * i - 2 * i - 1000 + i % 4 * 5 - i % 5 * i;
    double expected[] = {1.89524, -1.09934, 1.89551, 0.48337, -4.31887, -0.45298, 1.11972, -1.76043, -0.56855, 3.83117};
    cl_status status;
    clCreateStatus(&status, "src/ocl/gaussian_reduction.ocl");
    x = Gaussian_reduction_no_pivot_gpu_naive(U, NULL, 10, &status);
    ck_assert(compare_arr(x, expected, 10));
    clFreeStatus(&status);
    free(x);
}
END_TEST

Suite *gaussian_reduction_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("gaussian_reduction");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_Gaussian_reduction_pivot_3_int);
    tcase_add_test(tc_core, test_Gaussian_reduction_pivot_3_comma);
    tcase_add_test(tc_core, test_Gaussian_reduction_pivot_5_comma);
    tcase_add_test(tc_core, test_Gaussian_reduction_pivot_10);
    tcase_add_test(tc_core, test_Gaussian_reduction_no_pivot_3_int);
    tcase_add_test(tc_core, test_Gaussian_reduction_no_pivot_3_comma);
    tcase_add_test(tc_core, test_Gaussian_reduction_no_pivot_10);
    tcase_add_test(tc_core, test_Gaussian_reduction_no_pivot_gpu_3);
    tcase_add_test(tc_core, test_Gaussian_reduction_no_pivot_gpu_10);

    suite_add_tcase(s, tc_core);

    return s;
}