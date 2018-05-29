#pragma once

#include "DotNetUtilities.h"
#include "Mesh/GUA_OM.h"
#include "Mesh/DP.h"
#include <fstream>
#include <sstream>

Tri_Mesh *mesh;

xform xf = xform::trans(0, 0, -2);
xform xf2 = xform::trans(0.7, -0.7, -2)*xform::scale(0.5, 0.5, 1);
GLCamera camera;
bool showParameter=0;

float fov = 0.7f;
int winX=0;
int winY=0;

enum SELECTMODE {REMOVE,ADD,HOLD};
int Mode = HOLD;
int DynamicMode = HOLD;

std::vector<GLuint> TexIDs;
std::vector<std::string> TexSource;
GLuint currentTexture = 0;
std::string Model="";
vec4 currentColor(1,1,1,1);

static const Mouse::button physical_to_logical_map[] = {
	Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
	Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
};
Mouse::button Mouse_State = Mouse::ROTATE;

namespace OpenMesh_EX {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
			glEnable(GL_TEXTURE_2D);
		}
	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadModelToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openModelDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveModelDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveModelToolStripMenuItem;






	private: System::Windows::Forms::OpenFileDialog^  openTextureDialog;

	private: System::Windows::Forms::ToolStripMenuItem^  loadTextureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveFileToolStripMenuItem;


	private: System::Windows::Forms::ComboBox^  comboBox1;

	private: System::Windows::Forms::HScrollBar^  TextureSize;
	private: System::Windows::Forms::HScrollBar^  TextureAngle;

	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;
	private: System::Windows::Forms::ToolStripMenuItem^  loadFileToolStripMenuItem;
	private: System::Windows::Forms::HScrollBar^  TextureX;
	private: System::Windows::Forms::HScrollBar^  TextureY;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ViewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  SelectToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  unSeletModeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  reverseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem1;














	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadTextureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveModelDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openTextureDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->TextureSize = (gcnew System::Windows::Forms::HScrollBar());
			this->TextureAngle = (gcnew System::Windows::Forms::HScrollBar());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SelectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->unSeletModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->reverseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TextureX = (gcnew System::Windows::Forms::HScrollBar());
			this->TextureY = (gcnew System::Windows::Forms::HScrollBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1->SuspendLayout();
			this->contextMenuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(522, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->loadModelToolStripMenuItem,
					this->saveModelToolStripMenuItem, this->loadTextureToolStripMenuItem, this->saveFileToolStripMenuItem, this->loadFileToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadModelToolStripMenuItem
			// 
			this->loadModelToolStripMenuItem->Name = L"loadModelToolStripMenuItem";
			this->loadModelToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->loadModelToolStripMenuItem->Text = L"Load Model";
			this->loadModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadModelToolStripMenuItem_Click);
			// 
			// saveModelToolStripMenuItem
			// 
			this->saveModelToolStripMenuItem->Name = L"saveModelToolStripMenuItem";
			this->saveModelToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->saveModelToolStripMenuItem->Text = L"Save Model";
			this->saveModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveModelToolStripMenuItem_Click);
			// 
			// loadTextureToolStripMenuItem
			// 
			this->loadTextureToolStripMenuItem->Name = L"loadTextureToolStripMenuItem";
			this->loadTextureToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->loadTextureToolStripMenuItem->Text = L"Load Texture";
			this->loadTextureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadTextureToolStripMenuItem_Click);
			// 
			// saveFileToolStripMenuItem
			// 
			this->saveFileToolStripMenuItem->Name = L"saveFileToolStripMenuItem";
			this->saveFileToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->saveFileToolStripMenuItem->Text = L"Save File";
			this->saveFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveFileToolStripMenuItem_Click);
			// 
			// loadFileToolStripMenuItem
			// 
			this->loadFileToolStripMenuItem->Name = L"loadFileToolStripMenuItem";
			this->loadFileToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->loadFileToolStripMenuItem->Text = L"Load File";
			this->loadFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadFileToolStripMenuItem_Click);
			// 
			// openModelDialog
			// 
			this->openModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openModelDialog_FileOk);
			// 
			// saveModelDialog
			// 
			this->saveModelDialog->DefaultExt = L"obj";
			this->saveModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveModelDialog_FileOk);
			// 
			// openTextureDialog
			// 
			this->openTextureDialog->FileName = L"openFileDialog1";
			this->openTextureDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openTextureDialog_FileOk);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"Color" });
			this->comboBox1->Location = System::Drawing::Point(6, 12);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(92, 20);
			this->comboBox1->TabIndex = 11;
			this->comboBox1->Text = L"Style";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// TextureSize
			// 
			this->TextureSize->Location = System::Drawing::Point(120, 12);
			this->TextureSize->Maximum = 109;
			this->TextureSize->Name = L"TextureSize";
			this->TextureSize->Size = System::Drawing::Size(80, 18);
			this->TextureSize->TabIndex = 12;
			this->TextureSize->Value = 50;
			this->TextureSize->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MyForm::TextureAdjust);
			// 
			// TextureAngle
			// 
			this->TextureAngle->Location = System::Drawing::Point(216, 12);
			this->TextureAngle->Maximum = 109;
			this->TextureAngle->Name = L"TextureAngle";
			this->TextureAngle->Size = System::Drawing::Size(80, 18);
			this->TextureAngle->TabIndex = 13;
			this->TextureAngle->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MyForm::TextureAdjust);
			// 
			// hkoglPanelControl1
			// 
			this->hkoglPanelControl1->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->ContextMenuStrip = this->contextMenuStrip1;
			this->hkoglPanelControl1->Cursor = System::Windows::Forms::Cursors::NoMove2D;
			this->hkoglPanelControl1->Location = System::Drawing::Point(12, 34);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(500, 500);
			this->hkoglPanelControl1->TabIndex = 2;
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::hkoglPanelControl1_KeyDown);
			this->hkoglPanelControl1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::hkoglPanelControl1_KeyUp);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseUp);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseWheel);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->ViewToolStripMenuItem,
					this->SelectToolStripMenuItem, this->unSeletModeToolStripMenuItem, this->reverseToolStripMenuItem, this->clearToolStripMenuItem1
			});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(153, 136);
			// 
			// ViewToolStripMenuItem
			// 
			this->ViewToolStripMenuItem->Checked = true;
			this->ViewToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ViewToolStripMenuItem->Name = L"ViewToolStripMenuItem";
			this->ViewToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->ViewToolStripMenuItem->Text = L"View";
			this->ViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ViewToolStripMenuItem_Click);
			// 
			// SelectToolStripMenuItem
			// 
			this->SelectToolStripMenuItem->Name = L"SelectToolStripMenuItem";
			this->SelectToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->SelectToolStripMenuItem->Text = L"Select";
			this->SelectToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::SelectToolStripMenuItem_Click);
			// 
			// unSeletModeToolStripMenuItem
			// 
			this->unSeletModeToolStripMenuItem->Name = L"unSeletModeToolStripMenuItem";
			this->unSeletModeToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->unSeletModeToolStripMenuItem->Text = L"unSelect";
			this->unSeletModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::unSeletModeToolStripMenuItem_Click);
			// 
			// reverseToolStripMenuItem
			// 
			this->reverseToolStripMenuItem->Name = L"reverseToolStripMenuItem";
			this->reverseToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->reverseToolStripMenuItem->Text = L"Reverse";
			this->reverseToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::reverseToolStripMenuItem_Click);
			// 
			// clearToolStripMenuItem1
			// 
			this->clearToolStripMenuItem1->Name = L"clearToolStripMenuItem1";
			this->clearToolStripMenuItem1->Size = System::Drawing::Size(152, 22);
			this->clearToolStripMenuItem1->Text = L"Clear/Done";
			this->clearToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::clearToolStripMenuItem1_Click);
			// 
			// TextureX
			// 
			this->TextureX->Location = System::Drawing::Point(310, 12);
			this->TextureX->Maximum = 109;
			this->TextureX->Name = L"TextureX";
			this->TextureX->Size = System::Drawing::Size(80, 18);
			this->TextureX->TabIndex = 13;
			this->TextureX->Value = 50;
			this->TextureX->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MyForm::TextureAdjust);
			// 
			// TextureY
			// 
			this->TextureY->Location = System::Drawing::Point(404, 12);
			this->TextureY->Maximum = 109;
			this->TextureY->Name = L"TextureY";
			this->TextureY->Size = System::Drawing::Size(80, 18);
			this->TextureY->TabIndex = 13;
			this->TextureY->Value = 50;
			this->TextureY->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &MyForm::TextureAdjust);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(111, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(13, 12);
			this->label1->TabIndex = 14;
			this->label1->Text = L"R";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(208, 15);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(13, 12);
			this->label2->TabIndex = 14;
			this->label2->Text = L"G";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(302, 15);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(13, 12);
			this->label3->TabIndex = 15;
			this->label3->Text = L"B";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(396, 15);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(13, 12);
			this->label4->TabIndex = 16;
			this->label4->Text = L"A";
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog_FileOk);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(490, 509);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(22, 25);
			this->button1->TabIndex = 17;
			this->button1->Text = L"↖";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Controls->Add(this->TextureSize);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->TextureAngle);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->TextureX);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->TextureY);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Enabled = false;
			this->groupBox1->Location = System::Drawing::Point(17, 540);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(490, 35);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Texture/Color";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(413, -1);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(78, 16);
			this->checkBox1->TabIndex = 18;
			this->checkBox1->Text = L"TextureFlip";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveFileDialog_FileOk);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(522, 579);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"OpenMesh_EX";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->contextMenuStrip1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

