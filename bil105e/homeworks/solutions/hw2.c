/***************************
Student Number : 150120251
Student Name : Cem Yusuf Aydoðdu
Course : BIL105E
CRN : 21819
Term : 2014 Spring
Homework : #2
***************************/


#include <stdio.h>
#define LENGTH 7

int main()
{
	char *items[LENGTH]={"Water","Cola","Fanta","Chocolate","Biscuit","Gum","Candy"};
	int prices[LENGTH]={55,80,100,120,95,40,60};
	
	printf("AVAILABLE ITEMS \n(Item# ItemName ItemPrice)\n");
	int i;
	for(i=0;i<LENGTH;i++)
	{
		float priceTL=(prices[i]/100.0);
		printf("%d. %s %5.2f TL\n",i+1,items[i],priceTL);
	}
	
	int select;
	printf("\nEnter selection: ");
	scanf("%d",&select);
	while(select<=0 || select>LENGTH)
	{
		printf(" Wrong selection");
		printf("\nEnter selection: ");
		scanf("%d",&select);
	} 
	
	
	printf("\nEnter coins: ");
    int deposit =0, coin, inv_count=0;
    char ch;
    while(scanf("%d%c", &coin, &ch)==2)
	{
        if(coin==1 || coin==5 || coin==10 || coin==25 || coin==50)
		{
			if(coin==1)
			{
				deposit += (coin*100);
			}
			else
			{
				deposit += coin;
			}
				
        } 
		else inv_count++;
		
        if(ch == '\n')
            break;

    }
    if (inv_count!=0) printf("invalid coin(s)");
    printf("\nAccepted deposit: %d Kr\n", deposit);
    
    int remaining = (deposit-prices[select-1]);
    if(remaining > 0)
	{
		printf("\n%s discarded: %d Kr",items[select-1],prices[select-1]);
		
		printf("\nRemaining: %d Kr (",remaining);
		
		int accepted_coins[5]={100,50,25,10,5};
		for(i=0;i<5;i++)
		{
			while(remaining>accepted_coins[i]) 
			{
				remaining = remaining - accepted_coins[i];
				if(i!=0) 
				{
					printf("%d Kr, ", accepted_coins[i]);
				}
				else
				{
					printf("1 TL, ");
				}
													
			}			
			
			if(remaining==accepted_coins[i])
			{
				if(i!=0) 
				{
					printf("%d Kr", accepted_coins[i]);
				}
				else
				{
					printf("1 TL");
				}
				break;
			}
			
		}
		
		printf(")\n");
	}
	else if(remaining==0) printf("No remaining");	
	
	else printf("\nInsufficient deposit");
    
	return 0;
}
