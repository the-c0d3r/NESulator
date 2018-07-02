#include <assert.h>
#include "TestMemory.h"

/**
 * Tests how the system writes to memory. in order to actually only test the writing, we have to compare
 * the results by accessing the array directly. We wouldn't do that usually.
 */
void testWrite() {
    zeroMemory();

    //Test one byte write
    assert(memoryBank[0] == 0);
    byte data = 'd';
    wmem(BYTE, 0, &data);
    assert(memoryBank[0] == 'd');

    zeroMemory();

    //Test two byte write on random positions
    assert(memoryBank[512] == 0);
    assert(memoryBank[513] == 0);
    assert(memoryBank[514] == 0);
    byte *nesText = "NES";
    wmem(3, 512, nesText);

    assert(memoryBank[512] == 'N');
    assert(memoryBank[513] == 'E');
    assert(memoryBank[514] == 'S');

    //Test the memory write repeat
    zeroMemory();
    assert(memoryBank[512] == 0);
    assert(memoryBank[513] == 0);
    wmem_const(WORD, 512, 'S');
    assert(memoryBank[512] == 'S');
    assert(memoryBank[513] == 'S');


    printf("Write memory test passed!\n");
}

/**
 * Tests how the system reads from memory. Because the write test has passed all the asserts before this one
 * We can assume it works fine so we'll use wmem to ease out the writing
 */
void testRead() {
    zeroMemory();

    //Test one byte read
    //Test the empty values
    byte readSingleByte[1];
    rmem(BYTE, 0, readSingleByte);
    assert(readSingleByte[0] == 0);
    //Fill in the test data
    byte data = 'd';
    wmem(BYTE, 0, &data);
    //Make sure the test data is in there
    rmem(BYTE, 0, readSingleByte);
    assert(readSingleByte[0] == 'd');

    //Test three bytes read
    //Test the empty values
    zeroMemory();
    byte readMultipleBytes[3];
    rmem(3, 512, readMultipleBytes);
    assert(readMultipleBytes[0] == 0);
    assert(readMultipleBytes[1] == 0);
    assert(readMultipleBytes[2] == 0);
    //Fill in the test data
    byte *nesData = "NES";
    wmem(3, 512, nesData);
    //Make sure the test data is in there
    rmem(3, 512, readMultipleBytes);
    assert(readMultipleBytes[0] == 'N');
    assert(readMultipleBytes[1] == 'E');
    assert(readMultipleBytes[2] == 'S');

    printf("Read memory test passed!\n");
}

/**
 * Tests how the indexed indirect mode works
 */
void testIndirectXAddr() {
    word addr = 0;
    // First test
    zeroMemory();
    wmem_const(BYTE, 112, 11);
    wmem_const(BYTE, 113, 69);

    X = 100;
    addr = indirectx_addr(12);
    assert(addr == 91);

    // Second test
    zeroMemory();
    wmem_const(BYTE, 126, 42);
    wmem_const(BYTE, 127, 13);

    X = 100;
    addr = indirectx_addr(26);
    assert(addr == 218);

    printf("testIndirectXAddr test passed!\n");
}
