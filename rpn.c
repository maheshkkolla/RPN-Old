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
// 	int *operand, answer;
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
// 				case '+': answer = (num2 + num1); break;
// 				case '-': answer = (num2 - num1); break;
// 				case '*': answer = (num2 * num1); break;
// 				case '/': answer = (num2 / num1); break;
// 				break;
// 			}
// 		}
// 		free(c);
// 	}
// 	return answer;
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
	int answer;
	switch(*operator){
		case '+': answer = (operands[1] + operands[0]); break;
		case '-': answer = (operands[1] - operands[0]); break;
		case '*': answer = (operands[1] * operands[0]); break;
		case '/': answer = (operands[1] / operands[0]); break;
	}
	return answer;
}

void performOperations(char *c, Stack *stack) {
	int *answer = malloc(sizeof(int));
	int *operands;
	if(*c >= '0' && *c <= '9'){
		pushOperand(stack,c);	
	} else if(!isspace(*c)){
		operands = popTwoOperands(stack);
		*answer = calculate(c,operands);
		push(stack, answer);	
	}
}

int countOfOperands(char *expression) {
	int i, count = 0;
	for (i = 0; i < strlen(expression); ++i) {
		char *token;
		stringAtIndex(expression, &token, i);
		(*token >= '0' && *token <= '9') && count++;
	}
	return count;
}

int arrayIndexOf(char token, char *array) {
	int index = -1, i;
	for (i = 0; i < strlen(array); ++i) {
		(token == array[i]) && (index = i);
	}
	return index;
}

int countOfOperators(char *expression) {
	int i, count = 0;
	char *allOperators = "+-*/";
	for (i = 0; i < strlen(expression); ++i) {
		char *token;
		stringAtIndex(expression, &token, i);
		(arrayIndexOf(token[0], allOperators) >= 0) && count++;
	}
	return count;
}

int isError(char *expression, Status *status) {
	int operandsCount = countOfOperands(expression);
	int operatorsCount = countOfOperators(expression);
	int error = (operandsCount != (operatorsCount + 1));
	error && (status->error = 1);
	return error;
}

Status evaluate(char *expression) {
	Stack stack = createStack();
	int i, count = strlen(expression);
	Status status = {0,0};
	if(isError(expression, &status))return status;
	for (i = 0; i < count; ++i) {
		char *c;
		stringAtIndex(expression, &c, i);
		performOperations(c,&stack);
	}
	status.result = *(int *)pop(&stack);
	return status;
}
