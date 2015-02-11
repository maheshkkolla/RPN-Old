#include "rpn.h"
#include "linkedList.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "queue.h"

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


int isOperand(char *token){
	return(*token >= '0' && *token <= '9');
}

int isOperator(char *token){
	int i, operatorFlag = 0;
	char *allOperators = "+-*/^()";
	for (i = 0; i < strlen(allOperators); ++i) {
		(*token == allOperators[i])  && (operatorFlag = 1);
	}
	return operatorFlag;
}

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
	if(isOperand(c)){
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

int countOfOperators(char *expression) {
	int i, count = 0;
	for (i = 0; i < strlen(expression); ++i) {
		char *token;
		stringAtIndex(expression, &token, i);
		(isOperator(token)) && count++;
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

void insertOperatorsInStackToQueue(Stack *stack, Queue *outputQueue) {
	// int i;
	// for (i = 0; i < stack->count; ++i) {
	// 	enQueue(outputQueue, pop(stack));
	// }
	while(stack->top != NULL){
		enQueue(outputQueue, pop(stack));
	}
}

void queueToString(Queue *outputQueue, char *expression) {
	while(outputQueue->head != NULL){
		strcat(expression, (char *)deQueue(outputQueue));
		if(outputQueue->head != NULL)strcat(expression," ");
	}
}

int arrayIndexOf(char *array, char *token) {
	int i;
	for (i = 0; i < strlen(array); ++i) {
		if(token[0] == array[i]) return i;
	}
	return -1;
}

void pushOperator(Stack *stack, char *token, Queue *queue) {
	char *operators = ")-+*/^\0";
	char *precedence = "011223\0";
	if(stack->top == NULL) push(stack, token);
	else {
		printf("-------Top is Not Null\n");
		printf("-------Precedence of token %c is %d ",token[0],precedence[arrayIndexOf(operators,token)]-48);
		printf("-------Precedence of top stack %s is %d ",stack->top->data,precedence[arrayIndexOf(operators,stack->top->data)]-48);
		if(token[0] == '('){
			push(stack,token);
		} else {
			if(precedence[arrayIndexOf(operators,token)]-48 > precedence[arrayIndexOf(operators,stack->top->data)]-48) {
				printf("-------Inside If pushing to stack\n");
				push(stack, token);
			} else{
				printf("Inside else \n");
				while(precedence[arrayIndexOf(operators,token)]-48 <= precedence[arrayIndexOf(operators,stack->top->data)]-48){
					printf("---------Poping the Stack\n");
					printf("stack Top--> %s\n", stack->top->data);
					enQueue(queue, pop(stack));
					if(stack->top == NULL) break;
				}
				if(token[0] == ')'){
					pop(stack);
				} else push(stack,token);
			}
		}
	}	
}

char *infixToPostfix(char * expression) {
	int i;
	char *outputExpression = calloc(sizeof(char),strlen(expression));
	Queue outputQueue = createQueue();
	Stack stack = createStack();
	for (i = 0; i < strlen(expression); ++i) {
		char *token;
		stringAtIndex(expression, &token, i);
		printf("--------Expression token %s\n", token);
		if(isOperand(token)) enQueue(&outputQueue, token);
		if(isOperator(token)) pushOperator(&stack, token, &outputQueue);
	}
	insertOperatorsInStackToQueue(&stack,&outputQueue);
	queueToString(&outputQueue, outputExpression);
	printf("-------->[%s]\n",outputExpression);
	return outputExpression;
}