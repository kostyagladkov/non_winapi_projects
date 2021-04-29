#include <iostream>
#include <cstring>
#include <conio.h>

#define ENTER 13
#define TAB 9
#define BKSP 8

#define SIZE 20
#define PSWD_SIZE 16

using namespace std;

struct User{
    char username[SIZE];
    char password[PSWD_SIZE];
    int block;
};

int choose_privelege();

void admin_login();

int user_login();

void structure_printer(struct User *users, int amount);

void password_changer(struct User *users, int index);

void block_status_changer(struct User *users, int index);

int main()
{
    int choice = choose_privelege();

    if (choice == 1){
        admin_login();

        FILE *fx;
        fx = fopen("C:\\Users\\zed11\\users.txt", "r+");

        int count = 0;
        char c;

        for (c = getc(fx); c != EOF; c = getc(fx)){
            if (c == '\n') {
                count = count + 1;
            }
        }

        fclose(fx);

        FILE *fp;
        fp = fopen("C:\\Users\\zed11\\users.txt", "r+");

        int amount_structs = count / 3;
        struct User test_users[amount_structs];

        for (int i = 0; i < amount_structs; i++) {
            fscanf(fp, "%s\n", test_users[i].username);
            fscanf(fp, "%s\n", test_users[i].password);
            fscanf(fp, "%d\n", &test_users[i].block);
        }

        fclose(fp);

        for(;;){
            int j;

            cout << "\n\n\nYou are in admin mode so you can do the following:";
            cout << "\n1) Change someones password\n"
                    "2) Block a user\n"
                    "3) List all users\n"
                    "4) Change YOUR password\n"
                    "5) Add new user\n"
                    "6) Exit\n\n"
                    "Your choice: ";
            cin >> j;

            if (j == 1){
                int number;
                cout << "\nEnter the number of person whose password you want to change: ";
                cin >> number;
                number-=1;
                password_changer(test_users, number);
                FILE *fp;
                fp = fopen("C:\\Users\\zed11\\users.txt", "w");

                for (int i = 0; i < amount_structs; i++){
                    fprintf(fp, "%s\n%s\n%d\n", test_users[i].username, test_users[i].password, test_users[i].block);
                }
                fclose(fp);
            }
            else if (j == 2){
                cout << "\nTo continue you have to re-login\n";
                admin_login();
                int number;
                cout << "\nEnter the number of person who you want to block: ";
                cin >> number;
                number-=1;

                block_status_changer(test_users, number);

                FILE *fp;
                fp = fopen("C:\\Users\\zed11\\users.txt", "w");

                for (int i = 0; i < amount_structs; i++){
                    fprintf(fp, "%s\n%s\n%d\n", test_users[i].username, test_users[i].password, test_users[i].block);
                }
                fclose(fp);

            }
            else if (j == 3){
                structure_printer(test_users, amount_structs);
            }
            else if (j == 4){
                cout << "\nTo continue you have to re-login\n";
                admin_login();

                FILE *fp;
                fp = fopen("C:\\Users\\zed11\\Documents\\pswd.txt", "w");
                char pwd[100];
                int i = 0;
                char ch;

                printf("\nEnter your password. Hit ENTER to confirm.\n");
                printf("Password:");

                while(1){
                    ch = getch();	//get key

                    if(ch == ENTER || ch == TAB){
                        pwd[i] = '\0';
                        break;
                    }else if(ch == BKSP){
                        if(i > 0){
                            i--;
                            printf("\b \b");		//for backspace
                        }
                    }else{
                        pwd[i++] = ch;
                        printf("* \b");				//to replace password character with *
                    }
                }

                fprintf(fp, "%s", pwd);

                fclose(fp);
            }
            else if (j == 5){
                cout << "\nTo continue you have to re-login\n";
                admin_login();
                struct User new_users[amount_structs + 1];
                memcpy(&new_users, &test_users, sizeof(struct User) * amount_structs);

                char username[SIZE];
                char paswd[PSWD_SIZE];
                int block_status;
                cout << "\nEnter new users username:";
                cin >> username;
                cout << "\nEnter new users password:";
                cin >> paswd;
                cout << "\nEnter new users block status:";
                cin >> block_status;

                strcpy(new_users[amount_structs].username, username);
                strcpy(new_users[amount_structs].password, paswd);
                new_users[amount_structs].block = block_status;

                FILE *fp;
                fp = fopen("C:\\Users\\zed11\\users.txt", "w");

                for (int i = 0; i < amount_structs + 1; i++){
                    fprintf(fp, "%s\n%s\n%d\n", new_users[i].username, new_users[i].password, new_users[i].block);
                }
                fclose(fp);

            }
            else if (j == 6){
                break;
            }
            else{
                cout << "Wrong input!";
                exit(1);
            }
        }

    }
    else if (choice == 2){
        FILE *fx;
        fx = fopen("C:\\Users\\zed11\\users.txt", "r");

        int count = 0;
        char c;

        for (c = getc(fx); c != EOF; c = getc(fx)){
            if (c == '\n') {
                count = count + 1;
            }
        }

        fclose(fx);

        FILE *fp;
        fp = fopen("C:\\Users\\zed11\\users.txt", "r");

        int amount_structs = count / 3;
        struct User test_users[amount_structs];

        for (int i = 0; i < amount_structs; i++) {
            fscanf(fp, "%s\n", test_users[i].username);
            fscanf(fp, "%s\n", test_users[i].password);
            fscanf(fp, "%d\n", &test_users[i].block);
        }

        fclose(fp);

        int index = user_login();

        if (test_users[index].block != 1){
            int pass_choice;
            cout << "\nNow you can change your password, if you want to change it enter - 1, if not enter - 2: ";
            cin >> pass_choice;

            if (pass_choice == 1){
                char new_pass[PSWD_SIZE];
                cout << "\nEnter new password: ";
                cin >> new_pass;

                strcpy(test_users[index].password, new_pass);

                FILE *fp;
                fp = fopen("C:\\Users\\zed11\\users.txt", "w");

                for (int i = 0; i < amount_structs; i++){
                    fprintf(fp, "%s\n%s\n%d\n", test_users[i].username, test_users[i].password, test_users[i].block);
                }
                fclose(fp);
            }
            else if (pass_choice == 2){
                cout << "\nYou have nothing to do.\nProgram will exit";
                return 0;
            }
        }
        else if (test_users[index].block == 1){
            cout << "\nYou are blocked, you can't change anything!";
        }


    }

    return 0;
}

