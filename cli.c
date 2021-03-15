/*
 * Engs 128 Lab 1
 * Carter Jacobsen and Carter Noordsij
 * Code to run a machine for adding, subtracting, multiplying, and performing dot products
 *
 */

#include "platform.h"
#include "xil_printf.h"
#include "Engs128_Lab1.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"
#include <unistd.h>
#include <stdio.h>
#include "strings.h"
#include "stdbool.h"

const u32 baseaddr = (u32) XPAR_ENGS128_LAB1_0_S00_AXI_BASEADDR;

const int x_reg = 4;
const int y_reg = 8;
const int z_reg = 12;
const int ctrl_reg = 0;

int add_sub_mult(int x, int y, int op) {
    ENGS128_LAB1_mWriteReg(baseaddr, ctrl_reg, op);

    ENGS128_LAB1_mWriteReg(baseaddr, x_reg, (u32) x);

    ENGS128_LAB1_mWriteReg(baseaddr, y_reg, (u32) y);

    u32 result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
    int mask = 1 << 3;
    int run = result | mask;

    ENGS128_LAB1_mWriteReg(baseaddr, ctrl_reg, run);

    result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
    mask = 1 << 16;
    int masked_n = result & mask;
    int thebit = masked_n >> 16;

    while (thebit == 0) {
        result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
        mask = 1 << 16;
        masked_n = result & mask;
        thebit = masked_n >> 16;
        sleep(.0001);
    }
    int z = (int) ENGS128_LAB1_mReadReg(baseaddr, z_reg);
    printf("Z: %d\r\n", z);

    result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
    mask = 1 << 4;
    int ack = result | mask;
    ack &= ~(1 << 3);

    ENGS128_LAB1_mWriteReg(baseaddr, ctrl_reg, ack);
    result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);

    return z;
}

int dot_prod(int x_array[50], int y_array[50], int length) {

    ENGS128_LAB1_mWriteReg(baseaddr, ctrl_reg, 0x8);

    u32 result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
    int mask = 1 << 16;
    int masked_n = result & mask;
    int thebit = masked_n >> 16;

    while (thebit == 0) {
        result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
        mask = 1 << 16;
        masked_n = result & mask;
        thebit = masked_n >> 16;
        sleep(.0001);
    }

    result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
    mask = 1 << 4;
    int ack = result | mask;
    ack &= ~(1 << 3);

    ENGS128_LAB1_mWriteReg(baseaddr, ctrl_reg, ack);

    sleep(.0001);

    ENGS128_LAB1_mWriteReg(baseaddr, x_reg, (u32) 0);
    ENGS128_LAB1_mWriteReg(baseaddr, y_reg, (u32) 0);

    for (int i = 0; i < length; i++) {
        ENGS128_LAB1_mWriteReg(baseaddr, ctrl_reg, 0xC);
        u32 ctrl_reg_result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
        int mask = 1 << 17;
        int masked_n = ctrl_reg_result & mask;
        int the_bit = masked_n >> 17;

        while (the_bit == 0) {
            ctrl_reg_result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
            mask = 1 << 17;
            masked_n = ctrl_reg_result & mask;
            the_bit = masked_n >> 17;
            sleep(.0001);
        }
        ENGS128_LAB1_mWriteReg(baseaddr, x_reg, (u32) x_array[i]);

        ENGS128_LAB1_mWriteReg(baseaddr, y_reg, (u32) y_array[i]);

        ENGS128_LAB1_mWriteReg(baseaddr, ctrl_reg, 0x2C);
        sleep(.0001);
    }
    ENGS128_LAB1_mWriteReg(baseaddr, ctrl_reg, 0x5);

    result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
    mask = 1 << 16;
    masked_n = result & mask;
    thebit = masked_n >> 16;

    while (thebit == 0) {
        result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
        mask = 1 << 16;
        masked_n = result & mask;
        thebit = masked_n >> 16;
        sleep(.0001);
    }
    u32 z = ENGS128_LAB1_mReadReg(baseaddr, z_reg);
    printf("Z: %d\r\n", (int) z);

    result = ENGS128_LAB1_mReadReg(baseaddr, ctrl_reg);
    mask = 1 << 4;
    ack = result | mask;
    ack &= ~(1 << 3);

    ENGS128_LAB1_mWriteReg(baseaddr, ctrl_reg, ack);

    return z;
}

