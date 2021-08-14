#include<stdio.h>

class ABC {
public:
	ABC() {}
	ABC(ABC* A) {
		printf("Here1\n");
	}
	ABC(const ABC& A) {
		printf("Here2\n");
	}
};
void Fool(ABC A) {

}
ABC Foo2() {
	ABC a;
	return a;
}
int main() {
	ABC* A = new ABC();
	ABC B(A);
	Fool(A);
	Foo2();
}