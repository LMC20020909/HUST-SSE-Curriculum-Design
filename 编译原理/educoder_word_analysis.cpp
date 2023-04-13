#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, char* argv[])
{
    ifstream fs;
    fs.open(argv[1]);
	if (fs.is_open())
	{
		//cout << "文件打开成功！" << endl;
		string buff;
		while (fs >> buff)
		{
			/*1 int  2 while  3 if  4 else  5 return 50  标识符 51 整常数
			60 +   61 -   62 *   63 /
			64 =   65 <   66 <=   67 >   68 >=   69 ==   70 !=
			71 {   72 }   73 (   74 )   75 ，  76 ;*/
			if (buff == "int") cout << "(1,-) ";
			else if (buff == "while") cout << "(2,-) ";
			else if (buff == "if") cout << "(3,-) ";
			else if (buff == "else") cout << "(4,-) ";
			else if (buff == "return") cout << "(5,-) ";
			else
			{
				for (int i = 0;i < buff.size();++i) {
					if (buff[i] == '+') cout << "(60,-) ";
					else if (buff[i] == '-') cout << "(61,-) ";
					else if (buff[i] == '*') cout << "(62,-) ";
					else if (buff[i] == '/') cout << "(63,-) ";
					else if (buff[i] == '=') {
						if (buff[i + 1] != '=') {
							cout << "(64,-) ";
						}
						else
						{
							cout << "(69,-) ";
							++i;
						}
					}
					else if (buff[i] == '<') {
						if (buff[i + 1] != '=') {
							cout << "(65,-) ";
						}
						else
						{
							++i;
							cout << "(66,-) ";
						}
					} 
					else if (buff[i] == '>') {
						if (buff[i + 1] != '=') {
							cout << "(67,-) ";
						}
						else
						{
							cout << "(68,-) ";
							++i;
						}
					} 
					else if (buff[i] == '!') {
						if (buff[i + 1] != '=') {
							cout << "\n<error character \'" << buff << "\' in line %d> ";
						}
						else {
							cout << "(70, -) ";
							++i;
						}
					}
					else if (buff[i] == '{') cout << "(71,-) ";
					else if (buff[i] == '}') cout << "(72,-) ";
					else if (buff[i] == '(') cout << "(73,-) ";
					else if (buff[i] == ')') cout << "(74,-) ";
					else if (buff[i] == ',') cout << "(75,-) ";
					else if (buff[i] == ';') cout << "(76,-) ";
					else if (buff[i] >= '0' && buff[i] <= '9') {
						string s;
						for (int j = i;j < buff.size();++j) {
							if (buff[j] >= '0' && buff[j] <= '9') {
								s.push_back(buff[j]);
							}
							else
							{
								i = j-1;
								break;
							}
						}
						cout << "(51," << s << ") ";
					}
					else if ((buff[i] >= 'a' && buff[i] <= 'z') || (buff[i] >= 'A' && buff[i] <= 'Z')) {
						string s;
						for (int j = i;j < buff.size();++j) {
							if ((buff[j] >= '0' && buff[j] <= '9') || (buff[j] >= 'a' && buff[0] <= 'z') ||
                            		(buff[j] >= 'A' && buff[0] <= 'Z')) 
                            {
								s.push_back(buff[j]);
							}
							else
							{
								i = j-1;
								break;
							}
						}
						cout << "(50,\"" << s << "\") ";
					}
					else
					{
						cout << "\n<error character \'" << buff << "\' in line %d> ";
					}
				}
			}
			//cout << buff << endl;
		}
	}
	else
	{
		cout << "error" << endl;
	}
}



