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

#include "OpenedImageData\OpenedImageData.h"

#include "Helper\Helper.h"

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
	bool OPEN=false;//указывает бьл ли открыт файл

	char* myPath_char="";//путь к файлу
	char *char_pathCopyBMP = "copyBMP.bmp";
	
	cv::Mat imgBGR;
	cv::Mat imgBGRRes;
	cv::Mat imgShadowMask;

	//CONSTANTS

	//Default params for edges processing
	int INPAINT_DILATION_KERNEL_SIZE = 3;
	double INPAINT_RADIUS = 4;

	int GAUSSIAN_FILTER_DILATION_KERNEL_SIZE = 3;
	int MEDIAN_FILTER_DILATION_KERNEL_SIZE = 3;

	int GAUSSIAN_FILTER_KERNEL_SIZE = 3;
	int MEDIAN_FILTER_KERNEL_SIZE = 3;

	//Type required for removing range of indices from  C++ containers (built in array, vector, list)
	template<typename Cont, typename It>
	auto ToggleIndices(Cont &cont, It beg, It end) -> decltype(std::end(cont))
	{
		int helpIndx(0);
		return std::stable_partition(std::begin(cont), std::end(cont),
			[&](decltype(*std::begin(cont)) const& val) -> bool {
			return std::find(beg, end, helpIndx++) == end;
		});
	};
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
	private: System::Windows::Forms::PictureBox^  pictureBoxImgBGRRes;




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
	private: System::Windows::Forms::PictureBox^  pictureBoxImgBGR;
	private: System::Windows::Forms::PictureBox^  pictureBoxImgShadowMask;







private: System::Windows::Forms::Button^  buttonAdditive;
private: System::Windows::Forms::Button^  buttonBasicLightModel;

private: System::Windows::Forms::Button^  buttonYCbCr;

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






private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBoxMSSColorRadius;

	private: System::Windows::Forms::TextBox^  textBoxMSSSpatialRadius;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::TextBox^  textBoxMSSMinRegionSize;
private: System::Windows::Forms::Button^  buttonMSSApply;
private: System::Windows::Forms::Button^  buttonMSSDefault;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Button^  buttonDestroyAlllWindows;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Panel^  panel1;
private: System::Windows::Forms::Panel^  panel2;
private: System::Windows::Forms::Panel^  panel3;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::Panel^  panel4;
private: System::Windows::Forms::TextBox^  textBoxEdgesProcDilationKernelSize;

private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::TextBox^  textBoxEdgesProcInpaintRadius;

private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::Button^  buttonEdgesProcessingDefault;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::Button^  buttonInpaintEdges;
private: System::Windows::Forms::Button^  buttonSmoothUsingGaussianFilter;
private: System::Windows::Forms::Button^  buttonSmoothUsingMedianFilter;
private: System::Windows::Forms::TextBox^  textBoxEdgesProcMedianFilterKernelSize;

private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::TextBox^  textBoxEdgesProcGaussianFilterKernelSize;

private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  label18;




private: System::Windows::Forms::TextBox^  textBoxEdgesProcGaussianFilterDilationKernelSize;

private: System::Windows::Forms::Label^  label22;


