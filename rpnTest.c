#include "rpn.h"
#include "expr_assert.h"

void test_evaluate_function_should_return_the_result_of_the_add_expression(){
	char *expression = "2 3 +\0";
	int result = evaluate(expression);
	assertEqual(result, 5);
}
void test_evaluate_function_should_return_the_result_of_the_sub_expression(){
	char *expression = "2 3 -\0";
	int result = evaluate(expression);
	assertEqual(result, -1);
}
void test_evaluate_function_should_return_the_result_of_the_mul_expression(){
	char *expression = "2 3 *\0";
	int result = evaluate(expression);
	assertEqual(result, 6);
}
void test_evaluate_function_should_return_the_result_of_the_div_expression(){
	char *expression = "2 2 /\0";
	int result = evaluate(expression);
	assertEqual(result, 1);
}
void test_evaluate_function_should_return_the_result_of_expressions_with_multiple_operands(){
	char *expression = "2 3 4 5 + * -\0";
	int result = evaluate(expression);
	assertEqual(result, -25);
}

