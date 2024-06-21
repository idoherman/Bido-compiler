import json


"""
Translate the slr-parsing-table json created from 
"https://jsmachines.sourceforge.net/machines/slr.html",
into a c file that creates it as c arrays.
"""


def main():
    with open('parse_table.json', 'r') as file:
        data = json.load(file)


    GOTO_START = 31
    state = 0
    for array in data[3:]:
        print(f"// state {state} \n")
        for index, element in enumerate(array):
            if element != '':
                if index > 0 and index < GOTO_START:
                    if element == 'acc':
                        print(f"parse_table->action_table[{state}][{index - 1}].type = ACCEPT_ACTION;")
                        print(f"parse_table->action_table[{state}][{index - 1}].state = -2;")
                    else:
                        if element[0] == 's':
                            print(f"parse_table->action_table[{state}][{index - 1}].type = SHIFT_ACTION;")
                        elif element[0] == 'r':
                            print(f"parse_table->action_table[{state}][{index - 1}].type = REDUCE_ACTION;")
                        print(f"parse_table->action_table[{state}][{index - 1}].state = {int(element[1:])};")

                if index > GOTO_START and index <len(array):
                    print(f"parse_table->goto_table[{state}][{index - GOTO_START}].state = {int(element)};")


        print("\n \n \n")
        state += 1





if __name__ == '__main__':
    main()


