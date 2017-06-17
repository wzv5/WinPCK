//////////////////////////////////////////////////////////////////////
// CPckControlCenter.h: 用于解析完美世界公司的pck文件中的数据，并显示在List中
// 头文件,界面与PCK类的数据交互，控制中心
//
// 此程序由 李秋枫/stsm/liqf 编写，pck结构参考若水的pck结构.txt，并
// 参考了其易语言代码中并于读pck文件列表的部分
//
// 此代码预计将会开源，任何基于此代码的修改发布请保留原作者信息
// 
// 2012.10.10
//////////////////////////////////////////////////////////////////////

#pragma once

#include "globals.h"

//#include "PckXchgDef.h"
#include "PckHeader.h"



class CPckClass;

class CPckControlCenter  
{
//函数
public:
	CPckControlCenter();
	CPckControlCenter(HWND hWnd);
	virtual ~CPckControlCenter();
	
	void					init();
	void					Reset(DWORD dwUIProgressUpper = 1);

	LPPCK_RUNTIME_PARAMS	GetParams();
	//void					SetParams(LPPCK_RUNTIME_PARAMS in);

	//BOOL					ConfirmErrors(LPCSTR lpszMainString, LPCSTR lpszCaption, UINT uType);
	//BOOL					ConfirmErrors(LPCWSTR lpszMainString, LPCWSTR lpszCaption, UINT uType);

	void					New();
	//BOOL					Open(LPCSTR lpszFile);
	BOOL					Open(LPCTSTR lpszFile);
	void					Close();

	void					SetPckVersion(int verID);

	LPCTSTR					GetSaveDlgFilterString();


	//界面交互
	//当前操作的列表的index
	CONST INT				GetListCurrentHotItem();
	void					SetListCurrentHotItem(int _val);
	//列表显示模式 ，文件夹显示or 搜索显示模式
	CONST BOOL				GetListInSearchMode();
	void					SetListInSearchMode(BOOL _val);


	///pck 类的交互
	CONST	LPPCKINDEXTABLE		GetPckIndexTable();
	//CONST	LPPCK_PATH_NODE		GetPckPathNode();
	CONST	LPPCKHEAD			GetPckHead();

	//LPCTSTR						GetLastErrorString();


	BOOL						IsValidPck();

	//获取node路径
	BOOL						GetCurrentNodeString(char* szCurrentNodePathString, LPPCK_PATH_NODE lpNode);

	//获取文件数
	DWORD						GetPckFileCount();

	PCKADDR						GetPckSize();
	PCKADDR						GetPckDataAreaSize();
	PCKADDR						GetPckRedundancyDataSize();

	//获取当前配置名称
	LPCSTR						GetCurrentVersionName();


	//预览文件
	BOOL						GetSingleFileData(LPVOID lpvoidFileRead, LPPCKINDEXTABLE lpPckFileIndexTable, char *buffer, size_t sizeOfBuffer = 0);


	//设置附加信息
	char*						GetAdditionalInfo();
	BOOL						SetAdditionalInfo();

	VOID						RenameIndex(LPPCK_PATH_NODE lpNode, char* lpszReplaceString);
	VOID						RenameIndex(LPPCKINDEXTABLE lpIndex, char* lpszReplaceString);

	//重命名一个节点
	BOOL						RenameNode(LPPCK_PATH_NODE lpNode, char* lpszReplaceString);

	//解压文件
	BOOL	ExtractFiles(LPPCKINDEXTABLE *lpIndexToExtract, int nFileCount);
	BOOL	ExtractFiles(LPPCK_PATH_NODE *lpNodeToExtract, int nFileCount);


	//新建pck文件
	BOOL	CreatePckFileMT(LPTSTR szPckFile, LPTSTR szPath);

	//重建pck文件
	BOOL	RebuildPckFile(LPTSTR szRebuildPckFile);

	//更新pck文件
	BOOL	UpdatePckFile(LPTSTR szPckFile, TCHAR (*lpszFilePath)[MAX_PATH], int nFileCount, LPPCK_PATH_NODE lpNodeToInsert);

	//是否是支持更新的文件
	BOOL	isSupportAddFileToPck();

	//重命名文件
	BOOL	RenameFilename();

	//删除一个节点
	VOID	DeleteNode(LPPCK_PATH_NODE lpNode);


	//log日志相关功能 
	void	SetLogListWnd(HWND _hWndList);

	void	PrintLogE(char *);
	void	PrintLogW(char *);
	void	PrintLogI(char *);
	void	PrintLogD(char *);


	void	PrintLogE(wchar_t *);
	void	PrintLogW(wchar_t *);
	void	PrintLogI(wchar_t *);
	void	PrintLogD(wchar_t *);


	//__FILE__, __FUNCTION__, __LINE__
	void	PrintLogE(char *_maintext, char *_file, char *_func, long _line);
	void	PrintLogE(wchar_t *_maintext, char *_file, char *_func, long _line);
	void	PrintLogE(char *_fmt, char *_maintext, char *_file, char *_func, long _line);
	void	PrintLogE(char *_fmt, wchar_t *_maintext, char *_file, char *_func, long _line);

	void	PrintLog(char chLevel, char *_maintext);
	void	PrintLog(char chLevel, wchar_t *_maintext);
	void	PrintLog(char chLevel, char *_fmt, char *_maintext);
	void	PrintLog(char chLevel, char *_fmt, wchar_t *_maintext);

private:
	
	void	CreateRestoreData();
	void	RestoreData(LPCTSTR lpszFile);
	void	DeleteRestoreData();

	//log日志相关功能 
	void	_InsertLogIntoList(int, char *);
	void	_InsertLogIntoList(int, wchar_t *);

public:
	

	LPPCK_PATH_NODE				m_lpPckRootNode;

private:

	BOOL						m_isSearchMode;

	PCK_RUNTIME_PARAMS			cParams;
	CPckClass					*m_lpClassPck;

	BOOL						hasRestoreData;

	TCHAR						m_lpszFile4Restore[MAX_PATH];

	PCKHEAD						m_PckHead;
	LPBYTE						m_lpPckFileIndexData;
	DWORD						m_dwPckFileIndexDataSize;


	//LOG
	HWND						m_hWndMain;
	//HWND						m_hWndLogWnd;
	HWND						m_hWndLogListWnd;
	int							m_LogListCount;

	DWORD						m_dwLastError;

	//格式
	FMTPCK						m_emunFileFormat;

};