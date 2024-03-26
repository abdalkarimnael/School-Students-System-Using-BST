/////Project 3 DS -- Name: Abdalkarim Eiss --- ID: 1200015

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define NameLength 20
///To make a node for student
struct student;
typedef struct student *ptr;
struct student {
    int id;
    char name[NameLength];
    char address[NameLength];
    int class;
    char dateOfEnrollment[10];
    ptr left;
    ptr right;
};
typedef ptr BST;

///PreOrder Traversal to display all students
void traversal(BST S) {
    if (S != NULL) {
        printf("\n[ ");
        printf("Id: %d, Name: %s, Address: %s, Class: %d, Date of enrollment: %s", S->id, S->name, S->address, S->class,
               S->dateOfEnrollment);
        printf(" ]\n");
        traversal(S->left);
        traversal(S->right);
    }
}

///PreOrder Traversal to Visit all nodes
void visitAllNodes(BST S) {
    if (S != NULL) {
        traversal(S->left);
        traversal(S->right);
    }
}

//////Function to count the number of students
int numOfStudents(BST S) {
    if (S == NULL) {
        return 0;
    }

    return 1 + numOfStudents(S->left) + numOfStudents(S->right);
}

////Function to insert to BST
BST insert(int id, char name[], char address[], int class, char dateOfEnrollment[], BST s) {
    if (s == NULL) {
        s = (BST) malloc(sizeof(struct student));
        if (s == NULL) {
            printf("\nThe space isn't enough!!");
        } else {
            s->id = id;
            strcpy(s->name, name);
            strcpy(s->address, address);
            s->class = class;
            strcpy(s->dateOfEnrollment, dateOfEnrollment);
            s->left = s->right = NULL;
            ///printf("\n\nInsert Done!");
        }
    }
        ////Insert and order it by id
    else {
        if (id < s->id) {
            s->left = insert(id, name, address, class, dateOfEnrollment, s->left);
        } else if (id > s->id) {
            s->right = insert(id, name, address, class, dateOfEnrollment, s->right);
        }
    }
    return s;

}

////Function to check if id is valid using pre Order traversal
int isIdValid(int id, BST S) {
    if (S != NULL) {
        if (S->id == id) {
            return 0;
        }
        visitAllNodes(S->left);
        visitAllNodes(S->right);
    }
    return 1;
}

////Function to check if class number is valid
int isClassValid(int class) {
    if (class >= 1 && class <= 12) {
        return 1;
    }
    ///Else
    return 0;
}

//// Function to check if the is String of words or not
int isWord(char string[]) {
    int counter = 0;
    int i = 0;
    while (i < strlen(string)) {
        if (string[i] >= 'a' && string[i] <= 'z' || string[i] >= 'A' && string[i] <= 'Z') {
            counter++;
        }
        i++;
    }
    ///If all words are valid
    if (counter == strlen(string)) {
        return 1;
    } else {
        return 0;
    }
}

/////Function to check the validity of the enrollment date
int isValidDate(char date[]) {
    if ((strlen(date) == 10 || strlen(date) == 9 || strlen(date) == 8) && (date[1] == '/' || date[2] == '/') &&
        (date[3] == '/' || date[4] == '/' || date[5] == '/')) {
        return 1;
    }
    return 0;

}

////Function to search about student by id
int searchById(int id, BST S) {
    if (S != NULL) {
        if (id == S->id) {
            printf("\nThe student of %d ID is found\n", id);
            printf("Student's Information:\n");
            printf("\nId: %d, Name: %s, Address: %s, Class: %d, Date of enrollment: %s\n", S->id, S->name, S->address,
                   S->class, S->dateOfEnrollment);
            return 1;
        }
        int searchLeft = searchById(id, S->left);
        if (searchLeft) {
            return 1;
        }
        int searchRight = searchById(id, S->right);
        return searchRight;
    }
    return 0;
}

