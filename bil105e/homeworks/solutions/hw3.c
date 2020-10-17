/***************************
Student Number : 150120251
Student Name : Cem Yusuf Aydoðdu
Course : BIL105E
CRN : 21819
Term : 2014 Spring
Homework : #3
***************************/

#include <stdio.h>
#include <stdlib.h>
#define X_LIM 60
#define Y_LIM 30

int matrix[X_LIM+1][Y_LIM+1]={0};
unsigned int xMax=0,yMax=0,xMin=X_LIM;		//for drawing limits (yMin is always 0)


/***************************************************************** 
* Purpose: Assign value '1' to coordinates inside shapes * 
* Input parameter : Start, height, width from text file * 
* Output parameter: - *  
*****************************************************************/ 
void modify_Matrix(int start, int h, int w)
{
    size_t i,j;

    for(i=start+1;i<=start+w;i++)
    {
        for(j=1;j<=h;j++)
        {
            matrix[i][j]=1;
        }
    }
}


/***************************************************************** 
* Purpose: Write corner points to file and also displays at screen  * 
* Input parameter : Coordinates * 
* Output parameter: - *  
*****************************************************************/ 
void output_Matrix(int x,int y)
{
    FILE *ptr=fopen("outline.txt","a+");
    
    if(ptr!=NULL)
    {
    
    	fprintf(ptr,"(%d,%d) ",x,y);
    	printf("(%d,%d) ",x,y);
    	fclose(ptr);
	}
    else
    {
    	printf("(%d,%d) could not written to file. Press 0 to exit program, 1 to continue: ",x,y);
    	if(scanf("%d")==0)
    	{
    		exit(0);
    	}
    	
    }

}


/***************************************************************** 
* Purpose: Read start, height, width from file and call modify function * 
* Input parameter : - * 
* Output parameter: 1 or 0 to represent true-false *  
*****************************************************************/ 
int readFile()
{
	FILE *f= fopen("buildings.txt","r");

	if (f!=NULL)
	{
		int start,h,w;

		 while (fscanf(f,"%d %d %d",&start,&h,&w)==3)
		 {
            if((start+w)>=X_LIM || h >= Y_LIM)
            {
                printf("\n Please change defined limits for x,y values \n");
                return 0;
            }

            modify_Matrix(start,h+1,w+1);			//zeroth row and column are fixed to zero

            if((start+w)>xMax) xMax=start+w;
            if(start<xMin) xMin=start;
            if(h>yMax) yMax=h;
		 }
        fclose(f);
	  	return 1;
	}
	else
	{
	     printf("\nFile Error\n");
	     return 0;
    }


}


/***************************************************************** 
* Purpose: Find corner points and send their coordinates to function output_Matrix *
* Input parameter : Coordinates * 
* Output parameter: - *  
*****************************************************************/ 
void nodeCheck(int x,int y)
{
    int i,j;
    int count_1=0;

    for(i=-1;i<=1;i++)
    {
        for(j=-1;j<=1;j++)
        {
            if(matrix[x+i][y+j]==1) count_1++;
        }
    }

    if((count_1%4)==0 && count_1!=0 && matrix[x][y]==1)
    {
        output_Matrix(x-1,y-1);
    }
}


/***************************************************************** 
* Purpose: Draw the complex shape (arbitrary) * 
* Input parameter : - * 
* Output parameter: - *  
*****************************************************************/ 
void draw_Matrix()
{
    size_t i,j;
	FILE *ptr=fopen("hw3_draw.txt","w");
	printf("\n\n");

	if(ptr!=NULL)
	{
	  	for(i=yMax+5;i>=1;i--)
    	{
        	for(j=1;j<=xMax+5;j++)
        	{
	            fprintf(ptr,"%d",matrix[j][i]);
	            printf("%d",matrix[j][i]);
	        }

	    fprintf(ptr,"\n");
	    printf("\n");
	    }
	    fclose(ptr);
	}
    else
    {
    	printf("Drawing failed");
    }
        
}


int main()
{
    size_t t,z;
    
    if(readFile()!=0)
    {
        for(t=xMin+1;t<=xMax+1;t++)
        {
            for(z=1;z<=yMax+1;z++)
            {
                nodeCheck(t,z);
            }
        }
        draw_Matrix();
    }

        return 0;
}
