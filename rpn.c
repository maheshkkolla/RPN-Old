#include "rpn.h"
#include "linkedList.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// int evaluate(char *expression) {
// 	Stack stack = createStack();
// 	int i, count = strlen(expression);
// 	int *operand, result;
// 	for (i = 0; i < count; ++i) {
// 		char *c = malloc(sizeof(char)*2); 
// 		*c = expression[i];
// 		c[1] = '\0';
// 		if(*c >= '0' && *c <= '9'){
// 			operand = malloc(sizeof(int));
// 			*operand = atoi(c);
// 			push(&stack, operand);
// 		} else if(!isspace(*c)){
// 			int num1 = *(int *)pop(&stack);
// 			int num2 = *(int *)pop(&stack);
// 			switch(*c){
// 				case '+': result = (num2 + num1); break;
// 				case '-': result = (num2 - num1); break;
// 				case '*': result = (num2 * num1); break;
// 				case '/': result = (num2 / num1); break;
// 				break;
// 			}
// 		}
// 		free(c);
// 	}
// 	return result;
// }

void stringAtIndex(char *expression,char **token, int index) {
	*token = malloc(sizeof(char)*2); 
	**token = expression[index];
	token[0][1] = '\0';
}

void pushOperand(Stack *stack, char *c){
	int *operand = malloc(sizeof(int));
	*operand = atoi(c);
	push(stack, operand);
}

int *popTwoOperands(Stack *stack) {
	int *operands = malloc(sizeof(int)*2);
	operands[0] = *(int *)pop(stack);
	operands[1] = *(int *)pop(stack);
	return operands;
}

int calculate(char *operator, int *operands){
	int result;
	switch(*operator){
		case '+': result = (operands[1] + operands[0]); break;
		case '-': result = (operands[1] - operands[0]); break;
		case '*': result = (operands[1] * operands[0]); break;
		case '/': result = (operands[1] / operands[0]); break;
	}
	return result;
}

void performOperations(char *c, Stack *stack) {
	int *result = malloc(sizeof(int));
	int *operands;
	if(*c >= '0' && *c <= '9'){
		pushOperand(stack,c);	
	} else if(!isspace(*c)){
		operands = popTwoOperands(stack);
		*result = calculate(c,operands);
		push(stack, result);	
	}
}

int evaluate(char *expression) {
	Stack stack = createStack();
	int i, count = strlen(expression);
	int result;
	for (i = 0; i < count; ++i) {
		char *c;
		stringAtIndex(expression, &c, i);
		performOperations(c,&stack);
	}
	result = *(int *)pop(&stack);
	return result;
}
