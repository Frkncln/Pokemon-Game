#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef enum{Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Krabby} pokemon;
typedef enum{quadratic,linear} attack_type;


void selection_menu(char Pokemon_name[10][10], int range[10], attack_type type[10],int attack_power[10], int stamina[10]);
int str_comparison(char *str1,char *str2);

void pokedex(char Pokemon_name[10][10], int range[10], attack_type type[10],int attack_power[10], int stamina[10]);
void show_Pokemons(char Pokemon_name[10][10], pokemon Pokemons[10],int pokemon_count);
void catch_a_pokemon(char Pokemon_name[10][10], pokemon Pokemons[10],pokemon *my_pocket);
void release_a_pokemon(char Pokemon_name[10][10], pokemon Pokemons[10],pokemon *my_pocket);
void oaks_laboratory(char Pokemon_name[10][10], pokemon Pokemons[10],pokemon *my_Pokemons);

int pokemon_choice(char Pokemon_name[10][10],int area[8][8],int control_user_or_cmp[8][8],pokemon user_or_cmp_Pokemons[4],int *x,int *y,int control);
void fill_the_cmp_pokemon(pokemon cmp_Pokemon[4]);
void first_locate_pokemon_cmp_user(int area[8][8],char Pokemon_name[10][10],pokemon cmp_Pokemons[4],pokemon user_Pokemons[4],int pokemon_staminas[8][8],int stamina[10],int control[8][8]);
void move_and_attack(int area[8][8],int control_user_or_cmp[8][8],int pokemon_staminas[8][8],pokemon user_or_cmp_Pokemons[4],int pokemon_selection,int x,int y,int range[10], attack_type type[10], int attack_power[10],int stamina[10],int control);
int control_game(pokemon user_Pokemons[4],pokemon cmp_Pokemons[4]);
void battle(char Pokemon_name[10][10], int range[10], attack_type type[10], int attack_power[10], int stamina[10],pokemon user_Pokemons[4]);


void show_area (char Pokemon_name[10][10],int area[8][8],int pokemon_staminas[8][8]);


int main()
{

	char Pokemon_name[10][10]={"Charmande","Pikachu","Squirtle","Bulbasaur","Pidgeotto","Ratata","Mug","Caterpie","Zubat","Krabby"};
	int range[10]={1,3,4,3,2,2,1,2,3,2};
	int attack_power[10]={500,350,300,400,250,250,350,200,350,300};
	int stamina[10]={2200,1500,1700,2500,1900,2500,3000,1200,1250,2600};
	attack_type type[10]={0,1,1,1,0,1,0,0,1,1};
	srand(time(NULL));

	selection_menu(Pokemon_name,range,type,attack_power,stamina);

	return 0;
}

void selection_menu(char Pokemon_name[10][10], int range[10], attack_type type[10],int attack_power[10], int stamina[10])
{
	int selection,i,count;
	pokemon Pokemons[10]={0,1,2,3,4,5,6,7,8,9};
	pokemon my_Pokemons[4]={'\n','\n','\n','\n'};


	do{
		printf("1)	Open Pokedex\n");
		printf("2)	Go to Oak's Laboratory\n");
		printf("3)	Enter The Tournament\n");
		printf("Selection: ");
		scanf("%d",&selection);
		printf("\n\n");
		switch(selection){
			case 1:
				pokedex(Pokemon_name,range,type,attack_power,stamina);
				break;
			case 2:
				oaks_laboratory(Pokemon_name,Pokemons,my_Pokemons);
				break;
			case 3:
				//If My pokemons have '\n' You can not go to tournament
				count=0;
				for(i=0;i<4;i++){
					if(my_Pokemons[i]!='\n'){
						count++;		
					}
				}
				if(count==4)
					battle(Pokemon_name,range,type,attack_power,stamina,my_Pokemons);
				else
					printf("You don't have four pokemons Ash so you can not go to Tournament ! !\n");
				break;
			default:
				break;
		}
	}while(1);
}

int str_comparison(char *Pokemon_name,char *target){

   while (*Pokemon_name == *target) {
      Pokemon_name++;
      target++;
      if (*Pokemon_name == '\0' && *target == '\0')
         return 1;
   }

   return 0;
}
 