void SetTexture()
{
	if (currentTexture)
	{
		if (mesh != NULL)
		{
			mesh->CreateSubMesh();

			if (mesh->SubMesh)
			{
				mesh->SubMesh->parametrization(
					double(TextureSize->Value) / 100*5,
					double(TextureAngle->Value) / 100 * 6.28,
					double(TextureX->Value) / 100,
					double(TextureY->Value) / 100,
					checkBox1->Checked
				);
				mesh->BindTexture(currentTexture);
			}
			hkoglPanelControl1->Invalidate();
		}
	}
	else
	{

		if (mesh != NULL)
		{			
				currentColor = vec4(double(TextureSize->Value) / 100,
					double(TextureAngle->Value) / 100,
					double(TextureX->Value) / 100,
					double(TextureY->Value) / 100);

				mesh->BindColor(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
			
			hkoglPanelControl1->Invalidate();
		}			
	}

}

OMT::Vector3d window_2_ThreeD(int x, int y,xform xf)
{	
	OMT::Vector3d DrawDot(0, 0, 0);

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &DrawDot[0], &DrawDot[1], &DrawDot[2]);

	return OMT::Vector3d(
		DrawDot[0] * inv(xf)[0] + DrawDot[1] * inv(xf)[4] + DrawDot[2] * inv(xf)[8] + inv(xf)[12],
		DrawDot[0] * inv(xf)[1] + DrawDot[1] * inv(xf)[5] + DrawDot[2] * inv(xf)[9] + inv(xf)[13],
		DrawDot[0] * inv(xf)[2] + DrawDot[1] * inv(xf)[6] + DrawDot[2] * inv(xf)[10] + inv(xf)[14]
	);
}