private: System::Windows::Forms::TextBox^  textBoxEdgesProcMedianFilterDilationKernelSize;
private: System::Windows::Forms::Label^  label23;





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
			this->pictureBoxImgBGRRes = (gcnew System::Windows::Forms::PictureBox());
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
			this->pictureBoxImgBGR = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxImgShadowMask = (gcnew System::Windows::Forms::PictureBox());
			this->buttonAdditive = (gcnew System::Windows::Forms::Button());
			this->buttonBasicLightModel = (gcnew System::Windows::Forms::Button());
			this->buttonYCbCr = (gcnew System::Windows::Forms::Button());
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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxMSSColorRadius = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMSSSpatialRadius = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBoxMSSMinRegionSize = (gcnew System::Windows::Forms::TextBox());
			this->buttonMSSApply = (gcnew System::Windows::Forms::Button());
			this->buttonMSSDefault = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->buttonDestroyAlllWindows = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->textBoxEdgesProcMedianFilterDilationKernelSize = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->textBoxEdgesProcGaussianFilterDilationKernelSize = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->textBoxEdgesProcMedianFilterKernelSize = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->textBoxEdgesProcGaussianFilterKernelSize = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->buttonSmoothUsingMedianFilter = (gcnew System::Windows::Forms::Button());
			this->buttonSmoothUsingGaussianFilter = (gcnew System::Windows::Forms::Button());
			this->buttonInpaintEdges = (gcnew System::Windows::Forms::Button());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBoxEdgesProcInpaintRadius = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBoxEdgesProcDilationKernelSize = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->buttonEdgesProcessingDefault = (gcnew System::Windows::Forms::Button());
			this->label14 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxImgBGRRes))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxImgBGR))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxImgShadowMask))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1open
			// 
			this->textBox1open->Enabled = false;
			this->textBox1open->Location = System::Drawing::Point(8, 635);
			this->textBox1open->Multiline = true;
			this->textBox1open->Name = L"textBox1open";
			this->textBox1open->Size = System::Drawing::Size(623, 18);
			this->textBox1open->TabIndex = 0;
			// 
			// button1open
			// 
			this->button1open->Location = System::Drawing::Point(8, 523);
			this->button1open->Name = L"button1open";
			this->button1open->Size = System::Drawing::Size(193, 25);
			this->button1open->TabIndex = 1;
			this->button1open->Text = L"Open";
			this->button1open->UseVisualStyleBackColor = true;
			this->button1open->Click += gcnew System::EventHandler(this, &Form1::button1open_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBoxImgBGRRes
			// 
			this->pictureBoxImgBGRRes->Location = System::Drawing::Point(944, 23);
			this->pictureBoxImgBGRRes->Name = L"pictureBoxImgBGRRes";
			this->pictureBoxImgBGRRes->Size = System::Drawing::Size(460, 380);
			this->pictureBoxImgBGRRes->TabIndex = 2;
			this->pictureBoxImgBGRRes->TabStop = false;
			this->pictureBoxImgBGRRes->Click += gcnew System::EventHandler(this, &Form1::pictureBoxImgBGRRes_Click);
			// 
			// button2save
			// 
			this->button2save->Location = System::Drawing::Point(8, 551);
			this->button2save->Name = L"button2save";
			this->button2save->Size = System::Drawing::Size(193, 25);
			this->button2save->TabIndex = 5;
			this->button2save->Text = L"Save";
			this->button2save->UseVisualStyleBackColor = true;
			this->button2save->Click += gcnew System::EventHandler(this, &Form1::button2save_Click);
			// 
			// button3exit
			// 
			this->button3exit->Location = System::Drawing::Point(8, 607);
			this->button3exit->Name = L"button3exit";
			this->button3exit->Size = System::Drawing::Size(193, 25);
			this->button3exit->TabIndex = 6;
			this->button3exit->Text = L"Exit";
			this->button3exit->UseVisualStyleBackColor = true;
			this->button3exit->Click += gcnew System::EventHandler(this, &Form1::button3exit_Click);
			// 
			// button6Close
			// 
			this->button6Close->Location = System::Drawing::Point(8, 579);
			this->button6Close->Name = L"button6Close";
			this->button6Close->Size = System::Drawing::Size(193, 25);
			this->button6Close->TabIndex = 15;
			this->button6Close->Text = L"Close";
			this->button6Close->UseVisualStyleBackColor = true;
			this->button6Close->Click += gcnew System::EventHandler(this, &Form1::button6Close_Click);
			// 
			// button7colorCorrection
			// 
			this->button7colorCorrection->Enabled = false;
			this->button7colorCorrection->Location = System::Drawing::Point(331, 484);
			this->button7colorCorrection->Name = L"button7colorCorrection";
			this->button7colorCorrection->Size = System::Drawing::Size(98, 22);
			this->button7colorCorrection->TabIndex = 16;
			this->button7colorCorrection->Text = L"Color correction";
			this->button7colorCorrection->UseVisualStyleBackColor = true;
			this->button7colorCorrection->Click += gcnew System::EventHandler(this, &Form1::button7colorCorrection_Click);
			// 
			// textBoxRed
			// 
			this->textBoxRed->Location = System::Drawing::Point(233, 458);
			this->textBoxRed->Multiline = true;
			this->textBoxRed->Name = L"textBoxRed";
			this->textBoxRed->Size = System::Drawing::Size(44, 20);
			this->textBoxRed->TabIndex = 17;
			this->textBoxRed->Text = L"0";
			// 
			// textBoxGreen
			// 
			this->textBoxGreen->Location = System::Drawing::Point(282, 458);
			this->textBoxGreen->Multiline = true;
			this->textBoxGreen->Name = L"textBoxGreen";
			this->textBoxGreen->Size = System::Drawing::Size(44, 20);
			this->textBoxGreen->TabIndex = 18;
			this->textBoxGreen->Text = L"0";
			// 
			// textBoxBlue
			// 
			this->textBoxBlue->Location = System::Drawing::Point(331, 458);
			this->textBoxBlue->Multiline = true;
			this->textBoxBlue->Name = L"textBoxBlue";
			this->textBoxBlue->Size = System::Drawing::Size(44, 20);
			this->textBoxBlue->TabIndex = 19;
			this->textBoxBlue->Text = L"0";
			// 
			// textBoxRGB
			// 
			this->textBoxRGB->Location = System::Drawing::Point(380, 458);
			this->textBoxRGB->Multiline = true;
			this->textBoxRGB->Name = L"textBoxRGB";
			this->textBoxRGB->Size = System::Drawing::Size(49, 20);
			this->textBoxRGB->TabIndex = 20;
			this->textBoxRGB->Text = L"0";
			// 
			// buttonRestoreImage
			// 
			this->buttonRestoreImage->Enabled = false;
			this->buttonRestoreImage->Location = System::Drawing::Point(8, 495);
			this->buttonRestoreImage->Name = L"buttonRestoreImage";
			this->buttonRestoreImage->Size = System::Drawing::Size(193, 25);
			this->buttonRestoreImage->TabIndex = 21;
			this->buttonRestoreImage->Text = L"Restore image";
			this->buttonRestoreImage->UseVisualStyleBackColor = true;
			this->buttonRestoreImage->Click += gcnew System::EventHandler(this, &Form1::buttonRestoreImage_Click);
			// 
			// labelRed
			// 
			this->labelRed->AutoSize = true;
			this->labelRed->Location = System::Drawing::Point(230, 442);
			this->labelRed->Name = L"labelRed";
			this->labelRed->Size = System::Drawing::Size(27, 13);
			this->labelRed->TabIndex = 22;
			this->labelRed->Text = L"Red";
			// 
			// labelGreen
			// 
			this->labelGreen->AutoSize = true;
			this->labelGreen->Location = System::Drawing::Point(279, 442);
			this->labelGreen->Name = L"labelGreen";
			this->labelGreen->Size = System::Drawing::Size(36, 13);
			this->labelGreen->TabIndex = 23;
			this->labelGreen->Text = L"Green";
			// 
			// labelBlue
			// 
			this->labelBlue->AutoSize = true;
			this->labelBlue->Location = System::Drawing::Point(331, 442);
			this->labelBlue->Name = L"labelBlue";
			this->labelBlue->Size = System::Drawing::Size(28, 13);
			this->labelBlue->TabIndex = 24;
			this->labelBlue->Text = L"Blue";
			// 
			// labelRGB
			// 
			this->labelRGB->AutoSize = true;
			this->labelRGB->Location = System::Drawing::Point(377, 442);
			this->labelRGB->Name = L"labelRGB";
			this->labelRGB->Size = System::Drawing::Size(30, 13);
			this->labelRGB->TabIndex = 25;
			this->labelRGB->Text = L"RGB";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(233, 484);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(95, 22);
			this->button1->TabIndex = 26;
			this->button1->Text = L"Reset";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// pictureBoxImgBGR
			// 
			this->pictureBoxImgBGR->Location = System::Drawing::Point(12, 23);
			this->pictureBoxImgBGR->Name = L"pictureBoxImgBGR";
			this->pictureBoxImgBGR->Size = System::Drawing::Size(460, 380);
			this->pictureBoxImgBGR->TabIndex = 52;
			this->pictureBoxImgBGR->TabStop = false;
			// 
			// pictureBoxImgShadowMask
			// 
			this->pictureBoxImgShadowMask->Location = System::Drawing::Point(478, 23);
			this->pictureBoxImgShadowMask->Name = L"pictureBoxImgShadowMask";
			this->pictureBoxImgShadowMask->Size = System::Drawing::Size(460, 380);
			this->pictureBoxImgShadowMask->TabIndex = 61;
			this->pictureBoxImgShadowMask->TabStop = false;
			this->pictureBoxImgShadowMask->Click += gcnew System::EventHandler(this, &Form1::pictureBoxImgShadowMask_Click);
			// 
			// buttonAdditive
			// 
			this->buttonAdditive->Location = System::Drawing::Point(12, 3);
			this->buttonAdditive->Name = L"buttonAdditive";
			this->buttonAdditive->Size = System::Drawing::Size(163, 25);
			this->buttonAdditive->TabIndex = 65;
			this->buttonAdditive->Text = L"Additive shadow removal ";
			this->buttonAdditive->UseVisualStyleBackColor = true;
			this->buttonAdditive->Click += gcnew System::EventHandler(this, &Form1::buttonAdditive_Click);
			// 
			// buttonBasicLightModel
			// 
			this->buttonBasicLightModel->Location = System::Drawing::Point(12, 34);
			this->buttonBasicLightModel->Name = L"buttonBasicLightModel";
			this->buttonBasicLightModel->Size = System::Drawing::Size(163, 25);
			this->buttonBasicLightModel->TabIndex = 66;
			this->buttonBasicLightModel->Text = L"Basic light model removal";
			this->buttonBasicLightModel->UseVisualStyleBackColor = true;
			this->buttonBasicLightModel->Click += gcnew System::EventHandler(this, &Form1::buttonBasicLightModel_Click);
			// 
			// buttonYCbCr
			// 
			this->buttonYCbCr->Location = System::Drawing::Point(12, 65);
			this->buttonYCbCr->Name = L"buttonYCbCr";
			this->buttonYCbCr->Size = System::Drawing::Size(163, 25);
			this->buttonYCbCr->TabIndex = 68;
			this->buttonYCbCr->Text = L"Remove using YCbCr";
			this->buttonYCbCr->UseVisualStyleBackColor = true;
			this->buttonYCbCr->Click += gcnew System::EventHandler(this, &Form1::buttonYCbCr_Click);
			// 
			// button1Shadow2Lab
			// 
			this->button1Shadow2Lab->Location = System::Drawing::Point(19, 32);
			this->button1Shadow2Lab->Name = L"button1Shadow2Lab";
			this->button1Shadow2Lab->Size = System::Drawing::Size(141, 25);
			this->button1Shadow2Lab->TabIndex = 70;
			this->button1Shadow2Lab->Text = L"Detect with LAB";
			this->button1Shadow2Lab->UseVisualStyleBackColor = true;
			this->button1Shadow2Lab->Click += gcnew System::EventHandler(this, &Form1::button1Shadow2Lab_Click);
			// 
			// button11RemveLab
			// 
			this->button11RemveLab->Location = System::Drawing::Point(12, 127);
			this->button11RemveLab->Name = L"button11RemveLab";
			this->button11RemveLab->Size = System::Drawing::Size(163, 25);
			this->button11RemveLab->TabIndex = 71;
			this->button11RemveLab->Text = L"Remove using Lab";
			this->button11RemveLab->UseVisualStyleBackColor = true;
			this->button11RemveLab->Click += gcnew System::EventHandler(this, &Form1::button11RemveLab_Click);
			// 
			// button1Shadow4Math
			// 
			this->button1Shadow4Math->Location = System::Drawing::Point(19, 61);
			this->button1Shadow4Math->Name = L"button1Shadow4Math";
			this->button1Shadow4Math->Size = System::Drawing::Size(141, 25);
			this->button1Shadow4Math->TabIndex = 73;
			this->button1Shadow4Math->Text = L"Detect with MS";
			this->button1Shadow4Math->UseVisualStyleBackColor = true;
			this->button1Shadow4Math->Click += gcnew System::EventHandler(this, &Form1::button1Shadow4Math_Click);
			// 
			// buttonShadow0YCbCr
			// 
			this->buttonShadow0YCbCr->Location = System::Drawing::Point(19, 3);
			this->buttonShadow0YCbCr->Name = L"buttonShadow0YCbCr";
			this->buttonShadow0YCbCr->Size = System::Drawing::Size(141, 25);
			this->buttonShadow0YCbCr->TabIndex = 74;
			this->buttonShadow0YCbCr->Text = L"Detect with YCbCr";
			this->buttonShadow0YCbCr->UseVisualStyleBackColor = true;
			this->buttonShadow0YCbCr->Click += gcnew System::EventHandler(this, &Form1::buttonShadow0YCbCr_Click);
			// 
			// buttonHandleEdges
			// 
			this->buttonHandleEdges->Location = System::Drawing::Point(1297, 409);
			this->buttonHandleEdges->Name = L"buttonHandleEdges";
			this->buttonHandleEdges->Size = System::Drawing::Size(109, 25);
			this->buttonHandleEdges->TabIndex = 75;
			this->buttonHandleEdges->Text = L"Edges Correction";
			this->buttonHandleEdges->UseVisualStyleBackColor = true;
			this->buttonHandleEdges->Click += gcnew System::EventHandler(this, &Form1::buttonHandleEdges_Click);
			// 
			// buttonTestMEANSHIFT
			// 
			this->buttonTestMEANSHIFT->Location = System::Drawing::Point(887, 555);
			this->buttonTestMEANSHIFT->Name = L"buttonTestMEANSHIFT";
			this->buttonTestMEANSHIFT->Size = System::Drawing::Size(109, 25);
			this->buttonTestMEANSHIFT->TabIndex = 76;
			this->buttonTestMEANSHIFT->Text = L"Test MEAN SHIFT";
			this->buttonTestMEANSHIFT->UseVisualStyleBackColor = true;
			this->buttonTestMEANSHIFT->Click += gcnew System::EventHandler(this, &Form1::buttonTestMEANSHIFT_Click);
			// 
			// buttonBasicLightModelLAB
			// 
			this->buttonBasicLightModelLAB->Location = System::Drawing::Point(12, 96);
			this->buttonBasicLightModelLAB->Name = L"buttonBasicLightModelLAB";
			this->buttonBasicLightModelLAB->Size = System::Drawing::Size(163, 25);
			this->buttonBasicLightModelLAB->TabIndex = 78;
			this->buttonBasicLightModelLAB->Text = L"Basic light model removal (Lab)";
			this->buttonBasicLightModelLAB->UseVisualStyleBackColor = true;
			this->buttonBasicLightModelLAB->Click += gcnew System::EventHandler(this, &Form1::buttonBasicLightModelLAB_Click);
			// 
			// textBoxGrayAvg
			// 
			this->textBoxGrayAvg->Enabled = false;
			this->textBoxGrayAvg->Location = System::Drawing::Point(28, 125);
			this->textBoxGrayAvg->Multiline = true;
			this->textBoxGrayAvg->Name = L"textBoxGrayAvg";
			this->textBoxGrayAvg->Size = System::Drawing::Size(40, 20);
			this->textBoxGrayAvg->TabIndex = 79;
			this->textBoxGrayAvg->Text = L"0";
			// 
			// textBoxGrayDev
			// 
			this->textBoxGrayDev->Enabled = false;
			this->textBoxGrayDev->Location = System::Drawing::Point(74, 125);
			this->textBoxGrayDev->Multiline = true;
			this->textBoxGrayDev->Name = L"textBoxGrayDev";
			this->textBoxGrayDev->Size = System::Drawing::Size(40, 20);
			this->textBoxGrayDev->TabIndex = 80;
			this->textBoxGrayDev->Text = L"0";
			// 
			// textBoxShadowDetectionThreshold
			// 
			this->textBoxShadowDetectionThreshold->Location = System::Drawing::Point(120, 126);
			this->textBoxShadowDetectionThreshold->Multiline = true;
			this->textBoxShadowDetectionThreshold->Name = L"textBoxShadowDetectionThreshold";
			this->textBoxShadowDetectionThreshold->Size = System::Drawing::Size(40, 20);
			this->textBoxShadowDetectionThreshold->TabIndex = 82;
			this->textBoxShadowDetectionThreshold->Text = L"0";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(117, 110);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(43, 13);
			this->label5->TabIndex = 83;
			this->label5->Text = L"Thresh:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(26, 109);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(29, 13);
			this->label6->TabIndex = 84;
			this->label6->Text = L"Avg:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(71, 110);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(44, 13);
			this->label7->TabIndex = 85;
			this->label7->Text = L"Stddev:";
			// 
			// buttonRemoveUsingConstant
			// 
			this->buttonRemoveUsingConstant->Location = System::Drawing::Point(12, 158);
			this->buttonRemoveUsingConstant->Name = L"buttonRemoveUsingConstant";
			this->buttonRemoveUsingConstant->Size = System::Drawing::Size(163, 25);
			this->buttonRemoveUsingConstant->TabIndex = 86;
			this->buttonRemoveUsingConstant->Text = L"Remove Using Constant";
			this->buttonRemoveUsingConstant->UseVisualStyleBackColor = true;
			this->buttonRemoveUsingConstant->Click += gcnew System::EventHandler(this, &Form1::buttonRemoveUsingConstant_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(4, 29);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(70, 13);
			this->label2->TabIndex = 96;
			this->label2->Text = L"Color Radius:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(4, 6);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(78, 13);
			this->label3->TabIndex = 95;
			this->label3->Text = L"Spatial Radius:";
			// 
			// textBoxMSSColorRadius
			// 
			this->textBoxMSSColorRadius->Location = System::Drawing::Point(85, 29);
			this->textBoxMSSColorRadius->Multiline = true;
			this->textBoxMSSColorRadius->Name = L"textBoxMSSColorRadius";
			this->textBoxMSSColorRadius->Size = System::Drawing::Size(63, 20);
			this->textBoxMSSColorRadius->TabIndex = 94;
			this->textBoxMSSColorRadius->Text = L"0";
			// 
			// textBoxMSSSpatialRadius
			// 
			this->textBoxMSSSpatialRadius->Location = System::Drawing::Point(85, 3);
			this->textBoxMSSSpatialRadius->Multiline = true;
			this->textBoxMSSSpatialRadius->Name = L"textBoxMSSSpatialRadius";
			this->textBoxMSSSpatialRadius->Size = System::Drawing::Size(63, 20);
			this->textBoxMSSSpatialRadius->TabIndex = 93;
			this->textBoxMSSSpatialRadius->Text = L"0";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(877, 426);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(162, 13);
			this->label4->TabIndex = 97;
			this->label4->Text = L"Mean shift segmentation params:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(4, 55);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(80, 13);
			this->label8->TabIndex = 99;
			this->label8->Text = L"Min region size:";
			// 
			// textBoxMSSMinRegionSize
			// 
			this->textBoxMSSMinRegionSize->Location = System::Drawing::Point(85, 55);
			this->textBoxMSSMinRegionSize->Multiline = true;
			this->textBoxMSSMinRegionSize->Name = L"textBoxMSSMinRegionSize";
			this->textBoxMSSMinRegionSize->Size = System::Drawing::Size(63, 20);
			this->textBoxMSSMinRegionSize->TabIndex = 98;
			this->textBoxMSSMinRegionSize->Text = L"0";
			// 
			// buttonMSSApply
			// 
			this->buttonMSSApply->Location = System::Drawing::Point(85, 78);
			this->buttonMSSApply->Name = L"buttonMSSApply";
			this->buttonMSSApply->Size = System::Drawing::Size(63, 23);
			this->buttonMSSApply->TabIndex = 100;
			this->buttonMSSApply->Text = L"Apply";
			this->buttonMSSApply->UseVisualStyleBackColor = true;
			this->buttonMSSApply->Click += gcnew System::EventHandler(this, &Form1::buttonMSSApply_Click);
			// 
			// buttonMSSDefault
			// 
			this->buttonMSSDefault->Location = System::Drawing::Point(7, 78);
			this->buttonMSSDefault->Name = L"buttonMSSDefault";
			this->buttonMSSDefault->Size = System::Drawing::Size(75, 23);
			this->buttonMSSDefault->TabIndex = 101;
			this->buttonMSSDefault->Text = L"Default";
			this->buttonMSSDefault->UseVisualStyleBackColor = true;
			this->buttonMSSDefault->Click += gcnew System::EventHandler(this, &Form1::buttonMSSDefault_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::Control;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(9, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(73, 13);
			this->label1->TabIndex = 102;
			this->label1->Text = L"Original image";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::SystemColors::Control;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(475, 8);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(105, 13);
			this->label9->TabIndex = 103;
			this->label9->Text = L"Shadow mask image";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::SystemColors::Control;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(945, 7);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(68, 13);
			this->label10->TabIndex = 104;
			this->label10->Text = L"Result image";
			// 
			// buttonDestroyAlllWindows
			// 
			this->buttonDestroyAlllWindows->Location = System::Drawing::Point(8, 465);
			this->buttonDestroyAlllWindows->Name = L"buttonDestroyAlllWindows";
			this->buttonDestroyAlllWindows->Size = System::Drawing::Size(193, 25);
			this->buttonDestroyAlllWindows->TabIndex = 105;
			this->buttonDestroyAlllWindows->Text = L"Destroy alll windows";
			this->buttonDestroyAlllWindows->UseVisualStyleBackColor = true;
			this->buttonDestroyAlllWindows->Click += gcnew System::EventHandler(this, &Form1::buttonDestroyAlllWindows_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(487, 432);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(93, 13);
			this->label11->TabIndex = 106;
			this->label11->Text = L"Shadow detection";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(675, 426);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(86, 13);
			this->label12->TabIndex = 107;
			this->label12->Text = L"Shadow removal";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel1->Controls->Add(this->buttonMSSDefault);
			this->panel1->Controls->Add(this->textBoxMSSSpatialRadius);
			this->panel1->Controls->Add(this->textBoxMSSColorRadius);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->textBoxMSSMinRegionSize);
			this->panel1->Controls->Add(this->label8);
			this->panel1->Controls->Add(this->buttonMSSApply);
			this->panel1->Location = System::Drawing::Point(880, 442);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(159, 110);
			this->panel1->TabIndex = 108;
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel2->Controls->Add(this->buttonAdditive);
			this->panel2->Controls->Add(this->buttonBasicLightModel);
			this->panel2->Controls->Add(this->buttonYCbCr);
			this->panel2->Controls->Add(this->button11RemveLab);
			this->panel2->Controls->Add(this->buttonBasicLightModelLAB);
			this->panel2->Controls->Add(this->buttonRemoveUsingConstant);
			this->panel2->Location = System::Drawing::Point(678, 442);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(185, 195);
			this->panel2->TabIndex = 109;
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel3->Controls->Add(this->label13);
			this->panel3->Controls->Add(this->buttonShadow0YCbCr);
			this->panel3->Controls->Add(this->button1Shadow2Lab);
			this->panel3->Controls->Add(this->button1Shadow4Math);
			this->panel3->Controls->Add(this->textBoxShadowDetectionThreshold);
			this->panel3->Controls->Add(this->textBoxGrayAvg);
			this->panel3->Controls->Add(this->textBoxGrayDev);
			this->panel3->Controls->Add(this->label5);
			this->panel3->Controls->Add(this->label6);
			this->panel3->Controls->Add(this->label7);
			this->panel3->Location = System::Drawing::Point(478, 448);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(175, 163);
			this->panel3->TabIndex = 110;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(16, 93);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(137, 13);
			this->label13->TabIndex = 86;
			this->label13->Text = L"Grayscale image properties:";
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel4->Controls->Add(this->textBoxEdgesProcMedianFilterDilationKernelSize);
			this->panel4->Controls->Add(this->label23);
			this->panel4->Controls->Add(this->textBoxEdgesProcGaussianFilterDilationKernelSize);
			this->panel4->Controls->Add(this->label22);
			this->panel4->Controls->Add(this->textBoxEdgesProcMedianFilterKernelSize);
			this->panel4->Controls->Add(this->label20);
			this->panel4->Controls->Add(this->textBoxEdgesProcGaussianFilterKernelSize);
			this->panel4->Controls->Add(this->label19);
			this->panel4->Controls->Add(this->label18);
			this->panel4->Controls->Add(this->buttonSmoothUsingMedianFilter);
			this->panel4->Controls->Add(this->buttonSmoothUsingGaussianFilter);
			this->panel4->Controls->Add(this->buttonInpaintEdges);
			this->panel4->Controls->Add(this->label17);
			this->panel4->Controls->Add(this->textBoxEdgesProcInpaintRadius);
			this->panel4->Controls->Add(this->label16);
			this->panel4->Controls->Add(this->textBoxEdgesProcDilationKernelSize);
			this->panel4->Controls->Add(this->label15);
			this->panel4->Location = System::Drawing::Point(1054, 440);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(350, 213);
			this->panel4->TabIndex = 111;
			// 
			// textBoxEdgesProcMedianFilterDilationKernelSize
			// 
			this->textBoxEdgesProcMedianFilterDilationKernelSize->Location = System::Drawing::Point(24, 139);
			this->textBoxEdgesProcMedianFilterDilationKernelSize->Multiline = true;
			this->textBoxEdgesProcMedianFilterDilationKernelSize->Name = L"textBoxEdgesProcMedianFilterDilationKernelSize";
			this->textBoxEdgesProcMedianFilterDilationKernelSize->Size = System::Drawing::Size(95, 20);
			this->textBoxEdgesProcMedianFilterDilationKernelSize->TabIndex = 120;
			this->textBoxEdgesProcMedianFilterDilationKernelSize->Text = L"0";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(21, 123);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(98, 13);
			this->label23->TabIndex = 121;
			this->label23->Text = L"Dilation kernel size:";
			// 
			// textBoxEdgesProcGaussianFilterDilationKernelSize
			// 
			this->textBoxEdgesProcGaussianFilterDilationKernelSize->Location = System::Drawing::Point(24, 98);
			this->textBoxEdgesProcGaussianFilterDilationKernelSize->Multiline = true;
			this->textBoxEdgesProcGaussianFilterDilationKernelSize->Name = L"textBoxEdgesProcGaussianFilterDilationKernelSize";
			this->textBoxEdgesProcGaussianFilterDilationKernelSize->Size = System::Drawing::Size(95, 20);
			this->textBoxEdgesProcGaussianFilterDilationKernelSize->TabIndex = 118;
			this->textBoxEdgesProcGaussianFilterDilationKernelSize->Text = L"0";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(21, 82);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(98, 13);
			this->label22->TabIndex = 119;
			this->label22->Text = L"Dilation kernel size:";
			// 
			// textBoxEdgesProcMedianFilterKernelSize
			// 
			this->textBoxEdgesProcMedianFilterKernelSize->Location = System::Drawing::Point(125, 139);
			this->textBoxEdgesProcMedianFilterKernelSize->Multiline = true;
			this->textBoxEdgesProcMedianFilterKernelSize->Name = L"textBoxEdgesProcMedianFilterKernelSize";
			this->textBoxEdgesProcMedianFilterKernelSize->Size = System::Drawing::Size(64, 20);
			this->textBoxEdgesProcMedianFilterKernelSize->TabIndex = 114;
			this->textBoxEdgesProcMedianFilterKernelSize->Text = L"0";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(122, 123);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(61, 13);
			this->label20->TabIndex = 115;
			this->label20->Text = L"Kernel size:";
			// 
			// textBoxEdgesProcGaussianFilterKernelSize
			// 
			this->textBoxEdgesProcGaussianFilterKernelSize->Location = System::Drawing::Point(123, 97);
			this->textBoxEdgesProcGaussianFilterKernelSize->Multiline = true;
			this->textBoxEdgesProcGaussianFilterKernelSize->Name = L"textBoxEdgesProcGaussianFilterKernelSize";
			this->textBoxEdgesProcGaussianFilterKernelSize->Size = System::Drawing::Size(64, 20);
			this->textBoxEdgesProcGaussianFilterKernelSize->TabIndex = 112;
			this->textBoxEdgesProcGaussianFilterKernelSize->Text = L"0";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(120, 82);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(61, 13);
			this->label19->TabIndex = 113;
			this->label19->Text = L"Kernel size:";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(3, 61);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(46, 13);
			this->label18->TabIndex = 111;
			this->label18->Text = L"Smooth:";
			// 
			// buttonSmoothUsingMedianFilter
			// 
			this->buttonSmoothUsingMedianFilter->Location = System::Drawing::Point(193, 134);
			this->buttonSmoothUsingMedianFilter->Name = L"buttonSmoothUsingMedianFilter";
			this->buttonSmoothUsingMedianFilter->Size = System::Drawing::Size(152, 25);
			this->buttonSmoothUsingMedianFilter->TabIndex = 109;
			this->buttonSmoothUsingMedianFilter->Text = L"Smooth using Median filter";
			this->buttonSmoothUsingMedianFilter->UseVisualStyleBackColor = true;
			this->buttonSmoothUsingMedianFilter->Click += gcnew System::EventHandler(this, &Form1::buttonSmoothUsingMedianFilter_Click);
			// 
			// buttonSmoothUsingGaussianFilter
			// 
			this->buttonSmoothUsingGaussianFilter->Location = System::Drawing::Point(193, 95);
			this->buttonSmoothUsingGaussianFilter->Name = L"buttonSmoothUsingGaussianFilter";
			this->buttonSmoothUsingGaussianFilter->Size = System::Drawing::Size(152, 25);
			this->buttonSmoothUsingGaussianFilter->TabIndex = 108;
			this->buttonSmoothUsingGaussianFilter->Text = L"Smooth using Gaussian filter";
			this->buttonSmoothUsingGaussianFilter->UseVisualStyleBackColor = true;
			this->buttonSmoothUsingGaussianFilter->Click += gcnew System::EventHandler(this, &Form1::buttonSmoothUsingGaussianFilter_Click);
			// 
			// buttonInpaintEdges
			// 
			this->buttonInpaintEdges->Location = System::Drawing::Point(201, 31);
			this->buttonInpaintEdges->Name = L"buttonInpaintEdges";
			this->buttonInpaintEdges->Size = System::Drawing::Size(143, 25);
			this->buttonInpaintEdges->TabIndex = 107;
			this->buttonInpaintEdges->Text = L"Inpaint";
			this->buttonInpaintEdges->UseVisualStyleBackColor = true;
			this->buttonInpaintEdges->Click += gcnew System::EventHandler(this, &Form1::buttonInpaintEdges_Click);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(3, 2);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(42, 13);
			this->label17->TabIndex = 106;
			this->label17->Text = L"Inpaint:";
			// 
			// textBoxEdgesProcInpaintRadius
			// 
			this->textBoxEdgesProcInpaintRadius->Location = System::Drawing::Point(125, 34);
			this->textBoxEdgesProcInpaintRadius->Multiline = true;
			this->textBoxEdgesProcInpaintRadius->Name = L"textBoxEdgesProcInpaintRadius";
			this->textBoxEdgesProcInpaintRadius->Size = System::Drawing::Size(70, 20);
			this->textBoxEdgesProcInpaintRadius->TabIndex = 104;
			this->textBoxEdgesProcInpaintRadius->Text = L"0";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(122, 18);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(73, 13);
			this->label16->TabIndex = 105;
			this->label16->Text = L"Inpaint radius:";
			// 
			// textBoxEdgesProcDilationKernelSize
			// 
			this->textBoxEdgesProcDilationKernelSize->Location = System::Drawing::Point(24, 34);
			this->textBoxEdgesProcDilationKernelSize->Multiline = true;
			this->textBoxEdgesProcDilationKernelSize->Name = L"textBoxEdgesProcDilationKernelSize";
			this->textBoxEdgesProcDilationKernelSize->Size = System::Drawing::Size(95, 20);
			this->textBoxEdgesProcDilationKernelSize->TabIndex = 102;
			this->textBoxEdgesProcDilationKernelSize->Text = L"0";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(21, 18);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(98, 13);
			this->label15->TabIndex = 103;
			this->label15->Text = L"Dilation kernel size:";
			// 
			// buttonEdgesProcessingDefault
			// 
			this->buttonEdgesProcessingDefault->Location = System::Drawing::Point(964, 602);
			this->buttonEdgesProcessingDefault->Name = L"buttonEdgesProcessingDefault";
			this->buttonEdgesProcessingDefault->Size = System::Drawing::Size(75, 23);
			this->buttonEdgesProcessingDefault->TabIndex = 102;
			this->buttonEdgesProcessingDefault->Text = L"Default";
			this->buttonEdgesProcessingDefault->UseVisualStyleBackColor = true;
			this->buttonEdgesProcessingDefault->Click += gcnew System::EventHandler(this, &Form1::buttonEdgesProcessingDefault_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(1051, 424);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(91, 13);
			this->label14->TabIndex = 112;
			this->label14->Text = L"Edges processing";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1416, 662);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->buttonDestroyAlllWindows);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->buttonHandleEdges);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->buttonEdgesProcessingDefault);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->buttonTestMEANSHIFT);
			this->Controls->Add(this->pictureBoxImgShadowMask);
			this->Controls->Add(this->pictureBoxImgBGR);
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
			this->Controls->Add(this->pictureBoxImgBGRRes);
			this->Controls->Add(this->button1open);
			this->Controls->Add(this->textBox1open);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form1";
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResizeEnd += gcnew System::EventHandler(this, &Form1::Form1_ResizeEnd);
			this->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::Form1_Scroll);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxImgBGRRes))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxImgBGR))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxImgShadowMask))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	

	private: bool OpenImage(bool OpenDialog)
	{
				if (OpenDialog){
					OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
					openFileDialog1->InitialDirectory = "./";
					openFileDialog1->Filter = "Image Files (*.bmp, *.jpg, *.jpeg, *.png, *.gif) | *.bmp; *.jpg; *.jpeg; *.png; *.gif|BMP Files|*.bmp|JPG Files|*.jpg; *.jpeg|PNG Files|*.png|GIF Files|*.gif";
					openFileDialog1->FilterIndex = 1;
					openFileDialog1->RestoreDirectory = true;

					System::Windows::Forms::DialogResult dialogRes = openFileDialog1->ShowDialog();

					if (dialogRes == System::Windows::Forms::DialogResult::Cancel)
					{
						OPEN = OPEN;//OPEN=true;
						return false;
					}
					OPEN = false;
					if (dialogRes != System::Windows::Forms::DialogResult::OK)
					{
						//MessageBox::Show("Dialog error!");
						return false;
					}
					if ((myStream = openFileDialog1->OpenFile()) == nullptr)
					{
						MessageBox::Show("Stream error!");
						return false;
					}

					//получение полного пути к файлу
					myPath = openFileDialog1->FileName;
					textBox1open->Text = myPath;
					myStream->Close();
					delete openFileDialog1;
				}

				//Конвертация пути с System::String to char*
				using namespace System::Runtime::InteropServices;
				myPath_char = (char*)(void*)Marshal::StringToHGlobalAnsi(myPath);

				//Read file
				//OpenedImageData::Open(myPath);
				imgBGR = cv::imread(myPath_char);
				//imgBGRRes = cv::Mat(imgBGR.rows, imgBGR.cols, CV_8UC3);
				imgBGRRes = imgBGR.clone();
				imgShadowMask = cv::Mat(imgBGR.rows, imgBGR.cols, CV_8UC3);

				OPEN = true;//флаг, что открыт файл

				return true;
	}

	private: void ShowImgBGR()
	{
//				pictureBoxImgBGR->Image = gcnew System::Drawing::Bitmap
//					(imgBGR.cols, imgBGR.rows, imgBGR.step,
//					System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) imgBGR.ptr());
//				pictureBoxImgBGR->Refresh();

				 System::Drawing::Graphics^ graphics2 = pictureBoxImgBGR->CreateGraphics();
				 System::IntPtr ptr2(imgBGR.ptr());
				 System::Drawing::Bitmap^ b2 = gcnew System::Drawing::Bitmap(imgBGR.cols,
					 imgBGR.rows, imgBGR.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr2);
				 System::Drawing::RectangleF rect2(0, 0, pictureBoxImgBGR->Width, pictureBoxImgBGR->Height);
				 graphics2->DrawImage(b2, rect2);
	}

	private: void ShowImgShadowMask()
	{
//				 pictureBoxImgShadowMask->Image = gcnew System::Drawing::Bitmap
//					 (imgShadowMask.cols, imgShadowMask.rows, imgShadowMask.step,
//					 System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) imgShadowMask.ptr());
//				 pictureBoxImgShadowMask->Refresh();

				 System::Drawing::Graphics^ graphics2 = pictureBoxImgShadowMask->CreateGraphics();
				 System::IntPtr ptr2(imgShadowMask.ptr());
				 System::Drawing::Bitmap^ b2 = gcnew System::Drawing::Bitmap(imgShadowMask.cols,
					 imgShadowMask.rows, imgShadowMask.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr2);
				 System::Drawing::RectangleF rect2(0, 0, pictureBoxImgShadowMask->Width, pictureBoxImgShadowMask->Height);
				 graphics2->DrawImage(b2, rect2);
	}

	private: void ShowImgBGRRes()
	{
//				 pictureBoxImgBGRRes->Image = gcnew System::Drawing::Bitmap
//					 (imgBGRRes.cols, imgBGRRes.rows, imgBGRRes.step,
//					 System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr) imgBGRRes.ptr());
//				 pictureBoxImgBGRRes->Refresh(System::Drawing::Graphics^ graphics2 = pictureBoxImgShadowMask->CreateGraphics();

				 System::Drawing::Graphics^ graphics2 = pictureBoxImgBGRRes->CreateGraphics();
				 System::IntPtr ptr2(imgBGRRes.ptr());
				 System::Drawing::Bitmap^ b2 = gcnew System::Drawing::Bitmap(imgBGRRes.cols,
					 imgBGRRes.rows, imgBGRRes.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr2);
				 System::Drawing::RectangleF rect2(0, 0, pictureBoxImgBGRRes->Width, pictureBoxImgBGRRes->Height);
				 graphics2->DrawImage(b2, rect2);
	}

	private: bool SaveImgBGRRes()
	{
				 try
				 {
					 cv::imwrite(myPath_char, imgBGRRes);
				 }
				 catch (...)
				 {
					 return false;
				 }

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

	private: float myFabs(float x)
			 {
				 if(x < 0)
					 return -x;
				 else
					 return x;
			 }

	//END
		 
		 //Открыть
private: System::Void button1open_Click(System::Object^  sender, System::EventArgs^  e) {

				 button6Close_Click(sender,e);

				 //if( !OpenBmp(true) )
				 if (!OpenImage(true))
					 return;

				 ShowImgBGR();
				 ShowImgBGRRes();
				
				 button7colorCorrection->Enabled=true;
				 buttonRestoreImage->Enabled=true;

				 textBoxShadowDetectionThreshold->Text = System::Convert::ToString(0);
				 textBoxGrayAvg->Text = System::Convert::ToString(0);
				 textBoxGrayDev->Text = System::Convert::ToString(0);
		 }

private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

			 //Set mean shift segmentation params
			 textBoxMSSSpatialRadius->Text = System::Convert::ToString(MeanShiftParams::SPATIAL_RADIUS);
			 textBoxMSSColorRadius->Text = System::Convert::ToString(MeanShiftParams::COLOR_RADIUS);
			 textBoxMSSMinRegionSize->Text = System::Convert::ToString(MeanShiftParams::MIN_REGION_SIZE);

			 DisplayEdgesProcessingDefaultParams();
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
			 
			 //if(SaveBMP())
			 if(SaveImgBGRRes())
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
				 //ShowBmp();
			 }
		 }

		 //Обновить изображение при прокрутке формы
