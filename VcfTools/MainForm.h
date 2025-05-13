#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <io.h> // для _findfirst, _findnext
#include <Windows.h> // для MessageBox
#include <msclr/marshal_cppstd.h>  // Для работы со std::wstring
#include "Resource1.h"
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>
std::wstring inputFolder;
std::wstring outputFile;

namespace TextFileMerger {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    

    public ref class MainForm : public Form
    {
    public:

        MainForm(void)
        {
           InitializeComponent();
           LoadAppIcon();
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        
        void LoadAppIcon()
        {
            try
            {
                // Способ 1: Через WinAPI (рекомендуется)
                HICON hIcon = ::LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
                if (hIcon)
                {
                    this->Icon = System::Drawing::Icon::FromHandle(IntPtr(hIcon));
                    return;
                }

                // Способ 2: Резервный - из файла
                /*String^ iconPath = Path::Combine(Application::StartupPath, "Resources\\dropbox.ico");
                if (File::Exists(iconPath))
                {
                    this->Icon = gcnew System::Drawing::Icon(iconPath);
                }*/
            }
            catch (Exception^ e)
            {
                //Debug::WriteLine("Ошибка загрузки иконки: " + e->Message);
                MessageBox::Show("Файл dropbox.ico ненайден", "Ошибка",
                            MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }
        }


        System::Windows::Forms::ProgressBar^ progressBar1;
        System::Windows::Forms::Button^ btnSelectFolder;
        System::Windows::Forms::Button^ btnSelectOutput;
        System::Windows::Forms::Button^ btnMerge;
        System::Windows::Forms::TextBox^ txtLog;
        System::Windows::Forms::Label^ label1;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
           
            this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
            this->btnSelectFolder = (gcnew System::Windows::Forms::Button());
            this->btnSelectOutput = (gcnew System::Windows::Forms::Button());
            this->btnMerge = (gcnew System::Windows::Forms::Button());
            this->txtLog = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();

            // ProgressBar
            this->progressBar1->Location = System::Drawing::Point(20, 320);
            this->progressBar1->Size = System::Drawing::Size(530, 20);
            this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
            this->progressBar1->Text = L"Brogress bar";

            // btnSelectFolder
            this->btnSelectFolder->Location = System::Drawing::Point(20, 70);
            this->btnSelectFolder->Name = L"btnSelectFolder";
            this->btnSelectFolder->Size = System::Drawing::Size(150, 30);
            this->btnSelectFolder->TabIndex = 0;
            this->btnSelectFolder->Text = L"Выбрать папку";
            this->btnSelectFolder->Click += gcnew System::EventHandler(this, &MainForm::btnSelectFolder_Click);

            // btnSelectOutput
            this->btnSelectOutput->Location = System::Drawing::Point(20, 120);
            this->btnSelectOutput->Name = L"btnSelectOutput";
            this->btnSelectOutput->Size = System::Drawing::Size(150, 30);
            this->btnSelectOutput->TabIndex = 1;
            this->btnSelectOutput->Text = L"Выбрать выходной файл";
            this->btnSelectOutput->Click += gcnew System::EventHandler(this, &MainForm::btnSelectOutput_Click);

            // btnMerge Объединить файлы
            this->btnMerge->Location = System::Drawing::Point(20, 170);
            this->btnMerge->Name = L"btnMerge";
            this->btnMerge->Size = System::Drawing::Size(150, 30);
            this->btnMerge->TabIndex = 2;
            this->btnMerge->Text = L"Объединить файлы";
            this->btnMerge->Click += gcnew System::EventHandler(this, &MainForm::btnMerge_Click);

            // txtLog
            this->txtLog->Location = System::Drawing::Point(200, 50);
            this->txtLog->Multiline = true;
            this->txtLog->Name = L"txtLog";
            this->txtLog->ReadOnly = true;
            this->txtLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->txtLog->Size = System::Drawing::Size(350, 250);
            this->txtLog->TabIndex = 3;

            // label1
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(20, 30);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(350, 13);
            this->label1->TabIndex = 4;
            this->label1->Text = L"Выберите папку с файлами и укажите выходной файл:";

            // MainForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(570, 360);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->txtLog);
            this->Controls->Add(this->btnMerge);
            this->Controls->Add(this->btnSelectOutput);
            this->Controls->Add(this->btnSelectFolder);
            this->Controls->Add(this->progressBar1);
            this->Name = L"MainForm";
            this->Text = L"Объединение файлов контактов в формате vcf";
            this->ResumeLayout(false);
            this->PerformLayout();
            this->StartPosition = FormStartPosition::CenterScreen; // Центрирование окна
            
            //HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
            //if (hIcon)
            //{
            //    this->Icon = System::Drawing::Icon::FromHandle(IntPtr(hIcon));
            //    // Не вызывайте DestroyIcon - .NET управляет этим автоматически
            //}
            //else
            //{
            //    // Запасной вариант - загрузка из файла
            //    String^ iconPath = System::IO::Path::Combine(
            //        Application::StartupPath,
            //        "Resources\\app.ico");

            //    if (System::IO::File::Exists(iconPath))
            //    {
            //        this->Icon = gcnew System::Drawing::Icon(iconPath);
            //    }
            //}
            
            
            //try {
            //    this->Icon = gcnew System::Drawing::Icon("dropbox.ico"); // Иконка приложения
            //}
            //catch (...) {
            //    // Обработка ошибки, если иконка не найдена
            //    MessageBox::Show("Файл dropbox.ico ненайден", "Ошибка",
            //        MessageBoxButtons::OK, MessageBoxIcon::Warning);
            //}
        }
#pragma endregion

    private:

        // Обработчик кнопки "Выбрать папку"
        System::Void btnSelectFolder_Click(System::Object^ sender, System::EventArgs^ e)
        {
            FolderBrowserDialog^ folderDialog = gcnew FolderBrowserDialog();
            if (folderDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                inputFolder = msclr::interop::marshal_as<std::wstring>(folderDialog->SelectedPath);
                txtLog->AppendText("Выбрана папка: " + folderDialog->SelectedPath + "\r\n");
            }
        }

        // Обработчик кнопки "Выбрать выходной файл"
        System::Void btnSelectOutput_Click(System::Object^ sender, System::EventArgs^ e)
        {
            SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
            saveDialog->Filter = "Текстовые файлы (*.vcf)|*.vcf";
            if (saveDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
            {
                outputFile = msclr::interop::marshal_as<std::wstring>(saveDialog->FileName);
                txtLog->AppendText("Выходной файл: " + saveDialog->FileName + "\r\n");
                
            }
        }

        

        int CountFilesInDirectory(const std::wstring& directory)
        {
            int fileCount = 0;
            _wfinddata_t fileInfo;
            std::wstring searchPath = directory + L"\\*.vcf";

            intptr_t hFile = _wfindfirst(searchPath.c_str(), &fileInfo);
            if (hFile != -1)
            {
                do {
                    // Пропускаем директории
                    if ((fileInfo.attrib & _A_SUBDIR) == 0) {
                        fileCount++;
                    }
                } while (_wfindnext(hFile, &fileInfo) == 0);

                _findclose(hFile);
            }
            return fileCount;
        }

       

        // Обработчик кнопки "Объединить файлы"
        System::Void btnMerge_Click(System::Object^ sender, System::EventArgs^ e)
        {
            btnMerge->Enabled = false;
            progressBar1->Value = 0;
            txtLog->Clear();

            if (inputFolder.empty() || outputFile.empty())
            {
                MessageBox::Show("Сначала выберите папку и выходной файл!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                btnMerge->Enabled = true;
                return;
            }

            std::wofstream outFile(outputFile, std::ios::app);
            if (!outFile.is_open())
            {
                MessageBox::Show("Не удалось создать выходной файл!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                btnMerge->Enabled = true;
                return;
            }

            int fileCount = CountFilesInDirectory(inputFolder);
            txtLog->AppendText("Найдено " + fileCount + " файлов для обработки\r\n");
            progressBar1->Maximum = fileCount;

            _wfinddata_t fileInfo;
            intptr_t hFile = _wfindfirst((inputFolder + L"\\*.vcf").c_str(), &fileInfo);
            int processedCount = 0;

            if (hFile != -1)
            {
                do {
                    if ((fileInfo.attrib & _A_SUBDIR) == 0) // Пропускаем директории
                    {
                        std::wstring filePath = inputFolder + L"\\" + fileInfo.name;
                        std::wifstream inFile(filePath);

                        if (inFile.is_open())
                        {
                            outFile << inFile.rdbuf();
                            inFile.close();
                            processedCount++;

                            // Обновляем интерфейс
                            txtLog->AppendText(gcnew String(fileInfo.name) + "\r\n");
                            progressBar1->Value = processedCount;
                            progressBar1->Refresh();
                            Application::DoEvents();
                        }
                    }
                } while (_wfindnext(hFile, &fileInfo) == 0);

                _findclose(hFile);
            }

            outFile.close();
            btnMerge->Enabled = true;
            MessageBox::Show("Успешно объединено " + processedCount + " из " + fileCount + " файлов.",
                "Готово", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    };
}