private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
{
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	point center;
	center[0] = 0.0;
	center[1] = 0.0;
	center[2] = 0.0;
	camera.setupGL(xf* center, 1.0);

	/*--------------------------------------------------------------*/	
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixd((double *)xf2);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_DEPTH_TEST);
	glPolygonOffset(2.0, 2.0);
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
	glBindTexture(GL_TEXTURE_2D, currentTexture);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glNormal3d(0, 0, 1); glVertex3d(-0.5, -0.5, 0);
	glTexCoord2d(1, 0); glNormal3d(0, 0, 1); glVertex3d(0.5, -0.5,0);
	glTexCoord2d(1, 1); glNormal3d(0, 0, 1); glVertex3d(0.5, 0.5,0);
	glTexCoord2d(0, 1); glNormal3d(0, 0, 1); glVertex3d(-0.5, 0.5,0);
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);	

	if ((mesh != NULL) && (mesh->SubMesh != NULL))
	{
		mesh->SubMesh->drawParameterization(-0.5, -0.5);
	}
	glPopMatrix();
	/*--------------------------------------------------------------*/

	/*--------------------------------------------------------------*/
	if (!showParameter)
	{
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixd((double *)xf);

		if (mesh != NULL)
		{

			if (DynamicMode != HOLD)
				mesh->Render_SolidWireframe();
			else
				mesh->Render_Solid();
		}
		glPopMatrix();
	}	
	/*--------------------------------------------------------------*/

}
private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if(!showParameter)
	if (e->Button == System::Windows::Forms::MouseButtons::Left ||
		e->Button == System::Windows::Forms::MouseButtons::Middle)
	{
		point center;
		Mouse_State = Mouse::NONE;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.mouse(e->X, e->Y, Mouse_State,
			xf * center,
			1.0, xf);
	}
	if (Mode != Dynamic)
	Mode = DynamicMode;
}

 private: System::Void hkoglPanelControl1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	 Mode = HOLD;
	 hkoglPanelControl1->Invalidate();
 }