private: System::Void Form1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			 if(OPEN)
			 {
				 //ShowBmp();
			 }
		 }

		 //Получение фокуса
private: System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
			 if(OPEN)
			 {
				 //ShowBmp();
			 }
		 }

		 //Обновить при нажатии мишкой
private: System::Void pictureBoxImgBGRRes_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(OPEN)
			 {
				 //ShowBmp();
			 }
		 }

private: void ReleaseImage()
{
			 imgBGR.release();
			 imgBGRRes.release();
			 imgShadowMask.release();
}
		 
		 //Закрыть
private: System::Void button6Close_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 ReleaseImage();

			 pictureBoxImgBGRRes->Image = nullptr;
			 pictureBoxImgBGR->Image = nullptr;
			 pictureBoxImgShadowMask->Image = nullptr;

			 pictureBoxImgBGRRes->Refresh();
			 pictureBoxImgBGR->Refresh();
			 pictureBoxImgShadowMask->Refresh();

			 button7colorCorrection->Enabled=false;
			 buttonRestoreImage->Enabled=false;
	
			 textBox1open->Clear();
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

			 for (int i = 0; i < imgBGRRes.rows; i += 1) {
				 for (int j = 0; j < imgBGRRes.cols; j += 1) {

					 cv::Vec3b &pixel = imgBGRRes.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

					 if (shadowMaskPixel.val[0] == 255)
					 {
						 int B = pixel.val[0];
						 int G = pixel.val[1];
						 int R = pixel.val[2];

						 B + Blue + RGB>255 ? B = 255 : (B + Blue + RGB<0 ? B = 0 : B += Blue + RGB);//Blue
						 G + Green + RGB>255 ? G = 255 : (G + Green + RGB<0 ? G = 0 : G += Green + RGB);//Green
						 R + Red + RGB>255 ? R = 255 : (R + Red + RGB < 0 ? R = 0 : R += Red + RGB);//Red

						 pixel.val[0] = B;
						 pixel.val[1] = G;
						 pixel.val[2] = R;
					 }
				 }
			 }

			 ShowImgBGRRes();
		 }

		 //Востановить массив пикселей, который был при откритии файла
