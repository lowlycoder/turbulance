#include "stdio.h"
class Base{
	public:
		Base(){
			i=0;
		}
		virtual int get(){
			return i;
		}
	private:
		int i;
};

class Derived : public Base{
	public:
		Derived(){
			j=1;
		}
		virtual int get(){
			printf("this is %d\n", j);
		}
	private:
		int j;
};

int test(){
	Base *p = 0;
	Derived q;
	p = &q;
	int (*fun)(Base*)=NULL;
	fun = (int(*)(Base*))((*(unsigned int **)&q)[0]);
}

int main(){
	test();
	return 0;
}