////Function to search about student by id To return the all info of student
/////////////////////////////////////-------------------/////////////////////////////
BST searchByIdForUpdate(int id, BST S) {
    if (S != NULL) {
        if (id == S->id) {
            return S;
        }
        BST searchLeft = searchByIdForUpdate(id, S->left);
        if (searchLeft != NULL) {
            return searchLeft;
        }
        BST searchRight = searchByIdForUpdate(id, S->right);
        if (searchRight != NULL) {
            return searchRight;
        }
    }
    return NULL;
}

/////////////---------------/////////////////
/////Function to find the minimum by id
BST Minimum(BST S) {
    if (S != NULL) {
        BST temp = S;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        return temp;
    }
}

//////Function to delete a node (Student) from the BST
BST delete(int id, BST S) {
    if (S == NULL) {
        return S; /// empty tree
    }

    if (id < S->id) {
        S->left = delete(id, S->left); /// Node to be deleted is in the left
    } else if (id > S->id) {
        S->right = delete(id, S->right); /// Node to be deleted is in the right
    } else {
        ////To check if there isn't  left or right
        ////left not exist
        if (S->left == NULL) {
            BST current = S->right;
            free(S);
            return current;
        }
            ////right not exist
        else if (S->right == NULL) {
            BST current = S->left;
            free(S);
            return current;
        }

        ///// If the node to be deleted has both left and right children
        BST current = Minimum(S->right);
        S->id = current->id;
        strcpy(S->name, current->name);
        strcpy(S->address, current->address);
        S->class = current->class;
        strcpy(S->dateOfEnrollment, current->dateOfEnrollment);
        S->right = delete(current->id, S->right);
    }
    return S;
}

///Update the id //////////////////////////////////////////////////////
BST update_id(int id, int newId, BST S) {
    if (S != NULL) {
        BST newS = searchByIdForUpdate(id, S);
        char name[NameLength];
        strcpy(name, newS->name);
        S = delete(id, S);
        S = insert(newId, name, newS->address, newS->class, newS->dateOfEnrollment, S);
        return S;
    }
}

///Update the name //////////////////////////////////////////////////////
BST update_name(int id, char newName[], BST S) {
    if (S != NULL) {
        BST newS = searchByIdForUpdate(id, S);
        if (newS != NULL) {
            strcpy(newS->name, newName);
        }
    }
    return S;
}

///Update the City name //////////////////////////////////////////////////////
BST update_city(int id, char newCity[], BST S) {
    if (S != NULL) {
        BST newS = searchByIdForUpdate(id, S);
        if (newS != NULL) {
            strcpy(newS->address, newCity);
        }
    }
    return S;
}

///Update the Class number //////////////////////////////////////////////////////
BST update_class(int id, int newClass, BST S) {
    if (S != NULL) {
        BST newS = searchByIdForUpdate(id, S);
        if (newS != NULL) {
            newS->class = newClass;
        }
    }
    return S;
}

///Update the Date Of enrollment //////////////////////////////////////////////////////
BST update_date(int id, char newDate[], BST S) {
    if (S != NULL) {
        BST newS = searchByIdForUpdate(id, S);
        if (newS != NULL) {
            strcpy(newS->dateOfEnrollment, newDate);
        }
    }
    return S;
}

/////Function to save all students to the file
void save(BST S, FILE *out) {
    if (S != NULL) {
        fprintf(out, "%d\t\t%s\t\t%s\t\t%d\t\t%s\n", S->id, S->name, S->address, S->class, S->dateOfEnrollment);
        save(S->left, out);
        save(S->right, out);
    }
}

/////// Function to load all names on an array
void loadNames(BST S, char name[][NameLength], int *pointer, int numberOfStudents) {
    if (S != NULL) {
        loadNames(S->left, name, pointer, numberOfStudents);
        strcpy(name[*pointer], S->name);
        (*pointer)++;
        loadNames(S->right, name, pointer, numberOfStudents);
    }
}

