#include "D:\CppHeader\winapicore.h"
#include "D:\CppHeader\7zipAPI.h"
#include "D:\CppHeader\GlobalVar.h"
#include<vector>
using namespace std;

string VerCODE = "B1102";

//设置运行分区
string $PATHL = getselfpathA();
string $SelfADR = getselfinfo();
string n7zfile = $PATHL + "\\7zip\\7z.exe";
string $CFG = $PATHL + "\\XsComConfig.cfg";

string $HelpDoc = $PATHL + "\\HelpDoc.txt";

string ModelAddPart(string XSFileSelect,string writehead, string writeinfo) {
	writeini(XSFileSelect, "Xs-Model", writehead, writeinfo);
	return VerCODE;
}

string MAPRecordAdd(string File, string INFO) {
	int startline = 0;
	string readfullname;
	string slnew;
	string startlineS;
	string checkDATA;
	goto BackRecord;

UpScaleStartLine:
	slnew = GetGlobal("XSRecord");
	startline = atoi(slnew.c_str());
	startline++;
BackRecord:
	startlineS = to_string(startline);
	readfullname = "MRA" + startlineS;
	checkDATA = readini(File, "Record", readfullname);
	if (checkDATA == "readini-failed") {
		//初始化
		writeini(File, "Record", readfullname,INFO);
		
		startline++;
		startlineS = to_string(startline);
		readfullname = "MRA" + startlineS;

		writeini(File, "Record", readfullname, "mraEnd");
		return VerCODE;
	}
	if (checkDATA == "mraEnd") {
		//覆写
		writeini(File, "Record", readfullname, INFO);

		startline++;
		startlineS = to_string(startline);
		readfullname = "MRA" + startlineS;

		writeini(File, "Record", readfullname, "mraEnd");
		return VerCODE;
	}

	string olddata = to_string(startline);
	WriteGlobal("XSRecord",olddata);
	goto UpScaleStartLine;
}

string XSMODEdit(string XSModFile,string Path) {
	system("cls");
	cout << "正在加载编辑器" << endl;
	if (_access(XSModFile.c_str(), 0)) {
		cout << "初始化 :  " << XSModFile << endl;
		MAPRecordAdd(XSModFile, "Error");
		MAPRecordAdd(XSModFile, "BotName");
		MAPRecordAdd(XSModFile, "Name");
		ModelAddPart(XSModFile, "StartType", "Hello This is Xs");
		ModelAddPart(XSModFile, "BotName", "Hello My Name is XsCom Bot");
		ModelAddPart(XSModFile, "BOTName", "XsCom Bot");
		ModelAddPart(XSModFile, "Error", "Sorry I cant forward you this question");
	}
	Sleep(800);

	ReSetEdit:
	system("cls");
	cout << "XS Mod 编辑器" << endl;
	cout << "文件 :  " << XSModFile << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	//Type
	string CMDSC = "type \"" + XSModFile + "\"";
	system(CMDSC.c_str());
	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "np --open notepad  add --addchar close ---close edit rf --Refresh  _ $ ";
	string XsEditType;
	getline(cin, XsEditType);
	if (XsEditType == "np") {
		ShellExecute(0, "open", "notepad", XSModFile.c_str(), 0, SW_SHOW);
		goto ReSetEdit;
	}
	if (XsEditType == "add") {
		cout << "set head   _ $ ";
		string WHead;
		getline(cin, WHead);
		cout << endl;
		cout << "set info   _ $ ";
		string WINFO;
		getline(cin, WINFO);
		cout << endl;
		string checkexist = readini(XSModFile, "Xs-Model", WHead);
		if (checkexist == "readini-failed") {
			ModelAddPart(XSModFile, WHead, WINFO);
			MAPRecordAdd(XSModFile, WHead);
		}
		else {
			ModelAddPart(XSModFile, WHead, WINFO);
		}

		
		goto ReSetEdit;
	}
	if (XsEditType == "close") {
		return VerCODE;
	}
	if (XsEditType == "rf") {
		goto ReSetEdit;
	}
	cout << "无效指令" << endl;
	system("pause");
	goto ReSetEdit;
}

