#include "tconfig.hh"
#include <string>
#include <sstream>
#include <fstream>
#include <type_traits>
#include <cstring>

bool isdigit(std::string str){
	char* p;
	long converted = strtol(str.c_str(), &p, 10);
	return !bool(*p);
}

tconfig::TCParser::TCParser(std::string text)
{
	this->text = text;
	this->index = 0;
	this->line = 0;
	this->finished = false;
}

tconfig::TCParser::TCParser(std::string text,
			    unsigned int index,
			    unsigned int line)
{
	this->text = text;
	this->index = index;
	this->line = line;
}


void
tconfig::literal::setlit(tconfig::sliteral lit){
	this->lit = lit;
}

void
tconfig::literal::settype(tconfig::lit_t type){
	this->type = type;
}


tconfig::sliteral
tconfig::literal::getlit() const{
	return this->lit;
}

tconfig::lit_t
tconfig::literal::gettype() const{
	return this->type;
}



tconfig::TCParser*
tconfig::TCParser::parse_nextl()
{
	bool eq = false;
	
	if(this->finished){
		std::cout << "tconfig: TCParser: already finished parsing" << std::endl;
		return this;
	}
#ifdef DEBUG
	std::cout << "---- DEBUG parser line " << this->line << "-----" <<
		std::endl;
#endif

	std::string varname = "";
	std::string literal = "";
	int original_index = this->index;

#ifdef DEBUG
	std::cout << "parsing string `" << this->text.substr(this->index) << "`:"
		  << "\nwith index " << this->index << std::endl
		  << "\nfrom text " << "\"" << this->text << "\"\n";
#endif

	this->line++;

	for(char c: this->text.substr(this->index)){
#ifdef DEBUG
		std::cout << "\tparsing character \"" << c << "\"" << std::endl;
#endif

		if(c == '\n'){
			this->index++;
			break;
		}
		if(c == '='){

			eq = true;
		} else if (!(std::isspace(c))) {
			if (!eq){
				// equals not passed= varname
				varname += c;

			} else {
				// equals passed= literal
				literal += c;

			}

		}
		this->index++;
	}

	if(index == original_index){
		this->finished = true;
		return this;
	}

	if(literal == varname && literal == "")
	{
		return this;
	}

	tconfig::literal literal_map;
	tconfig::sliteral lit;

	if(literal == "false")
	{
		lit.bol = false;
		literal_map.setlit(lit);
		literal_map.settype(tconfig::lit_t::bol);
#ifdef DEBUG
		std::cout << "\ttype: boolean" << std::endl;
#endif
	} else if (literal == "true"){
		lit.bol = true;
		literal_map.setlit(lit);
		literal_map.settype(tconfig::lit_t::bol);
#ifdef DEBUG
		std::cout << "\ttype: boolean" << std::endl;
#endif

	} else if (literal.find('\"') == 0){
		std::string fin_str = (literal.substr(1,
				literal.length()-2));
		char* lit_str = (char*) malloc(sizeof(char)*(fin_str.length()+1));
		strncpy(lit_str,fin_str.c_str(),fin_str.length());
		lit_str[fin_str.length()] = '\0';
		lit.str = lit_str;

		literal_map.setlit(lit);
		literal_map.settype(tconfig::lit_t::str);
#ifdef DEBUG
		std::cout << "\ttype: string" << std::endl;
#endif

	} else if (literal.find('\'') == 0){
		if(literal.length() <= 2){
			std::cerr << "ERROR: LENGHT TOO SMALL"
				     "FOR CHARACTER."
				  << std::endl;
			return this;
		}

		lit.ch = literal[1];
		literal_map.setlit(lit);
		literal_map.settype(tconfig::lit_t::ch);

#ifdef DEBUG
		std::cout << "type: character" << std::endl;
#endif
	} else if (isdigit(literal)) {
		lit.i32 = std::stoi(literal);
		literal_map.setlit(lit);
		literal_map.settype(tconfig::lit_t::i32);
#ifdef DEBUG
		std::cout << "\ttype: integer" << std::endl;
#endif

	} else {
		std::cerr << "tconfig: ERROR: LITERAL NOT RECOGNIZED AT"
			     "LINE" << this->line << std::endl;
		if(eq) this->index = original_index;
		return this;
	}

#ifdef DEBUG
	std::cout << "mapped \"" << varname << "\" to \""
		  << literal     << "\"" << std::endl;
#endif
	this->mappings[varname] = literal_map;
	if(this->line == this->text.length()-1){
		this->finished = true;
	}
	return this;

}
tconfig::TCParser*
tconfig::TCParser::parse(){

	while(!(this->finished)){
		this->parse_nextl(); // parse line
	}

#ifdef DEBUG
	std::cout << "---- finished parsing. ----" << std::endl;
#endif
	return this;
}

