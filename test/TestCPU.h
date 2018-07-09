#ifndef NESULATOR_TESTCPU_H
#define NESULATOR_TESTCPU_H

#include "../src/Utils.h"
#include "../src/cpu.h"
#include "../src/memory.h"
#include <assert.h>

void testOpcodes();

void test_BRK();

void test_ORA();

void test_ASL();

void test_JSR();

void test_PHP();

void test_PHA();

void test_PLA();

void test_PLP();

#endif //NESULATOR_TESTCPU_H
