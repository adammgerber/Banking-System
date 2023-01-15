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
	struct user usr, usr1;
	FILE *fp;
	char filename[50], phone[50], pword[50];
	int opt, choice;
	char cont = 'y';
	float amount;

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
				printf("\n\tWelcome %s", usr.phone);
				while(cont == 'y'){
					system("clear");
					printf("\n\nPress 1 for balance inquuiry");
					printf("\nPress 2 to deposit an amount");
					printf("\nPress 3 for cash withdrawal");
					printf("\nPress 4 for online transfer");
					printf("\nPress 5 for password change");
					printf("\n\nYour choice:\t");
					scanf("%d", &choice);

					switch(choice){
						case 1:
							printf("\nYour current balance is Rs.%.2f", usr.balance);
							break;
						case 2:
							printf("\nEnter the amount:\t");
							scanf("%f", &amount);
							usr.balance += amount;
							fp = fopen(filename, "w");
							fwrite(&usr, sizeof(struct user),1,fp);
							if(&fwrite != NULL) printf("\nSuccessfully deposited.");
							fclose(fp);
							break;
						case 3:
							printf("\nEnter the amount:\t");
							scanf("%f", &amount);
							usr.balance -= amount;
							fp = fopen(filename, "w");
							fwrite(&usr, sizeof(struct user),1,fp);
							if(&fwrite != NULL) printf("\nYou have withdrawn Rs.%.2f. ", amount);
							fclose(fp);
							break;
						case 4:
							printf("\nPlease enter the phone number to transfer the balance: \t");
							scanf("%s", phone);
							printf("\nPlease enger the amount to transfer:\t");
							scanf("%f", &amount);
							if(amount > usr.balance) printf("\nInsufficient balance");
							else {
								strcpy(filename, phone);
								fp = fopen(strcat(filename, ".dat"), "r");
								if(fp == NULL){
									printf("\nPhone number not registered");
									return 0;
								}
								fread(&usr1, sizeof(struct user), 1,fp);
								fclose(fp);
								fp = fopen(filename, "w");
								usr1.balance += amount;
								fwrite(&usr1, sizeof(struct user),1,fp);

								fclose(fp);
								if(&fwrite != NULL){
									printf("You have successfully transfered Rs.%.2f to %s", amount, phone);
									strcpy(filename, usr.phone);
									fp = fopen(strcat(filename, ".dat"), "w");
									usr.balance -= amount;
									fwrite(&usr, sizeof(struct user), 1,fp);
									fclose(fp);
								}
							}
							break;

						case 5:
							printf("\nPlease enter your new password\t");
							scanf("%s", pword);
							fp = fopen(filename, "w");
							strcpy(usr.password, pword);
							fwrite(&usr, sizeof(struct user), 1,fp);
							if(&fwrite != NULL)
							printf("\nPassword successfully changed");
							break;
						default:
							printf("\nInvalid option");

					}

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

















