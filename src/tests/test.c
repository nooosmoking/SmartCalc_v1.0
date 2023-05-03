#include "test.h"

START_TEST(val_test1) {
  char str[] = "((cos(x)+0.853))";
  string inp = {str, 16};
  char res_str[] = "((c(x)+0.853))";
  int res_len = 14;
  int err = 0;
  double res = 0;
  int x = 1;
  double true = 1.3933023058681397;

  inp = validation(inp, &err);
  res = calc(inp, x);

  ck_assert_int_eq(strcmp(inp.str, res_str), 0);
  ck_assert_int_eq(inp.len, res_len);
  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(res, true, TEST_EPS);
}
END_TEST

START_TEST(val_test2) {
  char str[] = "((css(1)+0.853))";
  string inp = {str, 16};
  int err = 0;

  inp = validation(inp, &err);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(val_test3) {
  char str[] = "((cos(1)+0.853)))";
  string inp = {str, 17};
  int err = 0;

  inp = validation(inp, &err);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(val_test4) {
  char str[] = "( (sin(1) + 0.853) )";
  string inp = {str, 20};
  char res_str[] = "((s(1)+0.853))";
  int res_len = 14;
  int err = 0;
  double res = 0;
  double true = 1.6944709848078965;

  inp = validation(inp, &err);
  res = calc(inp, 0);

  ck_assert_int_eq(strcmp(inp.str, res_str), 0);
  ck_assert_int_eq(inp.len, res_len);
  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(res, true, TEST_EPS);
}
END_TEST

START_TEST(val_test5) {
  char str[] = " +( (cos(log(-1 + 777.777 )+.853) - 865.))";
  string inp = {str, 42};
  int res_len = 33;
  int err = 0;
  double res = 0;
  double true = -865.824372433783;

  inp = validation(inp, &err);
  res = calc(inp, 0);

  ck_assert_int_eq(inp.len, res_len);
  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(res, true, TEST_EPS);
}
END_TEST

START_TEST(val_test6) {
  char str[] = " +( (cos(log(-1 / .777.777 )+.853) - 865.))";
  string inp = {str, 43};
  int err = 0;

  inp = validation(inp, &err);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(val_test7) {
  char str[] = " +( (asin((ln(+.1 ^ .777777 ) + 5)mod 2-1) - 865.))";
  string inp = {str, 51};
  int res_len = 37;
  int err = 0;
  double res = 0;
  double true = -864.7893431503167;

  inp = validation(inp, &err);
  res = calc(inp, 0);

  ck_assert_int_eq(inp.len, res_len);
  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(res, true, TEST_EPS);
}
END_TEST

START_TEST(val_test8) {
  char str[] = "sqrt((6^atan(9))*9)";
  string inp = {str, 19};
  char res_str[] = "q((6^u(9))*9)";
  int res_len = 13;
  int err = 0;
  double res = 0;
  double true = 11.097516262125971;

  inp = validation(inp, &err);
  res = calc(inp, 0);

  ck_assert_int_eq(strcmp(inp.str, res_str), 0);
  ck_assert_int_eq(inp.len, res_len);
  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(res, true, TEST_EPS);
}
END_TEST

START_TEST(val_test9) {
  char str[] = "sqrt((6^atan())*9)";
  string inp = {str, 18};
  int err = 0;

  inp = validation(inp, &err);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(val_test10) {
  char str[] = "((css(1)+  0.853))";
  string inp = {str, 18};
  int err = 0;

  inp = validation(inp, &err);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(val_test11) {
  char str[] = "(6+3)(7-9)";
  string inp = {str, 10};
  int err = 0;

  inp = validation(inp, &err);

  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(val_test12) {
  char str[] = "tan (6)";
  string inp = {str, 7};
  char res_str[] = "t(6)";
  int res_len = 4;
  int err = 0;
  double res = 0;
  double true = -0.29100619138474915;

  inp = validation(inp, &err);
  res = calc(inp, 0);

  ck_assert_int_eq(strcmp(inp.str, res_str), 0);
  ck_assert_int_eq(inp.len, res_len);
  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(res, true, TEST_EPS);
}

START_TEST(val_test13) {
  char str[] = "sqrt )6)";
  string inp = {str, 8};
  int err = 0;

  inp = validation(inp, &err);

  ck_assert_int_eq(err, 1);
}

START_TEST(val_test14) {
  char str[] = "*sqrt(6)";
  string inp = {str, 8};
  int err = 0;

  inp = validation(inp, &err);

  ck_assert_int_eq(err, 1);
}

START_TEST(val_test15) {
  char str[] = "sqrt(6)mod";
  string inp = {str, 10};
  int err = 0;

  inp = validation(inp, &err);

  ck_assert_int_eq(err, 1);
}

START_TEST(val_test16) {
  char str[] = "acos(sin(3))";
  string inp = {str, 12};
  char res_str[] = "a(s(3))";
  int res_len = 7;
  int err = 0;
  double res = 0;
  double true = 1.4292036732051034;

  inp = validation(inp, &err);
  res = calc(inp, 0);

  ck_assert_int_eq(strcmp(inp.str, res_str), 0);
  ck_assert_int_eq(inp.len, res_len);
  ck_assert_int_eq(err, 0);
  ck_assert_double_eq_tol(res, true, TEST_EPS);
}

Suite *suite_s21_validate(void) {
  Suite *suite = suite_create("=== VALIDATE  TEST ===");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, val_test1);
  tcase_add_test(tc, val_test2);
  tcase_add_test(tc, val_test3);
  tcase_add_test(tc, val_test4);
  tcase_add_test(tc, val_test5);
  tcase_add_test(tc, val_test6);
  tcase_add_test(tc, val_test7);
  tcase_add_test(tc, val_test8);
  tcase_add_test(tc, val_test9);
  tcase_add_test(tc, val_test10);
  tcase_add_test(tc, val_test11);
  tcase_add_test(tc, val_test12);
  tcase_add_test(tc, val_test13);
  tcase_add_test(tc, val_test14);
  tcase_add_test(tc, val_test15);
  tcase_add_test(tc, val_test16);

  suite_add_tcase(suite, tc);

  return suite;
}