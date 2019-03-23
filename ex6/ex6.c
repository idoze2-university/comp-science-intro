/******************************************
*Student name: Ido Zeira
*Student ID: 322607177
*Submit Info: Zeiraid
*Exercise name: ex6
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WELCOME_MESSAGE "Welcome! please choose an option\n1 - Log in\n2 - New member\n3 - Exit\n"
#define BAD_CHOICE_MESSAGE "Bad choice, please try again\n"
#define LOGIN_MESSAGE_USERNAME "Please enter your username:\n"
#define LOGIN_MESSAGE_PASSWORD "Please enter your password:\n"
#define MAIN_MESSAGE "Please choose an option:\n1. Find a match\n2. I found love, DELETE me\n3. Log out\n"
#define FIND_MATCH_INPUT_MESSAGE "Please choose ages range:\n"
#define NO_USER_MESSAGE "User do not exist in the system, please try again\n"
#define WRONG_PASS_MESSAGE "Wrong password\n"
#define ERR_USER_EXISTS "Error: User already exists\n"
#define MAX_INPUT_LENGTH 300
#define PERSON_FIELDS 9
#define INDEX_ID 0
#define INDEX_FNAME 1
#define INDEX_LNAME 2
#define INDEX_AGE 3
#define INDEX_GENDER 4
#define INDEX_UNAME 5
#define INDEX_PASSWORD 6
#define INDEX_HOBBIES 7
#define INDEX_DESCRIPTION 8
#define ID_LENGTH 9
#define FNAME_MAX_LENGTH 10
#define FNAME_MIN_LENGTH 4
#define LNAME_MAX_LENGTH 15
#define LNAME_MIN_LENGTH 4
#define DESC_MAX_LENGTH 211
#define USERNAME_MAX_LENGTH 10
#define USERNAME_MIN_LENGTH 3
#define HOBBIES_TYPE_COUNT 8
#define HOBBIES_LENGTH 4
#define MIN_AGE 18
#define MAX_AGE 100
#define PASSWORD_MAX_LENGTH 15
#define PASSWORD_MIN_LENGTH 3
#define INPUT_PATH "input.txt"
#define OUTPUT_PATH "output.txt"

typedef enum genderEnum { MALE = 'M', FEMALE = 'F' } Gender;
typedef enum hobbyEnum { BASEBALL = 1, BASKETBALL, BICYCLE, BOOKS, DRAWING, GYM, MOVIES, POETRY } Hobby;
typedef struct Person {
	char id[ID_LENGTH + 1];
	char* fName;
	char* lName;
	int age;
	Gender gender;
	char* uName;
	char* password;
	char hobbies;
	char* description;
} Person;
typedef struct FemaleList FemaleList;
struct FemaleList {
	Person value;
	FemaleList* next;
};
typedef struct DataBase {
	Person* males;
	int maleCount;
	FemaleList* females;
}DataBase;

void main();

DataBase* dataBase_new(char*);
void split(char * buffer, char * delimiter, char ** arr);
Person person_new(char * arr[PERSON_FIELDS]);
FemaleList* femaleList_new(Person value, FemaleList* next);
char toHobbyChar(char * hobbies);
DataBase* addPerson(DataBase * db, Person p);
int login(DataBase*, Person*);
int tryLogin(char * username, DataBase* db, Person* user);
void mainMenu(Person user, DataBase* db);
void printMatches(Person user, DataBase * ptrDB);
int isMatch(Person p1, Person p2);
void printPerson(Person p);
void printHobbies(char hobbies_char);
void printHobby(Hobby h);
void deletePerson(Person user, DataBase* ptrDB);
void newMember(DataBase * ptrDB);
int isValidID(char * str, DataBase* ptrDB);
int isNumber(char c);
int isLetters(char * str);
int isLetter(char c);
int isValidUsername(char* str);
int isLowercase(char c);
int isUppercase(char c);
int isValidHobbies(char * str);
void generateOutput(DataBase* ptrDB);
void printToFile(Person p, FILE * outf);
void fprintHobbies(FILE * outf, char hobbies_char);
void freePerson(Person * person);

/************************************************************************
* function name: main		  											*
* The Input: None								 						*
* The output: None														*
* The Function operation: shows the login menu.						 	*
*************************************************************************/
void main()
{
	int optionNum;			// The mission number
	//Initialize database with input file.
	DataBase* ptrDB = dataBase_new(INPUT_PATH);
	do {
		Person user = { 0 };
		printf(WELCOME_MESSAGE);
		scanf("%d", &optionNum);		// Reading the mission number
		switch (optionNum)
		{
		case 1:
			if (login(ptrDB, &user))//if login is successful:
			{
				printf("Hello %s!\n", user.fName);
				mainMenu(user, ptrDB);//redirect user to main menu
			}
			break;
		case 2:
			newMember(ptrDB);//add a member to DB
			break;
		case 3:
			generateOutput(ptrDB);// output DB to out.txt
			break;
		default:
			printf(BAD_CHOICE_MESSAGE);
			break;
		}
	} while (optionNum != 3);
	releaseMem(ptrDB);//Free Excess memory
	free(ptrDB);
	exit(0);
}
/************************************************************************
* function name: dataBase_new	  										*
* The Input: path of file containing people	information.				*
* The output: Initialized database struct containing people as specified*
*				on file in path.										*
* The Function operation: initialized database using file on path.		*
*************************************************************************/
DataBase* dataBase_new(char* inputPath)
{
	DataBase* db = malloc(sizeof(DataBase));
	if (!db)
		exit(1);
	db->males = malloc(sizeof(Person*));
	if (!db->males)
		exit(1);
	db->maleCount = 0;
	db->females = 0;
	FILE* inputf = fopen(inputPath, "r");
	if (inputf == NULL)
	{
		printf("FAILED TO OPEN FILE!\n");
		return;
	}
	char buffer[MAX_INPUT_LENGTH];
	int peopleCount = 0;
	char** personData = malloc(PERSON_FIELDS * sizeof(char*));
	if (!personData)
		exit(1);
	while (fgets(buffer, MAX_INPUT_LENGTH, inputf))
	{
		//Stripins buffer from trailing newline characters (by tokenizing up to \n).
		strcpy(buffer, strtok(buffer, "\n"));
		split(buffer, ";", personData);
		Person p = person_new(personData);
		addPerson(db, p);
		int i;
		for (i = PERSON_FIELDS - 1; i >= 0; i--)
			free(personData[i]);
	}
	free(personData);
	fclose(inputf);
	return db;
}
/************************************************************************
* function name: split	  												*
* The Input: buffer- input text, delimiter- specifying character delimiter
*			 arr- output: dynamically allocated array of strings.		*
* The output: None														*
* The Function operation: splits buffer via delimiters to arr.			*
*************************************************************************/
void split(char* buffer, char* delimiter, char** arr)
{
	int count = 0;
	//tokenize buffer into string with delimiter.
	char* substr = strtok(buffer, delimiter);
	while (substr)
	{
		//dynamically allocate field and insert it 
		arr[count] = malloc((strlen(substr) + 1) * sizeof(char));
		if (!arr[count])
			exit(1);
		strcpy(arr[count++], substr);
		substr = strtok(NULL, delimiter);
	}
	return;
}
/************************************************************************
* function name: person_new	  											*
* The Input: arr- dynamically allocated array of strings containing person
*			 information.												*
* The output: struct Person initialized to contain person information.	*
* The Function operation: constructs a person struct with arr containing*
*						  its information.								*
*************************************************************************/
Person person_new(char* arr[PERSON_FIELDS])
{
	//empty person struct
	Person person;
	//fill id field
	strcpy(person.id, arr[INDEX_ID]);
	//fill fname field
	person.fName = malloc((strlen(arr[INDEX_FNAME]) + 1) * sizeof(char));
	if (!person.fName)
		exit(1);
	strcpy(person.fName, arr[INDEX_FNAME]);
	//fill lname field
	person.lName = malloc((strlen(arr[INDEX_LNAME]) + 1) * sizeof(char));
	if (!person.lName)
		exit(1);
	strcpy(person.lName, arr[INDEX_LNAME]);
	//fill age field
	person.age = atoi(arr[INDEX_AGE]);
	//fill gender field
	person.gender = arr[INDEX_GENDER][0];
	//fill uname field
	person.uName = malloc((strlen(arr[INDEX_UNAME]) + 1) * sizeof(char));
	if (!person.uName)
		exit(1);
	strcpy(person.uName, arr[INDEX_UNAME]);
	//fill password field
	person.password = malloc((strlen(arr[INDEX_PASSWORD]) + 1) * sizeof(char));
	if (!person.password)
		exit(1);
	strcpy(person.password, arr[INDEX_PASSWORD]);
	//fill hobbies field
	person.hobbies = toHobbyChar(arr[INDEX_HOBBIES]);
	//fill description field
	person.description = malloc((strlen(arr[INDEX_DESCRIPTION]) + 1) * sizeof(char));
	if (!person.description)
		exit(1);
	strcpy(person.description, arr[INDEX_DESCRIPTION]);
	return person;
}
/************************************************************************
* function name: femaleList_new	  										*
* The Input: value- person to insert to value field,					*
*			 next- linked-list next node referance						*
* The output: pointer to the initiailzed femaleList						*
* The Function operation: constructs a femaleList struct with value and	*
*						  next.											*
*************************************************************************/
FemaleList* femaleList_new(Person value, FemaleList* next)
{
	//initialize a new femaleList instance.
	FemaleList* femaleList = malloc(sizeof(FemaleList));
	if (!femaleList)
		exit(1);
	femaleList->value = value;
	femaleList->next = next;
	return femaleList;
}
/************************************************************************
* function name: toHobbyChar  											*
* The Input: string of hobbies split via ','s.							*
* The output: char encoded with hobbies.								*
* The Function operation: encodes char with hobbies by lighting corresponding bits*
*************************************************************************/
char toHobbyChar(char* hobbies)
{
	char hobbyChar = 0;
	char* hobbies_split[4];
	//split hobbies to hobbies_split by ',' and end-case: ' '
	split(hobbies, ", ", hobbies_split);
	int h;
	for (h = 0; h < 4; h++)
	{
		//Light up bit curresponding to hobbies_split[h]
		hobbyChar += 0x1 << (atoi(hobbies_split[h]) - 1);
		free(hobbies_split[h]);
	}
	return hobbyChar;
}
/************************************************************************
* function name: addPerson		  										*
* The Input: ptr to DB, value of p (struct person)						*
* The output: ptr to DB													*
* The Function operation: inserts p to ptrDB							*
*************************************************************************/
DataBase* addPerson(DataBase* ptrDB, Person p)
{
	if (p.gender == MALE)
	{
		//dynamically allocate males array
		ptrDB->males = realloc(ptrDB->males, ++ptrDB->maleCount * sizeof(Person));
		ptrDB->males[ptrDB->maleCount - 1] = p;
		return ptrDB;
	}
	else
	{
		//if females is empty, initialize it.
		if (!ptrDB->females)
		{
			ptrDB->females = femaleList_new(p, 0);
			return ptrDB;
		}
		FemaleList* currentFemale = ptrDB->females;
		while (currentFemale)
		{
			//if p.lName is Alphabetically before value.lName:
			if (strcmp(p.lName, currentFemale->value.lName) < 0)
			{
				//initialize a list with current values and current.next next, insert after P.
				FemaleList* temp = femaleList_new(currentFemale->value, currentFemale->next);
				currentFemale->next = temp;
				currentFemale->value = p;
				return ptrDB;
			}
			else if (currentFemale->next->value.id)
			{
				//if p.lName is Alphabetically before value.lName but before next.value.lName:
				if (strcmp(p.lName, currentFemale->next->value.lName) > 0)
				{
					//initialize a list with P values and current.next next,
					//insert after current and before next.
					FemaleList* temp = femaleList_new(p, currentFemale->next);
					currentFemale->next = temp;
					return ptrDB;
				}
				//else: p.lName is Alphabetically before next.value.lName, move forward.
				currentFemale = currentFemale->next;
			}
			//if reached end of list, insert there.
			else
			{
				//initialize a list with P values and NULL next, insert at the end.
				FemaleList* temp = femaleList_new(p, currentFemale->next);
				currentFemale->next = temp;
				return ptrDB;
			}

		}
	}
}