private: System::Void buttonRestoreImage_Click(System::Object^  sender, System::EventArgs^  e) {

			 imgBGRRes = imgBGR.clone();
			 ShowImgBGRRes();
		 }

		 //Обнулить значения цветов
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

			 textBoxRed->Text="0";
			 textBoxGreen->Text="0";
			 textBoxBlue->Text="0";
			 textBoxRGB->Text="0";
		 }

/*private: void K_Means(){

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
			 #1#

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
				 int[] class_q = new int[Q];#1#

				 double **teta = new double*[1];
				 for (int i = 0; i < 1; i++){
					 teta[i] = new double[Qn];
				 }
				 
				 int *class_q = new int[Q];

				 ///* Цикл занесення векторів до кластерів з найближчим центром #1#
				 for (int q = 0; q < Q; q++)
				 {
					 double d_min = 999999999.1;//999999.9;
					 double d = 0;
					 int k_min = 0;

					 ///* Цикл знаходження мінімальної відстані до центрів #1#
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
					 /*Позначення вектора x_q k-им класом #1#
					 //class(q) = k_min
					 class_q[q] = k_min;

					 //n(k_min) = n(k_min) + 1 ///* Інкрементація лічильника векторів k_min-го класу 
					 n_k[k_min] += 1;
				 }

				//Крок 3
				 //Console.WriteLine("Крок 3");

				 /* Цикл обчислення K нових центрів кластерів #1#
				 for (int k = 0; k < K; k++)
				 {
					 /* Знаходження середнього k1-го кластера #1#
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

				 ///* Цикл фіксації зміни хоча б одного центра за допомогою прапорця #1#
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

				 ///* При наявності змін обновити центри і повторити процедуру #1#
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
				 /* Інакше припинити кластеризацію #1#
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
						 #1#
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
							//	 continue;#1#

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
						 ShowBmp();#1#
						 
					 }
					 
					 
					 if (true)
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

}*/

//private: UCHAR* SwapBGRtoRGB(UCHAR* bufferBGR)
//{
//			 UCHAR* bufferRGB = new UCHAR[size];
//
//			 for (int i = 0; i < size; i += 3)
//			 {
//				 int B = bufferBGR[i];
//				 int G = bufferBGR[i + 1];
//				 int R = bufferBGR[i + 2];
//
//				 bufferRGB[i] = R;
//				 bufferRGB[i + 1] = G;
//				 bufferRGB[i + 2] = B;
//
//			 }
//
//			 return bufferRGB;
//}		

private: System::Void buttonAdditive_Click(System::Object^  sender, System::EventArgs^  e) {

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

			 for (int i = 0; i < imgBGR.rows; i += 1) {
				 for (int j = 0; j < imgBGR.cols; j += 1) {

					 cv::Vec3b &pixel = imgBGR.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

					 int Y = pixel.val[0];

					 if (shadowMaskPixel.val[0] == 255){
						 BS += pixel.val[0];
						 GS += pixel.val[1];
						 RS += pixel.val[2];

						 nShadow++;
					 }
					 else{
						 B += pixel.val[0];
						 G += pixel.val[1];
						 R += pixel.val[2];

						 nNonShadow++;
					 }
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

			 for (int i = 0; i < imgBGR.rows; i += 1) {
				 for (int j = 0; j < imgBGR.cols; j += 1) {

					 cv::Vec3b &pixel = imgBGR.at<cv::Vec3b>(i, j);
					 cv::Vec3b &pixelRes = imgBGRRes.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

					 int Y = pixel.val[0];

					 if (shadowMaskPixel.val[0] == 255){
						 int currB = pixel.val[0];
						 int currG = pixel.val[1];
						 int currR = pixel.val[2];

						 currB += diffB;
						 currG += diffG;
						 currR += diffR;

						 currB = currB > 255 ? 255 : (currB < 0 ? 0 : currB);
						 currG = currG > 255 ? 255 : (currG < 0 ? 0 : currG);
						 currR = currR > 255 ? 255 : (currR < 0 ? 0 : currR);

						 pixelRes.val[0] = currB;
						 pixelRes.val[1] = currG;
						 pixelRes.val[2] = currR;
					 }
				 }
			 }

			 ShowImgBGRRes();

			 return;
}

private: System::Void buttonBasicLightModel_Click(System::Object^  sender, System::EventArgs^  e) {
			 
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

			 for (int i = 0; i < imgBGR.rows; i += 1) {
				 for (int j = 0; j < imgBGR.cols; j += 1) {

					 cv::Vec3b &pixel = imgBGR.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

					 if (shadowMaskPixel.val[0] == 255){
						 BS += pixel.val[0];
						 GS += pixel.val[1];
						 RS += pixel.val[2];

						 nShadow++;
					 }
					 else{
						 B += pixel.val[0];
						 G += pixel.val[1];
						 R += pixel.val[2];

						 nNonShadow++;
					 }
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

			 for (int i = 0; i < imgBGR.rows; i += 1) {
				 for (int j = 0; j < imgBGR.cols; j += 1) {

					 cv::Vec3b &pixel = imgBGR.at<cv::Vec3b>(i, j);
					 cv::Vec3b &pixelRes = imgBGRRes.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

					 if (shadowMaskPixel.val[0] == 255){
						 double currB = pixel.val[0];
						 double currG = pixel.val[1];
						 double currR = pixel.val[2];

						 currB *= ratioB;
						 currG *= ratioG;
						 currR *= ratioR;

						 currB = currB > 255 ? 255 : (currB < 0 ? 0 : currB);
						 currG = currG > 255 ? 255 : (currG < 0 ? 0 : currG);
						 currR = currR > 255 ? 255 : (currR < 0 ? 0 : currR);

						 pixelRes.val[0] = currB;
						 pixelRes.val[1] = currG;
						 pixelRes.val[2] = currR;
					 }
				 }
			 }

			 ShowImgBGRRes();

			 return;
}

private: System::Void buttonYCbCr_Click(System::Object^  sender, System::EventArgs^  e) {

			 //RGBtoYCbCr();
			 cv::Mat imgYcbCr;
			 cv::cvtColor(imgBGR, imgYcbCr,CV_BGR2YCrCb);

			 float Y = 0;
			 float Cb = 0;
			 float Cr = 0;

			 float YS = 0;
			 float CbS = 0;
			 float CrS = 0;

			 float intensity = 0;
			 float intensityS = 0;

			 int nShadow = 0;
			 int nNonShadow = 0;

			 for (int i = 0; i < imgYcbCr.rows; i += 1) {
				 for (int j = 0; j < imgYcbCr.cols; j += 1) {

					 cv::Vec3b &pixel = imgYcbCr.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

					 if (shadowMaskPixel.val[0] == 255){
						 YS += pixel.val[0];
						 CbS += pixel.val[1];
						 CrS += pixel.val[2];

						 nShadow++;
					 }
					 else{
						 Y += pixel.val[0];
						 Cb += pixel.val[1];
						 Cr += pixel.val[2];

						 nNonShadow++;
					 }
				 }
			 }

			 Y = Y / nNonShadow;
			 Cb = Cb / nNonShadow;
			 Cr = Cr / nNonShadow;

			 YS = YS / nShadow;
			 CbS = CbS / nShadow;
			 CrS = CrS / nShadow;

			 float diffY = Y - YS;
			 float diffCb = Cb - CbS;
			 float diffCr = Cr - CrS;

			 float ratioY = Y / YS;
			 float ratioCb = Cb / CbS;
			 float ratioCr = Cr / CrS;

			 for (int i = 0; i < imgYcbCr.rows; i += 1) {
				 for (int j = 0; j < imgYcbCr.cols; j += 1) {

					 cv::Vec3b &pixel = imgYcbCr.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

					 if (shadowMaskPixel.val[0] == 255){
						 double currY = pixel.val[0];
						 double currCb = pixel.val[1];
						 double currCr = pixel.val[2];

						 currY = currY + 1 * diffY;
						 currCb = ratioCb*currCb;
						 currCr = ratioCr*currCr;

						 currY = currY > 255 ? 255 : (currY < 0 ? 0 : currY);
						 currCb = currCb > 255 ? 255 : (currCb < 0 ? 0 : currCb);
						 currCr = currCr > 255 ? 255 : (currCr < 0 ? 0 : currCr);

						 pixel.val[0] = currY;
						 pixel.val[1] = currCb;
						 pixel.val[2] = currCr;
					 }
				 }
			 }

			 cv::cvtColor(imgYcbCr,imgBGRRes,CV_YCrCb2BGR);

			 ShowImgBGRRes();

			 return;
}

private: System::Void pictureBoxImgShadowMask_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (OPEN)
			 {
				 //ShowShadowMaskBmp();
			 }
}

private: System::Void buttonShadow0YCbCr_Click(System::Object^  sender, System::EventArgs^  e) {

			 imgShadowMask.release();
			 imgShadowMask = cv::Mat(imgBGR.rows, imgBGR.cols, CV_8UC3);

			 //convert to YCbCr;
			 cv::Mat imgYcbcr;
			 cv::cvtColor(imgBGR, imgYcbcr, CV_BGR2YCrCb);

			 //FIND Shadow Mask
			 //Computing the average at Y channel 
			 float averageY = 1;
			 float sum = 0;
			 
			 for (int i = 0; i < imgYcbcr.rows; i += 1) {
				 for (int j = 0; j < imgYcbcr.cols; j += 1) {

					 cv::Vec3b &pixel = imgYcbcr.at<cv::Vec3b>(i, j);

					 int Y = pixel.val[0];
					 sum += Y;
				 }
			 }
			 averageY = sum / (float)(imgYcbcr.cols*imgYcbcr.rows);

			 //find shadow mask
			 for (int i = 0; i < imgYcbcr.rows; i += 1) {
				 for (int j = 0; j < imgYcbcr.cols; j += 1) {

					 cv::Vec3b &pixel = imgYcbcr.at<cv::Vec3b>(i, j);
					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

					 int Y = pixel.val[0];

					 if (Y < averageY){
						 shadowMaskPixel.val[0] = 255;
						 shadowMaskPixel.val[1] = 255;
						 shadowMaskPixel.val[2] = 255;
					 }
					 else{
						 shadowMaskPixel.val[0] = 0;
						 shadowMaskPixel.val[1] = 0;
						 shadowMaskPixel.val[2] = 0;
					 }
				 }
			 }

//			 shadowMask = new UCHAR[size];
//			 CopyMatToArray(imgShadowMask, shadowMask);
//
//			 saveMaskBMP();
//			 ShowShadowMaskBmp();

			 ShowImgShadowMask();
}

private: System::Void button1Shadow2Lab_Click(System::Object^  sender, System::EventArgs^  e) {

			//OpenCV To LAB
			cv::Mat imgLABforDetectMat;
			cv::cvtColor(imgBGR, imgLABforDetectMat, CV_BGR2Lab);

			cv::Mat imgBufferCIELAB = imgLABforDetectMat.clone();

			imgShadowMask.release();
			imgShadowMask = cv::Mat(imgBGR.rows, imgBGR.cols, CV_8UC3);

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

			for (int i = 0; i < imgBufferCIELAB.rows; i += 1) {
				for (int j = 0; j < imgBufferCIELAB.cols; j += 1) {

					cv::Vec3b &pixel = imgBufferCIELAB.at<cv::Vec3b>(i, j);

					double CIE_L = pixel.val[0];
					double CIE_A = pixel.val[1];
					double CIE_B = pixel.val[2];

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
			}

			CIE_L_avg /= count;
			CIE_A_avg /= count;
			CIE_B_avg /= count;

			//standart deviation for L
			double stdDevL = 0;

			for (int i = 0; i < imgBufferCIELAB.rows; i += 1) {
				for (int j = 0; j < imgBufferCIELAB.cols; j += 1) {

					cv::Vec3b &pixel = imgBufferCIELAB.at<cv::Vec3b>(i, j);

					double CIE_L = pixel.val[0];

					stdDevL += pow(CIE_L - CIE_L_avg, 2);
				}
			}
			stdDevL = stdDevL*(1.0 / ((double)count - 1.0));
			stdDevL = sqrt(stdDevL);

			for (int i = 0; i < imgShadowMask.rows; i += 1) {
				for (int j = 0; j < imgShadowMask.cols; j += 1) {

					//cv::Vec3b &pixel = imgBGR.at<cv::Vec3b>(i, j);
					cv::Vec3b &pixel = imgLABforDetectMat.at<cv::Vec3b>(i, j);
					cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

					double CIE_L = pixel.val[0];
					double CIE_A = pixel.val[1];
					double CIE_B = pixel.val[2];

					if (CIE_A_avg + CIE_B_avg >= 256)//256
					{
						if (CIE_L <= (CIE_L_avg - stdDevL / 3.0))
						{
							shadowMaskPixel.val[0] = 255;
							shadowMaskPixel.val[1] = 255;
							shadowMaskPixel.val[2] = 255;
						}
						else
						{
							shadowMaskPixel.val[0] = 0;
							shadowMaskPixel.val[1] = 0;
							shadowMaskPixel.val[2] = 0;
						}
					}
					else
					{
						if (CIE_L < CIE_L_avg && CIE_B < CIE_B_avg)
						{
							shadowMaskPixel.val[0] = 255;
							shadowMaskPixel.val[1] = 255;
							shadowMaskPixel.val[2] = 255;
						}
						else
						{
							shadowMaskPixel.val[0] = 0;
							shadowMaskPixel.val[1] = 0;
							shadowMaskPixel.val[2] = 0;
						}
					}
				}
			}

			 //cv::Mat shadowMaskMat = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth,CV_8UC3);
			 cv::Mat shadowMaskClosingMat;
			 cv::Mat shadowMaskOpeningMat;
			 cv::Mat shadowMaskOpeningClosingMat;
			 cv::Mat shadowMaskClosingOpeningMat;
			 cv::Mat tmp;
			 cv::Mat thresholdFixed;
			 cv::Mat thresholdAdaptive;
			 cv::Mat shadowMaskErosionFollowedByDilation;
			 cv::Mat shadowMaskDilationFollowedByErosion;

			 //// Apply Closing
			 cv::Mat const structure_elem = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(5, 5));
			 cv::morphologyEx(imgShadowMask, shadowMaskClosingMat,
				 cv::MORPH_CLOSE, structure_elem);

			 //// Apply Opening
			 cv::Mat const structure_elem2 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(5, 5));
			 cv::morphologyEx(imgShadowMask, shadowMaskOpeningMat,
				 cv::MORPH_OPEN, structure_elem2);

			 //// Apply Opening Followed By Closing
			 cv::Mat const structure_elem3 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(3, 3));
			 cv::Mat const structure_elem4 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(7, 7));
			 cv::Mat const structure_elem444 = cv::getStructuringElement(
				 cv::MORPH_RECT, cv::Size(3, 3));
			 cv::morphologyEx(imgShadowMask, tmp,
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
			 cv::morphologyEx(imgShadowMask, tmp,
				 cv::MORPH_OPEN, structure_elem44);
			 

			 // Apply Erosion  Followed By Dilation 
			 cv::Mat elementEr = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(9, 9));
			 cv::Mat elementDil = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(11, 11));
			 cv::erode(imgShadowMask, tmp, elementEr);
			 cv::dilate(tmp, shadowMaskErosionFollowedByDilation, elementDil);

			 // Apply Dilation Followed By Erosion
			 cv::Mat elementDil2 = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(3, 3));
			 cv::Mat elementEr2 = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(7, 7));
			 cv::dilate(imgShadowMask, tmp, elementDil2);
			 cv::erode(tmp, shadowMaskDilationFollowedByErosion, elementEr2);
			 


			 cv::imshow("imgShadowMask", imgShadowMask);
			 cv::imshow("shadowMaskClosingMat", shadowMaskClosingMat);
			 cv::imshow("shadowMaskOpeningMat", shadowMaskOpeningMat);
			 cv::imshow("shadowMaskOpeningClosingMat", shadowMaskOpeningClosingMat);
			 cv::imshow("shadowMaskClosingOpeningMat", shadowMaskClosingOpeningMat);
			 cv::imshow("ErosionFollowedByDilation", shadowMaskErosionFollowedByDilation);
			 cv::imshow("DilationFollowedByErosion", shadowMaskDilationFollowedByErosion);

