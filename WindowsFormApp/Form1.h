#include <iostream>
#include <fstream>
#include <stdio.h>
#include "windows.h"
#include "math.h"
#include <algorithm>

///////////////////////////
//OpenCv
///////////////////////////////
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv/cv.h>


#include "MeanShift\MeanShift.h"

#include "ColorProcessing\ColorDifference.h"

#include "ArrayHelperr\ArrayHelperr.h"

#pragma once

namespace WindowsFormApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
    using namespace System::Text;


	/**************************************************/

	#pragma pack(push)
	#pragma pack(1)
	// Заголовок файла
	struct bmpFILEHEADER
	{
		unsigned char	bfType[2]; //(смещение  0, длина 2) Символы BM
		//WORD	bfType;			   //(смещение  0, длина 2) Символы BM
		DWORD	bfSize;			   //(Смещение  2, длина 4) Размер файла в байтах
		WORD	bfReserved1;	   //(Смещение  6, длина 2) Зарезервированы и должны содержать ноль
		WORD	bfReserved2;	   //(Смещение  8, длина 2) Зарезервированы и должны содержать ноль
		DWORD	bfOffBits;		   //(Смещение 10, длина 4) Смещение, с которого начинается само изображение(растр) 
	};
	#pragma pack(pop)

	// Заголовок Bitmap
	struct bmpINFOHEADER
	{
		DWORD biSize;			//(смещение  14, длина 4) Размер заголовка BITMAP (в байтах)
		LONG biWidth;			//(смещение  18, длина 4) Ширина изображения в пикселях
		LONG biHeight;			//(смещение  22, длина 4) Высота изображения в пикселях
		WORD biPlanes;			//(смещение  26, длина 2) Число плоскостей
		WORD biBitCount;		//(смещение  28, длина 2) Бит/пиксел: 1, 4, 8 или 24
		DWORD biCompression;	//(смещение  30, длина 4) Тип сжатия(0 - несжатое изображение), способ хранения
		DWORD biSizeImage;		//(смещение  34, длина 4) 0 или размер сжатого изображения в байтах
		LONG biXPelsPerMeter;	//(смещение  38, длина 4) Горизонтальное разрешение, пиксел/м
		LONG biYPelsPerMeter;	//(смещение  42, длина 4) Вертикальное разрешение, пиксел/м
		DWORD biClrUsed;		//(смещение  46, длина 4) Количество используемых цветов
		DWORD biClrImportant;	//(смещение  50, длина 4) Количество "важных" цветов.Количество ячеек от начала таблицы цветов до последней используемой (включая её саму)
	};

	//заголовки структур bmp
	bmpFILEHEADER hdBMP;
	bmpINFOHEADER InfoHeader;
	
	bool OPEN=false;//указывает бьл ли открыт файл
	int size=0;//размер массива с пикселями
	unsigned char *buffer = nullptr;//одномерный массив с пикселями
	unsigned char *bufferBackup = nullptr;
	unsigned char *shadowMask = nullptr;
	char* myPath_char="";//путь к файлу
	char *char_pathCopyBMP = "copyBMP.bmp";
	
	double compr_coef=1.0;
	unsigned char marker='@';
	
	int size_palette=0;
	unsigned char* palette=nullptr;//палитра
	
	#define BI_RLE_NO_MARKER 10;//сжатие без маркера
	#define BI_RLE_MARKER 11;//сжатие с маркером
	/**************************************************/

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1open;
	protected: 

	private: System::Windows::Forms::Button^  button1open;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;



	protected: 


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		/*my variables*/
		Stream^ myStream;
		String^ myPath;
		
		/**/

	private: System::Windows::Forms::TextBox^  textBox2info;
	private: System::Windows::Forms::Button^  button2save;
	private: System::Windows::Forms::Button^  button6Close;
	private: System::Windows::Forms::Button^  button7colorCorrection;
	private: System::Windows::Forms::TextBox^  textBoxRed;
	private: System::Windows::Forms::TextBox^  textBoxGreen;
	private: System::Windows::Forms::TextBox^  textBoxBlue;
	private: System::Windows::Forms::TextBox^  textBoxRGB;
	private: System::Windows::Forms::Button^  buttonRestoreImage;
	private: System::Windows::Forms::Label^  labelRed;
	private: System::Windows::Forms::Label^  labelGreen;
	private: System::Windows::Forms::Label^  labelBlue;
	private: System::Windows::Forms::Label^  labelRGB;
	private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::PictureBox^  pictureBox2;
private: System::Windows::Forms::Button^  buttonToYCbCr;
private: System::Windows::Forms::CheckBox^  checkBoxConvertBack;
private: System::Windows::Forms::PictureBox^  pictureBox3;
private: System::Windows::Forms::CheckBox^  checkBox1Remove;
private: System::Windows::Forms::CheckBox^  checkBoxCluster;
private: System::Windows::Forms::CheckBox^  checkBoxClusterVisual;
private: System::Windows::Forms::Button^  buttonAdditive;
private: System::Windows::Forms::Button^  buttonBasicLightModel;
private: System::Windows::Forms::Button^  buttonAdvancedLightModel;
private: System::Windows::Forms::Button^  buttonYCbCr;
private: System::Windows::Forms::Button^  buttonShadow1;
private: System::Windows::Forms::Button^  button1Shadow2Lab;
private: System::Windows::Forms::Button^  button11RemveLab;

private: System::Windows::Forms::Button^  button1Shadow4Math;
private: System::Windows::Forms::Button^  buttonShadow0YCbCr;
private: System::Windows::Forms::Button^  buttonHandleEdges;
private: System::Windows::Forms::Button^  buttonTestMEANSHIFT;

private: System::Windows::Forms::Button^  buttonBasicLightModelLAB;
private: System::Windows::Forms::TextBox^  textBoxGrayAvg;
private: System::Windows::Forms::TextBox^  textBoxGrayDev;

private: System::Windows::Forms::TextBox^  textBoxShadowDetectionThreshold;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Button^  buttonRemoveUsingConstant;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::TextBox^  textBoxIntensityAdd;
private: System::Windows::Forms::Button^  buttonIntensityAdd;
private: System::Windows::Forms::RadioButton^  radioButtonIntensityAdd;
private: System::Windows::Forms::RadioButton^  radioButtonIntensityMul;
private: System::Windows::Forms::TextBox^  textBoxIntensityMul;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBoxMSSColorRadius;

	private: System::Windows::Forms::TextBox^  textBoxMSSSpatialRadius;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::TextBox^  textBoxMSSMinRegionSize;
private: System::Windows::Forms::Button^  buttonMSSApply;
private: System::Windows::Forms::Button^  buttonMSSDefault;



	private: System::Windows::Forms::Button^  button3exit;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1open = (gcnew System::Windows::Forms::TextBox());
			this->button1open = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox2info = (gcnew System::Windows::Forms::TextBox());
			this->button2save = (gcnew System::Windows::Forms::Button());
			this->button3exit = (gcnew System::Windows::Forms::Button());
			this->button6Close = (gcnew System::Windows::Forms::Button());
			this->button7colorCorrection = (gcnew System::Windows::Forms::Button());
			this->textBoxRed = (gcnew System::Windows::Forms::TextBox());
			this->textBoxGreen = (gcnew System::Windows::Forms::TextBox());
			this->textBoxBlue = (gcnew System::Windows::Forms::TextBox());
			this->textBoxRGB = (gcnew System::Windows::Forms::TextBox());
			this->buttonRestoreImage = (gcnew System::Windows::Forms::Button());
			this->labelRed = (gcnew System::Windows::Forms::Label());
			this->labelGreen = (gcnew System::Windows::Forms::Label());
			this->labelBlue = (gcnew System::Windows::Forms::Label());
			this->labelRGB = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->buttonToYCbCr = (gcnew System::Windows::Forms::Button());
			this->checkBoxConvertBack = (gcnew System::Windows::Forms::CheckBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->checkBox1Remove = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxCluster = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxClusterVisual = (gcnew System::Windows::Forms::CheckBox());
			this->buttonAdditive = (gcnew System::Windows::Forms::Button());
			this->buttonBasicLightModel = (gcnew System::Windows::Forms::Button());
			this->buttonAdvancedLightModel = (gcnew System::Windows::Forms::Button());
			this->buttonYCbCr = (gcnew System::Windows::Forms::Button());
			this->buttonShadow1 = (gcnew System::Windows::Forms::Button());
			this->button1Shadow2Lab = (gcnew System::Windows::Forms::Button());
			this->button11RemveLab = (gcnew System::Windows::Forms::Button());
			this->button1Shadow4Math = (gcnew System::Windows::Forms::Button());
			this->buttonShadow0YCbCr = (gcnew System::Windows::Forms::Button());
			this->buttonHandleEdges = (gcnew System::Windows::Forms::Button());
			this->buttonTestMEANSHIFT = (gcnew System::Windows::Forms::Button());
			this->buttonBasicLightModelLAB = (gcnew System::Windows::Forms::Button());
			this->textBoxGrayAvg = (gcnew System::Windows::Forms::TextBox());
			this->textBoxGrayDev = (gcnew System::Windows::Forms::TextBox());
			this->textBoxShadowDetectionThreshold = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->buttonRemoveUsingConstant = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxIntensityAdd = (gcnew System::Windows::Forms::TextBox());
			this->buttonIntensityAdd = (gcnew System::Windows::Forms::Button());
			this->radioButtonIntensityAdd = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonIntensityMul = (gcnew System::Windows::Forms::RadioButton());
			this->textBoxIntensityMul = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxMSSColorRadius = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMSSSpatialRadius = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBoxMSSMinRegionSize = (gcnew System::Windows::Forms::TextBox());
			this->buttonMSSApply = (gcnew System::Windows::Forms::Button());
			this->buttonMSSDefault = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1open
			// 
			this->textBox1open->Enabled = false;
			this->textBox1open->Location = System::Drawing::Point(8, 693);
			this->textBox1open->Multiline = true;
			this->textBox1open->Name = L"textBox1open";
			this->textBox1open->Size = System::Drawing::Size(623, 16);
			this->textBox1open->TabIndex = 0;
			// 
			// button1open
			// 
			this->button1open->Location = System::Drawing::Point(8, 579);
			this->button1open->Name = L"button1open";
			this->button1open->Size = System::Drawing::Size(193, 22);
			this->button1open->TabIndex = 1;
			this->button1open->Text = L"Open";
			this->button1open->UseVisualStyleBackColor = true;
			this->button1open->Click += gcnew System::EventHandler(this, &Form1::button1open_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(1165, 1);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(460, 400);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// textBox2info
			// 
			this->textBox2info->Location = System::Drawing::Point(8, 1);
			this->textBox2info->Multiline = true;
			this->textBox2info->Name = L"textBox2info";
			this->textBox2info->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2info->Size = System::Drawing::Size(196, 147);
			this->textBox2info->TabIndex = 3;
			// 
			// button2save
			// 
			this->button2save->Location = System::Drawing::Point(8, 607);
			this->button2save->Name = L"button2save";
			this->button2save->Size = System::Drawing::Size(193, 22);
			this->button2save->TabIndex = 5;
			this->button2save->Text = L"Save";
			this->button2save->UseVisualStyleBackColor = true;
			this->button2save->Click += gcnew System::EventHandler(this, &Form1::button2save_Click);
			// 
			// button3exit
			// 
			this->button3exit->Location = System::Drawing::Point(8, 663);
			this->button3exit->Name = L"button3exit";
			this->button3exit->Size = System::Drawing::Size(193, 22);
			this->button3exit->TabIndex = 6;
			this->button3exit->Text = L"Exit";
			this->button3exit->UseVisualStyleBackColor = true;
			this->button3exit->Click += gcnew System::EventHandler(this, &Form1::button3exit_Click);
			// 
			// button6Close
			// 
			this->button6Close->Location = System::Drawing::Point(8, 635);
			this->button6Close->Name = L"button6Close";
			this->button6Close->Size = System::Drawing::Size(193, 22);
			this->button6Close->TabIndex = 15;
			this->button6Close->Text = L"Close";
			this->button6Close->UseVisualStyleBackColor = true;
			this->button6Close->Click += gcnew System::EventHandler(this, &Form1::button6Close_Click);
			// 
			// button7colorCorrection
			// 
			this->button7colorCorrection->Enabled = false;
			this->button7colorCorrection->Location = System::Drawing::Point(108, 246);
			this->button7colorCorrection->Name = L"button7colorCorrection";
			this->button7colorCorrection->Size = System::Drawing::Size(98, 22);
			this->button7colorCorrection->TabIndex = 16;
			this->button7colorCorrection->Text = L"Color correction";
			this->button7colorCorrection->UseVisualStyleBackColor = true;
			this->button7colorCorrection->Click += gcnew System::EventHandler(this, &Form1::button7colorCorrection_Click);
			// 
			// textBoxRed
			// 
			this->textBoxRed->Location = System::Drawing::Point(10, 220);
			this->textBoxRed->Multiline = true;
			this->textBoxRed->Name = L"textBoxRed";
			this->textBoxRed->Size = System::Drawing::Size(44, 20);
			this->textBoxRed->TabIndex = 17;
			this->textBoxRed->Text = L"0";
			// 
			// textBoxGreen
			// 
			this->textBoxGreen->Location = System::Drawing::Point(59, 220);
			this->textBoxGreen->Multiline = true;
			this->textBoxGreen->Name = L"textBoxGreen";
			this->textBoxGreen->Size = System::Drawing::Size(44, 20);
			this->textBoxGreen->TabIndex = 18;
			this->textBoxGreen->Text = L"0";
			// 
			// textBoxBlue
			// 
			this->textBoxBlue->Location = System::Drawing::Point(108, 220);
			this->textBoxBlue->Multiline = true;
			this->textBoxBlue->Name = L"textBoxBlue";
			this->textBoxBlue->Size = System::Drawing::Size(44, 20);
			this->textBoxBlue->TabIndex = 19;
			this->textBoxBlue->Text = L"0";
			// 
			// textBoxRGB
			// 
			this->textBoxRGB->Location = System::Drawing::Point(157, 220);
			this->textBoxRGB->Multiline = true;
			this->textBoxRGB->Name = L"textBoxRGB";
			this->textBoxRGB->Size = System::Drawing::Size(49, 20);
			this->textBoxRGB->TabIndex = 20;
			this->textBoxRGB->Text = L"0";
			// 
			// buttonRestoreImage
			// 
			this->buttonRestoreImage->Enabled = false;
			this->buttonRestoreImage->Location = System::Drawing::Point(8, 551);
			this->buttonRestoreImage->Name = L"buttonRestoreImage";
			this->buttonRestoreImage->Size = System::Drawing::Size(193, 22);
			this->buttonRestoreImage->TabIndex = 21;
			this->buttonRestoreImage->Text = L"Restore image";
			this->buttonRestoreImage->UseVisualStyleBackColor = true;
			this->buttonRestoreImage->Click += gcnew System::EventHandler(this, &Form1::buttonRestoreImage_Click);
			// 
			// labelRed
			// 
			this->labelRed->AutoSize = true;
			this->labelRed->Location = System::Drawing::Point(7, 204);
			this->labelRed->Name = L"labelRed";
			this->labelRed->Size = System::Drawing::Size(27, 13);
			this->labelRed->TabIndex = 22;
			this->labelRed->Text = L"Red";
			// 
			// labelGreen
			// 
			this->labelGreen->AutoSize = true;
			this->labelGreen->Location = System::Drawing::Point(56, 204);
			this->labelGreen->Name = L"labelGreen";
			this->labelGreen->Size = System::Drawing::Size(36, 13);
			this->labelGreen->TabIndex = 23;
			this->labelGreen->Text = L"Green";
			// 
			// labelBlue
			// 
			this->labelBlue->AutoSize = true;
			this->labelBlue->Location = System::Drawing::Point(108, 204);
			this->labelBlue->Name = L"labelBlue";
			this->labelBlue->Size = System::Drawing::Size(28, 13);
			this->labelBlue->TabIndex = 24;
			this->labelBlue->Text = L"Blue";
			// 
			// labelRGB
			// 
			this->labelRGB->AutoSize = true;
			this->labelRGB->Location = System::Drawing::Point(154, 204);
			this->labelRGB->Name = L"labelRGB";
			this->labelRGB->Size = System::Drawing::Size(30, 13);
			this->labelRGB->TabIndex = 25;
			this->labelRGB->Text = L"RGB";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(10, 246);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(95, 22);
			this->button1->TabIndex = 26;
			this->button1->Text = L"Reset";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(233, 1);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(460, 400);
			this->pictureBox2->TabIndex = 52;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &Form1::pictureBox2_Click);
			// 
			// buttonToYCbCr
			// 
			this->buttonToYCbCr->Location = System::Drawing::Point(237, 590);
			this->buttonToYCbCr->Name = L"buttonToYCbCr";
			this->buttonToYCbCr->Size = System::Drawing::Size(65, 22);
			this->buttonToYCbCr->TabIndex = 59;
			this->buttonToYCbCr->Text = L"To YCbCr";
			this->buttonToYCbCr->UseVisualStyleBackColor = true;
			this->buttonToYCbCr->Click += gcnew System::EventHandler(this, &Form1::buttonToYCbCr_Click);
			// 
			// checkBoxConvertBack
			// 
			this->checkBoxConvertBack->AutoSize = true;
			this->checkBoxConvertBack->Checked = true;
			this->checkBoxConvertBack->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxConvertBack->Location = System::Drawing::Point(308, 594);
			this->checkBoxConvertBack->Name = L"checkBoxConvertBack";
			this->checkBoxConvertBack->Size = System::Drawing::Size(61, 17);
			this->checkBoxConvertBack->TabIndex = 60;
			this->checkBoxConvertBack->Text = L"to RGB";
			this->checkBoxConvertBack->UseVisualStyleBackColor = true;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(699, 1);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(460, 400);
			this->pictureBox3->TabIndex = 61;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &Form1::pictureBox3_Click);
			// 
			// checkBox1Remove
			// 
			this->checkBox1Remove->AutoSize = true;
			this->checkBox1Remove->Checked = true;
			this->checkBox1Remove->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1Remove->Location = System::Drawing::Point(307, 571);
			this->checkBox1Remove->Name = L"checkBox1Remove";
			this->checkBox1Remove->Size = System::Drawing::Size(61, 17);
			this->checkBox1Remove->TabIndex = 62;
			this->checkBox1Remove->Text = L"remove";
			this->checkBox1Remove->UseVisualStyleBackColor = true;
			// 
			// checkBoxCluster
			// 
			this->checkBoxCluster->AutoSize = true;
			this->checkBoxCluster->Checked = true;
			this->checkBoxCluster->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxCluster->Location = System::Drawing::Point(307, 617);
			this->checkBoxCluster->Name = L"checkBoxCluster";
			this->checkBoxCluster->Size = System::Drawing::Size(58, 17);
			this->checkBoxCluster->TabIndex = 63;
			this->checkBoxCluster->Text = L"Cluster";
			this->checkBoxCluster->UseVisualStyleBackColor = true;
			// 
			// checkBoxClusterVisual
			// 
			this->checkBoxClusterVisual->AutoSize = true;
			this->checkBoxClusterVisual->Location = System::Drawing::Point(307, 640);
			this->checkBoxClusterVisual->Name = L"checkBoxClusterVisual";
			this->checkBoxClusterVisual->Size = System::Drawing::Size(88, 17);
			this->checkBoxClusterVisual->TabIndex = 64;
			this->checkBoxClusterVisual->Text = L"Cluster visual";
			this->checkBoxClusterVisual->UseVisualStyleBackColor = true;
			// 
			// buttonAdditive
			// 
			this->buttonAdditive->Location = System::Drawing::Point(992, 570);
			this->buttonAdditive->Name = L"buttonAdditive";
			this->buttonAdditive->Size = System::Drawing::Size(109, 39);
			this->buttonAdditive->TabIndex = 65;
			this->buttonAdditive->Text = L"Additive shadow removal ";
			this->buttonAdditive->UseVisualStyleBackColor = true;
			this->buttonAdditive->Click += gcnew System::EventHandler(this, &Form1::buttonAdditive_Click);
			// 
			// buttonBasicLightModel
			// 
			this->buttonBasicLightModel->Location = System::Drawing::Point(1107, 569);
			this->buttonBasicLightModel->Name = L"buttonBasicLightModel";
			this->buttonBasicLightModel->Size = System::Drawing::Size(109, 40);
			this->buttonBasicLightModel->TabIndex = 66;
			this->buttonBasicLightModel->Text = L"Basic Light Model";
			this->buttonBasicLightModel->UseVisualStyleBackColor = true;
			this->buttonBasicLightModel->Click += gcnew System::EventHandler(this, &Form1::buttonBasicLightModel_Click);
			// 
			// buttonAdvancedLightModel
			// 
			this->buttonAdvancedLightModel->Location = System::Drawing::Point(1222, 569);
			this->buttonAdvancedLightModel->Name = L"buttonAdvancedLightModel";
			this->buttonAdvancedLightModel->Size = System::Drawing::Size(75, 40);
			this->buttonAdvancedLightModel->TabIndex = 67;
			this->buttonAdvancedLightModel->Text = L"Advanced Light Model";
			this->buttonAdvancedLightModel->UseVisualStyleBackColor = true;
			this->buttonAdvancedLightModel->Click += gcnew System::EventHandler(this, &Form1::buttonAdvancedLightModel_Click);
			// 
			// buttonYCbCr
			// 
			this->buttonYCbCr->Location = System::Drawing::Point(1303, 569);
			this->buttonYCbCr->Name = L"buttonYCbCr";
			this->buttonYCbCr->Size = System::Drawing::Size(75, 40);
			this->buttonYCbCr->TabIndex = 68;
			this->buttonYCbCr->Text = L"YCbCr";
			this->buttonYCbCr->UseVisualStyleBackColor = true;
			this->buttonYCbCr->Click += gcnew System::EventHandler(this, &Form1::buttonYCbCr_Click);
			// 
			// buttonShadow1
			// 
			this->buttonShadow1->Location = System::Drawing::Point(992, 621);
			this->buttonShadow1->Name = L"buttonShadow1";
			this->buttonShadow1->Size = System::Drawing::Size(109, 25);
			this->buttonShadow1->TabIndex = 69;
			this->buttonShadow1->Text = L"Shadow1 HSV";
			this->buttonShadow1->UseVisualStyleBackColor = true;
			this->buttonShadow1->Click += gcnew System::EventHandler(this, &Form1::buttonShadow1_Click);
			// 
			// button1Shadow2Lab
			// 
			this->button1Shadow2Lab->Location = System::Drawing::Point(1107, 621);
			this->button1Shadow2Lab->Name = L"button1Shadow2Lab";
			this->button1Shadow2Lab->Size = System::Drawing::Size(109, 25);
			this->button1Shadow2Lab->TabIndex = 70;
			this->button1Shadow2Lab->Text = L"Shadow1 LAB";
			this->button1Shadow2Lab->UseVisualStyleBackColor = true;
			this->button1Shadow2Lab->Click += gcnew System::EventHandler(this, &Form1::button1Shadow2Lab_Click);
			// 
			// button11RemveLab
			// 
			this->button11RemveLab->Location = System::Drawing::Point(1107, 649);
			this->button11RemveLab->Name = L"button11RemveLab";
			this->button11RemveLab->Size = System::Drawing::Size(109, 25);
			this->button11RemveLab->TabIndex = 71;
			this->button11RemveLab->Text = L"Remove LAB";
			this->button11RemveLab->UseVisualStyleBackColor = true;
			this->button11RemveLab->Click += gcnew System::EventHandler(this, &Form1::button11RemveLab_Click);
			// 
			// button1Shadow4Math
			// 
			this->button1Shadow4Math->Location = System::Drawing::Point(1337, 621);
			this->button1Shadow4Math->Name = L"button1Shadow4Math";
			this->button1Shadow4Math->Size = System::Drawing::Size(109, 25);
			this->button1Shadow4Math->TabIndex = 73;
			this->button1Shadow4Math->Text = L"Shadow4 Math";
			this->button1Shadow4Math->UseVisualStyleBackColor = true;
			this->button1Shadow4Math->Click += gcnew System::EventHandler(this, &Form1::button1Shadow4Math_Click);
			// 
			// buttonShadow0YCbCr
			// 
			this->buttonShadow0YCbCr->Location = System::Drawing::Point(877, 621);
			this->buttonShadow0YCbCr->Name = L"buttonShadow0YCbCr";
			this->buttonShadow0YCbCr->Size = System::Drawing::Size(109, 25);
			this->buttonShadow0YCbCr->TabIndex = 74;
			this->buttonShadow0YCbCr->Text = L"Shadow0 YCbCr";
			this->buttonShadow0YCbCr->UseVisualStyleBackColor = true;
			this->buttonShadow0YCbCr->Click += gcnew System::EventHandler(this, &Form1::buttonShadow0YCbCr_Click);
			// 
			// buttonHandleEdges
			// 
			this->buttonHandleEdges->Location = System::Drawing::Point(1107, 680);
			this->buttonHandleEdges->Name = L"buttonHandleEdges";
			this->buttonHandleEdges->Size = System::Drawing::Size(109, 25);
			this->buttonHandleEdges->TabIndex = 75;
			this->buttonHandleEdges->Text = L"Edges Correction";
			this->buttonHandleEdges->UseVisualStyleBackColor = true;
			this->buttonHandleEdges->Click += gcnew System::EventHandler(this, &Form1::buttonHandleEdges_Click);
			// 
			// buttonTestMEANSHIFT
			// 
			this->buttonTestMEANSHIFT->Location = System::Drawing::Point(417, 604);
			this->buttonTestMEANSHIFT->Name = L"buttonTestMEANSHIFT";
			this->buttonTestMEANSHIFT->Size = System::Drawing::Size(109, 25);
			this->buttonTestMEANSHIFT->TabIndex = 76;
			this->buttonTestMEANSHIFT->Text = L"Test MEAN SHIFT";
			this->buttonTestMEANSHIFT->UseVisualStyleBackColor = true;
			this->buttonTestMEANSHIFT->Click += gcnew System::EventHandler(this, &Form1::buttonTestMEANSHIFT_Click);
			// 
			// buttonBasicLightModelLAB
			// 
			this->buttonBasicLightModelLAB->Location = System::Drawing::Point(1452, 684);
			this->buttonBasicLightModelLAB->Name = L"buttonBasicLightModelLAB";
			this->buttonBasicLightModelLAB->Size = System::Drawing::Size(136, 25);
			this->buttonBasicLightModelLAB->TabIndex = 78;
			this->buttonBasicLightModelLAB->Text = L"Basic Light Model LAB";
			this->buttonBasicLightModelLAB->UseVisualStyleBackColor = true;
			this->buttonBasicLightModelLAB->Click += gcnew System::EventHandler(this, &Form1::buttonBasicLightModelLAB_Click);
			// 
			// textBoxGrayAvg
			// 
			this->textBoxGrayAvg->Enabled = false;
			this->textBoxGrayAvg->Location = System::Drawing::Point(1451, 622);
			this->textBoxGrayAvg->Multiline = true;
			this->textBoxGrayAvg->Name = L"textBoxGrayAvg";
			this->textBoxGrayAvg->Size = System::Drawing::Size(40, 20);
			this->textBoxGrayAvg->TabIndex = 79;
			this->textBoxGrayAvg->Text = L"0";
			// 
			// textBoxGrayDev
			// 
			this->textBoxGrayDev->Enabled = false;
			this->textBoxGrayDev->Location = System::Drawing::Point(1497, 622);
			this->textBoxGrayDev->Multiline = true;
			this->textBoxGrayDev->Name = L"textBoxGrayDev";
			this->textBoxGrayDev->Size = System::Drawing::Size(40, 20);
			this->textBoxGrayDev->TabIndex = 80;
			this->textBoxGrayDev->Text = L"0";
			// 
			// textBoxShadowDetectionThreshold
			// 
			this->textBoxShadowDetectionThreshold->Location = System::Drawing::Point(1543, 623);
			this->textBoxShadowDetectionThreshold->Multiline = true;
			this->textBoxShadowDetectionThreshold->Name = L"textBoxShadowDetectionThreshold";
			this->textBoxShadowDetectionThreshold->Size = System::Drawing::Size(40, 20);
			this->textBoxShadowDetectionThreshold->TabIndex = 82;
			this->textBoxShadowDetectionThreshold->Text = L"0";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(1540, 607);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(43, 13);
			this->label5->TabIndex = 83;
			this->label5->Text = L"Thresh:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(1449, 606);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(29, 13);
			this->label6->TabIndex = 84;
			this->label6->Text = L"Avg:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(1494, 607);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(44, 13);
			this->label7->TabIndex = 85;
			this->label7->Text = L"Stddev:";
			// 
			// buttonRemoveUsingConstant
			// 
			this->buttonRemoveUsingConstant->Location = System::Drawing::Point(417, 576);
			this->buttonRemoveUsingConstant->Name = L"buttonRemoveUsingConstant";
			this->buttonRemoveUsingConstant->Size = System::Drawing::Size(142, 25);
			this->buttonRemoveUsingConstant->TabIndex = 86;
			this->buttonRemoveUsingConstant->Text = L"Remove Using Constant";
			this->buttonRemoveUsingConstant->UseVisualStyleBackColor = true;
			this->buttonRemoveUsingConstant->Click += gcnew System::EventHandler(this, &Form1::buttonRemoveUsingConstant_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 276);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 13);
			this->label1->TabIndex = 88;
			this->label1->Text = L"Intensity";
			// 
			// textBoxIntensityAdd
			// 
			this->textBoxIntensityAdd->Location = System::Drawing::Point(12, 292);
			this->textBoxIntensityAdd->Multiline = true;
			this->textBoxIntensityAdd->Name = L"textBoxIntensityAdd";
			this->textBoxIntensityAdd->Size = System::Drawing::Size(44, 20);
			this->textBoxIntensityAdd->TabIndex = 87;
			this->textBoxIntensityAdd->Text = L"0";
			// 
			// buttonIntensityAdd
			// 
			this->buttonIntensityAdd->Location = System::Drawing::Point(106, 304);
			this->buttonIntensityAdd->Name = L"buttonIntensityAdd";
			this->buttonIntensityAdd->Size = System::Drawing::Size(98, 22);
			this->buttonIntensityAdd->TabIndex = 89;
			this->buttonIntensityAdd->Text = L"Apply";
			this->buttonIntensityAdd->UseVisualStyleBackColor = true;
			this->buttonIntensityAdd->Click += gcnew System::EventHandler(this, &Form1::buttonIntensityAdd_Click);
			// 
			// radioButtonIntensityAdd
			// 
			this->radioButtonIntensityAdd->AutoSize = true;
			this->radioButtonIntensityAdd->Location = System::Drawing::Point(62, 295);
			this->radioButtonIntensityAdd->Name = L"radioButtonIntensityAdd";
			this->radioButtonIntensityAdd->Size = System::Drawing::Size(44, 17);
			this->radioButtonIntensityAdd->TabIndex = 90;
			this->radioButtonIntensityAdd->TabStop = true;
			this->radioButtonIntensityAdd->Text = L"Add";
			this->radioButtonIntensityAdd->UseVisualStyleBackColor = true;
			// 
			// radioButtonIntensityMul
			// 
			this->radioButtonIntensityMul->AutoSize = true;
			this->radioButtonIntensityMul->Location = System::Drawing::Point(62, 318);
			this->radioButtonIntensityMul->Name = L"radioButtonIntensityMul";
			this->radioButtonIntensityMul->Size = System::Drawing::Size(42, 17);
			this->radioButtonIntensityMul->TabIndex = 91;
			this->radioButtonIntensityMul->TabStop = true;
			this->radioButtonIntensityMul->Text = L"Mul";
			this->radioButtonIntensityMul->UseVisualStyleBackColor = true;
			// 
			// textBoxIntensityMul
			// 
			this->textBoxIntensityMul->Location = System::Drawing::Point(12, 318);
			this->textBoxIntensityMul->Multiline = true;
			this->textBoxIntensityMul->Name = L"textBoxIntensityMul";
			this->textBoxIntensityMul->Size = System::Drawing::Size(44, 20);
			this->textBoxIntensityMul->TabIndex = 92;
			this->textBoxIntensityMul->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(696, 613);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(67, 13);
			this->label2->TabIndex = 96;
			this->label2->Text = L"Color Radius";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(696, 590);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(75, 13);
			this->label3->TabIndex = 95;
			this->label3->Text = L"Spatial Radius";
			// 
			// textBoxMSSColorRadius
			// 
			this->textBoxMSSColorRadius->Location = System::Drawing::Point(777, 613);
			this->textBoxMSSColorRadius->Multiline = true;
			this->textBoxMSSColorRadius->Name = L"textBoxMSSColorRadius";
			this->textBoxMSSColorRadius->Size = System::Drawing::Size(63, 20);
			this->textBoxMSSColorRadius->TabIndex = 94;
			this->textBoxMSSColorRadius->Text = L"0";
			// 
			// textBoxMSSSpatialRadius
			// 
			this->textBoxMSSSpatialRadius->Location = System::Drawing::Point(777, 587);
			this->textBoxMSSSpatialRadius->Multiline = true;
			this->textBoxMSSSpatialRadius->Name = L"textBoxMSSSpatialRadius";
			this->textBoxMSSSpatialRadius->Size = System::Drawing::Size(63, 20);
			this->textBoxMSSSpatialRadius->TabIndex = 93;
			this->textBoxMSSSpatialRadius->Text = L"0";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(696, 561);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(162, 13);
			this->label4->TabIndex = 97;
			this->label4->Text = L"Mean shift segmentation params:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(696, 639);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(77, 13);
			this->label8->TabIndex = 99;
			this->label8->Text = L"Min region size";
			// 
			// textBoxMSSMinRegionSize
			// 
			this->textBoxMSSMinRegionSize->Location = System::Drawing::Point(777, 639);
			this->textBoxMSSMinRegionSize->Multiline = true;
			this->textBoxMSSMinRegionSize->Name = L"textBoxMSSMinRegionSize";
			this->textBoxMSSMinRegionSize->Size = System::Drawing::Size(63, 20);
			this->textBoxMSSMinRegionSize->TabIndex = 98;
			this->textBoxMSSMinRegionSize->Text = L"0";
			// 
			// buttonMSSApply
			// 
			this->buttonMSSApply->Location = System::Drawing::Point(777, 662);
			this->buttonMSSApply->Name = L"buttonMSSApply";
			this->buttonMSSApply->Size = System::Drawing::Size(63, 23);
			this->buttonMSSApply->TabIndex = 100;
			this->buttonMSSApply->Text = L"Apply";
			this->buttonMSSApply->UseVisualStyleBackColor = true;
			this->buttonMSSApply->Click += gcnew System::EventHandler(this, &Form1::buttonMSSApply_Click);
			// 
			// buttonMSSDefault
			// 
			this->buttonMSSDefault->Location = System::Drawing::Point(710, 662);
			this->buttonMSSDefault->Name = L"buttonMSSDefault";
			this->buttonMSSDefault->Size = System::Drawing::Size(63, 23);
			this->buttonMSSDefault->TabIndex = 101;
			this->buttonMSSDefault->Text = L"Default";
			this->buttonMSSDefault->UseVisualStyleBackColor = true;
			this->buttonMSSDefault->Click += gcnew System::EventHandler(this, &Form1::buttonMSSDefault_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1637, 721);
			this->Controls->Add(this->buttonMSSDefault);
			this->Controls->Add(this->buttonMSSApply);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->textBoxMSSMinRegionSize);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBoxMSSColorRadius);
			this->Controls->Add(this->textBoxMSSSpatialRadius);
			this->Controls->Add(this->textBoxIntensityMul);
			this->Controls->Add(this->radioButtonIntensityMul);
			this->Controls->Add(this->radioButtonIntensityAdd);
			this->Controls->Add(this->buttonIntensityAdd);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBoxIntensityAdd);
			this->Controls->Add(this->buttonRemoveUsingConstant);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBoxShadowDetectionThreshold);
			this->Controls->Add(this->textBoxGrayDev);
			this->Controls->Add(this->textBoxGrayAvg);
			this->Controls->Add(this->buttonBasicLightModelLAB);
			this->Controls->Add(this->buttonTestMEANSHIFT);
			this->Controls->Add(this->buttonHandleEdges);
			this->Controls->Add(this->buttonShadow0YCbCr);
			this->Controls->Add(this->button1Shadow4Math);
			this->Controls->Add(this->button11RemveLab);
			this->Controls->Add(this->button1Shadow2Lab);
			this->Controls->Add(this->buttonShadow1);
			this->Controls->Add(this->buttonYCbCr);
			this->Controls->Add(this->buttonAdvancedLightModel);
			this->Controls->Add(this->buttonBasicLightModel);
			this->Controls->Add(this->buttonAdditive);
			this->Controls->Add(this->checkBoxClusterVisual);
			this->Controls->Add(this->checkBoxCluster);
			this->Controls->Add(this->checkBox1Remove);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->checkBoxConvertBack);
			this->Controls->Add(this->buttonToYCbCr);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->labelRGB);
			this->Controls->Add(this->labelBlue);
			this->Controls->Add(this->labelGreen);
			this->Controls->Add(this->labelRed);
			this->Controls->Add(this->buttonRestoreImage);
			this->Controls->Add(this->textBoxRGB);
			this->Controls->Add(this->textBoxBlue);
			this->Controls->Add(this->textBoxGreen);
			this->Controls->Add(this->textBoxRed);
			this->Controls->Add(this->button7colorCorrection);
			this->Controls->Add(this->button6Close);
			this->Controls->Add(this->button3exit);
			this->Controls->Add(this->button2save);
			this->Controls->Add(this->textBox2info);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1open);
			this->Controls->Add(this->textBox1open);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form1";
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResizeEnd += gcnew System::EventHandler(this, &Form1::Form1_ResizeEnd);
			this->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::Form1_Scroll);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	//Собственные ф-ции
	//START

			 //Окрыть bmp
	private: bool OpenBmp(bool OpenDialog)
			 {
				if(OpenDialog){
					OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
					openFileDialog1->InitialDirectory = "D:\Mail.ru.Disk\Study\Обробка зображень\Lab2";
					openFileDialog1->Filter = "bmp files|*.bmp";
					openFileDialog1->FilterIndex = 1;
					openFileDialog1->RestoreDirectory = true;
					
					System::Windows::Forms::DialogResult dialogRes= openFileDialog1->ShowDialog();

					if ( dialogRes == System::Windows::Forms::DialogResult::Cancel )
					{
						OPEN=OPEN;//OPEN=true;
						return false;
					}
					OPEN=false;
					if ( dialogRes != System::Windows::Forms::DialogResult::OK )
					{
						//MessageBox::Show("Dialog error!");
						return false;
					}
					if ( (myStream = openFileDialog1->OpenFile()) == nullptr )
					{
						MessageBox::Show("Stream error!");
						return false;
					}
				
					//получение полного пути к файлу
					myPath = openFileDialog1->FileName;
					textBox1open->Text=myPath;
					myStream->Close();
					delete openFileDialog1 ;
				}

				//Конвертация пути с System::String to char*
				using namespace System::Runtime::InteropServices;
				myPath_char = (char*)(void*)Marshal::StringToHGlobalAnsi(myPath);
						
				//Чтение файла
				FILE* f = fopen(myPath_char,"rb");
				if(!f){
					MessageBox::Show("File read error!");
					return false;
				}
				
				fread(&hdBMP,sizeof(hdBMP),1,f);//чтение заголовка BITMAPFILEHEADER. размер-14 байт

				//Проверка, что читаем bmp файл
				if( hdBMP.bfType[0]!='B' || hdBMP.bfType[1]!='M' ){
					MessageBox::Show("Required bmp format!");
					fclose(f);
					return false;
				}

				fread(&InfoHeader,sizeof(InfoHeader),1,f);//чтение заголовка BITMAPINFO. один из размеров-40 байт

				//Палитра
				size_palette = hdBMP.bfOffBits-( sizeof(hdBMP)+sizeof(InfoHeader) );
				int size_paletteCOPY = size_palette;
				delete palette;
				palette = new UCHAR[size_palette]; 

				fread(palette, size_palette, 1, f);//чтение палитры в массив

				fseek(f,hdBMP.bfOffBits,SEEK_SET);//переход на позицию, с кот. нач пиксельные данные

				size=InfoHeader.biSizeImage;//размер массива с пикселями
				delete buffer;//удаляем старый массив, если открываем новый файл
				delete bufferBackup;
				buffer = new UCHAR[size];//одномерный массив с пикселями
				bufferBackup = new UCHAR[size];//одномерный массив с пикселями(копия)

				fread(buffer, size, 1, f);//чтение пикселей в массив
				CopyArrayUCHAR(buffer, bufferBackup, size);//сохраняем копию массива с пикселями

				fclose(f);
				
				OPEN=true;//флаг, что открыт файл
		
				//Вывод информации о изображении
				textBox2info->Text=String::Format( "Размер файла в байтах: {0}\r\nШирина: {1}\r\nВысота: {2}\r\nКоличество бит на пиксель: {3}\r\nТип хранения(сжатия): {4}\r\nРазмер массива с пикселями: {5}\r\nСмещение, с которого начинается само изображение(растр): {6}\r\nКоэфициент сжатия: {7}",
													hdBMP.bfSize ,InfoHeader.biWidth, InfoHeader.biHeight,InfoHeader.biBitCount,InfoHeader.biCompression,InfoHeader.biSizeImage,hdBMP.bfOffBits,compr_coef);
			
				//convertToHalftone();
				//SaveBMP();

				saveCopyBMP();

				ShowBmp();//показать изображение если оно не сжато

				return true;
			 }

			 //Отобразить bmp
	private: void ShowBmp()
			 {
				pictureBox1->Refresh();
				pictureBox2->Refresh();
				if(InfoHeader.biCompression==0){
					//отображение изображения на экране
					Bitmap^ bmpOrig = gcnew Bitmap(myPath);
					Bitmap^ bmp = gcnew Bitmap(bmpOrig,pictureBox1->Width,pictureBox1->Height);
					Graphics^ g = pictureBox1->CreateGraphics();
					//pictureBox1->Width=bmpOrig->Width;
					//pictureBox1->Height=bmpOrig->Height;
					g->DrawImage(bmp, 1, 1);
					delete bmpOrig;
					delete bmp;
					delete g;

					ShowCopyBmp();
				}
				else{
					//MessageBox::Show("");
				}
			 }

	private: void ShowMaskBmp()
	{
//				 pictureBox1->Refresh();
//				 pictureBox2->Refresh();
				 pictureBox3->Refresh();
				 if (InfoHeader.biCompression == 0){
					 //отображение изображения на экране
					 System::String^ string_pathCopyBMP = "maskBMP.bmp";
					 Bitmap^ bmpOrig = gcnew Bitmap("maskBMP.bmp");
					 /*
					 System::String^ string_pathCopyBMP = "copyBMP.bmp";
					 Bitmap^ bmpOrig = gcnew Bitmap(string_pathCopyBMP);
					 */
					 Bitmap^ bmp = gcnew Bitmap(bmpOrig, pictureBox3->Width, pictureBox3->Height);
					 Graphics^ g = pictureBox3->CreateGraphics();
					 //pictureBox1->Width=bmpOrig->Width;
					 //pictureBox1->Height=bmpOrig->Height;
					 g->DrawImage(bmp, 1, 1);
					 delete bmpOrig;
					 delete bmp;
					 delete g;

				 }
				 else{
					 //MessageBox::Show("");
				 }
	}

	private: void ShowCopyBmp()
			{				 
				pictureBox2->Refresh();
				if(InfoHeader.biCompression==0){
					//отображение изображения на экране
					System::String^ string_pathCopyBMP_ = "copyBMP.bmp";
					Bitmap^ bmpOrig = gcnew Bitmap(string_pathCopyBMP_);

					Bitmap^ bmp = gcnew Bitmap(bmpOrig,pictureBox2->Width,pictureBox2->Height);
					Graphics^ g = pictureBox2->CreateGraphics();
					//pictureBox2->Width=bmpOrig->Width;
					//pictureBox2->Height=bmpOrig->Height;
					g->DrawImage(bmp, 1, 1);
					delete bmpOrig;
					delete bmp;
					delete g;
				}
				else{
					//MessageBox::Show("");
				}
			}

	private: bool SaveBMP()
			 {
				 FILE* f = fopen(myPath_char,"wb");

				 if(!f){
					 MessageBox::Show("File open error!");
					 return false;
				 }

				 fwrite(&hdBMP,sizeof(hdBMP),1,f);
				 fwrite(&InfoHeader,sizeof(InfoHeader),1,f);

				 //если есть палитра
				 if( InfoHeader.biBitCount<24 )
				 {
					 fwrite(palette,size_palette,1,f);
				 }

				 fseek(f,hdBMP.bfOffBits,SEEK_SET);//переход на позицию, с кот. нач пиксельные данные
				 fwrite(buffer,size,1,f);
				 fclose(f);

				 return true;
			 }

	private: bool CopyArrayUCHAR(UCHAR* array1, UCHAR* array2, int size)
			 {
				 for(int i=0;i<size;i++)
				 {
					 array2[i] = array1[i];
				 }

				 return true;
			 }

			 //Преобразование в полутоновое изображение
	private: void convertToHalftone()
			 {
				 float average;
				 for(int i=0;i<size;i+=3)
				 {
					 average=( buffer[i] +  buffer[i+1] +  buffer[i+2] )/3;
					 buffer[i] = average;//Blue
					 buffer[i+1] = average;//Green
					 buffer[i+2] = average;//Red
				 }
			 }

	private: float myFabs(float x)
			 {
				 if(x < 0)
					 return -x;
				 else
					 return x;
			 }

	private: bool saveCopyBMP()
			 {
				 FILE* f = fopen(char_pathCopyBMP,"wb");

				 if(!f){
					 MessageBox::Show("File open error!");
					 return false;
				 }

				 fwrite(&hdBMP,sizeof(hdBMP),1,f);
				 fwrite(&InfoHeader,sizeof(InfoHeader),1,f);

				 //если есть палитра
				 if( InfoHeader.biBitCount<24 )
				 {
					 fwrite(palette,size_palette,1,f);
				 }

				 fseek(f,hdBMP.bfOffBits,SEEK_SET);//переход на позицию, с кот. нач пиксельные данные
				 fwrite(bufferBackup,size,1,f);
				 fclose(f);

				 return true;
			 }

	private: bool saveMaskBMP()
	{
				 FILE* f = fopen("maskBMP.bmp", "wb");

				 if (!f){
					 MessageBox::Show("File open error!");
					 return false;
				 }

				 fwrite(&hdBMP, sizeof(hdBMP), 1, f);
				 fwrite(&InfoHeader, sizeof(InfoHeader), 1, f);

				 //если есть палитра
				 if (InfoHeader.biBitCount<24)
				 {
					 fwrite(palette, size_palette, 1, f);
				 }

				 fseek(f, hdBMP.bfOffBits, SEEK_SET);//переход на позицию, с кот. нач пиксельные данные
				 fwrite(shadowMask, size, 1, f);
				 fclose(f);

				 return true;
	}
	//END


		 //Открыть
