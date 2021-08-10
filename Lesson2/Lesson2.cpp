// Lesson2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
	for (int i = 1; i <= n; i++)
	{
		result *= i;
	}
	return result;
}

int main()
{
	int n = 0;
	std::cout << "Nhap so nguyen duong:";
	std::cin >> n;
	while (n <= 0) {
		std::cout << "Khong phai so nguyen duong\nNhap lai:";
		std::cin >> n;
	}
	std::cout << "Gia tri cua " << n << "! la:" << factorial(n);
}

