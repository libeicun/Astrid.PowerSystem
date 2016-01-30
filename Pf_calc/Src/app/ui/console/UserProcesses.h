#ifndef USER_PROCESSES_H
#define USER_PROCESSES_H
#include <list>
#include <string>
using namespace std;
void	fPfCalcOnce(list<string>& paras);
void	fPfBDF(list<string>& paras);
void	fReturn(list<string>& paras);
void	fDefaultProc();
void	fSyscall(list<string>& paras);
void	fLock(list<string>& paras);
void	fUnLock(list<string> &paras);
#endif // !USER_PROCESSES_H