void pokedex(char Pokemon_name[10][10], int range[10], attack_type type[10],int attack_power[10], int stamina[10])
{

	char target[10];
	int i,j,flag=0;
	char exit[10]="exit";
	do{
		printf("Please type name of the Pokémon (type exit to close Pokedex): ");
		scanf("%s",target);

		for(i=0;i<10;i++){
			if(1==str_comparison(Pokemon_name[i],target)){
				flag=1;
				printf("Name	: %s\n",Pokemon_name[i]);
			
				if(type[i]==0)
					printf("A. Type: Quadratic\n");
				if(type[i]==1)
					printf("A. Type: Linear\n");

				printf("Range	: %d\n",range[i]);
				printf("A. Power	: %d\n",attack_power[i]);
				printf("Stamina: %d\n",stamina[i]);
				printf("\n");
				break;
			}
			else
				flag=0;
		}

		if (1==str_comparison(exit,target))
		{
			printf("\n");
			break;
		}
		if (flag==0)
		{
			printf("This is not Pokemon name. Again Enter the Pokemon name ! !\n\n");
		}

	}
	while(1);
}

void show_Pokemons(char Pokemon_name[10][10], pokemon Pokemons[10],int pokemon_count)
{
	int i,j;
	if (pokemon_count==10)
	{
		printf("Pokemons In Pokedex:\n");
	}
	if (pokemon_count==4)
	{
		printf("Pokemons In Your pocket:\n");
	}

	for(i=0;i<pokemon_count;i++){
		if(Pokemons[i]!='\n')
			printf("%d - %s\n",Pokemons[i],Pokemon_name[Pokemons[i]]);
	}
	printf("\n");

}

void catch_a_pokemon(char Pokemon_name[10][10], pokemon Pokemons[10],pokemon *my_pocket)
{
	int count=0,i;
	int selection,flag;

	//TO CONTROL THE WHETHER YOU HAVE OR ANY POKEMON
	for(i=0;i<4;i++){
		if(*(my_pocket+i)!='\n'){
			count++;		
		}
	}

	if(count<4){
		do{
			show_Pokemons(Pokemon_name,Pokemons,10);

			printf("\nSelect Pokemon ASH: ");
			scanf("%d",&selection);
			printf("\n");
			//Previously caught pokemon, test
			for(i=0;i<4;i++){
				flag=1;

				if(selection==*(my_pocket+i)){
					printf("You've already caught this Pokémon.\n\n");
					flag=0;
					break;
				}
			}	
			//Does this pokemon have pokedex or not?
			if(flag!=0){
				for(i=0;i<10;i++){
					flag=0;
					if(Pokemons[i]==selection){
						flag=1;
						break;
					}
				}
				if(flag==0)
					printf("Pokedex does not have such a pokemon.\n\n");
			}	

		}while(flag!=1);

		//Record the your pokemon selection
		for(i=0;*(my_pocket+i)!='\n';i++);
		*(my_pocket+i)=selection;
	}
	else
		printf("Also You Have Four Pokemon\n\n");
}


void release_a_pokemon(char Pokemon_name[10][10], pokemon Pokemons[10],pokemon *my_pocket)
{
	int i,count;
	int selection,flag;
	//Do you have any Pokemon?
	for(i=0,count=0;*(my_pocket+i)=='\n';i++,count++);

	if(count!=4){
		do{
			show_Pokemons(Pokemon_name,my_pocket,4);
			printf("\nRelease Pokemon ASH: ");
			scanf("%d",&selection);
			printf("\n");

			for(i=0;i<10;i++){
				flag=0;
				if(Pokemons[i]==selection){
					flag=1;
					break;
				}
			}

			if(flag==0)
				printf("Pokedex does not have such a pokemon.\n\n");

			if(flag!=0){
				for(i=0;i<4;i++){
					flag=0;
					if(selection==*(my_pocket+i)){
						flag=1;
						break;
					}
				}	
				if(flag==0)
					printf("You don't have this Pokemon ASH.\n\n");			
			}	

		}while(flag!=1);
		//Deleting a Pokemon from your pocket
		for(i=0;*(my_pocket+i)!=selection;i++);
			
			*(my_pocket+i)='\n';	
	}
	else
		printf("You have any Pokemon ASH. Firstly You must to catch Pokemon\n\n");
	
}

