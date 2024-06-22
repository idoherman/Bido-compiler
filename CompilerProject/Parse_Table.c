#include "Parse_Table.h"


Parse_Table* init_parse_table()
{
    int i , j;
    Parse_Table* parse_table = (Parse_Table*) malloc(sizeof(Parse_Table));
    for(i = 0; i < NUM_OF_STATES; i++) {
        for (j = 0; j < NUM_OF_TERMINALS; j++) {
            parse_table->action_table[i][j].type = ERROR_ACTION;
            parse_table->action_table[i][j].state = -1;
        }
        for (j = 0; j < NUM_OF_NON_TERMINALS; j++) {
            parse_table->goto_table[i][j].state = -1;
        }
    }
    return parse_table;
}


Parse_Table* build_the_actual_table()
{
    Parse_Table* parse_table = init_parse_table();

    // state 0

    parse_table->action_table[0][0].type = SHIFT_ACTION;
    parse_table->action_table[0][0].state = 2;
    parse_table->goto_table[0][1].state = 1;


    // state 1

    parse_table->action_table[1][29].type = ACCEPT_ACTION;
    parse_table->action_table[1][29].state = -2;


    // state 2

    parse_table->action_table[2][1].type = SHIFT_ACTION;
    parse_table->action_table[2][1].state = 3;


    // state 3

    parse_table->action_table[3][2].type = SHIFT_ACTION;
    parse_table->action_table[3][2].state = 4;


    // state 4

    parse_table->action_table[4][3].type = SHIFT_ACTION;
    parse_table->action_table[4][3].state = 5;


    // state 5

    parse_table->action_table[5][4].type = SHIFT_ACTION;
    parse_table->action_table[5][4].state = 6;


    // state 6

    parse_table->action_table[6][5].type = SHIFT_ACTION;
    parse_table->action_table[6][5].state = 7;


    // state 7

    parse_table->action_table[7][6].type = SHIFT_ACTION;
    parse_table->action_table[7][6].state = 8;


    // state 8

    parse_table->action_table[8][7].type = SHIFT_ACTION;
    parse_table->action_table[8][7].state = 9;


    // state 9

    parse_table->action_table[9][8].type = SHIFT_ACTION;
    parse_table->action_table[9][8].state = 10;


    // state 10

    parse_table->action_table[10][9].type = SHIFT_ACTION;
    parse_table->action_table[10][9].state = 11;


    // state 11

    parse_table->action_table[11][10].type = REDUCE_ACTION;
    parse_table->action_table[11][10].state = 4;
    parse_table->action_table[11][12].type = REDUCE_ACTION;
    parse_table->action_table[11][12].state = 4;
    parse_table->action_table[11][13].type = SHIFT_ACTION;
    parse_table->action_table[11][13].state = 19;
    parse_table->action_table[11][14].type = SHIFT_ACTION;
    parse_table->action_table[11][14].state = 20;
    parse_table->action_table[11][16].type = SHIFT_ACTION;
    parse_table->action_table[11][16].state = 21;
    parse_table->goto_table[11][2].state = 12;
    parse_table->goto_table[11][3].state = 13;
    parse_table->goto_table[11][4].state = 14;
    parse_table->goto_table[11][5].state = 15;
    parse_table->goto_table[11][6].state = 16;
    parse_table->goto_table[11][7].state = 17;
    parse_table->goto_table[11][8].state = 18;


    // state 12

    parse_table->action_table[12][10].type = SHIFT_ACTION;
    parse_table->action_table[12][10].state = 22;


    // state 13

    parse_table->action_table[13][11].type = SHIFT_ACTION;
    parse_table->action_table[13][11].state = 23;


    // state 14

    parse_table->action_table[14][10].type = REDUCE_ACTION;
    parse_table->action_table[14][10].state = 4;
    parse_table->action_table[14][12].type = REDUCE_ACTION;
    parse_table->action_table[14][12].state = 4;
    parse_table->action_table[14][13].type = SHIFT_ACTION;
    parse_table->action_table[14][13].state = 19;
    parse_table->action_table[14][14].type = SHIFT_ACTION;
    parse_table->action_table[14][14].state = 20;
    parse_table->action_table[14][16].type = SHIFT_ACTION;
    parse_table->action_table[14][16].state = 21;
    parse_table->goto_table[14][2].state = 24;
    parse_table->goto_table[14][3].state = 13;
    parse_table->goto_table[14][4].state = 14;
    parse_table->goto_table[14][5].state = 15;
    parse_table->goto_table[14][6].state = 16;
    parse_table->goto_table[14][7].state = 17;
    parse_table->goto_table[14][8].state = 18;


    // state 15

    parse_table->action_table[15][11].type = REDUCE_ACTION;
    parse_table->action_table[15][11].state = 5;


    // state 16

    parse_table->action_table[16][11].type = REDUCE_ACTION;
    parse_table->action_table[16][11].state = 6;


    // state 17

    parse_table->action_table[17][10].type = REDUCE_ACTION;
    parse_table->action_table[17][10].state = 7;
    parse_table->action_table[17][12].type = REDUCE_ACTION;
    parse_table->action_table[17][12].state = 7;
    parse_table->action_table[17][13].type = REDUCE_ACTION;
    parse_table->action_table[17][13].state = 7;
    parse_table->action_table[17][14].type = REDUCE_ACTION;
    parse_table->action_table[17][14].state = 7;
    parse_table->action_table[17][16].type = SHIFT_ACTION;
    parse_table->action_table[17][16].state = 25;


    // state 18

    parse_table->action_table[18][10].type = REDUCE_ACTION;
    parse_table->action_table[18][10].state = 8;
    parse_table->action_table[18][12].type = REDUCE_ACTION;
    parse_table->action_table[18][12].state = 8;
    parse_table->action_table[18][13].type = REDUCE_ACTION;
    parse_table->action_table[18][13].state = 8;
    parse_table->action_table[18][14].type = REDUCE_ACTION;
    parse_table->action_table[18][14].state = 8;
    parse_table->action_table[18][16].type = REDUCE_ACTION;
    parse_table->action_table[18][16].state = 8;


    // state 19

    parse_table->action_table[19][1].type = SHIFT_ACTION;
    parse_table->action_table[19][1].state = 26;


    // state 20

    parse_table->action_table[20][15].type = SHIFT_ACTION;
    parse_table->action_table[20][15].state = 27;


    // state 21

    parse_table->action_table[21][7].type = SHIFT_ACTION;
    parse_table->action_table[21][7].state = 28;


    // state 22

    parse_table->action_table[22][14].type = SHIFT_ACTION;
    parse_table->action_table[22][14].state = 30;
    parse_table->action_table[22][28].type = SHIFT_ACTION;
    parse_table->action_table[22][28].state = 31;
    parse_table->goto_table[22][22].state = 29;


    // state 23

    parse_table->action_table[23][10].type = REDUCE_ACTION;
    parse_table->action_table[23][10].state = 4;
    parse_table->action_table[23][12].type = REDUCE_ACTION;
    parse_table->action_table[23][12].state = 4;
    parse_table->action_table[23][13].type = SHIFT_ACTION;
    parse_table->action_table[23][13].state = 19;
    parse_table->action_table[23][14].type = SHIFT_ACTION;
    parse_table->action_table[23][14].state = 20;
    parse_table->action_table[23][16].type = SHIFT_ACTION;
    parse_table->action_table[23][16].state = 21;
    parse_table->goto_table[23][2].state = 32;
    parse_table->goto_table[23][3].state = 13;
    parse_table->goto_table[23][4].state = 14;
    parse_table->goto_table[23][5].state = 15;
    parse_table->goto_table[23][6].state = 16;
    parse_table->goto_table[23][7].state = 17;
    parse_table->goto_table[23][8].state = 18;


    // state 24

    parse_table->action_table[24][10].type = REDUCE_ACTION;
    parse_table->action_table[24][10].state = 3;
    parse_table->action_table[24][12].type = REDUCE_ACTION;
    parse_table->action_table[24][12].state = 3;


    // state 25

    parse_table->action_table[25][17].type = SHIFT_ACTION;
    parse_table->action_table[25][17].state = 33;


    // state 26

    parse_table->action_table[26][14].type = SHIFT_ACTION;
    parse_table->action_table[26][14].state = 34;


    // state 27

    parse_table->action_table[27][7].type = SHIFT_ACTION;
    parse_table->action_table[27][7].state = 49;
    parse_table->action_table[27][14].type = SHIFT_ACTION;
    parse_table->action_table[27][14].state = 30;
    parse_table->action_table[27][27].type = SHIFT_ACTION;
    parse_table->action_table[27][27].state = 47;
    parse_table->action_table[27][28].type = SHIFT_ACTION;
    parse_table->action_table[27][28].state = 31;
    parse_table->goto_table[27][9].state = 35;
    parse_table->goto_table[27][10].state = 36;
    parse_table->goto_table[27][11].state = 37;
    parse_table->goto_table[27][12].state = 38;
    parse_table->goto_table[27][13].state = 39;
    parse_table->goto_table[27][14].state = 40;
    parse_table->goto_table[27][15].state = 41;
    parse_table->goto_table[27][16].state = 42;
    parse_table->goto_table[27][17].state = 43;
    parse_table->goto_table[27][18].state = 44;
    parse_table->goto_table[27][19].state = 45;
    parse_table->goto_table[27][20].state = 46;
    parse_table->goto_table[27][21].state = 48;
    parse_table->goto_table[27][22].state = 50;


    // state 28

    parse_table->action_table[28][7].type = SHIFT_ACTION;
    parse_table->action_table[28][7].state = 49;
    parse_table->action_table[28][14].type = SHIFT_ACTION;
    parse_table->action_table[28][14].state = 30;
    parse_table->action_table[28][27].type = SHIFT_ACTION;
    parse_table->action_table[28][27].state = 47;
    parse_table->action_table[28][28].type = SHIFT_ACTION;
    parse_table->action_table[28][28].state = 31;
    parse_table->goto_table[28][9].state = 51;
    parse_table->goto_table[28][10].state = 36;
    parse_table->goto_table[28][11].state = 37;
    parse_table->goto_table[28][12].state = 38;
    parse_table->goto_table[28][13].state = 39;
    parse_table->goto_table[28][14].state = 40;
    parse_table->goto_table[28][15].state = 41;
    parse_table->goto_table[28][16].state = 42;
    parse_table->goto_table[28][17].state = 43;
    parse_table->goto_table[28][18].state = 44;
    parse_table->goto_table[28][19].state = 45;
    parse_table->goto_table[28][20].state = 46;
    parse_table->goto_table[28][21].state = 48;
    parse_table->goto_table[28][22].state = 50;


    // state 29

    parse_table->action_table[29][11].type = SHIFT_ACTION;
    parse_table->action_table[29][11].state = 52;


    // state 30

    parse_table->action_table[30][8].type = REDUCE_ACTION;
    parse_table->action_table[30][8].state = 38;
    parse_table->action_table[30][11].type = REDUCE_ACTION;
    parse_table->action_table[30][11].state = 38;
    parse_table->action_table[30][18].type = REDUCE_ACTION;
    parse_table->action_table[30][18].state = 38;
    parse_table->action_table[30][19].type = REDUCE_ACTION;
    parse_table->action_table[30][19].state = 38;
    parse_table->action_table[30][20].type = REDUCE_ACTION;
    parse_table->action_table[30][20].state = 38;
    parse_table->action_table[30][21].type = REDUCE_ACTION;
    parse_table->action_table[30][21].state = 38;
    parse_table->action_table[30][22].type = REDUCE_ACTION;
    parse_table->action_table[30][22].state = 38;
    parse_table->action_table[30][23].type = REDUCE_ACTION;
    parse_table->action_table[30][23].state = 38;
    parse_table->action_table[30][24].type = REDUCE_ACTION;
    parse_table->action_table[30][24].state = 38;
    parse_table->action_table[30][25].type = REDUCE_ACTION;
    parse_table->action_table[30][25].state = 38;
    parse_table->action_table[30][26].type = REDUCE_ACTION;
    parse_table->action_table[30][26].state = 38;


    // state 31

    parse_table->action_table[31][8].type = REDUCE_ACTION;
    parse_table->action_table[31][8].state = 39;
    parse_table->action_table[31][11].type = REDUCE_ACTION;
    parse_table->action_table[31][11].state = 39;
    parse_table->action_table[31][18].type = REDUCE_ACTION;
    parse_table->action_table[31][18].state = 39;
    parse_table->action_table[31][19].type = REDUCE_ACTION;
    parse_table->action_table[31][19].state = 39;
    parse_table->action_table[31][20].type = REDUCE_ACTION;
    parse_table->action_table[31][20].state = 39;
    parse_table->action_table[31][21].type = REDUCE_ACTION;
    parse_table->action_table[31][21].state = 39;
    parse_table->action_table[31][22].type = REDUCE_ACTION;
    parse_table->action_table[31][22].state = 39;
    parse_table->action_table[31][23].type = REDUCE_ACTION;
    parse_table->action_table[31][23].state = 39;
    parse_table->action_table[31][24].type = REDUCE_ACTION;
    parse_table->action_table[31][24].state = 39;
    parse_table->action_table[31][25].type = REDUCE_ACTION;
    parse_table->action_table[31][25].state = 39;
    parse_table->action_table[31][26].type = REDUCE_ACTION;
    parse_table->action_table[31][26].state = 39;


    // state 32

    parse_table->action_table[32][10].type = REDUCE_ACTION;
    parse_table->action_table[32][10].state = 2;
    parse_table->action_table[32][12].type = REDUCE_ACTION;
    parse_table->action_table[32][12].state = 2;


    // state 33

    parse_table->action_table[33][9].type = SHIFT_ACTION;
    parse_table->action_table[33][9].state = 53;


    // state 34

    parse_table->action_table[34][3].type = SHIFT_ACTION;
    parse_table->action_table[34][3].state = 54;


    // state 35

    parse_table->action_table[35][11].type = REDUCE_ACTION;
    parse_table->action_table[35][11].state = 11;


    // state 36

    parse_table->action_table[36][8].type = REDUCE_ACTION;
    parse_table->action_table[36][8].state = 14;
    parse_table->action_table[36][11].type = REDUCE_ACTION;
    parse_table->action_table[36][11].state = 14;
    parse_table->action_table[36][18].type = SHIFT_ACTION;
    parse_table->action_table[36][18].state = 55;


    // state 37

    parse_table->action_table[37][8].type = REDUCE_ACTION;
    parse_table->action_table[37][8].state = 16;
    parse_table->action_table[37][11].type = REDUCE_ACTION;
    parse_table->action_table[37][11].state = 16;
    parse_table->action_table[37][18].type = REDUCE_ACTION;
    parse_table->action_table[37][18].state = 16;
    parse_table->action_table[37][19].type = SHIFT_ACTION;
    parse_table->action_table[37][19].state = 56;


    // state 38

    parse_table->action_table[38][8].type = REDUCE_ACTION;
    parse_table->action_table[38][8].state = 18;
    parse_table->action_table[38][11].type = REDUCE_ACTION;
    parse_table->action_table[38][11].state = 18;
    parse_table->action_table[38][18].type = REDUCE_ACTION;
    parse_table->action_table[38][18].state = 18;
    parse_table->action_table[38][19].type = REDUCE_ACTION;
    parse_table->action_table[38][19].state = 18;
    parse_table->action_table[38][20].type = SHIFT_ACTION;
    parse_table->action_table[38][20].state = 57;


    // state 39

    parse_table->action_table[39][8].type = REDUCE_ACTION;
    parse_table->action_table[39][8].state = 20;
    parse_table->action_table[39][11].type = REDUCE_ACTION;
    parse_table->action_table[39][11].state = 20;
    parse_table->action_table[39][18].type = REDUCE_ACTION;
    parse_table->action_table[39][18].state = 20;
    parse_table->action_table[39][19].type = REDUCE_ACTION;
    parse_table->action_table[39][19].state = 20;
    parse_table->action_table[39][20].type = REDUCE_ACTION;
    parse_table->action_table[39][20].state = 20;
    parse_table->action_table[39][21].type = SHIFT_ACTION;
    parse_table->action_table[39][21].state = 58;


    // state 40

    parse_table->action_table[40][8].type = REDUCE_ACTION;
    parse_table->action_table[40][8].state = 22;
    parse_table->action_table[40][11].type = REDUCE_ACTION;
    parse_table->action_table[40][11].state = 22;
    parse_table->action_table[40][18].type = REDUCE_ACTION;
    parse_table->action_table[40][18].state = 22;
    parse_table->action_table[40][19].type = REDUCE_ACTION;
    parse_table->action_table[40][19].state = 22;
    parse_table->action_table[40][20].type = REDUCE_ACTION;
    parse_table->action_table[40][20].state = 22;
    parse_table->action_table[40][21].type = REDUCE_ACTION;
    parse_table->action_table[40][21].state = 22;
    parse_table->action_table[40][22].type = SHIFT_ACTION;
    parse_table->action_table[40][22].state = 59;


    // state 41

    parse_table->action_table[41][8].type = REDUCE_ACTION;
    parse_table->action_table[41][8].state = 24;
    parse_table->action_table[41][11].type = REDUCE_ACTION;
    parse_table->action_table[41][11].state = 24;
    parse_table->action_table[41][18].type = REDUCE_ACTION;
    parse_table->action_table[41][18].state = 24;
    parse_table->action_table[41][19].type = REDUCE_ACTION;
    parse_table->action_table[41][19].state = 24;
    parse_table->action_table[41][20].type = REDUCE_ACTION;
    parse_table->action_table[41][20].state = 24;
    parse_table->action_table[41][21].type = REDUCE_ACTION;
    parse_table->action_table[41][21].state = 24;
    parse_table->action_table[41][22].type = REDUCE_ACTION;
    parse_table->action_table[41][22].state = 24;
    parse_table->action_table[41][23].type = SHIFT_ACTION;
    parse_table->action_table[41][23].state = 60;


    // state 42

    parse_table->action_table[42][8].type = REDUCE_ACTION;
    parse_table->action_table[42][8].state = 26;
    parse_table->action_table[42][11].type = REDUCE_ACTION;
    parse_table->action_table[42][11].state = 26;
    parse_table->action_table[42][18].type = REDUCE_ACTION;
    parse_table->action_table[42][18].state = 26;
    parse_table->action_table[42][19].type = REDUCE_ACTION;
    parse_table->action_table[42][19].state = 26;
    parse_table->action_table[42][20].type = REDUCE_ACTION;
    parse_table->action_table[42][20].state = 26;
    parse_table->action_table[42][21].type = REDUCE_ACTION;
    parse_table->action_table[42][21].state = 26;
    parse_table->action_table[42][22].type = REDUCE_ACTION;
    parse_table->action_table[42][22].state = 26;
    parse_table->action_table[42][23].type = REDUCE_ACTION;
    parse_table->action_table[42][23].state = 26;
    parse_table->action_table[42][24].type = SHIFT_ACTION;
    parse_table->action_table[42][24].state = 61;


    // state 43

    parse_table->action_table[43][8].type = REDUCE_ACTION;
    parse_table->action_table[43][8].state = 28;
    parse_table->action_table[43][11].type = REDUCE_ACTION;
    parse_table->action_table[43][11].state = 28;
    parse_table->action_table[43][18].type = REDUCE_ACTION;
    parse_table->action_table[43][18].state = 28;
    parse_table->action_table[43][19].type = REDUCE_ACTION;
    parse_table->action_table[43][19].state = 28;
    parse_table->action_table[43][20].type = REDUCE_ACTION;
    parse_table->action_table[43][20].state = 28;
    parse_table->action_table[43][21].type = REDUCE_ACTION;
    parse_table->action_table[43][21].state = 28;
    parse_table->action_table[43][22].type = REDUCE_ACTION;
    parse_table->action_table[43][22].state = 28;
    parse_table->action_table[43][23].type = REDUCE_ACTION;
    parse_table->action_table[43][23].state = 28;
    parse_table->action_table[43][24].type = REDUCE_ACTION;
    parse_table->action_table[43][24].state = 28;


    // state 44

    parse_table->action_table[44][8].type = REDUCE_ACTION;
    parse_table->action_table[44][8].state = 29;
    parse_table->action_table[44][11].type = REDUCE_ACTION;
    parse_table->action_table[44][11].state = 29;
    parse_table->action_table[44][18].type = REDUCE_ACTION;
    parse_table->action_table[44][18].state = 29;
    parse_table->action_table[44][19].type = REDUCE_ACTION;
    parse_table->action_table[44][19].state = 29;
    parse_table->action_table[44][20].type = REDUCE_ACTION;
    parse_table->action_table[44][20].state = 29;
    parse_table->action_table[44][21].type = REDUCE_ACTION;
    parse_table->action_table[44][21].state = 29;
    parse_table->action_table[44][22].type = REDUCE_ACTION;
    parse_table->action_table[44][22].state = 29;
    parse_table->action_table[44][23].type = REDUCE_ACTION;
    parse_table->action_table[44][23].state = 29;
    parse_table->action_table[44][24].type = REDUCE_ACTION;
    parse_table->action_table[44][24].state = 29;
    parse_table->action_table[44][25].type = SHIFT_ACTION;
    parse_table->action_table[44][25].state = 62;


    // state 45

    parse_table->action_table[45][8].type = REDUCE_ACTION;
    parse_table->action_table[45][8].state = 31;
    parse_table->action_table[45][11].type = REDUCE_ACTION;
    parse_table->action_table[45][11].state = 31;
    parse_table->action_table[45][18].type = REDUCE_ACTION;
    parse_table->action_table[45][18].state = 31;
    parse_table->action_table[45][19].type = REDUCE_ACTION;
    parse_table->action_table[45][19].state = 31;
    parse_table->action_table[45][20].type = REDUCE_ACTION;
    parse_table->action_table[45][20].state = 31;
    parse_table->action_table[45][21].type = REDUCE_ACTION;
    parse_table->action_table[45][21].state = 31;
    parse_table->action_table[45][22].type = REDUCE_ACTION;
    parse_table->action_table[45][22].state = 31;
    parse_table->action_table[45][23].type = REDUCE_ACTION;
    parse_table->action_table[45][23].state = 31;
    parse_table->action_table[45][24].type = REDUCE_ACTION;
    parse_table->action_table[45][24].state = 31;
    parse_table->action_table[45][25].type = REDUCE_ACTION;
    parse_table->action_table[45][25].state = 31;
    parse_table->action_table[45][26].type = SHIFT_ACTION;
    parse_table->action_table[45][26].state = 63;


    // state 46

    parse_table->action_table[46][8].type = REDUCE_ACTION;
    parse_table->action_table[46][8].state = 33;
    parse_table->action_table[46][11].type = REDUCE_ACTION;
    parse_table->action_table[46][11].state = 33;
    parse_table->action_table[46][18].type = REDUCE_ACTION;
    parse_table->action_table[46][18].state = 33;
    parse_table->action_table[46][19].type = REDUCE_ACTION;
    parse_table->action_table[46][19].state = 33;
    parse_table->action_table[46][20].type = REDUCE_ACTION;
    parse_table->action_table[46][20].state = 33;
    parse_table->action_table[46][21].type = REDUCE_ACTION;
    parse_table->action_table[46][21].state = 33;
    parse_table->action_table[46][22].type = REDUCE_ACTION;
    parse_table->action_table[46][22].state = 33;
    parse_table->action_table[46][23].type = REDUCE_ACTION;
    parse_table->action_table[46][23].state = 33;
    parse_table->action_table[46][24].type = REDUCE_ACTION;
    parse_table->action_table[46][24].state = 33;
    parse_table->action_table[46][25].type = REDUCE_ACTION;
    parse_table->action_table[46][25].state = 33;
    parse_table->action_table[46][26].type = REDUCE_ACTION;
    parse_table->action_table[46][26].state = 33;


    // state 47

    parse_table->action_table[47][7].type = SHIFT_ACTION;
    parse_table->action_table[47][7].state = 49;
    parse_table->action_table[47][14].type = SHIFT_ACTION;
    parse_table->action_table[47][14].state = 30;
    parse_table->action_table[47][27].type = SHIFT_ACTION;
    parse_table->action_table[47][27].state = 47;
    parse_table->action_table[47][28].type = SHIFT_ACTION;
    parse_table->action_table[47][28].state = 31;
    parse_table->goto_table[47][20].state = 64;
    parse_table->goto_table[47][21].state = 48;
    parse_table->goto_table[47][22].state = 50;


    // state 48

    parse_table->action_table[48][8].type = REDUCE_ACTION;
    parse_table->action_table[48][8].state = 35;
    parse_table->action_table[48][11].type = REDUCE_ACTION;
    parse_table->action_table[48][11].state = 35;
    parse_table->action_table[48][18].type = REDUCE_ACTION;
    parse_table->action_table[48][18].state = 35;
    parse_table->action_table[48][19].type = REDUCE_ACTION;
    parse_table->action_table[48][19].state = 35;
    parse_table->action_table[48][20].type = REDUCE_ACTION;
    parse_table->action_table[48][20].state = 35;
    parse_table->action_table[48][21].type = REDUCE_ACTION;
    parse_table->action_table[48][21].state = 35;
    parse_table->action_table[48][22].type = REDUCE_ACTION;
    parse_table->action_table[48][22].state = 35;
    parse_table->action_table[48][23].type = REDUCE_ACTION;
    parse_table->action_table[48][23].state = 35;
    parse_table->action_table[48][24].type = REDUCE_ACTION;
    parse_table->action_table[48][24].state = 35;
    parse_table->action_table[48][25].type = REDUCE_ACTION;
    parse_table->action_table[48][25].state = 35;
    parse_table->action_table[48][26].type = REDUCE_ACTION;
    parse_table->action_table[48][26].state = 35;


    // state 49

    parse_table->action_table[49][7].type = SHIFT_ACTION;
    parse_table->action_table[49][7].state = 49;
    parse_table->action_table[49][14].type = SHIFT_ACTION;
    parse_table->action_table[49][14].state = 30;
    parse_table->action_table[49][27].type = SHIFT_ACTION;
    parse_table->action_table[49][27].state = 47;
    parse_table->action_table[49][28].type = SHIFT_ACTION;
    parse_table->action_table[49][28].state = 31;
    parse_table->goto_table[49][9].state = 65;
    parse_table->goto_table[49][10].state = 36;
    parse_table->goto_table[49][11].state = 37;
    parse_table->goto_table[49][12].state = 38;
    parse_table->goto_table[49][13].state = 39;
    parse_table->goto_table[49][14].state = 40;
    parse_table->goto_table[49][15].state = 41;
    parse_table->goto_table[49][16].state = 42;
    parse_table->goto_table[49][17].state = 43;
    parse_table->goto_table[49][18].state = 44;
    parse_table->goto_table[49][19].state = 45;
    parse_table->goto_table[49][20].state = 46;
    parse_table->goto_table[49][21].state = 48;
    parse_table->goto_table[49][22].state = 50;


    // state 50

    parse_table->action_table[50][8].type = REDUCE_ACTION;
    parse_table->action_table[50][8].state = 37;
    parse_table->action_table[50][11].type = REDUCE_ACTION;
    parse_table->action_table[50][11].state = 37;
    parse_table->action_table[50][18].type = REDUCE_ACTION;
    parse_table->action_table[50][18].state = 37;
    parse_table->action_table[50][19].type = REDUCE_ACTION;
    parse_table->action_table[50][19].state = 37;
    parse_table->action_table[50][20].type = REDUCE_ACTION;
    parse_table->action_table[50][20].state = 37;
    parse_table->action_table[50][21].type = REDUCE_ACTION;
    parse_table->action_table[50][21].state = 37;
    parse_table->action_table[50][22].type = REDUCE_ACTION;
    parse_table->action_table[50][22].state = 37;
    parse_table->action_table[50][23].type = REDUCE_ACTION;
    parse_table->action_table[50][23].state = 37;
    parse_table->action_table[50][24].type = REDUCE_ACTION;
    parse_table->action_table[50][24].state = 37;
    parse_table->action_table[50][25].type = REDUCE_ACTION;
    parse_table->action_table[50][25].state = 37;
    parse_table->action_table[50][26].type = REDUCE_ACTION;
    parse_table->action_table[50][26].state = 37;


    // state 51

    parse_table->action_table[51][8].type = SHIFT_ACTION;
    parse_table->action_table[51][8].state = 66;


    // state 52

    parse_table->action_table[52][12].type = SHIFT_ACTION;
    parse_table->action_table[52][12].state = 67;


    // state 53

    parse_table->action_table[53][10].type = REDUCE_ACTION;
    parse_table->action_table[53][10].state = 4;
    parse_table->action_table[53][12].type = REDUCE_ACTION;
    parse_table->action_table[53][12].state = 4;
    parse_table->action_table[53][13].type = SHIFT_ACTION;
    parse_table->action_table[53][13].state = 19;
    parse_table->action_table[53][14].type = SHIFT_ACTION;
    parse_table->action_table[53][14].state = 20;
    parse_table->action_table[53][16].type = SHIFT_ACTION;
    parse_table->action_table[53][16].state = 21;
    parse_table->goto_table[53][2].state = 68;
    parse_table->goto_table[53][3].state = 13;
    parse_table->goto_table[53][4].state = 14;
    parse_table->goto_table[53][5].state = 15;
    parse_table->goto_table[53][6].state = 16;
    parse_table->goto_table[53][7].state = 17;
    parse_table->goto_table[53][8].state = 18;


    // state 54

    parse_table->action_table[54][11].type = REDUCE_ACTION;
    parse_table->action_table[54][11].state = 9;
    parse_table->action_table[54][15].type = SHIFT_ACTION;
    parse_table->action_table[54][15].state = 69;


    // state 55

    parse_table->action_table[55][7].type = SHIFT_ACTION;
    parse_table->action_table[55][7].state = 49;
    parse_table->action_table[55][14].type = SHIFT_ACTION;
    parse_table->action_table[55][14].state = 30;
    parse_table->action_table[55][27].type = SHIFT_ACTION;
    parse_table->action_table[55][27].state = 47;
    parse_table->action_table[55][28].type = SHIFT_ACTION;
    parse_table->action_table[55][28].state = 31;
    parse_table->goto_table[55][11].state = 70;
    parse_table->goto_table[55][12].state = 38;
    parse_table->goto_table[55][13].state = 39;
    parse_table->goto_table[55][14].state = 40;
    parse_table->goto_table[55][15].state = 41;
    parse_table->goto_table[55][16].state = 42;
    parse_table->goto_table[55][17].state = 43;
    parse_table->goto_table[55][18].state = 44;
    parse_table->goto_table[55][19].state = 45;
    parse_table->goto_table[55][20].state = 46;
    parse_table->goto_table[55][21].state = 48;
    parse_table->goto_table[55][22].state = 50;


    // state 56

    parse_table->action_table[56][7].type = SHIFT_ACTION;
    parse_table->action_table[56][7].state = 49;
    parse_table->action_table[56][14].type = SHIFT_ACTION;
    parse_table->action_table[56][14].state = 30;
    parse_table->action_table[56][27].type = SHIFT_ACTION;
    parse_table->action_table[56][27].state = 47;
    parse_table->action_table[56][28].type = SHIFT_ACTION;
    parse_table->action_table[56][28].state = 31;
    parse_table->goto_table[56][12].state = 71;
    parse_table->goto_table[56][13].state = 39;
    parse_table->goto_table[56][14].state = 40;
    parse_table->goto_table[56][15].state = 41;
    parse_table->goto_table[56][16].state = 42;
    parse_table->goto_table[56][17].state = 43;
    parse_table->goto_table[56][18].state = 44;
    parse_table->goto_table[56][19].state = 45;
    parse_table->goto_table[56][20].state = 46;
    parse_table->goto_table[56][21].state = 48;
    parse_table->goto_table[56][22].state = 50;


    // state 57

    parse_table->action_table[57][7].type = SHIFT_ACTION;
    parse_table->action_table[57][7].state = 49;
    parse_table->action_table[57][14].type = SHIFT_ACTION;
    parse_table->action_table[57][14].state = 30;
    parse_table->action_table[57][27].type = SHIFT_ACTION;
    parse_table->action_table[57][27].state = 47;
    parse_table->action_table[57][28].type = SHIFT_ACTION;
    parse_table->action_table[57][28].state = 31;
    parse_table->goto_table[57][13].state = 72;
    parse_table->goto_table[57][14].state = 40;
    parse_table->goto_table[57][15].state = 41;
    parse_table->goto_table[57][16].state = 42;
    parse_table->goto_table[57][17].state = 43;
    parse_table->goto_table[57][18].state = 44;
    parse_table->goto_table[57][19].state = 45;
    parse_table->goto_table[57][20].state = 46;
    parse_table->goto_table[57][21].state = 48;
    parse_table->goto_table[57][22].state = 50;


    // state 58

    parse_table->action_table[58][7].type = SHIFT_ACTION;
    parse_table->action_table[58][7].state = 49;
    parse_table->action_table[58][14].type = SHIFT_ACTION;
    parse_table->action_table[58][14].state = 30;
    parse_table->action_table[58][27].type = SHIFT_ACTION;
    parse_table->action_table[58][27].state = 47;
    parse_table->action_table[58][28].type = SHIFT_ACTION;
    parse_table->action_table[58][28].state = 31;
    parse_table->goto_table[58][14].state = 73;
    parse_table->goto_table[58][15].state = 41;
    parse_table->goto_table[58][16].state = 42;
    parse_table->goto_table[58][17].state = 43;
    parse_table->goto_table[58][18].state = 44;
    parse_table->goto_table[58][19].state = 45;
    parse_table->goto_table[58][20].state = 46;
    parse_table->goto_table[58][21].state = 48;
    parse_table->goto_table[58][22].state = 50;


    // state 59

    parse_table->action_table[59][7].type = SHIFT_ACTION;
    parse_table->action_table[59][7].state = 49;
    parse_table->action_table[59][14].type = SHIFT_ACTION;
    parse_table->action_table[59][14].state = 30;
    parse_table->action_table[59][27].type = SHIFT_ACTION;
    parse_table->action_table[59][27].state = 47;
    parse_table->action_table[59][28].type = SHIFT_ACTION;
    parse_table->action_table[59][28].state = 31;
    parse_table->goto_table[59][15].state = 74;
    parse_table->goto_table[59][16].state = 42;
    parse_table->goto_table[59][17].state = 43;
    parse_table->goto_table[59][18].state = 44;
    parse_table->goto_table[59][19].state = 45;
    parse_table->goto_table[59][20].state = 46;
    parse_table->goto_table[59][21].state = 48;
    parse_table->goto_table[59][22].state = 50;


    // state 60

    parse_table->action_table[60][7].type = SHIFT_ACTION;
    parse_table->action_table[60][7].state = 49;
    parse_table->action_table[60][14].type = SHIFT_ACTION;
    parse_table->action_table[60][14].state = 30;
    parse_table->action_table[60][27].type = SHIFT_ACTION;
    parse_table->action_table[60][27].state = 47;
    parse_table->action_table[60][28].type = SHIFT_ACTION;
    parse_table->action_table[60][28].state = 31;
    parse_table->goto_table[60][16].state = 75;
    parse_table->goto_table[60][17].state = 43;
    parse_table->goto_table[60][18].state = 44;
    parse_table->goto_table[60][19].state = 45;
    parse_table->goto_table[60][20].state = 46;
    parse_table->goto_table[60][21].state = 48;
    parse_table->goto_table[60][22].state = 50;


    // state 61

    parse_table->action_table[61][7].type = SHIFT_ACTION;
    parse_table->action_table[61][7].state = 49;
    parse_table->action_table[61][14].type = SHIFT_ACTION;
    parse_table->action_table[61][14].state = 30;
    parse_table->action_table[61][27].type = SHIFT_ACTION;
    parse_table->action_table[61][27].state = 47;
    parse_table->action_table[61][28].type = SHIFT_ACTION;
    parse_table->action_table[61][28].state = 31;
    parse_table->goto_table[61][17].state = 76;
    parse_table->goto_table[61][18].state = 44;
    parse_table->goto_table[61][19].state = 45;
    parse_table->goto_table[61][20].state = 46;
    parse_table->goto_table[61][21].state = 48;
    parse_table->goto_table[61][22].state = 50;


    // state 62

    parse_table->action_table[62][7].type = SHIFT_ACTION;
    parse_table->action_table[62][7].state = 49;
    parse_table->action_table[62][14].type = SHIFT_ACTION;
    parse_table->action_table[62][14].state = 30;
    parse_table->action_table[62][27].type = SHIFT_ACTION;
    parse_table->action_table[62][27].state = 47;
    parse_table->action_table[62][28].type = SHIFT_ACTION;
    parse_table->action_table[62][28].state = 31;
    parse_table->goto_table[62][19].state = 77;
    parse_table->goto_table[62][20].state = 46;
    parse_table->goto_table[62][21].state = 48;
    parse_table->goto_table[62][22].state = 50;


    // state 63

    parse_table->action_table[63][7].type = SHIFT_ACTION;
    parse_table->action_table[63][7].state = 49;
    parse_table->action_table[63][14].type = SHIFT_ACTION;
    parse_table->action_table[63][14].state = 30;
    parse_table->action_table[63][27].type = SHIFT_ACTION;
    parse_table->action_table[63][27].state = 47;
    parse_table->action_table[63][28].type = SHIFT_ACTION;
    parse_table->action_table[63][28].state = 31;
    parse_table->goto_table[63][20].state = 78;
    parse_table->goto_table[63][21].state = 48;
    parse_table->goto_table[63][22].state = 50;


    // state 64

    parse_table->action_table[64][8].type = REDUCE_ACTION;
    parse_table->action_table[64][8].state = 34;
    parse_table->action_table[64][11].type = REDUCE_ACTION;
    parse_table->action_table[64][11].state = 34;
    parse_table->action_table[64][18].type = REDUCE_ACTION;
    parse_table->action_table[64][18].state = 34;
    parse_table->action_table[64][19].type = REDUCE_ACTION;
    parse_table->action_table[64][19].state = 34;
    parse_table->action_table[64][20].type = REDUCE_ACTION;
    parse_table->action_table[64][20].state = 34;
    parse_table->action_table[64][21].type = REDUCE_ACTION;
    parse_table->action_table[64][21].state = 34;
    parse_table->action_table[64][22].type = REDUCE_ACTION;
    parse_table->action_table[64][22].state = 34;
    parse_table->action_table[64][23].type = REDUCE_ACTION;
    parse_table->action_table[64][23].state = 34;
    parse_table->action_table[64][24].type = REDUCE_ACTION;
    parse_table->action_table[64][24].state = 34;
    parse_table->action_table[64][25].type = REDUCE_ACTION;
    parse_table->action_table[64][25].state = 34;
    parse_table->action_table[64][26].type = REDUCE_ACTION;
    parse_table->action_table[64][26].state = 34;


    // state 65

    parse_table->action_table[65][8].type = SHIFT_ACTION;
    parse_table->action_table[65][8].state = 79;


    // state 66

    parse_table->action_table[66][9].type = SHIFT_ACTION;
    parse_table->action_table[66][9].state = 80;


    // state 67

    parse_table->action_table[67][29].type = REDUCE_ACTION;
    parse_table->action_table[67][29].state = 1;


    // state 68

    parse_table->action_table[68][12].type = SHIFT_ACTION;
    parse_table->action_table[68][12].state = 81;


    // state 69

    parse_table->action_table[69][7].type = SHIFT_ACTION;
    parse_table->action_table[69][7].state = 49;
    parse_table->action_table[69][14].type = SHIFT_ACTION;
    parse_table->action_table[69][14].state = 30;
    parse_table->action_table[69][27].type = SHIFT_ACTION;
    parse_table->action_table[69][27].state = 47;
    parse_table->action_table[69][28].type = SHIFT_ACTION;
    parse_table->action_table[69][28].state = 31;
    parse_table->goto_table[69][9].state = 82;
    parse_table->goto_table[69][10].state = 36;
    parse_table->goto_table[69][11].state = 37;
    parse_table->goto_table[69][12].state = 38;
    parse_table->goto_table[69][13].state = 39;
    parse_table->goto_table[69][14].state = 40;
    parse_table->goto_table[69][15].state = 41;
    parse_table->goto_table[69][16].state = 42;
    parse_table->goto_table[69][17].state = 43;
    parse_table->goto_table[69][18].state = 44;
    parse_table->goto_table[69][19].state = 45;
    parse_table->goto_table[69][20].state = 46;
    parse_table->goto_table[69][21].state = 48;
    parse_table->goto_table[69][22].state = 50;


    // state 70

    parse_table->action_table[70][8].type = REDUCE_ACTION;
    parse_table->action_table[70][8].state = 15;
    parse_table->action_table[70][11].type = REDUCE_ACTION;
    parse_table->action_table[70][11].state = 15;
    parse_table->action_table[70][18].type = REDUCE_ACTION;
    parse_table->action_table[70][18].state = 15;
    parse_table->action_table[70][19].type = SHIFT_ACTION;
    parse_table->action_table[70][19].state = 56;


    // state 71

    parse_table->action_table[71][8].type = REDUCE_ACTION;
    parse_table->action_table[71][8].state = 17;
    parse_table->action_table[71][11].type = REDUCE_ACTION;
    parse_table->action_table[71][11].state = 17;
    parse_table->action_table[71][18].type = REDUCE_ACTION;
    parse_table->action_table[71][18].state = 17;
    parse_table->action_table[71][19].type = REDUCE_ACTION;
    parse_table->action_table[71][19].state = 17;
    parse_table->action_table[71][20].type = SHIFT_ACTION;
    parse_table->action_table[71][20].state = 57;


    // state 72

    parse_table->action_table[72][8].type = REDUCE_ACTION;
    parse_table->action_table[72][8].state = 19;
    parse_table->action_table[72][11].type = REDUCE_ACTION;
    parse_table->action_table[72][11].state = 19;
    parse_table->action_table[72][18].type = REDUCE_ACTION;
    parse_table->action_table[72][18].state = 19;
    parse_table->action_table[72][19].type = REDUCE_ACTION;
    parse_table->action_table[72][19].state = 19;
    parse_table->action_table[72][20].type = REDUCE_ACTION;
    parse_table->action_table[72][20].state = 19;
    parse_table->action_table[72][21].type = SHIFT_ACTION;
    parse_table->action_table[72][21].state = 58;


    // state 73

    parse_table->action_table[73][8].type = REDUCE_ACTION;
    parse_table->action_table[73][8].state = 21;
    parse_table->action_table[73][11].type = REDUCE_ACTION;
    parse_table->action_table[73][11].state = 21;
    parse_table->action_table[73][18].type = REDUCE_ACTION;
    parse_table->action_table[73][18].state = 21;
    parse_table->action_table[73][19].type = REDUCE_ACTION;
    parse_table->action_table[73][19].state = 21;
    parse_table->action_table[73][20].type = REDUCE_ACTION;
    parse_table->action_table[73][20].state = 21;
    parse_table->action_table[73][21].type = REDUCE_ACTION;
    parse_table->action_table[73][21].state = 21;
    parse_table->action_table[73][22].type = SHIFT_ACTION;
    parse_table->action_table[73][22].state = 59;


    // state 74

    parse_table->action_table[74][8].type = REDUCE_ACTION;
    parse_table->action_table[74][8].state = 23;
    parse_table->action_table[74][11].type = REDUCE_ACTION;
    parse_table->action_table[74][11].state = 23;
    parse_table->action_table[74][18].type = REDUCE_ACTION;
    parse_table->action_table[74][18].state = 23;
    parse_table->action_table[74][19].type = REDUCE_ACTION;
    parse_table->action_table[74][19].state = 23;
    parse_table->action_table[74][20].type = REDUCE_ACTION;
    parse_table->action_table[74][20].state = 23;
    parse_table->action_table[74][21].type = REDUCE_ACTION;
    parse_table->action_table[74][21].state = 23;
    parse_table->action_table[74][22].type = REDUCE_ACTION;
    parse_table->action_table[74][22].state = 23;
    parse_table->action_table[74][23].type = SHIFT_ACTION;
    parse_table->action_table[74][23].state = 60;


    // state 75

    parse_table->action_table[75][8].type = REDUCE_ACTION;
    parse_table->action_table[75][8].state = 25;
    parse_table->action_table[75][11].type = REDUCE_ACTION;
    parse_table->action_table[75][11].state = 25;
    parse_table->action_table[75][18].type = REDUCE_ACTION;
    parse_table->action_table[75][18].state = 25;
    parse_table->action_table[75][19].type = REDUCE_ACTION;
    parse_table->action_table[75][19].state = 25;
    parse_table->action_table[75][20].type = REDUCE_ACTION;
    parse_table->action_table[75][20].state = 25;
    parse_table->action_table[75][21].type = REDUCE_ACTION;
    parse_table->action_table[75][21].state = 25;
    parse_table->action_table[75][22].type = REDUCE_ACTION;
    parse_table->action_table[75][22].state = 25;
    parse_table->action_table[75][23].type = REDUCE_ACTION;
    parse_table->action_table[75][23].state = 25;
    parse_table->action_table[75][24].type = SHIFT_ACTION;
    parse_table->action_table[75][24].state = 61;


    // state 76

    parse_table->action_table[76][8].type = REDUCE_ACTION;
    parse_table->action_table[76][8].state = 27;
    parse_table->action_table[76][11].type = REDUCE_ACTION;
    parse_table->action_table[76][11].state = 27;
    parse_table->action_table[76][18].type = REDUCE_ACTION;
    parse_table->action_table[76][18].state = 27;
    parse_table->action_table[76][19].type = REDUCE_ACTION;
    parse_table->action_table[76][19].state = 27;
    parse_table->action_table[76][20].type = REDUCE_ACTION;
    parse_table->action_table[76][20].state = 27;
    parse_table->action_table[76][21].type = REDUCE_ACTION;
    parse_table->action_table[76][21].state = 27;
    parse_table->action_table[76][22].type = REDUCE_ACTION;
    parse_table->action_table[76][22].state = 27;
    parse_table->action_table[76][23].type = REDUCE_ACTION;
    parse_table->action_table[76][23].state = 27;
    parse_table->action_table[76][24].type = REDUCE_ACTION;
    parse_table->action_table[76][24].state = 27;


    // state 77

    parse_table->action_table[77][8].type = REDUCE_ACTION;
    parse_table->action_table[77][8].state = 30;
    parse_table->action_table[77][11].type = REDUCE_ACTION;
    parse_table->action_table[77][11].state = 30;
    parse_table->action_table[77][18].type = REDUCE_ACTION;
    parse_table->action_table[77][18].state = 30;
    parse_table->action_table[77][19].type = REDUCE_ACTION;
    parse_table->action_table[77][19].state = 30;
    parse_table->action_table[77][20].type = REDUCE_ACTION;
    parse_table->action_table[77][20].state = 30;
    parse_table->action_table[77][21].type = REDUCE_ACTION;
    parse_table->action_table[77][21].state = 30;
    parse_table->action_table[77][22].type = REDUCE_ACTION;
    parse_table->action_table[77][22].state = 30;
    parse_table->action_table[77][23].type = REDUCE_ACTION;
    parse_table->action_table[77][23].state = 30;
    parse_table->action_table[77][24].type = REDUCE_ACTION;
    parse_table->action_table[77][24].state = 30;
    parse_table->action_table[77][25].type = REDUCE_ACTION;
    parse_table->action_table[77][25].state = 30;
    parse_table->action_table[77][26].type = SHIFT_ACTION;
    parse_table->action_table[77][26].state = 63;


    // state 78

    parse_table->action_table[78][8].type = REDUCE_ACTION;
    parse_table->action_table[78][8].state = 32;
    parse_table->action_table[78][11].type = REDUCE_ACTION;
    parse_table->action_table[78][11].state = 32;
    parse_table->action_table[78][18].type = REDUCE_ACTION;
    parse_table->action_table[78][18].state = 32;
    parse_table->action_table[78][19].type = REDUCE_ACTION;
    parse_table->action_table[78][19].state = 32;
    parse_table->action_table[78][20].type = REDUCE_ACTION;
    parse_table->action_table[78][20].state = 32;
    parse_table->action_table[78][21].type = REDUCE_ACTION;
    parse_table->action_table[78][21].state = 32;
    parse_table->action_table[78][22].type = REDUCE_ACTION;
    parse_table->action_table[78][22].state = 32;
    parse_table->action_table[78][23].type = REDUCE_ACTION;
    parse_table->action_table[78][23].state = 32;
    parse_table->action_table[78][24].type = REDUCE_ACTION;
    parse_table->action_table[78][24].state = 32;
    parse_table->action_table[78][25].type = REDUCE_ACTION;
    parse_table->action_table[78][25].state = 32;
    parse_table->action_table[78][26].type = REDUCE_ACTION;
    parse_table->action_table[78][26].state = 32;


    // state 79

    parse_table->action_table[79][8].type = REDUCE_ACTION;
    parse_table->action_table[79][8].state = 36;
    parse_table->action_table[79][11].type = REDUCE_ACTION;
    parse_table->action_table[79][11].state = 36;
    parse_table->action_table[79][18].type = REDUCE_ACTION;
    parse_table->action_table[79][18].state = 36;
    parse_table->action_table[79][19].type = REDUCE_ACTION;
    parse_table->action_table[79][19].state = 36;
    parse_table->action_table[79][20].type = REDUCE_ACTION;
    parse_table->action_table[79][20].state = 36;
    parse_table->action_table[79][21].type = REDUCE_ACTION;
    parse_table->action_table[79][21].state = 36;
    parse_table->action_table[79][22].type = REDUCE_ACTION;
    parse_table->action_table[79][22].state = 36;
    parse_table->action_table[79][23].type = REDUCE_ACTION;
    parse_table->action_table[79][23].state = 36;
    parse_table->action_table[79][24].type = REDUCE_ACTION;
    parse_table->action_table[79][24].state = 36;
    parse_table->action_table[79][25].type = REDUCE_ACTION;
    parse_table->action_table[79][25].state = 36;
    parse_table->action_table[79][26].type = REDUCE_ACTION;
    parse_table->action_table[79][26].state = 36;


    // state 80

    parse_table->action_table[80][10].type = REDUCE_ACTION;
    parse_table->action_table[80][10].state = 4;
    parse_table->action_table[80][12].type = REDUCE_ACTION;
    parse_table->action_table[80][12].state = 4;
    parse_table->action_table[80][13].type = SHIFT_ACTION;
    parse_table->action_table[80][13].state = 19;
    parse_table->action_table[80][14].type = SHIFT_ACTION;
    parse_table->action_table[80][14].state = 20;
    parse_table->action_table[80][16].type = SHIFT_ACTION;
    parse_table->action_table[80][16].state = 21;
    parse_table->goto_table[80][2].state = 83;
    parse_table->goto_table[80][3].state = 13;
    parse_table->goto_table[80][4].state = 14;
    parse_table->goto_table[80][5].state = 15;
    parse_table->goto_table[80][6].state = 16;
    parse_table->goto_table[80][7].state = 17;
    parse_table->goto_table[80][8].state = 18;


    // state 81

    parse_table->action_table[81][10].type = REDUCE_ACTION;
    parse_table->action_table[81][10].state = 13;
    parse_table->action_table[81][12].type = REDUCE_ACTION;
    parse_table->action_table[81][12].state = 13;
    parse_table->action_table[81][13].type = REDUCE_ACTION;
    parse_table->action_table[81][13].state = 13;
    parse_table->action_table[81][14].type = REDUCE_ACTION;
    parse_table->action_table[81][14].state = 13;
    parse_table->action_table[81][16].type = REDUCE_ACTION;
    parse_table->action_table[81][16].state = 13;


    // state 82

    parse_table->action_table[82][11].type = REDUCE_ACTION;
    parse_table->action_table[82][11].state = 10;


    // state 83

    parse_table->action_table[83][12].type = SHIFT_ACTION;
    parse_table->action_table[83][12].state = 84;


    // state 84

    parse_table->action_table[84][10].type = REDUCE_ACTION;
    parse_table->action_table[84][10].state = 12;
    parse_table->action_table[84][12].type = REDUCE_ACTION;
    parse_table->action_table[84][12].state = 12;
    parse_table->action_table[84][13].type = REDUCE_ACTION;
    parse_table->action_table[84][13].state = 12;
    parse_table->action_table[84][14].type = REDUCE_ACTION;
    parse_table->action_table[84][14].state = 12;
    parse_table->action_table[84][16].type = REDUCE_ACTION;
    parse_table->action_table[84][16].state = 12;

    return parse_table;
}