private: System::Void button1open_Click(System::Object^  sender, System::EventArgs^  e) {

				 button6Close_Click(sender,e);

				 if( !OpenBmp(true) )
					 return;
				
				 button7colorCorrection->Enabled=true;
				 buttonRestoreImage->Enabled=true;

				 textBoxShadowDetectionThreshold->Text = System::Convert::ToString(0);
		 }

private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

			 //Set mean shift segmentation params
			 textBoxMSSSpatialRadius->Text = System::Convert::ToString(MeanShiftParams::SPATIAL_RADIUS);
			 textBoxMSSColorRadius->Text = System::Convert::ToString(MeanShiftParams::COLOR_RADIUS);
			 textBoxMSSMinRegionSize->Text = System::Convert::ToString(MeanShiftParams::MIN_REGION_SIZE);
		 }
private: System::Void panel1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {			
		 }

		 //Сохранить
private: System::Void button2save_Click(System::Object^  sender, System::EventArgs^  e) {
		
			 //проверка на открытый файл
			 if(!OPEN){
				 MessageBox::Show("No file to save!");
				 return;
			 }
			 
			 if(SaveBMP())
				MessageBox::Show("Success!");
			 else
				 MessageBox::Show("Fail!");
		 }

		 //Выход
private: System::Void button3exit_Click(System::Object^  sender, System::EventArgs^  e) {
			 exit(0);
		 }

		 //Обновить изображение при изменении размеров формы
private: System::Void Form1_ResizeEnd(System::Object^  sender, System::EventArgs^  e) {
			 if(OPEN)
			 {
				 ShowBmp();
			 }
		 }

		 //Обновить изображение при прокрутке формы
private: System::Void Form1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 if(OPEN)
			 {
				 ShowBmp();
			 }
		 }

		 //Получение фокуса
private: System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
			 if(OPEN)
			 {
				 ShowBmp();
			 }
		 }

		 //Обновить при нажатии мишкой
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(OPEN)
			 {
				 ShowBmp();
			 }
		 }

		 //Закрыть
private: System::Void button6Close_Click(System::Object^  sender, System::EventArgs^  e) {
			pictureBox1->Refresh();
			pictureBox2->Refresh();
			 button7colorCorrection->Enabled=false;
			 buttonRestoreImage->Enabled=false;
	
			 textBox1open->Clear();
			 textBox2info->Clear();
			 OPEN=false;
		 }

		 //Цветовая коррекция
private: System::Void button7colorCorrection_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 int Red,Green,Blue,RGB;

			 //Если поле не заполнено, то обнуление
			 if( textBoxRed->Text=="" ) 
				 textBoxRed->Text="0";

			 if( textBoxGreen->Text=="" ) 
				 textBoxGreen->Text="0";

			 if( textBoxBlue->Text=="" ) 
				 textBoxBlue->Text="0";

			 if( textBoxRGB->Text=="" ) 
				 textBoxRGB->Text="0";
			 
			 Red = System::Convert::ToInt32(textBoxRed->Text);
			 Green = System::Convert::ToInt32(textBoxGreen->Text);
			 Blue = System::Convert::ToInt32(textBoxBlue->Text);
			 RGB = System::Convert::ToInt32(textBoxRGB->Text);
			 
			 for(int i=0;i<size;i+=3)
			 {
				 if (shadowMask[i] == 255)
				 {
					 buffer[i] + Blue + RGB>255 ? buffer[i] = 255 : (buffer[i] + Blue + RGB<0 ? buffer[i] = 0 : buffer[i] += Blue + RGB);//Blue
					 buffer[i + 1] + Green + RGB>255 ? buffer[i + 1] = 255 : (buffer[i + 1] + Green + RGB<0 ? buffer[i + 1] = 0 : buffer[i + 1] += Green + RGB);//Green
					 buffer[i + 2] + Red + RGB>255 ? buffer[i + 2] = 255 : (buffer[i + 2] + Red + RGB < 0 ? buffer[i + 2] = 0 : buffer[i + 2] += Red + RGB);//Red
				 }
			 }
			
			 SaveBMP();
			 ShowBmp();
		 }

		 //Востановить массив пикселей, который был при откритии файла
private: System::Void buttonRestoreImage_Click(System::Object^  sender, System::EventArgs^  e) {

			 CopyArrayUCHAR(bufferBackup, buffer, size);
			 SaveBMP();
			 ShowBmp();
		 }

		 //Обнулить значения цветов
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

			 textBoxRed->Text="0";
			 textBoxGreen->Text="0";
			 textBoxBlue->Text="0";
			 textBoxRGB->Text="0";
		 }

private: void CalcShadowMask()
{
			 //Computing the average at Y channel 
			 float averageY = 1;
			 float sum = 0;
			 for (int i = 0; i < size; i += 3)
			 {
				 int Y = buffer[i];
				 sum += Y;
			 }
			 averageY = sum / (float)(size / 3.0);

			 //find shadow mask
			 //unsigned char *shadowMask = nullptr;
			 shadowMask = new UCHAR[size];
			 for (int i = 0; i<size; i += 3)
			 {
				 //float average = (buffer[i] + buffer[i + 1] + buffer[i + 2]) / 3;
				 int Y = buffer[i];
				 if (Y < averageY){
					 shadowMask[i] = 255;
					 shadowMask[i + 1] = 255;
					 shadowMask[i + 2] = 255;
				 }
				 else{
					 shadowMask[i] = 0;
					 shadowMask[i + 1] = 0;
					 shadowMask[i + 2] = 0;
				 }
			 }
}
		 
private: System::Void buttonToYCbCr_Click(System::Object^  sender, System::EventArgs^  e) {

			 int size2 = size;

			 //convert to YCbCr;
			 RGBtoYCbCr();

			 //FIND Shadow Mask
			 CalcShadowMask();
			 saveMaskBMP();
			 ShowMaskBmp();

			 float diffA = 0;
			 //REMOVE
			 if (checkBox1Remove->Checked)
			 {

				 //Computing the average pixel intensities of the shadow and non - shadow areas
				 float shadowIntensity = 0;
				 float nonShadowIntensity = 0;
				 float sumShadow = 0;
				 float sumNonShadow = 0;
				 int nShadow = 0;
				 int nNonShadow = 0;
				 for (int i = 0; i < size; i += 3)
				 {
					 if (shadowMask[i] == 255){
						 sumShadow += buffer[i];
						 nShadow += 1;
					 }
					 else {
						 sumNonShadow += buffer[i];
						 nNonShadow += 1;
					 }
				 }
				 shadowIntensity = sumShadow / nShadow;
				 nonShadowIntensity = sumNonShadow / nNonShadow;
				 //float diff = shadowIntensity - nonShadowIntensity;
				 float diff = nonShadowIntensity - shadowIntensity;
				 diffA = diff;
				 //Adding this difference with Y channel 
				 for (int i = 0; i < size; i += 3)
				 {
					 if (shadowMask[i] == 255){
						 buffer[i] += diff;
					 }
				 }

				 //Computing the ratio between average shadow pixels and average non - shadow pixels

				 float r = 0;
				 r = nonShadowIntensity / shadowIntensity;
				 //r = shadowIntensity / nonShadowIntensity;

				 for (int i = 0; i < size; i += 3)
				 {
					 float ki = 0;
					 if (shadowMask[i] == 255){
						 ki = 1;
					 }
					 else
					 {
						 ki = 0;
					 }

					 if (shadowMask[i] == 255){
						 float a1, a2;
						 a1 = buffer[i + 1];
						 a2 = ((r + 1) / (ki*r + 1))*buffer[i + 1];

						 //buffer[i] = ((r + 1) / (ki*r + 1))*buffer[i];
						 buffer[i + 1] = ((r + 1) / (ki*r + 1))*buffer[i + 1];
						 buffer[i + 2] = ((r + 1) / (ki*r + 1))*buffer[i + 2];

					 }
				 }


				 ///////////////////// Correct average intensities

				 int a=0;
				 
				 float Cb = 0;
				 float Cr = 0;

				 float CbS = 0;
				 float CrS = 0;

				 for (int i = 0; i < size; i += 3)
				 {
					 if (shadowMask[i] == 255){
						 CbS += buffer[i + 1];
						 CrS += buffer[i + 2];
					 }
					 else{
						 Cb += buffer[i + 1];
						 Cr += buffer[i + 2];
					 }
				 }

				 Cb = Cb / nNonShadow;
				 Cr = Cr / nNonShadow;

				 CbS = CbS / nShadow;
				 CrS = CrS / nShadow;

				 float diffCb = Cb - CbS;
				 float diffCr = Cr - CrS;

				 float ratioCb = Cb / CbS;
				 float ratioCr = Cr / CrS;

				 for (int i = 0; i < size; i += 3)
				 {
					 if (shadowMask[i] == 255){
//						 buffer[i + 1] = buffer[i + 1] * ratioCb;
//						 buffer[i + 2] = buffer[i + 2] * ratioCr;
					 }
				 }
				 int b = 0;
			 }
			 
			 /////////////////////////////////////////////////////////////////
			 
			 if (checkBoxConvertBack->Checked)
			 {
				 //Converting YCbCr to RGB 
				 YCbCrtoRGB();
			 }
			 /////////////////////////////////
			 //Autolevels(false,true);
			 //RGBtoYCbCr();
			 if (checkBoxCluster->Checked)
			 {
				 K_Means();
			 }
			 //YCbCrtoRGB();
			
			 SaveBMP();
			 ShowBmp();
}

//Растяжение контрастности (“autolevels”) - Линейная коррекция
private: void Autolevels()
{
		/////
		//Растяжение контрастности (“autolevels”)
		int Rmin = 255;
		int Gmin = 255;
		int Bmin = 255;
		int Rmax = 0;
		int Gmax = 0;
		int Bmax = 0;
		for (int i = 0; i < size; i += 3)
		{

			if (buffer[i] < Rmin)
				Rmin = buffer[i];
			if (buffer[i + 1] < Gmin)
				Gmin = buffer[i + 1];
			if (buffer[i + 2] < Bmin)
				Bmin = buffer[i + 2];

			if (buffer[i] > Rmax)
				Rmax = buffer[i];
			if (buffer[i + 1] > Gmax)
				Gmax = buffer[i + 1];
			if (buffer[i + 2] > Bmax)
				Bmax = buffer[i + 2];
		}
		for (int i = 0; i < size; i += 3)
		{

			int R = buffer[i];
			int G = buffer[i + 1];
			int B = buffer[i + 2];

			buffer[i] = (R - Rmin)*(255 / (Rmax - Rmin));
			buffer[i + 1] = (G - Gmin)*(255 / (Gmax - Gmin));
			buffer[i + 2] = (B - Bmin)*(255 / (Bmax - Bmin));
		}
}

private: void RGBtoYCbCr()
{
			 //convert to YCbCr;
			 for (int i = 0; i<size; i += 3)
			 {
				 int R = buffer[i];//Blue
				 int G = buffer[i + 1];//Green
				 int B = buffer[i + 2];//Red


				 /*
				 int Y = (int)(0.299   * R + 0.587   * G + 0.114   * B);
				 int Cb = (int)(128 -0.16874 * R - 0.33126 * G + 0.50000 * B);
				 int Cr = (int)(128 + 0.50000 * R - 0.41869 * G - 0.08131 * B);
				 */


				 int Y = 0.299*R + 0.587*G + 0.114*B;
				 //int Cb =  - 0.168736*R - 0.331264*G + 0.5*B + 128;
				 int Cb = -0.169*R - 0.331*G + 0.5*B + 128;
				 //int Cr = +0.5*R - 0.418688*G - 0.081312*B + 128;
				 int Cr = +0.5*R - 0.419*G - 0.081*B + 128;


				 /*
				 int Y = round(0.299    *R + 0.587  *G + 0.114  *B);
				 int Cb = round(-0.1687   *R - 0.3313 *G + 0.5    *B) + 128;
				 int Cr = round(0.5      *R - 0.4187 *G - 0.0813 *B) + 128;
				 */


				 if (Y>255) Y = 255;
				 else if (Y<0) Y = 0;
				 if (Cb>255) Cb = 255;
				 else if (Cb<0) Cb = 0;
				 if (Cr>255) Cr = 255;
				 else if (Cr<0) Cr = 0;


				 buffer[i] = Y;//Blue
				 buffer[i + 1] = Cb;//Green
				 buffer[i + 2] = Cr;//Red
			 }
}

private: void YCbCrtoRGB()
{
		//Converting YCbCr to RGB 
		for (int i = 0; i < size; i += 3)
		{
			int Y = buffer[i];
			int Cb = buffer[i + 1];
			int Cr = buffer[i + 2];


			//int R = (int)((double)Y + 1.402 * (double)(Cr - 128));
			//int G = (int)((double)Y - 0.34414 * (double)(Cb - 128) - 0.71414 * (double)(Cr - 128));
			//int B = (int)((double)Y + 1.772 * (double)(Cb - 128));

			///int R = Y + 1.402*(Cr - 128);
			//int G = Y - 0.34414*(Cb - 128) - 0.71414*(Cr - 128);
			//int B = Y + 1.772*(Cb - 128);

			int R = Y + 1.4*(Cr - 128);
			int G = Y - 0.343*(Cb - 128) - 0.711*(Cr - 128);
			int B = Y + 1.765*(Cb - 128);


			if (R > 255) R = 255;
			else if (R<0) R = 0;
			if (G>255) G = 255;
			else if (G<0) G = 0;
			if (B>255) B = 255;
			else if (B < 0) B = 0;


			buffer[i] = R;
			buffer[i + 1] = G;
			buffer[i + 2] = B;
		}
}

