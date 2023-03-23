/*
* This code is based on C# code from this site:
* https://refactoring.guru/design-patterns/command/csharp/example
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct ICommand ICommand;
typedef struct Receiver Receiver;
typedef struct SimpleCommand SimpleCommand;
typedef struct ComplexCommand ComplexCommand;

/*****************************************************
* Interface
******************************************************/
struct ICommand {
    void (*execute)(ICommand *);
};

void Execute(ICommand *me){
    me->execute(me);
}

/*****************************************************
* Class
******************************************************/
struct Receiver {
    void (*doSomething)(Receiver *, char *);
    void (*doSomethingElse)(Receiver *, char *);
};


void Receiver_ctor(Receiver *me, void (*doSomething)(Receiver *, char *), void (*doSomethingElse)(Receiver *, char *) ){
    me->doSomething = doSomething;
    me->doSomethingElse = doSomethingElse;
}

void Receiver_doSomething(Receiver *me, char *a) {
    printf("Receiver: Working on (%s).\n", a);
}

void Receiver_doSomethingElse(Receiver *me, char *b) {
    printf("Receiver: Also working on (%s).\n", b);
}

/*****************************************************
* Class
******************************************************/

struct SimpleCommand {
    ICommand base;
    char* payload;
};

void SimpleCommand_execute(ICommand *command) {
    SimpleCommand *me = (SimpleCommand *)command;
    printf("SimpleCommand: See, I can do simple things like printing (%s)\n", me->payload);
}

void SimpleCommand_ctor(SimpleCommand *me,char *payload) {
    me->base.execute = SimpleCommand_execute;
    me->payload = payload;
}

/*****************************************************
* Class
******************************************************/
struct ComplexCommand {
    ICommand base;
    Receiver *receiver;
    char *a;
    char *b;
};

void ComplexCommand_execute(ICommand *command) {
    ComplexCommand *me = (ComplexCommand*)command;
    printf("ComplexCommand: Complex stuff should be done by a receiver object.\n");
    me->receiver->doSomething(me->receiver, me->a);
    me->receiver->doSomethingElse(me->receiver, me->b);
}

void ComplexCommand_ctor(ComplexCommand *me, Receiver *receiver, char *a, char *b){
    me->base.execute = ComplexCommand_execute;
    me->receiver = receiver;
    me->a = a;
    me->b = b;
}

int main() {

    Receiver *receiver = malloc( sizeof(Receiver) );
    Receiver_ctor(receiver,Receiver_doSomething,Receiver_doSomethingElse);

    SimpleCommand  *simpleCommand =  malloc(sizeof(SimpleCommand));
    SimpleCommand_ctor(simpleCommand,"Say Hi!");

    ComplexCommand *complexCommand = (ComplexCommand*)malloc(sizeof(ComplexCommand));
    ComplexCommand_ctor(complexCommand, receiver, "Send email", "to John");

    ICommand* commands[2] = {(ICommand *) simpleCommand, (ICommand *)complexCommand};

    for (int i = 0; i < 2; i++) {
       Execute(commands[i]);
    }

    free(simpleCommand);
    free(complexCommand);
    free(receiver);

    return 0;
}