private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	winX = e->X;
	winY = e->Y;
	if (mesh && (Mode != HOLD))
	{	
		OMT::Vector3d temp = window_2_ThreeD(winX, winY, xf);
		mesh->SelectFace(temp, Mode);
		
		if (mesh->selectedFaceCount)
			groupBox1->Enabled = TRUE;
		else
			groupBox1->Enabled =FALSE;
		
		hkoglPanelControl1->Invalidate();
	}
	else if(!showParameter)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			point center;
			Mouse_State = Mouse::ROTATE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			hkoglPanelControl1->Invalidate();
		}

		if (e->Button == System::Windows::Forms::MouseButtons::Middle)
		{
			point center;
			Mouse_State = Mouse::MOVEXY;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
	}	
}

private: System::Void hkoglPanelControl1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	
	if (mesh &&( DynamicMode != HOLD))
	{
		if (e->Delta > 0)
		{
			mesh->SelectOneRing();
		}
		else
			mesh->DeleteBoundary();
		
		hkoglPanelControl1->Invalidate();
	}
	else if (!showParameter)
	if (e->Delta < 0)
	{
		xf = xf*xform::scale(0.8, 0.8, 0.8);		
		hkoglPanelControl1->Invalidate();
	}
	else
	{
		xf = xf*xform::scale(1.1, 1.1,1.1);		
		hkoglPanelControl1->Invalidate();
	}
}

private: System::Void ViewToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	DynamicMode = HOLD;
	hkoglPanelControl1->Cursor = System::Windows::Forms::Cursors::NoMove2D;
	ViewToolStripMenuItem->Checked = TRUE;
	SelectToolStripMenuItem->Checked = FALSE;
	unSeletModeToolStripMenuItem->Checked = FALSE;
	hkoglPanelControl1->Invalidate();
}
private: System::Void SelectToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	DynamicMode = ADD;
	hkoglPanelControl1->Cursor = System::Windows::Forms::Cursors::Cross;
	ViewToolStripMenuItem->Checked = FALSE;
	SelectToolStripMenuItem->Checked = TRUE;
	unSeletModeToolStripMenuItem->Checked = FALSE;
	hkoglPanelControl1->Invalidate();
}
private: System::Void unSeletModeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	DynamicMode = REMOVE;
	hkoglPanelControl1->Cursor = System::Windows::Forms::Cursors::Cross;
	ViewToolStripMenuItem->Checked = FALSE;
	SelectToolStripMenuItem->Checked = FALSE;
	unSeletModeToolStripMenuItem->Checked = TRUE;
	hkoglPanelControl1->Invalidate();
}

private: System::Void ReverseFaceSelected_Click(System::Object^  sender, System::EventArgs^  e) {
	if (mesh)
	{
		mesh->ReverseSelected();

		if (mesh->selectedFaceCount)
			groupBox1->Enabled = TRUE;
		else
			groupBox1->Enabled = FALSE;


		hkoglPanelControl1->Invalidate();
	}
}

