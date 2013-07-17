#include <stdio.h>

struct test {
	int s : 16;
	int y : 16;
};

main_asdf () {
	struct test tt;
	int a = 5;
	tt.s = 0xffff;
	
	a += tt.s;
	printf("%d %d", tt.s, a);	
}


main_fff () {
	int a[] = {1, 2, 3, 4};
	int *g = (int*)((char*)(a) + 1);
	
	printf("%d", *g & 0xff);
	return 0;
}


main_LLL () {
	int i = -512;
	printf("%d", i << 8);
	return 0;
}


main_iiii() {
	int *a = 0;
	*a = 5;	
}


main() {
	int a = 0;
	float b = 0;
	double c=0,d=0;

	while(c == d) {
		a ++;
		b = a;
		c = a;
		d = b;
	}
	printf("%d", a);

	
}
