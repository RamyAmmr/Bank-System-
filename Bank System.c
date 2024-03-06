#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "STD_TYPES.h"
#include "Bank_System.h"

typedef struct BankAccount
{
    u8 Fullname[100];
    u8 Address[100];
    u8 Password[20];
    u8 AccountStatus[100];
    u8 Age;
    u32 National_ID;
    u32 BankAccount_ID;
    u32 GuardianNational_ID;
    f64 Balance;
} BankAccount;

typedef struct
{
    u8 UserName[100];
    u8 Password[100];
    u8 AccountStatus[100];
    f64 Balance;
} Window;

Window *Entery;

BankAccount *account;

Window Admin =
    {
        .UserName = "Admin1",
        .Password = "Admin123",
        .AccountStatus = "Active",
        .Balance = 5000};

Window client =
    {
        .UserName = "Client1",
        .Password = "Client123",
        .AccountStatus = "Active",
        .Balance = 5000};

void createNewAccount(BankAccount **account)
{
    *account = (BankAccount *)malloc(sizeof(BankAccount));

    printf("Please Enter your Fullname: ");
    scanf(" %[^\n]%*c", (*account)->Fullname);

    printf("Please Enter your Full Address: ");
    scanf(" %[^\n]%*c", (*account)->Address);

    printf("Please Enter your Age: ");
    scanf("%d", &(*account)->Age);

    if ((*account)->Age < 21)
    {
        printf("Please Enter your Guardian National ID: ");
        scanf("%d", &(*account)->GuardianNational_ID);
    }
    else
    {
        printf("Please Enter your National ID: ");
        scanf("%d", &(*account)->National_ID);
    }

    srand(time(NULL));
    sprintf((*account)->Password, "%d", rand() % 1000000000);
    (*account)->BankAccount_ID = rand() % 100000000000;
    strcpy((*account)->AccountStatus, "Active");

    printf("\nGenerated Password: %s\n", (*account)->Password);
    printf("Generated Account ID: %llu\n", (*account)->BankAccount_ID);
}

void deleteAccount(BankAccount *account)
{
    free(account);
}

void clientAccount(Window *client)
{
    if (strcmp(client->AccountStatus, "Active") == 0)
    {
        u8 choice;
        printf("\n 1. Make Transaction");
        printf("\n 2. Change Password");
        printf("\n 3. Get Cash");
        printf("\n 4. Deposit in Account");
        printf("\n 5. Return to main Menu");
        printf("\n 6. Exit");
        printf("\n Enter your choice: ");
        scanf("%hhu", &choice);

        switch (choice)
        {
        case 1:
            clientTransactions(client);
            break;

        case 2:
            ChangePassword(client);
            break;

        case 3:
            clientCash(client);
            break;

        case 4:
            clientDeposit(client);
            break;

        case 5:
            exitSystem();
            break;

        default:
            printf("Invalid input. Please try again.\n");
            break;
        }
    }
    else
    {
        printf("Sorry Your Account is Restricted Please Call Us \n");
    }
}

void ChangePassword(Window *client)
{
    if (strcmp(client->AccountStatus, "Active") == 0)
    {
        u8 currentpassword[20];
        printf("Please Enter Your Current Password \n");
        scanf("%s", currentpassword);
        if (strcmp(currentpassword, client->Password) == 0)
        {
            printf("Please Enter Your New Password: ");
            scanf(" %[^\n]%*c", client->Password);
            printf("Password Changed Successfully.\nYour new password is now: %s \n", client->Password);
        }
        else
        {
            printf("Invalid Password Please Try Again\n");
        }
    }
    else
    {
        printf("Sorry Your Account is Restricted Please Call Us \n");
    }
}

