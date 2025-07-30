#include "tconfig.hh"
#include <gtest/gtest.h>


TEST(boolean,basic)
{
	std::ifstream t("Testing/bol_basic.config",std::ifstream::in);
	std::stringstream buffer;

	ASSERT_TRUE(t.good());

	buffer << t.rdbuf();
	//std::cout << " 1 " << std::endl;
	tconfig::TCParser basicparser(buffer.str());
	//std::cout << " 2 " << std::endl;
	basicparser.parse();
	//std::cout << " 3 " << std::endl;

	EXPECT_EQ(basicparser.getbool("eminem"),true);
	EXPECT_EQ(basicparser.getbool("true_bool"),true);
	EXPECT_EQ(basicparser.getbool("false_bool"),false);
	EXPECT_EQ(basicparser.getbool("immortal"),false);

}


