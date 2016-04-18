
//private: void RGBtoYCbCr()
//{
//			 //convert to YCbCr;
//			 for (int i = 0; i<size; i += 3)
//			 {
//				 int R = buffer[i];//Blue
//				 int G = buffer[i + 1];//Green
//				 int B = buffer[i + 2];//Red
//
//
//				 /*
//				 int Y = (int)(0.299   * R + 0.587   * G + 0.114   * B);
//				 int Cb = (int)(128 -0.16874 * R - 0.33126 * G + 0.50000 * B);
//				 int Cr = (int)(128 + 0.50000 * R - 0.41869 * G - 0.08131 * B);
//				 */
//
//
//				 int Y = 0.299*R + 0.587*G + 0.114*B;
//				 //int Cb =  - 0.168736*R - 0.331264*G + 0.5*B + 128;
//				 int Cb = -0.169*R - 0.331*G + 0.5*B + 128;
//				 //int Cr = +0.5*R - 0.418688*G - 0.081312*B + 128;
//				 int Cr = +0.5*R - 0.419*G - 0.081*B + 128;
//
//
//				 /*
//				 int Y = round(0.299    *R + 0.587  *G + 0.114  *B);
//				 int Cb = round(-0.1687   *R - 0.3313 *G + 0.5    *B) + 128;
//				 int Cr = round(0.5      *R - 0.4187 *G - 0.0813 *B) + 128;
//				 */
//
//
//				 if (Y>255) Y = 255;
//				 else if (Y<0) Y = 0;
//				 if (Cb>255) Cb = 255;
//				 else if (Cb<0) Cb = 0;
//				 if (Cr>255) Cr = 255;
//				 else if (Cr<0) Cr = 0;
//
//
//				 buffer[i] = Y;//Blue
//				 buffer[i + 1] = Cb;//Green
//				 buffer[i + 2] = Cr;//Red
//			 }
//}
//
//
//private: void YCbCrtoRGB()
//{
//			 //Converting YCbCr to RGB 
//			 for (int i = 0; i < size; i += 3)
//			 {
//				 int Y = buffer[i];
//				 int Cb = buffer[i + 1];
//				 int Cr = buffer[i + 2];
//
//
//				 //int R = (int)((double)Y + 1.402 * (double)(Cr - 128));
//				 //int G = (int)((double)Y - 0.34414 * (double)(Cb - 128) - 0.71414 * (double)(Cr - 128));
//				 //int B = (int)((double)Y + 1.772 * (double)(Cb - 128));
//
//				 ///int R = Y + 1.402*(Cr - 128);
//				 //int G = Y - 0.34414*(Cb - 128) - 0.71414*(Cr - 128);
//				 //int B = Y + 1.772*(Cb - 128);
//
//				 int R = Y + 1.4*(Cr - 128);
//				 int G = Y - 0.343*(Cb - 128) - 0.711*(Cr - 128);
//				 int B = Y + 1.765*(Cb - 128);
//
//
//				 if (R > 255) R = 255;
//				 else if (R<0) R = 0;
//				 if (G>255) G = 255;
//				 else if (G<0) G = 0;
//				 if (B>255) B = 255;
//				 else if (B < 0) B = 0;
//
//
//				 buffer[i] = R;
//				 buffer[i + 1] = G;
//				 buffer[i + 2] = B;
//			 }
//}
//
//private: double* RGBtoXYZ(UCHAR* bufferRGB)
//{
//			 double *bufferXYZ = new double[size];
//
//			 for (int i = 0; i < size; i += 3)
//			 {
//				 int R = bufferRGB[i];
//				 int G = bufferRGB[i + 1];
//				 int B = bufferRGB[i + 2];
//
//				 double var_R = (double)R / (double)255.0;
//				 double var_G = (double)G / (double)255.0;
//				 double var_B = (double)B / (double)255.0;
//
//				 if (var_R > 0.04045)
//					 //var_R = ((var_R + 0.055) / 1.055) ^ 2.4;
//					 var_R = pow((double)(((var_R + 0.055) / 1.055)), (double)2.4);
//				 else
//					 var_R = var_R / 12.92;
//
//				 if (var_G > 0.04045)
//					 //var_G = ((var_G + 0.055) / 1.055) ^ 2.4;
//					 var_G = pow((double)(((var_G + 0.055) / 1.055)), (double)(2.4));
//				 else
//					 var_G = var_G / 12.92;
//
//				 if (var_B > 0.04045)
//					 //var_B = ((var_B + 0.055) / 1.055) ^ 2.4;
//					 var_B = pow((double)(((var_B + 0.055) / 1.055)), (double)(2.4));
//				 else
//					 var_B = var_B / 12.92;
//
//				 var_R = var_R * 100;
//				 var_G = var_G * 100;
//				 var_B = var_B * 100;
//
//				 //Observer. = 2°, Illuminant = D65
//				 double X = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
//				 double Y = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
//				 double Z = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;
//
//				 bufferXYZ[i] = X;
//				 bufferXYZ[i + 1] = Y;
//				 bufferXYZ[i + 2] = Z;
//			 }
//
//			 return bufferXYZ;
//}
//
//private: double* XYZtoCIELAB(double* bufferXYZ)
//{
//			 double *bufferLAB = new double[size];
//
//			 for (int i = 0; i < size; i += 3)
//			 {
//				 int X = bufferXYZ[i];
//				 int Y = bufferXYZ[i + 1];
//				 int Z = bufferXYZ[i + 2];
//
//				 double ref_X = 95.047;
//				 double ref_Y = 100.000;
//				 double ref_Z = 108.883;
//
//				 double var_X = (double)X / (double)ref_X;          //ref_X =  95.047   Observer= 2°, Illuminant= D65
//				 double var_Y = (double)Y / (double)ref_Y;          //ref_Y = 100.000
//				 double var_Z = (double)Z / (double)ref_Z;          //ref_Z = 108.883
//
//				 if (var_X > 0.008856)
//					 //var_X = var_X ^ (1 / 3);
//					 var_X = pow((double)(var_X), (double)(1.0 / 3.0));
//				 else
//					 var_X = (7.787 * var_X) + (16.0 / 116.0);
//
//				 if (var_Y > 0.008856)
//					 //var_Y = var_Y ^ (1 / 3);
//					 var_Y = pow((double)(var_Y), (double)(1.0 / 3.0));
//				 else
//					 var_Y = (7.787 * var_Y) + (16.0 / 116.0);
//
//				 if (var_Z > 0.008856)
//					 //var_Z = var_Z ^ (1 / 3);
//					 var_Z = pow((double)(var_Z), (double)(1.0 / 3.0));
//				 else
//					 var_Z = (7.787 * var_Z) + (16.0 / 116.0);
//
//				 double CIE_L = (116 * var_Y) - 16;
//				 double CIE_a = 500 * (var_X - var_Y);
//				 double CIE_b = 200 * (var_Y - var_Z);
//
//				 bufferLAB[i] = CIE_L;
//				 bufferLAB[i + 1] = CIE_a;
//				 bufferLAB[i + 2] = CIE_b;
//			 }
//
//			 return bufferLAB;
//}