/************************************************************************
* function name: login		  											*
* The Input: ptr to DB, ptr to User										*
* The output: int ture/false wether or not logged in					*
* The Function operation: gets username and password and tries to login with them*
*************************************************************************/
int login(DataBase* ptrDB, Person* ptrUser)
{
	char username[USERNAME_MAX_LENGTH + 1], password[PASSWORD_MAX_LENGTH + 1];
	int tries;
	for (tries = 0; tries < 3; tries++)
	{
		if (tries == 1)
			printf(NO_USER_MESSAGE);
		else if (tries == 2)
			return 0;
		printf(LOGIN_MESSAGE_USERNAME);
		//read username from stdin
		scanf("%s", username);
		//if username exists in db
		if (tryLogin(username, ptrDB, ptrUser))
		{
			printf(LOGIN_MESSAGE_PASSWORD);
			//read password from stdin
			scanf("%s", password);
			if (!strcmp(ptrUser->password, password))
				return 1;
			else
			{
				printf(WRONG_PASS_MESSAGE);
				return 0;
			}
		}
	}
	return 0;
}
/************************************************************************
* function name: tryLogin		  										*
* The Input: username, ptr to DB, ptr to user							*
* The output: int true/false wether or not login succeeded				*
* The Function operation: searches for user with uname username and inserts it to user ptr.							*
*************************************************************************/
int tryLogin(char* username, DataBase* ptrDB, Person* user)
{
	int i;
	//Search through males
	for (i = 0; i < ptrDB->maleCount; i++)
	{
		Person current = ptrDB->males[i];
		//if current scanned user has username as specified
		if (!strcmp(current.uName, username))
		{
			//save user info to *user
			*user = current;
			return 1;
		}
	}
	//Search through females
	FemaleList* currentFemale = ptrDB->females;
	while (currentFemale)
	{
		Person current = currentFemale->value;
		//if current scanned user has username as specified
		if (!strcmp(current.uName, username))
		{
			//save user info to *user
			*user = current;
			return 1;
		}
		currentFemale = currentFemale->next;
	}
	//if not found
	return 0;

}
/************************************************************************
* function name: mainMenu		  										*
* The Input: ptr to DB, ptr to user										*
* The output: None														*
* The Function operation: shows the mainmenu							*
*************************************************************************/
void mainMenu(Person user, DataBase* ptrDB)
{
	int optionNum = 0;
	while (optionNum != 3)
	{
		printf(MAIN_MESSAGE, user.fName);
		scanf("%d", &optionNum);
		switch (optionNum)
		{
		case 1:
			printMatches(user, ptrDB);
			break;
		case 2:
			deletePerson(user, ptrDB);
			return;
		case 3:
			break;
		default:
			printf(BAD_CHOICE_MESSAGE);
			break;
		}
	}

}
/************************************************************************
* function name: printMatches		  									*
* The Input: ptr to DB, user to find matchs to							*
* The output: None														*
* The Function operation: shows the matching people for user			*
*************************************************************************/
void printMatches(Person user, DataBase* ptrDB)
{
	printf(FIND_MATCH_INPUT_MESSAGE);
	int age_low, age_high;
	scanf("%d %d", &age_low, &age_high);
	if (age_low < MIN_AGE || age_low>MAX_AGE || age_high < age_low)
		return;
	//scan males
	if (user.gender == FEMALE)
	{
		int i;
		for (i = 0; i < ptrDB->maleCount; i++)
		{
			Person candidate = ptrDB->males[i];
			if (candidate.age <= age_high && candidate.age >= age_low)
			{
				//print if matchin
				if (isMatch(user, candidate))
				{
					printPerson(candidate);
					printf("\n\n");
				}
			}
		}
	}
	//scan females
	else
	{
		FemaleList* currentFemale = ptrDB->females;
		while (currentFemale)
		{
			if (currentFemale->value.age <= age_high && currentFemale->value.age >= age_low)
			{
				//print if matching
				if (isMatch(user, currentFemale->value))
				{
					printPerson(currentFemale->value);
					printf("\n\n");
				}
			}
			currentFemale = currentFemale->next;
		}
	}
}
/************************************************************************
* function name: isMatch		  										*
* The Input: people p1, p2												*
* The output: int true/false wether or not 	p1 and p2 are matching.		*
* The Function operation: calculate the amount of shared hobbies between*
*						  p1 & p2 and returns them.						*
*************************************************************************/
int isMatch(Person p1, Person p2)
{
	int i, mask = 0x1, count = 0;
	for (i = 0; i < 9; i++)
	{
		//if current bit(mask) is lit on both p1s hobbies and p2s hobbies, 
		//count it as a shared hobby
		if (mask&(p1.hobbies&p2.hobbies))
			count++;
		//insert mask to next bit
		mask <<= 1;
	}
	//return 1 if p1 & p2 share 2 or more similar hobbies: else 0.
	return count >= 2;

}
/************************************************************************
* function name: printPerson											*
* The Input: person p													*
* The output: None														*
* The Function operation: prints p's information						*
*************************************************************************/
void printPerson(Person p)
{
	printf("Name: %s %s ", p.fName, p.lName);
	printf("Age: %d ", p.age);
	printf("Hobbies: ");
	printHobbies(p.hobbies);
	printf("Description: %s", strtok(p.description, "\n"));
}
/************************************************************************
* function name: printHobbies											*
* The Input: char representing encoded hobbies							*
* The output: None														*
* The Function operation: splits hobbies_char into hobbies and prints each*
*************************************************************************/
void printHobbies(char hobbies_char)
{
	int i, j = 0;
	Hobby hobby_array[HOBBIES_LENGTH];//decoded hobbies array
	for (i = 0; i < HOBBIES_TYPE_COUNT; i++)
	{
		//if 2^i is lit, store it in decoded array
		if (hobbies_char & (0x1 << i))
		{
			hobby_array[j++] = i + 1;
		}
	}
	for (i = 0; i < HOBBIES_LENGTH; i++)
	{
		printHobby(hobby_array[i]);
		if (i < 3)//append ',' after the first 3 hobbies
			printf(",");
		printf(" ");
	}
}