private: double* RGBtoXYZ(UCHAR* bufferRGB)
{
			 double *bufferXYZ = new double[size];

			 for (int i = 0; i < size; i += 3)
			 {
				 int R = bufferRGB[i];
				 int G = bufferRGB[i + 1];
				 int B = bufferRGB[i + 2];

				 double var_R = (double)R / (double)255.0;
				 double var_G = (double)G / (double)255.0;
				 double var_B = (double)B / (double)255.0;

				 if (var_R > 0.04045)
					 //var_R = ((var_R + 0.055) / 1.055) ^ 2.4;
					 var_R = pow((double)(((var_R + 0.055) / 1.055)), (double)2.4); 
				 else
					 var_R = var_R / 12.92;

				 if (var_G > 0.04045)
					 //var_G = ((var_G + 0.055) / 1.055) ^ 2.4;
					 var_G = pow((double)(((var_G + 0.055) / 1.055)), (double)(2.4));
				 else
					 var_G = var_G / 12.92;

				 if (var_B > 0.04045)
					 //var_B = ((var_B + 0.055) / 1.055) ^ 2.4;
					 var_B = pow((double)(((var_B + 0.055) / 1.055)), (double)(2.4));
				 else
					 var_B = var_B / 12.92;

				 var_R = var_R * 100;
				 var_G = var_G * 100;
				 var_B = var_B * 100;

				 //Observer. = 2°, Illuminant = D65
				 double X = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
				 double Y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
				 double Z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;

				 bufferXYZ[i] = X;
				 bufferXYZ[i + 1] = Y;
				 bufferXYZ[i + 2] = Z;
			 }

			 return bufferXYZ;
}

private: double* XYZtoCIELAB(double* bufferXYZ)
{
			 double *bufferLAB = new double[size];

			 for (int i = 0; i < size; i += 3)
			 {
				 int X = bufferXYZ[i];
				 int Y = bufferXYZ[i + 1];
				 int Z = bufferXYZ[i + 2];

				 double ref_X = 95.047;
				 double ref_Y = 100.000;
				 double ref_Z = 108.883;

				 double var_X = (double)X / (double)ref_X;          //ref_X =  95.047   Observer= 2°, Illuminant= D65
				 double var_Y = (double)Y / (double)ref_Y;          //ref_Y = 100.000
				 double var_Z = (double)Z / (double)ref_Z;          //ref_Z = 108.883

				 if (var_X > 0.008856)
					 //var_X = var_X ^ (1 / 3);
					 var_X = pow((double)(var_X), (double)(1.0 / 3.0));
				 else
					 var_X = (7.787 * var_X) + (16.0 / 116.0);

				 if (var_Y > 0.008856)
					 //var_Y = var_Y ^ (1 / 3);
					 var_Y = pow((double)(var_Y), (double)(1.0 / 3.0));
				 else
					 var_Y = (7.787 * var_Y) + (16.0 / 116.0);

				 if (var_Z > 0.008856)
					 //var_Z = var_Z ^ (1 / 3);
					 var_Z = pow((double)(var_Z), (double)(1.0 / 3.0));
				 else
					 var_Z = (7.787 * var_Z) + (16.0 / 116.0);

				 double CIE_L = (116 * var_Y) - 16;
				 double CIE_a = 500 * (var_X - var_Y);
				 double CIE_b = 200 * (var_Y - var_Z);

				 bufferLAB[i] = CIE_L;
				 bufferLAB[i + 1] = CIE_a;
				 bufferLAB[i + 2] = CIE_b;
			 }

			 return bufferLAB;
}

private: void K_Means(){

			 int K = 5; //Кількість кластерів
			 int Q = size/3;//Кількість векторів
			 int Qn = 3; //Розмір векторів

			 //double[, ] X = new double[Q, Qn];
			 double **X = new double *[Q];
			 for (int i = 0; i < Q; i++){
				 X[i] = new double[Qn];
			 }
			 /*
			 for (int i = 0; i < M; i++) {
				delete []mas[i];
			}
			delete []mas;
			 */

			 //Copy buffer to matrix X
			 for (int i = 0, j = 0; j < size; i += 1,j += 3)
			 {
				X[i][0] = buffer[j];
				X[i][1] = buffer[j + 1];
				X[i][2] = buffer[j + 2];

//				 X[i][0] = buffer[j + 1];
//				 X[i][1] = buffer[j + 2];
			 }

			 //Центри кластерів
			 double **z = new double*[K];
			 for (int i = 0; i < K; i++){
				 z[i] = new double[Qn];
			 }

			 //Нові центри кластерів
			 double **z_new = new double*[K];
			 for (int i = 0; i < K; i++){
				 z_new[i] = new double[Qn];
			 }

			 //Кількість векторів к-го класу
			 int *n_k = new int[K];

			 bool skipStep1 = false;
			 for (int iteration = 0; true; iteration++)
			 {
				 if (!skipStep1)
				 {
					 //Крок 1
					 //Console.WriteLine("Крок 1");
					 //Цикл ініціалізації центрів кластерів
					 //Беремо центри які значно відрізняються
					 int step = Q / K;
					 int X_index = 0;
					 for (int k = 0; k < K; k++)
					 {
						 //z_k = x_k;
						 for (int j = 0; j < Qn; j++)
						 {
							 //z[k, j] = X[k, j];
							 z[k][j] = X[X_index][j];
						 }
						 double AAA1 = z[k][0];
						 double AAA2 = z[k][1];
						 double AAA3 = z[k][2];
						 //n(k1) = 0;
						 n_k[k] = 0;
						 X_index += step;
					 }
				 }

				 //Крок 2
				 //Console.WriteLine("Крок 2");

				 /*double[, ] teta = new double[1, Qn];
				 int[] class_q = new int[Q];*/

				 double **teta = new double*[1];
				 for (int i = 0; i < 1; i++){
					 teta[i] = new double[Qn];
				 }
				 
				 int *class_q = new int[Q];

				 ///* Цикл занесення векторів до кластерів з найближчим центром */
				 for (int q = 0; q < Q; q++)
				 {
					 double d_min = 999999999.1;//999999.9;
					 double d = 0;
					 int k_min = 0;

					 ///* Цикл знаходження мінімальної відстані до центрів */
					 for (int k = 0; k < K; k++)
					 {
						 //Знаходження відстані d = || x_q - z_k ||
						 double sum = 0;
						 for (int j = 0; j < Qn; j++)
						 {
							 //sum += Math.Pow(X[q, j] - z[k, j], 2);
							 double XXX = X[q][j];
							 double zzzz = z[k][j];
							 double ttt = X[q][j] - z[k][j];
							 double ttpow = pow(X[q][j] - z[k][j], 2); 
							 sum += pow(X[q][j] - z[k][j], 2);
						 }
						 //d = Math.Sqrt(sum);
						 d = pow(sum,0.5);

						 //Визначення мінімальної відстані
						 if (d < d_min)
						 {
							 d_min = d;
							 k_min = k;
						 }
					 }
					 /*Позначення вектора x_q k-им класом */
					 //class(q) = k_min
					 class_q[q] = k_min;

					 //n(k_min) = n(k_min) + 1 ///* Інкрементація лічильника векторів k_min-го класу 
					 n_k[k_min] += 1;
				 }

				//Крок 3
				 //Console.WriteLine("Крок 3");

				 /* Цикл обчислення K нових центрів кластерів */
				 for (int k = 0; k < K; k++)
				 {
					 /* Знаходження середнього k1-го кластера */
					 //1/n(k)
					 //double temp = 1.0 / (double)n_k[k];

					 for (int j = 0; j < Qn; j++)
					 {
						 double sum = 0;
						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 //sum += X[q, j];
								 sum += X[q][j];
							 }
						 }
						 //z_new[k, j] = sum / (double)n_k[k];
						 z_new[k][j] = sum / (double)n_k[k];
					 }
				 }

				 //Крок 4
				 //Console.WriteLine("Крок 4");
				 //перевіряємо умову припинення процедури кластеризації
				 bool Flag = false;

				 ///* Цикл фіксації зміни хоча б одного центра за допомогою прапорця */
				 for (int k = 0; k < K; k++)
				 {
					 //Знаходження відстані d_z = ||z_new_k - z_k||
					 double d_z = 0;
					 double sum = 0;
					 double diff = 1;
					 for (int j = 0; j < Qn; j++)
					 {
						 //diff = z_new[k, j] - z[k, j];
						 diff = z_new[k][j] - z[k][j];
						 //sum += Math.Pow(z_new[k, j] - z[k, j], 2);
						 sum += pow(z_new[k][j] - z[k][j], 2);
					 }
					 //d_z = Math.Sqrt(sum);
					 d_z = pow(sum,0.5);

					 if (d_z > 0.0000000001)//0.0005)
						 Flag = true;
				 }

				 ///* При наявності змін обновити центри і повторити процедуру */
				 if (Flag == true)
				 {
					 //Console.WriteLine("Повтор процедури. Ітерація - {0}", iteration);
					 for (int k = 0; k < K; k++)
					 {
						 n_k[k] = 0;
						 for (int j = 0; j < Qn; j++)
							 //z[k, j] = z_new[k, j];
							 z[k][j] = z_new[k][j];
					 }
					 skipStep1 = true; //Пропустити крок 1
				 }
				 /* Інакше припинити кластеризацію */
				 else
				 {
					 ////###////###/////####

					 //Видалити пустi кластери
					 for (int k = 0; k < K; k++)
					 {
						 int A = 0;

							 
						for (int q = 0; q < Q; q++)
						{
							if (class_q[q] == k)
							{
								A++;
							}
						}
						if (n_k[k] == 0)
						{
							n_k[k] = 0;


						}
							 
					 }

					 //Пройтись по всім кластерам і розділити їх на два, якщо в ньому присутні тіньові ті нетіньові пікселі
					 int need_to_separate = 0;

					 int *clusters_to_separate = new int[K];
					 int indexCTS = 0;
					 for (int k = 0; k < K; k++)
					 {
						 clusters_to_separate[k] = -1;
					 }

					 for (int k = 0; k < K; k++)
					 {
						 bool is_homogenous = true;
						 bool is_shadow = false;
						 bool is_non_shadow = false;
						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 if (shadowMask[q * 3] == 255)
								 {
									 is_shadow = true;
								 }
								 else
								 {
									 is_non_shadow = true;
								 }

								 if (is_shadow && is_non_shadow)
								 {
									 //clusters_to_separate[indexCTS] = k;
									 clusters_to_separate[k] = true;
									 indexCTS += 1;
									 need_to_separate += 1;
									 break;
								 }
							 }
						 }
					 }
					 int new_clusters_amount = indexCTS;

					 //Розбиваємо кластер на два
					 int new_cluster_number = K;
					 int *n_k_new = new int[new_clusters_amount];
					 for (int k = 0; k < new_clusters_amount; k++)
						 n_k_new[k] = 0;
					 for (int k = 0; k < K; k++)
					 {
						 if (clusters_to_separate[k] == -1)
							 continue;

						 //int current_cluster = clusters_to_separate[k];
						 
						 int current_cluster = -1;
						 if (clusters_to_separate[k] == true){
							 current_cluster = k;
						 }

						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == current_cluster)
							 {
								 if (shadowMask[q * 3] == 255)
								 {
									 class_q[q] = new_cluster_number;
									 //n_k[k] -= 1;
									 n_k_new[new_cluster_number - K] += 1;
								 }
							 }
						 }
						 n_k[k] = n_k[k] - n_k_new[new_cluster_number - K];
						 new_cluster_number += 1;
					 }
					 int *temp_n_k = new int[K + new_clusters_amount];
					 for (int k = 0; k < K + new_clusters_amount; k++)
					 {
						 if (k < K)
							 temp_n_k[k] = n_k[k];
						 else
							 temp_n_k[k] = n_k_new[k - K];
					 }
					 delete n_k;
					 delete n_k_new;
					 n_k = temp_n_k;
					 K = K + new_clusters_amount;
					 
					 //Записати номера векторів кожного кластера
					 int **clusters_elements = new int *[K];
					 for (int i = 0; i < K; i++)
					 {
						 clusters_elements[i] = new int[n_k[i]];
					 }
					 bool *is_shadow_claster = new bool[K];
					 for (int k = 0; k < K; k++)
					 {
						 int j = 0;
						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 //check if cluster contain shadow pixels
								 if (shadowMask[q*3] == 255)
									 is_shadow_claster[k] = true;
								 else
									 is_shadow_claster[k] = false;

								 clusters_elements[k][j] = q;
								 j += 1;
							 }
						 }
					 }
					 

					 //
					 
					 //Корекція кольору пікселів тіні
					 for (int k = 0; k < K; k++)
					 {
						 if (is_shadow_claster[k] == false)
							 continue;

						 //Знаходимо кольорову характеристику даного тіньового кластера
						 double average_color = 0;
						 double R_avg_shadow = 0;
						 double G_avg_shadow = 0;
						 double B_avg_shadow = 0;

						 double Y_avg_shadow = 0;
						 double Cb_avg_shadow = 0;
						 double Cr_avg_shadow = 0;
						 for (int j = 0; j < n_k[k]; j++)
						 {
							 int index = clusters_elements[k][j];
							 int R = buffer[index * 3];
							 int G = buffer[index * 3 + 1];
							 int B = buffer[index * 3 + 2];

							 int Cb = buffer[index * 3 + 1];
							 int Cr = buffer[index * 3 + 2];

							 //average_color += (double)((R + G + B) / 3.0);
							 average_color += (double)((R + G + B));
							 R_avg_shadow += R;
							 G_avg_shadow += G;
							 B_avg_shadow += B;

							 Cb_avg_shadow += G;
							 Cr_avg_shadow += B;
						 }
						 average_color = average_color / (n_k[k]);
						 R_avg_shadow /= n_k[k];
						 G_avg_shadow /= n_k[k];
						 B_avg_shadow /= n_k[k];

						 Cb_avg_shadow /= n_k[k];
						 Cr_avg_shadow /= n_k[k];

						 average_color = (R_avg_shadow + G_avg_shadow + B_avg_shadow) / 3;

						 //
						 int min_average_diff_cluster = -1;
						 double diff = 999999999.1;
						 double R_diff = 9999999.1;
						 double G_diff = 999999999.1;
						 double B_diff = 999999999.1;

						 double Cb_diff = 999999.1;
						 double Cr_diff = 999999.1;
						 for (int kk = 0; kk < K; kk++)
						 {
							 if (is_shadow_claster[kk] == true)
								 continue;

							 double average_color_non_shadow = 0;
							 double R_avg_non_shadow = 0;
							 double G_avg_non_shadow = 0;
							 double B_avg_non_shadow = 0;

							 double Y_avg_non_shadow = 0;
							 double Cb_avg_non_shadow = 0;
							 double Cr_avg_non_shadow = 0;
							 for (int jj = 0; jj < n_k[kk]; jj++)
							 {
								 int index = clusters_elements[kk][jj];
								 int R = buffer[index * 3];
								 int G = buffer[index * 3 + 1];
								 int B = buffer[index * 3 + 2];

								 int Cb = buffer[index * 3 + 1];
								 int Cr = buffer[index * 3 + 2];

								 //average_color_non_shadow += (double)((R + G + B) / 3.0);
								 average_color_non_shadow += (double)((R + G + B));
								 R_avg_non_shadow += R;
								 G_avg_non_shadow += G;
								 B_avg_non_shadow += B;

								 Cb_avg_non_shadow += G;
								 Cr_avg_non_shadow += B;
							 }
							 average_color_non_shadow = average_color_non_shadow / (n_k[kk]);
							 R_avg_non_shadow /= n_k[kk];
							 G_avg_non_shadow /= n_k[kk];
							 B_avg_non_shadow /= n_k[kk];

							 Cb_avg_non_shadow /= n_k[kk];
							 Cr_avg_non_shadow /= n_k[kk];

							 average_color_non_shadow = (R_avg_non_shadow + G_avg_non_shadow + B_avg_non_shadow) / 3;

							 
//							 if (abs(average_color_non_shadow - average_color) < diff)
//							 {
//								 min_average_diff_cluster = kk;
//								 diff = abs(average_color_non_shadow - average_color);
//							 }
//							 

							 double diffTotal = average_color_non_shadow - average_color;
							 if ((abs(R_avg_non_shadow - R_avg_shadow) < R_diff) && (abs(G_avg_non_shadow - G_avg_shadow) < G_diff) && (abs(B_avg_non_shadow - B_avg_shadow) < B_diff))
							 {
								 min_average_diff_cluster = kk;
								 diff = abs(average_color_non_shadow - average_color);
								 R_diff = abs(R_avg_non_shadow - R_avg_shadow);
								 G_diff = abs(G_avg_non_shadow - G_avg_shadow);
								 B_diff = abs(B_avg_non_shadow - B_avg_shadow);
							 }

//							 if ((abs(Cr_avg_non_shadow - Cr_avg_shadow) < Cr_diff) && (abs(Cb_avg_non_shadow - Cb_avg_shadow) < Cb_diff))
//							 {
//								 min_average_diff_cluster = kk;
//								 Cb_diff = abs(Cb_avg_non_shadow - Cb_avg_shadow);
//								 Cr_diff = abs(Cr_avg_non_shadow - Cr_avg_shadow);
//							 }
						 }
						 int asda = 0;

						 if (min_average_diff_cluster < 0)
						 {
							 Sleep(10);
						 }

//						 if (k == 5)
//							 min_average_diff_cluster = 3;
//						 if (k == 7)
//							 min_average_diff_cluster = 2;
						 //min_average_diff_cluster = 2;

						 //Коректуємо колір даного тіньового кластера з знайденим
						 double R_avg_other = 0;
						 double G_avg_other = 0;
						 double B_avg_other = 0;
						 for (int j = 0; j < n_k[min_average_diff_cluster]; j++)
						 {
							 int index = clusters_elements[min_average_diff_cluster][j];
							 int R = buffer[index * 3];
							 int G = buffer[index * 3 + 1];
							 int B = buffer[index * 3 + 2];

							 R_avg_other += R;
							 G_avg_other += G;
							 B_avg_other += B;
						 }
						 R_avg_other /= n_k[min_average_diff_cluster];
						 G_avg_other /= n_k[min_average_diff_cluster];
						 B_avg_other /= n_k[min_average_diff_cluster];

						 double R_avg_curr = 0;
						 double G_avg_curr = 0;
						 double B_avg_curr = 0;
						 for (int j = 0; j < n_k[k]; j++)
						 {
							 int index = clusters_elements[k][j];
							 int R = buffer[index * 3];
							 int G = buffer[index * 3 + 1];
							 int B = buffer[index * 3 + 2];

							 R_avg_curr += R;
							 G_avg_curr += G;
							 B_avg_curr += B;
						 }
						 R_avg_curr /= n_k[k];
						 G_avg_curr /= n_k[k];
						 B_avg_curr /= n_k[k];

						 //Values to add/sub
						 int Red = R_avg_other - R_avg_curr;
						 int Green = G_avg_other - G_avg_curr;
						 int Blue = B_avg_other - B_avg_curr;
						 int RGB = 0;

						 double R_ratio = (R_avg_other / R_avg_curr);
						 double G_ratio = (G_avg_other / G_avg_curr);
						 double B_ratio = (B_avg_other / B_avg_curr);
						 int asdasdasdasd = 0;

						 //Color correction
						 /*
						 for (int j = 0; j < n_k[k]; j++)
						 {
							 int index = clusters_elements[k][j];
							 buffer[index * 3] + Red + RGB>255 ? buffer[index * 3] = 255 : (buffer[index * 3] + Red + RGB < 0 ? buffer[index * 3] = 0 : buffer[index * 3] += Red + RGB);//Red
							 buffer[index * 3 + 1] + Green + RGB>255 ? buffer[index * 3 + 1] = 255 : (buffer[index * 3 + 1] + Green + RGB<0 ? buffer[index * 3 + 1] = 0 : buffer[index * 3 + 1] += Green + RGB);//Green
							 buffer[index * 3 + 2] + Blue + RGB>255 ? buffer[index * 3 + 2] = 255 : (buffer[index * 3 + 2] + Blue + RGB<0 ? buffer[index * 3 + 2] = 0 : buffer[index * 3 + 2] += Blue + RGB);//Blue
						 }
						 */
						 int maxI = 0;
						 for (int j = 0,index=0; j < n_k[k]; j++)
						 {
							 index = clusters_elements[k][j];

							 if (index > maxI)
								 maxI = index;
							 
							 int currR = buffer[index * 3];
							 int currG = buffer[index * 3 + 1];
							 int currB = buffer[index * 3 + 2];

							 currR += Red;
							 currG += Green;
							 currB += Blue;

//							 currR *= R_ratio;
//							 currG *= G_ratio;
//							 currB *= B_ratio;

//							 //Зафарбувати в середні кольори
//							 buffer[index * 3] = (unsigned char)R_avg_other;//Red
//							 buffer[index * 3 + 1] = (unsigned char)G_avg_other;//Green
//							 buffer[index * 3 + 2] = (unsigned char)B_avg_other;//Blue

//							 currR += -46;
//							 currG += -40;// -36;//Green
//							 currB += -19;// -11;//Blue

							 currR = currR > 255 ? 255 : (currR < 0 ? 0 : currR);
							 currG = currG > 255 ? 255 : (currG < 0 ? 0 : currG);
							 currB = currB > 255 ? 255 : (currB < 0 ? 0 : currB);

							 buffer[index * 3] = currR;//Red
							 buffer[index * 3 + 1] = currG;//Green
							 buffer[index * 3 + 2] = currB;//Blue

						 }

						 /////////////////////

						 //Показати два кластери що коректуються
						 //////Візуалізація результату кластеризації у виглядi кольорів
						 //int classR = 180;
						 //int classG = 255;
						 //int classB = 0;
						 //for (int kkk = 0; kkk < K; kkk++)
						 //{
							// /*if (kkk != k || kkk != min_average_diff_cluster)
							//	 continue;*/

							// for (int q = 0; q < Q; q++)
							// {
							//	 X[q][0] = 0;
							//	 X[q][1] = 255;
							//	 X[q][2] = 208;
							//	 if (class_q[q] == k)
							//	 {
							//		 X[q][0] = 0;
							//		 X[q][1] = 0;
							//		 X[q][2] = 0;
							//	 }
							//	 if (class_q[q] == min_average_diff_cluster)
							//	 {
							//		 X[q][0] = 0;
							//		 X[q][1] = 0;
							//		 X[q][2] = 255;
							//	 }
							// }
							// classR -= rand() % 70;
							// classG -= rand() % 255;
							// classB += rand() % 255;
						 //}

						 ////Copy X to buffer
						 //for (int iii = 0, jjj = 0; jjj < size; iii += 1, jjj += 3)
						 //{
							// int RR = buffer[jjj];
							// int XR = X[iii][0];

							// buffer[jjj] = X[iii][0];
							// buffer[jjj + 1] = X[iii][1];
							// buffer[jjj + 2] = X[iii][2];
						 //}


						 //SaveBMP();
						 //ShowBmp();
						 //int a = 0;
						 /////////////////////////
						 ////break;
						 //CopyArrayUCHAR(bufferBackup, buffer, size);
						 /*SaveBMP();
						 ShowBmp();*/
						 
					 }
					 
					 
					 if (checkBoxClusterVisual->Checked)
					 {

						 //Візуалізація результату кластеризації у виглядi кольорів
						 int classR = 180;
						 int classG = 255;
						 int classB = 0;

						 for (int k = 0; k < K; k++)
						 {
							 if (k == 0)
							 {
								 classR = 255;
								 classG = 255;
								 classB = 255;
							 }
							 if (k == 1)//красный
							 {
								 classR = 0;
								 classG = 0;
								 classB = 255;
							 }
							 if (k == 2)//зеленый
							 {
								 classR = 0;
								 classG = 255;
								 classB = 0;
							 }
							 if (k == 3)//синий
							 {
								 classR = 255;
								 classG = 0;
								 classB = 0;
							 }
							 if (k == 4)//розовый
							 {
								 classR = 209;
								 classG = 100;
								 classB = 255;
							 }


							 if (k == 5)//оранжевый
							 {
								 classR = 0;
								 classG = 213;
								 classB = 255;
							 }
							 if (k == 6)//берюзовый
							 {
								 classR = 255;
								 classG = 252;
								 classB = 50;
							 }
							 if (k == 7)//фиолетовый /бледно-синий
							 {
								 classR = 255;
								 classG = 0;
								 classB = 191;

//								 classR = 255;
//								 classG = 128;
//								 classB = 128;
							 }
							 if (k == 8)//черный
							 {
								 classR = 0;
								 classG = 0;
								 classB = 0;
							 }

							 for (int q = 0; q < Q; q++)
							 {
								 if (class_q[q] == k)
								 {
									 X[q][0] = classR;
									 X[q][1] = classG;
									 X[q][2] = classB;
								 }
							 }
							 classR -= rand() % 70;
							 classG -= rand() % 255;
							 classB += rand() % 255;
						 }

						 //Copy X to buffer
						 for (int i = 0, j = 0; j < size; i += 1, j += 3)
						 {
							 int RR = buffer[j];
							 int XR = X[i][0];

							 buffer[j] = X[i][0];
							 buffer[j + 1] = X[i][1];
							 buffer[j + 2] = X[i][2];
						 }

						 ////FOR SPECIAL CLUSTERS
//						 for (int k = 0; k < K; k++)
//						 {
////							 if (k == 5)//оранжевый
////							 {
////								 classR = 0;
////								 classG = 213;
////								 classB = 255;
////							 }
//							 if (k == 7)//фиолетовый /бледно-синий
//							{
//								classR = 255;
//								classG = 0;
//								classB = 191;
//								 
////								 classR = 255;
////								 classG = 128;
////								 classB = 128;
//							}
//							 else//берюзовый
//							 {
//								 classR = 255;
//								 classG = 252;
//								 classB = 50;
//							 }
//
//							 for (int j = 0; j < n_k[k]; j++)
//							 {
//								 int index = clusters_elements[k][j];
//
//								 buffer[index * 3] = classR;//Red
//								 buffer[index * 3 + 1] = classG;//Green
//								 buffer[index * 3 + 2] = classB;//Blue
//
//							 }
//						 }

						
					 }
					 
					 ////###////###/////####

					 break;
				 }
			 }

}

private: UCHAR* SwapBGRtoRGB(UCHAR* bufferBGR)
{
			 UCHAR* bufferRGB = new UCHAR[size];

			 for (int i = 0; i < size; i += 3)
			 {
				 int B = bufferBGR[i];
				 int G = bufferBGR[i + 1];
				 int R = bufferBGR[i + 2];

				 bufferRGB[i] = R;
				 bufferRGB[i + 1] = G;
				 bufferRGB[i + 2] = B;

			 }

			 return bufferRGB;
}

private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {
}
		

private: System::Void buttonAdditive_Click(System::Object^  sender, System::EventArgs^  e) {
//			 Another  –  rather  simple  –  shadow  removal  technique  was  an  additive  correction  of  the  color
//				 intensities in the shadow area.We computed the average pixel intensities in the shadow and lit areas of
//				 the image(let’s call them ⴬띰띰띰띰띰띰 and ⴬뒠뒠뒠) and added this difference to the pixels in the shadow areas.


//			 //convert to YCbCr;
//			 RGBtoYCbCr();
//
//			 //FIND Shadow Mask
//			 CalcShadowMask();
//			 saveMaskBMP();
//			 ShowMaskBmp();
//
//
//			 //Begin Additive
//			 //
//			 YCbCrtoRGB();

			 float R = 0;
			 float G = 0;
			 float B = 0;

			 float RS = 0;
			 float GS = 0;
			 float BS = 0;

			 float intensity = 0;
			 float intensityS = 0;

			 int nShadow = 0;
			 int nNonShadow = 0;

			 for (int i = 0; i < size; i += 3)
			 {
				 if (shadowMask[i] == 255){
					 RS += buffer[i];
					 GS += buffer[i + 1];
					 BS += buffer[i + 2];

					 nShadow++;
				 }
				 else{
					 R += buffer[i];
					 G += buffer[i + 1];
					 B += buffer[i + 2];

					 nNonShadow++;
				 }
			 }

			 intensity = (R + G + B) / (3 * nNonShadow);
			 intensityS = (RS + GS + BS) / (3 * nShadow);

			 R = R / nNonShadow;
			 G = G / nNonShadow;
			 B = B / nNonShadow;

			 RS = RS / nShadow;
			 GS = GS / nShadow;
			 BS = BS / nShadow;

			 float diffR = R - RS;
			 float diffG = G - GS;
			 float diffB = B - BS;

			 float diffIntensity = intensity - intensityS;

			 float ratioR = R / RS;
			 float ratioG = G / GS;
			 float ratioB = B / BS;

			 for (int i = 0; i < size; i += 3)
			 {
				 if (shadowMask[i] == 255){

//					 buffer[i] += diffR;
//					 buffer[i + 1] += diffG;
//					 buffer[i + 2] += diffB;

					 int currR = buffer[i];
					 int currG = buffer[i + 1];
					 int currB = buffer[i + 2];

					 currR += diffR;
					 currG += diffG;
					 currB += diffB;

					 currR = currR > 255 ? 255 : (currR < 0 ? 0 : currR);
					 currG = currG > 255 ? 255 : (currG < 0 ? 0 : currG);
					 currB = currB > 255 ? 255 : (currB < 0 ? 0 : currB);

					 buffer[i] = currR;//Red
					 buffer[i + 1] = currG;//Green
					 buffer[i + 2] = currB;//Blue
				 }
			 }

			 SaveBMP();
			 ShowBmp();

			 return;

			 //End Addititve

}

