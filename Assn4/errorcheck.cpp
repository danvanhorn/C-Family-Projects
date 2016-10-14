/*********************************************************************
** Program Filename: errorcheck.cpp
** Author: Dan Van Horn
** Date: 05/02/2016
** Description: Some useful functions for error checking that I'm starting to build
*********************************************************************/
#include "./errorcheck.h"


int str_len(char* array)
{
   int i=0;
   while(array[i]!='\0')
   {
      i++;
   }
   return i;
} 



bool is_num(char* arr)
{   
	for(int i = 0; i < str_len(arr) ; i++)
	{          
		if (!(arr[i]>='0' && arr[i]<='9'))
		{  
    		return false; 
    	}                      
	}
	return true;                             
}


bool is_1_2(char *arr)
{
	if(str_len(arr) == 1)
	{
		for (int i = 0; i < str_len(arr); i++)
		{
			if (!(arr[i]>='1' && arr[i]<='2'))
			{  
	    		return false; 
	    	} 
		}
		return true;
	}else
	{
		return false;
	}
}



bool is_1_3(char *arr)
{
	if (str_len(arr) == 1)
	{
		for (int i = 0; i < str_len(arr); i++)
			{
				if (!(arr[i]>='1' && arr[i]<='3'))
				{  
		    		return false; 
		    	} 
			}
			return true;
	}else
	{
		return false;
	}
}


bool is_1_4(char *arr)
{
	if (str_len(arr) == 1)
	{
		for (int i = 0; i < str_len(arr); i++)
		{
			if (!(arr[i]>='1' && arr[i]<='4'))
			{  
	    		return false; 
	    	} 
		}
		return true;
	}else
	{
		return false;
	}
}
