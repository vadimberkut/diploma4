void CopyMatrixToMatrix(int **a, int **b, int h, int w)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			b[i][j] = a[i][j];
		}
	}
}

UCHAR get_array_min(UCHAR* array, int size)
{
			 UCHAR min = array[0];
			 for (int i = 1; i<size; i++)
			 {
				 if (array[i]<min)
					 min = array[i];
			 }

			 return min;
}

UCHAR get_array_max(UCHAR* array, int size)
{
				UCHAR max = array[0];
				for (int i = 1; i<size; i++)
				{
					if (array[i]>max)
						max = array[i];
				}

				return max;
}

//UCHAR
UCHAR** Create2DArray(int m, int n, UCHAR defaultVal)
{
	UCHAR** matrix = new  UCHAR* [m];

	for (int i = 0; i < m; i++)
	{
		matrix[i] = new UCHAR[n];

		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = defaultVal;
		}
	}

	return matrix;
}
UCHAR** CreateMatrix(int m, int n, UCHAR defaultVal)
{
	return Create2DArray(m, n, defaultVal);
}

//BOOL
bool** Create2DArray(int m, int n, bool defaultVal)
{
	bool** matrix = new  bool*[m];

	for (int i = 0; i < m; i++)
	{
		matrix[i] = new bool[n];

		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = defaultVal;
		}
	}

	return matrix;
}
bool** CreateMatrix(int m, int n, bool defaultVal)
{
	return Create2DArray(m, n, defaultVal);
}

//FREE MEMORY
void Delete2dArray(UCHAR** matrix, int m)
{
	for (int i = 0; i < m; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}
void Delete2dArray(bool** matrix, int m)
{
	for (int i = 0; i < m; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
}

//RESET ARRAy
void Reset2dArray(bool** matrix, int m, int n, bool val)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			matrix[i][j] = val;
		}
	}
}