//Bot Scan
int checkChar(string text, char* c) {
	if (text.find(c) != string::npos) {
		return 1;
	}
	else {
		return 0;
	}
}

void renTrans(string OldFilePath, string NewName) {
	rename(OldFilePath.c_str(), NewName.c_str());
}

string XsModelForward(string $CHAT,string $ModelFile) {
	int startline = 0;
	string readfullname;
	string slnew;
	string startlineS;
	string $ChatWord;
	string BackInfoBorad;
	goto BackRecord;

UpScaleStartLine:
	slnew = GetGlobal("XSRecordRead");
	startline = atoi(slnew.c_str());
	startline++;
BackRecord:
	startlineS = to_string(startline);
	readfullname = "MRA" + startlineS;
	$ChatWord = readini($ModelFile, "Record", readfullname);
	if ($ChatWord == "mraEnd") {
		Sleep(1000);
		BackInfoBorad = GetGlobal("BackInfoS");
		if (BackInfoBorad == "readini-failed") {
			WriteGlobal("BackInfoS",readini($ModelFile, "Xs-Model", "Error"));
			return VerCODE;
		}
		else {
			BackInfoBorad = GetGlobal("BackInfoS");
			return VerCODE;
		}
	}

	char rWord[20];
	strcpy(rWord, $ChatWord.c_str());
	int ReturnTest = checkChar($CHAT,rWord);
	if (ReturnTest == 1) {
		//返回信息
		string BackInfo = readini($ModelFile, "Xs-Model", $ChatWord);
		if (BackInfo == "readini-failed") {
			MessageBox(0, "模型存在问题，在尝试返回数值时出现了一个无法读取的头，疑似模型存在MRA损坏，请尝试重新加载,", "Model Error", MB_OK);
			return BackInfo;
		}
		BackInfoBorad = GetGlobal("BackInfoS");
		if (BackInfoBorad == "readini-failed") {
			BackInfoBorad = BackInfo;
			WriteGlobal("BackInfoS", BackInfoBorad);
		}
		string NBackInfoBorad = BackInfoBorad + BackInfo;
		WriteGlobal("BackInfoS", NBackInfoBorad);
	}
	else {
		string olddata = to_string(startline);
		WriteGlobal("XSRecordRead", olddata);
		goto UpScaleStartLine;
	}
}