private: System::Void buttonBasicLightModel_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 //convert to YCbCr;
//			 RGBtoYCbCr();
//
//			 //FIND Shadow Mask
//			 CalcShadowMask();
//			 saveMaskBMP();
//			 ShowMaskBmp();
//
//			 YCbCrtoRGB();

			 float R = 0;
			 float G = 0;
			 float B = 0;

			 float RS = 0;
			 float GS = 0;
			 float BS = 0;

			 float intensity = 0;
			 float intensityS = 0;

			 int nShadow = 0;
			 int nNonShadow = 0;

			 for (int i = 0; i < size; i += 3)
			 {
				 if (shadowMask[i] == 255){
					 RS += buffer[i];
					 GS += buffer[i + 1];
					 BS += buffer[i + 2];

					 nShadow++;
				 }
				 else{
					 R += buffer[i];
					 G += buffer[i + 1];
					 B += buffer[i + 2];

					 nNonShadow++;
				 }
			 }

			 intensity = (R + G + B) / (3 * nNonShadow);
			 intensityS = (RS + GS + BS) / (3 * nShadow);

			 R = R / nNonShadow;
			 G = G / nNonShadow;
			 B = B / nNonShadow;

			 RS = RS / nShadow;
			 GS = GS / nShadow;
			 BS = BS / nShadow;

			 float diffR = R - RS;
			 float diffG = G - GS;
			 float diffB = B - BS;

			 float diffIntensity = intensity - intensityS;

			 float ratioR = R / RS;
			 float ratioG = G / GS;
			 float ratioB = B / BS;

			 for (int i = 0; i < size; i += 3)
			 {
				 if (shadowMask[i] == 255){
					 //					 	buffer[i + 1] = buffer[i + 1] * ratioCb;
					 //					 	buffer[i + 2] = buffer[i + 2] * ratioCr;

//					 buffer[i] += diffR;
//					 buffer[i + 1] += diffG;
//					 buffer[i + 2] += diffB;

//					 buffer[i] *= ratioR;
//					 buffer[i + 1] *= ratioG;
//					 buffer[i + 2] *= ratioB;

					 int currR = buffer[i];
					 int currG = buffer[i + 1];
					 int currB = buffer[i + 2];

					 currR *= ratioR;
					 currG *= ratioG;
					 currB *= ratioB;

					 currR = currR > 255 ? 255 : (currR < 0 ? 0 : currR);
					 currG = currG > 255 ? 255 : (currG < 0 ? 0 : currG);
					 currB = currB > 255 ? 255 : (currB < 0 ? 0 : currB);

					 buffer[i] = currR;//Red
					 buffer[i + 1] = currG;//Green
					 buffer[i + 2] = currB;//Blue
				 }
			 }

			 SaveBMP();
			 ShowBmp();

			 return;
}

private: System::Void buttonAdvancedLightModel_Click(System::Object^  sender, System::EventArgs^  e) {

			 //convert to YCbCr;
//			 RGBtoYCbCr();
//
//			 //FIND Shadow Mask
//			 CalcShadowMask();
//			 saveMaskBMP();
//			 ShowMaskBmp();
//
//			 YCbCrtoRGB();

			 float R = 0;
			 float G = 0;
			 float B = 0;

			 float RS = 0;
			 float GS = 0;
			 float BS = 0;

			 float intensity = 0;
			 float intensityS = 0;

			 int nShadow = 0;
			 int nNonShadow = 0;

			 for (int i = 0; i < size; i += 3)
			 {
				 if (shadowMask[i] == 255){
					 RS += buffer[i];
					 GS += buffer[i + 1];
					 BS += buffer[i + 2];

					 nShadow++;
				 }
				 else{
					 R += buffer[i];
					 G += buffer[i + 1];
					 B += buffer[i + 2];

					 nNonShadow++;
				 }
			 }

			 intensity = (R + G + B) / (3 * nNonShadow);
			 intensityS = (RS + GS + BS) / (3 * nShadow);

			 R = R / nNonShadow;
			 G = G / nNonShadow;
			 B = B / nNonShadow;

			 RS = RS / nShadow;
			 GS = GS / nShadow;
			 BS = BS / nShadow;

			 float diffR = R - RS;
			 float diffG = G - GS;
			 float diffB = B - BS;

			 float diffIntensity = intensity - intensityS;

			 float ratioR = R / RS - 1;
			 float ratioG = G / GS - 1;
			 float ratioB = B / BS - 1;

			 for (int i = 0; i < size; i += 3)
			 {
				 if (shadowMask[i] == 255){
					 //					 	buffer[i + 1] = buffer[i + 1] * ratioCb;
					 //					 	buffer[i + 2] = buffer[i + 2] * ratioCr;

					 //					 buffer[i] += diffR;
					 //					 buffer[i + 1] += diffG;
					 //					 buffer[i + 2] += diffB;

					 //					 buffer[i] *= ratioR;
					 //					 buffer[i + 1] *= ratioG;
					 //					 buffer[i + 2] *= ratioB;

					 int currR = buffer[i];
					 int currG = buffer[i + 1];
					 int currB = buffer[i + 2];

					 currR = (ratioR + 1) / (0 * ratioR + 1)*currR;
					 currG = (ratioG + 1) / (0 * ratioG + 1)*currG;
					 currB = (ratioB + 1) / (0 * ratioB + 1)*currB;

					 currR = currR > 255 ? 255 : (currR < 0 ? 0 : currR);
					 currG = currG > 255 ? 255 : (currG < 0 ? 0 : currG);
					 currB = currB > 255 ? 255 : (currB < 0 ? 0 : currB);

					 buffer[i] = currR;//Red
					 buffer[i + 1] = currG;//Green
					 buffer[i + 2] = currB;//Blue
				 }
			 }

			 SaveBMP();
			 ShowBmp();

			 return;
}

private: System::Void buttonYCbCr_Click(System::Object^  sender, System::EventArgs^  e) {


			 //convert to YCbCr;
			 RGBtoYCbCr();

//			 //FIND Shadow Mask
////			 CalcShadowMask();
//			  
//			 ////////////
//			 shadowMask = new UCHAR[size];
//			 //mask to 0
//			 for (int i = 0; i < size; i += 3)
//			 {
//				 shadowMask[i] = 0;
//				 shadowMask[i + 1] = 0;
//				 shadowMask[i + 2] = 0;
//			 }
//
//			 int maxa, maxb;
//			 int height = InfoHeader.biHeight;
//			 int width = InfoHeader.biWidth;
//			 int step = width*3;
//			 int channels = 3;
//
//			 UCHAR *data = buffer;// (uchar *)original->imageData;
//			 UCHAR *datam = shadowMask;// (uchar *)mask->imageData; MASK
//			 int stepm = width * 3;// mask->widthStep;
//			 //color* orig = new color[step*height];
//
//			 double fullaverage = 0;
//			 int a, b;
//			 double average;
//			 int count;
//
//			 //calc fullaverage
//			 //Computing the average at Y channel 
//			 float averageY = 1;
//			 float sum = 0;
//			 for (int i = 0; i < size; i += 3)
//			 {
//				 int Y = buffer[i];
//				 sum += Y;
//			 }
//			 averageY = sum / (float)(size / 3.0);
//			 fullaverage = averageY;
//
//			for (int window = 81; window > 3; window -= 16){
//			//for (int window = 36; window > 3; window -= 3){
//				maxa = maxb = window;
//
//				//				 for (int j = 0; j<height; j++){
//				//					 for (int i = 0; i<width; i++){
//				for (int i = 0; i<size; i += 1){
//
//					average = 0.;
//					count = 0;
//
//					//
//					//printf("3");
//					//						 for (a = 0; a<maxa; a++){
//					//							 for (b = 0; b<maxb; b++){
//					for (a = 0; a<maxa; a += 1){
//						for (b = 0; b<maxb; b += 1){
//
//
//							//							 int heightIndex = (i + a) / width;
//							//							 int widthIndex = ((i + b) % width);
//
//							int heightIndex = i / width + b;
//							int widthIndex = i%width + a;
//
//							//if ((j + a)<height && (i + b)<width){
//							if (heightIndex < height && widthIndex < width){
//
//								//int index1 = (j + a)*stepm + (i + b);
//								//int index1 = ((i + a) / width)*width + ((i + b) % width);
//
//								//int index1 = heightIndex + widthIndex;
//								int index1 = heightIndex*width * 3 + widthIndex * 3;
//
//								if (datam[index1] == 0){
//									// average += orig[(j + a)*step + (i + b)].y;
//									// int index2 = (j + a)*step + (i + b);
//									//int index2 = ((i + a) / width)*width + ((i + b) % width);
//									int index2 = heightIndex*width * 3 + widthIndex * 3;
//									average += buffer[index2];
//									count++;
//
//									if (index2 % 3 != 0)
//										int tyu = 0;
//								}
//							}
//						}
//					}
//
//					average /= count;
//					//
//					for (a = 0; a<maxa; a++){
//						for (b = 0; b<maxb; b++){
//
//							//								 int heightIndex = (i + a) / width;
//							//								 int widthIndex = ((i + b) % width);
//
//							int heightIndex = i / width + b;
//							int widthIndex = i%width + a;
//
//							int index = heightIndex*width * 3 + widthIndex * 3;
//
//							//if ((j + a)<height && (i + b)<width){
//							if (heightIndex < height && widthIndex < width){
//
//								//if (fullaverage*0.6>orig[(j + a)*step + (i + b)].y){
//								//if (fullaverage*0.6 > buffer[(j + a)*step + (i + b)]){
//								//if (fullaverage*0.6 > buffer[heightIndex*width + widthIndex]){
//								if (fullaverage*0.6 > buffer[index]){
//									//datam[(j + a)*stepm + (i + b)] = 255;
//									//datam[heightIndex*width + widthIndex] = 255;
//									datam[index] = 255;
//									datam[index + 1] = 255;
//									datam[index + 2] = 255;
//									//data[(j + a)*step + (i + b)*channels + 1] = 255;
//								}
//								else{
//									//if (average*0.6>orig[(j + a)*step + (i + b)].y){
//									// if (average*0.6 > buffer[(j + a)*step + (i + b)]){
//									//if (average*0.6 > buffer[heightIndex*width + widthIndex]){
//									if (average*0.8 > buffer[index]){
//										//if (datam[heightIndex*width + widthIndex] == 0){
//										if (datam[index] == 0){
//											//datam[heightIndex*width + widthIndex] = 255;
//											datam[index] = 255;
//											datam[index + 1] = 255;
//											datam[index + 2] = 255;
//											//data[(j + a)*step + (i + b)*channels + 2] = 255;
//										}
//									}
//								}
//
//							}
//
//						}
//					}
//
//					//}
//				}
//
//			}
//
//			 ///////////
//
//			 saveMaskBMP();
//			 ShowMaskBmp();
//
//			 //YCbCrtoRGB();
//
////			 SaveBMP();
////			 ShowBmp();
//
//			 //return;
//
//			 //YCbCrtoRGB();

			 float R = 0;
			 float G = 0;
			 float B = 0;

			 float RS = 0;
			 float GS = 0;
			 float BS = 0;

			 float intensity = 0;
			 float intensityS = 0;

			 int nShadow = 0;
			 int nNonShadow = 0;

			 for (int i = 0; i < size; i += 3)
			 {
				 if (shadowMask[i] == 255){
					 RS += buffer[i];
					 GS += buffer[i + 1];
					 BS += buffer[i + 2];

					 nShadow++;
				 }
				 else{
					 R += buffer[i];
					 G += buffer[i + 1];
					 B += buffer[i + 2];

					 nNonShadow++;
				 }
			 }

			 intensity = (R + G + B) / (3 * nNonShadow);
			 intensityS = (RS + GS + BS) / (3 * nShadow);

			 R = R / nNonShadow;
			 G = G / nNonShadow;
			 B = B / nNonShadow;

			 RS = RS / nShadow;
			 GS = GS / nShadow;
			 BS = BS / nShadow;

			 float diffR = R - RS;
			 float diffG = G - GS;
			 float diffB = B - BS;

			 float diffIntensity = intensity - intensityS;

			 float ratioR = R / RS;
			 float ratioG = G / GS;
			 float ratioB = B / BS;

			 for (int i = 0; i < size; i += 3)
			 {
				 if (shadowMask[i] == 255){

					 int currR = buffer[i];
					 int currG = buffer[i + 1];
					 int currB = buffer[i + 2];

//					 res_ycbcr(:, : , 1) = ycbcr(:, : , 1) + mask * diff_y;
//					 res_ycbcr(:, : , 2) = ycbcr(:, : , 2).*(1 - mask) + mask.*ratio_cb.*ycbcr(:, : , 2);
//					 res_ycbcr(:, : , 3) = ycbcr(:, : , 3).*(1 - mask) + mask.*ratio_cr.*ycbcr(:, : , 3);

					 currR = currR + 1 * diffR;
					 //currR = ratioR*currR;
					 currG = currG*(1 - 1) + 1 * ratioG*currG;
					 currB = currB*(1 - 1) + 1 * ratioB*currB;

					 currR = currR > 255 ? 255 : (currR < 0 ? 0 : currR);
					 currG = currG > 255 ? 255 : (currG < 0 ? 0 : currG);
					 currB = currB > 255 ? 255 : (currB < 0 ? 0 : currB);

					 buffer[i] = currR;//Red
					 buffer[i + 1] = currG;//Green
					 buffer[i + 2] = currB;//Blue
				 }
			 }

			 YCbCrtoRGB();

			 SaveBMP();
			 ShowBmp();

			 return;
}

private: System::Void pictureBox3_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (OPEN)
			 {
				 ShowMaskBmp();
			 }
}


private: System::Void buttonShadow0YCbCr_Click(System::Object^  sender, System::EventArgs^  e) {

			 //convert to YCbCr;
			 RGBtoYCbCr();

			 //FIND Shadow Mask
			 CalcShadowMask();
			 saveMaskBMP();
			 ShowMaskBmp();

			 YCbCrtoRGB();
}

private: System::Void buttonShadow1_Click(System::Object^  sender, System::EventArgs^  e) {

			 shadowMask = new UCHAR[size];
			 float * bufferHSV = new float[size];

			 //Mat imageShadow = image.clone();

			 int iW = InfoHeader.biWidth;
			 int iH = InfoHeader.biHeight;

			 //Mat imgTmp = imageShadow.clone();

			 //unsigned char* dataTmp = imgTmp.data;

			 //unsigned char* data = imageShadow.data;
			 unsigned char* data = buffer;

			// int channel = imageShadow.channels();
			 int channel = 3;

			 //for (int i = 5; i< iH - 5; i++) //
			 for (int i = 0; i < size; i += 3) //
			 {
				 //for (int j = 5; j< iW - 5; j++)
				 for (int j = 0; j == 0; j++)
				 {
					 //					 int B = data[channel*(i*iW + j)];
					 //					 int G = data[channel*(i*iW + j) + 1];
					 //					 int R = data[channel*(i*iW + j) + 2];

					 int B = data[i];
					 int G = data[i + 1];
					 int R = data[i + 2];

					 float H;
					 float S;
					 float V;

					 //Convert RGB to HSV
					 float var_R = (R / 255.0);                    //RGB from 0 to 255
					 float var_G = (G / 255.0);
					 float var_B = (B / 255.0);

					 //					 float var_Min = MIN(MIN(var_R, var_G), var_B);  //Min. value of RGB
					 //					 float   var_Max = MAX(MAX(var_R, var_G), var_B);  //Max. value of RGB
					 //					 float   del_Max = var_Max - var_Min;       //Delta RGB value 

					 //float   var_Min = min(min(var_R, var_G), var_B);  //Min. value of RGB
					 float   var_Min = std::min<float>(std::min<float>(var_R, var_G), var_B);  //Min. value of RGB
					 //float   var_Max = max(max(var_R, var_G), var_B);  //Max. value of RGB
					 float   var_Max = std::max<float>(std::max<float>(var_R, var_G), var_B);
					 float   del_Max = var_Max - var_Min;       //Delta RGB value 
					 
					 V = var_Max;

					 if (del_Max == 0)                     //This is a gray, no chroma...
					 {
						 H = 0;                              //HSV results from 0 to 1
						 S = 0;
					 }
					 else                                    //Chromatic data...
					 {
						 S = del_Max / var_Max;

						 float del_R = (((var_Max - var_R) / 6) + (del_Max / 2)) / del_Max;
						 float del_G = (((var_Max - var_G) / 6) + (del_Max / 2)) / del_Max;
						 float del_B = (((var_Max - var_B) / 6) + (del_Max / 2)) / del_Max;

						 if (var_R == var_Max)
							 H = del_B - del_G;
						 else if (var_G == var_Max)
							 H = (1. / 3.) + del_R - del_B;
						 else if (var_B == var_Max)
							 H = (2. / 3.) + del_G - del_R;

						 if (H < 0) H += 1;
						 if (H > 1) H -= 1;
					 }

					 bufferHSV[i] = H;
					 bufferHSV[i + 1] = S;
					 bufferHSV[i + 2] = V;

				 }
			 }

			 float Vavg = 0;
			 float Savg = 0;
			 int countV = 0;
			 for (int i = 0; i < size; i += 3) //
			 {
				 Vavg += bufferHSV[i];
				 Savg += bufferHSV[i + 1];
				 countV++;
			 }
			 Vavg /= countV;
			 Savg /= countV;

			 for (int i = 0; i < size; i += 3) //
			 {
				 float H = bufferHSV[i];
				 float S = bufferHSV[i + 1];
				 float V = bufferHSV[i + 2];

				 //fullaverage*0.6 > buffer[index]

					 //if(V>0.3 && V<0.85 && H<85 && S<0.15)
					 //if (V>0.3 && V<0.95 &&  S<0.2)
				 if (V > Vavg && S > Savg*0.3)
					 {
//						 data[channel*(i*iW + j)] = 0;// dataTmp[channel*(i*iW+j)];
//						 data[channel*(i*iW + j) + 1] = 0;// dataTmp[channel*(i*iW+j)+1];
//						 data[channel*(i*iW + j) + 2] = 0;// dataTmp[channel*(i*iW+j)+2];

						 shadowMask[i] = 0;// dataTmp[channel*(i*iW+j)];
						 shadowMask[i + 1] = 0;// dataTmp[channel*(i*iW+j)+1];
						 shadowMask[i + 2] = 0;// dataTmp[channel*(i*iW+j)+2];
					 }
					 else
					 {
//						 data[channel*(i*iW + j)] = 255;
//						 data[channel*(i*iW + j) + 1] = 255;
//						 data[channel*(i*iW + j) + 2] = 255;

						 shadowMask[i] = 255;
						 shadowMask[i + 1] = 255;
						 shadowMask[i + 2] = 255;
					 }
			 }


			 saveMaskBMP();
			 ShowMaskBmp();

}



private: System::Void button1Shadow2Lab_Click(System::Object^  sender, System::EventArgs^  e) {

//			 //Custom To LAB
//			 UCHAR* RGBbuffer = SwapBGRtoRGB(buffer);
//
//			 double *bufferXYZ = RGBtoXYZ(RGBbuffer);
//			 double *bufferCIELAB = XYZtoCIELAB(bufferXYZ);
//
//			 shadowMask = new UCHAR[size];
//
//			 double CIE_L_avg = 0;
//			 double CIE_A_avg = 0;
//			 double CIE_B_avg = 0;
//
//			 int count = 0;
//
//			 double CIE_L_min = 255;
//			 double CIE_A_min = 255;
//			 double CIE_B_min = 255;
//
//			 double CIE_L_max = 0;
//			 double CIE_A_max = 0;
//			 double CIE_B_max = 0;
//
//			 for (int i = 0; i < size; i += 3) //
//			 {
//				 double CIE_L = bufferCIELAB[i];
//				 double CIE_A = bufferCIELAB[i + 1];
//				 double CIE_B = bufferCIELAB[i + 2];
//
//				 //CIE_L = CIE_L < 0 ? 0 : CIE_L;
//
//				 CIE_L_avg += CIE_L;
//				 CIE_A_avg += CIE_A;
//				 CIE_B_avg += CIE_B;
//
//				 count += 1;
//
//				 CIE_L_min = CIE_L < CIE_L_min ? CIE_L : CIE_L_min;
//				 CIE_A_min = CIE_A < CIE_A_min ? CIE_A : CIE_A_min;
//				 CIE_B_min = CIE_B < CIE_B_min ? CIE_B : CIE_B_min;
//
//				 CIE_L_max = CIE_L > CIE_L_max ? CIE_L : CIE_L_max;
//				 CIE_A_max = CIE_A > CIE_A_max ? CIE_A : CIE_A_max;
//				 CIE_B_max = CIE_B > CIE_B_max ? CIE_B : CIE_B_max;
//			 }
//
//			 CIE_L_avg /= count;
//			 CIE_A_avg /= count;
//			 CIE_B_avg /= count;
//
//			 //standart deviation for L
//			 double stdDevL = 0;
//			 for (int i = 0; i < size; i += 3) //
//			 {
//				 double CIE_L = bufferCIELAB[i];
//				 //CIE_L = CIE_L < 0 ? 0 : CIE_L;
//
//				 stdDevL += pow(CIE_L - CIE_L_avg, 2);
//			 }
//			 stdDevL = stdDevL*(1.0 / ((double)count - 1.0));
//			 stdDevL = sqrt(stdDevL);
//
//			 for (int i = 0; i < size; i += 3) //
//			 {
//				 double CIE_L = bufferCIELAB[i];
//				 double CIE_A = bufferCIELAB[i + 1];
//				 double CIE_B = bufferCIELAB[i + 2];
//
//				// CIE_L = CIE_L < 0 ? 0 : CIE_L;
//				
//				 if (CIE_A_avg + CIE_B_avg <= 256)
//				 {
//					 if (CIE_L <= (CIE_L_avg - stdDevL / 3.0))
//					 {
//						 shadowMask[i] = 255;
//						 shadowMask[i + 1] = 255;
//						 shadowMask[i + 2] = 255;
//					 }
//					 else
//					 {
//						 shadowMask[i] = 0;
//						 shadowMask[i + 1] = 0;
//						 shadowMask[i + 2] = 0;
//					 }
//				 }
//				 else
//				 {
//					 if (CIE_L < CIE_L_avg && CIE_B < CIE_B_avg )
//					 {
//						 shadowMask[i] = 255;
//						 shadowMask[i + 1] = 255;
//						 shadowMask[i + 2] = 255;
//					 }
//					 else
//					 {
//						 shadowMask[i] = 0;
//						 shadowMask[i + 1] = 0;
//						 shadowMask[i + 2] = 0;
//					 }
//				 }
//			 }

			//OpenCV To LAB
			cv::Mat imgBGRforDetectMat = cv::imread(myPath_char);
			cv::Mat imgLABforDetectMat;
			//CopyArrayToMat(shadowMask, shadowMaskMat);
			cv::cvtColor(imgBGRforDetectMat, imgLABforDetectMat, CV_BGR2Lab);

			UCHAR *bufferCIELAB = new UCHAR[size];
			CopyMatToArray(imgLABforDetectMat, bufferCIELAB);

			shadowMask = new UCHAR[size];

			double CIE_L_avg = 0;
			double CIE_A_avg = 0;
			double CIE_B_avg = 0;

			int count = 0;

			double CIE_L_min = 255;
			double CIE_A_min = 255;
			double CIE_B_min = 255;

			double CIE_L_max = 0;
			double CIE_A_max = 0;
			double CIE_B_max = 0;

			for (int i = 0; i < size; i += 3) //
			{
				double CIE_L = bufferCIELAB[i];
				double CIE_A = bufferCIELAB[i + 1];
				double CIE_B = bufferCIELAB[i + 2];

//				CIE_L = (CIE_L * 100) / 255.0;
//				CIE_A = CIE_A - 128;
//				CIE_B = CIE_B - 128;

				//CIE_L = CIE_L < 0 ? 0 : CIE_L;

				CIE_L_avg += CIE_L;
				CIE_A_avg += CIE_A;
				CIE_B_avg += CIE_B;

				count += 1;

				CIE_L_min = CIE_L < CIE_L_min ? CIE_L : CIE_L_min;
				CIE_A_min = CIE_A < CIE_A_min ? CIE_A : CIE_A_min;
				CIE_B_min = CIE_B < CIE_B_min ? CIE_B : CIE_B_min;

				CIE_L_max = CIE_L > CIE_L_max ? CIE_L : CIE_L_max;
				CIE_A_max = CIE_A > CIE_A_max ? CIE_A : CIE_A_max;
				CIE_B_max = CIE_B > CIE_B_max ? CIE_B : CIE_B_max;
			}

			CIE_L_avg /= count;
			CIE_A_avg /= count;
			CIE_B_avg /= count;

			//standart deviation for L
			double stdDevL = 0;
			for (int i = 0; i < size; i += 3) //
			{
				double CIE_L = bufferCIELAB[i];

				//CIE_L = (CIE_L * 100) / 255.0;

				stdDevL += pow(CIE_L - CIE_L_avg, 2);
			}
			stdDevL = stdDevL*(1.0 / ((double)count - 1.0));
			stdDevL = sqrt(stdDevL);

			for (int i = 0; i < size; i += 3) //
			{
				double CIE_L = bufferCIELAB[i];
				double CIE_A = bufferCIELAB[i + 1];
				double CIE_B = bufferCIELAB[i + 2];

//				CIE_L = (CIE_L * 100) / 255.0;
//				CIE_A = CIE_A - 128;
//				CIE_B = CIE_B - 128;

				// CIE_L = CIE_L < 0 ? 0 : CIE_L;

				if (CIE_A_avg + CIE_B_avg >= 256)//256
				{
					if (CIE_L <= (CIE_L_avg - stdDevL / 3.0))
					{
						shadowMask[i] = 255;
						shadowMask[i + 1] = 255;
						shadowMask[i + 2] = 255;
					}
					else
					{
						shadowMask[i] = 0;
						shadowMask[i + 1] = 0;
						shadowMask[i + 2] = 0;
					}
				}
				else
				{
					if (CIE_L < CIE_L_avg && CIE_B < CIE_B_avg)
					{
						shadowMask[i] = 255;
						shadowMask[i + 1] = 255;
						shadowMask[i + 2] = 255;
					}
					else
					{
						shadowMask[i] = 0;
						shadowMask[i + 1] = 0;
						shadowMask[i + 2] = 0;
					}
				}
			}

			delete bufferCIELAB;

			 cv::Mat shadowMaskMat = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth,CV_8UC3);
			 cv::Mat shadowMaskClosingMat;
			 cv::Mat shadowMaskOpeningMat;
			 cv::Mat shadowMaskOpeningClosingMat;
			 cv::Mat shadowMaskClosingOpeningMat;
			 cv::Mat tmp;
			 cv::Mat thresholdFixed;
			 cv::Mat thresholdAdaptive;
			 cv::Mat areaThresholdMat;
			 cv::Mat shadowMaskErosionFollowedByDilation;
			 cv::Mat shadowMaskDilationFollowedByErosion;

			 CopyArrayToMat(shadowMask, shadowMaskMat);

			 //Area-based thresholding
			 ////////////////////
			 int height = shadowMaskMat.rows;
			 int width = shadowMaskMat.cols;

			 areaThresholdMat = shadowMaskMat.clone();

			 int maxa, maxb;
			 int a, b;

			 int window = 9;
			 int window_pixels_amount = window*window;
			 maxa = maxb = window;

			 //Move slide window and calc amount of shadow and non shadow pixels in it
			 for (int i = 0; i < shadowMaskMat.rows; i += window) {
				 for (int j = 0; j < shadowMaskMat.cols; j += window) {

					 int count_shadow_pixels = 0;
					 int count_non_shadow_pixels = 0;
					 int newValue = 0;
					 for (a = 0; a < maxa; a++){
						 for (b = 0; b<maxb; b++){
							 if ((i + a) < height && (j + b) < width){
								 cv::Vec3b &shadowMaskPixel = shadowMaskMat.at<cv::Vec3b>(i + a, j + b);
								 if (shadowMaskPixel.val[0] == 255)
									 count_shadow_pixels += 1;
								 else
									 count_non_shadow_pixels += 1;

								 //if (a != 0 ||  b != 0)
									 newValue += shadowMaskPixel.val[0];
							 }
						 }
					 }
					 
					 cv::Vec3b &shadowMaskPixel = areaThresholdMat.at<cv::Vec3b>(i, j);

					 newValue -= shadowMaskPixel.val[0];
					 newValue = newValue == 255 * (window - 1) ? 255 : 0;

					 shadowMaskPixel.val[0] = newValue;
					 shadowMaskPixel.val[1] = newValue;
					 shadowMaskPixel.val[2] = newValue;

					 //
					 //if (count_shadow_pixels < window_pixels_amount*0.2)
//					 if (count_shadow_pixels < window_pixels_amount*0.1)
//					 {
//						 for (a = 0; a < maxa; a++){
//							 for (b = 0; b<maxb; b++){
//								 if ((i + a) < height && (j + b) < width){
//									 cv::Vec3b &shadowMaskPixel = areaThresholdMat.at<cv::Vec3b>(i + a, j + b);
//									 shadowMaskPixel.val[0] = 0;
//									 shadowMaskPixel.val[1] = 0;
//									 shadowMaskPixel.val[2] = 0;
//								 }
//							 }
//						 }
//					 }

					 

				 }
			 }
			//////////////////

			 //// Apply Closing
			 cv::Mat const structure_elem = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(5, 5));
			 cv::morphologyEx(shadowMaskMat, shadowMaskClosingMat,
				 cv::MORPH_CLOSE, structure_elem);

			 //// Apply Opening
			 cv::Mat const structure_elem2 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(5, 5));
			 cv::morphologyEx(shadowMaskMat, shadowMaskOpeningMat,
				 cv::MORPH_OPEN, structure_elem2);

			 //// Apply Opening Followed By Closing
			 cv::Mat const structure_elem3 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(3, 3));
			 cv::Mat const structure_elem4 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(7, 7));
			 cv::Mat const structure_elem444 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(3, 3));
			 cv::morphologyEx(shadowMaskMat, tmp,
				 cv::MORPH_OPEN, structure_elem3);
			 cv::morphologyEx(tmp, shadowMaskOpeningClosingMat,
				 cv::MORPH_CLOSE, structure_elem444);

			 //// Apply Closing  Followed By Opening
			 cv::Mat const structure_elem33 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(5, 5));
			 cv::Mat const structure_elem44 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(5, 5));
			 cv::morphologyEx(tmp, shadowMaskClosingOpeningMat,
				 cv::MORPH_CLOSE, structure_elem33);
			 cv::morphologyEx(shadowMaskMat, tmp,
				 cv::MORPH_OPEN, structure_elem44);
			 

			 // Apply Erosion  Followed By Dilation 
			 cv::Mat elementEr = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(9, 9));
			 cv::Mat elementDil = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(11, 11));
			 cv::erode(shadowMaskMat, tmp, elementEr);
			 cv::dilate(tmp, shadowMaskErosionFollowedByDilation, elementDil);

			 // Apply Dilation Followed By Erosion
			 cv::Mat elementDil2 = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(3, 3));
			 cv::Mat elementEr2 = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(7, 7));
			 cv::dilate(shadowMaskMat, tmp, elementDil2);
			 cv::erode(tmp, shadowMaskDilationFollowedByErosion, elementEr2);
			 


			 cv::imshow("shadowMaskMat", shadowMaskMat);
			 cv::imshow("shadowMaskClosingMat", shadowMaskClosingMat);
			 cv::imshow("shadowMaskOpeningMat", shadowMaskOpeningMat);
			 cv::imshow("shadowMaskOpeningClosingMat", shadowMaskOpeningClosingMat);
			 cv::imshow("shadowMaskClosingOpeningMat", shadowMaskClosingOpeningMat);
			 cv::imshow("areaThresholdMat", areaThresholdMat);
			 cv::imshow("ErosionFollowedByDilation", shadowMaskErosionFollowedByDilation);
			 cv::imshow("DilationFollowedByErosion", shadowMaskDilationFollowedByErosion);

			 //CopyMatToArray(shadowMaskErosionFollowedByDilation, shadowMask);

			 saveMaskBMP();
			 ShowMaskBmp();
}

