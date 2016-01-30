extern char* strfleft(char* string,char separator);
/*该函数返回字符串string的第一个separator（不包括其本身）左边的子字符串。
string为输入字符串，separator为分隔符。
若string中不含separator，则返回源字符串string。
若separator为string的首个字符，则返回空字符串。
若string为空字符串，则返回空字符串。*/
extern char* strlleft(char* string,char separator);
/*该函数返回字符串string的最后一个separator（不包括其本身）左边的子字符串。
string为输入字符串，separator为分隔符。
若string中不含separator，则返回源字符串string。
若separator为string的首个字符，则返回空字符串。
若string为空字符串，则返回空字符串。*/

extern char* strfright(char* string,char separator);
/*该函数返回字符串string的第一个separator（不包括其本身）右边的子字符串。
string为输入字符串，separator为分隔符。
若string中不含separator，则返回源字符串string。
若separator为string的末部字符，则返回空字符串。
若string为空字符串，则返回空字符串。*/

extern char* strlright(char* string,char separator);
/*该函数返回字符串string的最后一个separator（不包括其本身）右边的子字符串。
string为输入字符串，separator为分隔符。
若string中不含separator，则返回源字符串string。
若separator为string的末部字符，则返回空字符串。
若string为空字符串，则返回空字符串。*/
extern char*  strfleft(const char* string,const char separator);
extern char*  strlright(const char* string,const char separator);
extern bool strincludechrs(const char* string,const char* substring);
/*该函数判断两个字符串的匹配结果。
若substring中所有字符均包含于string内（定义为“匹配”），则返回true。否则返回false。
若连字符串相同，返回true。
若substring为空字符串，返回true。
若string为空字符串且substring不是空字符串，返回false。*/

extern bool strsubstr(const char* string,const char* substring);
/*该函数判断两个字符串的包含关系。
若substring包含于string，则返回true。否则返回false。
若两字符串相同，返回true。
若substring为空字符串，返回false。
若string为空字符串且substring不是空字符串，返回false。*/


extern char* strdelchr(char* string,char ch);
/*该函数在string内查找字符ch并删除首次出现者。返回删除目标后的字符串。
若ch不包含于string内，则不作任何操作，返回源字符串。
*/

extern char* strdelchrs(char* string,char ch);
/*该函数在string内查找字符ch并删除所有ch。返回删除目标后的字符串。
若ch不包含于string内，则不作任何操作，返回源字符串。
*/

extern char* strdelstr(char* string,const char* substring);
/*该函数在string内查找字符串substring并删除首次出现者。返回删除目标后的字符串。
若substring不包含于string内，则不作任何操作，返回源字符串。
*/

extern char* strdelstrs(char* string,const char* substring);
/*该函数在string内查找字符串substring并删除所有substring。返回删除目标后的字符串。
若substring不包含于string内，则不作任何操作，返回源字符串。
*/

extern char* strdeln(char* string,int index);
/*该函数删除string内第index（从0开始）个字符。返回删除目标后的字符串。
若index超出字符串长度，则不作任何操作，返回源字符串。
*/

extern char* strdelbn(char* string,int index);
/*该函数删除string内倒数第index（从0开始）个字符。返回删除目标后的字符串。
若index超出字符串长度，则不作任何操作，返回源字符串。
*/
extern char* strreverse(char* string);
/*该函数反转字符串string，并返回反转后的字符串。
若string为空字符串，返回空字符串。*/
extern int   strmid(const char* string,const char* substring);
/*该函数在string内查找子字符串substring，返回首次出现者的对应字符数组下标。
若未找到，返回-1。
若substring为空字符串，返回0.
*/
