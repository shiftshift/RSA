#include"RSA.h"

size_t RSA::repet_mod(size_t m, vector<int> vec, size_t n)
{
	size_t s = 1;
	int i = 0;
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		if (*it == 1)
			s = (s*m) % n;
		m = (m*m) % n;
	}
	return s;
}

void RSA::convert(vector<int> &vec, int e)//十进制转二进制，存到vec容器中
{
	int remainder = 0;//余数
	int divisor = 2;//除数
	while (1)
	{
		if (e >= divisor)
		{
			remainder = e % divisor;
			vec.push_back(remainder);
			e = e / divisor;
		}
		else
		{
			remainder = e % divisor;
			vec.push_back(remainder);
			break;
		}
	}
}

int RSA::is_not_prime(size_t prime)
{
	for (int i = 2; i <= sqrt(prime); i++)
	{
		if (prime%i == 0)
		{
			return 1;
		}
	}
	return 0;
}

size_t RSA::gcd(size_t phi_n, size_t e)
{
	return e == 0 ? phi_n : gcd(e, phi_n % e);
}

size_t RSA::inverse(size_t e, size_t phi)
{
	int a = phi, b = e;
	int x = 0, y = 1, x0 = 1, y0 = 0, q, temp;
	while (a != 0) {
		q = b / a;
		temp = b % a;
		b = a;
		a = temp;
		temp = x; x = x0 - q * x; x0 = temp;
		temp = y; y = y0 - q * y; y0 = temp;
	}
	if (x0 < 0) x0 += phi;
	return x0;
}

int RSA::clac(size_t in_p, size_t in_q, size_t in_e, size_t in_m)
{
	if (is_not_prime(in_p) || is_not_prime(in_q))
		return 0;

	this->p = in_p;
	this->q = in_q;
	this->e = in_e;
	this->m = in_m;

	this->n = this->p * this->q;
	this->phi_n = (this->p - 1)*(this->q - 1);
	if (gcd(this->phi_n, this->e) != 1)
		return 0;
	this->d= inverse(this->e, this->phi_n);
	convert(this->vec1, this->e);
	convert(this->vec2, this->d);

	this->c= repet_mod(this->m, this->vec1, this->n);
	this->m = repet_mod(this->c, this->vec2, this->n);

	return 1;
}

int RSA::step(size_t e, size_t phi, size_t *a , size_t *b)
{
	int inv_a, inv_b,tmp;
	int i = 0, j = 0;
	a[0] = e;
	b[0] = phi;
	while (a[i] % b[j] != 0)
	{
		i++;
		j++;
		a[i] = b[j - 1];
		b[j] = a[i - 1] % b[j - 1];
	}
	return 1;
}