private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	
	TextureSize->Value = 50;
	TextureAngle->Value = 50;
	TextureX->Value = 50;
	TextureY->Value = 50;

	if (comboBox1->SelectedIndex)
	{
		TextureSize->Value = 10;
		label1->Text = "S"; label2->Text = "A"; label3->Text = "X"; label4->Text = "Y";

		currentTexture = TexIDs[comboBox1->SelectedIndex-1];
		SetTexture();		
	}
	else
	{
		currentTexture = 0;

		label1->Text = "R"; label2->Text = "G"; label3->Text = "B"; label4->Text = "A";				

		SetTexture();
	}
	
}

private: System::Void clear_Click(System::Object^  sender, System::EventArgs^  e) {
	if (mesh)
	{
		mesh->clearSelected();
		groupBox1->Enabled = FALSE;
	}
	hkoglPanelControl1->Invalidate();
}

private: System::Void TextureAdjust(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
	SetTexture();	
}

/*-----------------------------------------FileIO*/	

void saveFile(std::string dirname,std::string filename)
{	
	std::ifstream file;
	std::ofstream fileOut;

	file.open(filename.c_str(),std::ios::in|std::ios::binary);
	fileOut.open(dirname, std::ios::out | std::ios::binary);

	if (file.is_open())
	{
		fileOut << file.rdbuf();
		file.close();
		fileOut.close();
	}
	else
		std::cout <<"Can't find "<<filename<<std::endl;	

}

private: System::Void loadFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog->Filter = "files(*.txt) | *.txt";
	openFileDialog->ShowDialog();
}
private: System::Void openFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	std::string filename;
	MarshalString(openFileDialog->FileName, filename);
	std::size_t found = filename.find_last_of("/\\");
	std::string  path = filename.substr(0, found);
	std::string tmp;

	std::ifstream in;
	in.open(filename,std::ios::in|std::ios::binary);
	if (!in.is_open())return;

	/*---------------------------------loadModel*/
	if (mesh) delete mesh;
	mesh = new Tri_Mesh;
	in >> tmp;
	Model = path + "\\" + tmp;
	if (ReadFile(path+"\\"+tmp, mesh))
		std::cout << filename << std::endl;
	/*----------------------------------loadTexture*/
	for (auto id : TexIDs)
	{
		glDeleteTextures(1,&id);
	}
	TexSource.clear();
	TexIDs.clear();
	comboBox1->Items->Clear();
	comboBox1->Items->Add(gcnew String("Color"));
	int Texnum=0;
	in >> Texnum;
	for (int i = 0; i < Texnum; i++)
	{
		in >> tmp;
		filename = path +"\\"+tmp;

		char *cstr = new char[filename.length() + 1];
		strcpy(cstr, filename.c_str());
		char *tmp = strrchr(cstr, '\\');
		String^ net_s2 = gcnew String(tmp + 1);

		GLuint text = TextureApp::GenTexture(cstr);

		TexIDs.push_back(text);
		TexSource.push_back(filename);
		comboBox1->Items->Add(net_s2);

		delete[] cstr;
	}

	/*-------------------------------------SetModel*/
	mesh->input(in);

	hkoglPanelControl1->Invalidate();
}

private: System::Void saveFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	saveFileDialog1->Filter = "files(*.txt) | *.txt";
	saveFileDialog1->ShowDialog();
}
private: System::Void saveFileDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

	std::string filename;
	MarshalString(saveFileDialog1->FileName, filename);

	std::size_t found = filename.find_last_of("/\\");
	std::string  path = filename.substr(0, found);
	std::string  fileName = filename.substr(found+1);
	std::ofstream txt;
	txt.open(filename, std::ios::out | std::ios::binary);

	/*--------------------------------------------------------------Model*/
	if (Model != "")
	{
		std::size_t found = Model.find_last_of("/\\");
		std::string tmp = Model.substr(found + 1);
		std::string final = path + "\\" + tmp;

		if (SaveFile(final, mesh))
			std::cout << filename << std::endl;

		txt << tmp << std::endl;
	}
	/*--------------------------------------------------------------Texture*/
	txt << TexSource.size() << std::endl;
	for (auto name : TexSource)
	{
		std::size_t found = name.find_last_of("/\\");
		std::string tmp = name.substr(found+1);	
		std::string final = path +"\\"+tmp;
	
		saveFile(final,name);
		txt << tmp << std::endl;
	}
	/*--------------------------------------------------------------*/

	if (txt.is_open())
	{
		if (mesh)
		mesh->output(txt);
		txt.close();
	} 

}