void oaks_laboratory(char Pokemon_name[10][10], pokemon Pokemons[10],pokemon *my_Pokemons)
{
	int selection;
	do{
		printf("1)	Show Pokemons\n");
		printf("2)	Catch a Pokemon\n");
		printf("3)	Release a Pokemon\n");
		printf("4)	Show my pocket\n");
		printf("5)	Back\n");
		printf("Selection: ");
		scanf("%d",&selection);
		printf("\n");
		switch(selection){
			case 1:
				show_Pokemons(Pokemon_name,Pokemons,10);
				break;
			case 2:
				catch_a_pokemon(Pokemon_name,Pokemons,my_Pokemons);
				break;
			case 3:
				release_a_pokemon(Pokemon_name,Pokemons,my_Pokemons);
				break;
			case 4:
				show_Pokemons(Pokemon_name,my_Pokemons,4);
				break;
			case 5:
				break;
			default:
				printf("Invalid Selection\n");
				break;
		}
	}while(selection!=5);
}

//Fill the AI pocket with randomly
void fill_the_cmp_pokemon(pokemon cmp_Pokemon[4])
{
	int i,j;

	for(i=0;i<4;i++){
		cmp_Pokemon[i]=rand()%8;

		for(j=0;j<i;j++){
			if (cmp_Pokemon[i]==cmp_Pokemon[j])
			{
				do{
					cmp_Pokemon[i]=rand()%8;
					j=0;	
				}
				while(cmp_Pokemon[i]==cmp_Pokemon[j]);
			}

		}

	}
}

void first_locate_pokemon_cmp_user(int area[8][8],char Pokemon_name[10][10],pokemon cmp_Pokemons[4],pokemon user_Pokemons[4],int pokemon_staminas[8][8],int stamina[10],int control[8][8])
{
	int cmp_x,cmp_y;
	int user_x,user_y;
	int i;

	printf("First Locate Pocemon And User ...\n");
	//Locate AI POKEMON to AREA
	for(i=0;i<4;i++){
		cmp_x=6+rand()%2;
		cmp_y=rand()%8;
		while(area[cmp_x][cmp_y]!=-1){
			cmp_x=6+rand()%2;
			cmp_y=rand()%8;
		}
		area[cmp_x][cmp_y]=cmp_Pokemons[i];
		control[cmp_x][cmp_y]=2;
		pokemon_staminas[cmp_x][cmp_y]=stamina[cmp_Pokemons[i]];
	}	
	// Locate USER POKEMON to AREA
	for(i=0;i<4;i++){	
		do{
			do{
				printf("Which row(0 or 1) do you want to Pokemon '%s' :",Pokemon_name[user_Pokemons[i]]);
				scanf("%d",&user_x);
			}
			while(user_x!=0 && user_x!=1);
			do{
				printf("Which column(0>= y <8) do you want to Pokemon '%s' :",Pokemon_name[user_Pokemons[i]]);
				scanf("%d",&user_y);
			}
			while( !(user_y>=0 && user_y<8) );

			printf("\n");

			if(area[user_x][user_y]!=-1)
				printf("Change The Cordinate.This location already have %s ! ! \n\n",Pokemon_name[area[user_x][user_y]]);
		}
		while(area[user_x][user_y]!=-1);

		area[user_x][user_y]=user_Pokemons[i];
		control[user_x][user_y]=1;
		pokemon_staminas[user_x][user_y]=stamina[user_Pokemons[i]];
	}
}

