#pragma once


#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "CNC\INC\CNC.h"
#include "switch.h"
#include "simulate.h"

#if !DEBUG
#include "DRV\INC\stepMotorDRV.h"
#endif


using std::string;
using namespace System;

/*=======Global Define=======*/
int counter = 0;
CNC* cnc_system;

//
//simulation
//
double simu_u_valid,simu_v_valid,simu_w_valid;
bool simu_open;
/*=======/Global Define=======*/

//
//init time record
//
std::time_t start_time;

//
//machine define
//
#if !DEBUG
void _stdcall Timer_ISR_Function(LIOINT *pstINTSource)
{
	cnc_system->CNC_main_rt();
}
#endif




/*=============================================================*/
//typeChange
/*=============================================================*/
void MarshalString ( String ^ s, string& os )//System::string to std::string
{
   using namespace Runtime::InteropServices;
   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

/*=============================================================*/
String^ s2S (string& os) //std::string to System::string
{
   String^ SystemString = gcnew String(os.c_str());
   return SystemString;
}
/*=============================================================*/
namespace iCNC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			cnc_system = new CNC;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete cnc_system;
				delete components;
			}
		}
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Button^  button_openFile;
		private: System::Windows::Forms::OpenFileDialog^  openFileDialog_openNC;
		private: System::Windows::Forms::RichTextBox^  richTextBox_ncFile;
		private: System::Windows::Forms::TextBox^  textBox_filePath;
		private: System::Windows::Forms::TrackBar^  trackBar_feedOverride;
		private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::Label^  label_showX;
		private: System::Windows::Forms::Label^  label_showY;
		private: System::Windows::Forms::Label^  label_showZ;
		private: System::Windows::Forms::Timer^  RT_timer;
		private: System::Windows::Forms::Timer^  NRT_timer;
		private: System::Windows::Forms::Button^  button_uvw;
		private: System::Windows::Forms::Button^  button_zp;
		private: System::Windows::Forms::Button^  button_yp;
		private: System::Windows::Forms::Button^  button_xp;
		private: System::Windows::Forms::GroupBox^  groupBox1;
		private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
		private: System::Windows::Forms::Label^  Label_M30;
		private: System::Windows::Forms::Label^  Label_M00;
		private: System::Windows::Forms::Label^  Label_PGM;
		private: System::Windows::Forms::Label^  Label_ERR;
		private: System::Windows::Forms::Label^  Label_HX;
		private: System::Windows::Forms::Label^  Label_INX;
		private: System::Windows::Forms::Label^  Label_HY;
		private: System::Windows::Forms::Label^  Label_INY;
		private: System::Windows::Forms::Label^  Label_HZ;
		private: System::Windows::Forms::Label^  Label_INZ;
		private: System::Windows::Forms::Label^  Label_PX;
		private: System::Windows::Forms::Label^  Label_NX;
		private: System::Windows::Forms::Label^  Label_PY;
		private: System::Windows::Forms::Label^  Label_NY;
		private: System::Windows::Forms::Label^  Label_PZ;
		private: System::Windows::Forms::Label^  Label_NZ;
		private: System::Windows::Forms::GroupBox^  groupBox2;
		private: System::Windows::Forms::GroupBox^  groupBox3;
		private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
		private: System::Windows::Forms::Label^  label_showU;
		private: System::Windows::Forms::Label^  label8;
		private: System::Windows::Forms::Label^  label_showW;
		private: System::Windows::Forms::Label^  label_showV;
		private: System::Windows::Forms::Label^  label11;
		private: System::Windows::Forms::Label^  label12;
		private: System::Windows::Forms::Button^  button_sb;
		private: System::Windows::Forms::Button^  button_fh;
		private: System::Windows::Forms::Button^  button_m01;
		private: System::Windows::Forms::GroupBox^  groupBox4;
		private: System::Windows::Forms::Button^  button_zm;
		private: System::Windows::Forms::Button^  button_xm;
		private: System::Windows::Forms::Button^  button_ym;
		private: System::Windows::Forms::GroupBox^  groupBox5;
		private: System::Windows::Forms::Button^  button_x1;
		private: System::Windows::Forms::Button^  button_x100;
		private: System::Windows::Forms::Button^  button_x10;
		private: System::Windows::Forms::GroupBox^  groupBox6;
		private: System::Windows::Forms::Button^  button_teachST;
		private: System::Windows::Forms::Button^  button_teachED;
		private: System::Windows::Forms::Button^  button_rec;
		private: System::Windows::Forms::GroupBox^  groupBox7;
		private: System::Windows::Forms::GroupBox^  groupBox8;
		private: System::Windows::Forms::Button^  button_reset;
		private: System::Windows::Forms::Button^  button_start;
		private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
		private: System::Windows::Forms::GroupBox^  groupBox9;
		private: System::Windows::Forms::Button^  button_progD;
		private: System::Windows::Forms::Button^  button_progU;
		private: System::Windows::Forms::Button^  button_para;
		private: System::Windows::Forms::Button^  button_simu;
		private: System::Windows::Forms::Button^  button_diag;
		private: System::Windows::Forms::Button^  button_mem;
		private: System::Windows::Forms::Button^  button_mdi;
		private: System::Windows::Forms::Button^  button_jog;
		private: System::Windows::Forms::Button^  button_wheel;
		private: System::Windows::Forms::Button^  button_home;
		private: System::Windows::Forms::Button^  button_modeR;
		private: System::Windows::Forms::Button^  button_modeL;
		private: System::Windows::Forms::Button^  button_teach;
		private: System::Windows::Forms::Label^  label_runtime;
		private: System::Windows::Forms::Label^  label_run;
		private: System::Windows::Forms::Label^  label_global;
		private: System::Windows::Forms::Label^  label_globaltime;
		private: System::Windows::Forms::Button^  button_close;
		private: System::Windows::Forms::Button^  button_emerg_stop;
		private: System::Windows::Forms::Label^  label_feedOverride;
		private: System::Windows::Forms::Button^  button_100per;
		private: System::Windows::Forms::Label^  label_error_code;
		private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button_openFile = (gcnew System::Windows::Forms::Button());
			this->openFileDialog_openNC = (gcnew System::Windows::Forms::OpenFileDialog());
			this->richTextBox_ncFile = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox_filePath = (gcnew System::Windows::Forms::TextBox());
			this->trackBar_feedOverride = (gcnew System::Windows::Forms::TrackBar());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label_showX = (gcnew System::Windows::Forms::Label());
			this->label_showZ = (gcnew System::Windows::Forms::Label());
			this->label_showY = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->RT_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->NRT_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->button_zp = (gcnew System::Windows::Forms::Button());
			this->button_yp = (gcnew System::Windows::Forms::Button());
			this->button_xp = (gcnew System::Windows::Forms::Button());
			this->button_uvw = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button_zm = (gcnew System::Windows::Forms::Button());
			this->button_xm = (gcnew System::Windows::Forms::Button());
			this->button_ym = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->Label_M30 = (gcnew System::Windows::Forms::Label());
			this->Label_M00 = (gcnew System::Windows::Forms::Label());
			this->Label_PGM = (gcnew System::Windows::Forms::Label());
			this->Label_ERR = (gcnew System::Windows::Forms::Label());
			this->Label_HX = (gcnew System::Windows::Forms::Label());
			this->Label_INX = (gcnew System::Windows::Forms::Label());
			this->Label_HY = (gcnew System::Windows::Forms::Label());
			this->Label_INY = (gcnew System::Windows::Forms::Label());
			this->Label_HZ = (gcnew System::Windows::Forms::Label());
			this->Label_INZ = (gcnew System::Windows::Forms::Label());
			this->Label_PX = (gcnew System::Windows::Forms::Label());
			this->Label_NX = (gcnew System::Windows::Forms::Label());
			this->Label_PY = (gcnew System::Windows::Forms::Label());
			this->Label_NY = (gcnew System::Windows::Forms::Label());
			this->Label_PZ = (gcnew System::Windows::Forms::Label());
			this->Label_NZ = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label_showU = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label_showW = (gcnew System::Windows::Forms::Label());
			this->label_showV = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->button_sb = (gcnew System::Windows::Forms::Button());
			this->button_fh = (gcnew System::Windows::Forms::Button());
			this->button_m01 = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->button_x1 = (gcnew System::Windows::Forms::Button());
			this->button_x100 = (gcnew System::Windows::Forms::Button());
			this->button_x10 = (gcnew System::Windows::Forms::Button());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->button_teachST = (gcnew System::Windows::Forms::Button());
			this->button_teachED = (gcnew System::Windows::Forms::Button());
			this->button_rec = (gcnew System::Windows::Forms::Button());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->button_100per = (gcnew System::Windows::Forms::Button());
			this->label_feedOverride = (gcnew System::Windows::Forms::Label());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			this->button_start = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label_runtime = (gcnew System::Windows::Forms::Label());
			this->label_run = (gcnew System::Windows::Forms::Label());
			this->label_global = (gcnew System::Windows::Forms::Label());
			this->label_globaltime = (gcnew System::Windows::Forms::Label());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->button_progD = (gcnew System::Windows::Forms::Button());
			this->button_progU = (gcnew System::Windows::Forms::Button());
			this->button_para = (gcnew System::Windows::Forms::Button());
			this->button_simu = (gcnew System::Windows::Forms::Button());
			this->button_diag = (gcnew System::Windows::Forms::Button());
			this->button_mem = (gcnew System::Windows::Forms::Button());
			this->button_mdi = (gcnew System::Windows::Forms::Button());
			this->button_jog = (gcnew System::Windows::Forms::Button());
			this->button_wheel = (gcnew System::Windows::Forms::Button());
			this->button_home = (gcnew System::Windows::Forms::Button());
			this->button_modeR = (gcnew System::Windows::Forms::Button());
			this->button_modeL = (gcnew System::Windows::Forms::Button());
			this->button_teach = (gcnew System::Windows::Forms::Button());
			this->button_close = (gcnew System::Windows::Forms::Button());
			this->button_emerg_stop = (gcnew System::Windows::Forms::Button());
			this->label_error_code = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_feedOverride))->BeginInit();
			this->tableLayoutPanel1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Verdana", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 41);
			this->label1->TabIndex = 0;
			this->label1->Text = L"X";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button_openFile
			// 
			this->button_openFile->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_openFile->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_openFile->Location = System::Drawing::Point(217, 228);
			this->button_openFile->Name = L"button_openFile";
			this->button_openFile->Size = System::Drawing::Size(75, 23);
			this->button_openFile->TabIndex = 1;
			this->button_openFile->Text = L"OPEN";
			this->button_openFile->UseVisualStyleBackColor = true;
			this->button_openFile->Click += gcnew System::EventHandler(this, &Form1::button_openFile_Click);
			// 
			// openFileDialog_openNC
			// 
			this->openFileDialog_openNC->FileName = L"openFileDialog_openNC";
			// 
			// richTextBox_ncFile
			// 
			this->richTextBox_ncFile->BackColor = System::Drawing::SystemColors::Menu;
			this->richTextBox_ncFile->Location = System::Drawing::Point(217, 101);
			this->richTextBox_ncFile->Name = L"richTextBox_ncFile";
			this->richTextBox_ncFile->Size = System::Drawing::Size(408, 121);
			this->richTextBox_ncFile->TabIndex = 2;
			this->richTextBox_ncFile->Text = L"";
			// 
			// textBox_filePath
			// 
			this->textBox_filePath->BackColor = System::Drawing::SystemColors::MenuBar;
			this->textBox_filePath->Enabled = false;
			this->textBox_filePath->Location = System::Drawing::Point(298, 228);
			this->textBox_filePath->Name = L"textBox_filePath";
			this->textBox_filePath->Size = System::Drawing::Size(327, 22);
			this->textBox_filePath->TabIndex = 3;
			// 
			// trackBar_feedOverride
			// 
			this->trackBar_feedOverride->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->trackBar_feedOverride->BackColor = System::Drawing::SystemColors::Info;
			this->trackBar_feedOverride->Location = System::Drawing::Point(6, 14);
			this->trackBar_feedOverride->Maximum = 200;
			this->trackBar_feedOverride->Name = L"trackBar_feedOverride";
			this->trackBar_feedOverride->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->trackBar_feedOverride->Size = System::Drawing::Size(136, 45);
			this->trackBar_feedOverride->TabIndex = 4;
			this->trackBar_feedOverride->Value = 100;
			this->trackBar_feedOverride->Scroll += gcnew System::EventHandler(this, &Form1::trackBar_feedOverride_Scroll);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel1->Controls->Add(this->label_showX, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->label_showZ, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->label_showY, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->label3, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->label2, 0, 2);
			this->tableLayoutPanel1->Font = (gcnew System::Drawing::Font(L"Verdana", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->tableLayoutPanel1->Location = System::Drawing::Point(6, 14);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 5;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 3)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 3)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(183, 129);
			this->tableLayoutPanel1->TabIndex = 5;
			// 
			// label_showX
			// 
			this->label_showX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_showX->AutoSize = true;
			this->label_showX->BackColor = System::Drawing::Color::Transparent;
			this->label_showX->Font = (gcnew System::Drawing::Font(L"Verdana", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_showX->Location = System::Drawing::Point(53, 0);
			this->label_showX->Name = L"label_showX";
			this->label_showX->Size = System::Drawing::Size(127, 41);
			this->label_showX->TabIndex = 3;
			this->label_showX->Text = L"0000.000";
			this->label_showX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_showZ
			// 
			this->label_showZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_showZ->AutoSize = true;
			this->label_showZ->BackColor = System::Drawing::Color::Transparent;
			this->label_showZ->Font = (gcnew System::Drawing::Font(L"Verdana", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_showZ->Location = System::Drawing::Point(53, 88);
			this->label_showZ->Name = L"label_showZ";
			this->label_showZ->Size = System::Drawing::Size(127, 41);
			this->label_showZ->TabIndex = 5;
			this->label_showZ->Text = L"0000.000";
			this->label_showZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_showY
			// 
			this->label_showY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_showY->AutoSize = true;
			this->label_showY->BackColor = System::Drawing::Color::Transparent;
			this->label_showY->Font = (gcnew System::Drawing::Font(L"Verdana", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_showY->Location = System::Drawing::Point(53, 44);
			this->label_showY->Name = L"label_showY";
			this->label_showY->Size = System::Drawing::Size(127, 41);
			this->label_showY->TabIndex = 4;
			this->label_showY->Text = L"0000.000";
			this->label_showY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Verdana", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(3, 88);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 41);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Z";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Verdana", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(3, 44);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(44, 41);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Y";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// RT_timer
			// 
			this->RT_timer->Interval = 94;
			this->RT_timer->Tick += gcnew System::EventHandler(this, &Form1::RT_timer_Tick);
			// 
			// NRT_timer
			// 
			this->NRT_timer->Tick += gcnew System::EventHandler(this, &Form1::NRT_timer_Tick);
			// 
			// button_zp
			// 
			this->button_zp->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_zp->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->button_zp->Location = System::Drawing::Point(6, 100);
			this->button_zp->Name = L"button_zp";
			this->button_zp->Size = System::Drawing::Size(40, 30);
			this->button_zp->TabIndex = 5;
			this->button_zp->Text = L"Z+";
			this->button_zp->UseVisualStyleBackColor = true;
			this->button_zp->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zp_MouseDown);
			this->button_zp->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zp_MouseUp);
			// 
			// button_yp
			// 
			this->button_yp->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_yp->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->button_yp->Location = System::Drawing::Point(6, 68);
			this->button_yp->Name = L"button_yp";
			this->button_yp->Size = System::Drawing::Size(40, 30);
			this->button_yp->TabIndex = 3;
			this->button_yp->Text = L"Y+";
			this->button_yp->UseVisualStyleBackColor = true;
			this->button_yp->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yp_MouseDown);
			this->button_yp->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_yp_MouseUp);
			// 
			// button_xp
			// 
			this->button_xp->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_xp->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->button_xp->Location = System::Drawing::Point(6, 36);
			this->button_xp->Name = L"button_xp";
			this->button_xp->Size = System::Drawing::Size(40, 30);
			this->button_xp->TabIndex = 1;
			this->button_xp->Text = L"X+";
			this->button_xp->UseVisualStyleBackColor = true;
			this->button_xp->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xp_MouseDown);
			this->button_xp->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xp_MouseUp);
			// 
			// button_uvw
			// 
			this->button_uvw->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_uvw->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->button_uvw->Location = System::Drawing::Point(6, 10);
			this->button_uvw->Name = L"button_uvw";
			this->button_uvw->Size = System::Drawing::Size(79, 27);
			this->button_uvw->TabIndex = 0;
			this->button_uvw->Text = L"UVW";
			this->button_uvw->UseVisualStyleBackColor = true;
			this->button_uvw->Click += gcnew System::EventHandler(this, &Form1::button_uvw_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::Transparent;
			this->groupBox1->Controls->Add(this->button_zm);
			this->groupBox1->Controls->Add(this->button_xm);
			this->groupBox1->Controls->Add(this->button_ym);
			this->groupBox1->Controls->Add(this->button_uvw);
			this->groupBox1->Controls->Add(this->button_zp);
			this->groupBox1->Controls->Add(this->button_xp);
			this->groupBox1->Controls->Add(this->button_yp);
			this->groupBox1->Location = System::Drawing::Point(172, 257);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(91, 135);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			// 
			// button_zm
			// 
			this->button_zm->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_zm->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->button_zm->Location = System::Drawing::Point(45, 100);
			this->button_zm->Name = L"button_zm";
			this->button_zm->Size = System::Drawing::Size(40, 30);
			this->button_zm->TabIndex = 8;
			this->button_zm->Text = L"Z-";
			this->button_zm->UseVisualStyleBackColor = true;
			this->button_zm->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zm_MouseDown);
			this->button_zm->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_zm_MouseUp);
			// 
			// button_xm
			// 
			this->button_xm->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_xm->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->button_xm->Location = System::Drawing::Point(45, 36);
			this->button_xm->Name = L"button_xm";
			this->button_xm->Size = System::Drawing::Size(40, 30);
			this->button_xm->TabIndex = 6;
			this->button_xm->Text = L"X-";
			this->button_xm->UseVisualStyleBackColor = true;
			this->button_xm->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xm_MouseDown);
			this->button_xm->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_xm_MouseUp);
			// 
			// button_ym
			// 
			this->button_ym->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_ym->Font = (gcnew System::Drawing::Font(L"Consolas", 11));
			this->button_ym->Location = System::Drawing::Point(45, 68);
			this->button_ym->Name = L"button_ym";
			this->button_ym->Size = System::Drawing::Size(40, 30);
			this->button_ym->TabIndex = 7;
			this->button_ym->Text = L"Y-";
			this->button_ym->UseVisualStyleBackColor = true;
			this->button_ym->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_ym_MouseDown);
			this->button_ym->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button_ym_MouseUp);
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel2->ColumnCount = 8;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				12.5F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				12.5F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				12.5F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				12.5F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				12.5F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				12.5F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				12.5F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				12.5F)));
			this->tableLayoutPanel2->Controls->Add(this->Label_M30, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->Label_M00, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->Label_PGM, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->Label_ERR, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->Label_HX, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->Label_INX, 2, 1);
			this->tableLayoutPanel2->Controls->Add(this->Label_HY, 3, 0);
			this->tableLayoutPanel2->Controls->Add(this->Label_INY, 3, 1);
			this->tableLayoutPanel2->Controls->Add(this->Label_HZ, 4, 0);
			this->tableLayoutPanel2->Controls->Add(this->Label_INZ, 4, 1);
			this->tableLayoutPanel2->Controls->Add(this->Label_PX, 5, 0);
			this->tableLayoutPanel2->Controls->Add(this->Label_NX, 5, 1);
			this->tableLayoutPanel2->Controls->Add(this->Label_PY, 6, 0);
			this->tableLayoutPanel2->Controls->Add(this->Label_NY, 6, 1);
			this->tableLayoutPanel2->Controls->Add(this->Label_PZ, 7, 0);
			this->tableLayoutPanel2->Controls->Add(this->Label_NZ, 7, 1);
			this->tableLayoutPanel2->Location = System::Drawing::Point(16, 35);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(462, 60);
			this->tableLayoutPanel2->TabIndex = 9;
			// 
			// Label_M30
			// 
			this->Label_M30->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_M30->AutoSize = true;
			this->Label_M30->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_M30->Location = System::Drawing::Point(3, 30);
			this->Label_M30->Name = L"Label_M30";
			this->Label_M30->Size = System::Drawing::Size(51, 30);
			this->Label_M30->TabIndex = 0;
			this->Label_M30->Text = L"M30";
			this->Label_M30->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_M00
			// 
			this->Label_M00->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_M00->AutoSize = true;
			this->Label_M00->Font = (gcnew System::Drawing::Font(L"Consolas", 12));
			this->Label_M00->Location = System::Drawing::Point(3, 0);
			this->Label_M00->Name = L"Label_M00";
			this->Label_M00->Size = System::Drawing::Size(51, 30);
			this->Label_M00->TabIndex = 1;
			this->Label_M00->Text = L"M00";
			this->Label_M00->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_PGM
			// 
			this->Label_PGM->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_PGM->AutoSize = true;
			this->Label_PGM->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_PGM->Location = System::Drawing::Point(60, 0);
			this->Label_PGM->Name = L"Label_PGM";
			this->Label_PGM->Size = System::Drawing::Size(51, 30);
			this->Label_PGM->TabIndex = 2;
			this->Label_PGM->Text = L"PGM";
			this->Label_PGM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_ERR
			// 
			this->Label_ERR->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_ERR->AutoSize = true;
			this->Label_ERR->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_ERR->Location = System::Drawing::Point(60, 30);
			this->Label_ERR->Name = L"Label_ERR";
			this->Label_ERR->Size = System::Drawing::Size(51, 30);
			this->Label_ERR->TabIndex = 3;
			this->Label_ERR->Text = L"ERR";
			this->Label_ERR->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_HX
			// 
			this->Label_HX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_HX->AutoSize = true;
			this->Label_HX->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_HX->Location = System::Drawing::Point(117, 0);
			this->Label_HX->Name = L"Label_HX";
			this->Label_HX->Size = System::Drawing::Size(51, 30);
			this->Label_HX->TabIndex = 4;
			this->Label_HX->Text = L"HX";
			this->Label_HX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_INX
			// 
			this->Label_INX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_INX->AutoSize = true;
			this->Label_INX->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_INX->Location = System::Drawing::Point(117, 30);
			this->Label_INX->Name = L"Label_INX";
			this->Label_INX->Size = System::Drawing::Size(51, 30);
			this->Label_INX->TabIndex = 5;
			this->Label_INX->Text = L"INX";
			this->Label_INX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_HY
			// 
			this->Label_HY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_HY->AutoSize = true;
			this->Label_HY->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_HY->Location = System::Drawing::Point(174, 0);
			this->Label_HY->Name = L"Label_HY";
			this->Label_HY->Size = System::Drawing::Size(51, 30);
			this->Label_HY->TabIndex = 6;
			this->Label_HY->Text = L"HY";
			this->Label_HY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_INY
			// 
			this->Label_INY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_INY->AutoSize = true;
			this->Label_INY->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_INY->Location = System::Drawing::Point(174, 30);
			this->Label_INY->Name = L"Label_INY";
			this->Label_INY->Size = System::Drawing::Size(51, 30);
			this->Label_INY->TabIndex = 7;
			this->Label_INY->Text = L"INY";
			this->Label_INY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_HZ
			// 
			this->Label_HZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_HZ->AutoSize = true;
			this->Label_HZ->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_HZ->Location = System::Drawing::Point(231, 0);
			this->Label_HZ->Name = L"Label_HZ";
			this->Label_HZ->Size = System::Drawing::Size(51, 30);
			this->Label_HZ->TabIndex = 8;
			this->Label_HZ->Text = L"HZ";
			this->Label_HZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_INZ
			// 
			this->Label_INZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_INZ->AutoSize = true;
			this->Label_INZ->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_INZ->Location = System::Drawing::Point(231, 30);
			this->Label_INZ->Name = L"Label_INZ";
			this->Label_INZ->Size = System::Drawing::Size(51, 30);
			this->Label_INZ->TabIndex = 9;
			this->Label_INZ->Text = L"INZ";
			this->Label_INZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_PX
			// 
			this->Label_PX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_PX->AutoSize = true;
			this->Label_PX->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_PX->Location = System::Drawing::Point(288, 0);
			this->Label_PX->Name = L"Label_PX";
			this->Label_PX->Size = System::Drawing::Size(51, 30);
			this->Label_PX->TabIndex = 10;
			this->Label_PX->Text = L"PX";
			this->Label_PX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_NX
			// 
			this->Label_NX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_NX->AutoSize = true;
			this->Label_NX->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_NX->Location = System::Drawing::Point(288, 30);
			this->Label_NX->Name = L"Label_NX";
			this->Label_NX->Size = System::Drawing::Size(51, 30);
			this->Label_NX->TabIndex = 11;
			this->Label_NX->Text = L"NX";
			this->Label_NX->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_PY
			// 
			this->Label_PY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_PY->AutoSize = true;
			this->Label_PY->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_PY->Location = System::Drawing::Point(345, 0);
			this->Label_PY->Name = L"Label_PY";
			this->Label_PY->Size = System::Drawing::Size(51, 30);
			this->Label_PY->TabIndex = 12;
			this->Label_PY->Text = L"PY";
			this->Label_PY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_NY
			// 
			this->Label_NY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_NY->AutoSize = true;
			this->Label_NY->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_NY->Location = System::Drawing::Point(345, 30);
			this->Label_NY->Name = L"Label_NY";
			this->Label_NY->Size = System::Drawing::Size(51, 30);
			this->Label_NY->TabIndex = 13;
			this->Label_NY->Text = L"NY";
			this->Label_NY->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_PZ
			// 
			this->Label_PZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_PZ->AutoSize = true;
			this->Label_PZ->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_PZ->Location = System::Drawing::Point(402, 0);
			this->Label_PZ->Name = L"Label_PZ";
			this->Label_PZ->Size = System::Drawing::Size(57, 30);
			this->Label_PZ->TabIndex = 14;
			this->Label_PZ->Text = L"PZ";
			this->Label_PZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_NZ
			// 
			this->Label_NZ->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->Label_NZ->AutoSize = true;
			this->Label_NZ->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_NZ->Location = System::Drawing::Point(402, 30);
			this->Label_NZ->Name = L"Label_NZ";
			this->Label_NZ->Size = System::Drawing::Size(57, 30);
			this->Label_NZ->TabIndex = 15;
			this->Label_NZ->Text = L"NZ";
			this->Label_NZ->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::Transparent;
			this->groupBox2->Controls->Add(this->tableLayoutPanel1);
			this->groupBox2->Location = System::Drawing::Point(16, 101);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(195, 150);
			this->groupBox2->TabIndex = 10;
			this->groupBox2->TabStop = false;
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::Transparent;
			this->groupBox3->Controls->Add(this->tableLayoutPanel3);
			this->groupBox3->Location = System::Drawing::Point(16, 257);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(150, 135);
			this->groupBox3->TabIndex = 11;
			this->groupBox3->TabStop = false;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 2;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				30)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel3->Controls->Add(this->label_showU, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->label8, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->label_showW, 1, 4);
			this->tableLayoutPanel3->Controls->Add(this->label_showV, 1, 2);
			this->tableLayoutPanel3->Controls->Add(this->label11, 0, 4);
			this->tableLayoutPanel3->Controls->Add(this->label12, 0, 2);
			this->tableLayoutPanel3->Font = (gcnew System::Drawing::Font(L"Verdana", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->tableLayoutPanel3->Location = System::Drawing::Point(6, 12);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 5;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 3)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33334F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 3)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33334F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(138, 116);
			this->tableLayoutPanel3->TabIndex = 5;
			// 
			// label_showU
			// 
			this->label_showU->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_showU->AutoSize = true;
			this->label_showU->BackColor = System::Drawing::Color::Transparent;
			this->label_showU->Font = (gcnew System::Drawing::Font(L"Consolas", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_showU->Location = System::Drawing::Point(33, 0);
			this->label_showU->Name = L"label_showU";
			this->label_showU->Size = System::Drawing::Size(102, 36);
			this->label_showU->TabIndex = 3;
			this->label_showU->Text = L"0000.000";
			this->label_showU->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(3, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(24, 36);
			this->label8->TabIndex = 0;
			this->label8->Text = L"U";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_showW
			// 
			this->label_showW->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_showW->AutoSize = true;
			this->label_showW->BackColor = System::Drawing::Color::Transparent;
			this->label_showW->Font = (gcnew System::Drawing::Font(L"Consolas", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_showW->Location = System::Drawing::Point(33, 78);
			this->label_showW->Name = L"label_showW";
			this->label_showW->Size = System::Drawing::Size(102, 38);
			this->label_showW->TabIndex = 5;
			this->label_showW->Text = L"0000.000";
			this->label_showW->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_showV
			// 
			this->label_showV->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_showV->AutoSize = true;
			this->label_showV->BackColor = System::Drawing::Color::Transparent;
			this->label_showV->Font = (gcnew System::Drawing::Font(L"Consolas", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_showV->Location = System::Drawing::Point(33, 39);
			this->label_showV->Name = L"label_showV";
			this->label_showV->Size = System::Drawing::Size(102, 36);
			this->label_showV->TabIndex = 4;
			this->label_showV->Text = L"0000.000";
			this->label_showV->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label11
			// 
			this->label11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(3, 78);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(24, 38);
			this->label11->TabIndex = 2;
			this->label11->Text = L"W";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label12
			// 
			this->label12->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::Transparent;
			this->label12->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(3, 39);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(24, 36);
			this->label12->TabIndex = 1;
			this->label12->Text = L"V";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button_sb
			// 
			this->button_sb->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_sb->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_sb->Location = System::Drawing::Point(5, 90);
			this->button_sb->Name = L"button_sb";
			this->button_sb->Size = System::Drawing::Size(40, 40);
			this->button_sb->TabIndex = 20;
			this->button_sb->Text = L"SB";
			this->button_sb->UseVisualStyleBackColor = true;
			this->button_sb->Click += gcnew System::EventHandler(this, &Form1::button_sb_Click);
			// 
			// button_fh
			// 
			this->button_fh->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_fh->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_fh->Location = System::Drawing::Point(5, 50);
			this->button_fh->Name = L"button_fh";
			this->button_fh->Size = System::Drawing::Size(40, 40);
			this->button_fh->TabIndex = 19;
			this->button_fh->Text = L"FH";
			this->button_fh->UseVisualStyleBackColor = true;
			this->button_fh->Click += gcnew System::EventHandler(this, &Form1::button_fh_Click);
			// 
			// button_m01
			// 
			this->button_m01->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_m01->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_m01->Location = System::Drawing::Point(5, 10);
			this->button_m01->Name = L"button_m01";
			this->button_m01->Size = System::Drawing::Size(40, 40);
			this->button_m01->TabIndex = 18;
			this->button_m01->Text = L"M01";
			this->button_m01->UseVisualStyleBackColor = true;
			this->button_m01->Click += gcnew System::EventHandler(this, &Form1::button_m01_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::Transparent;
			this->groupBox4->Controls->Add(this->button_m01);
			this->groupBox4->Controls->Add(this->button_sb);
			this->groupBox4->Controls->Add(this->button_fh);
			this->groupBox4->Location = System::Drawing::Point(421, 257);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(50, 135);
			this->groupBox4->TabIndex = 8;
			this->groupBox4->TabStop = false;
			// 
			// groupBox5
			// 
			this->groupBox5->BackColor = System::Drawing::Color::Transparent;
			this->groupBox5->Controls->Add(this->button_x1);
			this->groupBox5->Controls->Add(this->button_x100);
			this->groupBox5->Controls->Add(this->button_x10);
			this->groupBox5->Location = System::Drawing::Point(269, 257);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(50, 135);
			this->groupBox5->TabIndex = 21;
			this->groupBox5->TabStop = false;
			// 
			// button_x1
			// 
			this->button_x1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_x1->Font = (gcnew System::Drawing::Font(L"Consolas", 8));
			this->button_x1->Location = System::Drawing::Point(5, 10);
			this->button_x1->Name = L"button_x1";
			this->button_x1->Size = System::Drawing::Size(40, 40);
			this->button_x1->TabIndex = 18;
			this->button_x1->Text = L"X1";
			this->button_x1->UseVisualStyleBackColor = true;
			this->button_x1->Click += gcnew System::EventHandler(this, &Form1::button_x1_Click);
			// 
			// button_x100
			// 
			this->button_x100->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_x100->Font = (gcnew System::Drawing::Font(L"Consolas", 8));
			this->button_x100->Location = System::Drawing::Point(5, 90);
			this->button_x100->Name = L"button_x100";
			this->button_x100->Size = System::Drawing::Size(40, 40);
			this->button_x100->TabIndex = 20;
			this->button_x100->Text = L"X100";
			this->button_x100->UseVisualStyleBackColor = true;
			this->button_x100->Click += gcnew System::EventHandler(this, &Form1::button_x100_Click);
			// 
			// button_x10
			// 
			this->button_x10->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_x10->Font = (gcnew System::Drawing::Font(L"Consolas", 8));
			this->button_x10->Location = System::Drawing::Point(5, 50);
			this->button_x10->Name = L"button_x10";
			this->button_x10->Size = System::Drawing::Size(40, 40);
			this->button_x10->TabIndex = 19;
			this->button_x10->Text = L"X10";
			this->button_x10->UseVisualStyleBackColor = true;
			this->button_x10->Click += gcnew System::EventHandler(this, &Form1::button_x10_Click);
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::Transparent;
			this->groupBox6->Controls->Add(this->button_teachST);
			this->groupBox6->Controls->Add(this->button_teachED);
			this->groupBox6->Controls->Add(this->button_rec);
			this->groupBox6->Location = System::Drawing::Point(325, 257);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(90, 135);
			this->groupBox6->TabIndex = 21;
			this->groupBox6->TabStop = false;
			// 
			// button_teachST
			// 
			this->button_teachST->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_teachST->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_teachST->Location = System::Drawing::Point(5, 10);
			this->button_teachST->Name = L"button_teachST";
			this->button_teachST->Size = System::Drawing::Size(80, 40);
			this->button_teachST->TabIndex = 18;
			this->button_teachST->Text = L"TEACH\r\nSTART";
			this->button_teachST->UseVisualStyleBackColor = true;
			// 
			// button_teachED
			// 
			this->button_teachED->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_teachED->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_teachED->Location = System::Drawing::Point(5, 90);
			this->button_teachED->Name = L"button_teachED";
			this->button_teachED->Size = System::Drawing::Size(80, 40);
			this->button_teachED->TabIndex = 20;
			this->button_teachED->Text = L"TEACH\r\nEND";
			this->button_teachED->UseVisualStyleBackColor = true;
			// 
			// button_rec
			// 
			this->button_rec->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_rec->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_rec->Location = System::Drawing::Point(5, 50);
			this->button_rec->Name = L"button_rec";
			this->button_rec->Size = System::Drawing::Size(80, 40);
			this->button_rec->TabIndex = 19;
			this->button_rec->Text = L"RECORD";
			this->button_rec->UseVisualStyleBackColor = true;
			// 
			// groupBox7
			// 
			this->groupBox7->BackColor = System::Drawing::Color::Transparent;
			this->groupBox7->Controls->Add(this->button_100per);
			this->groupBox7->Controls->Add(this->label_feedOverride);
			this->groupBox7->Controls->Add(this->trackBar_feedOverride);
			this->groupBox7->Location = System::Drawing::Point(477, 257);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(148, 66);
			this->groupBox7->TabIndex = 22;
			this->groupBox7->TabStop = false;
			// 
			// button_100per
			// 
			this->button_100per->Font = (gcnew System::Drawing::Font(L"Consolas", 6));
			this->button_100per->Location = System::Drawing::Point(111, 43);
			this->button_100per->Name = L"button_100per";
			this->button_100per->Size = System::Drawing::Size(30, 15);
			this->button_100per->TabIndex = 6;
			this->button_100per->Text = L"100";
			this->button_100per->UseVisualStyleBackColor = true;
			this->button_100per->Click += gcnew System::EventHandler(this, &Form1::button_100per_Click);
			// 
			// label_feedOverride
			// 
			this->label_feedOverride->AutoSize = true;
			this->label_feedOverride->BackColor = System::Drawing::SystemColors::Info;
			this->label_feedOverride->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_feedOverride->Location = System::Drawing::Point(58, 45);
			this->label_feedOverride->Name = L"label_feedOverride";
			this->label_feedOverride->Size = System::Drawing::Size(35, 14);
			this->label_feedOverride->TabIndex = 5;
			this->label_feedOverride->Text = L"100%";
			// 
			// groupBox8
			// 
			this->groupBox8->BackColor = System::Drawing::Color::Transparent;
			this->groupBox8->Controls->Add(this->button_reset);
			this->groupBox8->Controls->Add(this->button_start);
			this->groupBox8->Location = System::Drawing::Point(477, 323);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(148, 69);
			this->groupBox8->TabIndex = 23;
			this->groupBox8->TabStop = false;
			// 
			// button_reset
			// 
			this->button_reset->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button_reset->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_reset->Font = (gcnew System::Drawing::Font(L"Consolas", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_reset->Location = System::Drawing::Point(82, 12);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(60, 50);
			this->button_reset->TabIndex = 1;
			this->button_reset->Text = L"RESET";
			this->button_reset->UseVisualStyleBackColor = false;
			this->button_reset->Click += gcnew System::EventHandler(this, &Form1::button_reset_Click);
			// 
			// button_start
			// 
			this->button_start->BackColor = System::Drawing::Color::Lime;
			this->button_start->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_start->Font = (gcnew System::Drawing::Font(L"Consolas", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_start->Location = System::Drawing::Point(6, 12);
			this->button_start->Name = L"button_start";
			this->button_start->Size = System::Drawing::Size(70, 50);
			this->button_start->TabIndex = 0;
			this->button_start->Text = L"START";
			this->button_start->UseVisualStyleBackColor = false;
			this->button_start->Click += gcnew System::EventHandler(this, &Form1::button_start_Click);
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->BackColor = System::Drawing::Color::Transparent;
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel4->Controls->Add(this->label_runtime, 0, 1);
			this->tableLayoutPanel4->Controls->Add(this->label_run, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->label_global, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->label_globaltime, 0, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(484, 35);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 2;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(162, 60);
			this->tableLayoutPanel4->TabIndex = 24;
			// 
			// label_runtime
			// 
			this->label_runtime->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_runtime->AutoSize = true;
			this->label_runtime->BackColor = System::Drawing::Color::Transparent;
			this->label_runtime->Font = (gcnew System::Drawing::Font(L"Consolas", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_runtime->Location = System::Drawing::Point(73, 30);
			this->label_runtime->Name = L"label_runtime";
			this->label_runtime->Size = System::Drawing::Size(86, 30);
			this->label_runtime->TabIndex = 7;
			this->label_runtime->Text = L"12:59:59";
			this->label_runtime->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_run
			// 
			this->label_run->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_run->AutoSize = true;
			this->label_run->BackColor = System::Drawing::Color::Transparent;
			this->label_run->Font = (gcnew System::Drawing::Font(L"Consolas", 10));
			this->label_run->Location = System::Drawing::Point(3, 30);
			this->label_run->Name = L"label_run";
			this->label_run->Size = System::Drawing::Size(64, 30);
			this->label_run->TabIndex = 6;
			this->label_run->Text = L"RunTime";
			this->label_run->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_global
			// 
			this->label_global->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_global->AutoSize = true;
			this->label_global->BackColor = System::Drawing::Color::Transparent;
			this->label_global->Font = (gcnew System::Drawing::Font(L"Consolas", 10));
			this->label_global->Location = System::Drawing::Point(3, 0);
			this->label_global->Name = L"label_global";
			this->label_global->Size = System::Drawing::Size(64, 30);
			this->label_global->TabIndex = 5;
			this->label_global->Text = L"Global";
			this->label_global->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_globaltime
			// 
			this->label_globaltime->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label_globaltime->AutoSize = true;
			this->label_globaltime->BackColor = System::Drawing::Color::Transparent;
			this->label_globaltime->Font = (gcnew System::Drawing::Font(L"Consolas", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_globaltime->Location = System::Drawing::Point(73, 0);
			this->label_globaltime->Name = L"label_globaltime";
			this->label_globaltime->Size = System::Drawing::Size(86, 30);
			this->label_globaltime->TabIndex = 4;
			this->label_globaltime->Text = L"12:59:59";
			this->label_globaltime->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// groupBox9
			// 
			this->groupBox9->BackColor = System::Drawing::Color::Transparent;
			this->groupBox9->Controls->Add(this->button_progD);
			this->groupBox9->Controls->Add(this->button_progU);
			this->groupBox9->Controls->Add(this->button_para);
			this->groupBox9->Controls->Add(this->button_simu);
			this->groupBox9->Controls->Add(this->button_diag);
			this->groupBox9->Location = System::Drawing::Point(631, 101);
			this->groupBox9->Margin = System::Windows::Forms::Padding(0);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(73, 291);
			this->groupBox9->TabIndex = 25;
			this->groupBox9->TabStop = false;
			// 
			// button_progD
			// 
			this->button_progD->Cursor = System::Windows::Forms::Cursors::PanSouth;
			this->button_progD->Font = (gcnew System::Drawing::Font(L"Microsoft JhengHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_progD->Location = System::Drawing::Point(6, 253);
			this->button_progD->Name = L"button_progD";
			this->button_progD->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->button_progD->Size = System::Drawing::Size(60, 30);
			this->button_progD->TabIndex = 5;
			this->button_progD->Text = L"▼";
			this->button_progD->UseVisualStyleBackColor = true;
			this->button_progD->Click += gcnew System::EventHandler(this, &Form1::button_progD_Click);
			// 
			// button_progU
			// 
			this->button_progU->Cursor = System::Windows::Forms::Cursors::PanNorth;
			this->button_progU->Font = (gcnew System::Drawing::Font(L"Microsoft JhengHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_progU->Location = System::Drawing::Point(6, 13);
			this->button_progU->Name = L"button_progU";
			this->button_progU->Size = System::Drawing::Size(60, 30);
			this->button_progU->TabIndex = 4;
			this->button_progU->Text = L"▲";
			this->button_progU->UseVisualStyleBackColor = true;
			this->button_progU->Click += gcnew System::EventHandler(this, &Form1::button_progU_Click);
			// 
			// button_para
			// 
			this->button_para->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button_para->Font = (gcnew System::Drawing::Font(L"Microsoft JhengHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_para->Location = System::Drawing::Point(6, 43);
			this->button_para->Name = L"button_para";
			this->button_para->Size = System::Drawing::Size(60, 70);
			this->button_para->TabIndex = 3;
			this->button_para->Text = L"參數";
			this->button_para->UseVisualStyleBackColor = true;
			// 
			// button_simu
			// 
			this->button_simu->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button_simu->Font = (gcnew System::Drawing::Font(L"Microsoft JhengHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_simu->Location = System::Drawing::Point(6, 113);
			this->button_simu->Name = L"button_simu";
			this->button_simu->Size = System::Drawing::Size(60, 70);
			this->button_simu->TabIndex = 2;
			this->button_simu->Text = L"模擬";
			this->button_simu->UseVisualStyleBackColor = true;
			this->button_simu->Click += gcnew System::EventHandler(this, &Form1::button_simu_Click);
			// 
			// button_diag
			// 
			this->button_diag->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button_diag->Font = (gcnew System::Drawing::Font(L"Microsoft JhengHei", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->button_diag->Location = System::Drawing::Point(6, 183);
			this->button_diag->Name = L"button_diag";
			this->button_diag->Size = System::Drawing::Size(60, 70);
			this->button_diag->TabIndex = 1;
			this->button_diag->Text = L"診斷";
			this->button_diag->UseVisualStyleBackColor = true;
			// 
			// button_mem
			// 
			this->button_mem->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button_mem->Font = (gcnew System::Drawing::Font(L"Georgia", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_mem->Location = System::Drawing::Point(46, 398);
			this->button_mem->Name = L"button_mem";
			this->button_mem->Size = System::Drawing::Size(80, 70);
			this->button_mem->TabIndex = 26;
			this->button_mem->Text = L"MEM";
			this->button_mem->UseVisualStyleBackColor = true;
			this->button_mem->Click += gcnew System::EventHandler(this, &Form1::button_mem_Click);
			// 
			// button_mdi
			// 
			this->button_mdi->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button_mdi->Font = (gcnew System::Drawing::Font(L"Georgia", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_mdi->Location = System::Drawing::Point(126, 398);
			this->button_mdi->Name = L"button_mdi";
			this->button_mdi->Size = System::Drawing::Size(80, 70);
			this->button_mdi->TabIndex = 27;
			this->button_mdi->Text = L"MDI";
			this->button_mdi->UseVisualStyleBackColor = true;
			this->button_mdi->Click += gcnew System::EventHandler(this, &Form1::button_mdi_Click);
			// 
			// button_jog
			// 
			this->button_jog->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button_jog->Font = (gcnew System::Drawing::Font(L"Georgia", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_jog->Location = System::Drawing::Point(206, 398);
			this->button_jog->Name = L"button_jog";
			this->button_jog->Size = System::Drawing::Size(80, 70);
			this->button_jog->TabIndex = 28;
			this->button_jog->Text = L"JOG";
			this->button_jog->UseVisualStyleBackColor = true;
			this->button_jog->Click += gcnew System::EventHandler(this, &Form1::button_jog_Click);
			// 
			// button_wheel
			// 
			this->button_wheel->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button_wheel->Font = (gcnew System::Drawing::Font(L"Georgia", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_wheel->Location = System::Drawing::Point(286, 398);
			this->button_wheel->Name = L"button_wheel";
			this->button_wheel->Size = System::Drawing::Size(80, 70);
			this->button_wheel->TabIndex = 29;
			this->button_wheel->Text = L"WHEEL";
			this->button_wheel->UseVisualStyleBackColor = true;
			this->button_wheel->Click += gcnew System::EventHandler(this, &Form1::button_wheel_Click);
			// 
			// button_home
			// 
			this->button_home->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button_home->Font = (gcnew System::Drawing::Font(L"Georgia", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_home->Location = System::Drawing::Point(446, 398);
			this->button_home->Name = L"button_home";
			this->button_home->Size = System::Drawing::Size(80, 70);
			this->button_home->TabIndex = 30;
			this->button_home->Text = L"HOME";
			this->button_home->UseVisualStyleBackColor = true;
			this->button_home->Click += gcnew System::EventHandler(this, &Form1::button_home_Click);
			// 
			// button_modeR
			// 
			this->button_modeR->Cursor = System::Windows::Forms::Cursors::PanEast;
			this->button_modeR->Font = (gcnew System::Drawing::Font(L"Georgia", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_modeR->Location = System::Drawing::Point(526, 398);
			this->button_modeR->Name = L"button_modeR";
			this->button_modeR->Size = System::Drawing::Size(30, 70);
			this->button_modeR->TabIndex = 31;
			this->button_modeR->Text = L"▶︎";
			this->button_modeR->UseVisualStyleBackColor = true;
			this->button_modeR->Click += gcnew System::EventHandler(this, &Form1::button_modeR_Click);
			// 
			// button_modeL
			// 
			this->button_modeL->Cursor = System::Windows::Forms::Cursors::PanWest;
			this->button_modeL->Font = (gcnew System::Drawing::Font(L"Georgia", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_modeL->Location = System::Drawing::Point(16, 398);
			this->button_modeL->Name = L"button_modeL";
			this->button_modeL->Size = System::Drawing::Size(30, 70);
			this->button_modeL->TabIndex = 32;
			this->button_modeL->Text = L"◀︎";
			this->button_modeL->UseVisualStyleBackColor = true;
			this->button_modeL->Click += gcnew System::EventHandler(this, &Form1::button_modeL_Click);
			// 
			// button_teach
			// 
			this->button_teach->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button_teach->Font = (gcnew System::Drawing::Font(L"Georgia", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_teach->Location = System::Drawing::Point(366, 398);
			this->button_teach->Name = L"button_teach";
			this->button_teach->Size = System::Drawing::Size(80, 70);
			this->button_teach->TabIndex = 33;
			this->button_teach->Text = L"TEACH";
			this->button_teach->UseVisualStyleBackColor = true;
			this->button_teach->Click += gcnew System::EventHandler(this, &Form1::button_teach_Click);
			// 
			// button_close
			// 
			this->button_close->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button_close->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_close->Font = (gcnew System::Drawing::Font(L"Georgia", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_close->ForeColor = System::Drawing::Color::Black;
			this->button_close->Location = System::Drawing::Point(652, 33);
			this->button_close->Name = L"button_close";
			this->button_close->Size = System::Drawing::Size(51, 62);
			this->button_close->TabIndex = 34;
			this->button_close->Text = L"✖︎";
			this->button_close->UseVisualStyleBackColor = false;
			this->button_close->Click += gcnew System::EventHandler(this, &Form1::button_close_Click);
			// 
			// button_emerg_stop
			// 
			this->button_emerg_stop->BackColor = System::Drawing::Color::Transparent;
			this->button_emerg_stop->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button_emerg_stop.BackgroundImage")));
			this->button_emerg_stop->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->button_emerg_stop->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button_emerg_stop->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button_emerg_stop->Location = System::Drawing::Point(633, 398);
			this->button_emerg_stop->Name = L"button_emerg_stop";
			this->button_emerg_stop->Size = System::Drawing::Size(70, 70);
			this->button_emerg_stop->TabIndex = 35;
			this->button_emerg_stop->UseVisualStyleBackColor = false;
			this->button_emerg_stop->Click += gcnew System::EventHandler(this, &Form1::button_emerg_stop_Click);
			// 
			// label_error_code
			// 
			this->label_error_code->AutoSize = true;
			this->label_error_code->BackColor = System::Drawing::Color::Transparent;
			this->label_error_code->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label_error_code->ForeColor = System::Drawing::Color::White;
			this->label_error_code->Location = System::Drawing::Point(21, 471);
			this->label_error_code->Name = L"label_error_code";
			this->label_error_code->Size = System::Drawing::Size(0, 14);
			this->label_error_code->TabIndex = 37;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->CancelButton = this->button_emerg_stop;
			this->ClientSize = System::Drawing::Size(720, 500);
			this->Controls->Add(this->label_error_code);
			this->Controls->Add(this->button_emerg_stop);
			this->Controls->Add(this->button_close);
			this->Controls->Add(this->button_teach);
			this->Controls->Add(this->button_modeL);
			this->Controls->Add(this->button_modeR);
			this->Controls->Add(this->button_home);
			this->Controls->Add(this->button_wheel);
			this->Controls->Add(this->button_jog);
			this->Controls->Add(this->button_mdi);
			this->Controls->Add(this->button_mem);
			this->Controls->Add(this->groupBox9);
			this->Controls->Add(this->tableLayoutPanel4);
			this->Controls->Add(this->groupBox8);
			this->Controls->Add(this->groupBox7);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->textBox_filePath);
			this->Controls->Add(this->richTextBox_ncFile);
			this->Controls->Add(this->button_openFile);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"iCNC";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_feedOverride))->EndInit();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->groupBox8->ResumeLayout(false);
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

//
//label light
//
void label_lighton( System::Windows::Forms::Label^ label)
{
	label->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
	label->ForeColor = System::Drawing::Color::White;
	label->BackColor =  System::Drawing::Color::DarkRed;
}
void label_lightoff( System::Windows::Forms::Label^ label)
{
	label->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
	label->ForeColor = SystemColors::ControlText;
	label->BackColor =  System::Drawing::Color::Transparent;
}
void label_lightControl( System::Windows::Forms::Label^ label, bool state)
{
	if(state){label_lighton(label);}
	else{label_lightoff(label);}
}
//label flash light
bool flash_valid;
System::Windows::Forms::Label^ flash_label;
int flash_sec;
bool lighton;

void label_flashon( System::Windows::Forms::Label^ label, int sec)
{
	flash_valid = true;
	flash_label = label;
	flash_sec = sec;
	
}
void label_flashoff( System::Windows::Forms::Label^ label)
{
	flash_valid = false;
	label_lightoff(label);
}
void label_flash_main( System::Windows::Forms::Label^ label, int sec)
{
	if(flash_valid && counter%(sec*5) == 0 && lighton == true)
			{
				label_lighton(label);
				lighton = false;
			}
			else if(flash_valid && counter%(sec*5) == 0 && lighton == false)
			{
				label_lightoff(label);
				lighton = true;
			}
}
//
//sys <> form label
//
void label_main()
{
	label_lightControl(Label_M00, cnc_system->sys->M00);
	label_lightControl(Label_M30, cnc_system->sys->M30);
	label_lightControl(Label_PGM, cnc_system->sys->PGM);
	//label_lightControl(Label_ERR, cnc_system->sys->ERR);
	if( cnc_system->sys->ERR) { label_flashon(Label_ERR,1);}
	else{label_flashoff(Label_ERR);}

	label_lightControl(Label_HX, cnc_system->sys->HX);
	label_lightControl(Label_INX, cnc_system->sys->INX);
	label_lightControl(Label_HY, cnc_system->sys->HY);
	label_lightControl(Label_INY, cnc_system->sys->INY);
	label_lightControl(Label_HZ, cnc_system->sys->HZ);
	label_lightControl(Label_INZ, cnc_system->sys->INZ);

	label_lightControl(Label_PX, cnc_system->sys->PX);
	label_lightControl(Label_NX, cnc_system->sys->NX);
	label_lightControl(Label_PY, cnc_system->sys->PY);
	label_lightControl(Label_NY, cnc_system->sys->NY);
	label_lightControl(Label_PZ, cnc_system->sys->PZ);
	label_lightControl(Label_NZ, cnc_system->sys->NZ);


}

//
//time function
//
System::String^ global_time()
{
		std::time_t t = std::time(nullptr);
		struct tm *local;
		local=localtime(&t);
     	return local->tm_hour.ToString("00") + ":"+  local->tm_min.ToString("00") + ":"+ local->tm_sec.ToString("00");
}

System::String^ system_time()
{

	std::time_t t = std::time(nullptr)-start_time;
    return (t/3600).ToString("00") + ":"+ ((t%3600)/60).ToString("00") + ":"+ (t%60).ToString("00") ;
	//return (counter/36000).ToString("00") + ":"+ ((counter%36000)/600).ToString("00") + ":"+ (counter%600/10).ToString("00") ;
}


//
//error function
//
void errorShow()
{
	if(cnc_system->sys->error_valid)
	{
		System::String^ errorBlock;
		switch(cnc_system->sys->error_block)
		{
		case 1:
			errorBlock = "CNC";
			break;
		case 2:
			errorBlock = "SYS";
			break;
		case 3:
			errorBlock = "MMI";
			break;
		case 4:
			errorBlock = "DEC";
			break;
		case 5:
			errorBlock = "INTP";
			break;
		default:
			break;
		}

		System::String^ errorCode = cnc_system->sys->error_code.ToString() ;
		label_error_code->Text = "Error: "+errorBlock+"("+errorCode+")";
	}
	else
	{
		label_error_code->Text = "";
	}
}

 /*=======Movable Boardless Form=======*/
private: bool dragging;
private: Point offset;
private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->dragging = true;
			 this->offset = Point(e->X, e->Y);
		 }
private: System::Void Form1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			     if (this->dragging){ 
					 Point currentScreenPos = PointToScreen(e->Location);
					 Location = Point(currentScreenPos.X - this->offset.X, currentScreenPos.Y - this->offset.Y);
				 }
		 }
private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			  this->dragging = false;
		 }
/*=======/Movable Boardless Form=======*/


		 //
		 //Events
		 //
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e)
		 {
			 //
			 //form setting
			 //
			this->NRT_timer->Enabled = true;
			this->NRT_timer->Interval = 100;

#if DEBUG
			this->RT_timer->Enabled = true;
			this->RT_timer->Interval = 20;
#else
			initMotionCard(0,90,100,CyclingTime*1000,Timer_ISR_Function);
			enableHDTimer(HD_interval);
#endif

			this->dragging = false; //Prevent drag until set it
			this->Opacity = .95;
			flash_valid = false;
			
			//
			//record start time
			//
			start_time = std::time(nullptr);

			//
			//cnc init
			//
			 cnc_system->CNC_initialization();


			 //
			 //initial color setting
			 //
			 button_mem->BackColor = SystemColors::ActiveCaption;
			 button_mdi->BackColor = SystemColors::Control;
			 button_jog->BackColor = SystemColors::Control;
			 button_wheel->BackColor = SystemColors::Control;
			 button_teach->BackColor = SystemColors::Control;
			 button_home->BackColor = SystemColors::Control;
			 button_modeR->BackColor = SystemColors::Control;
			 button_modeL->BackColor = SystemColors::Control;

			  //
			 //active button
			 //
			 button_mem->Enabled=false;
			 button_mdi->Enabled=true;
			 button_jog->Enabled=true;
			 button_wheel->Enabled=true;
			 button_teach->Enabled=true;
			 button_home->Enabled=true;

			  //
			 //buttom enable
			 //
			 button_uvw->Enabled = false;
			 button_xp->Enabled = false;
			 button_xm->Enabled = false;
			 button_yp->Enabled = false;
			 button_ym->Enabled = false;
		  	 button_zp->Enabled = false;
		 	 button_zm->Enabled = false;
			 button_x1->Enabled = false;
			 button_x10->Enabled = false;
			 button_x100->Enabled = false;
			 button_teachST->Enabled = false;
			 button_rec->Enabled = false;
			 button_teachED->Enabled = false;
			 button_m01->Enabled = true;
			 button_fh->Enabled = true;
			 button_sb->Enabled = true;
			 trackBar_feedOverride->Enabled = false;
			 button_100per->Enabled = false;
			 richTextBox_ncFile->Enabled = true;
			 richTextBox_ncFile->ReadOnly = true;
			 button_openFile->Enabled = true;
			 button_start->Enabled = true;
			 button_reset->Enabled = true;
			 //
			 //form setting
			 //
			 simu_open = false;

		 }


private: System::Void button_openFile_Click(System::Object^  sender, System::EventArgs^  e) {	
			 
			 openFileDialog_openNC->InitialDirectory = " ";
			 openFileDialog_openNC->Filter = "文字檔(*.txt)|*.txt|所有檔案(*.*)|*.*";
			 openFileDialog_openNC->FilterIndex = 1;
			 openFileDialog_openNC->DefaultExt = "*.txt";
			 openFileDialog_openNC->FileName = "";
			 openFileDialog_openNC->RestoreDirectory = true;

			 if(openFileDialog_openNC->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 textBox_filePath->Text = openFileDialog_openNC->FileName;
				 richTextBox_ncFile->LoadFile(openFileDialog_openNC->FileName , RichTextBoxStreamType::PlainText);

				string NcPath, NcText;

				MarshalString(textBox_filePath->Text,NcPath); //包裝成std::string
				MarshalString(richTextBox_ncFile->Text,NcText); //包裝成std::string

				cnc_system->mmi->form2mmi(1, true); //驗證開啟成功

				cnc_system->mmi->form2mmi(30 ,NcPath);
				cnc_system->mmi->form2mmi(31 ,NcText);
			 }
			 else
			 {
				 //error
			 }
		 }
private: System::Void NRT_timer_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //
			 //program main
			 //
			 cnc_system->CNC_main_nrt();

			  //
			 //time show
			 //
			 label_runtime->Text = system_time();
     		 label_globaltime->Text = global_time();
			 label_main();

			 //
			 //error main
			 //
			 errorShow();

			  //
			 //label flash
			 //
			label_flash_main(flash_label,flash_sec);

			//
			 //counter
			 //
			 counter++;

			 //
			 //xyz/uvw show
			 //
			 label_showX->Text = cnc_system->sys->x_valid.ToString("#000.0000");
			 label_showY->Text = cnc_system->sys->y_valid.ToString("#000.0000");
			 label_showZ->Text = cnc_system->sys->z_valid.ToString("#000.0000");
			 label_showU->Text = Force360(cnc_system->sys->u_valid).ToString("#000.0000");
			 label_showV->Text = Force360( cnc_system->sys->v_valid).ToString("#000.0000");
			 label_showW->Text = cnc_system->sys->w_valid.ToString("#000.0000");

			  simu_u_valid = cnc_system->sys->u_valid;
			  simu_v_valid = cnc_system->sys->v_valid;
			  simu_w_valid = cnc_system->sys->w_valid;

		 }
private: System::Void RT_timer_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //
			 //cnc main
			 //
			 cnc_system->CNC_main_rt();

		
		 }
private: System::Void button_close_Click(System::Object^  sender, System::EventArgs^  e) {
			 //
			 //close form
			 //
			 this->Close();
		 }
private: System::Void button_emerg_stop_Click(System::Object^  sender, System::EventArgs^  e) {
			 cnc_system->mmi->form2mmi(26, true);
		 }


private: System::Void button_start_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(cnc_system->sys->cnc_mode==MDI)
			 {
				 string NcText;
				MarshalString(richTextBox_ncFile->Text,NcText); //包裝成std::string
				cnc_system->mmi->form2mmi(1, true); //驗證開啟成功
				cnc_system->mmi->form2mmi(31 ,NcText);
				cnc_system->mmi->form2mmi(18, true);
			 }
			 else
			 {
				 cnc_system->mmi->form2mmi(18, true);
			 }
			 
		 }
private: System::Void button_mem_Click(System::Object^  sender, System::EventArgs^  e) {
			 //reset
			 cnc_system->cncReset();
			 richTextBox_ncFile->Text = "";
			 textBox_filePath->Text="";

			 //
			 //form->mmi
			 //
			 cnc_system->mmi->form2mmi(20, true);

			 //
			 //buttom enable
			 //
			 button_uvw->Enabled = false;
			 button_xp->Enabled = false;
			 button_xm->Enabled = false;
			 button_yp->Enabled = false;
			 button_ym->Enabled = false;
		  	 button_zp->Enabled = false;
		 	 button_zm->Enabled = false;
			 button_x1->Enabled = false;
			 button_x10->Enabled = false;
			 button_x100->Enabled = false;
			 button_teachST->Enabled = false;
			 button_rec->Enabled = false;
			 button_teachED->Enabled = false;
			 button_m01->Enabled = true;
			 button_fh->Enabled = true;
			 button_sb->Enabled = true;
			 trackBar_feedOverride->Enabled = false;
			 button_100per->Enabled = false;
			 richTextBox_ncFile->Enabled = true;
			 richTextBox_ncFile->ReadOnly = true;
			 button_openFile->Enabled = true;
			 button_start->Enabled = true;
			 button_reset->Enabled = true;
			 //
			 //button color setting
			 //
			 button_mem->BackColor = SystemColors::ActiveCaption;
			 button_mdi->BackColor = SystemColors::Control;
			 button_jog->BackColor = SystemColors::Control;
			 button_wheel->BackColor = SystemColors::Control;
			 button_teach->BackColor = SystemColors::Control;
			 button_home->BackColor = SystemColors::Control;

			 //
			 //active button
			 //
			 button_mem->Enabled=false;
			 button_mdi->Enabled=true;
			 button_jog->Enabled=true;
			 button_wheel->Enabled=true;
			 button_teach->Enabled=true;
			 button_home->Enabled=true;
		 }
private: System::Void button_mdi_Click(System::Object^  sender, System::EventArgs^  e) {
			 //reset
			 cnc_system->cncReset();
			 richTextBox_ncFile->Text = "";
			 textBox_filePath->Text="";
			 //
			 //form->mmi
			 //
			 cnc_system->mmi->form2mmi(21, true);
			 //
			 //buttom enable
			 //
			 button_uvw->Enabled = false;
			 button_xp->Enabled = false;
			 button_xm->Enabled = false;
			 button_yp->Enabled = false;
			 button_ym->Enabled = false;
		  	 button_zp->Enabled = false;
		 	 button_zm->Enabled = false;
			 button_x1->Enabled = false;
			 button_x10->Enabled = false;
			 button_x100->Enabled = false;
			 button_teachST->Enabled = false;
			 button_rec->Enabled = false;
			 button_teachED->Enabled = false;
			 button_m01->Enabled = true;
			 button_fh->Enabled = true;
			 button_sb->Enabled = true;
			 trackBar_feedOverride->Enabled = false;
			 button_100per->Enabled = false;
			 richTextBox_ncFile->Enabled = true;
			 richTextBox_ncFile->ReadOnly = false;
			 button_openFile->Enabled = false;
			 button_start->Enabled = true;
			 button_reset->Enabled = true;
			  //
			 //button color setting
			 //
			 button_mem->BackColor = SystemColors::Control;
			 button_mdi->BackColor = SystemColors::ActiveCaption;
			 button_jog->BackColor = SystemColors::Control;
			 button_wheel->BackColor = SystemColors::Control;
			 button_teach->BackColor = SystemColors::Control;
			 button_home->BackColor = SystemColors::Control;

			  //
			 //active button
			 //
			 button_mem->Enabled=true;
			 button_mdi->Enabled=false;
			 button_jog->Enabled=true;
			 button_wheel->Enabled=true;
			 button_teach->Enabled=true;
			 button_home->Enabled=true;
		 }
private: System::Void button_jog_Click(System::Object^  sender, System::EventArgs^  e) {
			 //reset
			 cnc_system->cncReset();
			 richTextBox_ncFile->Text = "";
			 textBox_filePath->Text="";
			 //
			 //form->mmi
			 //
			 cnc_system->mmi->form2mmi(22, true);
			 //
			 //buttom enable
			 //
			 button_uvw->Enabled =true;
			 button_xp->Enabled = true;
			 button_xm->Enabled = true;
			 button_yp->Enabled = true;
			 button_ym->Enabled = true;
		  	 button_zp->Enabled =true;
		 	 button_zm->Enabled = true;
			 button_x1->Enabled =false;
			 button_x10->Enabled = false;
			 button_x100->Enabled = false;
			 button_teachST->Enabled =false;
			 button_rec->Enabled = false;
			 button_teachED->Enabled = false;
			 button_m01->Enabled =false;
			 button_fh->Enabled = false;
			 button_sb->Enabled = false;
			 trackBar_feedOverride->Enabled =true;
			 button_100per->Enabled = true;
			 richTextBox_ncFile->Enabled = false;
			 button_openFile->Enabled = false;
			 button_start->Enabled = false;
			 button_reset->Enabled = false;
			  //
			 //button color setting
			 //
			 button_mem->BackColor = SystemColors::Control;
			 button_mdi->BackColor = SystemColors::Control;
			 button_jog->BackColor = SystemColors::ActiveCaption;
			 button_wheel->BackColor = SystemColors::Control;
			 button_teach->BackColor = SystemColors::Control;
			 button_home->BackColor = SystemColors::Control;

			  //
			 //active button
			 //
			 button_mem->Enabled=true;
			 button_mdi->Enabled=true;
			 button_jog->Enabled=false;
			 button_wheel->Enabled=true;
			 button_teach->Enabled=true;
			 button_home->Enabled=true;
		 }
private: System::Void button_wheel_Click(System::Object^  sender, System::EventArgs^  e) {
			 //reset
			 cnc_system->cncReset();
			 richTextBox_ncFile->Text = "";
			 textBox_filePath->Text="";
			 //
			 //form->mmi
			 //
			 cnc_system->mmi->form2mmi(23, true);
			 //
			 //buttom enable
			 //
			 button_uvw->Enabled =true;
			 button_xp->Enabled = true;
			 button_xm->Enabled = true;
			 button_yp->Enabled = true;
			 button_ym->Enabled = true;
		  	 button_zp->Enabled =true;
		 	 button_zm->Enabled = true;
			 button_x1->Enabled =true;
			 button_x10->Enabled = true;
			 button_x100->Enabled = true;
			 button_teachST->Enabled =false;
			 button_rec->Enabled = false;
			 button_teachED->Enabled = false;
			 button_m01->Enabled =false;
			 button_fh->Enabled = false;
			 button_sb->Enabled = false;
			 trackBar_feedOverride->Enabled =false;
			 button_100per->Enabled = false;
			 richTextBox_ncFile->Enabled = false;
			 button_openFile->Enabled = false;
			 button_start->Enabled = false;
			 button_reset->Enabled = false;
			  //
			 //button color setting
			 //
			 button_mem->BackColor = SystemColors::Control;
			 button_mdi->BackColor = SystemColors::Control;
			 button_jog->BackColor = SystemColors::Control;
			 button_wheel->BackColor = SystemColors::ActiveCaption;
			 button_teach->BackColor = SystemColors::Control;
			 button_home->BackColor = SystemColors::Control;

			  //
			 //active button
			 //
			 button_mem->Enabled=true;
			 button_mdi->Enabled=true;
			 button_jog->Enabled=true;
			 button_wheel->Enabled=false;
			 button_teach->Enabled=true;
			 button_home->Enabled=true;
		 }
private: System::Void button_teach_Click(System::Object^  sender, System::EventArgs^  e) {
			 //reset
			 cnc_system->cncReset();
			 richTextBox_ncFile->Text = "";
			 textBox_filePath->Text="";
			 //
			 //form->mmi
			 //
			 cnc_system->mmi->form2mmi(24, true);
			  //
			 //button color setting
			 //
			 button_mem->BackColor = SystemColors::Control;
			 button_mdi->BackColor = SystemColors::Control;
			 button_jog->BackColor = SystemColors::Control;
			 button_wheel->BackColor = SystemColors::Control;
			 button_teach->BackColor = SystemColors::ActiveCaption;
			 button_home->BackColor = SystemColors::Control;

			  //
			 //active button
			 //
			 button_mem->Enabled=true;
			 button_mdi->Enabled=true;
			 button_jog->Enabled=true;
			 button_wheel->Enabled=true;
			 button_teach->Enabled=false;
			 button_home->Enabled=true;
		 }
private: System::Void button_home_Click(System::Object^  sender, System::EventArgs^  e) {
			 //reset
			 cnc_system->cncReset();
			 richTextBox_ncFile->Text = "";
			 textBox_filePath->Text="";
			 //
			 //form->mmi
			 //
			 cnc_system->mmi->form2mmi(25, true);
			  //
			 //buttom enable
			 //
			 button_uvw->Enabled =false;
			 button_xp->Enabled =false;
			 button_xm->Enabled = false;
			 button_yp->Enabled =false;
			 button_ym->Enabled = false;
		  	 button_zp->Enabled =false;
		 	 button_zm->Enabled = false;
			 button_x1->Enabled =false;
			 button_x10->Enabled = false;
			 button_x100->Enabled = false;
			 button_teachST->Enabled =false;
			 button_rec->Enabled = false;
			 button_teachED->Enabled = false;
			 button_m01->Enabled =false;
			 button_fh->Enabled = false;
			 button_sb->Enabled = false;
			 trackBar_feedOverride->Enabled =false;
			 button_100per->Enabled = false;
			 richTextBox_ncFile->Enabled = false;
			 button_openFile->Enabled = false;
			 button_start->Enabled = true;
			 button_reset->Enabled = false;

			 //
			 //input home data
			 //
			 cnc_system->mmi->form2mmi(1, true);
			 string homeCmd = "N0 G00 G90 U0 V90 W100;\nN99 M30;";
			 cnc_system->mmi->form2mmi(31 ,homeCmd);
			 richTextBox_ncFile->Text = "N0 G00 G90 U0 V90 W100;\nN99 M30;";
			  //
			 //button color setting
			 //
			 button_mem->BackColor = SystemColors::Control;
			 button_mdi->BackColor = SystemColors::Control;
			 button_jog->BackColor = SystemColors::Control;
			 button_wheel->BackColor = SystemColors::Control;
			 button_teach->BackColor = SystemColors::Control;
			 button_home->BackColor = SystemColors::ActiveCaption;

			  //
			 //active button
			 //
			 button_mem->Enabled=true;
			 button_mdi->Enabled=true;
			 button_jog->Enabled=true;
			 button_wheel->Enabled=true;
			 button_teach->Enabled=true;
			 button_home->Enabled=false;
		 }
private: System::Void button_modeR_Click(System::Object^  sender, System::EventArgs^  e) {
			 int right_click = 80;
			 if(button_mem->Location.X <440){ 
				 button_mem->Location = System::Drawing::Point(button_mem->Location.X+right_click, button_mem->Location.Y);}
			 else{button_mem->Location = System::Drawing::Point(button_mem->Location.X-5*right_click, button_mem->Location.Y);}

			 if(button_mdi->Location.X <440){ 
				 button_mdi->Location = System::Drawing::Point(button_mdi->Location.X+right_click, button_mdi->Location.Y);}
			 else{button_mdi->Location = System::Drawing::Point(button_mdi->Location.X-5*right_click, button_mdi->Location.Y);}

			 if(button_jog->Location.X <440){ 
				 button_jog->Location = System::Drawing::Point(button_jog->Location.X+right_click, button_jog->Location.Y);}
			 else{button_jog->Location = System::Drawing::Point(button_jog->Location.X-5*right_click, button_jog->Location.Y);}

			 if(button_wheel->Location.X <440){ 
				 button_wheel->Location = System::Drawing::Point(button_wheel->Location.X+right_click, button_wheel->Location.Y);}
			 else{button_wheel->Location = System::Drawing::Point(button_wheel->Location.X-5*right_click, button_wheel->Location.Y);}

			 if(button_teach->Location.X <440){ 
				 button_teach->Location = System::Drawing::Point(button_teach->Location.X+right_click, button_teach->Location.Y);}
			 else{button_teach->Location = System::Drawing::Point(button_teach->Location.X-5*right_click, button_teach->Location.Y);}

			 if(button_home->Location.X <440){ 
				 button_home->Location = System::Drawing::Point(button_home->Location.X+right_click, button_home->Location.Y);}
			 else{button_home->Location = System::Drawing::Point(button_home->Location.X-5*right_click, button_home->Location.Y);}
		 }
private: System::Void button_modeL_Click(System::Object^  sender, System::EventArgs^  e) {
			 int left_click = -80;
			 if(button_mem->Location.X >50){ 
				 button_mem->Location = System::Drawing::Point(button_mem->Location.X+left_click, button_mem->Location.Y);}
			 else{button_mem->Location = System::Drawing::Point(button_mem->Location.X-5*left_click, button_mem->Location.Y);}

			 if(button_mdi->Location.X >50){ 
				 button_mdi->Location = System::Drawing::Point(button_mdi->Location.X+left_click, button_mdi->Location.Y);}
			 else{button_mdi->Location = System::Drawing::Point(button_mdi->Location.X-5*left_click, button_mdi->Location.Y);}

			 if(button_jog->Location.X >50){ 
				 button_jog->Location = System::Drawing::Point(button_jog->Location.X+left_click, button_jog->Location.Y);}
			 else{button_jog->Location = System::Drawing::Point(button_jog->Location.X-5*left_click, button_jog->Location.Y);}

			 if(button_wheel->Location.X >50){ 
				 button_wheel->Location = System::Drawing::Point(button_wheel->Location.X+left_click, button_wheel->Location.Y);}
			 else{button_wheel->Location = System::Drawing::Point(button_wheel->Location.X-5*left_click, button_wheel->Location.Y);}

			 if(button_teach->Location.X >50){ 
				 button_teach->Location = System::Drawing::Point(button_teach->Location.X+left_click, button_teach->Location.Y);}
			 else{button_teach->Location = System::Drawing::Point(button_teach->Location.X-5*left_click, button_teach->Location.Y);}

			 if(button_home->Location.X >50){ 
				 button_home->Location = System::Drawing::Point(button_home->Location.X+left_click, button_home->Location.Y);}
			 else{button_home->Location = System::Drawing::Point(button_home->Location.X-5*left_click, button_home->Location.Y);}
		 }
private: System::Void button_x1_Click(System::Object^  sender, System::EventArgs^  e) {
			 cnc_system->sys->speed_1=true;
			 cnc_system->sys->speed_10=false;
			 cnc_system->sys->speed_100=false;

			 button_x1->BackColor = SystemColors::ActiveCaption;
			 button_x10->BackColor = SystemColors::Control;
			 button_x100->BackColor = SystemColors::Control;
		 }
private: System::Void button_x10_Click(System::Object^  sender, System::EventArgs^  e) {
			 cnc_system->sys->speed_1=false;
			 cnc_system->sys->speed_10=true;
			 cnc_system->sys->speed_100=false;

			 button_x1->BackColor = SystemColors::Control;
			 button_x10->BackColor = SystemColors::ActiveCaption;
			 button_x100->BackColor = SystemColors::Control;
		 }
private: System::Void button_x100_Click(System::Object^  sender, System::EventArgs^  e) {
			 cnc_system->sys->speed_1=false;
			 cnc_system->sys->speed_10=false;
			 cnc_system->sys->speed_100=true;

			 button_x1->BackColor = SystemColors::Control;
			 button_x10->BackColor = SystemColors::Control;
			 button_x100->BackColor = SystemColors::ActiveCaption;
		 }
private: System::Void button_progU_Click(System::Object^  sender, System::EventArgs^  e) {
			 int up_click = -70;
			 if(button_para->Location.Y >50){ 
				 button_para->Location = System::Drawing::Point(button_para->Location.X, button_para->Location.Y+up_click);}
			 else{button_para->Location = System::Drawing::Point(button_para->Location.X, button_para->Location.Y-2*up_click);}

			 if(button_simu->Location.Y >50){ 
				 button_simu->Location = System::Drawing::Point(button_simu->Location.X, button_simu->Location.Y+up_click);}
			 else{button_simu->Location = System::Drawing::Point(button_simu->Location.X, button_simu->Location.Y-2*up_click);}

			 if(button_diag->Location.Y >50){ 
				 button_diag->Location = System::Drawing::Point(button_diag->Location.X, button_diag->Location.Y+up_click);}
			 else{button_diag->Location = System::Drawing::Point(button_diag->Location.X, button_diag->Location.Y-2*up_click);}
		 }
private: System::Void button_progD_Click(System::Object^  sender, System::EventArgs^  e) {
			 int down_click = 70;
			 if(button_para->Location.Y <180){ 
				 button_para->Location = System::Drawing::Point(button_para->Location.X, button_para->Location.Y+down_click);}
			 else{button_para->Location = System::Drawing::Point(button_para->Location.X, button_para->Location.Y-2*down_click);}

			 if(button_simu->Location.Y <180){ 
				 button_simu->Location = System::Drawing::Point(button_simu->Location.X, button_simu->Location.Y+down_click);}
			 else{button_simu->Location = System::Drawing::Point(button_simu->Location.X, button_simu->Location.Y-2*down_click);}

			 if(button_diag->Location.Y <180){ 
				 button_diag->Location = System::Drawing::Point(button_diag->Location.X, button_diag->Location.Y+down_click);}
			 else{button_diag->Location = System::Drawing::Point(button_diag->Location.X, button_diag->Location.Y-2*down_click);}
		 }
private: System::Void trackBar_feedOverride_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 label_feedOverride->Text = trackBar_feedOverride->Value.ToString() + "%";
			  cnc_system->mmi->form2mmi(32, trackBar_feedOverride->Value);
		 }
private: System::Void button_100per_Click(System::Object^  sender, System::EventArgs^  e) {
			 trackBar_feedOverride->Value = 100;
			  label_feedOverride->Text = "100%";
			  cnc_system->mmi->form2mmi(32, trackBar_feedOverride->Value);
		 }
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 // If the no button was pressed ...
			  if ((MessageBox::Show(
				 "Are you sure that you would like to exit?", 
				 "Exit", MessageBoxButtons::YesNo, 
				 MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No ))
			  {
				 // cancel the closure of the form.
				 e->Cancel = true;
 #if !DEBUG
				disableHDTimer();
				closeMotionCard();
#endif
			  }
				 }

private: System::Void button_simu_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!simu_open) //ensure only one form will show
			 {
				simulate^ Simu = gcnew simulate;
				Simu->Show();
				simu_open = true;
			 }
		 }
private: System::Void button_reset_Click(System::Object^  sender, System::EventArgs^  e) {
			 cnc_system->cncReset();
			 richTextBox_ncFile->Text = "";
			 textBox_filePath->Text="";
		 }
private: System::Void button_m01_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!cnc_system->sys->M01)
			{
				cnc_system->sys->M01=true;
				button_m01->BackColor = SystemColors::ActiveCaption;
			 }
			 else
			 {
				 cnc_system->sys->M01=false;
				 button_m01->BackColor = SystemColors::Control;
			 }
		 }
private: System::Void button_fh_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!cnc_system->sys->FH)
			{
				cnc_system->sys->FH=true;
				button_fh->BackColor = SystemColors::ActiveCaption;
			 }
			 else
			 {
				 cnc_system->sys->FH=false;
				 button_fh->BackColor = SystemColors::Control;
			 }
		 }
private: System::Void button_sb_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!cnc_system->sys->SB)
			{
				cnc_system->sys->SB=true;
				button_sb->BackColor = SystemColors::ActiveCaption;
			 }
			 else
			 {
				 cnc_system->sys->SB=false;
				 button_sb->BackColor = SystemColors::Control;
			 }
		 }
private: System::Void button_uvw_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(!cnc_system->sys->UVW)
			{
				cnc_system->sys->UVW=true;
				button_uvw->BackColor = SystemColors::ActiveCaption;
				button_xp->Text = "U+";
				button_xm->Text = "U-";
				button_yp->Text = "V+";
				button_ym->Text = "V-";
				button_zp->Text = "W+";
				button_zm->Text = "W-";
			 }
			 else
			 {
				 cnc_system->sys->UVW=false;
				 button_uvw->BackColor = SystemColors::Control;
				 button_xp->Text = "X+";
				button_xm->Text = "X-";
				button_yp->Text = "Y+";
				button_ym->Text = "Y-";
				button_zp->Text = "Z+";
				button_zm->Text = "Z-";
			 }
		 }
		 //
		 //JOG MODE
		 //
private: System::Void button_xp_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 //
			 //input data
			 //
			if(cnc_system->sys->cnc_mode == JOG)
			{
				 if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->PX)
					 {
						 cnc_system->intp->INTP_input(0,300,cnc_system->sys-> feedOverride*0.2);
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
					 cnc_system->intp->INTP_input(3,360,cnc_system->sys-> feedOverride*0.1);
				 }
			}
			else if(cnc_system->sys->cnc_mode == WHEEL)
			{
				if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->PX)
					 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(0,0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(0,1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(0,10,20);
						}
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(3,0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(3,1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(3,10,20);
						}
				 }
			}
		 }
private: System::Void button_xp_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(cnc_system->sys->cnc_mode == JOG)
			{
				cnc_system->intp->INTP_stop();
			}
		 }
private: System::Void button_xm_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 //
			 //input data
			 //
			if(cnc_system->sys->cnc_mode == JOG)
			{
				 if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->NX)
					 {
						 cnc_system->intp->INTP_input(0,-300,cnc_system->sys-> feedOverride*0.2);
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
					 cnc_system->intp->INTP_input(3,-360,cnc_system->sys-> feedOverride*0.1);
				 }
			}
			else if(cnc_system->sys->cnc_mode == WHEEL)
			{
				if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->NX)
					 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(0,-0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(0,-1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(0,-10,20);
						}
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(3,-0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(3,-1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(3,-10,20);
						}
				 }
			}
		 }
private: System::Void button_xm_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(cnc_system->sys->cnc_mode == JOG)
			{
				cnc_system->intp->INTP_stop();
			}
		 }
private: System::Void button_yp_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			  //
			 //input data
			 //
			if(cnc_system->sys->cnc_mode == JOG)
			{
				 if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->PY)
					 {
						 cnc_system->intp->INTP_input(1,300,cnc_system->sys-> feedOverride*0.2);
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
					 cnc_system->intp->INTP_input(4,360,cnc_system->sys-> feedOverride*0.1);
				 }
			}
			else if(cnc_system->sys->cnc_mode == WHEEL)
			{
				if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->PY)
					 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(1,0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(1,1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(1,10,20);
						}
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(4,0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(4,1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(4,10,20);
						}
				 }
			}
		 }
private: System::Void button_yp_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(cnc_system->sys->cnc_mode == JOG)
			{
				cnc_system->intp->INTP_stop();
			}
		 }
private: System::Void button_ym_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			  //
			 //input data
			 //
			if(cnc_system->sys->cnc_mode == JOG)
			{
				 if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->NY)
					 {
						 cnc_system->intp->INTP_input(1,-300,cnc_system->sys-> feedOverride*0.2);
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
					 cnc_system->intp->INTP_input(4,-360,cnc_system->sys-> feedOverride*0.1);
				 }
			}
			else if(cnc_system->sys->cnc_mode == WHEEL)
			{
				if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->NY)
					 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(1,-0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(1,-1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(1,-10,20);
						}
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(4,-0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(4,-1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(4,-10,20);
						}
				 }
			}
		 }
private: System::Void button_ym_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			if(cnc_system->sys->cnc_mode == JOG)
			{
				cnc_system->intp->INTP_stop();
			}
		 }
private: System::Void button_zp_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			  //
			 //input data
			 //
			if(cnc_system->sys->cnc_mode == JOG)
			{
				 if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->PZ)
					 {
						 cnc_system->intp->INTP_input(2,300,cnc_system->sys-> feedOverride*0.2);
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
					 cnc_system->intp->INTP_input(5,360,cnc_system->sys-> feedOverride*0.1);
				 }
			}
			else if(cnc_system->sys->cnc_mode == WHEEL)
			{
				if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->PZ)
					 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(2,0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(2,1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(2,10,20);
						}
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(5,0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(5,1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(5,10,20);
						}
				 }
			}
		 }
private: System::Void button_zp_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(cnc_system->sys->cnc_mode == JOG)
			{
				cnc_system->intp->INTP_stop();
			}
		 }
private: System::Void button_zm_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			  //
			 //input data
			 //
			if(cnc_system->sys->cnc_mode == JOG)
			{
				 if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->NZ)
					 {
						 cnc_system->intp->INTP_input(2,-300,cnc_system->sys-> feedOverride*0.2);
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
					 cnc_system->intp->INTP_input(5,-360,cnc_system->sys-> feedOverride*0.1);
				 }
			}
			else if(cnc_system->sys->cnc_mode == WHEEL)
			{
				if(!cnc_system->sys->UVW)
				 {
					 if (!cnc_system->sys->NZ)
					 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(2,-0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(2,-1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(2,-10,20);
						}
					 }
					 else
					 {
						 cnc_system->intp->INTP_stop();
					 }
				 }
				 else
				 {
						if(cnc_system->sys->speed_1)
						{
							cnc_system->intp->INTP_input(5,-0.1,5);
						}
						else if(cnc_system->sys->speed_10)
						{
							cnc_system->intp->INTP_input(5,-1,10);
						}
						else if(cnc_system->sys->speed_100)
						{
							cnc_system->intp->INTP_input(5,-10,20);
						}
				 }
			}
		 }
private: System::Void button_zm_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(cnc_system->sys->cnc_mode == JOG)
			{
				cnc_system->intp->INTP_stop();
			}
		 }
};
}