private: System::Void button11RemveLab_Click(System::Object^  sender, System::EventArgs^  e) {
			
//			 textBoxSpatialRadius->Text = System::Convert::ToString(spatial_radius_MEAN_SHIFT);
//			 textBoxColorRadius->Text = System::Convert::ToString(color_radius_MEAN_SHIFT);
//
//			 spatial_radius_MEAN_SHIFT = System::Convert::ToInt32(textBoxSpatialRadius->Text);
//			 color_radius_MEAN_SHIFT = System::Convert::ToInt32(textBoxColorRadius->Text);

			 cv::Mat imgBGR;
			 cv::Mat imgBGRres;
			 cv::Mat imgLAB;
			 cv::Mat imgLAB_ORIGIN;
			 cv::Mat imgKMeansRes;
			 cv::Mat imgBGRbeforeCluster;
			 cv::Mat shadowMaskMat = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth,CV_8UC3);

			 imgBGR = cv::imread(myPath_char);
			 
			 //Проверки на размер - если ширина не кратная 4, то дополняется мусором
			 /////////////////////////////////////////////////////////////////////////
			 int biWidth = InfoHeader.biWidth;
			 int biHeight = InfoHeader.biHeight;

			 int biWidth_add = biWidth % 4;

			 int cols = imgBGR.cols;
			 int rows = imgBGR.rows;

			 int sizeB = size;
			 int sizeB2 = (biWidth * 3)*biHeight;
			 int sizeB3 = (biWidth * 3 + biWidth % 4)*biHeight;
			 int size2 = imgBGR.rows*imgBGR.cols*imgBGR.channels();
			 /////////////////////////////////////////////////////////////////////////////

			 //Copy shadw mask to Mat
			 CopyArrayToMat(shadowMask, shadowMaskMat);

			 //Convert to LAB
			 cv::cvtColor(imgBGR, imgLAB, CV_BGR2Lab);
			 cv::cvtColor(imgBGR, imgLAB_ORIGIN, CV_BGR2Lab);

			 //Calc intensity average values
			 double CIE_L_avg_shadow = 0;
			 double CIE_A_avg_shadow = 0;
			 double CIE_B_avg_shadow = 0;

			 double CIE_L_avg_non_shadow = 0;
			 double CIE_A_avg_non_shadow = 0;
			 double CIE_B_avg_non_shadow = 0;

			 double CIE_L_avg_img = 0;

			 int count_shadow = 0;
			 int count_non_shadow = 0;
			 int count_img= 0;

			 int step = imgLAB.step;
			 int channels = imgLAB.channels();
			 for (int i = 0; i < imgLAB.rows; i++) {
				 for (int j = 0; j < imgLAB.cols; j++) {

					 double raw_CIE_L = imgLAB.data[step*i + channels*j + 0]; //L*: 0-255 (elsewhere is represented by 0 to 100)	
					 double raw_CIE_A = imgLAB.data[step*i + channels*j + 1]; //L*: 0-255 (elsewhere is represented by 0 to 100)	
					 double raw_CIE_B = imgLAB.data[step*i + channels*j + 2]; //L*: 0-255 (elsewhere is represented by 0 to 100)	

					 //double CIE_L = (raw_CIE_L * 100) / 255.0;
					 double CIE_L = raw_CIE_L;
					 double CIE_A = raw_CIE_A;
					 double CIE_B = raw_CIE_B;

					 cv::Vec3b &shadowMaskPixel = shadowMaskMat.at<cv::Vec3b>(i, j);

					 if (shadowMaskPixel.val[0] == 255)
					 {
						 CIE_L_avg_shadow += CIE_L;
						 CIE_A_avg_shadow += CIE_A;
						 CIE_B_avg_shadow += CIE_B;
						 count_shadow += 1;
					 }
					 else
					 {
						 CIE_L_avg_non_shadow += CIE_L;
						 CIE_A_avg_non_shadow += CIE_A;
						 CIE_B_avg_non_shadow += CIE_B;
						 count_non_shadow += 1;
					 }
					 CIE_L_avg_img += CIE_L;
					 count_img += 1;
				 }
			 }
			 CIE_L_avg_shadow /= count_shadow;
			 CIE_A_avg_shadow /= count_shadow;
			 CIE_B_avg_shadow /= count_shadow;

			 CIE_L_avg_non_shadow /= count_non_shadow;
			 CIE_A_avg_non_shadow /= count_non_shadow;
			 CIE_B_avg_non_shadow /= count_non_shadow;

			 CIE_L_avg_img /= count_img;

			 //calc intensity diff
			 double L_diff = CIE_L_avg_non_shadow - CIE_L_avg_shadow;

			 double L_ratio = CIE_L_avg_non_shadow/CIE_L_avg_shadow;
			 double A_ratio = CIE_A_avg_non_shadow/CIE_A_avg_shadow;
			 double B_ratio = CIE_B_avg_non_shadow/CIE_B_avg_shadow;

			 //add diff to shadow pixels
			 for (int i = 0; i < imgLAB.rows; i++) {
				 for (int j = 0; j < imgLAB.cols; j++) {

					 cv::Vec3b &shadowMaskPixel = shadowMaskMat.at<cv::Vec3b>(i, j);
					 cv::Vec3b &imgLABPixel = imgLAB.at<cv::Vec3b>(i, j);
					 

					 if (shadowMaskPixel.val[0] == 255 && imgLABPixel.val[0] < CIE_L_avg_img){
						 int L = imgLABPixel.val[0];
//						 int A = imgLABPixel.val[1];
//						 int B = imgLABPixel.val[2];

						 //L+= L_diff;
						 //L *= L_ratio;

//						 A *= A_ratio;
//						 B *= B_ratio;

						 L = (L > 255 ? 255 : (L < 0 ? 0 : L));
//						 A = (A > 255 ? 255 : (A < 0 ? 0 : A));
//						 B = (B > 255 ? 255 : (B < 0 ? 0 : B));

						 imgLABPixel.val[0] = L;
//						 imgLABPixel.val[1] = A;
//						 imgLABPixel.val[2] = B;
					 } 
				 }
			 }

//			 cv::imshow("imgLAB", imgLAB);

			 cv::cvtColor(imgLAB, imgBGRbeforeCluster, CV_Lab2BGR);

//			 //Apply K_means
//			 CopyMatToArray(imgLAB, buffer);
//
////			 imgKMeansRes = imgBGR.clone();
////			 K_MeansLab(imgKMeansRes);
////			 cv::imshow("imgKMeansRes", imgKMeansRes);
//
//			 cv::Mat imgKMeansResVisual = imgBGR.clone();
//			 K_MeansLabByChrom(imgKMeansResVisual);
//			 cv::imshow("imgKMeansResVisual", imgKMeansResVisual);
//			 ///
//
//			 
//			 CopyArrayToMat(buffer, imgLAB);

//			 //Convert to BGR
//			 cv::cvtColor(imgLAB, imgBGRres, CV_Lab2BGR);
//			 CopyMatToArray(imgBGRres, buffer);

			 //Mean Shift  takes BGR and do in LAB, writes res in first param
			 cv::Mat imgMeanShiftVisual = imgBGR.clone();
			 cv::Mat imgForMeanShiftForCluster;
			 cv::Mat imgForMeanShiftForAlign;
			 cv::cvtColor(imgLAB, imgForMeanShiftForAlign, CV_Lab2BGR);
			 cv::cvtColor(imgLAB_ORIGIN, imgForMeanShiftForCluster, CV_Lab2BGR);
			 //cv::cvtColor(imgLAB, imgForMeanShiftForCluster, CV_Lab2BGR);
			 ApplyMeanShiftAndCorrections(imgForMeanShiftForCluster, imgForMeanShiftForAlign, imgMeanShiftVisual);
			 cv::imshow("imgMeanShiftVisual", imgMeanShiftVisual);
			 CopyMatToArray(imgForMeanShiftForAlign, buffer); //write result to buffer
			 imgBGRres = imgForMeanShiftForAlign.clone();

			 cv::imshow("imgBGR", imgBGR);
			 //cv::imshow("imgLAB", imgLAB);
			 cv::imshow("imgBGRRelight", imgBGRbeforeCluster);
			 cv::imshow("imgBGRres", imgBGRres);

//			 //
//			 //Process dark pixel on and near shadow edges
//			 //
//			 cv::Mat imgShadowMask = imgBGRres.clone();
//			 cv::Mat imgShadowMaskGRAY;
//			 cv::Mat imgEdge;
//			 cv::Mat imgEdgeDilated;
//			 CopyArrayToMat(shadowMask, imgShadowMask);
//			 cv::cvtColor(imgShadowMask, imgShadowMaskGRAY, CV_BGR2GRAY);
//
//			 cv::Canny(imgShadowMaskGRAY, imgEdge, 50, 150, 3);
//
//			 cv::Mat elementDil = getStructuringElement(cv::MORPH_RECT,
//				 cv::Size(5, 5));
//			 cv::dilate(imgEdge, imgEdgeDilated, elementDil);
//
//			 cv::Mat imgProcessEdgeDarkPixelsBGR = imgBGRres.clone();
//			 cv::Mat imgProcessEdgeDarkPixelsLAB = imgBGRres.clone();
//			 //cv::Mat imgLABres;
//			 cv::cvtColor(imgBGRres, imgProcessEdgeDarkPixelsLAB, CV_BGR2Lab);
//			 int DISTANCE = 10;
//			 for (int i = 0; i < imgProcessEdgeDarkPixelsLAB.rows; i++) {
//				 for (int j = 0; j < imgProcessEdgeDarkPixelsLAB.cols; j++) {
//
//					 UCHAR &shadowEdgePixel = imgEdgeDilated.at<UCHAR>(i, j);
//					 cv::Vec3b &pixel = imgProcessEdgeDarkPixelsLAB.at<cv::Vec3b>(i, j);
//					 int L = pixel.val[0];
//					 int A = pixel.val[1];
//					 int B = pixel.val[2];
//					 if (shadowEdgePixel == 255)
//					 {
//						 if (L < CIE_L_avg_non_shadow)
//						 {
//							 //L = CIE_L_avg_non_shadow - L;
//							 L = L + 40;
//							 A = CIE_A_avg_non_shadow - A;
//							 B = CIE_B_avg_non_shadow - B;
//
//							 L = (L > 255 ? 255 : (L < 0 ? 0 : L));
//							 A = (A > 255 ? 255 : (A < 0 ? 0 : A));
//							 B = (B > 255 ? 255 : (B < 0 ? 0 : B));
//						 }
//
//						 pixel.val[0] = L;
////						 pixel.val[1] = A;
////						 pixel.val[2] = B;
//					 }
//				 }
//			 }
//			 cv::cvtColor(imgProcessEdgeDarkPixelsLAB, imgProcessEdgeDarkPixelsBGR, CV_Lab2BGR);
//			 cv::imshow("imgProcessEdgeDarkPixels", imgProcessEdgeDarkPixelsBGR);
//			 //CopyMatToArray(imgProcessEdgeDarkPixelsBGR, buffer);

			 //Rlease memory
			 imgBGR.release();
			 delete imgBGR.data;

			 imgLAB.release();
			 delete imgLAB.data;

			 imgBGRres.release();
			 delete imgBGRres.data;

			 SaveBMP();
			 ShowBmp();
}

private: void CopyMatToMat(cv::Mat source, cv::Mat dest){

			 int step = source.step; // width * channels
			 int channels = source.channels();

			 //В Mat счет пикселей идет сверху
			 for (int i = 0; i < source.rows; i++) {
				 for (int j = 0; j < source.cols; j++) {

					 cv::Vec3b &Pixel = source.at<cv::Vec3b>(i, j);
					 cv::Vec3b &PixelDest = dest.at<cv::Vec3b>(i, j);

					 PixelDest.val[0] = Pixel.val[0];
					 PixelDest.val[1] = Pixel.val[1];
					 PixelDest.val[2] = Pixel.val[2];
				 }
			 }
}

private: void CopyMatToArray(cv::Mat source, UCHAR *dest){

			 int step = source.step; // width * channels
			 int channels = source.channels();

			 int i_buff = source.rows - 1;
			 int j_buff = 0;

			 ////Test - прямая запись с тестовымим цветовыми линиями - пишет вверх ногами
//			 for (int i = 0; i < source.cols * 3; i += 3)
//			 {
//				 if (i < (source.cols * 3) / 2){
//					 source.data[i] = 0;
//					 source.data[i + 1] = 0;
//					 source.data[i + 2] = 255;
//				 }
//				 else
//				 {
//					 source.data[i] = 0;
//					 source.data[i + 1] = 255;
//					 source.data[i + 2] = 0;
//				 }
//			 }
//			 for (int i = source.cols * 3*2; i < source.cols * 3*3; i += 3)
//			 {
//				 source.data[i] = 255;
//				 source.data[i + 1] = 0;
//				 source.data[i + 2] = 0;
//			 }
//			 for (int i = source.cols * 3 * 3; i < source.cols * 3 * 4; i += 3)
//			 {
//				 source.data[i] = 255;
//				 source.data[i + 1] = 255;
//				 source.data[i + 2] = 255;
//			 }
//			 for (int i = source.cols * 3 * 30; i < source.cols * 3 * 31; i += 3)
//			 {
//				 source.data[i] = 255;
//				 source.data[i + 1] = 255;
//				 source.data[i + 2] = 255;
//			 }
//
//			 for (int i = source.cols * 3 * 50; i < source.cols * 3 * 51; i += 3)
//			 {
//				 if (i < ((source.cols * 3)/2) * 51){
//					 source.data[i] = 255;
//					 source.data[i + 1] = 30;
//					 source.data[i + 2] = 255;
//				 }
//				 else
//				 {
//					 source.data[i] = 255;
//					 source.data[i + 1] = 45;
//					 source.data[i + 2] = 45;
//				 }
//			 }
//
//			 
//
//			 for (int i = 0, j = 0; i < source.rows*source.cols*channels; i += 3, j += 3)
//			 {
//				 dest[j] = source.data[i];
//				 dest[j + 1] = source.data[i + 1];
//				 dest[j + 2] = source.data[i + 2];
//			 }
//			 return;

			 //В Mat счет пикселей идет сверху
			 for (int i = 0; i < source.rows; i++) {
				 j_buff = 0;
				 for (int j = 0; j < source.cols; j++) {

					 double CIE_L = source.data[step*i + channels*j + 0];;
					 double CIE_A = source.data[step*i + channels*j + 1];
					 double CIE_B = source.data[step*i + channels*j + 2];

					 int ind = i_buff * step + channels*j_buff + 0;

					 dest[i_buff * step + channels*j_buff + 0] = CIE_L;
					 dest[i_buff * step + channels*j_buff + 1] = CIE_A;
					 dest[i_buff * step + channels*j_buff + 2] = CIE_B;

					 j_buff += 1;

					 if (i_buff < 0)
						 throw gcnew Exception("i_buff index less than 0 !");
					 
				 }
				 i_buff -= 1;
			 }
}

private: void CopyArrayToMat(UCHAR * source, cv::Mat dest){

			 int step = dest.step; // width * channels
			 int channels = dest.channels();

			 int i_buff = dest.rows - 1;
			int j_buff = 0;

			//В Mat счет пикселей идет сверху
			for (int i = 0; i < dest.rows; i++) {
				j_buff = 0;
				for (int j = 0; j < dest.cols; j++) {

					double CIE_L = source[i_buff * step + channels*j_buff + 0];
					double CIE_A = source[i_buff * step + channels*j_buff + 1];
					double CIE_B = source[i_buff * step + channels*j_buff + 2];

					cv::Vec3b &Pixel = dest.at<cv::Vec3b>(i, j);

					Pixel.val[0] = CIE_L;
					Pixel.val[1] = CIE_A;
					Pixel.val[2] = CIE_B;

					j_buff++;

				}
				i_buff--;
			}
}

private: void K_MeansLab(cv::Mat imgResVisual){

			 int K = 5; //Кількість кластерів
			 int Q = size / 3;//Кількість векторів
			 int Qn = 3; //Розмір векторів

			 //double[, ] X = new double[Q, Qn];
			 double **X = new double *[Q];
			 for (int i = 0; i < Q; i++){
				 X[i] = new double[Qn];
			 }
			 /*
			 for (int i = 0; i < M; i++) {
			 delete []mas[i];
			 }
			 delete []mas;
			 */

			 //Copy buffer to matrix X
			 for (int i = 0, j = 0; j < size; i += 1, j += 3)
			 {
				 X[i][0] = buffer[j];
				 X[i][1] = buffer[j + 1];
				 X[i][2] = buffer[j + 2];

				 //				 X[i][0] = buffer[j + 1];
				 //				 X[i][1] = buffer[j + 2];
			 }

			 //Центри кластерів
			 double **z = new double*[K];
			 for (int i = 0; i < K; i++){
				 z[i] = new double[Qn];
			 }

			 //Нові центри кластерів
			 double **z_new = new double*[K];
			 for (int i = 0; i < K; i++){
				 z_new[i] = new double[Qn];
			 }

			 //Кількість векторів к-го класу
			 int *n_k = new int[K];

			 bool skipStep1 = false;
			 for (int iteration = 0; true; iteration++)
			 {
				 if (!skipStep1)
				 {
					 //Крок 1
					 //Console.WriteLine("Крок 1");
					 //Цикл ініціалізації центрів кластерів
					 //Беремо центри які значно відрізняються
					 int step = Q / K;
					 int X_index = 0;
					 for (int k = 0; k < K; k++)
					 {
						 //z_k = x_k;
						 for (int j = 0; j < Qn; j++)
						 {
							 //z[k, j] = X[k, j];
							 z[k][j] = X[X_index][j];
						 }
						 double AAA1 = z[k][0];
						 double AAA2 = z[k][1];
						 double AAA3 = z[k][2];
						 //n(k1) = 0;
						 n_k[k] = 0;
						 X_index += step;
					 }
				 }

				 //Крок 2
				 //Console.WriteLine("Крок 2");

				 /*double[, ] teta = new double[1, Qn];
				 int[] class_q = new int[Q];*/

				 double **teta = new double*[1];
				 for (int i = 0; i < 1; i++){
					 teta[i] = new double[Qn];
				 }

				 int *class_q = new int[Q];

				 ///* Цикл занесення векторів до кластерів з найближчим центром */
				 for (int q = 0; q < Q; q++)
				 {
					 double d_min = 999999999.1;//999999.9;
					 double d = 0;
					 int k_min = 0;

					 ///* Цикл знаходження мінімальної відстані до центрів */
					 for (int k = 0; k < K; k++)
					 {
						 //Знаходження відстані d = || x_q - z_k ||
						 double sum = 0;
						 for (int j = 0; j < Qn; j++)
						 {
							 //sum += Math.Pow(X[q, j] - z[k, j], 2);
							 double XXX = X[q][j];
							 double zzzz = z[k][j];
							 double ttt = X[q][j] - z[k][j];
							 double ttpow = pow(X[q][j] - z[k][j], 2);
							 sum += pow(X[q][j] - z[k][j], 2);
						 }
						 //d = Math.Sqrt(sum);
						 d = pow(sum, 0.5);

						 //Визначення мінімальної відстані
						 if (d < d_min)
						 {
							 d_min = d;
							 k_min = k;
						 }
					 }
					 /*Позначення вектора x_q k-им класом */
					 //class(q) = k_min
					 class_q[q] = k_min;

					 //n(k_min) = n(k_min) + 1 ///* Інкрементація лічильника векторів k_min-го класу 
					 n_k[k_min] += 1;
				 }

				 //Крок 3
				 //Console.WriteLine("Крок 3");

				 /* Цикл обчислення K нових центрів кластерів */
				 for (int k = 0; k < K; k++)
				 {
					 /* Знаходження середнього k1-го кластера */
					 //1/n(k)
					 //double temp = 1.0 / (double)n_k[k];

					 for (int j = 0; j < Qn; j++)
					 {
						 double sum = 0;
						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 //sum += X[q, j];
								 sum += X[q][j];
							 }
						 }
						 //z_new[k, j] = sum / (double)n_k[k];
						 z_new[k][j] = sum / (double)n_k[k];
					 }
				 }

				 //Крок 4
				 //Console.WriteLine("Крок 4");
				 //перевіряємо умову припинення процедури кластеризації
				 bool Flag = false;

				 ///* Цикл фіксації зміни хоча б одного центра за допомогою прапорця */
				 for (int k = 0; k < K; k++)
				 {
					 //Знаходження відстані d_z = ||z_new_k - z_k||
					 double d_z = 0;
					 double sum = 0;
					 double diff = 1;
					 for (int j = 0; j < Qn; j++)
					 {
						 //diff = z_new[k, j] - z[k, j];
						 diff = z_new[k][j] - z[k][j];
						 //sum += Math.Pow(z_new[k, j] - z[k, j], 2);
						 sum += pow(z_new[k][j] - z[k][j], 2);
					 }
					 //d_z = Math.Sqrt(sum);
					 d_z = pow(sum, 0.5);

					 if (d_z > 0.0000000001)//0.0005)
						 Flag = true;
				 }

				 ///* При наявності змін обновити центри і повторити процедуру */
				 if (Flag == true)
				 {
					 //Console.WriteLine("Повтор процедури. Ітерація - {0}", iteration);
					 for (int k = 0; k < K; k++)
					 {
						 n_k[k] = 0;
						 for (int j = 0; j < Qn; j++)
							 //z[k, j] = z_new[k, j];
							 z[k][j] = z_new[k][j];
					 }
					 skipStep1 = true; //Пропустити крок 1
				 }
				 /* Інакше припинити кластеризацію */
				 else
				 {
					 ////###////###/////####

					 //Видалити пустi кластери
					 for (int k = 0; k < K; k++)
					 {
						 int A = 0;


						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 A++;
							 }
						 }
						 if (n_k[k] == 0)
						 {
							 n_k[k] = 0;


						 }

					 }

					 //Пройтись по всім кластерам і розділити їх на два, якщо в ньому присутні тіньові ті нетіньові пікселі
					 int need_to_separate = 0;

					 int *clusters_to_separate = new int[K];
					 int indexCTS = 0;
					 for (int k = 0; k < K; k++)
					 {
						 clusters_to_separate[k] = -1;
					 }

					 for (int k = 0; k < K; k++)
					 {
						 bool is_homogenous = true;
						 bool is_shadow = false;
						 bool is_non_shadow = false;
						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 if (shadowMask[q * 3] == 255)
								 {
									 is_shadow = true;
								 }
								 else
								 {
									 is_non_shadow = true;
								 }

								 if (is_shadow && is_non_shadow)
								 {
									 //clusters_to_separate[indexCTS] = k;
									 clusters_to_separate[k] = true;
									 indexCTS += 1;
									 need_to_separate += 1;
									 break;
								 }
							 }
						 }
					 }
					 int new_clusters_amount = indexCTS;

					 //Розбиваємо кластер на два
					 int new_cluster_number = K;
					 int *n_k_new = new int[new_clusters_amount];
					 for (int k = 0; k < new_clusters_amount; k++)
						 n_k_new[k] = 0;
					 for (int k = 0; k < K; k++)
					 {
						 if (clusters_to_separate[k] == -1)
							 continue;

						 //int current_cluster = clusters_to_separate[k];

						 int current_cluster = -1;
						 if (clusters_to_separate[k] == true){
							 current_cluster = k;
						 }

						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == current_cluster)
							 {
								 if (shadowMask[q * 3] == 255)
								 {
									 class_q[q] = new_cluster_number;
									 //n_k[k] -= 1;
									 n_k_new[new_cluster_number - K] += 1;
								 }
							 }
						 }
						 n_k[k] = n_k[k] - n_k_new[new_cluster_number - K];
						 new_cluster_number += 1;
					 }
					 int *temp_n_k = new int[K + new_clusters_amount];
					 for (int k = 0; k < K + new_clusters_amount; k++)
					 {
						 if (k < K)
							 temp_n_k[k] = n_k[k];
						 else
							 temp_n_k[k] = n_k_new[k - K];
					 }
					 delete n_k;
					 delete n_k_new;
					 n_k = temp_n_k;
					 K = K + new_clusters_amount;

					 //Записати номера векторів кожного кластера
					 int **clusters_elements = new int *[K];
					 for (int i = 0; i < K; i++)
					 {
						 clusters_elements[i] = new int[n_k[i]];
					 }
					 bool *is_shadow_claster = new bool[K];
					 for (int k = 0; k < K; k++)
					 {
						 int j = 0;
						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 //check if cluster contain shadow pixels
								 if (shadowMask[q * 3] == 255)
									 is_shadow_claster[k] = true;
								 else
									 is_shadow_claster[k] = false;

								 clusters_elements[k][j] = q;
								 j += 1;
							 }
						 }
					 }


					 //

					 //Корекція кольору пікселів тіні
					 for (int k = 0; k < K; k++)
					 {
						 if (is_shadow_claster[k] == false)
							 continue;

						 //Знаходимо кольорову характеристику даного тіньового кластера
						 double average_color = 0;
						 double R_avg_shadow = 0;
						 double G_avg_shadow = 0;
						 double B_avg_shadow = 0;

						 double Y_avg_shadow = 0;
						 double Cb_avg_shadow = 0;
						 double Cr_avg_shadow = 0;
						 for (int j = 0; j < n_k[k]; j++)
						 {
							 int index = clusters_elements[k][j];
							 int R = buffer[index * 3];
							 int G = buffer[index * 3 + 1];
							 int B = buffer[index * 3 + 2];

							 int Cb = buffer[index * 3 + 1];
							 int Cr = buffer[index * 3 + 2];

							 //average_color += (double)((R + G + B) / 3.0);
							 average_color += (double)((R + G + B));
							 R_avg_shadow += R;
							 G_avg_shadow += G;
							 B_avg_shadow += B;

							 Cb_avg_shadow += G;
							 Cr_avg_shadow += B;
						 }
						 average_color = average_color / (n_k[k]);
						 R_avg_shadow /= n_k[k];
						 G_avg_shadow /= n_k[k];
						 B_avg_shadow /= n_k[k];

						 Cb_avg_shadow /= n_k[k];
						 Cr_avg_shadow /= n_k[k];

						 average_color = (R_avg_shadow + G_avg_shadow + B_avg_shadow) / 3;

						 //
						 int min_average_diff_cluster = -1;
						 double diff = 999999999.1;
						 double R_diff = 9999999.1;
						 double G_diff = 999999999.1;
						 double B_diff = 999999999.1;

						 double Cb_diff = 999999.1;
						 double Cr_diff = 999999.1;
						 for (int kk = 0; kk < K; kk++)
						 {
							 if (is_shadow_claster[kk] == true)
								 continue;

							 double average_color_non_shadow = 0;
							 double R_avg_non_shadow = 0;
							 double G_avg_non_shadow = 0;
							 double B_avg_non_shadow = 0;

							 double Y_avg_non_shadow = 0;
							 double Cb_avg_non_shadow = 0;
							 double Cr_avg_non_shadow = 0;
							 for (int jj = 0; jj < n_k[kk]; jj++)
							 {
								 int index = clusters_elements[kk][jj];
								 int R = buffer[index * 3];
								 int G = buffer[index * 3 + 1];
								 int B = buffer[index * 3 + 2];

								 int Cb = buffer[index * 3 + 1];
								 int Cr = buffer[index * 3 + 2];

								 //average_color_non_shadow += (double)((R + G + B) / 3.0);
								 average_color_non_shadow += (double)((R + G + B));
								 R_avg_non_shadow += R;
								 G_avg_non_shadow += G;
								 B_avg_non_shadow += B;

								 Cb_avg_non_shadow += G;
								 Cr_avg_non_shadow += B;
							 }
							 average_color_non_shadow = average_color_non_shadow / (n_k[kk]);
							 R_avg_non_shadow /= n_k[kk];
							 G_avg_non_shadow /= n_k[kk];
							 B_avg_non_shadow /= n_k[kk];

							 Cb_avg_non_shadow /= n_k[kk];
							 Cr_avg_non_shadow /= n_k[kk];

							 average_color_non_shadow = (R_avg_non_shadow + G_avg_non_shadow + B_avg_non_shadow) / 3;


							 //							 if (abs(average_color_non_shadow - average_color) < diff)
							 //							 {
							 //								 min_average_diff_cluster = kk;
							 //								 diff = abs(average_color_non_shadow - average_color);
							 //							 }
							 //							 

//							 double diffTotal = average_color_non_shadow - average_color;
//							 if ((abs(R_avg_non_shadow - R_avg_shadow) < R_diff) && (abs(G_avg_non_shadow - G_avg_shadow) < G_diff) && (abs(B_avg_non_shadow - B_avg_shadow) < B_diff))
//							 {
//								 min_average_diff_cluster = kk;
//								 diff = abs(average_color_non_shadow - average_color);
//								 R_diff = abs(R_avg_non_shadow - R_avg_shadow);
//								 G_diff = abs(G_avg_non_shadow - G_avg_shadow);
//								 B_diff = abs(B_avg_non_shadow - B_avg_shadow);
//							 }

							 int k___ = k;
							 int kk___ = kk;
							if ((abs(Cr_avg_non_shadow - Cr_avg_shadow) < Cr_diff) && (abs(Cb_avg_non_shadow - Cb_avg_shadow) < Cb_diff))
							{
							 	min_average_diff_cluster = kk;
							 	Cb_diff = abs(Cb_avg_non_shadow - Cb_avg_shadow);
							 	Cr_diff = abs(Cr_avg_non_shadow - Cr_avg_shadow);
							}
						 }
						 int asda = 0;

						 if (min_average_diff_cluster < 0)
						 {
							 Sleep(10);
						 }

						 //						 if (k == 5)
						 //							 min_average_diff_cluster = 3;
						 //						 if (k == 7)
						 //							 min_average_diff_cluster = 2;
						 //min_average_diff_cluster = 2;

//						 if (k == 6 || k == 9)
//							 min_average_diff_cluster = 2;

						 //Коректуємо колір даного тіньового кластера з знайденим
						 double R_avg_other = 0;
						 double G_avg_other = 0;
						 double B_avg_other = 0;
						 for (int j = 0; j < n_k[min_average_diff_cluster]; j++)
						 {
							 int index = clusters_elements[min_average_diff_cluster][j];
							 int R = buffer[index * 3];
							 int G = buffer[index * 3 + 1];
							 int B = buffer[index * 3 + 2];

							 R_avg_other += R;
							 G_avg_other += G;
							 B_avg_other += B;
						 }
						 R_avg_other /= n_k[min_average_diff_cluster];
						 G_avg_other /= n_k[min_average_diff_cluster];
						 B_avg_other /= n_k[min_average_diff_cluster];

						 double R_avg_curr = 0;
						 double G_avg_curr = 0;
						 double B_avg_curr = 0;
						 for (int j = 0; j < n_k[k]; j++)
						 {
							 int index = clusters_elements[k][j];
							 int R = buffer[index * 3];
							 int G = buffer[index * 3 + 1];
							 int B = buffer[index * 3 + 2];

							 R_avg_curr += R;
							 G_avg_curr += G;
							 B_avg_curr += B;
						 }
						 R_avg_curr /= n_k[k];
						 G_avg_curr /= n_k[k];
						 B_avg_curr /= n_k[k];

						 //Values to add/sub
						 int Red = R_avg_other - R_avg_curr;
						 int Green = G_avg_other - G_avg_curr;
						 int Blue = B_avg_other - B_avg_curr;
						 int RGB = 0;

						 double R_ratio = (R_avg_other / R_avg_curr);
						 double G_ratio = (G_avg_other / G_avg_curr);
						 double B_ratio = (B_avg_other / B_avg_curr);
						 int asdasdasdasd = 0;

						 //Color correction
						 /*
						 for (int j = 0; j < n_k[k]; j++)
						 {
						 int index = clusters_elements[k][j];
						 buffer[index * 3] + Red + RGB>255 ? buffer[index * 3] = 255 : (buffer[index * 3] + Red + RGB < 0 ? buffer[index * 3] = 0 : buffer[index * 3] += Red + RGB);//Red
						 buffer[index * 3 + 1] + Green + RGB>255 ? buffer[index * 3 + 1] = 255 : (buffer[index * 3 + 1] + Green + RGB<0 ? buffer[index * 3 + 1] = 0 : buffer[index * 3 + 1] += Green + RGB);//Green
						 buffer[index * 3 + 2] + Blue + RGB>255 ? buffer[index * 3 + 2] = 255 : (buffer[index * 3 + 2] + Blue + RGB<0 ? buffer[index * 3 + 2] = 0 : buffer[index * 3 + 2] += Blue + RGB);//Blue
						 }
						 */

						 int CURRENT = k;
						 int MIN_DIFF = min_average_diff_cluster;
						 
						 int maxI = 0;
						 for (int j = 0, index = 0; j < n_k[k]; j++)
						 {
							 index = clusters_elements[k][j];

							 if (index > maxI)
								 maxI = index;

							 int currR = buffer[index * 3];
							 int currG = buffer[index * 3 + 1];
							 int currB = buffer[index * 3 + 2];

//							 currR += Red;
//							 currG += Green;
//							 currB += Blue;

							//currR *= R_ratio;
							currG *= G_ratio;
							currB *= B_ratio;

							 //							 //Зафарбувати в середні кольори
							 //							 buffer[index * 3] = (unsigned char)R_avg_other;//Red
							 //							 buffer[index * 3 + 1] = (unsigned char)G_avg_other;//Green
							 //							 buffer[index * 3 + 2] = (unsigned char)B_avg_other;//Blue

							 //							 currR += -46;
							 //							 currG += -40;// -36;//Green
							 //							 currB += -19;// -11;//Blue

							 currR = currR > 255 ? 255 : (currR < 0 ? 0 : currR);
							 currG = currG > 255 ? 255 : (currG < 0 ? 0 : currG);
							 currB = currB > 255 ? 255 : (currB < 0 ? 0 : currB);

							 buffer[index * 3] = currR;//Red
							 buffer[index * 3 + 1] = currG;//Green
							 buffer[index * 3 + 2] = currB;//Blue

						 }

						 /////////////////////

						 //Показати два кластери що коректуються
						 //////Візуалізація результату кластеризації у виглядi кольорів
						 //int classR = 180;
						 //int classG = 255;
						 //int classB = 0;
						 //for (int kkk = 0; kkk < K; kkk++)
						 //{
						 // /*if (kkk != k || kkk != min_average_diff_cluster)
						 //	 continue;*/

						 // for (int q = 0; q < Q; q++)
						 // {
						 //	 X[q][0] = 0;
						 //	 X[q][1] = 255;
						 //	 X[q][2] = 208;
						 //	 if (class_q[q] == k)
						 //	 {
						 //		 X[q][0] = 0;
						 //		 X[q][1] = 0;
						 //		 X[q][2] = 0;
						 //	 }
						 //	 if (class_q[q] == min_average_diff_cluster)
						 //	 {
						 //		 X[q][0] = 0;
						 //		 X[q][1] = 0;
						 //		 X[q][2] = 255;
						 //	 }
						 // }
						 // classR -= rand() % 70;
						 // classG -= rand() % 255;
						 // classB += rand() % 255;
						 //}

						 ////Copy X to buffer
						 //for (int iii = 0, jjj = 0; jjj < size; iii += 1, jjj += 3)
						 //{
						 // int RR = buffer[jjj];
						 // int XR = X[iii][0];

						 // buffer[jjj] = X[iii][0];
						 // buffer[jjj + 1] = X[iii][1];
						 // buffer[jjj + 2] = X[iii][2];
						 //}


						 //SaveBMP();
						 //ShowBmp();
						 //int a = 0;
						 /////////////////////////
						 ////break;
						 //CopyArrayUCHAR(bufferBackup, buffer, size);
						 /*SaveBMP();
						 ShowBmp();*/

					 }


					 if (checkBoxClusterVisual->Checked)
					 {

						 //Візуалізація результату кластеризації у виглядi кольорів
						 int classR = 180;
						 int classG = 255;
						 int classB = 0;

						 for (int k = 0; k < K; k++)
						 {
							 if (k == 0)
							 {
								 classR = 255;
								 classG = 255;
								 classB = 255;
							 }
							 if (k == 1)//красный
							 {
								 classR = 0;
								 classG = 0;
								 classB = 255;
							 }
							 if (k == 2)//зеленый
							 {
								 classR = 0;
								 classG = 255;
								 classB = 0;
							 }
							 if (k == 3)//синий
							 {
								 classR = 255;
								 classG = 0;
								 classB = 0;
							 }
							 if (k == 4)//розовый
							 {
								 classR = 209;
								 classG = 100;
								 classB = 255;
							 }


							 if (k == 5)//оранжевый
							 {
								 classR = 0;
								 classG = 213;
								 classB = 255;
							 }
							 if (k == 6)//берюзовый
							 {
								 classR = 255;
								 classG = 252;
								 classB = 50;
							 }
							 if (k == 7)//фиолетовый /бледно-синий
							 {
								 classR = 255;
								 classG = 0;
								 classB = 191;

								 //								 classR = 255;
								 //								 classG = 128;
								 //								 classB = 128;
							 }
							 if (k == 8)//черный
							 {
								 classR = 0;
								 classG = 0;
								 classB = 0;
							 }
							 if (k == 9)//желтовато-зеленый
							 {
								 classR = 0;
								 classG = 240;
								 classB = 232;
							 }

							 for (int q = 0; q < Q; q++)
							 {
								 if (class_q[q] == k)
								 {
									 X[q][0] = classR;
									 X[q][1] = classG;
									 X[q][2] = classB;
								 }
							 }
							 classR -= rand() % 70;
							 classG -= rand() % 255;
							 classB += rand() % 255;
						 }

//						 //Copy X to buffer
//						 for (int i = 0, j = 0; j < size; i += 1, j += 3)
//						 {
//
//							 buffer[j] = X[i][0];
//							 buffer[j + 1] = X[i][1];
//							 buffer[j + 2] = X[i][2];
//						 }

						 //Copy X to buffer
						 UCHAR * buffer2 = new UCHAR[size];
						 for (int i = 0, j = 0; j < size; i += 1, j += 3)
						 {
							 buffer2[j] = X[i][0];
							 buffer2[j + 1] = X[i][1];
							 buffer2[j + 2] = X[i][2];
						 }

						 CopyArrayToMat(buffer2, imgResVisual);

						 ////FOR SPECIAL CLUSTERS
						 //						 for (int k = 0; k < K; k++)
						 //						 {
						 ////							 if (k == 5)//оранжевый
						 ////							 {
						 ////								 classR = 0;
						 ////								 classG = 213;
						 ////								 classB = 255;
						 ////							 }
						 //							 if (k == 7)//фиолетовый /бледно-синий
						 //							{
						 //								classR = 255;
						 //								classG = 0;
						 //								classB = 191;
						 //								 
						 ////								 classR = 255;
						 ////								 classG = 128;
						 ////								 classB = 128;
						 //							}
						 //							 else//берюзовый
						 //							 {
						 //								 classR = 255;
						 //								 classG = 252;
						 //								 classB = 50;
						 //							 }
						 //
						 //							 for (int j = 0; j < n_k[k]; j++)
						 //							 {
						 //								 int index = clusters_elements[k][j];
						 //
						 //								 buffer[index * 3] = classR;//Red
						 //								 buffer[index * 3 + 1] = classG;//Green
						 //								 buffer[index * 3 + 2] = classB;//Blue
						 //
						 //							 }
						 //						 }


					 }

					 ////###////###/////####

					 break;
				 }
			 }

}