void existingAccount(Window *Admin)
{
    if (strcmp(Admin->AccountStatus, "Active") == 0)
    {
        u8 choice;
        printf("\n 1. Make Transaction");
        printf("\n 2. Change Account Status");
        printf("\n 3. Get Cash");
        printf("\n 4. Deposit in Account");
        printf("\n 5. Return to main Menu");
        printf("\n 6. Exit");
        printf("\n Enter your choice: ");
        scanf("%hhu", &choice);

        switch (choice)
        {
        case 1:
            adminTransaction(Admin);
            break;

        case 2:
            changeAccountStatus(Admin);
            break;

        case 3:
            AdminCash(Admin);
            break;

        case 4:
            AdminDeposit(Admin);
            break;
        case 5:
            exitSystem();
            break;

        default:
            printf("Invalid input. Please try again.\n");
            break;
        }
    }
    else
    {
        printf("Sorry Your Account is Restricted Please Call Us \n");
    }
}

void changeAccountStatus(Window *Admin)
{
    if (strcmp(Admin->AccountStatus, "Active") == 0)
    {
        u8 choice;
        u8 choice1;
        printf("Please Enter 0 to Continue or anything else to break\n");
        scanf("%hhu", &choice);
        if (choice == 0)
        {
            printf("Do you want to change your account status? (1: Yes, 2: No)\n");
            scanf("%hhu", &choice1);
            if (choice1 == 1)
            {
                printf("Do you want to close or restrict the account? (1: Close, 2: Restrict)\n");
                scanf("%hhu", &choice1);
                if (choice1 == 1)
                {
                    strcpy(Admin->AccountStatus, "Closed");
                    printf("Your Account is now CLOSED\n");
                }
                else if (choice1 == 2)
                {
                    strcpy(Admin->AccountStatus, "Restricted");
                    printf("Your Account is now RESTRICTED\n");
                }
                else
                {
                    printf("Invalid INPUT. Please Try Again\n");
                }
            }
            else
            {
                printf("Invalid choice. Please try again later.\n");
            }
        }
        else
        {
            printf("Account status change cancelled.\n");
        }
    }
    else
    {
        printf("Sorry, Your Account is Restricted. Please Call Us.\n");
    }
}

void adminTransaction(Window *Admin)
{
    if (strcmp(Admin->AccountStatus, "Active") == 0)
    {
        f64 amount;
        printf("Enter the amount to Transact: ");
        scanf("%lf", &amount);
        if (Admin->Balance >= amount)
        {
            Admin->Balance -= amount;
            printf("Your Balance after Transaction= %f\n", Admin->Balance);
            printf("Withdrawal Successful!\n");
        }
        else
        {
            printf("Check Your Balance!\n");
        }
    }
    else
    {
        printf("Sorry, Your Account is Restricted. Please Call Us.\n");
    }
}

void clientTransactions(Window *client)
{
    if (strcmp(client->AccountStatus, "Active") == 0)
    {
        f64 amount;
        printf("Enter the amount to Transact: ");
        scanf("%lf", &amount);
        if (client->Balance >= amount)
        {
            client->Balance -= amount;
            printf("Your Balance after Transation= %lf \n", client->Balance);
            printf("Withdrawal Successful!\n");
        }
        else
        {
            printf("Check Your balance!\n");
        }
    }
    else
    {
        printf("Sorry Your Account is Restricted Please Call Us \n");
    }
}

void AdminCash(Window *Admin)
{
    if (strcmp(Admin->AccountStatus, "Active") == 0)
    {
        f64 amount;
        printf("Enter the amount to withdraw: ");
        scanf("%lf", &amount);

        if (Admin->Balance >= amount)
        {
            Admin->Balance -= amount;
            printf("Your Balance after Withdrow= %lf ", Admin->Balance);
            printf("Withdrawal Successful!\n");
        }
        else
        {
            printf("Check Your balance!\n");
        }
    }
    else
    {
        printf("Sorry Your Account is Restricted Please Call Us \n");
    }
}

void clientCash(Window *client)
{
    if (strcmp(client->AccountStatus, "Active") == 0)
    {
        f64 amount;
        printf("Enter the amount to withdraw: ");
        scanf("%lf", &amount);

        if (client->Balance >= amount)
        {
            client->Balance -= amount;
            printf("Your Balance after Withdrow= %lf ", client->Balance);
            printf("Withdrawal Successful!\n");
        }
        else
        {
            printf("Check Your balance!\n");
        }
    }
    else
    {
        printf("Sorry Your Account is Restricted Please Call Us \n");
    }
}

