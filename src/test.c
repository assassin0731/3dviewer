#include <check.h>
#include <stdlib.h>

#include "C-files/myMain.h"

#define eps 0.000001

START_TEST(test_1) {
    Elements elements;
    myMain(&elements, "Models/file.obj");
    int real_index[48] = {1,2,2,3,3,1,3,2,2,4,4,3,3,4,4,5,5,3,5,4,4,6,6,5,
        5,6,6,7,7,5,7,6,6,8,8,7,7,8,8,1,1,7,1,8,8,2,2,1};
    double real_vertex[24] = {-0.500000, -0.500000, 0.500000,
        0.500000, -0.500000, 0.500000,
        -0.500000, 0.500000, 0.500000,
        0.500000, 0.500000, 0.500000,
        -0.500000, 0.500000, -0.500000,
        0.500000, 0.500000, -0.500000,
        -0.500000, -0.500000, -0.500000,
        0.500000, -0.500000, -0.500000,
    };
    ck_assert_int_eq(elements.vertex_counter, 8);
    ck_assert_int_eq(elements.index_counter, 36);
    for (int i = 0; i < 48; i++) {
        ck_assert_int_eq(elements.index[i], real_index[i] - 1);
    }
    for (int i = 0; i < 24; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_2) {
    Elements elements;
    myMain(&elements, "Models/fole1.obj");
    int real_index[10] = {1,2,2,3,3,4,4,1,1,5};
    double real_vertex[10] = {-0.500000, -0.500000, 0.500000,
        0.500000, -0.500000, 0.500000,
        -0.500000, 0.500000, 0.500000,
        0.500000
    };
    ck_assert_int_eq(elements.vertex_counter, 8);
    ck_assert_int_eq(elements.index_counter, 16);
    for (int i = 0; i < 10; i++) {
        ck_assert_int_eq(elements.index[i], real_index[i] - 1);
    }
    for (int i = 0; i < 10; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_3) {
    Elements elements;
    myMain(&elements, "Models/heart.obj");
    int real_index[10] = {1, 2, 2, 3, 3, 4, 4, 1, 5, 6};
    double real_vertex[10] = {-5.7868, -2.8897, 6.9550,
        -5.8939, -2.7443, 6.7745,
        -5.4647, -2.7112, 6.3057,
        -5.3747
    };
    ck_assert_int_eq(elements.vertex_counter, 5634);
    for (int i = 0; i < 10; i++) {
        ck_assert_int_eq(elements.index[i], real_index[i] - 1);
    }
    for (int i = 0; i < 10; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_4) {
    Elements elements;
    myMain(&elements, "Models/luster.obj");
    int real_index[10] = {1, 2, 2, 3, 3, 4, 4, 1, 2, 5};
    double real_vertex[10] = {-168.6158, -9350.9287, 9.8047,
        -167.7503, -9350.9287, 15.2691,
        -167.6017, -9344.4023, 15.2691,
        -168.4663
    };
    ck_assert_int_eq(elements.vertex_counter, 59947);
    for (int i = 0; i < 10; i++) {
        ck_assert_int_eq(elements.index[i], real_index[i] - 1);
    }
    for (int i = 0; i < 10; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_5) {
    Elements elements;
    myMain(&elements, "Models/file.obj");
    double real_vertex[24] = {-0.600000, -0.600000, 0.600000,
        0.600000, -0.600000, 0.600000,
        -0.600000, 0.600000, 0.600000,
        0.600000, 0.600000, 0.600000,
        -0.600000, 0.600000, -0.600000,
        0.600000, 0.600000, -0.600000,
        -0.600000, -0.600000, -0.600000,
        0.600000, -0.600000, -0.600000
    };
    ScalingC(&elements, 1.2);
    for (int i = 0; i < 24; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_6) {
    Elements elements;
    myMain(&elements, "Models/file.obj");
    double real_vertex[24] = {-0.400000, -0.400000, 0.400000,
        0.400000, -0.400000, 0.400000,
        -0.40000, 0.40000, 0.40000,
        0.40000, 0.400000, 0.400000,
        -0.40000, 0.400000, -0.40000,
        0.400000, 0.400000, -0.400000,
        -0.400000, -0.40000, -0.400000,
        0.400000, -0.400000, -0.40000
    };
    ScalingC(&elements, 0.8);
    for (int i = 0; i < 24; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_7) {
    Elements elements;
    myMain(&elements, "Models/file.obj");
    double real_vertex[24] = {-0.28800000, -0.288, 0.288,
        0.288, -0.288, 0.288,
        -0.288, 0.288, 0.288,
        0.288, 0.288, 0.288,
        -0.288, 0.2880, -0.288,
        0.2880, 0.28800, -0.288,
        -0.288, -0.288, -0.288,
        0.288, -0.288, -0.288
    };
    ScalingC(&elements, 0.8);
    ScalingC(&elements, 0.4);
    ScalingC(&elements, 1.8);
    for (int i = 0; i < 24; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_8) {
    Elements elements;
    myMain(&elements, "Models/file.obj");
    double real_vertex[24] = {19.500000, -0.500000, 0.500000,
        20.500000, -0.500000, 0.500000,
        19.50000, 0.50000, 0.50000,
        20.50000, 0.500000, 0.500000,
        19.50000, 0.500000, -0.50000,
        20.500000, 0.500000, -0.500000,
        19.500000, -0.50000, -0.500000,
        20.500000, -0.500000, -0.50000
    };
    MovingC(&elements, 20, 0 , 0);
    for (int i = 0; i < 24; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_9) {
    Elements elements;
    myMain(&elements, "Models/file.obj");
    double real_vertex[24] = {-0.500000, -10.500000, 0.500000,
        0.500000, -10.500000, 0.500000,
        -0.500000, -9.500000, 0.500000,
        0.500000, -9.500000, 0.500000,
        -0.500000, -9.500000, -0.500000,
        0.500000, -9.500000, -0.500000,
        -0.500000, -10.500000, -0.500000,
        0.500000, -10.500000, -0.500000,
    };
    MovingC(&elements, 0, -10 , 0);
    for (int i = 0; i < 24; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_10) {
    Elements elements;
    myMain(&elements, "Models/file.obj");
    double real_vertex[24] = {-0.500000, -0.500000, 0.500000,
        0.500000, -0.500000, 0.500000,
        -0.500000, 0.500000, 0.500000,
        0.500000, 0.500000, 0.500000,
        -0.500000, 0.500000, -0.500000,
        0.500000, 0.500000, -0.500000,
        -0.500000, -0.500000, -0.500000,
        0.500000, -0.500000, -0.500000,
    };
    MovingC(&elements, 0, 0 , 0);
    for (int i = 0; i < 24; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_11) {
    Elements elements;
    myMain(&elements, "Models/file.obj");
    double real_vertex[24] = {3.500000, 0.500000, -2.500000,
        4.500000, 0.500000, -2.500000,
        3.500000, 1.500000, -2.500000,
        4.500000, 1.500000, -2.500000,
        3.500000, 1.500000, -3.500000,
        4.500000, 1.500000, -3.500000,
        3.500000, 0.500000, -3.500000,
        4.500000, 0.500000, -3.500000,
    };
    MovingC(&elements, 1, 2 , 1);
    MovingC(&elements, -2, 3 , 2);
    MovingC(&elements, 5, -4 , -6);
    for (int i = 0; i < 24; i++) {
        ck_assert_double_eq_tol(elements.vertex[i], real_vertex[i], eps);
    }
    free(elements.vertex);
    free(elements.index);
}
END_TEST

START_TEST(test_12) {
    Elements elements;
    myMain(&elements, "Models/file.obj");
    double real_x = -0.112791, real_y = -0.853764, real_z = -0.0914633;
    RotationC(&elements, 30./57.3, 30./57.3, 30./57.3);
    ck_assert_double_eq_tol(elements.vertex[0], real_x, eps);
    ck_assert_double_eq_tol(elements.vertex[1], real_y, eps);
    ck_assert_double_eq_tol(elements.vertex[2], real_z, eps);
    free(elements.vertex);
    free(elements.index);
}
END_TEST


int main() {
  Suite *s1 = suite_create("s21_viewer: ");
  TCase *tc1_1 = tcase_create("s21_viewer: ");
  SRunner *sr = srunner_create(s1);
  int result;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, test_1);
    tcase_add_test(tc1_1, test_2);
    tcase_add_test(tc1_1, test_3);
    tcase_add_test(tc1_1, test_4);
    tcase_add_test(tc1_1, test_5);
    tcase_add_test(tc1_1, test_6);
    tcase_add_test(tc1_1, test_7);
    tcase_add_test(tc1_1, test_8);
    tcase_add_test(tc1_1, test_9);
    tcase_add_test(tc1_1, test_10);
    tcase_add_test(tc1_1, test_11);
    tcase_add_test(tc1_1, test_12);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}
