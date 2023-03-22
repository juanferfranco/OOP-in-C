/*
* This code is based on C# code from this site:
* https://refactoring.guru/design-patterns/command/csharp/example
* I asked for BingChat to generate the C code using this prompt:
* Please write the next code in C language: C# code
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
    void (*execute)(ICommand*);
};

/*****************************************************
* Class
******************************************************/
struct Receiver {
    void (*doSomething)(Receiver*, char*);
    void (*doSomethingElse)(Receiver*, char*);
};

void Receiver_doSomething(Receiver* self, char* a) {
    printf("Receiver: Working on (%s).\n", a);
}

void Receiver_doSomethingElse(Receiver* self, char* b) {
    printf("Receiver: Also working on (%s).\n", b);
}

/*****************************************************
* Class
******************************************************/
struct SimpleCommand {
    ICommand base;
    char* payload;
};

void SimpleCommand_execute(ICommand* command) {
    SimpleCommand* self = (SimpleCommand*)command;
    printf("SimpleCommand: See, I can do simple things like printing (%s)\n", self->payload);
}

/*****************************************************
* Class
******************************************************/
struct ComplexCommand {
    ICommand base;
    Receiver* receiver;
    char* a;
    char* b;
};

void ComplexCommand_execute(ICommand* command) {
    ComplexCommand* self = (ComplexCommand*)command;
    printf("ComplexCommand: Complex stuff should be done by a receiver object.\n");
    self->receiver->doSomething(self->receiver, self->a);
    self->receiver->doSomethingElse(self->receiver, self->b);
}

SimpleCommand* SimpleCommand_new(char* payload) {
    SimpleCommand* self = (SimpleCommand*)malloc(sizeof(SimpleCommand));
    self->base.execute = SimpleCommand_execute;
    self->payload = payload;
    return self;
}

ComplexCommand* ComplexCommand_new(Receiver* receiver, char* a, char* b) {
    ComplexCommand* self = (ComplexCommand*)malloc(sizeof(ComplexCommand));
    self->base.execute = ComplexCommand_execute;
    self->receiver = receiver;
    self->a = a;
    self->b = b;
    return self;
}

int main() {
    Receiver* receiver = (Receiver*)malloc(sizeof(Receiver));
    receiver->doSomething = Receiver_doSomething;
    receiver->doSomethingElse = Receiver_doSomethingElse;

    SimpleCommand* simpleCommand = SimpleCommand_new("Say Hi!");
    ComplexCommand* complexCommand = ComplexCommand_new(receiver, "Send email", "to John");

    ICommand* commands[2];
    commands[0] = &simpleCommand->base;
    commands[1] = &complexCommand->base;

    for (int i = 0; i < 2; i++) {
        commands[i]->execute(commands[i]);
    }

    free(simpleCommand);
    free(complexCommand);
    free(receiver);

    return 0;
}