string XsModelRun(string $ModelFile) {
	SetConsoleTitle("Xs Compute Model Run");
	system("cls");
	cout << "正在启动XsModel Runtime Block" << endl;
	cout << "加载模型中 :  " << $ModelFile << endl;

	string $TEMPFOLDER = readini($CFG, "Config", "TempPath");
	string RootFolder = $TEMPFOLDER + "\\ModelRunTime";

	clearfolder(RootFolder);

	mdfolder(RootFolder);
	n7zUNZIP(n7zfile, $ModelFile, RootFolder, "0");
	Sleep(1500);
	string CheckFile = RootFolder + "\\XsComFile.mark";
	if (_access(CheckFile.c_str(), 0)) {
		system("cls");
		cout << "模型 :  " << $ModelFile << " 无效" << endl;
		cout << "无法加载模型，验证模型XsComFile失败" << endl;
		cout << "正在卸载模型" << endl;
		cout << "按任意键返回" << endl;
		rmfolder(RootFolder);
		Sleep(2000);
		system("pause");
		return VerCODE;
	}
	string SMods = "default.xsmod";
	goto BACKXMRS;

	ResetGLV:
	SMods == GetGlobal("SMods");

	BACKXMRS:
	system("cls");
	cout << "加载模型完成" << endl;
	cout << "文件 :  " << $ModelFile << " . mod :  " <<SMods  << endl;
	cout << "使用Shell进行操作 :  openmod 选择mod文件(默认为default.xsmod),  chat打开chatmode,  exitchat退出chatmode，" << endl;
	cout << "输入 exit 返回" << endl;
	cout << endl;
	string XMR;
	cout << "XMR Shell :   _$ ";
	getline(cin, XMR);
	
	if (XMR == "exit") {
		rmfolder(RootFolder);
		return VerCODE;
	}
	if (XMR == "openmod") {
		RLOPENMOD:
		system("cls");
		cout << "选择一个xsmod继续,加上 \".xsmod\"" << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		string cmdl = "dir " + RootFolder + "\\XsCModel";
		system(cmdl.c_str());
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "XSMod Select :   _ $";
		getline(cin, SMods);
		string SFilepart = RootFolder + "\\XsCModel\\" + SMods;
		if (_access(SFilepart.c_str(), 0)) {
			cout << "没有找到 :  " << SFilepart << endl;
			cout << "请在检查名称后重试，确保加上 .xsmod 文件后缀" << endl;
			system("pause");
			goto RLOPENMOD;
		}
		WriteGlobal("SMods", SMods);
		goto ResetGLV;
	}
	if (XMR == "chat") {
		string SFilePath = RootFolder + "\\XsCModel\\" + SMods;
		if (_access(SFilePath.c_str(), 0)) {
			system("cls");
			cout << "无法加载 Chat Box，请尝试重新配置 XSMod" << endl;
			system("pause");
			goto RLOPENMOD;
		}
		system("cls");
		cout << "正在加载Chat Box" << endl;
		
		Sleep(1000);

		BACKCHATBOX:
		system("cls");
		SetConsoleTitle("Chat Box");
		cout << "Xs 已经被成功加载" << endl;
		cout << "ChatBox模式,使用 exitchat 退出" << endl;
		cout << "ChatScript :   " << SFilePath << endl;
		cout << "受模型限制，部分问答可能会出现无法回答情况" << endl;
		cout << "Xs " << VerCODE << " .XsChatBox" << endl;
		cout << "--------------------------------------------------------------" << endl;
		string ChatBoxDialog;

		string starthead = readini(SFilePath, "Xs-Model", "StartType");
		string BotName = readini(SFilePath, "Xs-Model", "BOTName");
		cout << endl;
		cout << BotName << " :  " << starthead << endl;
		ReturnDialog:
		cout << endl;
		cout << "You :   _$";
		getline(cin, ChatBoxDialog);
		cout << endl;
		if (ChatBoxDialog == "exitchat") {
			rmfolder(RootFolder);
			return VerCODE;
		}
		SetConsoleTitle("Processing Info");
		XsModelForward(ChatBoxDialog, SFilePath);
		Sleep(500);
		string $ForwardINFO = GetGlobal("BackInfoS");
		if ($ForwardINFO == "") {
			MessageBox(0, "模型响应超时，返回值没有被收到，请尝试重新加载模型以解决问题", "Xs Model Warning", MB_OK);
		}
		cout << BotName << " :  " << $ForwardINFO << endl;
		WriteGlobal("BackInfoS", " ");
		goto ReturnDialog;
	}

	cout << "无效指令" << endl;
	system("pause");
	goto BACKXMRS;
}