//			 shadowMask = new UCHAR[size];
//			 CopyMatToArray(shadowMaskErosionFollowedByDilation, shadowMask);
//
//			 saveMaskBMP();
//			 ShowShadowMaskBmp();

			 imgShadowMask = shadowMaskErosionFollowedByDilation.clone();
			 ShowImgShadowMask();
}

private: System::Void button11RemveLab_Click(System::Object^  sender, System::EventArgs^  e) {
			
			 //cv::Mat imgBGRres;
			 cv::Mat imgLAB;
			 cv::Mat imgLAB_ORIGIN;
			 cv::Mat imgKMeansRes;
			 cv::Mat imgBGRbeforeCluster;
			 //cv::Mat shadowMaskMat = cv::Mat(InfoHeader.biHeight, InfoHeader.biWidth,CV_8UC3);
			 
			 //Проверки на размер - если ширина не кратная 4, то дополняется мусором
			 /////////////////////////////////////////////////////////////////////////
			 //int biWidth = InfoHeader.biWidth;
			 //int biHeight = InfoHeader.biHeight;

			 //int biWidth_add = biWidth % 4;

//			 int cols = imgBGR.cols;
//			 int rows = imgBGR.rows;
//
//			 //int sizeB = size;
//			 int sizeB2 = (biWidth * 3)*biHeight;
//			 int sizeB3 = (biWidth * 3 + biWidth % 4)*biHeight;
//			 int size2 = imgBGR.rows*imgBGR.cols*imgBGR.channels();
			 /////////////////////////////////////////////////////////////////////////////

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

					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);

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

					 cv::Vec3b &shadowMaskPixel = imgShadowMask.at<cv::Vec3b>(i, j);
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

			 cv::cvtColor(imgLAB, imgBGRbeforeCluster, CV_Lab2BGR);

			 //Mean Shift  takes BGR and do in LAB, writes res in first param
			 cv::Mat imgMeanShiftVisual = imgBGR.clone();
			 cv::Mat imgForMeanShiftForCluster;
			 cv::Mat imgForMeanShiftForAlign;
			 cv::cvtColor(imgLAB, imgForMeanShiftForAlign, CV_Lab2BGR);
			 cv::cvtColor(imgLAB_ORIGIN, imgForMeanShiftForCluster, CV_Lab2BGR);
			 //cv::cvtColor(imgLAB, imgForMeanShiftForCluster, CV_Lab2BGR);
			 ApplyMeanShiftAndCorrections(imgForMeanShiftForCluster, imgForMeanShiftForAlign, imgMeanShiftVisual);
			 cv::imshow("imgMeanShiftVisual", imgMeanShiftVisual);
			 imgBGRRes = imgForMeanShiftForAlign.clone();

			 cv::imshow("imgBGR", imgBGR);
			 //cv::imshow("imgLAB", imgLAB);
			 cv::imshow("imgBGRRelight", imgBGRbeforeCluster);
			 cv::imshow("imgBGRRes", imgBGRRes);

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
//			 imgBGR.release();
//			 delete imgBGR.data;
//
//			 imgLAB.release();
//			 delete imgLAB.data;
//
//			 imgBGRres.release();
//			 delete imgBGRres.data;

			 ShowImgBGRRes();
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
			 cv::Mat imgResLABOnlyChroma;
			 cv::cvtColor(imgForAlign, imgResLAB, CV_BGR2Lab);
			 cv::cvtColor(imgForAlign, imgResLABAddLDiff, CV_BGR2Lab);
			 cv::cvtColor(imgForAlign, imgResLABOnlyChroma, CV_BGR2Lab);
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

			 //regions that have already aligned
			 //std::vector<int> hadled_shadow_regions_labels; 
			 bool *hadled_shadow_regions_labels = new bool[regionCount];
			 bool *hadled_shadow_regions_labels_FOR_NEXT_ITER = new bool[regionCount];
			 for (int i = 0; i < regionCount; i++)
			 {
				 hadled_shadow_regions_labels[i] = false;
				 hadled_shadow_regions_labels_FOR_NEXT_ITER[i] = false;
			 }

			 std::vector<int> unhadled_shadow_regions_labels; //regions that have not aligned

			 //Loop through all labels (clusters)
			 for (int iterations = 0; iterations < 10; iterations++){
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

//					 if (std::find(hadled_shadow_regions_labels.begin(), hadled_shadow_regions_labels.end(), CURRENT_LABEL) != hadled_shadow_regions_labels.end()) { //if found
//						 continue;
//					 }

					 if (hadled_shadow_regions_labels[CURRENT_LABEL] == true)
					 {
						 continue;
					 }


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
					 int min_deviation = 6;
					 int max_deviation = 20;
					 int max_iterations = max_deviation*100;
					 for (int it = 0; adjacent_labels.size() < min_adjacent_labels_required; it++) {
						 for (int dev = min_deviation; dev <= max_deviation; dev++) {
							 for (int i = 0; i < imgSourceLAB.rows; i++) {
								 bool break_ = false;
								 for (int j = 0; j < imgSourceLAB.cols; j++) {

									 //Handle current region
									 int cl = ilabels[i][j];
									 if (cl != CURRENT_LABEL) //CURRENT_LABEL == SHADOW_LABEL
									 {
										 continue;
									 }

									 //check handled shadow regions
									 bool i_plus = false;
									 bool i_minus = false;
									 bool j_plus = false;
									 bool j_minus = false;
//									 if (std::find(hadled_shadow_regions_labels.begin(), hadled_shadow_regions_labels.end(), ilabels[i + dev][j]) != hadled_shadow_regions_labels.end()) { //if found
//										 i_plus = true;
//									 }
//									 if (std::find(hadled_shadow_regions_labels.begin(), hadled_shadow_regions_labels.end(), ilabels[i - dev][j]) != hadled_shadow_regions_labels.end()) { //if found
//										 i_minus = true;
//									 }
//									 if (std::find(hadled_shadow_regions_labels.begin(), hadled_shadow_regions_labels.end(), ilabels[i][j + dev]) != hadled_shadow_regions_labels.end()) { //if found
//										 j_plus = true;
//									 }
//									 if (std::find(hadled_shadow_regions_labels.begin(), hadled_shadow_regions_labels.end(), ilabels[i][j - dev]) != hadled_shadow_regions_labels.end()) { //if found
//										 j_minus = true;
//									 }
									 

									 //Go 1px to 4 base direction - up,down,left,right
									 if (i + dev < imgSourceLAB.rows)
									 {
										 if (hadled_shadow_regions_labels[ilabels[i + dev][j]] == true) { //if found
											 i_plus = true;
										 }

										 cv::Vec3b &pixelDown = imgShadowMask.at<cv::Vec3b>(i + dev, j);
										 //if non shadow
										 if (pixelDown.val[0] == 0 || i_plus){
											 //adjacent_labels.push_back(ilabels[i + 1][j]);
											 int ilabel = ilabels[i + dev][j];
											 if (std::find(adjacent_labels.begin(), adjacent_labels.end(), ilabel) == adjacent_labels.end()) {
												 adjacent_labels.push_back(ilabel);
											 }
										 }
									 }
									 if (i - dev >= 0)
									 {
										 if (hadled_shadow_regions_labels[ilabels[i - dev][j]] == true) { //if found
											 i_minus = true;
										 }

										 cv::Vec3b &pixelUp = imgShadowMask.at<cv::Vec3b>(i - dev, j);
										 //if non shadow
										 if (pixelUp.val[0] == 0 || i_minus){
											 //adjacent_labels.push_back(ilabels[i - 1][j]);
											 int ilabel = ilabels[i - dev][j];
											 if (std::find(adjacent_labels.begin(), adjacent_labels.end(), ilabel) == adjacent_labels.end()) {
												 adjacent_labels.push_back(ilabel);
											 }
										 }
									 }
									 if (j + dev < imgSourceLAB.cols)
									 {
										 if (hadled_shadow_regions_labels[ilabels[i][j + dev]] == true) { //if found
											 j_plus = true;
										 }

										 cv::Vec3b &pixelRight = imgShadowMask.at<cv::Vec3b>(i, j + dev);
										 //if non shadow
										 if (pixelRight.val[0] == 0 || j_plus){
											 //adjacent_labels.push_back(ilabels[i][j + 1]);
											 int ilabel = ilabels[i][j + dev];
											 if (std::find(adjacent_labels.begin(), adjacent_labels.end(), ilabel) == adjacent_labels.end()) {
												 adjacent_labels.push_back(ilabel);
											 }
										 }
									 }
									 if (j - dev >= 0)
									 {
										 if (hadled_shadow_regions_labels[ilabels[i][j - dev]] == true) { //if found
											 j_minus = true;
										 }

										 cv::Vec3b &pixelLeft = imgShadowMask.at<cv::Vec3b>(i, j - dev);
										 //if non shadow
										 if (pixelLeft.val[0] == 0 || j_minus){
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
						 if (NON_SHADOW_LABEL_COUNT < SHADOW_LABEL_COUNT*0.05)
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

					 //if no non shadow region found
					 if (SHADOW_LABEL == -1 || NON_SHADOW_LABEL == -1)
					 {
						 unhadled_shadow_regions_labels.push_back(SHADOW_LABEL);
						 continue;
					 }

					 //mark shadow region as handled
					 //hadled_shadow_regions_labels.push_back(SHADOW_LABEL);
					 hadled_shadow_regions_labels_FOR_NEXT_ITER[SHADOW_LABEL] = true;

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
							 //L = ((L*L_ratio) + (L + L_diff_))/2.0;
							 //L += L_diff_;
							 A *= A_ratio;
							 B *= B_ratio;

//							 //If region colors too far from shadow region colors - only relight
//							 int COLOR_METRIC_THRESHOLD = 20;
//							 if (LAB_delta_e_metric < COLOR_METRIC_THRESHOLD)
//							 {
//								 L *= L_ratio;
//								 A *= A_ratio;
//								 B *= B_ratio;
//							 }
//							 else
//							 {
//								 L *= L_ratio;
//								 //L += L_diff_;
//							 }

							

							 L = (L > 255 ? 255 : (L < 0 ? 0 : L));
							 A = (A > 255 ? 255 : (A < 0 ? 0 : A));
							 B = (B > 255 ? 255 : (B < 0 ? 0 : B));
							

							pixel.val[0] = L;
							pixel.val[1] = A;
							pixel.val[2] = B;

							 //Add diff image
							 
							 cv::Vec3b &pixel2 = imgResLABAddLDiff.at<cv::Vec3b>(i, j);
							 double L2 = pixel2.val[0];
							 double A2 = pixel2.val[1];
							 double B2 = pixel2.val[2];

							 L2 += L_diff_;
							 A2 *= A_ratio;
							 B2 *= B_ratio;

//							 if (LAB_delta_e_metric < COLOR_METRIC_THRESHOLD)
//							 {
//								 A2 *= A_ratio;
//								 B2 *= B_ratio;
//							 }

							 L2 = (L2 > 255 ? 255 : (L2 < 0 ? 0 : L2));
							 A2 = (A2 > 255 ? 255 : (A2 < 0 ? 0 : A2));
							 B2 = (B2 > 255 ? 255 : (B2 < 0 ? 0 : B2));

							 pixel2.val[0] = L2;
							 pixel2.val[1] = A2;
							 pixel2.val[2] = B2;

							 //imgResLABOnlyChroma
							 cv::Vec3b &pixel3 = imgResLABOnlyChroma.at<cv::Vec3b>(i, j);
							 double L3 = pixel3.val[0];
							 double A3 = pixel3.val[1];
							 double B3 = pixel3.val[2];
							 
							 //L3 += L_diff_;
							 A3 *= A_ratio;
							 B3 *= B_ratio;

							 L3 = (L3 > 255 ? 255 : (L3 < 0 ? 0 : L3));
							 A3 = (A3 > 255 ? 255 : (A3 < 0 ? 0 : A3));
							 B3 = (B3 > 255 ? 255 : (B3 < 0 ? 0 : B3));

							 pixel3.val[0] = L3;
							 pixel3.val[1] = A3;
							 pixel3.val[2] = B3;
						 }
					 }
				 }

//				 delete hadled_shadow_regions_labels;
//				 hadled_shadow_regions_labels = hadled_shadow_regions_labels_FOR_NEXT_ITER;
//				 hadled_shadow_regions_labels_FOR_NEXT_ITER = new bool[regionCount];
				 for (int i = 0; i < regionCount; i++)
				 {
					 //hadled_shadow_regions_labels_FOR_NEXT_ITER[i] = false;

					 hadled_shadow_regions_labels[i] = hadled_shadow_regions_labels[i] || hadled_shadow_regions_labels_FOR_NEXT_ITER[i];
				 }

				 //if some regions was not aligned then repeat procedure
				 if (unhadled_shadow_regions_labels.size() > 0)
				 {
					 int a = 0;
				 }
				 else
				 {
					 break;
				 }

				 imgSourceLAB = imgResLAB.clone();

//				 cv::Mat imgIter;
//				 cv::cvtColor(imgResLAB, imgIter, CV_Lab2BGR);
//				 System::String ^str = "imgIter ";
//				 cv::imshow(System::Convert:z(iterations), imgIter);
			 }
			 cv::Mat imgResBGROnlyChroma;
			 cv::cvtColor(imgResLAB, imgResBGR, CV_Lab2BGR);
			 cv::cvtColor(imgResLABAddLDiff, imgResBGRAddDiff, CV_Lab2BGR);
			 cv::cvtColor(imgResLABOnlyChroma, imgResBGROnlyChroma, CV_Lab2BGR);
			 cv::imshow("!! imgResBGR", imgResBGR);
			 cv::imshow("!! imgResBGRAddDiff", imgResBGRAddDiff);
			 cv::imshow("!! imgResBGROnlyChroma", imgResBGROnlyChroma);

			 cv::cvtColor(imgResLAB, imgResBGR, CV_Lab2BGR);
			 //cv::cvtColor(imgResLABAddLDiff, imgResBGR, CV_Lab2BGR);
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
			 
			 cv::Mat imgGaussian;
			 cv::Mat imgMeanShift;
			 cv::Mat imgMeanShiftGrayscal;
			 cv::Mat imgMeanShiftRes;
			 cv::Mat imgThresholdFixed;
 
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
			 double thresh = avg - stdDev/3.0;
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

			 cv::cvtColor(imgThresholdFixed, imgShadowMask, CV_GRAY2BGR);

//			 shadowMask = new UCHAR[size];
//			 CopyMatToArray(imgShadowMask, shadowMask);
//
//			 saveMaskBMP();
//			 ShowShadowMaskBmp();

			 ShowImgShadowMask();
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

			 //imgBGRRes = imgBGR.clone();

			 //Shadow edge detection
			 cv::Mat imgShadowMaskGRAY;
			 cv::Mat imgEdge;
			 cv::Mat imgEdgeDilated;
			 cv::Mat imgEdgeDilated5;
			 cv::Mat imgEdgeDilated7;
			 cv::Mat imgEdgeDilatedForInpaint;
			 cv::Mat imgEdgeGaussianWhole;
			 cv::Mat imgEdgeGaussianEdgeOnly;
			 
			 cv::Mat imgMedianEdgeOnly;
			 cv::Mat imgMedianEdgeOnly2;

			 cv::cvtColor(imgShadowMask, imgShadowMaskGRAY, CV_BGR2GRAY);
			 
			 cv::Canny(imgShadowMaskGRAY, imgEdge, 50, 150, 3);

			 cv::Mat elementDil5 = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(5, 5));
			 cv::Mat elementDil7 = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(7, 7));

			 

			 //Load inpaint params from UI
			 System::String^ inpaintDilationKernelSizeStr = textBoxEdgesProcDilationKernelSize->Text;
			 
			 int inpaintDilationKernelSize = System::String::IsNullOrWhiteSpace(inpaintDilationKernelSizeStr) ? INPAINT_DILATION_KERNEL_SIZE : System::Convert::ToInt32(inpaintDilationKernelSizeStr);
			 System::String^ inpaintRadiusStr = textBoxEdgesProcInpaintRadius->Text; 
			 
			 double inpaintRadius = System::String::IsNullOrWhiteSpace(inpaintRadiusStr) ? INPAINT_RADIUS : System::Convert::ToDouble(inpaintRadiusStr);

			 cv::Mat elementDilationForInpaint = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(inpaintDilationKernelSize, inpaintDilationKernelSize));
			 cv::dilate(imgEdge, imgEdgeDilated, elementDil5);
			 cv::dilate(imgEdge, imgEdgeDilated5, elementDil5);
			 cv::dilate(imgEdge, imgEdgeDilated7, elementDil7);
			 cv::dilate(imgEdge, imgEdgeDilatedForInpaint, elementDilationForInpaint);

			 imgEdgeGaussianEdgeOnly = imgBGRRes.clone();
			 cv::GaussianBlur(imgBGRRes, imgEdgeGaussianWhole, cv::Size(3, 3), 0);
			 imgEdgeGaussianWhole.copyTo(imgEdgeGaussianEdgeOnly, imgEdgeDilated);

			 cv::Mat imgMedianWhole3;
			 cv::Mat imgMedianWhole5;
			 imgMedianEdgeOnly = imgBGRRes.clone();
			 imgMedianEdgeOnly2 = imgBGRRes.clone();
			 cv::medianBlur(imgBGRRes, imgMedianWhole3, 3);
			 cv::medianBlur(imgBGRRes, imgMedianWhole5, 5);
			 imgMedianWhole3.copyTo(imgMedianEdgeOnly, imgEdgeDilated);
			 imgMedianWhole5.copyTo(imgMedianEdgeOnly2, imgEdgeDilated);
			 ///

			 

			 //Inpaint edge artifacts
			 cv::Mat imgBGRInpainted;
			 //cv::inpaint(imgBGRres, imgEdgeDilatedForInpaint, imgBGRInpainted, 7, CV_INPAINT_TELEA);//CV_INPAINT_NS
			 cv::inpaint(imgBGRRes, imgEdgeDilatedForInpaint, imgBGRInpainted, inpaintRadius, CV_INPAINT_TELEA);//CV_INPAINT_NS

			 cv::imshow("imgBGRres", imgBGRRes);
			 cv::imshow("imgBGRInpainted", imgBGRInpainted);

			 cv::imshow("imgEdgeGaussianEdgeOnly", imgEdgeGaussianEdgeOnly);

			 cv::imshow("imgMedianEdgeOnly", imgMedianEdgeOnly);
			 cv::imshow("imgMedianEdgeOnly2", imgMedianEdgeOnly2);
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

			 //cv::Mat imgBGR = cv::imread(myPath_char);
			 cv::Mat imgLAB;
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

			 cv::cvtColor(imgLAB, imgBGRRes, CV_Lab2BGR);

			 ShowImgBGRRes();
}

		 //GenerateRandomColor