void getCash(Window *client)
{
    if (strcmp(client->AccountStatus, "Active") == 0)
    {
        f64 amount;
        printf("Enter the amount to withdraw: ");
        scanf("%lf", &amount);

        if (client->Balance >= amount)
        {
            client->Balance -= amount;
            printf("Your Balance after Withdrow= %lf ", client->Balance);
            printf("Withdrawal Successful!\n");
        }
        else
        {
            printf("Check Your balance!\n");
        }
    }
    else
    {
        printf("Sorry Your Account is Restricted Please Call Us \n");
    }
}

void AdminDeposit(Window *Admin)
{
    if (strcmp(Admin->AccountStatus, "Active") == 0)
    {
        f64 amount;
        printf("Enter the amount to deposit: ");
        scanf("%lf", &amount);
        Admin->Balance += amount;
        printf("Your Balance is= %lf ", Admin->Balance);
        printf("Deposit Successful!\n");
    }
    else
    {
        printf("Sorry Your Account is Restricted Please Call Us \n");
    }
}

void clientDeposit(Window *client)
{
    if (strcmp(client->AccountStatus, "Active") == 0)
    {
        f64 amount;
        printf("Enter the amount to deposit: ");
        scanf("%lf", &amount);
        client->Balance += amount;
        printf("Your Balance is= %lf ", client->Balance);
        printf("Deposit Successful!\n");
    }
    else
    {
        printf("Sorry Your Account is Restricted Please Call Us \n");
    }
}

u32 exitSystem()
{
    printf("Exiting System...\n");
    return 0;
}

u32 main()
{
    u8 choice;
    u8 choice1;
    u8 Continue = 0;
    while (Continue == 0) 
    {
    Entery = (Window *)malloc(sizeof(Window));
    printf("Welcome to IMT Bank System\n");
    printf("\n 1. Admin");
    printf("\n 2. Client");
    printf("\n 3. Exit");
    printf("\n Enter your choice: ");
    scanf("%hhu", &choice);

    switch (choice)

    {
    case 1:
        printf("Admin Login\n");
        printf("Admin UserName: ");
        scanf(" %[^\n]%*c", Entery->UserName);
        printf("Admin Password: ");
        scanf(" %[^\n]%*c", Entery->Password);
        if ((strcmp(Entery->UserName, Admin.UserName) == 0) && (strcmp(Entery->Password, Admin.Password) == 0))
        {
            printf("Admin Login Successful!\n");
            printf("\n 1. Create New Account");
            printf("\n 2. Existing Account");
            printf("\n Enter your choice: ");
            scanf("%hhu", &choice1);
            switch (choice1)
            {
            case 1:
                account = (BankAccount *)malloc(sizeof(BankAccount));
                createNewAccount(&account);

                break;
            case 2:
                existingAccount(&Admin);
                break;
            default:
                printf("invaild INPUT Please try again \n");
                break;
            }
            break;
        }
        else
        {
            printf("invaild INPUT Please try again \n");
        }
        break;
    case 2:

        printf("client Login\n");
        printf("client UserName: ");
        scanf(" %[^\n]%*c", Entery->UserName);
        printf("client Password: ");
        scanf(" %[^\n]%*c", Entery->Password);
        if ((strcmp(Entery->UserName, client.UserName) == 0) && (strcmp(Entery->Password, client.Password) == 0))
        {
            printf("Client Login Successful!\n");
            clientAccount(&client);
            break;
        }
        else
        {
            printf("Invalid Client Login. Please Try Again!\n");
            break;
        }
        break;

    case 3:
        exitSystem();
        break;

    default:
        printf("Invalid input. Please try again.\n");
        break;
    }
   		deleteAccount(account);
		printf("Please Enter 0 To Continue Or Any Other Letter To EXIT \n");
        scanf("%hhd", &Continue);
    }
}
