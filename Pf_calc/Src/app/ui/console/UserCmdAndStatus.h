#ifndef USER_CMD_AND_STATUS_H
#define USER_CMD_AND_STATUS_H

enum eUserCmd
{
	eUserCmdPfCalc=1,
	eUserCmdBuildDataFile,
	eUserReturn
};


enum eStatus
{
	eStatusWaitForCmd=1,
	eStatusPostPfCalc,
	eStatusPostBuildDataFile,
	eStatusErrOccured,
	eStatusLocked
};
#endif // !USER_CMD_AND_STATUS_H