/************************************************************************
* function name: printHobby												*
* The Input: Hobby to print												*
* The output: None														*
* The Function operation: prints The literal representation of enum hobby*
*************************************************************************/
void printHobby(Hobby h)
{
	switch (h)
	{
	case BASEBALL:
		printf("Baseball");
		break;
	case BASKETBALL:
		printf("Basketball");
		break;
	case BICYCLE:
		printf("Bicycle");
		break;
	case BOOKS:
		printf("Books");
		break;
	case DRAWING:
		printf("Drawing");
		break;
	case GYM:
		printf("Gym");
		break;
	case MOVIES:
		printf("Movies");
		break;
	case POETRY:
		printf("Poetry");
		break;
	}

}
/************************************************************************
* function name: deletePerson											*
* The Input: person p, ptr to DB										*
* The output: None														*
* The Function operation: finds, deletes and frees P from DB			*
*************************************************************************/
void deletePerson(Person p, DataBase* ptrDB)
{
	if (p.gender == MALE)
	{
		//scan through males
		int i;
		for (i = 0; i < ptrDB->maleCount; i++)
		{
			if (!strcmp(p.id, ptrDB->males[i].id))//(p.id==ptrDB->males[i].id)
			{
				for (; i < ptrDB->maleCount - 1; i++)
				{
					//move each male to the previous cell
					ptrDB->males[i] = ptrDB->males[i + 1];
				}
				//allocate -1 size to males
				ptrDB->males = realloc(ptrDB->males, --ptrDB->maleCount * sizeof(Person));
				//free the cells stored in the freed man
				freePerson(&p);
				return;
			}
		}
	}
	else
	{
		//scan through females
		FemaleList* currentFemale = ptrDB->females;
		//if p is the first females
		if (!strcmp(p.id, currentFemale->value.id))//id equals on both p and currentFemale
		{
			FemaleList* temp = currentFemale;
			ptrDB->females = currentFemale->next;
			//delete temp and free the cells stored in it's woman
			free(temp);
			freePerson(&p);
			return;
		}
		while (currentFemale->next)
		{
			if (!strcmp(p.id, currentFemale->next->value.id))
			{
				//save a ptr to the female which is to be deleted
				FemaleList* temp = currentFemale->next;
				currentFemale->next = temp->next;
				//delete temp and free the cells stored in it's woman
				free(temp);
				freePerson(&p);
				return;
			}
			//scan through next female
			currentFemale = currentFemale->next;
		}
		//at last, free the temporary ptr currentFemale
		free(currentFemale);

	}
}

