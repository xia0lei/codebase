#include <iostream>

class A{
	public:
		int a = 0;

		bool operator<(const A& object){
			return (a < object.a)? true:false;
		}

		std::ostream & operator<<(std::ostream &out){
			out << a;
			return out;
		}
};

template<class T>
inline T const& max( const T& a, const T& b){
	return a < b ? b:a;
}

int main(){
	auto max = ::max(3,2);
	std::cout <<"max int "<<max<<std::endl;

	max = ::max(4.0, 4.01);
	std::cout <<"max double"<<max<<std::endl;

	std::string s1 = "mathematics";
	std::string s2 = 	"math";
	std::cout<<"max(s1, s2): "<<::max<std::string>(s1, s2)<<std::endl;

	return 0;
}