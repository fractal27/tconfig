#include "tconfig.hh"
#include "str.test.cpp"
#include "char.test.cpp"
#include "i32.test.cpp"
#include "bool.test.cpp"


int main(int argc, char** argv)
{
	std::cout << "NOTE: This file must run into the build/ directory, where the Testing directory is located, to get the data for the data assertions." << std::endl;
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
