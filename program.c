#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node{
    char data;
    struct Node* next;
};

struct Stack{
    struct Node* top;
};

//intitializing a new node
struct Node* new_node(char the_character){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node -> data = the_character;
    node -> next = NULL;

    return node;
}

struct Stack* create_stack(){
    struct Stack* stack = (struct Stack*)malloc((sizeof(struct Stack)));

    stack -> top = NULL;

    return stack;
}

int is_empty(struct Stack* stack){
    return stack -> top == NULL;
}

void push(struct Stack* stack, char the_character){
    struct Node* node = new_node(the_character);

    node -> next = stack -> top;
    stack -> top = node;
}

char pop(struct Stack* stack){

    if(is_empty(stack)){
        printf("Stack is empty\n");

        return '\0';
    }
    char data = stack -> top -> data;
    struct Node* temp = stack -> top;

    stack -> top = stack -> top -> next;
    free(temp);

    return data;
}

char peek(struct Stack* stack){
    if(is_empty(stack)){
        printf("Stack is empty\n");
        return '\0';

    }return stack -> top -> data;
}

int is_operator(char operator_){
    return operator_ == '+' || operator_ == '-' || operator_ == '*' || operator_ == '/' || operator_ == '%';

}

int get_precedence(char operator_){
    switch (operator_) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return -1; // Invalid operator
    }
}

void infix_to_postfix(char* infix, char* postfix){
    struct Stack* stack = create_stack();

    int i, k;

    for(i = 0, k = -1; infix[i]; ++i){
        if(isalnum(infix[i])){
            postfix[++k] = infix[i];
        }else if(infix[i] == '('){
            push(stack, infix[i]);
        }else if(infix[i] == ')'){
            while (!is_empty(stack) && peek(stack) != '('){
                postfix[++k] = pop(stack);
            }
            if (!is_empty(stack) && peek(stack) == '('){
                pop(stack);
            }else{
                printf("Invalid Expression\n");
                return;
            }
        }else if(is_operator(infix[i])){
            while(!is_empty(stack) && get_precedence(infix[i]) <= get_precedence(stack)){
                postfix[++k] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }
    while(!is_empty(stack)){
        if(peek(stack) == '('){
            printf("Invalid Expression\n");
            return;
        }
        postfix[++k] = pop(stack);
    }
    postfix[++k] = '\0';
}

int main(){
    char infix[100];
    char postfix[100];

    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strlen(infix) - 1] = '\0';

    infix_to_postfix(infix, postfix);
    if(strcmp(postfix, "") != 0){
        printf("Postfix expression: %s\n", postfix);
    }
    return 0;
}