private: void K_MeansLabByChrom(cv::Mat imgResVisual){

			 int K = 5; //Кількість кластерів
			 int Q = size / 3;//Кількість векторів
			 int Qn = 2; //Розмір векторів

			 //double[, ] X = new double[Q, Qn];
			 double **X = new double *[Q];
			 for (int i = 0; i < Q; i++){
				 X[i] = new double[Qn];
			 }
			 /*
			 for (int i = 0; i < M; i++) {
			 delete []mas[i];
			 }
			 delete []mas;
			 */

			 //Copy buffer to matrix X
			 for (int i = 0, j = 0; j < size; i += 1, j += 3)
			 {
				 //X[i][0] = buffer[j];
				 X[i][0] = buffer[j + 1];
				 X[i][1] = buffer[j + 2];

				 //				 X[i][0] = buffer[j + 1];
				 //				 X[i][1] = buffer[j + 2];
			 }

			 //Центри кластерів
			 double **z = new double*[K];
			 for (int i = 0; i < K; i++){
				 z[i] = new double[Qn];
			 }

			 //Нові центри кластерів
			 double **z_new = new double*[K];
			 for (int i = 0; i < K; i++){
				 z_new[i] = new double[Qn];
			 }

			 //Кількість векторів к-го класу
			 int *n_k = new int[K];

			 bool skipStep1 = false;
			 for (int iteration = 0; true; iteration++)
			 {
				 if (!skipStep1)
				 {
					 //Крок 1
					 //Console.WriteLine("Крок 1");
					 //Цикл ініціалізації центрів кластерів
					 //Беремо центри які значно відрізняються
					 int step = Q / K;
					 int X_index = 0;
					 for (int k = 0; k < K; k++)
					 {
						 //z_k = x_k;
						 for (int j = 0; j < Qn; j++)
						 {
							 //z[k, j] = X[k, j];
							 z[k][j] = X[X_index][j];
						 }

						 //n(k1) = 0;
						 n_k[k] = 0;
						 X_index += step;
					 }
				 }

				 //Крок 2
				 //Console.WriteLine("Крок 2");

				 /*double[, ] teta = new double[1, Qn];
				 int[] class_q = new int[Q];*/

				 double **teta = new double*[1];
				 for (int i = 0; i < 1; i++){
					 teta[i] = new double[Qn];
				 }

				 int *class_q = new int[Q];

				 ///* Цикл занесення векторів до кластерів з найближчим центром */
				 for (int q = 0; q < Q; q++)
				 {
					 double d_min = 999999999.1;//999999.9;
					 double d = 0;
					 int k_min = 0;

					 ///* Цикл знаходження мінімальної відстані до центрів */
					 for (int k = 0; k < K; k++)
					 {
						 //Знаходження відстані d = || x_q - z_k ||
						 double sum = 0;
						 for (int j = 0; j < Qn; j++)
						 {
							 //sum += Math.Pow(X[q, j] - z[k, j], 2);
							 sum += pow(X[q][j] - z[k][j], 2);
						 }
						 //d = Math.Sqrt(sum);
						 d = pow(sum, 0.5);

						 //Визначення мінімальної відстані
						 if (d < d_min)
						 {
							 d_min = d;
							 k_min = k;
						 }
					 }
					 /*Позначення вектора x_q k-им класом */
					 //class(q) = k_min
					 class_q[q] = k_min;

					 //n(k_min) = n(k_min) + 1 ///* Інкрементація лічильника векторів k_min-го класу 
					 n_k[k_min] += 1;
				 }

				 //Крок 3
				 //Console.WriteLine("Крок 3");

				 /* Цикл обчислення K нових центрів кластерів */
				 for (int k = 0; k < K; k++)
				 {
					 /* Знаходження середнього k1-го кластера */
					 //1/n(k)
					 //double temp = 1.0 / (double)n_k[k];

					 for (int j = 0; j < Qn; j++)
					 {
						 double sum = 0;
						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 //sum += X[q, j];
								 sum += X[q][j];
							 }
						 }
						 //z_new[k, j] = sum / (double)n_k[k];
						 z_new[k][j] = sum / (double)n_k[k];
					 }
				 }

				 //Крок 4
				 //Console.WriteLine("Крок 4");
				 //перевіряємо умову припинення процедури кластеризації
				 bool Flag = false;

				 ///* Цикл фіксації зміни хоча б одного центра за допомогою прапорця */
				 for (int k = 0; k < K; k++)
				 {
					 //Знаходження відстані d_z = ||z_new_k - z_k||
					 double d_z = 0;
					 double sum = 0;
					 double diff = 1;
					 for (int j = 0; j < Qn; j++)
					 {
						 //diff = z_new[k, j] - z[k, j];
						 diff = z_new[k][j] - z[k][j];
						 //sum += Math.Pow(z_new[k, j] - z[k, j], 2);
						 sum += pow(z_new[k][j] - z[k][j], 2);
					 }
					 //d_z = Math.Sqrt(sum);
					 d_z = pow(sum, 0.5);

					 if (d_z > 0.0000000001)//0.0005)
						 Flag = true;
				 }

				 ///* При наявності змін обновити центри і повторити процедуру */
				 if (Flag == true)
				 {
					 //Console.WriteLine("Повтор процедури. Ітерація - {0}", iteration);
					 for (int k = 0; k < K; k++)
					 {
						 n_k[k] = 0;
						 for (int j = 0; j < Qn; j++)
							 //z[k, j] = z_new[k, j];
							 z[k][j] = z_new[k][j];
					 }
					 skipStep1 = true; //Пропустити крок 1
				 }
				 /* Інакше припинити кластеризацію */
				 else
				 {
					 ////###////###/////####

					 //Видалити пустi кластери
					 for (int k = 0; k < K; k++)
					 {
						 int A = 0;


						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 A++;
							 }
						 }
						 if (n_k[k] == 0)
						 {
							 n_k[k] = 0;


						 }

					 }

					 //Пройтись по всім кластерам і розділити їх на два, якщо в ньому присутні тіньові ті нетіньові пікселі
					 int need_to_separate = 0;

					 int *clusters_to_separate = new int[K];
					 int indexCTS = 0;
					 for (int k = 0; k < K; k++)
					 {
						 clusters_to_separate[k] = -1;
					 }

					 for (int k = 0; k < K; k++)
					 {
						 bool is_homogenous = true;
						 bool is_shadow = false;
						 bool is_non_shadow = false;
						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 if (shadowMask[q * 3] == 255)
								 {
									 is_shadow = true;
								 }
								 else
								 {
									 is_non_shadow = true;
								 }

								 if (is_shadow && is_non_shadow)
								 {
									 //clusters_to_separate[indexCTS] = k;
									 clusters_to_separate[k] = true;
									 indexCTS += 1;
									 need_to_separate += 1;
									 break;
								 }
							 }
						 }
					 }
					 int new_clusters_amount = indexCTS;

					 //Розбиваємо кластер на два
					 int new_cluster_number = K;
					 int *n_k_new = new int[new_clusters_amount];
					 for (int k = 0; k < new_clusters_amount; k++)
						 n_k_new[k] = 0;
					 for (int k = 0; k < K; k++)
					 {
						 if (clusters_to_separate[k] == -1)
							 continue;

						 //int current_cluster = clusters_to_separate[k];

						 int current_cluster = -1;
						 if (clusters_to_separate[k] == true){
							 current_cluster = k;
						 }

						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == current_cluster)
							 {
								 if (shadowMask[q * 3] == 255)
								 {
									 class_q[q] = new_cluster_number;
									 //n_k[k] -= 1;
									 n_k_new[new_cluster_number - K] += 1;
								 }
							 }
						 }
						 n_k[k] = n_k[k] - n_k_new[new_cluster_number - K];
						 new_cluster_number += 1;
					 }
					 int *temp_n_k = new int[K + new_clusters_amount];
					 for (int k = 0; k < K + new_clusters_amount; k++)
					 {
						 if (k < K)
							 temp_n_k[k] = n_k[k];
						 else
							 temp_n_k[k] = n_k_new[k - K];
					 }
					 delete n_k;
					 delete n_k_new;
					 n_k = temp_n_k;
					 K = K + new_clusters_amount;

					 //Записати номера векторів кожного кластера
					 int **clusters_elements = new int *[K];
					 for (int i = 0; i < K; i++)
					 {
						 clusters_elements[i] = new int[n_k[i]];
					 }
					 bool *is_shadow_claster = new bool[K];
					 for (int k = 0; k < K; k++)
					 {
						 int j = 0;
						 for (int q = 0; q < Q; q++)
						 {
							 if (class_q[q] == k)
							 {
								 //check if cluster contain shadow pixels
								 if (shadowMask[q * 3] == 255)
									 is_shadow_claster[k] = true;
								 else
									 is_shadow_claster[k] = false;

								 clusters_elements[k][j] = q;
								 j += 1;
							 }
						 }
					 }


					 //

					 //Корекція кольору пікселів тіні
					 for (int k = 0; k < K; k++)
					 {
						 if (is_shadow_claster[k] == false)
							 continue;

						 //Знаходимо кольорову характеристику даного тіньового кластера
						 double average_color = 0;
						 double R_avg_shadow = 0;
						 double G_avg_shadow = 0;
						 double B_avg_shadow = 0;

						 double Y_avg_shadow = 0;
						 double Cb_avg_shadow = 0;
						 double Cr_avg_shadow = 0;
						 for (int j = 0; j < n_k[k]; j++)
						 {
							 int index = clusters_elements[k][j];
							 int R = buffer[index * 3];
							 int G = buffer[index * 3 + 1];
							 int B = buffer[index * 3 + 2];

							 int Cb = buffer[index * 3 + 1];
							 int Cr = buffer[index * 3 + 2];

							 //average_color += (double)((R + G + B) / 3.0);
							 average_color += (double)((R + G + B));
							 R_avg_shadow += R;
							 G_avg_shadow += G;
							 B_avg_shadow += B;

							 Cb_avg_shadow += G;
							 Cr_avg_shadow += B;
						 }
						 average_color = average_color / (n_k[k]);
						 R_avg_shadow /= n_k[k];
						 G_avg_shadow /= n_k[k];
						 B_avg_shadow /= n_k[k];

						 Cb_avg_shadow /= n_k[k];
						 Cr_avg_shadow /= n_k[k];

						 average_color = (R_avg_shadow + G_avg_shadow + B_avg_shadow) / 3;

						 //
						 int min_average_diff_cluster = -1;
						 double diff = 999999999.1;
						 double R_diff = 9999999.1;
						 double G_diff = 999999999.1;
						 double B_diff = 999999999.1;

						 double Cb_diff = 999999.1;
						 double Cr_diff = 999999.1;
						 for (int kk = 0; kk < K; kk++)
						 {
							 if (is_shadow_claster[kk] == true)
								 continue;

							 double average_color_non_shadow = 0;
							 double R_avg_non_shadow = 0;
							 double G_avg_non_shadow = 0;
							 double B_avg_non_shadow = 0;

							 double Y_avg_non_shadow = 0;
							 double Cb_avg_non_shadow = 0;
							 double Cr_avg_non_shadow = 0;
							 for (int jj = 0; jj < n_k[kk]; jj++)
							 {
								 int index = clusters_elements[kk][jj];
								 int R = buffer[index * 3];
								 int G = buffer[index * 3 + 1];
								 int B = buffer[index * 3 + 2];

								 int Cb = buffer[index * 3 + 1];
								 int Cr = buffer[index * 3 + 2];

								 //average_color_non_shadow += (double)((R + G + B) / 3.0);
								 average_color_non_shadow += (double)((R + G + B));
								 R_avg_non_shadow += R;
								 G_avg_non_shadow += G;
								 B_avg_non_shadow += B;

								 Cb_avg_non_shadow += G;
								 Cr_avg_non_shadow += B;
							 }
							 average_color_non_shadow = average_color_non_shadow / (n_k[kk]);
							 R_avg_non_shadow /= n_k[kk];
							 G_avg_non_shadow /= n_k[kk];
							 B_avg_non_shadow /= n_k[kk];

							 Cb_avg_non_shadow /= n_k[kk];
							 Cr_avg_non_shadow /= n_k[kk];

							 average_color_non_shadow = (R_avg_non_shadow + G_avg_non_shadow + B_avg_non_shadow) / 3;


							 //							 if (abs(average_color_non_shadow - average_color) < diff)
							 //							 {
							 //								 min_average_diff_cluster = kk;
							 //								 diff = abs(average_color_non_shadow - average_color);
							 //							 }
							 //							 

							 //							 double diffTotal = average_color_non_shadow - average_color;
							 //							 if ((abs(R_avg_non_shadow - R_avg_shadow) < R_diff) && (abs(G_avg_non_shadow - G_avg_shadow) < G_diff) && (abs(B_avg_non_shadow - B_avg_shadow) < B_diff))
							 //							 {
							 //								 min_average_diff_cluster = kk;
							 //								 diff = abs(average_color_non_shadow - average_color);
							 //								 R_diff = abs(R_avg_non_shadow - R_avg_shadow);
							 //								 G_diff = abs(G_avg_non_shadow - G_avg_shadow);
							 //								 B_diff = abs(B_avg_non_shadow - B_avg_shadow);
							 //							 }

							 int k__ = k;
							 int kk__ = kk;
							 if ((abs(Cr_avg_non_shadow - Cr_avg_shadow) < Cr_diff) && (abs(Cb_avg_non_shadow - Cb_avg_shadow) < Cb_diff))
							 {
								 min_average_diff_cluster = kk;
								 Cb_diff = abs(Cb_avg_non_shadow - Cb_avg_shadow);
								 Cr_diff = abs(Cr_avg_non_shadow - Cr_avg_shadow);
							 }
						 }
						 int asda = 0;

						 if (min_average_diff_cluster < 0)
						 {
							 Sleep(10);
						 }

						 //						 if (k == 5)
						 //							 min_average_diff_cluster = 3;
						 //						 if (k == 7)
						 //							 min_average_diff_cluster = 2;
						 //min_average_diff_cluster = 2;

						 //Коректуємо колір даного тіньового кластера з знайденим
						 double R_avg_other = 0;
						 double G_avg_other = 0;
						 double B_avg_other = 0;
						 for (int j = 0; j < n_k[min_average_diff_cluster]; j++)
						 {
							 int index = clusters_elements[min_average_diff_cluster][j];
							 int R = buffer[index * 3];
							 int G = buffer[index * 3 + 1];
							 int B = buffer[index * 3 + 2];

							 R_avg_other += R;
							 G_avg_other += G;
							 B_avg_other += B;
						 }
						 R_avg_other /= n_k[min_average_diff_cluster];
						 G_avg_other /= n_k[min_average_diff_cluster];
						 B_avg_other /= n_k[min_average_diff_cluster];

						 double R_avg_curr = 0;
						 double G_avg_curr = 0;
						 double B_avg_curr = 0;
						 for (int j = 0; j < n_k[k]; j++)
						 {
							 int index = clusters_elements[k][j];
							 int R = buffer[index * 3];
							 int G = buffer[index * 3 + 1];
							 int B = buffer[index * 3 + 2];

							 R_avg_curr += R;
							 G_avg_curr += G;
							 B_avg_curr += B;
						 }
						 R_avg_curr /= n_k[k];
						 G_avg_curr /= n_k[k];
						 B_avg_curr /= n_k[k];

						 //Values to add/sub
						 int Red = R_avg_other - R_avg_curr;
						 int Green = G_avg_other - G_avg_curr;
						 int Blue = B_avg_other - B_avg_curr;
						 int RGB = 0;

						 double R_ratio = (R_avg_other / R_avg_curr);
						 double G_ratio = (G_avg_other / G_avg_curr);
						 double B_ratio = (B_avg_other / B_avg_curr);
						 int asdasdasdasd = 0;

						 //Color correction
						 /*
						 for (int j = 0; j < n_k[k]; j++)
						 {
						 int index = clusters_elements[k][j];
						 buffer[index * 3] + Red + RGB>255 ? buffer[index * 3] = 255 : (buffer[index * 3] + Red + RGB < 0 ? buffer[index * 3] = 0 : buffer[index * 3] += Red + RGB);//Red
						 buffer[index * 3 + 1] + Green + RGB>255 ? buffer[index * 3 + 1] = 255 : (buffer[index * 3 + 1] + Green + RGB<0 ? buffer[index * 3 + 1] = 0 : buffer[index * 3 + 1] += Green + RGB);//Green
						 buffer[index * 3 + 2] + Blue + RGB>255 ? buffer[index * 3 + 2] = 255 : (buffer[index * 3 + 2] + Blue + RGB<0 ? buffer[index * 3 + 2] = 0 : buffer[index * 3 + 2] += Blue + RGB);//Blue
						 }
						 */

						 int CURRENT = k;
						 int MIN_DIFF = min_average_diff_cluster;

						 int maxI = 0;
						 for (int j = 0, index = 0; j < n_k[k]; j++)
						 {
							 index = clusters_elements[k][j];

							 if (index > maxI)
								 maxI = index;

							 int currR = buffer[index * 3];
							 int currG = buffer[index * 3 + 1];
							 int currB = buffer[index * 3 + 2];

							 //							 currR += Red;
							 //							 currG += Green;
							 //							 currB += Blue;

							 //currR *= R_ratio;
							 currG *= G_ratio;
							 currB *= B_ratio;

							 //							 //Зафарбувати в середні кольори
							 //							 buffer[index * 3] = (unsigned char)R_avg_other;//Red
							 //							 buffer[index * 3 + 1] = (unsigned char)G_avg_other;//Green
							 //							 buffer[index * 3 + 2] = (unsigned char)B_avg_other;//Blue

							 //							 currR += -46;
							 //							 currG += -40;// -36;//Green
							 //							 currB += -19;// -11;//Blue

							 currR = currR > 255 ? 255 : (currR < 0 ? 0 : currR);
							 currG = currG > 255 ? 255 : (currG < 0 ? 0 : currG);
							 currB = currB > 255 ? 255 : (currB < 0 ? 0 : currB);

							 buffer[index * 3] = currR;//Red
							 buffer[index * 3 + 1] = currG;//Green
							 buffer[index * 3 + 2] = currB;//Blue

						 }

						 /////////////////////

						 //Показати два кластери що коректуються
						 //////Візуалізація результату кластеризації у виглядi кольорів
						 //int classR = 180;
						 //int classG = 255;
						 //int classB = 0;
						 //for (int kkk = 0; kkk < K; kkk++)
						 //{
						 // /*if (kkk != k || kkk != min_average_diff_cluster)
						 //	 continue;*/

						 // for (int q = 0; q < Q; q++)
						 // {
						 //	 X[q][0] = 0;
						 //	 X[q][1] = 255;
						 //	 X[q][2] = 208;
						 //	 if (class_q[q] == k)
						 //	 {
						 //		 X[q][0] = 0;
						 //		 X[q][1] = 0;
						 //		 X[q][2] = 0;
						 //	 }
						 //	 if (class_q[q] == min_average_diff_cluster)
						 //	 {
						 //		 X[q][0] = 0;
						 //		 X[q][1] = 0;
						 //		 X[q][2] = 255;
						 //	 }
						 // }
						 // classR -= rand() % 70;
						 // classG -= rand() % 255;
						 // classB += rand() % 255;
						 //}

						 ////Copy X to buffer
						 //for (int iii = 0, jjj = 0; jjj < size; iii += 1, jjj += 3)
						 //{
						 // int RR = buffer[jjj];
						 // int XR = X[iii][0];

						 // buffer[jjj] = X[iii][0];
						 // buffer[jjj + 1] = X[iii][1];
						 // buffer[jjj + 2] = X[iii][2];
						 //}


						 //SaveBMP();
						 //ShowBmp();
						 //int a = 0;
						 /////////////////////////
						 ////break;
						 //CopyArrayUCHAR(bufferBackup, buffer, size);
						 /*SaveBMP();
						 ShowBmp();*/

					 }


					 if (checkBoxClusterVisual->Checked)
					 {

						 double **X = new double *[Q];
						 for (int i = 0; i < Q; i++){
							 X[i] = new double[Qn + 1]; //include L
						 }

						 //Візуалізація результату кластеризації у виглядi кольорів
						 int classR = 180;
						 int classG = 255;
						 int classB = 0;

						 for (int k = 0; k < K; k++)
						 {
							 if (k == 0)
							 {
								 classR = 255;
								 classG = 255;
								 classB = 255;
							 }
							 if (k == 1)//красный
							 {
								 classR = 0;
								 classG = 0;
								 classB = 255;
							 }
							 if (k == 2)//зеленый
							 {
								 classR = 0;
								 classG = 255;
								 classB = 0;
							 }
							 if (k == 3)//синий
							 {
								 classR = 255;
								 classG = 0;
								 classB = 0;
							 }
							 if (k == 4)//розовый
							 {
								 classR = 209;
								 classG = 100;
								 classB = 255;
							 }


							 if (k == 5)//оранжевый
							 {
								 classR = 0;
								 classG = 213;
								 classB = 255;
							 }
							 if (k == 6)//берюзовый
							 {
								 classR = 255;
								 classG = 252;
								 classB = 50;
							 }
							 if (k == 7)//фиолетовый /бледно-синий
							 {
								 classR = 255;
								 classG = 0;
								 classB = 191;

								 //								 classR = 255;
								 //								 classG = 128;
								 //								 classB = 128;
							 }
							 if (k == 8)//черный
							 {
								 classR = 0;
								 classG = 0;
								 classB = 0;
							 }
							 if (k == 9)//желтовато-зеленый
							 {
								 classR = 0;
								 classG = 240;
								 classB = 232;
							 }

							 for (int q = 0; q < Q; q++)
							 {
								 if (class_q[q] == k)
								 {
									 X[q][0] = classR;
									 X[q][1] = classG;
									 X[q][2] = classB;
								 }
							 }
							 classR -= rand() % 70;
							 classG -= rand() % 255;
							 classB += rand() % 255;
						 }

						 //Copy X to buffer
						 UCHAR * buffer2 = new UCHAR[size];
						 for (int i = 0, j = 0; j < size; i += 1, j += 3)
						 {
							 buffer2[j] = X[i][0];
							 buffer2[j + 1] = X[i][1];
							 buffer2[j + 2] = X[i][2];
						 }

						 CopyArrayToMat(buffer2, imgResVisual);

						 ////FOR SPECIAL CLUSTERS
						 //						 for (int k = 0; k < K; k++)
						 //						 {
						 ////							 if (k == 5)//оранжевый
						 ////							 {
						 ////								 classR = 0;
						 ////								 classG = 213;
						 ////								 classB = 255;
						 ////							 }
						 //							 if (k == 7)//фиолетовый /бледно-синий
						 //							{
						 //								classR = 255;
						 //								classG = 0;
						 //								classB = 191;
						 //								 
						 ////								 classR = 255;
						 ////								 classG = 128;
						 ////								 classB = 128;
						 //							}
						 //							 else//берюзовый
						 //							 {
						 //								 classR = 255;
						 //								 classG = 252;
						 //								 classB = 50;
						 //							 }
						 //
						 //							 for (int j = 0; j < n_k[k]; j++)
						 //							 {
						 //								 int index = clusters_elements[k][j];
						 //
						 //								 buffer[index * 3] = classR;//Red
						 //								 buffer[index * 3 + 1] = classG;//Green
						 //								 buffer[index * 3 + 2] = classB;//Blue
						 //
						 //							 }
						 //						 }


					 }

					 ////###////###/////####

					 break;
				 }
			 }

}

