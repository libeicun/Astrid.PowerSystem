#include "stringExtends.h"
#include <string.h>

static char*  strdelfchr(char* string);//删除string的首个字符，并返回其删除后的字符串。若string为空字符串，则不作任何操作并返回源字符串。
static bool   strincludechr(const char* string,char ch);
extern char*  strfleft(const char* string,const char separator)//TESTED
{
	int len=strlen(string);
  	char* copy=new char[len+1];
	strcpy(copy,string);
	

	for(char* p=copy;*p!='\0';p++)
	{
		if(*p==separator)
		{
			*p='\0';
			break;
		}
	}
	return copy;
}
extern char*  strlright(const char* string,const char separator)//TESTED
{
	int len=strlen(string);
  	char* copy=new char[len+1];
	strcpy(copy,string);
	if(len==0)//若为空字符串
		return copy;
	char* p=copy;
	while(*p!='\0')
		p++;
	p--;//使p指向字符串末位字符
	for(;p!=copy;p--)
	{
		if(*p==separator)
		{
			p++;
			break;
		}
	}
	return p;
}
extern char*  strfleft(char* string,const char separator)//TESTED
{
	for(char* p=string;*p!='\0';p++)
	{
		if(*p==separator)
		{
			*p='\0';
			break;
		}
	}
	return string;
}
extern char*  strlright(char* string,const char separator)//TESTED
{
	int len=strlen(string);
	if(len==0)//若为空字符串
		return string;
	char* p=string;
	while(*p!='\0')
		p++;
	p--;//使p指向字符串末位字符
	for(;p!=string-1;p--)
	{
		if(*p==separator)
		{
			p++;
			break;
		}
	}
	//p指向结果字符串的首字符
	int i;
	for(i=0;*p!='\0';i++,p++)
	{
		string[i]=*p;
	}
	string[i]='\0';
	return string;
}
extern bool   strincludechrs(const char* string,const char* substring)//TESTED
{
	bool rtnflag=true;
	const char* p1;
	for(const char* p2=substring;*p2!='\0';p2++)
	{
		for(p1=string;*p1!='\0';p1++)
		{
			if(*p1==*p2)
				break;
		}
		if(*p1=='\0')
		{
			rtnflag=0;
			return rtnflag;
		}
	}

	return rtnflag;
}

extern char*  strlleft(char* string,char separator)//TESTED
{
	int lindex=-1;
	for(int i=0;string[i]!='\0';i++)
		if(string[i]==separator)
			lindex=i;
	if(lindex==-1)
		return string;
	else
	{
		string[lindex]='\0';
		return string;
	}
}
extern char*  strfright(char* string,char separator)//TESTED
{	
	char* p;
	for(p=string;*p!='\0';p++)
	{
		if(*p==separator)
		{
			p++;
			break;
		}
	}//p指向结果字符串的首字符
	int i;
	for(i=0;*p!='\0';i++,p++)
	{
		string[i]=*p;
	}
	string[i]='\0';
	return string;

}
extern bool   strsubstr(const char* string,const char* substring)//TESTED
{
	if(*substring=='\0')
		return false;
	bool rtnflag=0;
	const char* pstr;
	const char* psubstr=substring;

	const char* p;
	for(p=string;*p!='\0';p++)
	{
		if(*p==*substring)
		{
			rtnflag=1;
			for(pstr=p,psubstr=substring;(*pstr!='\0')&&(*psubstr!='\0');pstr++,psubstr++)
			{
				if(*pstr!=*psubstr)
				{
					rtnflag=0;
					break;
				}

			}
			if((rtnflag==1)&&(*psubstr!='\0'))
				rtnflag=0;

		}

		if(rtnflag==1)
			return rtnflag;
	}
	return rtnflag;
}
extern char*  strdelchr(char* string,char ch)//TESTED
{
	char* pstr=string;
	do{
		if(*pstr==ch)
		{
			strdelfchr(pstr);
			break;
		}
		pstr++;
	}while(*pstr!='\0');
	return string;
}
extern char*  strdelchrs(char* string,char ch)//TESTED
{
	char* pstr=string;
	do{
		if(*pstr==ch)
		{
			strdelfchr(pstr);
		}
		pstr++;
	}while(*pstr!='\0');
	return string;
}
extern char*  strdelstr(char* string,const char* substring);
extern char*  strdelstrs(char* string,const char* substring);
extern char*  strdeln(char* string,int index);
extern char*  strdelbn(char* string,int index);
extern char*  strreverse(char* string)
{

	if(string[0]=='\0')
		return string;
	char* p1=string;
	
	char* p2=string;
	while(*p2)
		p2++;
	p2--;

	char t;

	for(;p1<p2;p1++,p2--)
	{
		t=*p2;
		*p2=*p1;
		*p1=t;
	}
	return string;
}
extern int    strmid(const char* string,const char* substring)
{
	if(*substring=='\0')
		return 0;
	const char* pstr;
	const char* psubstr=substring;
	bool rtnflag=0;
	int index=0;
	for(const char* p=string;*p!='\0';p++)
	{
		if(*p==*substring)
		{
			rtnflag=1;
			for(pstr=p,psubstr=substring;(*pstr!='\0')&&(*psubstr!='\0');pstr++,psubstr++)
			{
				if(*pstr!=*psubstr)
				{
					rtnflag=0;
					break;
				}

			}
			if((rtnflag==1)&&(*psubstr!='\0'))
				rtnflag=0;

		}

		if(rtnflag==1)
			return index;
		index++;

	}
	if(rtnflag==1)
		return index;
	else
		return -1;
}
static char*  strdelfchr(char* string)
{
	char* p_pre=string;
	char* p_nex=p_pre+1;
	if(*p_pre=='\0')//若为空字符串
		return p_pre;
	if(*p_nex=='\0')//若为仅有一个字符的字符串
	{
		*p_pre='\0';
		return p_nex;
	
	}
	while(*p_pre!='\0')
	{
		*p_pre=*p_nex;
		p_pre++,p_nex++;
	}
	return string;
}
static bool   strincludechr(char* string,char ch)
{
	bool rtnflag=0;
	char* p=string;
	if(*p=='\0')//若为空字符串
		return 0;
	do{
		if(*p==ch)
		{
			rtnflag=1;
			break;
		}
		p++;
	}while(*p!='\0');
	return rtnflag;
}
