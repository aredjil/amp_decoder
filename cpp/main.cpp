#include<boost/numeric/ublas/vector.hpp>
#include<boost/numeric/ublas/io.hpp>


int main()
{
	int n = 10;
	using namespace boost::numeric::ublas;
	vector<double> v(10);
	for(int i=0;i<v.size();++i)
		v(i) = i;
	std::cout<<v<<std::endl;
	return 0;
}