int main() {
    init_platform();

    bool end = false;
    while (!end) {

        printf("Choose arithmetic ('add', 'subtract', 'multiply', 'dot', or 'end'): ");

        char user_input[10];
        int x;
        int y;

        scanf("%s", user_input);
        if (strcmp(user_input, "add") == 0) {
            printf("\nX: ");
            int valid = scanf("%d", & x);
            while (valid != 1) {
                printf("\nPlease enter an integer X: ");
                getchar();
                valid = scanf("%d", & x);
            }
            printf("%d\nY: ", x);
            valid = scanf("%d", & y);
            while (valid != 1) {
                printf("\nPlease enter an integer Y: ");
                getchar();
                valid = scanf("%d", & y);
            }
            printf("%d\n", y);
            add_sub_mult(x, y, 1);
        } else if (strcmp(user_input, "subtract") == 0) {
            printf("\nX: ");
            int valid = scanf("%d", & x);
            while (valid != 1) {
                printf("\nPlease enter an integer X: ");
                getchar();
                valid = scanf("%d", & x);
            }
            printf("%d\nY: ", x);
            valid = scanf("%d", & y);
            while (valid != 1) {
                printf("\nPlease enter an integer Y: ");
                getchar();
                valid = scanf("%d", & y);
            }
            printf("%d\n", y);
            add_sub_mult(x, y, 2);
        } else if (strcmp(user_input, "multiply") == 0) {
            printf("\nX: ");
            int valid = scanf("%d", & x);
            while (valid != 1) {
                printf("\nPlease enter an integer X: ");
                getchar();
                valid = scanf("%d", & x);
            }
            printf("%d\nY: ", x);
            valid = scanf("%d", & y);
            while (valid != 1) {
                printf("\nPlease enter an integer Y: ");
                getchar();
                valid = scanf("%d", & y);
            }
            printf("%d\n", y);
            add_sub_mult(x, y, 3);
        } else if (strcmp(user_input, "dot") == 0) {
            int x_array[50];
            int y_array[50];
            int counter = 0;

            printf("\n\rChoose x and y as 0 to end the sequence\n\r");
            printf("\nX: ");
            int valid = scanf("%d", & x);
            while (valid != 1) {
                printf("\nPlease enter an integer X: ");
                getchar();
                valid = scanf("%d", & x);
            }
            printf("%d\nY: ", x);
            valid = scanf("%d", & y);
            while (valid != 1) {
                printf("\nPlease enter an integer Y: ");
                getchar();
                valid = scanf("%d", & y);
            }
            printf("%d\n", y);

            x_array[counter] = x;
            y_array[counter] = y;

            while (!(x == 0 && y == 0)) {
                counter++;
                printf("\nX: ");
                int valid = scanf("%d", & x);
                while (valid != 1) {
                    printf("\nPlease enter an integer X: ");
                    getchar();
                    valid = scanf("%d", & x);
                }
                printf("%d\nY: ", x);
                valid = scanf("%d", & y);
                while (valid != 1) {
                    printf("\nPlease enter an integer Y: ");
                    getchar();
                    valid = scanf("%d", & y);
                }
                printf("%d\n", y);
                x_array[counter] = x;
                y_array[counter] = y;
            }
            dot_prod(x_array, y_array, counter);

        } else if (strcmp(user_input, "end") == 0) {

            end = true;

        } else {
            printf("Please enter one of the specified options\r\n");
        }

    }

    printf("\r\nEnd\r\n");
    cleanup_platform();
    return 0;
}
