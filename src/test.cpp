#include "tconfig.hh"
#include "str.test.cpp"
#include "char.test.cpp"
#include "i32.test.cpp"
#include "bool.test.cpp"


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
