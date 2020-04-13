#include <iostream>
#include <string>

class FN {
public:
    FN() = delete;
    FN(int n, int start);
    ~FN();
    uint64_t getSumVal();
private:
    uint64_t calcSumVal(int start);
    int n_;
    int start_; 
};

FN::FN(int n, int start)
{
    n_= 0;
    start_ = 0;

    if (n > 0)
	n_ = n;

    if (start > 0 && start <= n)
	start_ = start;
}

FN::~FN()
{
}

uint64_t FN::getSumVal()
{
    uint64_t sumval = 0;

    sumval = calcSumVal(start_);

    return sumval;
}

uint64_t FN::calcSumVal(int start)
{
    uint64_t tmp = 0;

    if (start < n_) {
	return uint64_t(start) + calcSumVal(start+1);
    } else {
	return uint64_t(start);
    }
}

int main(int argc, char **argv)
{
    int n = 0, start = 1;
    uint64_t fnret = 0;

    if (argc == 3) {
	std::string max(argv[1]);
	std::string startno(argv[2]);
    	FN instance(std::stoi(max), std::stoi(startno));

	fnret = instance.getSumVal();
    	std::cout << "fn(" << startno << " - " << max << "): " << fnret << std::endl;
    } else {
	std::cout << "please check your input: <program> <n> <i>" << std::endl;
    }


    return 0;
}
