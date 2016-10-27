/*! \file
 *
 * This file contains definitions for an Arithmetic/Logic Unit of an
 * emulated processor.
 */


#include <stdio.h>
#include <stdlib.h>   /* malloc(), free() */
#include <string.h>   /* memset() */

#include "alu.h"
#include "instruction.h"


/*!
 * This function dynamically allocates and initializes the state for a new ALU
 * instance.  If allocation fails, the program is terminated.
 */
ALU * build_alu() {
    /* Try to allocate the ALU struct.  If this fails, report error then exit. */
    ALU *alu = malloc(sizeof(ALU));
    if (!alu) {
        fprintf(stderr, "Out of memory building an ALU!\n");
        exit(11);
    }

    /* Initialize all values in the ALU struct to 0. */
    memset(alu, 0, sizeof(ALU));
    return alu;
}


/*! This function frees the dynamically allocated ALU instance. */
void free_alu(ALU *alu) {
    free(alu);
}


/*!
 * This function implements the logic of the ALU.  It reads the inputs and
 * opcode, then sets the output accordingly.  Note that if the ALU does not
 * recognize the opcode, it should simply produce a zero result.
 */
void alu_eval(ALU *alu) {
    uint32_t A, B, aluop;
    uint32_t result;

    A = pin_read(alu->in1);
    B = pin_read(alu->in2);
    aluop = pin_read(alu->op);

    result = 0;
    
    switch (aluop) {
    case ALUOP_ADD: /* Adds two data inputs */
      result = A + B;
      break;
    case ALUOP_INV: /* Computes the twos-complement negation of an input */
      result = ~A;
      break;
    case ALUOP_SUB: /* Subtracts two data inputs */
      result = A - B;
      break;
    case ALUOP_XOR: /* Performs exclusive or operation on two inputs */
      result = A ^ B;
      break;
    case ALUOP_OR: /* Performs or operation on two inputs */
      result = A | B;
      break;
    case ALUOP_INCR: /* Increments an input by 1 */
      result = A + 1;
      break;
    case ALUOP_AND: /* Performs and operation on two inputs */
      result = A & B;
      break;
    case ALUOP_SRA: /* Arithmetic shift right */
      result = 0x80000000 | (A >> 1);
      break;
    case ALUOP_SRL: /* Logical shift right */
      result = A >> 1;
      break;
    case ALUOP_SLA: /* Arithmetic shift left */
      result = A << 1;
      break;
    case ALUOP_SLL: /* Logical shift left */
      result = A << 1;
      break;
    default: /* If the opcode is not recognized by the ALU */
      result = 0;
    }

    pin_set(alu->out, result);
}

