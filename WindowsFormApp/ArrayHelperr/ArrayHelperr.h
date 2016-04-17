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