#include <iostream>

class FibN {
public:
    FibN(int n);
    ~FibN() {};
    int getFn() {return fn_;};
private:
    int calcFn(int n);
    int n_;
    int fn_;
};

FibN::FibN(int n)
{
    n_ = n;
    fn_ = calcFn(n);
}

int FibN::calcFn(int n)
{
    int i = 1;
    int ret = 0;

    if (n == 2) {
	return 1;
    } else if (n == 1) {
	return 1;
    }
    for (; i < n; i++) {
	ret += calcFn(i);
    }
    return ret;
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

    for (int i = 1; i <= n; i++) {
	int fnv = 0;
        FibN fbn(i);
	fnv = fbn.getFn();
	sum += fnv;
	if (i != 1) {std::cout << "+ "; calcSum += " + ";};
	calcSum += std::to_string(fnv);
	std::cout << "fn(" + std::to_string(i) + ") "; 
    }
    std::cout << "= " << calcSum<< "= " << sum << std::endl;

    return 0;
}