private: System::Void loadTextureToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	openTextureDialog->Filter = "Image Files(*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|All files (*.*)|*.*";
	openTextureDialog->Multiselect = TRUE;
	openTextureDialog->ShowDialog();
}
private: System::Void openTextureDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < openTextureDialog->FileNames->Length; i++)
	{
		std::string filename;
		MarshalString(openTextureDialog->FileNames[i], filename);
		std::cout << filename << std::endl;

		char *cstr = new char[filename.length() + 1];
		strcpy(cstr, filename.c_str());
		char *tmp = strrchr(cstr, '\\');
		String^ net_s2 = gcnew String(tmp + 1);

		GLuint text = TextureApp::GenTexture(cstr);

		TexIDs.push_back(text);
		TexSource.push_back(filename);
		comboBox1->Items->Add(net_s2);
		
		delete[] cstr;
		hkoglPanelControl1->Invalidate();
	}
}

private: System::Void saveModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	saveModelDialog->Filter = "Model(*.obj)|*obj";
	saveModelDialog->ShowDialog();
}
private: System::Void saveModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	std::string filename;
	MarshalString(saveModelDialog->FileName, filename);

	if (SaveFile(filename, mesh))
		std::cout << filename << std::endl;
}

private: System::Void loadModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	openModelDialog->Filter = "Model(*.obj)|*obj";
	openModelDialog->Multiselect = false;
	openModelDialog->ShowDialog();
}
private: System::Void openModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	std::string filename;
	MarshalString(openModelDialog->FileName, filename);

	Model = filename;

	if (mesh != NULL)
		delete mesh;

	mesh = new Tri_Mesh;

	if (ReadFile(filename, mesh))
		std::cout << filename << std::endl;

	hkoglPanelControl1->Invalidate();
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {	

	if (xf2 == xform::trans(0.7, -0.7, -2)*xform::scale(0.5, 0.5, 1))
	{
		xf2 = xform::trans(0, 0, -2)*xform::scale(2,2,2);	
		showParameter = 1;
	}
	else
	{
		xf2 = xform::trans(0.7, -0.7, -2)*xform::scale(0.5, 0.5, 1);
		showParameter = 0;
	}	

	hkoglPanelControl1->Invalidate();
}

private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	SetTexture();
}
private: System::Void hkoglPanelControl1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	//std::cout <<e->KeyValue <<std::endl;
	if (e->KeyValue == 17)
	{
			DynamicMode = HOLD;
			hkoglPanelControl1->Cursor = System::Windows::Forms::Cursors::NoMove2D;
			SetTexture();
			hkoglPanelControl1->Invalidate();
	}
}
private: System::Void hkoglPanelControl1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	
	if (e->KeyValue == 17)
	{
		if (ViewToolStripMenuItem->Checked)
			DynamicMode = HOLD;
		else if (SelectToolStripMenuItem->Checked)
			DynamicMode = ADD;
		else if (unSeletModeToolStripMenuItem->Checked)
			DynamicMode = REMOVE;
		hkoglPanelControl1->Cursor = System::Windows::Forms::Cursors::Cross;

		hkoglPanelControl1->Invalidate();
			
	}
}



private: System::Void reverseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (mesh)
	{
		mesh->ReverseSelected();

		if (mesh->selectedFaceCount)
			groupBox1->Enabled = TRUE;
		else
			groupBox1->Enabled = FALSE;


		hkoglPanelControl1->Invalidate();
	}
}
private: System::Void clearToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (mesh)
	{
		mesh->clearSelected();
		groupBox1->Enabled = FALSE;
	}
	hkoglPanelControl1->Invalidate();
}
};
}
