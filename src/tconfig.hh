#ifndef TCONFIG_HH
#define TCONFIG_HH
#include <iostream>
#include <string>
#include <map>


namespace tconfig {
	template<typename T>
	 struct tmap{
		std::string key;
		T value;
	};

	typedef union {
		char* str;
		int i32;
		char ch;
		bool bol;
	} sliteral;

	typedef enum {
		str,
		i32,
		ch,
		bol
	} lit_t;

	class literal {

		sliteral lit;
		lit_t type;

		public:

			literal() {};
			literal(sliteral lit,
				lit_t type): lit(lit), type(type) {};
			void setlit(sliteral);
			void settype(lit_t);
			lit_t gettype() const;
			sliteral getlit() const;
	};

	class TCParser
	{
		bool finished;
		unsigned int index;
		unsigned int line;
		std::string text;
		std::map<std::string,literal> mappings; //hash table

		public:
			TCParser(std::string  text);
			TCParser(std::string  text,
				unsigned int index,
				unsigned int line);

			TCParser* parse_nextl();
			TCParser* parse();

			template<typename T>
			tmap<T>* begin();
			template<typename T>
			size_t getlen();

			bool getbool(std::string name);
			int getint (std::string name);
			char getchar(std::string name);
			std::string getstr (std::string name);
	};
};

#endif