//////Function to search about student by name
void searchByName(char name[], BST S) {
    if (S != NULL) {
        if (strcmp(name, S->name) == 0) {
            printf("\nId: %d, Name: %s, Address: %s, Class: %d, Date of enrollment: %s\n", S->id, S->name, S->address,
                   S->class, S->dateOfEnrollment);
        }
        searchByName(name, S->left);
        searchByName(name, S->right);
    }
}

////Function to make nodes on lexicographic order depend on its names
void lexicographic_order(BST S, char name[][NameLength]) {
    int StudentsNumber = numOfStudents(S);
    if (S != NULL) {
        char memory[NameLength]; ///A memory to save a name
        ///Order by Using bubble sort
        for (int i = 0; i < StudentsNumber - 1; i++) {
            for (int j = 0; j < StudentsNumber - i - 1; j++) {
                if (strcmp(name[j], name[j + 1]) > 0) {
                    strcpy(memory, name[j]);
                    strcpy(name[j], name[j + 1]);
                    strcpy(name[j + 1], memory);
                }
            }
        }
    }
}

//////Function to search about city by name
void search_cityName(char cityName[], BST S, BST *new) {
    if (S != NULL) {
        if (strcmp(cityName, S->address) == 0) {
            *new = insert(S->id, S->name, cityName, S->class, S->dateOfEnrollment, *new);
            // printf("\nId: %d, Name: %s, Address: %s, Class: %d, Date of enrollment: %s\n",S->id, S->name, S->address, S->class, S->dateOfEnrollment);
        }
        search_cityName(cityName, S->left, new);
        search_cityName(cityName, S->right, new);
    }
}

/////Function to search about class
void search_class(int class, BST S, BST *new) {
    if (S != NULL) {
        if (S != NULL) {
            if (class == S->class) {
                *new = insert(S->id, S->name, S->address, class, S->dateOfEnrollment, *new);
                ///printf("\nId: %d, Name: %s, Address: %s, Class: %d, Date of enrollment: %s\n",S->id, S->name, S->address, S->class, S->dateOfEnrollment);
            }
            search_class(class, S->left, new);
            search_class(class, S->right, new);
        }
    }
}

////Function to traverse the BST and search about the classes, this will be called on main
void travForClasses(BST S, BST **class) {
    if (S != NULL) {
        int classNumber = S->class;
        search_class(classNumber, S, &(class[classNumber]));
    }
    if (S->left != NULL) {
        travForClasses(S->left, class);
    }

    if (S->right != NULL) {
        travForClasses(S->right, class);
    }
}