private: void ApplyMeanShiftAndCorrections(cv::Mat &imgForCluster, cv::Mat &imgForAlign, cv::Mat &imgResVisual)
{
//			 IplImage *img = cvLoadImage("MeanShift/input.png");
//			 cv::Mat imgBGR = cv::imread(myPath_char);
			 IplImage *img = cvCloneImage(&(IplImage)imgForCluster);

			 // Mean shift
			 int **ilabels = new int *[img->height];

			 for (int i = 0; i<img->height; i++)
				 ilabels[i] = new int[img->width];

			 int regionCount = MeanShift(img, ilabels);
			 
			 cv::Mat imgShadowMask = imgForCluster.clone();
			 CopyArrayToMat(shadowMask, imgShadowMask);

			 ///////////////////////////////////////////////////////
			 //determine regions contain both shadow and non0shadow pixels
			 std::vector<int> regions_to_separate;
			 for (int r = 0; r < regionCount; r++) {
				 int CURRENT_LABEL = r;
				 bool is_non_shadow_region = false;
				 bool is_shadow_region = false;
				 for (int i = 0; i < imgShadowMask.rows; i++) {
					 bool break_ = false;
					 for (int j = 0; j < imgShadowMask.cols; j++) {

						 //Handle current region
						 int cl = ilabels[i][j];
						 if (cl != CURRENT_LABEL)
						 {
							 continue;
						 }

						 //Handle shadow region
						 cv::Vec3b &shadowPixelMask = imgShadowMask.at<cv::Vec3b>(i, j);
						 if (shadowPixelMask.val[0] == 255)
						 {
							 is_non_shadow_region = true;
						 }
						 else
						 {
							 is_shadow_region = true;
						 }

						 if (is_non_shadow_region && is_shadow_region)
						 {
							 regions_to_separate.push_back(CURRENT_LABEL);
							 break_ = true;
							 break;
						 }
					 }
					 if (break_) break;
				 }
			 }

			 //Save old segmentaion info
			 int **ilabelsOld = new int *[img->height];
			 for (int i = 0; i<img->height; i++)
				 ilabelsOld[i] = new int[img->width];
			 CopyMatrixToMatrix(ilabels, ilabelsOld, img->height, img->width);
			 int regionCountOld = regionCount;

			 // Draw random color for old segmentaion
			 cv::vector<int> color2(regionCount);
			 CvRNG rng2 = cvRNG(cvGetTickCount());
			 for (int i = 0; i<regionCount; i++)
				 color2[i] = cvRandInt(&rng2);

			 cv::Mat imgSegmentationResOld(img);
			 for (int i = 0; i < imgSegmentationResOld.rows; i++) {
				 for (int j = 0; j < imgSegmentationResOld.cols; j++) {
					 cv::Vec3b &pixel = imgSegmentationResOld.at<cv::Vec3b>(i, j);

					 int cl = ilabelsOld[i][j];

					 if (cl >= regionCountOld)
						 int a = 0;

					 pixel.val[0] = (color2[cl]) & 255;
					 pixel.val[1] = (color2[cl] >> 8) & 255;
					 pixel.val[2] = (color2[cl] >> 16) & 255;
				 }
			 }
			 cv::imshow("imgSegmentationResOld", imgSegmentationResOld);

			 //separate such regions on two (old label - non shadow, new label - shadow region)
			 for (std::vector<int>::size_type r = 0; r != regions_to_separate.size(); r++)
			 {
				 int CURRENT_LABEL = regions_to_separate[r];
				 for (int i = 0; i < imgShadowMask.rows; i++) {
					 bool break_ = false;
					 for (int j = 0; j < imgShadowMask.cols; j++) {

						 //Handle current region
						 int cl = ilabels[i][j];
						 if (cl != CURRENT_LABEL)
						 {
							 continue;
						 }

						 cv::Vec3b &shadowPixelMask = imgShadowMask.at<cv::Vec3b>(i, j);
						 //Assign new label for shadow pixels AND Leave old label for non shadow pixels
						 if (shadowPixelMask.val[0] == 255)
						 {
							 ilabels[i][j] = regionCount;
						 }	 
					 }
					 if (break_) break;
				 }
				 regionCount += 1;
			 }
			 //////////////////////////////////////////////////////

			 cv::Mat imgSourceLAB;
			 cv::cvtColor(imgForAlign, imgSourceLAB, CV_BGR2Lab);

			 cv::Mat imgResLAB;
			 cv::Mat imgResLABAddLDiff;
			 cv::cvtColor(imgForAlign, imgResLAB, CV_BGR2Lab);
			 cv::cvtColor(imgForAlign, imgResLABAddLDiff, CV_BGR2Lab);
			 cv::Mat imgResBGR;
			 cv::Mat imgResBGRAddDiff;


			 ////@@
			 //Count pixels for each region
			 int *ilablesCount = new int[regionCount];
			 for (int r = 0; r < regionCount; r++)
			 {
				 ilablesCount[r] = 0;
			 }
			 for (int r = 0; r < regionCount; r++) {
				 int CURRENT_LABEL = r;
				 for (int i = 0; i < imgSourceLAB.rows; i++) {
					 bool break_ = false;
					 for (int j = 0; j < imgSourceLAB.cols; j++) {

						 //Handle current region
						 int cl = ilabels[i][j];
						 if (cl != CURRENT_LABEL)
						 {
							 continue;
						 }

						 ilablesCount[r] += 1;
					 }
				 }
			 }
			 ////@@

			 //Loop through all labels (clusters)
			 for (int iterations = 0; iterations < 1; iterations++){
				 for (int r = 0; r < regionCount; r++) {
					 int CURRENT_LABEL = r;
					 int SHADOW_LABEL = -1;
					 int NON_SHADOW_LABEL = -1;

					 double L_shadow_avg = 0;
					 double A_shadow_avg = 0;
					 double B_shadow_avg = 0;
					 int count = 0;

					 double L_non_shadow_avg = 0;
					 double A_non_shadow_avg = 0;
					 double B_non_shadow_avg = 0;


					 //Take Shadow Regions
					 for (int i = 0; i < imgSourceLAB.rows; i++) {
						 for (int j = 0; j < imgSourceLAB.cols; j++) {

							 //Handle current region
							 int cl = ilabels[i][j];
							 if (cl != CURRENT_LABEL)
							 {
								 continue;
							 }

							 //Handle shadow region
							 cv::Vec3b &shadowPixelMask = imgShadowMask.at<cv::Vec3b>(i, j);
							 if (shadowPixelMask.val[0] != 255)
							 {
								 continue;
							 }

							 cv::Vec3b &pixel = imgSourceLAB.at<cv::Vec3b>(i, j);

							 L_shadow_avg += pixel.val[0];
							 A_shadow_avg += pixel.val[1];
							 B_shadow_avg += pixel.val[2];
							 count++;
						 }
					 }
					 //If current region do not contain shadow pixels, go to next region
					 if (count == 0)
					 {
						 continue;
					 }
					 L_shadow_avg /= count;
					 A_shadow_avg /= count;
					 B_shadow_avg /= count;

					 SHADOW_LABEL = CURRENT_LABEL;

					 //////
					 //Find neightbor non shadow regions
					 //////

					 //Loop through current shadow region's pixels and find adjacent non shadow regions
					 std::vector<int> adjacent_labels;
					 int min_adjacent_labels_required = 1;
					 int max_deviation = 20;
					 int max_iterations = max_deviation*100;
					 for (int it = 0; adjacent_labels.size() < min_adjacent_labels_required; it++) {
						 for (int dev = 1; dev <= max_deviation; dev++) {
							 for (int i = 0; i < imgSourceLAB.rows; i++) {
								 bool break_ = false;
								 for (int j = 0; j < imgSourceLAB.cols; j++) {

									 //Handle current region
									 int cl = ilabels[i][j];
									 if (cl != CURRENT_LABEL) //CURRENT_LABEL == SHADOW_LABEL
									 {
										 continue;
									 }

									 //Go 1px to 4 base direction - up,down,left,right
									 if (i + dev < imgSourceLAB.rows)
									 {
										 cv::Vec3b &pixelDown = imgShadowMask.at<cv::Vec3b>(i + dev, j);
										 //if non shadow
										 if (pixelDown.val[0] == 0){
											 //adjacent_labels.push_back(ilabels[i + 1][j]);
											 int ilabel = ilabels[i + dev][j];
											 if (std::find(adjacent_labels.begin(), adjacent_labels.end(), ilabel) == adjacent_labels.end()) {
												 adjacent_labels.push_back(ilabel);
											 }
										 }
									 }
									 if (i - dev >= 0)
									 {
										 cv::Vec3b &pixelUp = imgShadowMask.at<cv::Vec3b>(i - dev, j);
										 //if non shadow
										 if (pixelUp.val[0] == 0){
											 //adjacent_labels.push_back(ilabels[i - 1][j]);
											 int ilabel = ilabels[i - dev][j];
											 if (std::find(adjacent_labels.begin(), adjacent_labels.end(), ilabel) == adjacent_labels.end()) {
												 adjacent_labels.push_back(ilabel);
											 }
										 }
									 }
									 if (j + dev < imgSourceLAB.cols)
									 {
										 cv::Vec3b &pixelRight = imgShadowMask.at<cv::Vec3b>(i, j + dev);
										 //if non shadow
										 if (pixelRight.val[0] == 0){
											 //adjacent_labels.push_back(ilabels[i][j + 1]);
											 int ilabel = ilabels[i][j + dev];
											 if (std::find(adjacent_labels.begin(), adjacent_labels.end(), ilabel) == adjacent_labels.end()) {
												 adjacent_labels.push_back(ilabel);
											 }
										 }
									 }
									 if (j - dev >= 0)
									 {
										 cv::Vec3b &pixelLeft = imgShadowMask.at<cv::Vec3b>(i, j - dev);
										 //if non shadow
										 if (pixelLeft.val[0] == 0){
											 //adjacent_labels.push_back(ilabels[i][j - 1]);
											 int ilabel = ilabels[i][j - dev];
											 if (std::find(adjacent_labels.begin(), adjacent_labels.end(), ilabel) == adjacent_labels.end()) {
												 adjacent_labels.push_back(ilabel);
											 }
										 }
									 }

								 }
								 if (break_) break;
							 }
						 }
						 max_deviation += 10;
						 if (it > max_iterations) break;
					 }

					 //Find in adjacent regions one closest in chromatacity
					 double L_diff = 255;
					 double A_diff = 255;
					 double B_diff = 255;
					 double AB_diff_avg = 255;

					 double LAB_delta_e_metric = 255;
					 //for (int r2 = 0; r2 < regionCount; r2++) 
					 for (std::vector<int>::size_type r2 = 0; r2 != adjacent_labels.size(); r2++)
					 {
						 int CURRENT_LABEL2 = adjacent_labels[r2];

						 double L_non_shadow_avg__ = 0;
						 double A_non_shadow_avg__ = 0;
						 double B_non_shadow_avg__ = 0;
						 int count2 = 0;

						 //Take Shadow Regions
						 for (int i = 0; i < imgSourceLAB.rows; i++) {
							 for (int j = 0; j < imgSourceLAB.cols; j++) {

								 //Handle current region
								 int cl = ilabels[i][j];
								 if (cl != CURRENT_LABEL2)
								 {
									 continue;
								 }

								 cv::Vec3b &pixel = imgSourceLAB.at<cv::Vec3b>(i, j);

								 L_non_shadow_avg__ += pixel.val[0];
								 A_non_shadow_avg__ += pixel.val[1];
								 B_non_shadow_avg__ += pixel.val[2];
								 count2++;
							 }
						 }
						 //If current region do not contain non shadow pixels, go to next region
						 if (count2 == 0)
						 {
							 continue;
						 }
						 L_non_shadow_avg__ /= count2;
						 A_non_shadow_avg__ /= count2;
						 B_non_shadow_avg__ /= count2;

						 int SHADOW_LABEL_COUNT = ilablesCount[CURRENT_LABEL];
						 int NON_SHADOW_LABEL_COUNT = ilablesCount[CURRENT_LABEL2];
						 if (NON_SHADOW_LABEL_COUNT < SHADOW_LABEL_COUNT*0.1)
							 continue;

						 //Compare chrom values to define minimum diff region
						 double L_abs_diff = abs(L_shadow_avg - L_non_shadow_avg__);
						 double A_abs_diff = abs(A_shadow_avg - A_non_shadow_avg__);
						 double B_abs_diff = abs(B_shadow_avg - B_non_shadow_avg__);
						 double AB_abs_diff_avg = (A_abs_diff + B_abs_diff) / 2.0;

						 double MAX_A_DIFF = 18;
						 double MAX_B_DIFF = 18;

//						 if (A_abs_diff > MAX_A_DIFF || B_abs_diff > MAX_B_DIFF)
//							 continue;
						 double *a = new double[3] {1,2,3};
						 //double delta_e_metric = CIE76::GetMetric(cv::Vec3b(L_shadow_avg, A_shadow_avg, B_shadow_avg), cv::Vec3b(L_non_shadow_avg__, A_non_shadow_avg__, B_non_shadow_avg__));
						 double delta_e_metric = CIE76::GetMetric(new double[2]{A_shadow_avg, B_shadow_avg}, new double[2]{ A_non_shadow_avg__, B_non_shadow_avg__},2);

						 if (delta_e_metric < LAB_delta_e_metric)
						 {
							 LAB_delta_e_metric = delta_e_metric;

							 NON_SHADOW_LABEL = CURRENT_LABEL2;

							 L_non_shadow_avg = L_non_shadow_avg__;
							 A_non_shadow_avg = A_non_shadow_avg__;
							 B_non_shadow_avg = B_non_shadow_avg__;
						 }

//						 if ((A_abs_diff < A_diff && B_abs_diff < B_diff) || AB_abs_diff_avg < AB_diff_avg)
//						 {
//							 A_diff = A_abs_diff;
//							 B_diff = B_abs_diff;
//							 AB_diff_avg = AB_abs_diff_avg;
//							 NON_SHADOW_LABEL = CURRENT_LABEL2;
//
//							 L_non_shadow_avg = L_non_shadow_avg__;
//							 A_non_shadow_avg = A_non_shadow_avg__;
//							 B_non_shadow_avg = B_non_shadow_avg__;
//						 }
					 }
					 /////

//					 if (SHADOW_LABEL == -1 || NON_SHADOW_LABEL == -1)
//						 MessageBox::Show("NO LABEL");

					 if (SHADOW_LABEL == -1 || NON_SHADOW_LABEL == -1)
						 continue;

					 int SHADOW_LABEL_COPY = SHADOW_LABEL;
					 int NON_SHADOW_LABEL_COPY = NON_SHADOW_LABEL;
					 int SHADOW_LABEL_COUNT = ilablesCount[SHADOW_LABEL];
					 int NON_SHADOW_LABEL_COUNT = ilablesCount[NON_SHADOW_LABEL];

					 //Find values
					 double L_diff_ = L_non_shadow_avg - L_shadow_avg;
					 double A_diff_ = A_non_shadow_avg - A_shadow_avg;
					 double B_diff_ = B_non_shadow_avg - B_shadow_avg;

					 double L_ratio = L_non_shadow_avg / L_shadow_avg;
					 double A_ratio = A_non_shadow_avg / A_shadow_avg;
					 double B_ratio = B_non_shadow_avg / B_shadow_avg;

					 //Perform COLOR ALIGNMENT 
					 for (int i = 0; i < imgResLAB.rows; i++) {
						 for (int j = 0; j < imgResLAB.cols; j++) {

							 //Handle current region
							 int cl = ilabels[i][j];
							 if (cl != CURRENT_LABEL)
							 {
								 continue;
							 }

							 //Handle shadow region
							 cv::Vec3b &shadowPixelMask = imgShadowMask.at<cv::Vec3b>(i, j);
							 if (shadowPixelMask.val[0] != 255)
							 {
								 continue;
							 }

							 cv::Vec3b &pixel = imgResLAB.at<cv::Vec3b>(i, j);

							 double L = pixel.val[0];
							 double A = pixel.val[1];
							 double B = pixel.val[2];

							 L *= L_ratio;
							 //L += L_diff_;
							 A *= A_ratio;
							 B *= B_ratio;

							 L = (L > 255 ? 255 : (L < 0 ? 0 : L));
							 A = (A > 255 ? 255 : (A < 0 ? 0 : A));
							 B = (B > 255 ? 255 : (B < 0 ? 0 : B));
							

							pixel.val[0] = L;
							pixel.val[1] = A;
							pixel.val[2] = B;

							 if (SHADOW_LABEL == 11)
							 {
//								 pixel.val[0] = 0;
//								 pixel.val[1] = 0;
//								 pixel.val[2] = 255;
							 }

							 //Add diff image
							 
							 cv::Vec3b &pixel2 = imgResLABAddLDiff.at<cv::Vec3b>(i, j);
							 double L2 = pixel2.val[0];
							 double A2 = pixel2.val[1];
							 double B2 = pixel2.val[2];
							 L2 += L_diff_;
							 A2 *= A_ratio;
							 B2 *= B_ratio;
							 L2 = (L2 > 255 ? 255 : (L2 < 0 ? 0 : L2));
							 A2 = (A2 > 255 ? 255 : (A2 < 0 ? 0 : A2));
							 B2 = (B2 > 255 ? 255 : (B2 < 0 ? 0 : B2));
							 pixel2.val[0] = L2;
							 pixel2.val[1] = A2;
							 pixel2.val[2] = B2;
						 }
					 }


					 int a = 0;

				 }

				 imgSourceLAB = imgResLAB.clone();
			 }
			 cv::cvtColor(imgResLAB, imgResBGR, CV_Lab2BGR);
			 cv::cvtColor(imgResLABAddLDiff, imgResBGRAddDiff, CV_Lab2BGR);
			 cv::imshow("!! imgResBGR", imgResBGR);
			 cv::imshow("!! imgResBGRAddDiff", imgResBGRAddDiff);

			 cv::cvtColor(imgResLAB, imgResBGR, CV_Lab2BGR);
			 imgForAlign = imgResBGR.clone();

//			 // Draw random color
//			 cv::Mat imgRes(img);
//			 cv::Mat imgResBGR = imgRes.clone();
//			 for (int i = 0; i < imgResBGR.rows; i++) {
//				 for (int j = 0; j < imgResBGR.cols; j++) {
//
//
//					 cv::Vec3b &pixel = imgResBGR.at<cv::Vec3b>(i, j);
//
//					 int cl = ilabels[i][j];
//
//					 pixel.val[0] = (color[cl]) & 255;
//					 pixel.val[1] = (color[cl] >> 8) & 255;
//					 pixel.val[2] = (color[cl] >> 16) & 255;
//				 }
//			 }
//
//			 cv::imshow("TEST", imgResBGR);

			 // Draw random color

			 cv::vector<int> color(regionCount);
			 CvRNG rng = cvRNG(cvGetTickCount());
			 for (int i = 0; i<regionCount; i++)
				 color[i] = cvRandInt(&rng);

			 for (int i = 0; i<img->height; i++)
				 for (int j = 0; j<img->width; j++)
				 {
					 int cl = ilabels[i][j];
					 ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 0] = (color[cl]) & 255;
					 ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 1] = (color[cl] >> 8) & 255;
					 ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 2] = (color[cl] >> 16) & 255;
				 }


				 cv::Mat resultVisual(img);
				 imgResVisual = resultVisual.clone();
//			 cvNamedWindow("MeanShift2", CV_WINDOW_AUTOSIZE);
//			 cvShowImage("MeanShift2", img);
}

//mean Shift - returns regionCount and labels
private: void ApplyMeanShift(cv::Mat &imgForCluster, int &regionCountForReturn, int **ilabelsForReturn)
{
			 //			 IplImage *img = cvLoadImage("MeanShift/input.png");
			 //			 cv::Mat imgBGR = cv::imread(myPath_char);
			 IplImage *img = cvCloneImage(&(IplImage)imgForCluster);

			 // Mean shift
			 int **ilabels = new int *[img->height];

			 for (int i = 0; i<img->height; i++)
				 ilabels[i] = new int[img->width];

			 int regionCount = MeanShift(img, ilabels);

			 regionCountForReturn = regionCount;
			 //ilabelsForReturn = ilabels;
			 CopyMatrixToMatrix(ilabels, ilabelsForReturn, img->height, img->width);

			 cv::Mat imgVisual = imgForCluster.clone();
			 VisualizeMeanShift(regionCount, ilabels, imgVisual);
			 }

private: void VisualizeMeanShift(int regionCount,int **ilabels, cv::Mat &imgResVisual)
{
			 //			 IplImage *img = cvLoadImage("MeanShift/input.png");
			 //			 cv::Mat imgBGR = cv::imread(myPath_char);
			 IplImage *img = cvCloneImage(&(IplImage)imgResVisual);

			 cv::vector<int> color(regionCount);
			 CvRNG rng = cvRNG(cvGetTickCount());

			 for (int i = 0; i<regionCount; i++)
				 color[i] = cvRandInt(&rng);

			 //			 // Draw random color
			 //			 cv::Mat imgRes(img);
			 //			 cv::Mat imgResBGR = imgRes.clone();
			 //			 for (int i = 0; i < imgResBGR.rows; i++) {
			 //				 for (int j = 0; j < imgResBGR.cols; j++) {
			 //
			 //
			 //					 cv::Vec3b &pixel = imgResBGR.at<cv::Vec3b>(i, j);
			 //
			 //					 int cl = ilabels[i][j];
			 //
			 //					 pixel.val[0] = (color[cl]) & 255;
			 //					 pixel.val[1] = (color[cl] >> 8) & 255;
			 //					 pixel.val[2] = (color[cl] >> 16) & 255;
			 //				 }
			 //			 }
			 //
			 //			 cv::imshow("TEST", imgResBGR);

			 // Draw random color
			 for (int i = 0; i<img->height; i++)
			 for (int j = 0; j<img->width; j++)
			 {
				 int cl = ilabels[i][j];
				 ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 0] = (color[cl]) & 255;
				 ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 1] = (color[cl] >> 8) & 255;
				 ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 2] = (color[cl] >> 16) & 255;
			 }


			 cv::Mat resultVisual(img);
			 imgResVisual = resultVisual.clone();
			 cv::imshow("VisualizeMeanShift", imgResVisual);
			 //			 cvNamedWindow("MeanShift2", CV_WINDOW_AUTOSIZE);
			 //			 cvShowImage("MeanShift2", img);
}

//
private: System::Void button1Shadow4Math_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 cv::Mat imgBGR;
			 cv::Mat imgGaussian;
			 cv::Mat imgMeanShift;
			 cv::Mat imgMeanShiftGrayscal;
			 cv::Mat imgMeanShiftRes;
			 cv::Mat imgThresholdFixed;
			 cv::Mat imgres;

			 imgBGR = cv::imread(myPath_char);
 
			 cv::GaussianBlur(imgBGR, imgGaussian, cv::Size(7, 7), 0);

			 //cv::pyrMeanShiftFiltering(imgGaussian, imgMeanShift, 20, 20, 1);
			 cv::pyrMeanShiftFiltering(imgGaussian, imgMeanShift, 25, 25, 1);
			 imgMeanShiftRes = imgMeanShift.clone();
			 floodFillPostprocess(imgMeanShiftRes, cv::Scalar::all(2));

			 //Convert BGR to Gray
			 cv::cvtColor(imgMeanShift, imgMeanShiftGrayscal, CV_BGR2GRAY);

			 //AVG
			 double avg = 0;
			 int count = 0;
			 for (int i = 0; i < imgMeanShiftGrayscal.rows; i++) {
				 for (int j = 0; j < imgMeanShiftGrayscal.cols; j++) {

					 uchar &Pixel = imgMeanShiftGrayscal.at<uchar>(i, j);
					 
					 avg += Pixel;
					 count += 1;
				 }
			 }
			 avg /= count;

			 //STD DEV
			 count = 0;
			 double stdDev = 0;
			 for (int i = 0; i < imgMeanShiftGrayscal.rows; i++) {
				 for (int j = 0; j < imgMeanShiftGrayscal.cols; j++) {

					 uchar &Pixel = imgMeanShiftGrayscal.at<uchar>(i, j);

					 stdDev += pow(Pixel - avg, 2);
					 count += 1;
				 }
			 }
			 stdDev = stdDev*(1.0 / ((double)count - 1.0));
			 stdDev = sqrt(stdDev);
			 
			 textBoxGrayAvg->Text = System::Convert::ToString(avg);
			 textBoxGrayDev->Text = System::Convert::ToString(stdDev);

			 //Fixed Threshold
			 double thresh = avg - stdDev;
			 //double thresh = avg;
			 double maxValue = 255;

			 double custom_threshold = System::Convert::ToDouble(textBoxShadowDetectionThreshold->Text);
			 //If not equal 0 than apply custom threshold
			 if (custom_threshold > 0 && custom_threshold < 255)
			 {
				 thresh = custom_threshold;
			 }
			 //If equal 0 than set calculated threshold on form
			 else
			 {
				 textBoxShadowDetectionThreshold->Text = System::Convert::ToString(thresh);
			 }
			 
			 cv::threshold(imgMeanShiftGrayscal, imgThresholdFixed, thresh, maxValue, CV_THRESH_BINARY_INV); // Binary Threshold

//			 //Morfological operations
//			 cv::Mat elementDil1 = getStructuringElement(cv::MORPH_RECT,
//				 cv::Size(3, 3));
//			 cv::Mat elementDil2 = getStructuringElement(cv::MORPH_RECT,
//				 cv::Size(5, 5));
//
//			 cv::Mat imgThresholdFixedDil1;
//			 cv::Mat imgThresholdFixedDil2;
//			 cv::dilate(imgThresholdFixed, imgThresholdFixedDil1, elementDil1);
//			 cv::dilate(imgThresholdFixed, imgThresholdFixedDil2, elementDil2);
//
//			 cv::Mat imgThresholdFixedErode1;
//			 cv::erode(imgThresholdFixed, imgThresholdFixedErode1, elementDil1);
//
//			 imgThresholdFixed = imgThresholdFixedErode1.clone();
//
//			 cv::imshow("imgThresholdFixedDil1", imgThresholdFixedDil1);
//			 cv::imshow("imgThresholdFixedDil2", imgThresholdFixedDil2);
//			 cv::imshow("imgThresholdFixedErode1", imgThresholdFixedErode1);

//			 cv::imshow("1 imgBGR", imgBGR);
//			 cv::imshow("2 imgGaussian", imgGaussian);
//			 cv::imshow("3 imgMeanShift", imgMeanShift);
//			 cv::imshow("4 imgMeanShiftRes", imgMeanShiftRes);
			 cv::imshow("5 imgMeanShiftGrayscal", imgMeanShiftGrayscal);
			 cv::imshow("6 imgThresholdFixed", imgThresholdFixed);

			 //imgres = imgThresholdFixed.clone();
			 cv::cvtColor(imgThresholdFixed, imgres, CV_GRAY2BGR);
			 shadowMask = new UCHAR[size];
			 CopyMatToArray(imgres,shadowMask);

			 saveMaskBMP();
			 ShowMaskBmp();
}

//This colors the segmentations
private: void floodFillPostprocess(cv::Mat& img, const cv::Scalar& colorDiff /*= cv::Scalar::all(1)*/)
{
	 //colorDiff = cv::Scalar::all(1);

	CV_Assert(!img.empty());
	cv::RNG rng = cv::theRNG();
	cv::Mat mask(img.rows + 2, img.cols + 2, CV_8UC1, cv::Scalar::all(0));
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			if (mask.at<uchar>(y + 1, x + 1) == 0)
			{
				cv::Scalar newVal(rng(256), rng(256), rng(256));
				cv::floodFill(img, mask, cv::Point(x, y), newVal, 0, colorDiff, colorDiff);
			}
		}
	}
}

