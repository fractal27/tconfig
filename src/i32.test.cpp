#include "tconfig.hh"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <gtest/gtest.h>

TEST(i32, basic)
{
	std::ifstream t("../Testing/i32_basic.config",std::ifstream::in);
	std::stringstream buffer;

	ASSERT_TRUE(t.good());

	buffer << t.rdbuf();
	//std::cout << " 1 " << std::endl;
	tconfig::TCParser basicparser(buffer.str());
	//std::cout << " 2 " << std::endl;
	basicparser.parse();
	//std::cout << " 3 " << std::endl;

	EXPECT_EQ(basicparser.getint("config1"),1);
	EXPECT_EQ(basicparser.getint("config2"),2);
	EXPECT_EQ(basicparser.getint("config3"),3);
	EXPECT_EQ(basicparser.getint("config4"),4);
	//std::free(&basicparser);
}

TEST(i32, largequantity)
{
	std::ifstream t("../Testing/i32_largequant.config", std::ifstream::in);
	std::stringstream buffer;
	
	ASSERT_TRUE(t.good());

	buffer << t.rdbuf();
	tconfig::TCParser parser(buffer.str());
	parser.parse();

	//EXPECT_EQ(parser.getint("config1"), 25458253);
	EXPECT_EQ(parser.getint("config2"), 16284695);
	EXPECT_EQ(parser.getint("config3"), 34268493);
	EXPECT_EQ(parser.getint("config4"), 12042005);
	//std::free(&parser);
}