//////Main function
int main() {
    ////Header for the system
    printf("\t\t---------------------------\n");
    printf("\t\t\b\bWELCOME TO SCHOOL CLASSES SYSTEM\n");
    printf("\t\t---------------------------\n");
    printf("\t\t\t\t\t\tCreated by: A.N.A\n");
    ///Output File to save all students
    FILE *out;
    int q = 0;  ////For loop
    BST students = NULL;  /// Creat the BST
    while (q == 0) {
        ////To insert the students from the same city
        BST sameCity = NULL;
        ///To insert a student from the same class
        BST *Classes[12]; /// Define BST for each class
        ////Variables
        int numberOfStudents = numOfStudents(students);
        char names[numberOfStudents][NameLength]; ///Array to load all students' names
        char names_sameCity[numberOfStudents][NameLength]; ///Array to load all students' names
        char names_sameClass[numberOfStudents][NameLength]; ///Array to load all students' names
        int id;
        char Sname[NameLength];
        char newName[NameLength];
        char Saddress[NameLength];
        char newAddress[NameLength];
        int Sclass;
        int newClass;
        char SdateOfEnrollment[10];
        char newDate[10];
        int choice;
        int searchID;
        int chooseTheUpdate;  ////To choose the field that you need to update it
        char update[1];  //// To store the choice of what do you need an update or not
        char cityName[NameLength]; ///// variable to put the city name which was read from the user to search about it
        BST sameClass = NULL;///Tp put the searched class students on it for case 5

        ///Menu
        printf("\n\nWhat do you need from the menu? \n\t1. Add new student with all (his/her) information.\n\t2. Search about a Student using (his/her) ID.\n\t");
        printf("3. List all students in lexicographic order of their names.\n\t4. Search about a City using its name and list all students from that city \n\tin lexicographic order of their names.\n\t"
               "5. List all students by their class in lexicographic order of their names.\n\t6. Delete a Student by (his/her) ID.");
        printf("\n\t7. Save all Students in a file.\n\t8. Exit.\n\tEnter:");
        scanf("%d", &choice);
        switch (choice) {
            ///Insert new student
            case 1:
                printf("\nPlease enter the information of the student:\n");
                printf("Id:");
                scanf("%d", &id);
                while (!isIdValid(id, students)) {
                    printf("\nThis Id isn't valid, is already exist!!\n");
                    printf("Please enter another Id:");
                    scanf("%d", &id);
                }
                printf("Name:");
                scanf("%s", &Sname);
                /////To check the validity of student name
                while (!isWord(Sname)) {
                    printf("\nThis name isn't valid.\n");
                    printf("Please enter another name:");
                    scanf("%s", &Sname);
                }
                printf("Address (City):");
                scanf("%s", &Saddress);
                /////To check the validity of City name
                while (!isWord(Saddress)) {
                    printf("\nThis address isn't valid.\n");
                    printf("Please enter another address (City Name):");
                    scanf("%s", &Saddress);
                }
                printf("Class Number:");
                scanf("%d", &Sclass);
                ////To check the validity of Class Number
                while (!isClassValid(Sclass)) {
                    printf("\nThis class number isn't valid!!\n");
                    printf("Please enter another Class Number:");
                    scanf("%d", &Sclass);
                }
                printf("Date of enrollment (ex: 12/5/2023):");
                scanf("%s", &SdateOfEnrollment);
                ////To check the validity of date
                while (!isValidDate(SdateOfEnrollment)) {
                    printf("\nThis date format isn't valid!!\n");
                    printf("Please enter another date (ex: 12/5/2023 or 12/05/2023):");
                    scanf("%s", &SdateOfEnrollment);
                }
                ////To insert the student
                students = insert(id, Sname, Saddress, Sclass, SdateOfEnrollment, students);
                printf("\nInsert Done!\n");
                ///To printf all students
                traversal(students); ///Call traversal function
                break;
                ///To search about a student by id and make an update
            case 2:
                printf("\nPlease enter the id of student who you search about it:");
                scanf("%d", &searchID);
                ///If exist
                if (searchById(searchID, students)) {
                    printf("\nDo you need to make an update (y/n)?");
                    scanf("%s", &update);
                    //////Update on fields
                    if (update[0] == 'y') {
                        printf("\nOn what you need to make an update:\n\t1. Id.\n\t2. Name.\n\t3. Address (City).\n\t4. Class Number.\n\t"
                               "5. Date of Enrollment\n\tEnter:");
                        scanf("%d", &chooseTheUpdate);
                        switch (chooseTheUpdate) {
                            ///To update the  id
                            case 1:
                                printf("\nEnter new ID:");
                                scanf("%d", &id);
                                while (!isIdValid(id, students)) {
                                    printf("\nThis Id isn't valid, is already exist!!\n");
                                    printf("Please enter another Id:");
                                    scanf("%d", &id);
                                }
                                ///Update
                                students = update_id(searchID, id, students);
                                printf("\nThe update of ID is done!\n");
                                break;
                                ///To update the name
                            case 2:
                                printf("\nEnter new Name:");
                                scanf("%s", &newName);
                                while (!isWord(newName)) {
                                    printf("\nThis name isn't valid.\n");
                                    printf("Please enter another new name:");
                                    scanf("%s", &newName);
                                }
                                students = update_name(searchID, newName, students);
                                printf("\nThe update of name is done!\n");
                                break;
                                ///To update the address
                            case 3:
                                printf("\nEnter new address (City Name):");
                                scanf("%s", &newAddress);
                                while (!isWord(newAddress)) {
                                    printf("\nThis address isn't valid.\n");
                                    printf("Please enter another new address (City Name):");
                                    scanf("%s", &newAddress);
                                }
                                students = update_city(searchID, newAddress, students);
                                printf("\nThe update of address is done!\n");
                                break;
                                ///To update the class
                            case 4:
                                printf("\nEnter new Class Number :");
                                scanf("%d", &newClass);
                                ////To check the validity of Class
                                while (!isClassValid(newClass)) {
                                    printf("\nThis class number isn't valid!!\n");
                                    printf("Please enter another Class Number:");
                                    scanf("%d", &newClass);
                                }
                                students = update_class(searchID, newClass, students);
                                printf("\nThe update of Class is done!\n");
                                break;
                                ///To update the date
                            case 5:
                                printf("\nEnter new date of enrollment:");
                                scanf("%s", &newDate);
                                while (!isValidDate(newDate)) {
                                    printf("\nThis date format isn't valid!!\n");
                                    printf("Please enter another date (ex: 12/5/2023 or 12/05/2023):");
                                    scanf("%s", &newDate);
                                }
                                students = update_date(searchID, newDate, students);
                                printf("\nThe update of date of enrollment is done!\n");
                                break;
                        }
                        /// To display all students after the update
                        traversal(students);
                    }
                        ///ELSE
                    else {
                        printf("\nOk as you want, there is no update!\n");
                    }
                }else{
                    printf("\nThe student isn't found\n");  ///If the student isn't found
                }
                break;
                ///To display all students in lexicographic order
            case 3:

                printf("\n\nNUM: %d\n", numOfStudents(students));
                int j = 0;
                ///Load all student names into an array to order it
                loadNames(students, names, &j, numberOfStudents);

                lexicographic_order(students, names);
                printf("\nThe list of all students on Lexicographic Order:\n");
                for (int i = 0; i < j; i++) {
                    searchByName(names[i], students);
                }
                break;
                ///To search about city and display all students in lexicographic order
            case 4:
                printf("\nPlease enter the name of city:");
                scanf("%s", &cityName);

                ////To search about students from the same city and insert it into new BST
                search_cityName(cityName, students, &sameCity);
//                traversal(sameCity);
                int k = 0;
                loadNames(sameCity, names_sameCity, &k, numberOfStudents);

                lexicographic_order(sameCity, names_sameCity);
                printf("\nThe list of all students From %s on Lexicographic Order:\n", cityName);
                for (int i = 0; i < k; i++) {
                    searchByName(names_sameCity[i], sameCity);
                }
                break;
                ///To list all students by their classes and display all students in the same class on lexicographic order
            case 5:
                for (int i = 1; i <= 12; i++) {
                    Classes[i] = NULL;
                }
                travForClasses(students, Classes);
                for (int j = 1; j <= 12; j++) {
                    traversal(Classes[j]);
                }
                printf("\nPlease enter the number of class:");
                int class;
                scanf("%d", &class);
                int f = 0;
                ///sameClass=NULL;
                search_class(class, students, &sameClass);
//                traversal(sameClass);
                loadNames(sameClass, names_sameClass, &f, numberOfStudents);
                lexicographic_order(sameClass, names_sameClass);
                for (int j = 0; j < f; j++) {
                    searchByName(names_sameClass[j], sameClass);
                }
                break;
                ////Delete
            case 6:
                printf("Please enter the id of the student:");
                scanf("%d", &id);
                students = delete(id, students);
                printf("\nDelete Done !\n");
                traversal(students);
                break;
                ///To save  all student to a file
            case 7:
                out = fopen("students.data", "w");
                if (out != NULL) {
                    fprintf(out, "ID\t\tName\t\tAddress\t\tClass\t\tDate of Enrollment\n");
                    save(students, out);
                    printf("\nSave Done!\n");
                } else {
                    printf("\nFile doesn't exist!\n");
                }
                break;
            case 8:
                printf("\nThanks for using this system ^_*\n\n");
                return 1;
            default:
                printf("\nError, this choice isn't available !\n");
                break;
        }
    }
    return 0;
}
