#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;




//[STAThread] // ����� ��� Windows Forms
//int main(array<System::String^>^ args)
//{
//    // �������� ���������� �����
//    Application::EnableVisualStyles();
//    Application::SetCompatibleTextRenderingDefault(false);
//
//    // ������� � ��������� �����
//    Application::Run(gcnew TextFileMerger::MainForm());
//
//    return 0;
//}

[STAThreadAttribute]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ������������� UI
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // ������ ������� ����� (��� ����� ��������� � namespace TextFileMerger)
    Application::Run(gcnew TextFileMerger::MainForm());

    return 0;
}