template<typename T>
tconfig::tmap<T>* 
tconfig::TCParser::begin(){

	std::map<std::string,tconfig::literal> map = this->mappings;
	tconfig::tmap<T>* begin = malloc(sizeof(tconfig::tmap<T>) *
					 this->mappings.size());
	size_t index = 0;

	for (auto const& x : map)
	{

		if(x.second.gettype() == tconfig::lit_t::str &&
		   	  std::is_same<T,std::string>::value){
			begin[index].key = x.first;
			begin[index].value = x.second.getlit().str;
		} else if(x.second.gettype() == tconfig::lit_t::bol &&
			  std::is_same<T,bool>::value){
			begin[index].key = x.first;
			begin[index].value = x.second.getlit().bol;
		} else if(x.second.gettype() == tconfig::lit_t::ch &&
			  std::is_same<T,char>::value){
			begin[index].key = x.first;
			begin[index].value = x.second.getlit().ch;
		} else if(x.second.gettype() == tconfig::lit_t::i32 &&
			  std::is_same<T,int>::value){
			begin[index].key = x.first;
			begin[index].value = x.second.getlit().i32;
		}

		index++;
	}

	return realloc(begin, sizeof(tconfig::tmap<T>) * index);
};


template<typename T>
size_t
tconfig::TCParser::getlen(){

	std::map<std::string,tconfig::literal> map = this->mappings;
	size_t index = 0;
	size_t size = 0;
	for (auto const& x : map)
	{
		
		if(x.second.gettype() == tconfig::lit_t::str &&
		   std::is_same<T, std::string>::value){
			size++;

		} else if(x.second.gettype() == tconfig::lit_t::bol &&
			  std::is_same<T, bool>::value){
			size++;
		} else if(x.second.gettype() == tconfig::lit_t::ch &&
			  std::is_same<T, char>::value){
			size++;
		} else if(x.second.gettype() == tconfig::lit_t::i32 &&
			  std::is_same<T, int>::value){
			size++;
		}


		index++;
	}
	return size;
}

bool
tconfig::TCParser::getbool(std::string name)
{
	if(this->mappings[name].gettype() == tconfig::lit_t::bol)
	{
		return this->mappings[name].getlit().bol;
	}
	std::cerr << "TCParser: ERROR: boolean not found with name \""<< name <<"\"";
	tconfig::lit_t type = this->mappings[name].gettype();
	std::string newtype = type == tconfig::lit_t::bol
					? "" // never gonna happen( case already checked before )
					: type == tconfig::lit_t::str
					  ? "string"
					  : type == tconfig::lit_t::i32
					    ? "integer"
					    : type == tconfig::lit_t::ch
					      ? "character"
				              : "?";
	std::cout << "instead found type: " << newtype << "\n";
	exit(1);
}

int
tconfig::TCParser::getint(std::string name)
{
	if(this->mappings[name].gettype() == tconfig::lit_t::i32)
	{
		return this->mappings[name].getlit().i32;
	}

	std::cerr << "TCParser: ERROR: integer not found with name \""<< name <<"\"\n";

	tconfig::lit_t type = this->mappings[name].gettype();
	std::string newtype = type == tconfig::lit_t::bol
					? "boolean"
					: type == tconfig::lit_t::str
					  ? "string"
					  : type == tconfig::lit_t::i32
					    ? ""
					    : type == tconfig::lit_t::ch
					      ? "character"
				              : "?";
	std::cout << "instead found type: " << newtype << "\n";
	exit(1);
}

char
tconfig::TCParser::getchar(std::string name)
{
	if(this->mappings[name].gettype() == tconfig::lit_t::ch)
	{
		return this->mappings[name].getlit().ch;
	}
	std::cerr << "TCParser: ERROR: char not found with name \""<< name <<"\"";
	tconfig::lit_t type = this->mappings[name].gettype();
	std::string newtype = type == tconfig::lit_t::bol
					? "boolean"
					: type == tconfig::lit_t::str
					  ? "string"
					  : type == tconfig::lit_t::i32
					    ? "integer"
					    : "";
	std::cout << "instead found type: " << newtype << "\n";
	exit(1);
}

std::string
tconfig::TCParser::getstr(std::string name)
{
	if(this->mappings[name].gettype() == tconfig::lit_t::str)
	{
		return this->mappings[name].getlit().str;
	}
	std::cerr << "TCParser: ERROR: string not found with name \""<< name <<"\"";
	exit(1);
}




