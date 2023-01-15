#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct user{
	char phone[50];
	char ac[50];
	char password[50];
	float balance;
};

int main(){
	struct user usr;
	FILE *fp;
	char filename[50], phone[50], pword[50];
	int opt;
	char cont = 'y';

	printf("\nWhat do you want to do?");
	printf("\n\n1. Register an account");
	printf("\n2. Login to an account");

	printf("\n\nYour choice:\n");
	scanf("%d", &opt);

	if(opt == 1){
		system("clear");
		printf("Enter your account number:\t");
		scanf("%s", usr.ac);
		printf("\nEnter your phone number:\t");
		scanf("%s", usr.phone);
		printf("\nEnter your new password:\t");
		scanf("%s",usr.password);
		usr.balance = 0;
		//store in file, use phone number of each user as file name
		strcpy(filename, usr.phone);
		fp = fopen(strcat(filename, ".dat"), "w");
		//first argument = address of struct, second = size of struct, third = number of instances stored in file
		fwrite(&usr, sizeof(struct user), 1, fp);
		// this is giving a warning because there will neve be a situation where fwrite == nil
		if(&fwrite != 0){
			printf("\n\nAccount successfully registered.");
		} else {
			printf("\n\nSomething went wrong please try again.");
		};
		fclose(fp);
	};

	if(opt == 2){
		system("clear");
		printf("\nPhone number:\t");
		scanf("%s", phone);
		printf("Password:\t");
		scanf("%s", pword);
		strcpy(filename, phone);
		fp = fopen(strcat(filename, ".dat"), "r");
		if(fp == NULL){
			printf("\nAccount number not registered.");
		} else {
			fread(&usr, sizeof(struct user), 1, fp);
			fclose(fp);
			if(!strcmp(pword, usr.password)){
				while(cont == 'y'){
					system("clear");
					printf("\nPress 1 to check balance");
					printf("\nPress 2 to deposit an amount");
					printf("\nPress 3 to withdraw");
					printf("\nPress 4 to transfer the balance");
					printf("\nPress 5 to change the password");

					printf("\nDo you want to continue the transaction [y/n]\t");
					scanf("%s", &cont);
				}
			} else {
				printf("\nInvalid password");
			}

		}
		

	}

	return 0;
}

