private: cv::Scalar GenerateRandomColor()
{
			 //int n = clock(); //clock - Returns the processor time consumed by the program.
			 int n = cvGetTickCount(); //
			 cv::RNG rng(n);
			 return cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
}

//V4 (Start from one point - using grid) - 
private: void GoThroughAllAdjacentShadowPixelsRec(std::vector<cv::Point> currentContour, bool **passedThroughPixels)
{
			 cv::Mat imgShadowMaskCopy = imgShadowMask.clone();

			 //mark countour pixels as shadow to avoid errors in shadow pixels search
			 for (int k = 0; k < currentContour.size(); k++)
			 {
				 int j2 = currentContour[k].x;
				 int i2 = currentContour[k].y;

				 cv::Vec3b &pixel = imgShadowMaskCopy.at<cv::Vec3b>(i2, j2);
				 pixel.val[0] = 255;
				 pixel.val[1] = 255;
				 pixel.val[2] = 255;
			 }

			 //Take any shadow countour pixel as init value;
			 cv::Point startPixel = currentContour[0];
			 for (int k = 0; k < currentContour.size(); k++)
			 {
				 int j = currentContour[k].x;
				 int i = currentContour[k].y;
				 if (imgShadowMask.at<cv::Vec3b>(i, j).val[0] == 255)
				 {
					 startPixel = currentContour[k];
					 break;
				 }
			 }

			 int rows = imgShadowMaskCopy.rows;
			 int cols = imgShadowMaskCopy.cols;

			 int gridPixelsSize = imgShadowMaskCopy.rows * imgShadowMaskCopy.cols;
			 int newGridPixelsSize = gridPixelsSize;

			 int actualGridPixelsSize = 0;
			 int actualNewGridPixelsSize = 0;

			 cv::Point *gridPixels = new cv::Point[gridPixelsSize];
			 cv::Point *newGridPixels = new cv::Point[newGridPixelsSize];
			 bool **handledGridPixels = Create2DArray(rows, cols, false);

			 gridPixels[0] = startPixel;
			 actualGridPixelsSize += 1;

			 //main loop
			 for (int i = 0; true; i++)
			 {
				 for (int k = 0; k < actualGridPixelsSize; k++)
				 {
					 int j2 = gridPixels[k].x;
					 int i2 = gridPixels[k].y;

					 passedThroughPixels[i2][j2] = true;

					 //look for adjacent shadow pixels
					 int disctance = 1;

					 //Go up, down, left, right
					 //up
					 if (i2 - disctance >= 0 && imgShadowMaskCopy.at<cv::Vec3b>(i2 - disctance, j2).val[0] == 255)
					 {
						 passedThroughPixels[i2 - disctance][j2] = true;
						 if (handledGridPixels[i2 - disctance][j2] == false)
						 {
							 newGridPixels[actualNewGridPixelsSize] = cv::Point(j2, i2 - disctance);
							 handledGridPixels[i2 - disctance][j2] = true;
							 actualNewGridPixelsSize += 1;
						 }
						 
					 }
					 //down
					 if (i2 + disctance < imgShadowMaskCopy.rows && imgShadowMaskCopy.at<cv::Vec3b>(i2 + disctance, j2).val[0] == 255)
					 {
						 passedThroughPixels[i2 + disctance][j2] = true;
						 if (handledGridPixels[i2 + disctance][j2] == false)
						 {
							 newGridPixels[actualNewGridPixelsSize] = cv::Point(j2, i2 + disctance);
							 handledGridPixels[i2 + disctance][j2] = true;
							 actualNewGridPixelsSize += 1;
						 }
						 
					 }
					 //left
					 if (j2 - disctance >= 0 && imgShadowMaskCopy.at<cv::Vec3b>(i2, j2 - disctance).val[0] == 255)
					 {
						 passedThroughPixels[i2][j2 - disctance] = true;
						 if (handledGridPixels[i2][j2 - disctance] == false)
						 {
							 newGridPixels[actualNewGridPixelsSize] = cv::Point(j2 - disctance, i2);
							 handledGridPixels[i2][j2 - disctance] = true;
							 actualNewGridPixelsSize += 1;
						 }
						 
					 }
					 //rigth
					 if (j2 + disctance < imgShadowMaskCopy.cols && imgShadowMaskCopy.at<cv::Vec3b>(i2, j2 + disctance).val[0] == 255)
					 {
						 passedThroughPixels[i2][j2 + disctance] = true;
						 if (handledGridPixels[i2][j2 + disctance] == false)
						 {
							 newGridPixels[actualNewGridPixelsSize] = cv::Point(j2 + disctance, i2);
							 handledGridPixels[i2][j2 + disctance] = true;
							 actualNewGridPixelsSize += 1;
						 }
						 
					 }

				 }

				 delete gridPixels;
				 gridPixels = newGridPixels;
				 actualGridPixelsSize = actualNewGridPixelsSize;

				 actualNewGridPixelsSize = 0;
				 newGridPixels = new cv::Point[newGridPixelsSize];

				 //Reset2dArray(handledGridPixels,rows,cols,false);

				 if (actualGridPixelsSize == 0)
				 {
					 break;
				 }
			 }

}

private: System::Void buttonRemoveUsingConstant_Click(System::Object^  sender, System::EventArgs^  e) {

			 cv::Mat shadowMaskGRAY;
			 cv::cvtColor(imgShadowMask, shadowMaskGRAY, CV_BGR2GRAY);

			 cv::Mat imgEdge;
			 cv::Mat imgEdgeCopy;
			 cv::Mat imgEdgeD;

			 int aperture_size = 5;// — размер для оператора Собеля
			 cv::Canny(shadowMaskGRAY, imgEdge, 50, 150, aperture_size);

			 cv::Mat elementD = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(3,3));
			 cv::dilate(imgEdge, imgEdgeD, elementD);

			 cv::imshow("imgEdge", imgEdge);
			 //cv::imshow("imgEdgeD", imgEdgeD);
			 //imgEdge = imgEdgeD.clone();

#pragma region FIND CONTOURS USING findContours
			 //////FIND CONTOURS USING  cv::findContours

			 // extract contours of the canny image:
			 imgEdgeCopy = imgEdge.clone();
			 std::vector<std::vector<cv::Point> > contours; //Detected contours. Each contour is stored as a vector of points
			 std::vector<cv::Vec4i> hierarchy; //Optional output vector, containing information about the image topology. 
			 //int mode = CV_RETR_EXTERNAL; //retrieves only the extreme outer contours.
			 int mode = CV_RETR_TREE;//retrieves all of the contours and reconstructs a full hierarchy of nested contours
			 //int method = CV_CHAIN_APPROX_SIMPLE; //compresses horizontal, vertical, and diagonal segments and leaves only their end points
			 int method = CV_CHAIN_APPROX_NONE; //stores absolutely all the contour points
			 cv::findContours(imgEdgeCopy, contours, hierarchy, mode, method, cv::Point(0, 0));

			 // draw the contours to a copy of the input image:
			 cv::Mat outputContour ;
			 cv::cvtColor(imgEdge, outputContour, CV_GRAY2BGR);

			 int thickness = 1;
			 int lineType = 8;
			 int maxLevel = 0;
			 for (int i = 0; i< contours.size(); i++)
			 {
				 cv::Scalar color = GenerateRandomColor();
				 cv::drawContours(outputContour, contours, i, color, thickness, lineType, hierarchy, maxLevel);
			 }
			 cv::imshow("outputContour", outputContour);
			 //

			 //Sort countours by size descending
			 SortVectorOfVectorsDesc(contours);
			 //TODO: NEED TO SORT hierarchy TOO
			 //TODO: NEED TO SORT hierarchy TOO
			 //TODO: NEED TO SORT hierarchy TOO
			 //TODO: NEED TO SORT hierarchy TOO

			 //Delete small countours useing threshold
			 int MIN_COUNTOUR_THRESHLD = 30;
			 std::vector<int> indicesToRemove;
			 for (int i = 0; i < contours.size(); i++)
			 {
				 if (contours[i].size() < MIN_COUNTOUR_THRESHLD)
					 indicesToRemove.push_back(i);
			 }
			 //contours.erase(contours.begin());
			 contours.erase(ToggleIndices(contours, std::begin(indicesToRemove), std::end(indicesToRemove)), contours.end());

#pragma endregion

#pragma region FIND CONTOURS (MY REALISTION) - NOT COMPLETED

