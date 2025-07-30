#include "tconfig.hh"
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

TEST(str, basic)
{
	//if getting missing initializer, try #include <fstream>
	std::ifstream t("Testing/str_basic.config",std::ifstream::in);
	std::stringstream buffer;

	ASSERT_TRUE(t.good());

	buffer << t.rdbuf();
	//std::cout << " 1 " << std::endl;
	tconfig::TCParser basicparser(buffer.str());
	//std::cout << " 2 " << std::endl;
	basicparser.parse();
	//std::cout << " 3 " << std::endl;

	EXPECT_EQ(basicparser.getstr("basic"),"basic");
	EXPECT_EQ(basicparser.getstr("key"),"configuration");
	EXPECT_EQ(basicparser.getstr("resolution"),"1980x1080");
	EXPECT_EQ(basicparser.getstr("name"),"James");
}
/*
TEST(str, longtext)
{
	std::ifstream t("Testing/str_long.config",std::ifstream::in);
	std::stringstream buffer;

	ASSERT_TRUE(t.good());

	buffer << t.rdbuf();
	//std::cout << " 1 " << std::endl;
	tconfig::TCParser basicparser(buffer.str());
	//std::cout << " 2 " << std::endl;
	basicparser.parse();
	//std::cout << " 3 " << std::endl;

	EXPECT_EQ(basicparser.getstr("config1"),1);
	EXPECT_EQ(basicparser.getstr("config2"),2);
	EXPECT_EQ(basicparser.getstr("config3"),3);
	EXPECT_EQ(basicparser.getstr("config4"),4);

}
*/
