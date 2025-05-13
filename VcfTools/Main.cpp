#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;




//[STAThread] // Важно для Windows Forms
//int main(array<System::String^>^ args)
//{
//    // Включаем визуальные стили
//    Application::EnableVisualStyles();
//    Application::SetCompatibleTextRenderingDefault(false);
//
//    // Создаем и запускаем форму
//    Application::Run(gcnew TextFileMerger::MainForm());
//
//    return 0;
//}

[STAThreadAttribute]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Инициализация UI
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Запуск главной формы (ваш класс находится в namespace TextFileMerger)
    Application::Run(gcnew TextFileMerger::MainForm());

    return 0;
}