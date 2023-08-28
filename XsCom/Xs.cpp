#include "D:\CppHeader\winapicore.h"
#include "D:\CppHeader\7zipAPI.h"
#include "D:\CppHeader\GlobalVar.h"
#include<vector>
using namespace std;

string VerCODE = "B1102";

//�������з���
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
		//��ʼ��
		writeini(File, "Record", readfullname,INFO);
		
		startline++;
		startlineS = to_string(startline);
		readfullname = "MRA" + startlineS;

		writeini(File, "Record", readfullname, "mraEnd");
		return VerCODE;
	}
	if (checkDATA == "mraEnd") {
		//��д
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
	cout << "���ڼ��ر༭��" << endl;
	if (_access(XSModFile.c_str(), 0)) {
		cout << "��ʼ�� :  " << XSModFile << endl;
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
	cout << "XS Mod �༭��" << endl;
	cout << "�ļ� :  " << XSModFile << endl;
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
	cout << "��Чָ��" << endl;
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
		//������Ϣ
		string BackInfo = readini($ModelFile, "Xs-Model", $ChatWord);
		if (BackInfo == "readini-failed") {
			MessageBox(0, "ģ�ʹ������⣬�ڳ��Է�����ֵʱ������һ���޷���ȡ��ͷ������ģ�ʹ���MRA�𻵣��볢�����¼���,", "Model Error", MB_OK);
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
	cout << "��������XsModel Runtime Block" << endl;
	cout << "����ģ���� :  " << $ModelFile << endl;

	string $TEMPFOLDER = readini($CFG, "Config", "TempPath");
	string RootFolder = $TEMPFOLDER + "\\ModelRunTime";

	clearfolder(RootFolder);

	mdfolder(RootFolder);
	n7zUNZIP(n7zfile, $ModelFile, RootFolder, "0");
	Sleep(1500);
	string CheckFile = RootFolder + "\\XsComFile.mark";
	if (_access(CheckFile.c_str(), 0)) {
		system("cls");
		cout << "ģ�� :  " << $ModelFile << " ��Ч" << endl;
		cout << "�޷�����ģ�ͣ���֤ģ��XsComFileʧ��" << endl;
		cout << "����ж��ģ��" << endl;
		cout << "�����������" << endl;
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
	cout << "����ģ�����" << endl;
	cout << "�ļ� :  " << $ModelFile << " . mod :  " <<SMods  << endl;
	cout << "ʹ��Shell���в��� :  openmod ѡ��mod�ļ�(Ĭ��Ϊdefault.xsmod),  chat��chatmode,  exitchat�˳�chatmode��" << endl;
	cout << "���� exit ����" << endl;
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
		cout << "ѡ��һ��xsmod����,���� \".xsmod\"" << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		string cmdl = "dir " + RootFolder + "\\XsCModel";
		system(cmdl.c_str());
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "XSMod Select :   _ $";
		getline(cin, SMods);
		string SFilepart = RootFolder + "\\XsCModel\\" + SMods;
		if (_access(SFilepart.c_str(), 0)) {
			cout << "û���ҵ� :  " << SFilepart << endl;
			cout << "���ڼ�����ƺ����ԣ�ȷ������ .xsmod �ļ���׺" << endl;
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
			cout << "�޷����� Chat Box���볢���������� XSMod" << endl;
			system("pause");
			goto RLOPENMOD;
		}
		system("cls");
		cout << "���ڼ���Chat Box" << endl;
		
		Sleep(1000);

		BACKCHATBOX:
		system("cls");
		SetConsoleTitle("Chat Box");
		cout << "Xs �Ѿ����ɹ�����" << endl;
		cout << "ChatBoxģʽ,ʹ�� exitchat �˳�" << endl;
		cout << "ChatScript :   " << SFilePath << endl;
		cout << "��ģ�����ƣ������ʴ���ܻ�����޷��ش����" << endl;
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
			MessageBox(0, "ģ����Ӧ��ʱ������ֵû�б��յ����볢�����¼���ģ���Խ������", "Xs Model Warning", MB_OK);
		}
		cout << BotName << " :  " << $ForwardINFO << endl;
		WriteGlobal("BackInfoS", " ");
		goto ReturnDialog;
	}

	cout << "��Чָ��" << endl;
	system("pause");
	goto BACKXMRS;
}

string XsComBLOCK(string ModelFile, string TempFile) {
	string $ProjectFolder = readini($CFG, "Config", "SavePath");
	string $TEMPFOLDER = readini($CFG, "Config", "TempPath");

	system("cls");
	cout << "���ڼ��� Xs BLOCK" << endl;
	cout << "���Եȣ��������ڼ���XsCM" << endl;

	string $MarkFileP = TempFile + "\\XsComFile.mark";
	Sleep(1500);
	if (_access($MarkFileP.c_str(), 0)) {
		system("cls");
		cout << "�޷����������Ŀ :   " << ModelFile << endl;
		cout << "�޷���֤����Ŀ�Ƿ���Ч,�볢��ʹ��������Ŀ��" << endl;
		system("pause");
		return VerCODE;
	}

	Sleep(2000);
	string XsLockFile = $TEMPFOLDER + "\\.xslock";

XsCMShell:
	cmarkfile(XsLockFile, "Locking Folder");
	system("cls");
	SetConsoleTitle("XsComBlock Shell");
	cout << "��ӭʹ�� Xs Compute Block" << endl;
	cout << "�ѳɹ����� :  " << ModelFile << endl;
	cout << "ʹ�� save ������Ŀ" << endl;
	cout << "ʹ�� close �ر���Ŀ" << endl;
	cout << "ʹ��openxsr ��Ҫȷ����ǰ��Ŀ�Ѿ�����" << endl;
	cout << "���ʹ�ù��������κ�������Գ��������Ƿ���" << endl;
	cout << "Xs " << VerCODE << endl;
	string XSCMType;
	cout << "XSCM Shell   _$ ";
	getline(cin, XSCMType);
	if (XSCMType == "close") {
		system("cls");
		cout << "����Ҫ�ر������Ŀ��" << endl;
		cout << "�����û�б��������Ŀ�����ʧȥ���и���" << endl;
		cout << "�����Ƽ��㷵������ save �Ա�����Ŀ" << endl;
		cout << "���� y �˳������Ŀ,��������ֵ����   _$ ";
			string uselectcp;
			getline(cin, uselectcp);
			if (uselectcp == "y") {
				system("cls");
				cout << "���ڹر���Ŀ :  " << ModelFile << endl;
				cout << "����������ʱ�ļ������Ե�" << endl;
				rmfolder(TempFile);
				remove(XsLockFile.c_str());
				Sleep(1500);
				return VerCODE;
			}
			if (uselectcp == "Y") {
				system("cls");
				cout << "���ڹر���Ŀ :  " << ModelFile << endl;
				cout << "����������ʱ�ļ������Ե�" << endl;
				rmfolder(TempFile);
				remove(XsLockFile.c_str());
				Sleep(1500);
				return VerCODE;
			}
			goto XsCMShell;
	}
	if (XSCMType == "save") {
		system("cls");
		cout << "���ڱ��������Ŀ :  " << ModelFile << endl;
		cout << "���Ե�" << endl;
		remove(ModelFile.c_str());
		string TempPJF = $ProjectFolder + "\\TempPackage~s.zip";
		remove(TempPJF.c_str());
		n7zNewZIP(n7zfile, TempFile + "\\*", TempPJF, "0");
		Sleep(1000);
	RetestSVP:
		rename(TempPJF.c_str(), ModelFile.c_str());
		if (_access(ModelFile.c_str(), 0)) {
			system("cls");
			cout << "�ļ��ϴ������ĵȴ�" << endl;
			cout << "���ڴ����ļ� ... " << endl;
			Sleep(800);
			goto RetestSVP;
		}
		system("cls");
		cout << "���" << endl;
		cout << "��Ŀ�ļ��Ѿ��ɹ��ر��浽�� :  " << ModelFile << endl;
		cout << "��Enter����" << endl;
		getchar();
		goto XsCMShell;
	}
	if (XSCMType == "help") {

		string cmd = "type \"" + $HelpDoc + "\"";
		system(cmd.c_str());
		cout << "��Enter����" << endl;
		getchar();
		goto XsCMShell;
	}
	if (XSCMType == "openxsr") {
		XsModelRun(ModelFile);
		goto XsCMShell;
	}
	if (XSCMType == "edit") {
		system("cls");
		cout << "ѡ��һ��ģ�����" << endl;
		cout << "������������ǻ���д���,ĩβ�벻Ҫ���� \".xsmod\"" << endl;
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
	cout << "δָ֪��볢��ʹ�� help ��ȡ����" << endl;
	cout << "��Enter����" << endl;
	getchar();
	goto XsCMShell;
}

int main(int argc,char* argv[]) {
	//�κ�ΰ������룬��ʼ����С��һ���ж�

	//������Ϣ
	cout << "Xs " << VerCODE << endl;

	//չ��Help
	ofstream outpoint;
	outpoint.open($HelpDoc);
	outpoint << "Xs ��������" << endl;
	outpoint << "��ҳ��" << endl;
	outpoint << "open-root        --�򿪸�Ŀ¼" << endl;
	outpoint << "open-cfg          --�������ļ�" << endl;
	outpoint << "create              --�����µ���Ŀ" << endl;
	outpoint << "load                 --�����Ѿ���������Ŀ" << endl;
	outpoint << endl;
	outpoint << "XsCMָ��" << endl;
	outpoint << "openxsr            --��XSR��Ŀ" << endl;
	outpoint << "save                 --������Ŀ" << endl;
	outpoint << "close                --�ر���Ŀ" << endl;
	outpoint << "edit                  --�༭xsmod�ļ�" << endl;
	outpoint << "..." << endl;
	outpoint << "Copyright FoxaXu 2023" << endl;
	outpoint << endl;

	//���������ļ�
	if (_access($CFG.c_str(), 0)) {
		//����
		writeini($CFG, "Head", "Version", VerCODE);

		//��ʱĿ¼
		string TempPathSet = $PATHL + "\\Temp";
		writeini($CFG, "Config", "TempPath", TempPathSet);
		//������Ŀ�ĵ�ַ
		string SavePathSet = $PATHL + "\\Project";
		writeini($CFG, "Config", "SavePath", SavePathSet);
	}

	//����7Zip
	if (_access(n7zfile.c_str(), 0)) {
		cout << "Download 7zip" << endl;
		string n7zfolder = $PATHL + "\\7zip";
		mdfolder(n7zfolder);
		URLDown(geturlcode("https://developer.foxaxu.com/SoftwareUpdate/FXToolAPI/7zinsexe.api"), n7zfile);
		string n7zfiledll = $PATHL + "\\7zip\\7z.dll";
		URLDown(geturlcode("https://developer.foxaxu.com/SoftwareUpdate/FXToolAPI/7zinsdll.api"), n7zfiledll);
	}

	//���������ļ�
	string $TEMPFOLDER = readini($CFG, "Config", "TempPath");
	string $ProjectFolder = readini($CFG, "Config", "SavePath");
	mdfolder($ProjectFolder);

	bool anticrashclean = existfileA($TEMPFOLDER + "\\.xslock");
	//�ָ�ģʽ
	if (anticrashclean) {
	BACKACC:
		system("cls");
		cout << "Xs �ָ�����" << endl;
		cout << "��ʱ�ļ����������һ��δ��������ļ���Ϊ��ֹ��Ŀ��ʧ���볢�����¼�����Ŀ" << endl;
		cout << "ѡ��֮ǰʹ�õ���Ŀ" << endl;
		cout << "���� skip ����" << endl;
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
			cout << "���ڻ�ԭ :  " << $PGFiles << endl;
			cout << "�������ڼ������ļ�" << endl;
			cout << "���Ե�" << endl;

			Sleep(2000);
			XsComBLOCK($PGFiles, TempFolderS);
			goto TypeLineSS;

 		}
		else {
			cout << "�����޷���ԭ�����Ŀ��δ��Temp�ļ����ҵ������Ŀ" << endl;
			cout << "��������Ŀ�Ƿ�������ȷ" << endl;
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

	//������
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
				MessageBox(0, "��Ч�����ļ�", "Xs Error", MB_OK);
				return 0;
			}
			XsModelRun(XSPFile);
			return 0;
		}
	}

TypeLineSS:
	system("cls");
	SetConsoleTitle("Xs Command");
	cout << "Xs ����̨" << endl;
	cout << "ѡ��ָ���Կ�ʼ" << endl;
	cout << "XsC ������ :  " << $PATHL << endl;
	cout << "XsC �ļ�λ�� :  " << $SelfADR << endl;
	cout << "XsC ��Ŀ�ļ�λ�� :  " << $ProjectFolder << endl;
	cout << "��ʱ�ļ���" << $TEMPFOLDER << endl;
	
	//����ָ̨����
	string $TypeLine;
	cout << endl;
	cout << "XsCom Shell   _$ ";
	getline(cin, $TypeLine);
	cout << endl;

	//ָ���

	if ($TypeLine == "help") {
		system("cls");

		string cmd = "type \"" + $HelpDoc + "\"";
		system(cmd.c_str());
		cout << "��Enter����" << endl;
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
		cout << "�������Ŀ��һ������" << endl;
		cout << "��Ŀ�ļ��������� :  " << $ProjectFolder << endl;
		cout << endl;
	
		string $ProjectFile;
		cout << "Project :  " << $ProjectFile << " \\_$";
		getline(cin, $ProjectFile);
		string CheckFile = $ProjectFolder + "\\" + $ProjectFile + ".xsproj";
		if (_access(CheckFile.c_str(), 0)) {}
		else {
			cout << "��Ŀ :  " << CheckFile << " �Ѿ�����" << endl;
			cout << "�޷�Ϊ�㴴�������Ŀ" << endl;
			cout << "��Enter����" << endl;
			getchar();
			goto TypeLineSS;
		}
		system("cls");
		string $PFData = $ProjectFolder + "\\" + $ProjectFile + ".xsproj";
		cout << "���ڴ��� :  " << $PFData << endl;
		cout << "�Ժ����ǻ���������û���������" << endl;
		string $PFTemp = $TEMPFOLDER + "\\" + $ProjectFile;
		clearfolder($PFTemp);
		Sleep(2000);
		system("cls");
		cout << "���ڹ�����ʱ�ļ���" << endl;
		cout << "Ŀ¼ :  " << $PFTemp << endl;

		cmarkfile($PFTemp + "\\XsComFile.mark", "?");
		
		//�����ļ���
		mdfolder($PFTemp + "\\XsCModel");

		//�����ļ���
		string $PJProF = $PFTemp + "\\Project.cfg";
		writeini($PJProF, "CurrentFormat", "Version", "1");

		//�����ļ���
		Sleep(1000);
		system("cls");
		cout << "������Ŀ :  " << $ProjectFile << ".xsproj" << " ��" << endl;
		cout << "���Ե�" << endl;

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
			cout << "��������Ŀʧ�ܣ�����ж�ص�ǰ��Ŀ" << endl;
			cout << "�볢�����°�װ Xs�� ���������Ǳ����������" << endl;
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
		cout << "ѡ��һ����Ŀ������,ע�ⲻҪ���� \".xsproj\"" << endl;
		cout << "��Ŀ�ļ������� :  " << $ProjectFolder << endl;
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
			cout << "��Ŀ :  " << CheckFile << " δ���ҵ�" << endl;
			cout << "�޷�Ϊ����������Ŀ" << endl;
			cout << "��Enter����" << endl;
			getchar();
			goto TypeLineSS;
		}
		system("cls");
		cout << "���ڼ��� :  " << $ProjectFile << endl;
		cout << "���Ե�" << endl;

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
		cout << "����XSR " << endl;
		cout << "ѡ��һ�������ļ�,������ \".xsproj\" �ļ���׺" << endl;
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
			cout << "��Ч���ƣ��޷��ҵ�����Ҫ���ļ�";
			system("pause");
			goto reopenxsr;
		}
		XsModelRun(realpath);
		goto TypeLineSS;
	}

	if ($TypeLine == "testbox") {
		cout << "���ü���ֽ�" << endl;
		string CHECKLINE;
		cout << "CLINE   _ $ ";
		getline(cin, CHECKLINE);
		char CLines[20];
		strcpy(CLines, CHECKLINE.c_str());
		cout << "��ʼ����" << endl;
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

	cout << "��ʹ�� help ��ȡ������" << endl;
	cout << "��Чָ�� " << endl;
	cout << "��Enter����" << endl;
	getchar();
	goto TypeLineSS;

}

//End