//			 ///FIND CONTOURS (MY REALISTION) - NOT COMPLETED
//			 //determine shadow regions lookig at edges 
//			 cv::Mat imgEdgeHandled = cv::Mat(imgEdge.rows, imgEdge.cols, CV_8U, cvScalar(0.)); //fil with 0
//			 std::vector<std::vector<int*>> regionsEgesPixels = std::vector<std::vector<int*>>();
//			 //std::vector<int*> edgeHadledPixels = std::vector<int*>();
//			 int determinedShadowRegions = 0;
//			 //std::vector<int*> determinedShadowRegionsPixels = std::vector<int*>();
//			 int maxIters = 1000000;
//			 for(int i = 0; i < imgEdge.rows; i++) {
//				 for (int j = 0; j < imgEdge.cols; j++) {
//
//					 uchar &edgePixel = imgEdge.at<uchar>(i, j);
//					 
//					 //skip handled
//					 if (imgEdgeHandled.at<uchar>(i, j) == 255)
//					 {
//						 continue;
//					 }
//
//					 if (edgePixel == 255)
//					 {
//						 //go by edge pixels path and save indexes
//						 int i2 = i;
//						 int j2 = j;
//						 bool goNext = true;
//
//						 determinedShadowRegions += 1;
//
//						 std::vector<int*> currentRegionEgePixels = std::vector<int*>();
//
//						 for (int k = 0; goNext == true;k++)
//						 {
//							 goNext = false;
//
//							 uchar &p = imgEdgeHandled.at<uchar>(i2, j2);
//							 p = 255;
//
//							 currentRegionEgePixels.push_back(new int[2] {i2, j2});
//
//							 if (k > maxIters)
//							 {
//								 throw new std::exception("Max iterations limit");
//								 return;
//							 }
//
//							 //look at all possible direction to determine where to go next
//							 int disctance = 1;
//							 int maxDisctance = 2;
//							 for (;true;)
//							 {
//								 //First look up, down, left, right
//								 if (i2 + disctance < imgEdge.rows && imgEdge.at<uchar>(i2 + disctance, j2) == 255 && imgEdgeHandled.at<uchar>(i2 + disctance, j2) != 255 && goNext == false)
//								 {
//									 goNext = true;
//									 i2 = i2 + disctance;
//									 //continue;
//								 }
//								 if (i2 - disctance >= 0 && imgEdge.at<uchar>(i2 - disctance, j2) == 255 && imgEdgeHandled.at<uchar>(i2 - disctance, j2) != 255 && goNext == false)
//								 {
//									 goNext = true;
//									 i2 = i2 - disctance;
//									 //continue;
//								 }
//								 if (j2 + disctance < imgEdge.cols && imgEdge.at<uchar>(i2, j2 + disctance) == 255 && imgEdgeHandled.at<uchar>(i2, j2 + disctance) != 255 && goNext == false)
//								 {
//									 goNext = true;
//									 j2 = j2 + disctance;
//									 //continue;
//								 }
//								 if (j2 - disctance >= 0 && imgEdge.at<uchar>(i2, j2 - disctance) == 255 && imgEdgeHandled.at<uchar>(i2, j2 - disctance) != 255 && goNext == false)
//								 {
//									 goNext = true;
//									 j2 = j2 - disctance;
//									 //continue;
//								 }
//
//								 //then top-left, top-right, etc
//								 if ((i2 - disctance >= 0 && j2 - disctance >= 0) && imgEdge.at<uchar>(i2 - disctance, j2 - disctance) == 255 && imgEdgeHandled.at<uchar>(i2 - disctance, j2 - disctance) != 255 && goNext == false)
//								 {
//									 goNext = true;
//									 i2 = i2 - disctance;
//									 j2 = j2 - disctance;
//									 //continue;
//								 }
//								 if ((i2 - disctance >= 0 && j2 + disctance < imgEdge.cols) && imgEdge.at<uchar>(i2 - disctance, j2 + disctance) == 255 && imgEdgeHandled.at<uchar>(i2 - disctance, j2 + disctance) != 255 && goNext == false)
//								 {
//									 goNext = true;
//									 i2 = i2 - disctance;
//									 j2 = j2 + disctance;
//									 //continue;
//								 }
//								 if ((i2 + disctance < imgEdge.rows && j2 - disctance >= 0) && imgEdge.at<uchar>(i2 + disctance, j2 - disctance) == 255 && imgEdgeHandled.at<uchar>(i2 + disctance, j2 - disctance) != 255 && goNext == false)
//								 {
//									 goNext = true;
//									 i2 = i2 + disctance;
//									 j2 = j2 - disctance;
//									 //continue;
//								 }
//								 if ((i2 + disctance < imgEdge.rows && j2 + disctance < imgEdge.cols) && imgEdge.at<uchar>(i2 + disctance, j2 + disctance) == 255 && imgEdgeHandled.at<uchar>(i2 + disctance, j2 + disctance) != 255 && goNext == false)
//								 {
//									 goNext = true;
//									 i2 = i2 + disctance;
//									 j2 = j2 + disctance;
//									 //continue;
//								 }
//
//								 if (goNext)
//								 {
//									 break;
//								 }
//								 else
//								 {
//									 if (disctance < maxDisctance)
//									 {
//										 disctance += 1;
//									 }
//									 else
//									 {
//										 break;
//									 }
//								 }
//							 }
//							 
//						 }
//
//						 regionsEgesPixels.push_back(currentRegionEgePixels);
//					 }
//
//				 }
//			 }
//
//			 //Draw contours
//			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//			 cv::imshow("imgEdgeHandled", imgEdgeHandled);
//			 cv::Mat imgRegionsEgesPixels = cv::Mat(imgEdge.rows, imgEdge.cols, CV_8UC3, cvScalar(0.));
//			  
//			 cv::vector<int> color(determinedShadowRegions);
//			 CvRNG rng = cvRNG(cvGetTickCount());
//
//			 for (int k = 0; k < determinedShadowRegions; k++)
//			 {
//				 color[k] = cvRandInt(&rng);
//			 }
//
//			 for (int k = 0; k < determinedShadowRegions; k++)
//			 {
//				 std::vector<int*> currentRegionEgePixels = regionsEgesPixels[k];
//				 for (int i = 0; i < currentRegionEgePixels.size(); i++)
//				 {
//					 int *indexes = currentRegionEgePixels[i];
//
//					 cv::Vec3b &pixel = imgRegionsEgesPixels.at<cv::Vec3b>(indexes[0], indexes[1]);
//
//					 pixel.val[0] = (color[k]) & 255;
//					 pixel.val[1] = (color[k] >> 8) & 255;
//					 pixel.val[2] = (color[k] >> 16) & 255;
//				 }
//			 }
//			 
//			 cv::imshow("imgRegionsEgesPixels", imgRegionsEgesPixels);
//			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma endregion

			int rows = imgBGR.rows;
			int cols = imgBGR.cols;
			bool **lightenedPixels = Create2DArray(rows, cols, false); //indicates pixels than already have lightened

	         //Iterate through all countrous
			 for (int contour_i = 0; contour_i < contours.size(); contour_i++)
			 //for (int contour_i = 0; contour_i < 1; contour_i++)
			 {
				 std::vector<cv::Point> currentContour = contours[contour_i];
				 int currentContourSize = currentContour.size();

#pragma region Find pixels adjacent to shadow border (for specific contour)
				 
				 std::vector<int*> border_adjacent_shadow_pixels_indexes = std::vector<int*>();
				 std::vector<int*> border_adjacent_non_shadow_pixels_indexes = std::vector<int*>();

//				 int distance_shadow = 20;
//				 int distance_non_shadow = 10;
				 int distance = 10;

//				 //Loop thorough image to find edge pixel and determine adjacent
//				 for (int i = 0; i < imgEdge.rows; i++) {
//					 for (int j = 0; j < imgEdge.cols; j++) {
//
//						 //uchar &pixel = imgEdge.at<uchar>(i, j);
//						 cv::Vec3b &pixel = imgBGR.at<cv::Vec3b>(i, j);
//						 cv::Vec3b &shadow_mask_pixel = imgShadowMask.at<cv::Vec3b>(i, j);
//
//						 //Loop through edge pixels
//						 if (imgEdge.rows && imgEdge.at<uchar>(i, j) != 255)
//						 {
//							 continue;
//						 }
//
//						 //					 if (shadow_mask_pixel.val[0] == 255)
//						 //					 {
//						 //						 distance = distance_shadow;
//						 //					 }
//						 //					 else{
//						 //						 distance = distance_non_shadow;
//						 //					 }
//
//						 if (i - distance >= 0)
//						 {
//							 if (imgShadowMask.at<cv::Vec3b>(i - distance, j).val[0] == 255)
//							 {
//								 border_adjacent_shadow_pixels_indexes.push_back(new int[2]{i - distance, j});
//							 }
//							 else{
//								 border_adjacent_non_shadow_pixels_indexes.push_back(new int[2]{i - distance, j});
//							 }
//						 }
//						 if (i + distance < imgEdge.rows)
//						 {
//							 if (imgShadowMask.at<cv::Vec3b>(i + distance, j).val[0] == 255)
//							 {
//								 border_adjacent_shadow_pixels_indexes.push_back(new int[2]{i + distance, j});
//							 }
//							 else{
//								 border_adjacent_non_shadow_pixels_indexes.push_back(new int[2]{i + distance, j});
//							 }
//						 }
//
//						 if (j - distance >= 0)
//						 {
//							 if (imgShadowMask.at<cv::Vec3b>(i, j - distance).val[0] == 255)
//							 {
//								 border_adjacent_shadow_pixels_indexes.push_back(new int[2]{i, j - distance});
//							 }
//							 else{
//								 border_adjacent_non_shadow_pixels_indexes.push_back(new int[2]{i, j - distance});
//							 }
//						 }
//						 if (j + distance < imgEdge.cols)
//						 {
//							 if (imgShadowMask.at<cv::Vec3b>(i, j + distance).val[0] == 255)
//							 {
//								 border_adjacent_shadow_pixels_indexes.push_back(new int[2]{i, j + distance});
//							 }
//							 else{
//								 border_adjacent_non_shadow_pixels_indexes.push_back(new int[2]{i, j + distance});
//							 }
//						 }
//					 }
//				 }

				 //Loop thorough countour pixels  and determine adjacent
				 for (int k = 0; k < currentContour.size(); k++)
				 {
					 int j = currentContour[k].x;
					 int i = currentContour[k].y;

					 if (i - distance >= 0)
					 {
						 if (imgShadowMask.at<cv::Vec3b>(i - distance, j).val[0] == 255)
						 {
							 border_adjacent_shadow_pixels_indexes.push_back(new int[2]{i - distance, j});
						 }
						 else{
							 border_adjacent_non_shadow_pixels_indexes.push_back(new int[2]{i - distance, j});
						 }
					 }
					 if (i + distance < imgEdge.rows)
					 {
						 if (imgShadowMask.at<cv::Vec3b>(i + distance, j).val[0] == 255)
						 {
							 border_adjacent_shadow_pixels_indexes.push_back(new int[2]{i + distance, j});
						 }
						 else{
							 border_adjacent_non_shadow_pixels_indexes.push_back(new int[2]{i + distance, j});
						 }
					 }

					 if (j - distance >= 0)
					 {
						 if (imgShadowMask.at<cv::Vec3b>(i, j - distance).val[0] == 255)
						 {
							 border_adjacent_shadow_pixels_indexes.push_back(new int[2]{i, j - distance});
						 }
						 else{
							 border_adjacent_non_shadow_pixels_indexes.push_back(new int[2]{i, j - distance});
						 }
					 }
					 if (j + distance < imgEdge.cols)
					 {
						 if (imgShadowMask.at<cv::Vec3b>(i, j + distance).val[0] == 255)
						 {
							 border_adjacent_shadow_pixels_indexes.push_back(new int[2]{i, j + distance});
						 }
						 else{
							 border_adjacent_non_shadow_pixels_indexes.push_back(new int[2]{i, j + distance});
						 }
					 }
				 }

				 //int MIN_ADJACENT_NON_SHADOW_PIXELS = 10;

				 if (border_adjacent_shadow_pixels_indexes.size() == 0 || border_adjacent_non_shadow_pixels_indexes.size() == 0)
					 continue;

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
#pragma endregion

#pragma region FINDING A CONSTANT
				 //
				 //FINDING A CONSTANT

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

				 double sigma = 0.005; //accuracy
				 int max_step = 100000; //max iterations

				 //hold all calculated constant values
				 std::vector<double> c_B_values;
				 std::vector<double> c_G_values;
				 std::vector<double> c_R_values;

				 //calsc f value; f = sum (Pi - Si*r)^2

				 //R
				 for (int i = 0; true; i++)
				 {
					 double f_a_R = 0;
					 double f_b_R = 0;

					 for (std::vector<int>::size_type r = 0; r != border_adjacent_shadow_pixels_indexes.size(); r++)
					 {
						 int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
						 int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];

						 cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
						 cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);

						 f_a_R += pow(P_pixel.val[2] - S_pixel.val[2] * a_R, 2);
						 f_b_R += pow(P_pixel.val[2] - S_pixel.val[2] * b_R, 2);
					 }

					 if (f_a_R < f_b_R)
					 {
						 b_R = (a_R + b_R) / 2.0;
					 }
					 else
					 {
						 a_R = (a_R + b_R) / 2.0;
					 }

					 c_R = (a_R + b_R) / 2;
					 c_R_values.push_back(c_R);

					 if ((b_R - a_R) <= sigma || i >= max_step)
					 {
						 
						 break;
					 }
				 }

				 //G
				 for (int i = 0; true; i++)
				 {
					 double f_a_G = 0;
					 double f_b_G = 0;

					 for (std::vector<int>::size_type r = 0; r != border_adjacent_shadow_pixels_indexes.size(); r++)
					 {
						 int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
						 int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];

						 cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
						 cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);

						 f_a_G += pow(P_pixel.val[1] - S_pixel.val[1] * a_G, 2);
						 f_b_G += pow(P_pixel.val[1] - S_pixel.val[1] * b_G, 2);
					 }

					 if (f_a_G < f_b_G)
					 {
						 b_G = (a_G + b_G) / 2.0;
					 }
					 else
					 {
						 a_G = (a_G + b_G) / 2.0;
					 }

					 c_G = (a_G + b_G) / 2;
					 c_G_values.push_back(c_G);

					 if ((((b_G - a_G) <= sigma || i >= max_step)))
					 {
						 
						 break;
					 }
				 }

				 //B
				 for (int i = 0; true; i++)
				 {
					 double f_a_B = 0;
					 double f_b_B = 0;

					 for (std::vector<int>::size_type r = 0; r != border_adjacent_shadow_pixels_indexes.size(); r++)
					 {
						 int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
						 int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];

						 cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
						 cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);

						 f_a_B += pow(P_pixel.val[0] - S_pixel.val[0] * a_B, 2);
						 f_b_B += pow(P_pixel.val[0] - S_pixel.val[0] * b_B, 2);
					 }

					 if (f_a_B < f_b_B)
					 {
						 b_B = (a_B + b_B) / 2.0;
					 }
					 else
					 {
						 a_B = (a_B + b_B) / 2.0;
					 }

					 c_B = (a_B + b_B) / 2;
					 c_B_values.push_back(c_B);

					 if (((b_B - a_B) <= sigma || i >= max_step))
					 {
						 //c_B = (a_B + b_B) / 2;
						 break;
					 }
				 }

				 //Choose constants according to condition: Rc > Gc > Bc