int pokemon_choice(char Pokemon_name[10][10],int area[8][8],int control_user_or_cmp[8][8],pokemon user_or_cmp_Pokemons[4],int *x,int *y,int control)
{
	int i,j,flag=0;
	int pokemon_selection;
	char target[10];

	// 'CONTROL' PARAMETER :Who will work for this function? control '1'=user '0'=AI
	//This funxtion choice the pokemon and its coordinate 'x' 'y'

	if (control==1)
	{
		do{
			printf("Choice The Pokemon(With Pokemon Name For example 'Charmande'): ");
			scanf("%s",target);
			for(i=0;i<10;i++){
				if(1==str_comparison(Pokemon_name[i],target) ){
					for (j=0 ; j < 4; j++)
					{
						if (user_or_cmp_Pokemons[j]==i)
						{
							flag=1;
							break;
						}

					}
				
					break;
				}
			}
			if (flag==0)
			{
				printf("This is not your Pokémon or This Pokémon died ! !\n");
			}
			else
				break;
		}while(1);

		pokemon_selection=i;
		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				if (area[i][j]==pokemon_selection && control_user_or_cmp[i][j]==1)
				{
					*x=i;
					*y=j;
					return pokemon_selection;
				}
			}
		}
	}

	if (control==2)
	{
		do{
			pokemon_selection=0+rand()%4;
			if (user_or_cmp_Pokemons[pokemon_selection]!='\n')
			{
				break;
			}
		}
		while(1);

		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				if (area[i][j]==user_or_cmp_Pokemons[pokemon_selection] && control_user_or_cmp[i][j]==2)
				{
					printf("Computer Choice: %s\n",Pokemon_name[user_or_cmp_Pokemons[pokemon_selection]]);
					*x=i;
					*y=j;
					return user_or_cmp_Pokemons[pokemon_selection];
				}
			}
		}
	}
	return 0;
}

