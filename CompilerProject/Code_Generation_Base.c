#include "Code_Generation_Base.h"

Register init_register(char* name)
{
    Register reg;
    str_copy(name, reg.name);
    reg.in_use = NOT_IN_USE;
    reg.last_use = 0;
    return reg;
}

Register* init_free_registers()
{
    Register* registers = (Register*) malloc(NUM_OF_REGISTERS * sizeof(Register));
    registers[0] = init_register(AX);
    registers[1] = init_register(BX);
    registers[2] = init_register(CX);
    registers[3] = init_register(DX);
    return registers;
}


Register get_reg(Register* registers)
{
    int i, max, max_index = 0;
    Register reg = registers[0];
    max = reg.last_use;


    for(i = 0; i < NUM_OF_REGISTERS; i++) {
        if (registers[i].last_use > max) {
            reg = registers[i];
            max = reg.last_use;
            max_index = i;
        }
        registers[i].last_use++;
    }
    registers[max_index].last_use = 0;
    registers[max_index].in_use = IN_USE;
    return reg;
}
