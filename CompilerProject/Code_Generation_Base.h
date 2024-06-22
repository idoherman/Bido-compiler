#include "Parser.h"
// REGISTERS

#define NUM_OF_REGISTERS 4


// The registers used for some arithmetic operations (because they're the default result registers)
#define AX "ax"
#define BX "bx"
#define CX "cx"
#define DX "dx"

#define REGISTER_NAME_LENGTH 3

typedef enum In_Use {
    NOT_IN_USE,
    IN_USE
} In_Use;

typedef struct Register
{
    char name[REGISTER_NAME_LENGTH]; // The register's name
    In_Use in_use;     // Is the register in use? -> 1 is in use, 0 is not in use.
    int last_use;
} Register;

Register init_register(char* name);
Register* init_free_registers();
Register get_reg(Register* registers);



// The format of a lable.
// Expecting label number for the %d.
#define LABEL_FORMAT "$$L%d"
// The maximum length of lables's name
#define LABEL_NAME_LENGTH 8


#define MOV "\tmov %s, %s\n"
// Control flow
#define CMP "\tcmp %s, %s\n"
#define LABEL "%s:\n"
#define JMP "\tjmp %s\n"
#define JE "\tje %s\n"
#define JNE "\tjne %s\n"
#define JG "\tjg %s\n"
#define JGE "\tjge %s\n"
#define JL "\tjl %s\n"
#define JLE "\tjle %s\n"
#define JC "\tjc %s\n"
#define JNC "\tjnc %s\n"

// Arithmetic commands:
#define ADD "\tadd %s, %s\n"
#define SUB "\tsub %s, %s\n"
#define SBB "\tsbb %s, %s\n"
#define IMUL "\timul %s, %s\n"
#define IDIV "\tidiv %s\n"
#define NEG "\tneg %s\n"