void move_and_attack(int area[8][8],int control_user_or_cmp[8][8],int pokemon_staminas[8][8],pokemon user_or_cmp_Pokemons[4],int pokemon_selection,int x,int y,int range[10], attack_type type[10], int attack_power[10],int stamina[10],int control){

	int i,j,k;
	int temp_x,temp_y,direction;
	int cmp_move_range;
	int linear_attack[4][3],temp;

	// 'CONTROL' PARAMETER :Who will work for this function? control '1'=user '0'=AI
	//This function firstly move secondly attack

	//Keeps pokemon and distances to be attacked 'linee_attack[4][3]'
	//Linee_Attack[4][0] is range [4][1] 'x' direction coordinate [4][2]'y' direction coordinate
	linear_attack[0][0]=-1;
	linear_attack[1][0]=-1;
	linear_attack[2][0]=-1;
	linear_attack[3][0]=-1;

	if (control==1)
	{
		do{
			printf("Enter Move Cordinate(Move Range '1 or 2') :\n");
			printf("x : ");
			scanf("%d",&temp_x);
			printf("y : ");
			scanf("%d",&temp_y);
			if ( ( (2==temp_x-x || 1==temp_x-x || (-1)==temp_x-x ||(-2)==temp_x-x) && 0==temp_y-y) && (temp_x<8 && temp_x>=0 && temp_y>=0 && temp_y<8) && (area[temp_x][temp_y]==-1) )
				break;
			else if(0==temp_x-x && 0==temp_y-y && area[temp_x][temp_y]!=-1)
				break;
			else if ( ( (2==temp_y-y || 1==temp_y-y || (-1)==temp_y-y ||(-2)==temp_y-y) && 0==temp_x-x) && (temp_x<8 && temp_x>=0 && temp_y>=0 && temp_y<8) && (area[temp_x][temp_y]==-1))
				break;
		}
		while(1);
		area[temp_x][temp_y]=area[x][y];
		control_user_or_cmp[temp_x][temp_y]=1;
		pokemon_staminas[temp_x][temp_y]=pokemon_staminas[x][y];
		if ( !(temp_x==x && temp_y==y) )
		{
			area[x][y]=-1;
			control_user_or_cmp[x][y]=-1;
			pokemon_staminas[x][y]=-1;
		}

	}


	if (control==2)
	{
		printf("Computer Move(Move Range '1 or 2')...\n");
		do{
			direction=1+rand()%4;
			if (direction==1)
			{
				cmp_move_range=0+rand()%3;
				temp_x=x-cmp_move_range;
				temp_y=y;
			}
			if (direction==2)
			{
				cmp_move_range=0+rand()%3;
				temp_x=x+cmp_move_range;
				temp_y=y;

			}
			if (direction==3)
			{
				cmp_move_range=0+rand()%3;
				temp_y=y-cmp_move_range;
				temp_x=x;

			}
			if (direction==4)
			{
				cmp_move_range=0+rand()%3;
				temp_y=y+cmp_move_range;
				temp_x=x;

			}

			if ( ( (2==temp_x-x || 1==temp_x-x || 0==temp_x-x || (-1)==temp_x-x ||(-2)==temp_x-x) && 0==temp_y-y) && (temp_x<8 && temp_x>=0 && temp_y>=0 && temp_y<8) && (area[temp_x][temp_y]==-1) )
				break;
			else if ( ( (2==temp_y-y || 1==temp_y-y || (-1)==temp_y-y ||(-2)==temp_y-y) && 0==temp_x-x) && (temp_x<8 && temp_x>=0 && temp_y>=0 && temp_y<8) && (area[temp_x][temp_y]==-1))
				break;
		}
		while(1);
		area[temp_x][temp_y]=area[x][y];
		control_user_or_cmp[temp_x][temp_y]=2;
		pokemon_staminas[temp_x][temp_y]=pokemon_staminas[x][y];

		if ( !(temp_x==x && temp_y==y) )
		{
			area[x][y]=-1;
			control_user_or_cmp[x][y]=-1;
			pokemon_staminas[x][y]=-1;
		}
	}

	//Lineer attack
	if (type[pokemon_selection]==1)
	{
		for (i = 1, j = 0; i <= range[pokemon_selection] ; i++)
		{

			if (temp_x-i>=0)
			{
				x=temp_x-i;
				y=temp_y;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					linear_attack[j][0]=temp_x-x;
					linear_attack[j][1]=x;
					linear_attack[j][2]=y;
					j++;
				}
			}
			if (temp_x+i<8)
			{
				x=temp_x+i;
				y=temp_y;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					linear_attack[j][0]=x-temp_x;
					linear_attack[j][1]=x;
					linear_attack[j][2]=y;
					j++;
				}
			}
			if (temp_y-i>=0)
			{
				y=temp_y-i;
				x=temp_x;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					linear_attack[j][0]=temp_y-y;
					linear_attack[j][1]=x;
					linear_attack[j][2]=y;
					j++;
				}
			}
			if (temp_y+i<8)
			{
				y=temp_y+i;
				x=temp_x;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					linear_attack[j][0]=y-temp_y;
					linear_attack[j][1]=x;
					linear_attack[j][2]=y;
					j++;
				}
			}
		}
		temp=linear_attack[0][0];
		for (i = 0; linear_attack[i][0]!=-1 && i<4; i++)
		{
			for (j = 0; j < i; j++)
			{
				if (linear_attack[i][0]<linear_attack[j][0])
				{
					temp=linear_attack[i][0];				
				}
			}
		}

		for (i = 0; linear_attack[i][0]!=-1 && i<4; i++)
		{
			if (linear_attack[i][0]==temp)
			{
				pokemon_staminas[linear_attack[i][1]][linear_attack[i][2]]-=attack_power[pokemon_selection];

				if (pokemon_staminas[linear_attack[i][1]][linear_attack[i][2]]<=0)
				{
					for (j = 0; j < 4; j++)
					{
						if(user_or_cmp_Pokemons[j]==area[linear_attack[i][1]][linear_attack[i][2]]){
							user_or_cmp_Pokemons[j]='\n';
							break;
						}
					}
					pokemon_staminas[linear_attack[i][1]][linear_attack[i][2]]=-1;
					area[linear_attack[i][1]][linear_attack[i][2]]=-1;
					control_user_or_cmp[linear_attack[i][1]][linear_attack[i][2]]=-1;
				}
			}
		}

	}
	//Quadratic attack
	if (type[pokemon_selection]==0)
	{
		for (i = 1 ; i <= range[pokemon_selection] ; i++)
		{

			if (temp_x-i>=0)
			{
				x=temp_x-i;
				y=temp_y;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					pokemon_staminas[x][y]-=attack_power[pokemon_selection];
					if (pokemon_staminas[x][y]<=0)
					{
						for (j = 0; j < 4; j++)
						{
							if(user_or_cmp_Pokemons[j]==area[x][y]){
								user_or_cmp_Pokemons[j]='\n';
								break;
							}
						}
						pokemon_staminas[x][y]=-1;
						area[x][y]=-1;
						control_user_or_cmp[x][y]=-1;
					}
				}
			}
			if (temp_y-i>=0)
			{
				y=temp_y-i;
				x=temp_x;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					pokemon_staminas[x][y]-=attack_power[pokemon_selection];
					if (pokemon_staminas[x][y]<=0)
					{
						for (j = 0; j < 4; j++)
						{
							if(user_or_cmp_Pokemons[j]==area[x][y]){
								user_or_cmp_Pokemons[j]='\n';
								break;
							}
						}
						pokemon_staminas[x][y]=-1;
						area[x][y]=-1;
						control_user_or_cmp[x][y]=-1;
					}
				}
			}

			if (temp_y-i>=0 && temp_x-i>=0)
			{
				x=temp_x-i;
				y=temp_y-i;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					pokemon_staminas[x][y]-=attack_power[pokemon_selection];
					if (pokemon_staminas[x][y]<=0)
					{
						for (j = 0; j < 4; j++)
						{
							if(user_or_cmp_Pokemons[j]==area[x][y]){
								user_or_cmp_Pokemons[j]='\n';
								break;
							}
						}
						pokemon_staminas[x][y]=-1;
						area[x][y]=-1;
						control_user_or_cmp[x][y]=-1;
					}
				}
			}
			if (temp_y+i<8 && temp_x-i>=0)
			{
				x=temp_x-i;
				y=temp_y+i;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					pokemon_staminas[x][y]-=attack_power[pokemon_selection];
					if (pokemon_staminas[x][y]<=0)
					{
						for (j = 0; j < 4; j++)
						{
							if(user_or_cmp_Pokemons[j]==area[x][y]){
								user_or_cmp_Pokemons[j]='\n';
								break;
							}
						}
						pokemon_staminas[x][y]=-1;
						area[x][y]=-1;
						control_user_or_cmp[x][y]=-1;
					}
				}
			}

			if (temp_x+i<8 )
			{
				x=temp_x+i;
				y=temp_y;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					pokemon_staminas[x][y]-=attack_power[pokemon_selection];
					if (pokemon_staminas[x][y]<=0)
					{
						for (j = 0; j < 4; j++)
						{
							if(user_or_cmp_Pokemons[j]==area[x][y]){
								user_or_cmp_Pokemons[j]='\n';
								break;
							}
						}
						pokemon_staminas[x][y]=-1;
						area[x][y]=-1;
						control_user_or_cmp[x][y]=-1;
					}
				}
			}
			if (temp_y+i<8)
			{
				x=temp_x;
				y=temp_y+i;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					pokemon_staminas[x][y]-=attack_power[pokemon_selection];
					if (pokemon_staminas[x][y]<=0)
					{
						for (j = 0; j < 4; j++)
						{
							if(user_or_cmp_Pokemons[j]==area[x][y]){
								user_or_cmp_Pokemons[j]='\n';
								break;
							}
						}
						pokemon_staminas[x][y]=-1;
						area[x][y]=-1;
						control_user_or_cmp[x][y]=-1;
					}
				}		
			}
			if (temp_x+i<8 && temp_y+i<8)
			{
				x=temp_x+i;
				y=temp_y+i;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					pokemon_staminas[x][y]-=attack_power[pokemon_selection];
					if (pokemon_staminas[x][y]<=0)
					{
						for (j = 0; j < 4; j++)
						{
							if(user_or_cmp_Pokemons[j]==area[x][y]){
								user_or_cmp_Pokemons[j]='\n';
								break;
							}
						}
						pokemon_staminas[x][y]=-1;
						area[x][y]=-1;
						control_user_or_cmp[x][y]=-1;
					}
				}
			}
			if (temp_y-i>=0 && temp_x+i<8)
			{
				x=temp_x+i;
				y=temp_y-i;
				if (area[x][y]!=-1 && control_user_or_cmp[x][y] != control)
				{
					pokemon_staminas[x][y]-=attack_power[pokemon_selection];
					if (pokemon_staminas[x][y]<=0)
					{
						for (j = 0; j < 4; j++)
						{
							if(user_or_cmp_Pokemons[j]==area[x][y]){
								user_or_cmp_Pokemons[j]='\n';
								break;
							}
						}
						pokemon_staminas[x][y]=-1;
						area[x][y]=-1;
						control_user_or_cmp[x][y]=-1;
					}
				}
			}

		}
	}


}

