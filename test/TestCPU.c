#include "TestCPU.h"

/**
 * Simply calls each function to test. It's going to get messy but what the hell!....
 */
void testOpcodes() {
    power_up(0);
    test_BRK();
    test_ORA();
}

/**
 * For this test to succeed, after executing BRK, PC has to increase just by one,
 * the B flag and the Z flag have both to be 1
 */
void test_BRK() {
    int cachedPC = PC;
    int cachedCyclesThisSec = cyclesThisSec;
    bit_clear(&P, 4);
    assert(bit_test(P, 4) == 0);
    wmem_const(BYTE, PC, 0x00); // brk opcode injected
    cpu_cycle();
    assert(cachedPC + 1 == PC);
    assert(bit_test(P, 4) == 1);
    assert(bit_test(P, 1) == 1);
    assert(cachedCyclesThisSec + 7 == cyclesThisSec);
    printf("Test BRK passed!\n");
}

/**
 * For this test to succeed, PC has to increase by two or three and only Z and N flags can be modified
 */
void test_ORA() {
    // Testing ora_ind_x() through ora()
    int cachedPC = PC;
    int cachedCyclesThisSec = cyclesThisSec;
    wmem_const(BYTE, PC, 0x01); // ora_ind_x opcode injected
    wmem_const(BYTE, PC + 1, 0x42); // value injected at the next PC position
    A = 0x80; //Inject a value in the acumulator to do the "OR" with
    word addr = indirectx_addr(0x42);//ora_x will use this addr to get the value. So put it there
    wmem_const(BYTE, addr, 0x58);
    cpu_cycle();
    assert(cachedPC + 2 == PC);
    assert(cachedCyclesThisSec + 6 == cyclesThisSec);
    assert(bit_test(P, 7) == 1);
    assert(A == 0xD8);

    //testing ora_absolute_x
    cachedPC = PC;
    cachedCyclesThisSec = cyclesThisSec;
    wmem_const(BYTE, PC, 0x19);
    word param = 0x6959;
	wmem(WORD, PC+1, (byte*)&param);
	Y = 0x10;
	addr = absolutey_addr((byte*)&param);
	wmem_const(WORD, addr, 0x58);
	A = 0x80;
	cpu_cycle();
	assert(cachedPC + 3 == PC);
	assert(cachedCyclesThisSec + 4 == cyclesThisSec);
	assert(bit_test(P, 7) == 1);
	assert(A == 0xD8);

    printf("Test ORAIndX passed!\n");
}

void test_ASL(){
	// Testing ora_ind_x() through ora()
	int cachedPC = PC;
	int cachedCyclesThisSec = cyclesThisSec;
	wmem_const(BYTE, PC, 0x01); // ora_ind_x opcode injected
	wmem_const(BYTE, PC + 1, 0x42); // value injected at the next PC position
	A = 0x80; //Inject a value in the accumulator to do the "OR" with
	word addr = indirectx_addr(0x42);//ora_x will use this addr to get the value. So put it there
	wmem_const(BYTE, addr, 0x58);
	cpu_cycle();
	assert(cachedPC + 2 == PC);
	assert(cachedCyclesThisSec + 6 == cyclesThisSec);
	assert(bit_test(P, 7) == 1);
	assert(A == 0xD8);
}