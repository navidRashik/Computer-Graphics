#include <iostream>

using namespace std;
int **createMatrix(int rows,int columns)
{
    int **Matrix;
    Matrix=new int*[rows];
    for(int i=0;i<rows;i++)
	{
		Matrix[i]=new int[columns];//the ith array is initialized


		for(int j=0;j<columns;j++)		//the i,jth element is defined
		{
			//cout<<"Enter element in row "<<(i+1)<<" and column "<<(j+1)<<": ";
			cin>>Matrix[i][j];
		}
	}
	return Matrix;
}

int **multiMatrix(int **matrix1,int **matrix2,int r1,int c1,int r2,int c2)
{
    int **mult;
    mult=new int*[r1];
    for(int i = 0; i < r1; ++i)
	{
        mult[i]=new int[c2];//the ith array is initialized
        for(int j = 0; j < c2; ++j)
        {
            mult[i][j]=0;
            for(int k = 0; k < c1; ++k)
            {
                mult[i][j]+= matrix1[i][k] * matrix2[k][j];
            }
        }
	}
	return mult;
}
void matdel(int **matrix, int rows)
{
    for(int i=0;i<rows;i++)
		delete[] matrix[i];
	delete[] matrix;
    //c++ can delete up to 1 dimensional vectors
}

int main()
{
    int **mat1=createMatrix(4,4);
    int **mat2=createMatrix(4,1);

    int **multply=multiMatrix(mat1,mat2,4,4,4,1);
    cout<<"The matrix you have input is:\n";
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<1;j++)
			cout<<multply[i][j]<<"\t";	//tab between each element
		cout<<"\n";						//new row
	}
}