private: System::Void buttonHandleEdges_Click(System::Object^  sender, System::EventArgs^  e) {

			 cv::Mat imgBGRres = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth, CV_8UC3);
			 CopyArrayToMat(buffer, imgBGRres);
			 //cv::Mat shadowMaskMat = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth, CV_8UC3);

			 //Shadow edge detection
			 cv::Mat imgShadowMask;
			 cv::Mat imgShadowMaskGRAY;
			 cv::Mat imgEdge;
			 cv::Mat imgEdgeDilated;
			 cv::Mat imgEdgeDilatedForInpaint;
			 //cv::Mat imgEdgeInverted;
			 cv::Mat imgEdgeGaussianWhole;
			 cv::Mat imgEdgeGaussianEdgeOnly;
			 cv::Mat imgMedianWhole;
			 cv::Mat imgMedianEdgeOnly;

			 //imgShadowMask = imgBGRres.clone();
			 imgShadowMask = imgBGRres.clone();
			 CopyArrayToMat(shadowMask, imgShadowMask);
			 cv::cvtColor(imgShadowMask, imgShadowMaskGRAY, CV_BGR2GRAY);

			 cv::Canny(imgShadowMaskGRAY, imgEdge, 50, 150, 3);

			 cv::Mat elementDil2 = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(5, 5));
			 cv::Mat elementDil3 = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(3, 3));
			 cv::dilate(imgEdge, imgEdgeDilated, elementDil2);
			 cv::dilate(imgEdge, imgEdgeDilatedForInpaint, elementDil3);

			 imgEdgeGaussianEdgeOnly = imgBGRres.clone();
			 cv::GaussianBlur(imgBGRres, imgEdgeGaussianWhole, cv::Size(3, 3), 0);
			 imgEdgeGaussianWhole.copyTo(imgEdgeGaussianEdgeOnly, imgEdgeDilated);

			 imgMedianEdgeOnly = imgBGRres.clone();
			 cv::medianBlur(imgBGRres, imgMedianWhole, 3);
			 imgMedianWhole.copyTo(imgMedianEdgeOnly, imgEdgeDilated);
			 ///

			 //Inpaint edge artifacts
			 cv::Mat imgBGRInpainted;
			 //cv::inpaint(imgBGRres, imgEdgeDilatedForInpaint, imgBGRInpainted, 7, CV_INPAINT_TELEA);//CV_INPAINT_NS
			 cv::inpaint(imgBGRres, imgEdgeDilatedForInpaint, imgBGRInpainted, 2, CV_INPAINT_TELEA);//CV_INPAINT_NS
			 cv::imshow("imgBGRres", imgBGRres);
			 cv::imshow("imgBGRInpainted", imgBGRInpainted);

			 cv::imshow("imgEdgeGaussianEdgeOnly", imgEdgeGaussianEdgeOnly);
			 cv::imshow("imgMedianEdgeOnly", imgMedianEdgeOnly);
}

private: System::Void buttonTestMEANSHIFT_Click(System::Object^  sender, System::EventArgs^  e) {

//			 IplImage *img = cvLoadImage("MeanShift/input.png");
			 cv::Mat imgBGR = cv::imread(myPath_char);
			 IplImage *img = cvCloneImage(&(IplImage)imgBGR);

			 // Mean shift
			 int **ilabels = new int *[img->height];

			 for (int i = 0; i<img->height; i++) 
				 ilabels[i] = new int[img->width];

			 int regionCount = MeanShift(img, ilabels);

			 cv::vector<int> color(regionCount);
			 CvRNG rng = cvRNG(cvGetTickCount());

			 for (int i = 0; i<regionCount; i++)
				 color[i] = cvRandInt(&rng);

			 cvNamedWindow("MeanShift1", CV_WINDOW_AUTOSIZE);
			 cvShowImage("MeanShift1", img);

			 // Draw random color
			 for (int i = 0; i<img->height; i++)
				 for (int j = 0; j<img->width; j++)
				 {
					 int cl = ilabels[i][j];
					 ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 0] = (color[cl]) & 255;
					 ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 1] = (color[cl] >> 8) & 255;
					 ((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 2] = (color[cl] >> 16) & 255;
				 }

			 cvNamedWindow("MeanShift", CV_WINDOW_AUTOSIZE);
			 cvShowImage("MeanShift", img);
}


private: System::Void buttonBasicLightModelLAB_Click(System::Object^  sender, System::EventArgs^  e) {

			 //Add diff to L and correct A and B

			 cv::Mat imgBGR = cv::imread(myPath_char);
			 cv::Mat imgLAB;
			 cv::Mat imgShadowMask = imgBGR.clone();
			 CopyArrayToMat(shadowMask, imgShadowMask);
			 cv::cvtColor(imgBGR, imgLAB, CV_BGR2Lab);

			 int count_shadow = 0;
			 int count_non_shadow = 0;

			 double L_shadow = 0;
			 double A_shadow = 0;
			 double B_shadow = 0;

			 double L_non_shadow = 0;
			 double A_non_shadow = 0;
			 double B_non_shadow = 0;

			 for (int i = 0; i < imgLAB.rows; i++) {
				 for (int j = 0; j < imgLAB.cols; j++) {

					 cv::Vec3b &shadowPixelMask = imgShadowMask.at<cv::Vec3b>(i, j);
					 cv::Vec3b &pixel = imgLAB.at<cv::Vec3b>(i, j);
					 if (shadowPixelMask.val[0] == 255)
					 {
						 L_shadow += pixel.val[0];
						 A_shadow += pixel.val[1];
						 B_shadow += pixel.val[2];

						 count_shadow += 1;
					 }
					 else
					 {
						 L_non_shadow += pixel.val[0];
						 A_non_shadow += pixel.val[1];
						 B_non_shadow += pixel.val[2];

						 count_non_shadow += 1;
					 }
				 }
			 }

			 L_shadow /= count_shadow;
			 A_shadow /= count_shadow;
			 B_shadow /= count_shadow;

			 L_non_shadow /= count_non_shadow;
			 A_non_shadow /= count_non_shadow;
			 B_non_shadow /= count_non_shadow;

			 double diff_L = L_non_shadow - L_shadow;
			 double diff_A = A_non_shadow - A_shadow;
			 double diff_B = B_non_shadow - B_shadow;

			 double ratio_L = L_non_shadow / L_shadow;
			 double ratio_A = A_non_shadow / A_shadow;
			 double ratio_B = B_non_shadow / B_shadow;

			 //Mul on ratio
			 for (int i = 0; i < imgLAB.rows; i++) {
				 for (int j = 0; j < imgLAB.cols; j++) {

					 cv::Vec3b &shadowPixelMask = imgShadowMask.at<cv::Vec3b>(i, j);
					 cv::Vec3b &pixel = imgLAB.at<cv::Vec3b>(i, j);
					 if (shadowPixelMask.val[0] == 255)
					 {
						 int L = pixel.val[0];
						 int A = pixel.val[1];
						 int B = pixel.val[2];

						 L *= ratio_L;
						 A *= ratio_A;
						 B *= ratio_B;

//						 L += diff_L;
//						 A += diff_A;
//						 B += diff_B;

						 L = L > 255 ? 255 : (L < 0 ? 0 : L);
						 A = A > 255 ? 255 : (A < 0 ? 0 : A);
						 B = B > 255 ? 255 : (B < 0 ? 0 : B);

						 pixel.val[0] = L;
						 pixel.val[1] = A;
						 pixel.val[2] = B;
					 }
				 }
			 }

			 cv::cvtColor(imgLAB, imgBGR, CV_Lab2BGR);
			 CopyMatToArray(imgBGR, buffer);

			 SaveBMP();
			 ShowBmp();
}

private: System::Void buttonRemoveUsingConstant_Click(System::Object^  sender, System::EventArgs^  e) {

			 cv::Mat imgBGR = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth, CV_8UC3);
			 CopyArrayToMat(buffer, imgBGR);
			 cv::Mat shadowMaskMat = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth, CV_8UC3);
			 CopyArrayToMat(shadowMask, shadowMaskMat);

			 cv::Mat shadowMaskGRAY;
			 cv::cvtColor(shadowMaskMat, shadowMaskGRAY, CV_BGR2GRAY);

			 cv::Mat imgEdge;
			 cv::Mat imgEdgeD;
			 cv::Canny(shadowMaskGRAY, imgEdge, 50, 150, 3);

			 cv::Mat elementD = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(3,3));
			 cv::dilate(imgEdge, imgEdgeD, elementD);

			 cv::imshow("imgEdge", imgEdge);
			 cv::imshow("imgEdgeD", imgEdgeD);

			 imgEdge = imgEdgeD.clone();

			 std::vector<int*> border_adjacent_shadow_pixels_indexes = std::vector<int*>();
			 std::vector<int*> border_adjacent_non_shadow_pixels_indexes = std::vector<int*>();

			 int distance = 1;

			 for (int i = 0; i < imgEdge.rows; i++) {
				 for (int j = 0; j < imgEdge.cols; j++) {

					 //uchar &pixel = imgEdge.at<uchar>(i, j);
					 cv::Vec3b &pixel = imgBGR.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadow_mask_pixel = shadowMaskMat.at<cv::Vec3b>(i, j);

					 bool adjacent_to_border = false;

					 if (i - distance >= 0 && imgEdge.at<uchar>(i - distance, j) == 255)
					 {
						 adjacent_to_border = true;
					 }
					 if (i + distance < imgEdge.rows && imgEdge.at<uchar>(i + distance, j) == 255)
					 {
						 adjacent_to_border = true;
					 }

					 if (j - distance >= 0 && imgEdge.at<uchar>(i, j - distance) == 255)
					 {
						 adjacent_to_border = true;
					 }
					 if (j + distance < imgEdge.cols && imgEdge.at<uchar>(i, j + distance) == 255)
					 {
						 adjacent_to_border = true;
					 }

					 if (adjacent_to_border == true)
					 {
						 if (shadow_mask_pixel.val[0] == 255)
						 {
							 border_adjacent_shadow_pixels_indexes.push_back(new int[2]{i, j});
						 }
						 else{
							 border_adjacent_non_shadow_pixels_indexes.push_back(new int[2]{i, j});
						 }
					 }
				 }
			 }

			 if (border_adjacent_shadow_pixels_indexes.size() > border_adjacent_non_shadow_pixels_indexes.size())
			 {
				 int count = border_adjacent_shadow_pixels_indexes.size() - border_adjacent_non_shadow_pixels_indexes.size();
				 for (int i = 0; i < count; i++)
				 {
					 border_adjacent_shadow_pixels_indexes.pop_back();
				 }
			 }
			 if (border_adjacent_shadow_pixels_indexes.size() < border_adjacent_non_shadow_pixels_indexes.size())
			 {
				 int count = border_adjacent_non_shadow_pixels_indexes.size() - border_adjacent_shadow_pixels_indexes.size();
				 for (int i = 0; i < count; i++)
				 {
					 border_adjacent_non_shadow_pixels_indexes.pop_back();
				 }
			 }

			 //
			 //
			 //FINDING A CONSTANT
			 //
			 //

//			 //1-st way diff constant
//			 int prev_error_B = 999999;
//			 int prev_error_G = 999999;
//			 int prev_error_R = 999999;
//
//			 int c_res_B = 0;
//			 int c_res_G = 0;
//			 int c_res_R = 0;
//
//			 std::vector<int> c_B_min_values = std::vector<int>();
//
//			 for (std::vector<int>::size_type r = 1; r != border_adjacent_shadow_pixels_indexes.size(); r++)
//			 {
//				 int *S1_indexes = border_adjacent_shadow_pixels_indexes[r-1];
//				 int *P1_indexes = border_adjacent_non_shadow_pixels_indexes[r-1];
//
//				 int *S2_indexes = border_adjacent_shadow_pixels_indexes[r];
//				 int *P2_indexes = border_adjacent_non_shadow_pixels_indexes[r];
//
//				 int S1_index_0 = S1_indexes[0];
//				 int S1_index_1 = S1_indexes[1];
//
//				 int P1_index_0 = P1_indexes[0];
//				 int P1_index_1 = P1_indexes[1];
//				 
//				 int S2_index_0 = S2_indexes[0];
//				 int S2_index_1 = S2_indexes[1];
//
//				 int P2_index_0 = P2_indexes[0];
//				 int P2_index_1 = P2_indexes[1];
//
//				 cv::Vec3b &S1 = imgBGR.at<cv::Vec3b>(S1_indexes[0], S1_indexes[1]);
//				 cv::Vec3b &P1 = imgBGR.at<cv::Vec3b>(P1_indexes[0], P1_indexes[1]);
//
//				 cv::Vec3b &S2 = imgBGR.at<cv::Vec3b>(S2_indexes[0], S2_indexes[1]);
//				 cv::Vec3b &P2 = imgBGR.at<cv::Vec3b>(P2_indexes[0], P2_indexes[1]);
//
//				 int c_B = P1.val[0] - S1.val[0];
//				 int c_G = P1.val[1] - S1.val[1];
//				 int c_R = P1.val[2] - S1.val[2];
//
//				 //error = P2 − (S2 + c) = P2 − (S2 + P1 − S1)
//				 int error_B = P2.val[0] - (S2.val[0] + c_B);
//				 int error_G = P2.val[1] - (S2.val[1] + c_G);
//				 int error_R = P2.val[2] - (S2.val[2] + c_R);
//
//				 //Rc > Gc > Bc
//				 if ((c_R > c_G && c_G > c_B) == false)
//				 {
//					 continue;
//				 }
//
//				 if (error_B < prev_error_B)
//				 {
//					 prev_error_B = error_B;
//					 c_res_B = c_B;
//
//					 c_B_min_values.push_back(c_res_B);
//				 }
//
//				 if (error_G < prev_error_G)
//				 {
//					 prev_error_G = error_G;
//					 c_res_G = c_G;
//				 }
//
//				 if (error_R < prev_error_R)
//				 {
//					 prev_error_R = error_R;
//					 c_res_R = c_R;
//				 }
//
//				 int a = 0;
//			 }
//
//			 int a = 0;

//			 //1-st way ratio constant
//			 double prev_error_B = 999999;
//			 double prev_error_G = 999999;
//			 double prev_error_R = 999999;
//
//			 double c_res_B = 0;
//			 double c_res_G = 0;
//			 double c_res_R = 0;
//
//			 std::vector<double> c_B_min_values = std::vector<double>();
//
//			 for (std::vector<int>::size_type r = 1; r != border_adjacent_shadow_pixels_indexes.size(); r++)
//			 {
//				 int *S1_indexes = border_adjacent_shadow_pixels_indexes[r - 1];
//				 int *P1_indexes = border_adjacent_non_shadow_pixels_indexes[r - 1];
//
//				 int *S2_indexes = border_adjacent_shadow_pixels_indexes[r];
//				 int *P2_indexes = border_adjacent_non_shadow_pixels_indexes[r];
//
//				 int S1_index_0 = S1_indexes[0];
//				 int S1_index_1 = S1_indexes[1];
//
//				 int P1_index_0 = P1_indexes[0];
//				 int P1_index_1 = P1_indexes[1];
//
//				 int S2_index_0 = S2_indexes[0];
//				 int S2_index_1 = S2_indexes[1];
//
//				 int P2_index_0 = P2_indexes[0];
//				 int P2_index_1 = P2_indexes[1];
//
//				 cv::Vec3b &S1 = imgBGR.at<cv::Vec3b>(S1_indexes[0], S1_indexes[1]);
//				 cv::Vec3b &P1 = imgBGR.at<cv::Vec3b>(P1_indexes[0], P1_indexes[1]);
//
//				 cv::Vec3b &S2 = imgBGR.at<cv::Vec3b>(S2_indexes[0], S2_indexes[1]);
//				 cv::Vec3b &P2 = imgBGR.at<cv::Vec3b>(P2_indexes[0], P2_indexes[1]);
//
//				 double c_B = (double)P1.val[0] / (double)S1.val[0];
//				 double c_G = (double)P1.val[1] / (double)S1.val[1];
//				 double c_R = (double)P1.val[2] / (double)S1.val[2];
//
//				 //error = P2 − (S2 + c) = P2 − (S2 + P1 − S1)
//				 double error_B = (double)P2.val[0] - ((double)S2.val[0] * c_B);
//				 double error_G = (double)P2.val[1] - ((double)S2.val[1] * c_G);
//				 double error_R = (double)P2.val[2] - ((double)S2.val[2] * c_R);
//
//				 //Rc > Gc > Bc
////				 if ((c_R > c_G && c_G > c_B) == false)
////				 {
////					 continue;
////				 }
//
//				 if (error_B < prev_error_B)
//				 {
//					 prev_error_B = error_B;
//					 c_res_B = c_B;
//
//					 c_B_min_values.push_back(c_res_B);
//				 }
//
//				 if (error_G < prev_error_G)
//				 {
//					 prev_error_G = error_G;
//					 c_res_G = c_G;
//				 }
//
//				 if (error_R < prev_error_R)
//				 {
//					 prev_error_R = error_R;
//					 c_res_R = c_R;
//				 }
//
//				 int a = 0;
//			 }


//			 //2-nd way diff
//			 double min_a_B = 99999999999999;
//			 double min_a_G = 99999999999999;
//			 double min_a_R = 99999999999999;
//
//			 int i_min_a_B = 9999999999999;
//			 int i_min_a_G = 9999999999999;
//			 int i_min_a_R = 9999999999999;
//
//			 for (int i = -255; i <= 255; i++)
//			 {
//				 double a_B = 0;
//				 double a_G = 0;
//				 double a_R = 0;
//
//				 for (std::vector<int>::size_type r = 1; r != border_adjacent_shadow_pixels_indexes.size(); r++)
//				 {
//					 int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
//					 int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];
//
//					 cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
//					 cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);
//
//					 a_B += cv::pow(P_pixel.val[0] - S_pixel.val[0] + i,2);
//					 a_G += cv::pow(P_pixel.val[1] - S_pixel.val[1] + i,2);
//					 a_R += cv::pow(P_pixel.val[2] - S_pixel.val[2] + i,2);
//				 }
//
//				 if (a_B < min_a_B)
//				 {
//					 min_a_B = a_B;
//					 i_min_a_B = i;
//				 }
//				 if (a_G < min_a_G)
//				 {
//					 min_a_G = a_G;
//					 i_min_a_G = i;
//				 }
//				 if (a_R < min_a_R)
//				 {
//					 min_a_R = a_R;
//					 i_min_a_R = i;
//				 }
//			 }

			 ////2-nd way MNK - NOT WORKING/ take average -> get grey pixels
//			 double min_a_B = 99999999999999;
//			 double min_a_G = 99999999999999;
//			 double min_a_R = 99999999999999;
//
//			 int i_min_a_B = 9999999999999;
//			 int i_min_a_G = 9999999999999;
//			 int i_min_a_R = 9999999999999;
//
//
//			 //take stat data P and S vectors
//
//			 //MNK x - S; y - P
//
//			 //sum xi
//			 double sum_Si_B = 0;
//			 double sum_Si_G = 0;
//			 double sum_Si_R = 0;
//
//			 //sum xi^2
//			 double sum_Si2_B = 0;
//			 double sum_Si2_G = 0;
//			 double sum_Si2_R = 0;
//			 
//			 //sum yi
//			 double sum_Pi_B = 0;
//			 double sum_Pi_G = 0;
//			 double sum_Pi_R = 0;
//
//			 //sum xi*yi
//			 double sum_SiPi_R = 0;
//			 double sum_SiPi_G = 0;
//			 double sum_SiPi_B = 0;
//
//			 //y = a*x + b; 
//			 //P = a*S + b
//			 double mnk_n = border_adjacent_shadow_pixels_indexes.size();
//			 //double mnk_n = 100;
//
//			 double mnk_a_B = 0;
//			 double mnk_a_G = 0;
//			 double mnk_a_R = 0;
//
//			 double mnk_b_B = 0;
//			 double mnk_b_G = 0;
//			 double mnk_b_R = 0;
//
//			 //sum Si sum Pi sum Si^2
//			 for (std::vector<int>::size_type r = 1; r != mnk_n; r++)
//			 {
//				 int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
//				 int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];
//
//				 cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
//				 cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);
//
//				 sum_Si_B += S_pixel.val[0];
//				 sum_Si_G += S_pixel.val[1];
//				 sum_Si_R += S_pixel.val[2];
//
//				 sum_Si2_B += pow(S_pixel.val[0], 2);
//				 sum_Si2_G += pow(S_pixel.val[1], 2);
//				 sum_Si2_R += pow(S_pixel.val[2], 2);
//
//				 sum_Pi_B += P_pixel.val[0];
//				 sum_Pi_G += P_pixel.val[1];
//				 sum_Pi_R += P_pixel.val[2];
//			 }
//
//			 //sum Si*Pi
//			 for (std::vector<int>::size_type r = 1; r != mnk_n; r++)
//			 {
//				 int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
//				 int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];
//
//				 cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
//				 cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);
//
//				 sum_SiPi_B += S_pixel.val[0] * P_pixel.val[0];
//				 sum_SiPi_G += S_pixel.val[1] * P_pixel.val[1];
//				 sum_SiPi_R += S_pixel.val[2] * P_pixel.val[2];
//			 }
//
//			 mnk_a_B = (mnk_n*sum_SiPi_B - sum_Si_B*sum_Pi_B) / (mnk_n*sum_Si2_B - pow(sum_Si_B, 2));
//			 mnk_a_G = (mnk_n*sum_SiPi_G - sum_Si_G*sum_Pi_G) / (mnk_n*sum_Si2_G - pow(sum_Si_G, 2));
//			 mnk_a_R = (mnk_n*sum_SiPi_R - sum_Si_R*sum_Pi_R) / (mnk_n*sum_Si2_R - pow(sum_Si_R, 2));
//
//			 mnk_b_B = (sum_Pi_B - mnk_a_B*sum_Si_B) / mnk_n;
//			 mnk_b_G = (sum_Pi_G - mnk_a_G*sum_Si_G) / mnk_n;
//			 mnk_b_R = (sum_Pi_R - mnk_a_R*sum_Si_R) / mnk_n;
//
//			 double c_res_B = 0;
//			 double c_res_G = 0;
//			 double c_res_R = 0;

//			 c_res_B = abs(i_min_a_B);
//			 c_res_G = abs(i_min_a_G);
//			 c_res_R = abs(i_min_a_R);

			//2-nd way Metod Deleniya popolam

			double a_B = 0;
			double a_G = 0;
			double a_R = 0;

			double b_B = 256;
			double b_G = 256;
			double b_R = 256;
			
			double c_B = 0;
			double c_G = 0;
			double c_R = 0;

			double r_B = 0;
			double r_G = 0;
			double r_R = 0;

			

			double sigma = 0.01;
			int max_step = 100000;

			//calsc f value; f = sum (Pi - Si*r)^2
			for (int i = 0; true; i++)
			{
				double f_a_B = 0;

				double f_b_B = 0;
				
				double f_c_B = 0;

				for (std::vector<int>::size_type r = 1; r != border_adjacent_shadow_pixels_indexes.size(); r++)
				{
					int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
					int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];

					cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
					cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);

					//r==a
					f_a_B += pow(P_pixel.val[0] - S_pixel.val[0] * a_B, 2);

					//r==b
					f_b_B += pow(P_pixel.val[0] - S_pixel.val[0] * b_B, 2);

					//r==c
					c_B = (a_B + b_B) / 2.0;

					f_c_B += pow(P_pixel.val[0] - S_pixel.val[0] * c_B, 2);				
				}

				if (f_c_B < f_a_B)
				{
					a_B = c_B;
				}
				else if (f_c_B < f_b_B)
				{
					b_B = c_B;
				}


				if ((b_B - a_B)<=sigma || i >= max_step)
				{
					r_B = (a_B + b_B) / 2;
					break;
				}
			}

			for (int i = 0; true; i++)
			{
				double f_a_G = 0;

				double f_b_G = 0;

				double f_c_G = 0;

				for (std::vector<int>::size_type r = 1; r != border_adjacent_shadow_pixels_indexes.size(); r++)
				{
					int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
					int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];

					cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
					cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);

					//r==a
					f_a_G += pow(P_pixel.val[1] - S_pixel.val[1] * a_G, 2);

					//r==b
					f_b_G += pow(P_pixel.val[1] - S_pixel.val[1] * b_G, 2);

					//r==c
					c_G = (a_G + b_G) / 2.0;

					f_c_G += pow(P_pixel.val[1] - S_pixel.val[1] * c_G, 2);
				}

				if (f_c_G < f_a_G)
				{
					a_G = c_G;
				}
				else if (f_c_G < f_b_G)
				{
					b_G = c_G;
				}

				r_G = (a_G + b_G) / 2;

				if (((b_G - a_G) <= sigma || i >= max_step))
				{
					
					break;
				}
			}

			for (int i = 0; true; i++)
			{
				double f_a_R = 0;

				double f_b_R = 0;

				double f_c_R = 0;

				for (std::vector<int>::size_type r = 1; r != border_adjacent_shadow_pixels_indexes.size(); r++)
				{
					int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
					int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];

					cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
					cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);

					//r==a
					f_a_R += pow(P_pixel.val[2] - S_pixel.val[2] * a_R, 2);

					//r==b
					f_b_R += pow(P_pixel.val[2] - S_pixel.val[2] * b_R, 2);

					//r==c
					c_R = (a_R + b_R) / 2.0;

					f_c_R += pow(P_pixel.val[2] - S_pixel.val[2] * c_R, 2);
				}

				if (f_c_R < f_a_R)
				{
					a_R = c_R;
				}
				else if (f_c_R < f_b_R)
				{
					b_R = c_R;
				}

				if ((b_R - a_R) <= sigma || i >= max_step)
				{
					r_R = (a_R + b_R) / 2;
					break;
				}
			}
			 
			double c_res_B = r_B;
			double c_res_G = r_G;
			double c_res_R = r_R;

			 //
			 //
			 //APPLYING A CONSTANT
			 //
			 //
			for (int i = 0; i < imgEdge.rows; i++) {
				for (int j = 0; j < imgEdge.cols; j++) {

					cv::Vec3b &pixel = imgBGR.at<cv::Vec3b>(i, j);
					cv::Vec3b &shadow_mask_pixel = shadowMaskMat.at<cv::Vec3b>(i, j);

					if (shadow_mask_pixel.val[0] == 255){

						double B = pixel.val[0];
						double G = pixel.val[1];
						double R = pixel.val[2];

//						B += c_res_B;
//						G += c_res_G;
//						R += c_res_R;

						B *= c_res_B;
						G *= c_res_G;
						R *= c_res_R;

//						B = B*mnk_a_B + mnk_b_B;
//						G = G*mnk_a_G + mnk_b_G;
//						R = R*mnk_a_R + mnk_b_R;

//						B *= 2.7;
//						G *= 3.3;
//						R *= 4;

//						//wall
//						B *= 1.705;
//						G *= 2.04;
//						R *= 2.59;

//						B += 67;
//						G += 93;
//						R += 121;

//						//man on alley
//						B *= 1.409;
//						G *= 1.46;
//						R *= 1.62;

						B = B > 255 ? 255 : (B < 0 ? 0 : B);
						G = G > 255 ? 255 : (G < 0 ? 0 : G);
						R = R > 255 ? 255 : (R < 0 ? 0 : R);

						pixel.val[0] = B;
						pixel.val[1] = G;
						pixel.val[2] = R;
					}
				}
			}

			 cv::imshow("const res", imgBGR);
}
private: System::Void button5Decompress_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void buttonIntensityAdd_Click(System::Object^  sender, System::EventArgs^  e) {

			 double intensity_to_add = System::Convert::ToDouble(textBoxIntensityAdd->Text);
			 double intensity_to_mul = System::Convert::ToDouble(textBoxIntensityMul->Text);

			 cv::Mat img = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth, CV_8UC3);
			 cv::Mat shadow_mask = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth, CV_8UC3);
			 cv::Mat imgLAB;
			 CopyArrayToMat(buffer,img);
			 CopyArrayToMat(shadowMask, shadow_mask);
			 cv::cvtColor(img, imgLAB,CV_BGR2Lab);

			 for (int i = 0; i < imgLAB.rows; i++) {
				 for (int j = 0; j < imgLAB.cols; j++) {

					 cv::Vec3b &pixel = imgLAB.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadow_mask_pixel = shadow_mask.at<cv::Vec3b>(i, j);

					 if (shadow_mask_pixel.val[0] == 255){
						 double L = pixel.val[0];
						 if (radioButtonIntensityAdd->Checked){
							 L += intensity_to_add;
						 }
						 if (radioButtonIntensityMul->Checked){
							 L *= intensity_to_mul;
						 }
						 L = L > 255 ? 255 : (L < 0 ? 0 : L);
						 pixel.val[0] = L;
					 }
				 }
			 }

			 cv::cvtColor(imgLAB, img, CV_Lab2BGR);
			 CopyMatToArray(img, buffer);

			 SaveBMP();
			 ShowBmp();
}

		 //Apply mean shift segentation params
private: System::Void buttonMSSApply_Click(System::Object^  sender, System::EventArgs^  e) {
			 try
			 {
				 MeanShiftParams::SPATIAL_RADIUS = System::Convert::ToInt32(textBoxMSSSpatialRadius->Text);
				 MeanShiftParams::COLOR_RADIUS = System::Convert::ToDouble(textBoxMSSColorRadius->Text);
				 MeanShiftParams::MIN_REGION_SIZE = System::Convert::ToDouble(textBoxMSSMinRegionSize->Text);
			 }
//			 catch (const std::exception& ex) {
//				 // ...
//			 }
//			 catch (const std::string& ex) {
//				 // ...
//			 }
			 catch (...) {
				 ShowMsgBox(System::Convert::ToString("Bad data was received. Check your input."));
			 }
}
		 //Reset mean shift segentation params
private: System::Void buttonMSSDefault_Click(System::Object^  sender, System::EventArgs^  e) {

			 //Set mean shift segmentation params
			 textBoxMSSSpatialRadius->Text = System::Convert::ToString(MeanShiftParams::SPATIAL_RADIUS_DEFAULT);
			 textBoxMSSColorRadius->Text = System::Convert::ToString(MeanShiftParams::COLOR_RADIUS_DEFAULT);
			 textBoxMSSMinRegionSize->Text = System::Convert::ToString(MeanShiftParams::MIN_REGION_SIZE_DEFAULT);

			 MeanShiftParams::SPATIAL_RADIUS = MeanShiftParams::SPATIAL_RADIUS_DEFAULT;
			 MeanShiftParams::COLOR_RADIUS = MeanShiftParams::COLOR_RADIUS_DEFAULT;
			 MeanShiftParams::MIN_REGION_SIZE = MeanShiftParams::MIN_REGION_SIZE;
}

//private: void ShowMsgBox(System::String msg)
//{ 
//			 MessageBox::Show(msg.Normalize());
//}
private: void ShowMsgBox(System::String ^msg)
{
		MessageBox::Show(msg);
}


};



}