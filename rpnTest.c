#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>
#include <string.h>

void test_evaluate_function_should_return_the_answer_of_the_add_expression(){
	char *expression = "2 3 +\0";
	Status answer = evaluate(expression);
	assertEqual(answer.result, 5);
	assertEqual(answer.error, 0);
}
void test_evaluate_function_should_return_the_answer_of_the_sub_expression(){
	char *expression = "2 3 -\0";
	Status answer = evaluate(expression);
	assertEqual(answer.result, -1);
	assertEqual(answer.error, 0);
}
void test_evaluate_function_should_return_the_answer_of_the_mul_expression(){
	char *expression = "2 3 *\0";
	Status answer = evaluate(expression);
	assertEqual(answer.error, 0);
	assertEqual(answer.result, 6);
}
void test_evaluate_function_should_return_the_answer_of_the_div_expression(){
	char *expression = "2 2 /\0";
	Status answer = evaluate(expression);
	assertEqual(answer.error, 0);
	assertEqual(answer.result, 1);
}
void test_evaluate_function_should_return_the_answer_of_expressions_with_multiple_operands(){
	char *expression = "2 3 4 5 + * -\0";
	Status answer = evaluate(expression);
	assertEqual(answer.error, 0);
	assertEqual(answer.result, -25);
}

void test_evaluate_should_return_the_answer_for_complex_expressions(){
	char *expression = "2 2 2 * 2 - 3 + +";
	Status answer = evaluate(expression);
	assertEqual(answer.error, 0);
	assertEqual(answer.result, 7);
}

void test_evaluate_should_return_20_for_the_complex_multiplication_expression(){
	char *expression = "2 2 2 2 2 * * 2 + + 2 - *";
	Status answer = evaluate(expression);
	assertEqual(answer.error, 0);
	assertEqual(answer.result, 20);
}

void test_evaluate_should_gives_the_error_if_there_is_more_operators_than_operands(){
	char *expression = "2 2 + +";
	Status status = evaluate(expression);
	assertEqual(status.error, 1);
}

void test_infixToPostfix_takes_the_simple_infix_expression_and_gives_as_postfix_expression() {
	char *expression = "3 + 4";
	char *postfixExpression = infixToPostfix(expression);
	assertEqual(strcmp(postfixExpression, "3 4 +"),0);
}

void test_infixToPostfix_takes_the_infix_expression_and_gives_as_postfix_expression() {
	char *expression = "3 + 4 * 2 / ( 1 - 5 ) ";
	char *postfixExpression = infixToPostfix(expression);
	assertEqual(strcmp(postfixExpression, "3 4 2 * 1 5 - / +"),0);
}