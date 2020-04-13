#include <iostream>

class FibN {
public:
    FibN(int n);
    ~FibN() {};
    int getSum();
private:
    int mPow(int a, int b);
    int n_;
};

FibN::FibN(int n)
{
    n_ = n;
}

int FibN::mPow(int a, int b)
{
    int ret = 1;

    for (int i = 0; i < b; i++)
	ret *= a;

    return ret;
}

int FibN::getSum()
{
    int q = 2;
    int a1 = 1;
    int sum = 0;

    if (n_ == 1) return 1;
    sum += 1; /* fn(1) */
    sum += (mPow(q, n_ - 1) - 1) / (q-1);

    return sum;
}

int main(int argc, char **argv)
{
    int n = 0;
    int sum = 0;
    std::string calcSum;

    if (argc != 2) {
	std::cout << "please check your input: <program> <n>" << std::endl;
	return 0;
    }

    n = std::stoi(argv[1]);
    if (n < 1) {
	std::cout << "\"n\" error" << std::endl;
	return 0;
    }

    FibN fbn(n);
    sum = fbn.getSum();

    std::cout << "sum of fn(1) to fn(" << std::to_string(n) << ") is " <<  std::to_string(sum) << std::endl;

    return 0;
}
