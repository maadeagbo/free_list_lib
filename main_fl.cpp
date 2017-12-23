#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "freelist.h"

int main(const int argc, const char **argv){
	//printf("Max uint8: %u\n", U8_SIZE);
	printf("Max freelist size: %u\n", FREELIST_MAX);
	//printf("Max uint32: %u\n", U32_SIZE);
	printf("\nTesting freelist library...\n");
	printf("Size of freelist: %ld B\n", sizeof(freelist));
	
	freelist test_list;
	test_list.initialize(100);
	printf("\tSize of freelist(100): %lu B\n", 
				(unsigned long)test_list.list.size() + sizeof(freelist));
	// check initialized values
	test_list.print_freelist();
	
	// check nxt_free_slot functionality
	uint32_t idx = 0; 
	for (unsigned i = (unsigned)test_list.list.size(); i > 0; i--) {
		if(test_list.nxt_free_slot(idx)) { 
			printf("Next free slot: %u\n", idx); 
		} else {
			printf("No slots left\n");
		}
	}
	test_list.print_freelist();
	
	// check release_slot functionality
	for (unsigned i = (unsigned)test_list.list.size(); i > 0; i--) {
		printf("Releasing %u...\n", i - 1);
		test_list.release_slot(i - 1);
	}
	test_list.print_freelist();
	printf("Next free slot: %u\n", test_list.nxt_free);

	// randomly use and free values from list
	test_list.initialize(50);
	srand(time(NULL));
	idx = 0;
	for(unsigned i = 0; i < (unsigned)test_list.list.size() * 2; i++) {
		// randomly choose to use or release a slot
		unsigned r_num = (unsigned)rand() % (unsigned)test_list.list.size();
		if (r_num % 2 != 0) {
			if (test_list.nxt_free_slot(idx)) { 
				printf("--> %u\n", idx);
			}
		} else {
			if (test_list.release_slot(r_num)) {
				printf("<-- %u\n", r_num);
			}
		}
	}
	test_list.print_freelist();
	printf("Next free slot: %u\n", test_list.nxt_free);
	printf("Remaining free slots: %u\n", test_list.remaining_slots());

	return 0; 
}