string XsComBLOCK(string ModelFile, string TempFile) {
	string $ProjectFolder = readini($CFG, "Config", "SavePath");
	string $TEMPFOLDER = readini($CFG, "Config", "TempPath");

	system("cls");
	cout << "正在加载 Xs BLOCK" << endl;
	cout << "请稍等，我们正在加载XsCM" << endl;

	string $MarkFileP = TempFile + "\\XsComFile.mark";
	Sleep(1500);
	if (_access($MarkFileP.c_str(), 0)) {
		system("cls");
		cout << "无法加载这个项目 :   " << ModelFile << endl;
		cout << "无法验证此项目是否有效,请尝试使用其他项目。" << endl;
		system("pause");
		return VerCODE;
	}

	Sleep(2000);
	string XsLockFile = $TEMPFOLDER + "\\.xslock";

XsCMShell:
	cmarkfile(XsLockFile, "Locking Folder");
	system("cls");
	SetConsoleTitle("XsComBlock Shell");
	cout << "欢迎使用 Xs Compute Block" << endl;
	cout << "已成功加载 :  " << ModelFile << endl;
	cout << "使用 save 保存项目" << endl;
	cout << "使用 close 关闭项目" << endl;
	cout << "使用openxsr 需要确保当前项目已经保存" << endl;
	cout << "如果使用过程中有任何问题可以尝试向我们反馈" << endl;
	cout << "Xs " << VerCODE << endl;
	string XSCMType;
	cout << "XSCM Shell   _$ ";
	getline(cin, XSCMType);
	if (XSCMType == "close") {
		system("cls");
		cout << "你想要关闭这个项目吗" << endl;
		cout << "如果你没有保存这个项目，你会失去所有更改" << endl;
		cout << "我们推荐你返回输入 save 以保存项目" << endl;
		cout << "输入 y 退出这个项目,输入任意值返回   _$ ";
			string uselectcp;
			getline(cin, uselectcp);
			if (uselectcp == "y") {
				system("cls");
				cout << "正在关闭项目 :  " << ModelFile << endl;
				cout << "正在清理临时文件，请稍等" << endl;
				rmfolder(TempFile);
				remove(XsLockFile.c_str());
				Sleep(1500);
				return VerCODE;
			}
			if (uselectcp == "Y") {
				system("cls");
				cout << "正在关闭项目 :  " << ModelFile << endl;
				cout << "正在清理临时文件，请稍等" << endl;
				rmfolder(TempFile);
				remove(XsLockFile.c_str());
				Sleep(1500);
				return VerCODE;
			}
			goto XsCMShell;
	}
	if (XSCMType == "save") {
		system("cls");
		cout << "正在保存你的项目 :  " << ModelFile << endl;
		cout << "请稍等" << endl;
		remove(ModelFile.c_str());
		string TempPJF = $ProjectFolder + "\\TempPackage~s.zip";
		remove(TempPJF.c_str());
		n7zNewZIP(n7zfile, TempFile + "\\*", TempPJF, "0");
		Sleep(1000);
	RetestSVP:
		rename(TempPJF.c_str(), ModelFile.c_str());
		if (_access(ModelFile.c_str(), 0)) {
			system("cls");
			cout << "文件较大，请耐心等待" << endl;
			cout << "正在处理文件 ... " << endl;
			Sleep(800);
			goto RetestSVP;
		}
		system("cls");
		cout << "完成" << endl;
		cout << "项目文件已经成功地保存到了 :  " << ModelFile << endl;
		cout << "按Enter返回" << endl;
		getchar();
		goto XsCMShell;
	}
	if (XSCMType == "help") {

		string cmd = "type \"" + $HelpDoc + "\"";
		system(cmd.c_str());
		cout << "按Enter返回" << endl;
		getchar();
		goto XsCMShell;
	}
	if (XSCMType == "openxsr") {
		XsModelRun(ModelFile);
		goto XsCMShell;
	}
	if (XSCMType == "edit") {
		system("cls");
		cout << "选择一个模块继续" << endl;
		cout << "如果不存在我们会进行创建,末尾请不要加上 \".xsmod\"" << endl;
		cout << "--------------------------------------------------------------------" << endl;
		string XSRoot = TempFile + "\\XsCModel";
		string cmsds = "dir " + XSRoot;
		system(cmsds.c_str());
		cout << "--------------------------------------------------------------------" << endl;

		string $XSModFile;
		cout << "XSMod Part   _ $ ";
		getline(cin, $XSModFile);
		string XSFileS = TempFile + "\\XsCModel\\" + $XSModFile + ".xsmod";
		
		XSMODEdit(XSFileS,XSRoot);
		goto XsCMShell;
	}
	cout << "未知指令，请尝试使用 help 获取帮助" << endl;
	cout << "按Enter返回" << endl;
	getchar();
	goto XsCMShell;
}

