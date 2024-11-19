#include "tconfig.hh"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <gtest/gtest.h>

TEST(ch, basic)
{
	std::ifstream t("../Testing/char_basic.config",std::ifstream::in);
	std::stringstream buffer;

	ASSERT_TRUE(t.good());

	buffer << t.rdbuf();
	tconfig::TCParser basicparser(buffer.str());
	basicparser.parse();

	EXPECT_EQ(basicparser.getchar("a"),'a');
	EXPECT_EQ(basicparser.getchar("B"),'B');
	EXPECT_EQ(basicparser.getchar("c"),'c');
	EXPECT_EQ(basicparser.getchar("D"),'D');
	//std::free(&basicparser);
}


TEST(ch,spaces)
{
	std::ifstream t("../Testing/char_wspaces.config", std::ifstream::in);
	std::stringstream buffer;
	//std::cout << " 1 " << std::endl;
	ASSERT_TRUE(t.good());
	//std::cout << " 2 " << std::endl;

	buffer << t.rdbuf();
	//std::cout << " 3 " << std::endl;
	tconfig::TCParser parser(buffer.str());

	//std::cout << " 4 " << std::endl;

	parser.parse();

	//std::cout << " 5 " << std::endl;

	ASSERT_EQ(parser.getchar("A"),'A');
	ASSERT_EQ(parser.getchar("b"),'b');
	ASSERT_EQ(parser.getchar("C"),'c');
	ASSERT_EQ(parser.getchar("D"),'D');
	ASSERT_EQ(parser.getchar("e"),'e');
}


