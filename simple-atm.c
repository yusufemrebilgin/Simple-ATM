#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<dos.h>
#include<windows.h>
void login(void);
void menu(void);
void withdrawal(void);
void deposit(void);
void transfer(void);
void transactions(void);
void changePIN(void);
void receiptP1(void);
void receiptP2(void);
void printCh219(int,int);
void pw(char[]);


char pin[5];

float balance = 13750.50;
float totalWithdrawal=0.0, totalDeposit=0.0, totalTransfer=0.0;

int main(){
	
	
	system("COLOR B");	
	printf("Insert your card to make transactions.\n\n");
	printf("Please wait while your transaction being processed.");
	Sleep(1500); 
	system("cls");
	
	login();
			
	return 0;
}

void login(){
	
	pw(pin);
	
	system("cls");
	
	int i, temp;
	char control[5];
	
	while(1){
		
		printCh219(14,0);
		printf(" WELCOME ");
		printCh219(14,0);
		
		printf("\n\n\n\xBA Please enter PIN: ");
		for(i=0 ; i<4 ; ){
			temp = getch();
			if( temp>='0' && temp<='9'){
				control[i++] = temp;
				printf("*");	
			}
			else if( temp==8 && i!=0 ){
				--i;
				printf("\b \b");
			}
		}
		control[i]='\0';
		
		if( strcmp(pin,control)==0 ){
			menu();
			break;
		}
		else{
			printf("\n\nWrong PIN entered.");
			Sleep(400); 
			system("cls");
		}
	}
	
}

void menu(){
	
	char ch;
	
	while(1){
		
		system("cls");
		printCh219(16,1);
		printf(" ATM ");
		printCh219(16,1);
		
		printf("\n\n\n\xBA Please choose a transaction:\n\n");
		printf("Withdrawal                      [1]\n");
		printf("Deposit                         [2]\n");
		printf("Transfer                        [3]\n");
		printf("PIN Change                      [4]\n");
		printf("Balance and Transactions        [5]\n\n\n");
		printf("\xBA Press [0] for exit.");
	
		ch = getch();
		if( ch == '1' )
			withdrawal();
		if( ch == '2' )
			deposit();
		if( ch == '3' )
			transfer();
		if( ch == '4' )
			changePIN();
		if( ch == '5' )
			transactions();
		if( ch == '0' ){
			system("cls");
			break;
		}
	}
	
}

void withdrawal(){
	
	float amount;
	
	system("cls");
	printf("\xBA Please enter amount: ");
	
	while(1){
		scanf("%f", &amount);
		if( amount<=balance && amount>0 )
			break;
		else{
			system("cls");
			printf("\xBA Insufficent balance. Please try again: ");
		}
		
	}
	printf("\nDo you want a receipt with your transaction?\n\n");
	printf("Yes (1)\nNo  (2)\n\n");
	balance -= amount;
	totalWithdrawal += amount;
	
	if( getch()=='1' ){
		receiptP1();
		printf("Withdrawal: %17.2lf",  amount);
		receiptP2();
	}
	
	
}

void deposit(){
	
	float amount;
	
	system("cls");
	printf("\xBA Please enter amount: ");
	scanf("%f", &amount);
	printf("\nStack all your cash and insert them directly into the ATM slot.\n\n");
	printf("..Scanning..");
	sleep(2);
	printf("\n\n\nDo you want a receipt with your transaction?\n\n");
	printf("Yes (1)\nNo (2)\n\n");
	
	balance += amount;
	totalDeposit += amount;
			
	if( getch()=='1' ){
		receiptP1();
		printf("Deposit: %20.2lf", amount);
		receiptP2();
	} 

}

void transfer(){
	
	int i, temp;
	float amount;
	char accountNumber[27] = "TR";
	
	system("cls");
	printf("Please enter the account number to be transferred:\n\n\xBA\xB3\xDB\xDB TR");
			
	for(i=2 ; i<26 ; ){
				
		temp = getch();
		if( temp>='0' && temp<='9'){
			accountNumber[i] = temp;
			printf("%c", accountNumber[i++]);
			if( i%4==0 )
				printf(" ");
		}
	}
	accountNumber[i] = '\0';	
	printf("\n\n");
		
	while(1){
				
		printf("Please enter amount:\n\n\xBA\xB3\xDB\xDB ");
		scanf("%f", &amount);
				
		if( amount>balance && amount>0 ){
			system("cls");
			printf("Insufficent balance. Please try again.");
			sleep(1); 
			system("cls");
		}
		else
			break;
	}
			
	printf("\n\n..Transferring..");
	sleep(2);
	printf("\n\n\n\xBA Transaction completed.\n\nDo you want a receipt?\n");
	printf("Yes (1)\nNo  (2)\n\n");
			
	totalTransfer += amount;
	balance -= amount;
			
	if( getch()=='1' ){
		receiptP1();
		printf("Transfer: %19.2lf", amount);
		receiptP2();
	}

}

void changePIN(){
	
	int i, temp;
	char control[5];
	
	while(1){
				
		system("cls");
		printCh219(12,1);
		printf(" PIN Change ");
		printCh219(12,1);
		printf("\n\n\xBA Enter your current PIN: ");
				
		for(i=0 ; i<4 ; ){
			temp = getch();
			if( temp>='0' && temp<='9' ){
				control[i++] = temp;
				printf("*");
			}
			else if( temp==8 && i!=0 ){
				--i;
				printf("\b \b");
			}
		}
		control[i]='\0';
				
		if( strcmp(control,pin)!=0 ){
					
			printf("\n\n\xBA Wrong PIN entered.");
			sleep(1); 
			system("cls");
			printf("Press [ENTER] to continue.\nPress [0] to return to the menu.");
			if( getch()=='0' )
				break;
		}
				
		else{
			printf("\n\n\xBA Enter your new PIN: ");
			for(i=0 ; i<4 ; ){
				temp = getch();
				if( temp>='0' && temp<='9' ){
					pin[i++] = temp;
					printf("*");
				}
				else if( temp==8 && i!=0 ){
					--i;
					printf("\b \b");
				}
			}
			pin[i]='\0';
			break;
		}
				
	}
	
}

void transactions(){
	
	receiptP1();
	printf("Withdrawal: %17.2lf\n", totalWithdrawal);
	printf("Deposit: %20.2lf\n", totalDeposit);
	printf("Transfer: %19.2lf\n", totalTransfer);
	receiptP2();
	
}

void pw(char pin[]){
	
	strcpy(pin,"2345");
}

void printCh219(int i, int ms){
	
	for( i ; i!=0 ; i--){
		printf("%c", 219);
		Sleep(ms);
	}	
}

void receiptP1(){
	
	system("cls");
	
	int i;
	
	time_t t;
	time(&t);
	
	printCh219(30,1);
	printf("\n\n\n%s", ctime(&t) );
	
	for(i=0 ; i<30 ; i++)
		printf("-");
		
	printf("\n\n");
}

void receiptP2(){
	
	int i;
	
	printf("\n\n\n");
	for(i=0;i<30;i++)
		printf("-");
			
	printf("\nCurrent Balance: %12.2f\n\n\n", balance);
	printCh219(30,1);
	getch();
}
