#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

struct Stats
{
   int health; 
};

void displayOptions();
void getChoice( char &choice);
void getDamage( int &damage, int &i);
void heroAttack(Stats &enemy, int &i); 
void enemyAttack(Stats &hero, int &i);
void runAttempt( bool &runSuccessful);
void use(bool &first);
void getStats( Stats hero, Stats enemy);

/**********************************************************************
 * 
 ***********************************************************************/
int main()
{
   
   Stats hero;
   hero.health = 25;
   Stats enemy;
   enemy.health = 25;
   int i = 0;
   bool runSuccessful = false;
   bool first = true;
   
   displayOptions();
      
   // while someone is still alive battle is still ongoing
   while ( enemy.health > 0 && hero.health > 0 && runSuccessful == false)
   {
      // get what the player does
      char choice;
      getChoice(choice);
      
      // try to run away
      if (choice == 'R')
      {
         runAttempt(runSuccessful);
      }

      // display battle options
      if (choice == 'O')
         displayOptions();
         
      // hero attacks
      if (choice == 'A')
      {
         heroAttack(enemy, i);
      }

      // Use
      if (choice == 'U')
      {
         use(first);
      }

      if ( choice == 'S' )
         getStats(hero, enemy);
      
      // enemy's turn
      if (enemy.health > 0 && runSuccessful == false && choice != 'O' && choice != 'S')
         enemyAttack(hero, i);
      
   }
   
   return 0;
}

/**********************************************************************
 * Function: displayOptions
 * Purpose: Display the options
 ***********************************************************************/
void displayOptions()
{
   cout << "Battle Options\n"
        << "\tOptions" << setw(6) << "["
        << "\E[22;32m" << "O" << "\E[0m" << "]\n"
        << "\tAttack" << setw(7) << "["
        << "\E[22;32m" << "A" << "\E[0m" << "]\n"
        << "\tUse Item" << setw(5) << "["
        << "\E[22;32m" << "U" << "\E[0m" << "]\n"
        << "\tRun" << setw(10) << "[" 
        << "\E[22;32m" << "R" << "\E[0m" << "]\n"
        << "\tCheck Stats" << setw(2) << "["
        << "\E[22;32m" << "S" << "\E[0m" << "]\n\n";;
}

/**********************************************************************
 * Function: getChoice
 * Purpose: Get whether the player wants to attack.
 ***********************************************************************/
void getChoice(char &choice)
{
   bool error = true;

   while ( error == true)
   {
      cout << "Your turn: ";
      cin >> choice;

      error = false;

      switch (choice)
      {
         case 'O':
            error = false;
            break;
         case 'A':
            error = false;
            break;
         case 'U':
            error = false;
            break;
         case 'R':
            error = false;
            break;
         case 'S':
            error = false;
            break;
         default:
            error = true;         
      }
      
      if ( choice == true)
         {
            cout << "I didn't understand that,\nplease try again.\n\n";
         }
   }
}

/**********************************************************************
 * Function: runAttempt
 * Purpose: See if the hero can run away
 ***********************************************************************/
void runAttempt( bool &runSuccessful)
{
   srand(time(0));
   int chance = (rand() % 11);
   cout << "You try to run\n\n";

   // You get away
   if ( chance > 2 )
   {
      runSuccessful = true;
      cout << "You manage to get away\n";
   }

   // You don't get away
   else
   {
      runSuccessful = false;
      cout << "You failed to get away\n";
   }
    
}

void use( bool &first)
{
   if ( first == false )
   {
      cout << "Why are you checking again? You already know you\n"
           << "have nothing. Once again, your enemy attacks you\n"
           << "idiot\n\n";
   }

   if (first == true)
   {
      cout << "You have no items you can use\n"
           << "As you stand confused by the laziness of the\n"
           << " programmer, your enemy sees a chance to attack!\n\n";
      first = false;
   }
   
}

void getStats( Stats hero, Stats enemy)
{
   cout << "Hero Health: " << setw(18) << hero.health << endl
        << "Enemy Health: " << setw(17) << enemy.health << endl << endl;
   
}


/**********************************************************************
 * Function: heroAttack
 * Purpose: Determine the damage done by the player
 ***********************************************************************/
void heroAttack(Stats &enemy, int &i)
{

   int enemyDamage;
   
   // get the damage
   getDamage(enemyDamage, i);
   enemy.health -= enemyDamage;

   cout << "You attack the enemy dealing "
        << enemyDamage
        << " points of damage"
        << endl;

   // if the enemy is still alive
   if ( enemy.health > 0 )
   {
      cout << "Enemy is now at "
           << enemy.health
           << " hit points\n\n";
   }

   // if the enemy dies
   else
      cout << "You have killed the enemy\n";
}

/**********************************************************************
 * Function: enemyAttack
 * Purpose: Determine the attack done by the enemy
 ***********************************************************************/
void enemyAttack(Stats &hero, int &i)
{
   int heroDamage;
   // get the damage
   getDamage(heroDamage, i);
   hero.health -= heroDamage;

   cout << "The enemy attacks you dealing "
        << heroDamage
        << " points of damage"
        << endl;

   // if the hero is still alive
   if ( hero.health > 0 )
   {
      cout << "You are now at "
           << hero.health
           << " hit points\n\n";
   }

   // if the hero dies
   else
      cout << "You were slain\n";

}

/**********************************************************************
 * Function: getDamage
 * Purpose: Determine the damage.
 ***********************************************************************/
void getDamage( int &damage, int &i)
{  
   int randomArray[30] =
      {1, 3, 6, 9, 5,
       7, 3, 5, 7, 4,
       2, 3, 6, 8, 2,
       4, 6, 8, 2, 4,
       1, 1, 4, 3, 6,
       8, 2, 4, 6, 8};

   i++;
   srand(time(0));
   damage = (rand() + randomArray[i]) % 11;

   if ( i >= 30)
      i = 0;
}