//				 if ((c_R > c_G) == false)
//				 {
//					 for (int z = c_G_values.size() - 1; z >= 0; z--)
//					 {
//						 if (c_G_values[z] < c_R)
//						 {
//							 c_G = c_G_values[z];
//							 break;
//						 }
//					 }
//				 }
//				 if ((c_G > c_B) == false)
//				 {
//					 for (int z = c_B_values.size() - 1; z >= 0; z--)
//					 {
//						 if (c_B_values[z] < c_G)
//						 {
//							 c_B = c_B_values[z];
//							 break;
//						 }
//					 }
//				 }

				
				 double c_res_B = c_B;
				 double c_res_G = c_G;
				 double c_res_R = c_R;

				 //			/////Very slow - just find sequencelly
				 //			c_B = 0;
				 //			c_G = 0;
				 //			c_R = 0;
				 //
				 //			double f_c_B_prev = 99999999999999;
				 //			double f_c_G_prev = 99999999999999;
				 //			double f_c_R_prev = 99999999999999;
				 //
				 //			for (double i = 0; i < 20; i += 0.001)
				 //			{
				 //				double f_c_B = 0;
				 //				double f_c_G = 0;
				 //				double f_c_R = 0;
				 //
				 //				for (std::vector<int>::size_type r = 1; r != border_adjacent_shadow_pixels_indexes.size(); r++)
				 //				{
				 //					int *Si_indexes = border_adjacent_shadow_pixels_indexes[r];
				 //					int *Pi_indexes = border_adjacent_non_shadow_pixels_indexes[r];
				 //
				 //					cv::Vec3b &S_pixel = imgBGR.at<cv::Vec3b>(Si_indexes[0], Si_indexes[1]);
				 //					cv::Vec3b &P_pixel = imgBGR.at<cv::Vec3b>(Pi_indexes[0], Pi_indexes[1]);
				 //
				 //					f_c_B += pow(P_pixel.val[0] - S_pixel.val[0] * i, 2);
				 //					f_c_G += pow(P_pixel.val[1] - S_pixel.val[1] * i, 2);
				 //					f_c_R += pow(P_pixel.val[2] - S_pixel.val[2] * i, 2);
				 //				}
				 //
				 //				if (f_c_B < f_c_B_prev)
				 //				{
				 //					f_c_B_prev = f_c_B;
				 //					c_B = i;
				 //				}
				 //				if (f_c_G < f_c_G_prev)
				 //				{
				 //					f_c_G_prev = f_c_G;
				 //					c_G = i;
				 //				}
				 //				if (f_c_R < f_c_R_prev)
				 //				{
				 //					f_c_R_prev = f_c_R;
				 //					c_R = i;
				 //				}
				 //
				 //				if (i >= max_step)
				 //				{
				 //					break;
				 //				}
				 //			}
				 //			double c_res_B = c_B;
				 //			double c_res_G = c_G;
				 //			double c_res_R = c_R;
				 //			//////////

#pragma endregion

#pragma region FIND SHADOW PIXELS FOR CURRENT COUNTOUR
				 				 
				 bool **passedThroughPixels = Create2DArray(rows, cols, false); //indicates pixelsForRelight
				 //bool **passedThroughEdgeAdjacentPixels = Create2DArray(rows, cols, false); //indicates pixels near shadow edge

				 int pixelsHandled = 0;

				 GoThroughAllAdjacentShadowPixelsRec(currentContour, passedThroughPixels);//V3

				 //visualize
				 cv::Mat visualRes = cv::Mat(imgBGR.rows, imgBGR.cols, CV_8UC3, cv::Scalar(0,0,0));

				 for (int i = 0; i < visualRes.rows; i++) { //draw all adjacent shadow pixels
					 for (int j = 0; j < visualRes.cols; j++) {

						 if (passedThroughPixels[i][j] == true)
						 {
							 cv::Vec3b &pixel = visualRes.at<cv::Vec3b>(i, j);
							 pixel.val[2] = 200;
						 }	 
					 }
				 }

//				 for (int k = 0; k < currentContour.size(); k++) //draw countour pixels only
//				 {
//					 int j = currentContour[k].x;
//					 int i = currentContour[k].y;
//					 cv::Vec3b &pixel = visualRes.at<cv::Vec3b>(i, j);
//					 pixel.val[2] = 200;
//				 }

				char integer_string[32];
				int integer = contour_i;
				sprintf(integer_string, "%d", integer);
				char other_string[64] = "visualRes"; // make sure you allocate enough space to append the other string
				strcat(other_string, integer_string); // other_string now contains "Integer: 1234"
				cv::imshow(other_string, visualRes);
#pragma endregion

#pragma region Find near shadow edge pixels (relight separatelly from shadow core pixels)

				//std::vector<int*> countour_adjacent_shadow_pixels_indexes = std::vector<int*>();
				bool **countour_adjacent_shadow_pixels_indexes = Create2DArray(rows,cols,false);
				
				int maxDistance = 2; //max distance from countour

				//Loop thorough countour pixels and determine adjacent. start from coutours
				for (int distance = 0; distance < maxDistance; distance++)
				{
					for (int k = 0; k < currentContour.size(); k++)
					{
						int j = currentContour[k].x;
						int i = currentContour[k].y;

						if (i - distance >= 0)
						{
							if (imgShadowMask.at<cv::Vec3b>(i - distance, j).val[0] == 255)
							{
								//countour_adjacent_shadow_pixels_indexes.push_back(new int[2]{i - distance, j});
								countour_adjacent_shadow_pixels_indexes[i - distance][j] = true;
							}
						}
						if (i + distance < rows)
						{
							if (imgShadowMask.at<cv::Vec3b>(i + distance, j).val[0] == 255)
							{
								//countour_adjacent_shadow_pixels_indexes.push_back(new int[2]{i + distance, j});
								countour_adjacent_shadow_pixels_indexes[i + distance][j] = true;
							}
						}

						if (j - distance >= 0)
						{
							if (imgShadowMask.at<cv::Vec3b>(i, j - distance).val[0] == 255)
							{
								//countour_adjacent_shadow_pixels_indexes.push_back(new int[2]{i, j - distance});
								countour_adjacent_shadow_pixels_indexes[i][j - distance] = true;
							}
						}
						if (j + distance < cols)
						{
							if (imgShadowMask.at<cv::Vec3b>(i, j + distance).val[0] == 255)
							{
								//countour_adjacent_shadow_pixels_indexes.push_back(new int[2]{i, j + distance});
								countour_adjacent_shadow_pixels_indexes[i][j + distance] = true;
							}
						}
					}
				}
#pragma endregion

#pragma region APPLYING THE CONSTANT
				 //
				 //
				 //APPLYING THE CONSTANT
				 //
				 //

				 //Apply to all pixels adajcent to border and all pixels adjacent to that pixels etc
				 for (int i = 0; i < imgEdge.rows; i++) {
					 for (int j = 0; j < imgEdge.cols; j++) {

						 //relight only pixels for cuurent countour
						 if (passedThroughPixels[i][j] != true)
						 {
							 continue;
						 }

						 //do not relight pixels that already lightened
						 if (lightenedPixels[i][j] == true)
						 {
							 continue;
						 }

						 //mark pixels as lightened to avoid double relight
						 lightenedPixels[i][j] = true;

						 cv::Vec3b &pixel = imgBGRRes.at<cv::Vec3b>(i, j);
						 cv::Vec3b &shadow_mask_pixel = imgShadowMask.at<cv::Vec3b>(i, j);

						 if (shadow_mask_pixel.val[0] == 255){

							 double B = pixel.val[0];
							 double G = pixel.val[1];
							 double R = pixel.val[2];

							 if (countour_adjacent_shadow_pixels_indexes[i][j] == true)
							 {
								 //if pixel is near to edge
								 double percent = 1;
								 B *= c_res_B*percent;
								 G *= c_res_G*percent;
								 R *= c_res_R*percent;
							 }
							 else
							 {
								 //if it is core pixel
								 B *= c_res_B;
								 G *= c_res_G;
								 R *= c_res_R;
							 }

//							 B *= c_res_B;
//							 G *= c_res_G;
//							 R *= c_res_R;

							 //						B = B*mnk_a_B + mnk_b_B;
							 //						G = G*mnk_a_G + mnk_b_G;
							 //						R = R*mnk_a_R + mnk_b_R;

							 //						//wall
							 //						B *= 1.705;
							 //						G *= 2.04;
							 //						R *= 2.59;

							 B = B > 255 ? 255 : (B < 0 ? 0 : B);
							 G = G > 255 ? 255 : (G < 0 ? 0 : G);
							 R = R > 255 ? 255 : (R < 0 ? 0 : R);

							 pixel.val[0] = B;
							 pixel.val[1] = G;
							 pixel.val[2] = R;
						 }
					 }
				 }

#pragma endregion

				 //Free memory
				 Delete2dArray(passedThroughPixels, rows);
				 Delete2dArray(countour_adjacent_shadow_pixels_indexes, rows);
			 }
			cv::imshow("const res", imgBGRRes);
			ShowImgBGRRes();

			
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

		 //Load default params for edges processing
private: void DisplayEdgesProcessingDefaultParams()
{
			 textBoxEdgesProcDilationKernelSize->Text = System::Convert::ToString(INPAINT_DILATION_KERNEL_SIZE);
			 textBoxEdgesProcInpaintRadius->Text = System::Convert::ToString(INPAINT_RADIUS);

			 textBoxEdgesProcGaussianFilterDilationKernelSize->Text = System::Convert::ToString(GAUSSIAN_FILTER_DILATION_KERNEL_SIZE);
			 textBoxEdgesProcMedianFilterDilationKernelSize->Text = System::Convert::ToString(MEDIAN_FILTER_DILATION_KERNEL_SIZE);

			 textBoxEdgesProcGaussianFilterKernelSize->Text = System::Convert::ToString(GAUSSIAN_FILTER_KERNEL_SIZE);
			 textBoxEdgesProcMedianFilterKernelSize->Text = System::Convert::ToString(MEDIAN_FILTER_KERNEL_SIZE);
}



		 //Destroy all windows
private: System::Void buttonDestroyAlllWindows_Click(System::Object^  sender, System::EventArgs^  e) {
			 cv::destroyAllWindows();
}
		 //DisplayEdgesProcessingDefaultParams
private: System::Void buttonEdgesProcessingDefault_Click(System::Object^  sender, System::EventArgs^  e) {
			 DisplayEdgesProcessingDefaultParams();
}
		 //InpaintEdges
private: System::Void buttonInpaintEdges_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 cv::Mat imgShadowMaskGRAY;
			 cv::Mat imgEdge;
			 cv::Mat imgEdgeDilatedForInpaint;
			 cv::Mat imgBGRInpainted;

			 cv::cvtColor(imgShadowMask, imgShadowMaskGRAY, CV_BGR2GRAY);

			 cv::Canny(imgShadowMaskGRAY, imgEdge, 50, 150, 3); //Shadow edge detection

			 //Load inpaint params from UI
			 System::String^ inpaintDilationKernelSizeStr = textBoxEdgesProcDilationKernelSize->Text;			 
			 System::String^ inpaintRadiusStr = textBoxEdgesProcInpaintRadius->Text;
			 int inpaintDilationKernelSize = System::String::IsNullOrWhiteSpace(inpaintDilationKernelSizeStr) ? INPAINT_DILATION_KERNEL_SIZE : System::Convert::ToInt32(inpaintDilationKernelSizeStr);
			 double inpaintRadius = System::String::IsNullOrWhiteSpace(inpaintRadiusStr) ? INPAINT_RADIUS : System::Convert::ToDouble(inpaintRadiusStr);

			 cv::Mat elementDilationForInpaint = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(inpaintDilationKernelSize, inpaintDilationKernelSize));
			 cv::dilate(imgEdge, imgEdgeDilatedForInpaint, elementDilationForInpaint);

			 //Inpaint edge artifacts
			 cv::inpaint(imgBGRRes, imgEdgeDilatedForInpaint, imgBGRInpainted, inpaintRadius, CV_INPAINT_TELEA);//CV_INPAINT_NS

			 cv::imshow("imgBGRInpainted", imgBGRInpainted);
}
		 //Smooth Using Gaussian Filter
private: System::Void buttonSmoothUsingGaussianFilter_Click(System::Object^  sender, System::EventArgs^  e) {

			 //Shadow edge detection
			 cv::Mat imgShadowMaskGRAY;
			 cv::Mat imgEdge;
			 cv::Mat imgEdgeDilated;
			 cv::Mat imgEdgeGaussianWhole;
			 //cv::Mat imgEdgeGaussianEdgeOnly = cv::Mat(imgBGRRes.rows, imgBGRRes.cols, CV_8UC3);
			 cv::Mat imgEdgeGaussianEdgeOnly = imgBGRRes.clone();

			 cv::cvtColor(imgShadowMask, imgShadowMaskGRAY, CV_BGR2GRAY);

			 cv::Canny(imgShadowMaskGRAY, imgEdge, 50, 150, 3);

			 //Load params from UI
			 System::String^ dilationKernelSizeStr = textBoxEdgesProcGaussianFilterDilationKernelSize->Text;
			 System::String^ kernelSizeStr = textBoxEdgesProcGaussianFilterKernelSize->Text; 
			 int diationKernelSize = System::String::IsNullOrWhiteSpace(dilationKernelSizeStr) ? GAUSSIAN_FILTER_DILATION_KERNEL_SIZE : System::Convert::ToInt32(dilationKernelSizeStr);
			 int kernelSize = System::String::IsNullOrWhiteSpace(kernelSizeStr) ? GAUSSIAN_FILTER_KERNEL_SIZE : System::Convert::ToInt32(kernelSizeStr);

			 cv::Mat elementDilation = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(diationKernelSize, diationKernelSize));
			 cv::dilate(imgEdge, imgEdgeDilated, elementDilation);

			 cv::GaussianBlur(imgBGRRes, imgEdgeGaussianWhole, cv::Size(kernelSize, kernelSize), 0);
			 imgEdgeGaussianWhole.copyTo(imgEdgeGaussianEdgeOnly, imgEdgeDilated);

			 cv::imshow("imgEdgeGaussianWhole", imgEdgeGaussianWhole);
			 cv::imshow("imgEdgeGaussianEdgeOnly", imgEdgeGaussianEdgeOnly);
}

		 //Smooth Using Median Filter
private: System::Void buttonSmoothUsingMedianFilter_Click(System::Object^  sender, System::EventArgs^  e) {

			 cv::Mat imgShadowMaskGRAY;
			 cv::Mat imgEdge;
			 cv::Mat imgEdgeDilated;
			 cv::Mat imgMedianEdgeOnly = imgBGRRes.clone();
			 cv::Mat imgMedianWhole;

			 cv::cvtColor(imgShadowMask, imgShadowMaskGRAY, CV_BGR2GRAY);

			 cv::Canny(imgShadowMaskGRAY, imgEdge, 50, 150, 3);

			 //Load params from UI
			 System::String^ dilationKernelSizeStr = textBoxEdgesProcMedianFilterDilationKernelSize->Text;
			 System::String^ kernelSizeStr = textBoxEdgesProcMedianFilterKernelSize->Text;
			 int diationKernelSize = System::String::IsNullOrWhiteSpace(dilationKernelSizeStr) ? MEDIAN_FILTER_DILATION_KERNEL_SIZE : System::Convert::ToInt32(dilationKernelSizeStr);
			 int kernelSize = System::String::IsNullOrWhiteSpace(kernelSizeStr) ? MEDIAN_FILTER_KERNEL_SIZE : System::Convert::ToInt32(kernelSizeStr);

			 cv::Mat elementDilation = getStructuringElement(cv::MORPH_RECT,
				 cv::Size(diationKernelSize, diationKernelSize));
			 cv::dilate(imgEdge, imgEdgeDilated, elementDilation);

			 cv::medianBlur(imgBGRRes, imgMedianWhole, kernelSize);
			 imgMedianWhole.copyTo(imgMedianEdgeOnly, imgEdgeDilated);

			 cv::imshow("imgMedianWhole", imgMedianWhole);
			 cv::imshow("imgMedianEdgeOnly", imgMedianEdgeOnly);
}

};



}