

#include <iostream>
#include<stack>
#include<vector>
#pragma warning (once : 4996)

char* begin = nullptr;
char* end = nullptr;

bool CutPiece(char* begin, char* end) //функция вырезает область между скобками в строке, включая сами скобки.
    //при этом, проверяя четность количества скобкок типа |
{
    int lenght = end - begin;
    int count = 0;
    for (int i = 1; i <= lenght-1; ++i)
    {
        if (begin[i] == '|')
        {
            count++;
        }
    }
    char* buff = _strdup(end+1); //строка, начиная с символа после правой скобки
    begin[0] = '\0'; //вставляем теминальный символ вместо левой скобки для корректной раобты функции strcat()
    strcat(begin, buff);
    delete[]buff;
    return count % 2 == 0;
}
std::pair<char,char> IsABracket(char c, std::vector<std::pair<char, char>> brackets) //фнкция проверяет является 
    //ли символ скобкой и возвращает пару правой и левой скобки, если да 
{
    std::pair<char, char> empty = { '\0','\0' };
    for (auto v : brackets)
    {
        if (c == v.first || c == v.second)
        {
            return v;
        }
    }
    return empty;
}

bool check(char str[], std::vector<std::pair<char, char>> brackets)
{
    std::stack<char*> stackBrackets;
    int i = 0;
    int count = 0;

    while (str[i])
    {
        if (IsABracket(str[i], brackets).first == str[i])
        {
            stackBrackets.push(str + i);
            begin = str + i;
        }
        else if (IsABracket(str[i], brackets).second == str[i])
        {
            if (stackBrackets.size() == 0)
            {
                return false;
            }
            char *c = stackBrackets.top(); 
            if (IsABracket(str[i], brackets).first != *c)
            {
                return false;
            }
            stackBrackets.pop();
            end = str + i;

            if (!CutPiece(c, end))
            {
                return false;
            }
            i = c - str -1;
        }
        ++i;
        count++;
    }
    if (stackBrackets.size() != 0)
    {
        return false;
    }
    return true;
}
std::vector<std::pair<char, char>> brackets =
{
    {'{','}'},
    {'(',')'},
    {'[',']'}
};


int main()
{
    char str1[] = "((.))[[(', ')]]";
    char str2[] = "'((()))()', [['(', ')']]";
    char str3[] = "'())(', [['(', ')']]";
    char str4[] = "'([{}])', [['(', ')'], ['[', ']'], ['{', '}']]";
    char str5[] = "'[(])', [['(', ')'], ['[', ']']]";
    char str6[] = "'[]()', [['(', ')'], ['[', ']']]";
    char str7[] = "'[]()(', [['(', ')'], ['[', ']']]";
   
    char str8[] = "'||', [['|', '|']]";
    char str9[] = "'|()|', [['(', ')'], ['|', '|']]";
    char str10[] = "'|(|)', [['(', ')'], ['|', '|']]";
    char str11[] = "'|()|(||)||', [['(', ')'], ['|', '|']]";

    std::cout << check(str1, brackets) << std::endl;
    std::cout << check(str2, brackets) << std::endl;
    std::cout << check(str3, brackets) << std::endl;
    std::cout << check(str4, brackets) << std::endl;
    std::cout << check(str5, brackets) << std::endl;
    std::cout << check(str6, brackets) << std::endl;
    std::cout << check(str7, brackets) << std::endl;
    std::cout <<  std::endl;

    std::cout << check(str8, brackets) << std::endl;
    std::cout << check(str9, brackets) << std::endl;
    std::cout << check(str10, brackets) << std::endl;
    std::cout << check(str11, brackets) << std::endl;
    return 0;
}

