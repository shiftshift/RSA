#pragma once

#include<iostream>
#include<vector>
using namespace std;

class RSA
{
public:
	RSA():p(0),q(0),n(0),e(0),d(0),c(0),phi_n(0),m(0),vec1(0),vec2(0){}
	~RSA(){}
	size_t repet_mod(size_t m, vector<int> vec, size_t n);//模重复
	void convert(vector<int> &vec, int e);//十进制转二进制，存到
	int is_not_prime(size_t prime);//检查是否素数
	size_t gcd(size_t phi_n, size_t e);//检查是否同余且余数为1
	size_t inverse(size_t e, size_t phi);//辗转相除
	int clac(size_t in_p, size_t in_q, size_t in_e, size_t in_m);//加密解密
	int step(size_t e, size_t phi, size_t *a, size_t *b);//保存中间值的辗转相除

	size_t get_n()
	{
		return n;
	}
	size_t get_phi_n()
	{
		return phi_n;
	}
	size_t get_d()
	{
		return d;
	}
	size_t get_c()
	{
		return c;
	}
	size_t get_m()
	{
		return m;
	}

private:
	size_t p, q, n, e, d, c, phi_n, m;
	vector<int> vec1;
	vector<int> vec2;
};