int choose_privelege(){

    int choice;

    cout << "Choose:\n[1] - for Admin\n[2] - for User\n";
    cout << "Your choice: ";
    cin >> choice;

    if (choice > 2 || choice < 1){
        cout << "\nWrong input!";
        exit(1);
    }

    return choice;
}

void admin_login(){

    FILE *fp;
    fp = fopen("C:\\Users\\zed11\\Documents\\pswd.txt", "r");

    char password[PSWD_SIZE];
    fgets(password, PSWD_SIZE, (FILE*)fp);

    int i = 0;
    char ch;

    for (int k = 0; k < 3; k++){
        char pwd[100];

        cout << endl;
        printf("Enter your password. Hit ENTER to confirm. (Try: %d out of 3)\n", k + 1);
        printf("Password:");

        while(1){
            ch = getch();

            if(ch == ENTER || ch == TAB){
                pwd[i] = '\0';
                break;
            }else if(ch == BKSP){
                if(i > 0){
                    i--;
                    printf("\b \b");
                }
            }else{
                pwd[i++] = ch;
                printf("* \b");
            }
        }
        if (strcmp(pwd, password) == 0){
            cout << "\n\nLogged in!";
            break;
        }
        else if (strcmp(pwd, password) != 0){
            i = 0;
            memset(pwd, 0, PSWD_SIZE);
        }
        if (k == 2){
            cout << "\nOut of tries!";
            exit(1);
        }
    }

    fclose(fp);

}

int user_login() {

    FILE *fx;
    fx = fopen("C:\\Users\\zed11\\users.txt", "r");

    int count = 0;
    char c;

    for (c = getc(fx); c != EOF; c = getc(fx)){
        if (c == '\n') {
            count = count + 1;
        }
    }

    fclose(fx);

    FILE *fp;
    fp = fopen("C:\\Users\\zed11\\users.txt", "r+");

    int amount_structs = count / 3;
    struct User test_users[amount_structs];

    for (int i = 0; i < amount_structs; i++) {
        fscanf(fp, "%s\n", test_users[i].username);
        fscanf(fp, "%s\n", test_users[i].password);
        fscanf(fp, "%d\n", &test_users[i].block);
    }
    char username[SIZE];

    cout << "\nEnter username: ";
    cin >> username;

    int i = 0;
    char ch;

    int user_index = -1;

    for (int k = 0; k < 3; k++){
        char pwd[100];

        cout << endl;
        printf("Enter your password. Hit ENTER to confirm. (Try: %d out of 3)\n", k + 1);
        printf("Password:");

        while(1){
            ch = getch();

            if(ch == ENTER || ch == TAB){
                pwd[i] = '\0';
                break;
            }else if(ch == BKSP){
                if(i > 0){
                    i--;
                    printf("\b \b");
                }
            }else{
                pwd[i++] = ch;
                printf("* \b");
            }
        }
//        cout << "!" << pwd << "*";
        for (int j = 0; j < amount_structs; j++){
            if (strcmp(test_users[j].username, username) == 0 && strcmp(test_users[j].password, pwd) == 0){
                cout << "\nLogged in!";
                user_index = j;
                break;
            }

        }
        if (user_index != -1){
            break;
        }
        if (k == 2){
            cout << "\nOut of tries!";
            exit(1);
        }
        i = 0;
    }

    fclose(fp);

    return user_index;
}

void structure_printer(struct User *users, int amount){

    cout << endl;
    for (int i = 0; i < amount; i++){
        cout << "\n\n" << i + 1 << " user)\n";
        printf("Username: %s,\nPassword: %s,\nBlock status: %d", users[i].username, users[i].password, users[i].block);
    }

}

void password_changer(struct User *users, int index){

    char pwd[100];
    int i = 0;
    char ch;

    printf("\nEnter your password. Hit ENTER to confirm.\n");
    printf("Password:");

    while(1){
        ch = getch();	//get key

        if(ch == ENTER || ch == TAB){
            pwd[i] = '\0';
            break;
        }else if(ch == BKSP){
            if(i > 0){
                i--;
                printf("\b \b");		//for backspace
            }
        }else{
            pwd[i++] = ch;
            printf("* \b");				//to replace password character with *
        }
    }
    strcpy(users[index].password, pwd);
}

void block_status_changer(struct User *users, int index){

    int new_val;

    cout << "\nEnter 1 to block the user and 0 to unblock:";

    cin >> new_val;

    if (new_val > 1 || new_val < 0){
        cout << "\nWrong input!";
        exit(1);
    }

    users[index].block = new_val;
}