/************************************************************************
* function name: newMemeber												*
* The Input: ptr to DB to insert member to								*
* The output: None														*
* The Function operation: reads member data from stdin and inserts a new member*
*************************************************************************/
void newMember(DataBase* ptrDB)
{
	int i = 0;
	char dummy;
	printf("Please enter your ID:\n");
	char id[ID_LENGTH + 1];
	scanf("%s", id);
	if (!isValidID(id, ptrDB))
	{
		printf(ERR_USER_EXISTS);
		return;
	}
	printf("Please enter your first name:\n");
	char fName[FNAME_MAX_LENGTH + 1];
	scanf("%s", fName);
	if (!isLetters(fName))
		return;
	printf("Please enter your last name:\n");
	char lName[LNAME_MAX_LENGTH + 1];
	scanf("%s", lName);
	if (!isLetters(lName))
		return;
	printf("Please enter your age (18 to 100):\n");
	char age[4];//up to Three chars ('100') followed by \0 - hence size 4
	scanf("%s", &age);
	if (atoi(age) < MIN_AGE || atoi(age) > MAX_AGE)
		return;
	printf("Please enter your gender (F-female, M-male):\n");
	char gender[2];//One Char followed by \0 - hence size 2
	scanf("%s", &gender);
	if (gender[0] == 'm')
		gender[0] = MALE;
	else if (gender[0] == 'f')
		gender[0] = FEMALE;
	if (gender[0] != MALE && gender[0] != FEMALE)
		return;
	printf("Choose a username (3-10 characters):\n");
	char uName[USERNAME_MAX_LENGTH + 1];
	scanf("%s", uName);
	if (!isValidUsername(uName))
		return;
	printf("please choose 4 hobbies: Baseball=1, Basketball=2, Bicycle=3, Books=4, Drawing=5, Gym=6, Movies=7, Poetry=8\n");
	char hobbies[2 * HOBBIES_LENGTH];
	scanf("%c %c %c %c %c", &dummy, hobbies, hobbies + 2, hobbies + 4, hobbies + 6);
	hobbies[1] = ',';
	hobbies[3] = ',';
	hobbies[5] = ',';
	hobbies[7] = '\0';
	if (!isValidHobbies(hobbies))
		return;
	printf("Choose a password (attention-minimum 3 characters):\n");
	char password[PASSWORD_MAX_LENGTH + 1];
	scanf("%s", password);
	if (strlen(password) < PASSWORD_MIN_LENGTH)
		return;
	printf("Some words about yourself:\n");
	char description[DESC_MAX_LENGTH + 1];
	scanf("%c%[^\n]s", &dummy, description);
	//simulate reading from a file and splitting with split() -> store data in input
	char* input[PERSON_FIELDS] = { id,fName,lName,age,gender,uName,password,hobbies,description };
	//create a new person with the input 
	Person p = person_new(input);
	//add p to db
	ptrDB = addPerson(ptrDB, p);
	printf("Hi %s, lets find love!\n", p.fName);
	//login as p
	mainMenu(p, ptrDB);
}
/************************************************************************
* function name: isValidID												*
* The Input: str,db														*
* The output: true/false(1/0)											*
* The Function operation: returns 1/0 if str is a valid ID not used in DB*
*************************************************************************/
int isValidID(char* str, DataBase* ptrDB)
{
	if (strlen(str) != 9)
		return 0;
	int i;
	for (i = 0; i < strlen(str); i++)
	{
		//if any character is not a number
		if (!isNumber(str[i]))
			return 0;
	}
	if (isExistingID(str, ptrDB))
		return 0;
	//pass
	return 1;
}
/************************************************************************
* function name: isExistingID											*
* The Input: id, DB														*
* The output: None														*
* The Function operation: prints The literal representation of enum hobby*
*************************************************************************/
int isExistingID(char id[ID_LENGTH + 1], DataBase* ptrDB)
{
	int i;
	for (i = 0; i < ptrDB->maleCount; i++)
	{
		Person current = ptrDB->males[i];
		if (!strcmp(current.id, id))
		{
			return 1;
		}
	}
	FemaleList* currentFemale = ptrDB->females;
	while (currentFemale)
	{
		Person current = currentFemale->value;
		if (!strcmp(current.id, id))
		{
			return 1;
		}
		currentFemale = currentFemale->next;
	}
	return 0;
}
/************************************************************************
* function name: isNumber												*
* The Input: character to evaluate										*
* The output: true/false(1/0)											*
* The Function operation: returns wether or not the char represents a digit*
*************************************************************************/
int isNumber(char c)
{
	return (c >= '0') && (c <= '9');
}
/************************************************************************
* function name: isLetters												*
* The Input: str to evaluate											*
* The output: true/false(1/0)											*
* The Function operation: returns wether or not the str contains letters*
*							Exclusively.								*
*************************************************************************/
int isLetters(char* str)
{
	int i;
	for (i = 0; i < strlen(str); i++)
	{
		if (!isLetter(str[i]))
			return 0;
	}
	return 1;
}
/************************************************************************
* function name: isLetter												*
* The Input: character to evaluate										*
* The output: true/false(1/0)											*
* The Function operation: returns wether or not the char represents an	*
*							english alphabet leter.						*
*************************************************************************/
int isLetter(char c)
{
	return isLowercase(c) || isUppercase(c);
}
/************************************************************************
* function name: isValidUsername										*
* The Input: str to evaluate											*
* The output: true/false(1/0)											*
* The Function operation: returns wether or not str represents a valid Username*
*************************************************************************/
int isValidUsername(char* str)
{
	//ensure valid length
	if (strlen(str) < USERNAME_MIN_LENGTH)
		return 0;
	return isLetter(str[0]);
}
/************************************************************************
* function name: isLowercase											*
* The Input: char to evaluate											*
* The output: true/false(1/0)											*
* The Function operation: returns wether or not str represents a lowercase letter*
*************************************************************************/
int isLowercase(char c)
{
	return (c >= 'a' && c <= 'z');
}
/************************************************************************
* function name: isUppercase											*
* The Input: char to evaluate											*
* The output: true/false(1/0)											*
* The Function operation: returns wether or not str represents a uppercase letter*
*************************************************************************/
int isUppercase(char c)
{
	return (c >= 'A' && c <= 'Z');
}
/************************************************************************
* function name: isLowercase											*
* The Input: char to evaluate											*
* The output: true/false(1/0)											*
* The Function operation: returns wether or not str represents a		*
*							valid array of hobbies						*
*************************************************************************/
int isValidHobbies(char* str)
{
	int i, countHobbies = 0, lastHobby = 0;
	for (i = 0; i < strlen(str); i++)
	{
		if (isNumber(str[i]))
		{
			int x = str[i] - '0';
			if (x > lastHobby && x <= HOBBIES_TYPE_COUNT)
			{
				countHobbies++;
				lastHobby = x;
			}
			else
				return 0;
		}
	}
	if (countHobbies != HOBBIES_LENGTH)
		return 0;
	return 1;
}

