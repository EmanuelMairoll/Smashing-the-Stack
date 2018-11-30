#include <stdio.h>
#include <stdlib.h>

void secrFunc(){
	printf("Called secret func\n");
	int j = 1;	
	return;
}

void vulnFunc(){
	printf("vuln func start\n");
	long i = 0;
	long * pi = &i;
	int offset = 2;
	
	void * pSecrFunc = &secrFunc;
	void * pSecrFuncBody = pSecrFunc + 8;
	pi += offset;
	
	printf("	Adress of pointer: 0x%016lx\n", (unsigned long) pi);
	printf("	Variable before:   0x%016lx\n", *pi);
	*pi = (long *) pSecrFuncBody;
	printf("	Variable after:    0x%016lx\n", *pi);
	
	printf("vuln func return\n");
	return;
}

void bufferFuncForCallStack(){
	printf("buffer func start\n");
	vulnFunc();
	printf("buffer func return\n");
	return;
}

int main(int argc, char *argv[]) {
	printf("main start\n");
	bufferFuncForCallStack();
	printf("main return\n");
}