int main(int argc,char* argv[]) {
	//任何伟大的梦想，都始于最小的一步行动

	//启动信息
	cout << "Xs " << VerCODE << endl;

	//展开Help
	ofstream outpoint;
	outpoint.open($HelpDoc);
	outpoint << "Xs 帮助中心" << endl;
	outpoint << "主页项" << endl;
	outpoint << "open-root        --打开根目录" << endl;
	outpoint << "open-cfg          --打开配置文件" << endl;
	outpoint << "create              --创建新的项目" << endl;
	outpoint << "load                 --加载已经创建的项目" << endl;
	outpoint << endl;
	outpoint << "XsCM指令" << endl;
	outpoint << "openxsr            --打开XSR项目" << endl;
	outpoint << "save                 --保存项目" << endl;
	outpoint << "close                --关闭项目" << endl;
	outpoint << "edit                  --编辑xsmod文件" << endl;
	outpoint << "..." << endl;
	outpoint << "Copyright FoxaXu 2023" << endl;
	outpoint << endl;

	//生成配置文件
	if (_access($CFG.c_str(), 0)) {
		//创建
		writeini($CFG, "Head", "Version", VerCODE);

		//临时目录
		string TempPathSet = $PATHL + "\\Temp";
		writeini($CFG, "Config", "TempPath", TempPathSet);
		//保存项目的地址
		string SavePathSet = $PATHL + "\\Project";
		writeini($CFG, "Config", "SavePath", SavePathSet);
	}

	//下载7Zip
	if (_access(n7zfile.c_str(), 0)) {
		cout << "Download 7zip" << endl;
		string n7zfolder = $PATHL + "\\7zip";
		mdfolder(n7zfolder);
		URLDown(geturlcode("https://developer.foxaxu.com/SoftwareUpdate/FXToolAPI/7zinsexe.api"), n7zfile);
		string n7zfiledll = $PATHL + "\\7zip\\7z.dll";
		URLDown(geturlcode("https://developer.foxaxu.com/SoftwareUpdate/FXToolAPI/7zinsdll.api"), n7zfiledll);
	}

	//加载配置文件
	string $TEMPFOLDER = readini($CFG, "Config", "TempPath");
	string $ProjectFolder = readini($CFG, "Config", "SavePath");
	mdfolder($ProjectFolder);

	bool anticrashclean = existfileA($TEMPFOLDER + "\\.xslock");
	//恢复模式
	if (anticrashclean) {
	BACKACC:
		system("cls");
		cout << "Xs 恢复界面" << endl;
		cout << "临时文件夹里面存在一个未被保存的文件，为防止项目丢失，请尝试重新加载项目" << endl;
		cout << "选择之前使用的项目" << endl;
		cout << "输入 skip 跳过" << endl;
		cout << endl;
		cout << "--------------------------------------------------------------------" << endl;
		string cmds = "dir " + $TEMPFOLDER;
		system(cmds.c_str());
		cout << "--------------------------------------------------------------------" << endl;
		cout << endl;
		string userselectload;
		cout << "$Temp    _$ ";
		getline(cin, userselectload);
		if (userselectload == "skip") {
			goto TypeLineSS;
		}
		string TempFolderS = $TEMPFOLDER + "\\" + userselectload;
		
		bool testACCF = existfolder(TempFolderS);
		if (testACCF) {
			system("cls");
			string $PGFiles = $ProjectFolder + "\\" + userselectload + ".xsproj";
			cout << "正在还原 :  " << $PGFiles << endl;
			cout << "我们正在检查你的文件" << endl;
			cout << "请稍等" << endl;

			Sleep(2000);
			XsComBLOCK($PGFiles, TempFolderS);
			goto TypeLineSS;

 		}
		else {
			cout << "我们无法还原你的项目，未在Temp文件中找到你的项目" << endl;
			cout << "检查你的项目是否输入正确" << endl;
			system("pause");
			goto BACKACC;
		}
	}
	else {
	     bool retfoldertemp = existfolder($TEMPFOLDER);
	     if (retfoldertemp) {
		clearfolder($TEMPFOLDER);
	}
	     else {
		mdfolder($TEMPFOLDER);
	}
	}

	//主窗口
	system("cls");
	if (argc > 1) {
		int alg = 0;
		alg++;
		string ParameterA = argv[alg];
		if (ParameterA == "-loadxsp") {
			alg++;
			string XSPFile = argv[alg];
			cout << "Loading Files  :  " << XSPFile << endl;
			if (_access(XSPFile.c_str(), 0)) {
				MessageBox(0, "无效加载文件", "Xs Error", MB_OK);
				return 0;
			}
			XsModelRun(XSPFile);
			return 0;
		}
	}

TypeLineSS:
	system("cls");
	SetConsoleTitle("Xs Command");
	cout << "Xs 控制台" << endl;
	cout << "选择指令以开始" << endl;
	cout << "XsC 运行在 :  " << $PATHL << endl;
	cout << "XsC 文件位置 :  " << $SelfADR << endl;
	cout << "XsC 项目文件位置 :  " << $ProjectFolder << endl;
	cout << "临时文件夹" << $TEMPFOLDER << endl;
	
	//控制台指令栏
	string $TypeLine;
	cout << endl;
	cout << "XsCom Shell   _$ ";
	getline(cin, $TypeLine);
	cout << endl;

	//指令框

	if ($TypeLine == "help") {
		system("cls");

		string cmd = "type \"" + $HelpDoc + "\"";
		system(cmd.c_str());
		cout << "按Enter返回" << endl;
		getchar();
		goto TypeLineSS;
	}
	if ($TypeLine == "open-root") {
		ShellExecute(0, "open", "explorer", $PATHL.c_str(), 0, SW_SHOW);
		goto TypeLineSS;
	}
	if ($TypeLine == "open-cfg") {
		ShellExecute(0, "open", "notepad", $CFG.c_str(), 0, SW_SHOW);
		goto TypeLineSS;
	}

	if ($TypeLine == "create") {
		system("cls");
		cout << endl;
		cout << "给这个项目起一个名字" << endl;
		cout << "项目文件将保存在 :  " << $ProjectFolder << endl;
		cout << endl;
	
		string $ProjectFile;
		cout << "Project :  " << $ProjectFile << " \\_$";
		getline(cin, $ProjectFile);
		string CheckFile = $ProjectFolder + "\\" + $ProjectFile + ".xsproj";
		if (_access(CheckFile.c_str(), 0)) {}
		else {
			cout << "项目 :  " << CheckFile << " 已经存在" << endl;
			cout << "无法为你创建这个项目" << endl;
			cout << "按Enter返回" << endl;
			getchar();
			goto TypeLineSS;
		}
		system("cls");
		string $PFData = $ProjectFolder + "\\" + $ProjectFile + ".xsproj";
		cout << "正在创建 :  " << $PFData << endl;
		cout << "稍后我们会帮助你配置基础的设置" << endl;
		string $PFTemp = $TEMPFOLDER + "\\" + $ProjectFile;
		clearfolder($PFTemp);
		Sleep(2000);
		system("cls");
		cout << "正在挂载临时文件夹" << endl;
		cout << "目录 :  " << $PFTemp << endl;

		cmarkfile($PFTemp + "\\XsComFile.mark", "?");
		
		//创建文件夹
		mdfolder($PFTemp + "\\XsCModel");

		//定义文件夹
		string $PJProF = $PFTemp + "\\Project.cfg";
		writeini($PJProF, "CurrentFormat", "Version", "1");

		//保存文件夹
		Sleep(1000);
		system("cls");
		cout << "保存项目 :  " << $ProjectFile << ".xsproj" << " 中" << endl;
		cout << "请稍等" << endl;

		string CheckOldPack = $ProjectFolder + "\\TempProject.zip";
		if (_access(CheckOldPack.c_str(),0)){}
		else {
			remove(CheckOldPack.c_str());
		}
		n7zNewZIP(n7zfile, $PFTemp + "\\*", $ProjectFolder + "\\TempProject.zip", "0");
		Sleep(1000);
		string Oldname = $ProjectFolder + "\\TempProject.zip";
		string ONewName = $ProjectFolder + "\\" + $ProjectFile + ".xsproj";
		rename(Oldname.c_str(), ONewName.c_str());
		if (_access(ONewName.c_str(), 0)) {
			system("cls");
			cout << "创建新项目失败，正在卸载当前项目" << endl;
			cout << "请尝试重新安装 Xs， 或者向我们报告这个问题" << endl;
			rmfolder($PFTemp);
			Sleep(3000);
			goto TypeLineSS;
		}
		XsComBLOCK(ONewName, $PFTemp);
		goto TypeLineSS;
	}
	if ($TypeLine == "load") {
		system("cls");
		cout << endl;
		cout << "选择一个项目并继续,注意不要加上 \".xsproj\"" << endl;
		cout << "项目文件保存在 :  " << $ProjectFolder << endl;
		cout << endl;
		cout << "--------------------------------------------------------------------" << endl;
		string cmd = "dir " + $ProjectFolder;
		system(cmd.c_str());
		cout << "--------------------------------------------------------------------" << endl;
		cout << endl;


		string $ProjectFile;
		cout << "Project :  " << $ProjectFile << " \\_$";
		getline(cin, $ProjectFile);
		string CheckFile = $ProjectFolder + "\\" + $ProjectFile + ".xsproj";
		if (_access(CheckFile.c_str(), 0)) {
			cout << "项目 :  " << CheckFile << " 未被找到" << endl;
			cout << "无法为你加载这个项目" << endl;
			cout << "按Enter返回" << endl;
			getchar();
			goto TypeLineSS;
		}
		system("cls");
		cout << "正在加载 :  " << $ProjectFile << endl;
		cout << "请稍等" << endl;

		string TEMPPATH = $TEMPFOLDER + "\\" + $ProjectFile;
		clearfolder(TEMPPATH);
		string PackFileSL = CheckFile;
		n7zUNZIP(n7zfile, PackFileSL, TEMPPATH, "0");
		Sleep(800);
	reboolfolderTP:
		bool retTPFold = existfolder(TEMPPATH + "\\XsCModel");
		if (retTPFold) {
			XsComBLOCK(PackFileSL, TEMPPATH);
			goto TypeLineSS;
		}
		else {
			Sleep(1000);
			goto reboolfolderTP;
		}

	}
	if ($TypeLine == "openxsr") {
		reopenxsr:
		system("cls");
		cout << "加载XSR " << endl;
		cout << "选择一个配置文件,不加上 \".xsproj\" 文件后缀" << endl;
		string selprof;
		string xcmcd = "dir " + $ProjectFolder;
		cout << "------------------------------------------------------------------------------" << endl;
		system(xcmcd.c_str());
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "Load XsProj   _ $ ";
		getline(cin, selprof);
		string realpath = $ProjectFolder + "\\" + selprof + ".xsproj";
		if (_access(realpath.c_str(), 0)) {
			system("cls");
			cout << "无效名称，无法找到你需要的文件";
			system("pause");
			goto reopenxsr;
		}
		XsModelRun(realpath);
		goto TypeLineSS;
	}

	if ($TypeLine == "testbox") {
		cout << "设置检测字节" << endl;
		string CHECKLINE;
		cout << "CLINE   _ $ ";
		getline(cin, CHECKLINE);
		char CLines[20];
		strcpy(CLines, CHECKLINE.c_str());
		cout << "开始输入" << endl;
		string TPL;
		cout << "TypeLine   _ $ ";
		getline(cin, TPL);

		cout << endl;
		//BotScan
		if (TPL == "exit") {
			goto TypeLineSS;
		}
		int SCANOUT = checkChar(TPL, CLines);
		if (SCANOUT == 1) {
			cout << "SCAN OUT 1" << endl;
		}
		else {
			cout << "SCAN OUT 0" << endl;
		}
		system("pause");
		goto TypeLineSS;
	}

	cout << "请使用 help 获取帮助，" << endl;
	cout << "无效指令 " << endl;
	cout << "按Enter返回" << endl;
	getchar();
	goto TypeLineSS;

}

//End