int get_terminal_type_from_token(Token* token, Error* errors)
{
    switch (token->type) {
        case TOKEN_FUNCTION:
            return FUNCTION;
        case TOKEN_LT:
            return LESS_THAN;
        case TOKEN_MAIN:
            return MAIN;
        case TOKEN_GT:
            return GREATER_THAN;
        case TOKEN_RETURNS:
            return RETURNS;
        case TOKEN_INT_FUNC:
            return INT_TYPE;
        case TOKEN_GETS:
            return GETS;
        case TOKEN_LPAREN:
            return LEFT_PAREN;
        case TOKEN_RPAREN:
            return RIGHT_PAREN;
        case TOKEN_LBRACE:
            return LEFT_BRACE;
        case TOKEN_RBRACE:
            return RIGHT_BRACE;
        case TOKEN_CHAR:
        case TOKEN_TEXT:
        case TOKEN_BOOL:
            return VARIABLE_TYPE;
        case TOKEN_IS:
            return IS;
        case TOKEN_TRUE:
        case TOKEN_FALSE:
            return VARIABLE_VALUE;
        case TOKEN_IF:
            return IF;
        case TOKEN_NOT:
            return NOT;
        case TOKEN_AND:
            return AND;
        case TOKEN_OR:
            return OR;
        case TOKEN_DOT:
            return DOT;
        case TOKEN_EQUAL:
        case TOKEN_NEQ:
            return EQUAL_CMP_OP;
        case TOKEN_GTE:
        case TOKEN_LTE:
            return CMP_OP;
        case TOKEN_PLUS:
        case TOKEN_MINUS:
            return ADD_OP;
        case TOKEN_MULT:
        case TOKEN_DIV:
        case TOKEN_MOD:
            return MULT_OP;
        case TOKEN_AND_OP:
            return BITWISE_AND;
        case TOKEN_OR_OP:
            return BITWISE_OR;
        case TOKEN_XOR_OP:
            return BITWISE_XOR;
        case TOKEN_NOT_UNARY_OP:
        case TOKEN_PLUS_UNARY_OP:
        case TOKEN_MINUS_UNARY_OP:
            return UNARY_OP;
        case TOKEN_RETURN_END:
            return RETURN;
        case TOKEN_INT:
            return VARIABLE_TYPE;
        case TOKEN_VARIABLE:
            return VARIABLE_NAME;
        case TOKEN_INT_NUMBER:
        case TOKEN_CHAR_LITERAL:
        case TOKEN_TEXT_LITERAL:
            return VARIABLE_VALUE;
        case TOKEN_DOLLAR:
            return DOLLAR;
        default:
            error_unknown_token_type(token, errors);
            return -1;
    }
}


Action* get_action(Parse_Table* table, Token* token, int row, Parse_Stack* st, Error* errors)
{
    int col;
    col = get_terminal_type_from_token(token, errors);
    if (col == -1) {
        return NULL;
    }

    return &(table->action_table[row][col]);
}


GoTo* get_goto(Parse_Table* table, int state, int rule, Error* errors)
{
    return &(table->goto_table[state][get_non_terminal_type(rule, errors)]);
}