int control_game(pokemon user_Pokemons[4],pokemon cmp_Pokemons[4]){

	int i;

	for (i = 0; i < 4; ++i)
	{
		if (user_Pokemons[i]!='\n')
		{
			printf("\n");
			break;
		}
		else if (i==3)
		{
			return 1;
		}
	}
	for (i = 0; i < 4; ++i)
	{
		if (cmp_Pokemons[i]!='\n')
		{
			printf("\n");
			break;
		}
		else if (i==3)
		{
			return 0;
		}
	}
}

void battle(char Pokemon_name[10][10], int range[10], attack_type type[10], int attack_power[10],int stamina[10],pokemon user_Pokemons[4])
{

	int area[8][8],pokemon_staminas[8][8];
	int flag=-1,control=0;
	int move,pokemon_selection;
	int i,j;
	int x,y;
	int control_user_or_cmp[8][8];
	int game=-1;
	pokemon cmp_Pokemons[4]={'\n','\n','\n','\n'};

	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			area[i][j]=-1;	
			pokemon_staminas[i][j]=-1;
			control_user_or_cmp[i][j]=-1;
		}
	}

	fill_the_cmp_pokemon(cmp_Pokemons);
	first_locate_pokemon_cmp_user(area,Pokemon_name,cmp_Pokemons,user_Pokemons,pokemon_staminas,stamina,control_user_or_cmp);
	show_area(Pokemon_name,area,pokemon_staminas);

	do{

		pokemon_selection=pokemon_choice(Pokemon_name, area,control_user_or_cmp, user_Pokemons, &x, &y, 1);
		printf("%s= x:%d y:%d \n",Pokemon_name[pokemon_selection],x,y );

		move_and_attack(area,control_user_or_cmp,pokemon_staminas,cmp_Pokemons,pokemon_selection,x,y,range,type,attack_power,stamina,1);
		game=control_game(user_Pokemons,cmp_Pokemons);

		if(game==1){
			printf("Computer Is The Win ! ! !\n");
			break;
		}
		if (game==0)
		{
			printf("User Is The Win ! ! !\n");
			break;
		}

		pokemon_selection=pokemon_choice(Pokemon_name, area,control_user_or_cmp, cmp_Pokemons, &x, &y, 2);
		printf("%s= x:%d y:%d \n",Pokemon_name[pokemon_selection],x,y );

		move_and_attack(area,control_user_or_cmp,pokemon_staminas,user_Pokemons,pokemon_selection,x,y,range,type,attack_power,stamina,2);

		show_area(Pokemon_name,area,pokemon_staminas);
		game=control_game(user_Pokemons,cmp_Pokemons);


		if(game==1){
			printf("\n\nComputer Is The Win ! ! !\n");
			break;
		}
		if (game==0)
		{
			printf("\n\nUser Is The Win ! ! !\n");
			break;
		}
	}
	while(1);

		show_area(Pokemon_name,area,pokemon_staminas);
}


void show_area (char Pokemon_name[10][10],int area[8][8],int pokemon_staminas[8][8])
{
	int i,j,k;
	for (j= 0; j < 97; j++)
	{
		printf("-");
	}
	printf("\n");

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			printf("|    ");
			if (area[i][j]!=-1)
			{
				for (k = 0; k < 3; k++)
				{
					printf("%c",Pokemon_name[area[i][j]][k]);
				}
				printf("    ");
			}
			else
				printf("       ");
		}
		printf("|\n");

		for (j = 0; j < 8; j++)
		{
			printf("|   ");
			if (pokemon_staminas[i][j]!=-1)
			{
				printf("(%4d)  ",pokemon_staminas[i][j]);
			}
			else
				printf("        ");
		}
		printf("|\n");

		for (j= 0; j < 97; j++)
		{
			printf("-");
		}
		printf("\n");
	}
}
