#include <iostream>
#include <string>

int main()
{
	std::string ourString;
    int b, e, len, ch; // begin of string, end of string, length of string, one character 

	std::cout << "Enter your string: ";
	std::getline (std::cin, ourString);

	len = ourString.length();
	
	for(b = 0, e = len - 1; b < e; e--, b++)
	{
		ch = ourString[b];
		ourString[b] = ourString[e];
		ourString[e] = ch;
	}

	std::cout << ourString << std::endl;
	
    return 0;
}
