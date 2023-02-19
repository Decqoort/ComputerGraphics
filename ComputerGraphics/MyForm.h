#pragma once
#include "OpenGl.h"

namespace ComputerGraphics {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace OpenGLForm;


	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

			OpenGl = gcnew COpenGl(this, this->panel1->Size.Width, this->panel1->Size.Height);
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		COpenGl^ OpenGl;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::ComboBox^ comboBox1;


		System::Windows::Forms::Timer^ timer1;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(10, 10);
			this->panel1->Margin = System::Windows::Forms::Padding(0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(980, 670);
			this->panel1->TabIndex = 0;
			this->panel1->Visible = false;
			// 
			// comboBox1
			// 
			this->comboBox1->BackColor = System::Drawing::SystemColors::HighlightText;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"GL_TRIANGLES", L"GL_POINTS" });
			this->comboBox1->Location = System::Drawing::Point(1034, 31);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(191, 21);
			this->comboBox1->TabIndex = 1;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			this->comboBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::comboBox1_KeyPress);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1264, 681);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Ибатов Н. 0381";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		/*UNREFERENCED_PARAMETER(sender);
		UNREFERENCED_PARAMETER(e);
		OpenGl->Render();
		OpenGl->SwapOpenGLBuffers();*/
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		UNREFERENCED_PARAMETER(sender);
		UNREFERENCED_PARAMETER(e);
		std::vector<std::pair<float,float>> triangle = {
			std::make_pair(0.5, 0),
			std::make_pair(0, 0.5),
			std::make_pair(0, 0)
		};
		OpenGl->RenderInit();
		OpenGl->Render(triangle, GL_TRIANGLES);
		OpenGl->SwapOpenGLBuffers();
	}
	private: System::Void comboBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		e->Handled = true;
	}
	};
}