/************************************************************************
* function name: generateOutput											*
* The Input: ptr to DB from which to generate output					*
* The output: None														*
* The Function operation: generates output file from db					*
*************************************************************************/
void generateOutput(DataBase * ptrDB)
{
	FILE* outf = fopen(OUTPUT_PATH, "w+");
	int i;
	for (i = 0; i < ptrDB->maleCount; i++)
	{
		Person current = ptrDB->males[i];
		printToFile(current, outf);
	}
	FemaleList* currentFemale = ptrDB->females;
	while (currentFemale)
	{
		Person current = currentFemale->value;
		printToFile(current, outf);
		currentFemale = currentFemale->next;
	}
	fclose(outf);
}
/************************************************************************
* function name: printToFile											*
* The Input: Person and file ptr										*
* The output: None														*
* The Function operation: prints p's info to outf file.					*
*************************************************************************/
void printToFile(Person p, FILE* outf)
{
	fprintf(outf, "%s;", p.id);
	fprintf(outf, "%s;", p.fName);
	fprintf(outf, "%s;", p.lName);
	fprintf(outf, "%d;", p.age);
	fprintf(outf, "%c;", p.gender);
	fprintf(outf, "%s;", p.uName);
	fprintf(outf, "%s;", p.password);
	fprintHobbies(outf, p.hobbies);
	fprintf(outf, "%s\n", p.description);

}
/************************************************************************
* function name: fprintHobbies											*
* The Input: file ptr, hobbies to print									*
* The output: None														*
* The Function operation: prints hobbies to outf file, as numbers.		*
*************************************************************************/
void fprintHobbies(FILE* outf, char hobbies_char)
{
	int i, j = 0;
	Hobby hobby_array[HOBBIES_LENGTH];
	for (i = 0; i < HOBBIES_TYPE_COUNT; i++)
	{
		if (hobbies_char & (0x1 << i))
		{
			hobby_array[j++] = i + 1;
		}
	}
	for (i = 0; i < HOBBIES_LENGTH; i++)
	{
		fprintf(outf, "%d", hobby_array[i]);
		if (i < 3)
			fprintf(outf, ",");
	}
	fprintf(outf, ";");
}
/************************************************************************
* function name: releaseMem												*
* The Input: ptr to DB													*
* The output: None														*
* The Function operation: releases allocated memory of DB to prevent leaks.*
*************************************************************************/
void releaseMem(DataBase* ptrDB)
{
	int i;
	for (i = ptrDB->maleCount - 1; i >= 0; i--)
	{
		freePerson((ptrDB->males) + i);
	}
	free(ptrDB->males);
	FemaleList* current = ptrDB->females;
	while (current)
	{
		freePerson(&(current->value));
		FemaleList* temp = current;
		current = current->next;
		free(temp);
	}
}
/************************************************************************
* function name: freePerson												*
* The Input: ptr to person												*
* The output: None														*
* The Function operation: releases allocated memory of pointed peron's fields.*
*************************************************************************/
void freePerson(Person* person)
{
	free(person->fName);
	free(person->lName);
	free(person->uName);
	free(person->password);
	free(person->description);
}