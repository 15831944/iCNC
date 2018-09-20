#pragma once

extern double simu_u_valid,simu_v_valid,simu_w_valid;
extern bool simu_open;
#include "UTIL\INC\UTIL.h"


namespace iCNC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for simulate
	/// </summary>
	public ref class simulate : public System::Windows::Forms::Form
	{
	public:
		simulate(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~simulate()
		{
			if (components)
			{
				simu_open = false;
				delete components;
				
			}
		}
	private: System::Windows::Forms::Timer^  simu_timer;
	protected: 

	protected: 
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
			this->simu_timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// simu_timer
			// 
			this->simu_timer->Tick += gcnew System::EventHandler(this, &simulate::simu_timer_Tick);
			// 
			// simulate
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(334, 331);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"simulate";
			this->Text = L"Simulator";
			this->Load += gcnew System::EventHandler(this, &simulate::simulate_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &simulate::simulate_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void simulate_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ Coordi = e->Graphics;
				 Graphics^ Machine = e->Graphics;
				 Pen^ BlackPen = gcnew Pen(Color::FromArgb(0,0,0) );
			     BlackPen->Width = 1.0F;

				 //
				 //Draw coordinate
				 //
				  Coordi->DrawLine(BlackPen,15,170,325,170);
				  Coordi->DrawLine(BlackPen,170,15,170,325);
				  //
				  //Draw spacing point
				  //
				  Coordi->DrawLine(BlackPen,140,170,140,168);  //x-30
				  Coordi->DrawLine(BlackPen,110,170,110,168);  //x-60
				  Coordi->DrawLine(BlackPen,80,170,80,168);  //x-90
				  Coordi->DrawLine(BlackPen,50,170,50,168);  //x-120
				  Coordi->DrawLine(BlackPen,20,170,20,168);  //x-150
				  Coordi->DrawLine(BlackPen,200,170,200,168);  //x+30
				  Coordi->DrawLine(BlackPen,230,170,230,168);  //x+60
				  Coordi->DrawLine(BlackPen,260,170,260,168);  //x+90
				  Coordi->DrawLine(BlackPen,290,170,290,168);  //x+120
				  Coordi->DrawLine(BlackPen,320,170,320,168);  //x+150
				  Coordi->DrawLine(BlackPen,170,140,172,140);  //y-30
				  Coordi->DrawLine(BlackPen,170,110,172,110);  //y-60
				  Coordi->DrawLine(BlackPen,170,80,172,80);  //y-90
				  Coordi->DrawLine(BlackPen,170,50,172,50);  //y-120
				  Coordi->DrawLine(BlackPen,170,20,172,20);  //y-150
				  Coordi->DrawLine(BlackPen,170,200,172,200);  //y+30
				  Coordi->DrawLine(BlackPen,170,230,172,230);  //y+60
				  Coordi->DrawLine(BlackPen,170,260,172,260);  //y+90
				  Coordi->DrawLine(BlackPen,170,290,172,290);  //y+120
				  Coordi->DrawLine(BlackPen,170,320,172,320);  //y+150

				  Pen^ GrayPen = gcnew Pen(Color::FromArgb(127,0,0) );
			      BlackPen->Width = 1.5F;
				  Coordi->DrawEllipse(GrayPen,20,20,300,300);  //margin

				  
				 //
				//Define L1 L2 point
				//
				double L1,L2;
				L1 = L2 = 75;
				int P1[2],P2[2];
				P1[0] = (int)(L1*cos(DegreeToRad(simu_u_valid)));
				P1[1] = (int)(L1*sin(DegreeToRad(simu_u_valid)));
				P2[0] = (int)(L1*cos(DegreeToRad(simu_u_valid))+L2*cos(DegreeToRad(simu_u_valid+simu_v_valid)));
				P2[1] = (int)(L1*sin(DegreeToRad(simu_u_valid))+L2*sin(DegreeToRad(simu_u_valid+simu_v_valid)));
				double a = simu_u_valid;
				double b = simu_v_valid;

				//
				//plot
				//
				Pen^ LinePen = gcnew Pen(Color::FromArgb((int)simu_w_valid*255/200,255-(int)simu_w_valid*255/200,10) );
			    LinePen->Width = 2.0F;
				Machine->DrawLine(LinePen,170,170,170+P1[0],170-P1[1]);  //L1
				Machine->DrawLine(LinePen,170+P1[0],170-P1[1],170+P2[0],170-P2[1]);  //L2

			 }
	private: System::Void simulate_Load(System::Object^  sender, System::EventArgs^  e) {
				 simu_timer->Enabled = true;
				 simu_timer->Interval = 100;
			 }

private: System::Void simu_timer_Tick(System::Object^  sender, System::EventArgs^  e) {
			 this->Invalidate();
		 }
};
}
