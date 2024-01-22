package assignment1_374;

//Benjamin Luzier
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


class sort
{
private Person[] a;        //Array to have player's inserted into.        
private int nElems;    
String lastName, firstName, College; //Person attribute's
int number, age, weight;



public sort(int max)       //Constructor for sort.   
   {
   a = new Person[max];                 
   nElems = 0;                        
   }
public static void printPlayer(Person player) { //Prints a player with the respective attributes.
	System.out.printf("%s %s\t\t%d\t%s\t%s\t%d\t%d\t%s ",player.firstName,  player.lastName, player.number, player.Position, player.Height, player.weight, player.age, player.Exp);
	System.out.println(player.College);
	
}

public void insert(Person player)   //Inserts a player into the array.
{
a[nElems] = new Person(player.firstName, player.lastName, player.number, player.Position, player.Height, player.age, player.weight, player.Exp, player.College);             
nElems++;                      
}

public void display(int count)  //Calls the print player function to print each player within the array.            
   {
	for (int j=0; j< count; j++)
	{
		printPlayer(a[j]);
	}
   }

public void bubbleSort(int choice) //Depending on the user input of choice, it sorts by number, age, or weight, using a bubble sort method.
{
   int out, in;

   if (choice == 0)
   {
   for(out=nElems-1; out>1; out--)   
      for(in=0; in<out; in++)        
         if( a[in].number > a[in+1].number)       
            swap(in, in+1);  
   }
   if (choice == 1)
   {
   for(out=nElems-1; out>1; out--)   
      for(in=0; in<out; in++)        
         if( a[in].age > a[in+1].age )       
            swap(in, in+1);  
   }
   if (choice == 2)
   {
   for(out=nElems-1; out>1; out--)   
      for(in=0; in<out; in++)        
         if( a[in].weight > a[in+1].weight )       
            swap(in, in+1);  
   }
}  

public void selectionSort(int choice)//Depending on the user input of choice, it uses a selection sort method to sort players by their first name, last name, or college.
{
int out, in, min;

	if (choice==3)
	{
		for(out=0; out<nElems-1; out++)   
		{
			min = out;                     
			for(in=out+1; in<nElems; in++) 
				if(a[in].firstName.compareTo(a[min].firstName) < 0 )         
					min = in;               
			swap(out, min);                
		}
	}
	if (choice==4)
	{
		for(out=0; out<nElems-1; out++)   
		{
			min = out;                     
			for(in=out+1; in<nElems; in++) 
				if(a[in].lastName.compareTo(a[min].lastName) < 0 )         
					min = in;               
			swap(out, min);                
		}
	}
	if (choice==5)
	{
		for(out=0; out<nElems-1; out++)   
		{
			min = out;                     
			for(in=out+1; in<nElems; in++) 
				if(a[in].College.compareTo(a[min].College) < 0 )         
					min = in;               
			swap(out, min);                
		}
	}
}  

private void swap(int one, int two) //Is called by both sorting methods to swap two array values if the prerequisites are met.
   {
   Person temp = a[one];
   a[one] = a[two];
   a[two] = temp;
   }

}  

class sortApp
{
	
	public static int readData(Person [] player) throws FileNotFoundException //Is used to read the data from the text file and create a value in the array for each person.
	{
		int count =0;
		String lastName, firstName, College, Position, Height, Exp;
		int number, age, weight; 
		Scanner sc = new Scanner (new File("browns.txt"));
		while (sc.hasNextLine()) {
			firstName= new String();
			firstName = sc.next();
			lastName = new String();
			lastName=sc.next();
			number = sc.nextInt();
			Position = new String();
			Position = sc.next();
			Height = new String();
			Height = sc.next();
			weight = sc.nextInt();
			age = sc.nextInt();
			Exp = new String();
			Exp= sc.next();
			College = new String();
			College = sc.nextLine();
			
			
			
			
			
			player[count]= new Person(firstName, lastName, number, Position, Height, age, weight, Exp, College);
			count++;
			}
		sc.close();
		return count;
	}
public static void main(String[] args)throws FileNotFoundException
   { 
	Person [] player = new Person[100];
   int maxSize = 100;           
   sort arr;   //Creates the array object which can be used by the sorting methods.             
   arr = new sort(maxSize);
   int count=0;
	int field=1;
	int i;
	Scanner keyboard=new Scanner(System.in); //Used to read the file into the array.
	Scanner scan = new Scanner(System.in); //Used to take in user input.
	count=readData(player);
   int choice;
   
   for (i=0; i < count; i++)
   {
	   arr.insert(player[i]); //Inserts the entire array of players into the array which can be sorted.
   }

 
   do { //Recieves the user input and sorts it based on their request, until they enter a 6 to quit.
	   System.out.println("Cleveland Browns Roster\n0)Sort by player number.\n1)Sort by age\n2)Sort by weight.\n3)Sort by first name.\n4)Sort by last name.\n5)Sort by college.\n6)Quit.");
	   choice = scan.nextInt(); 
	   if (choice >= 0 && choice <= 2)
	   {
		   arr.bubbleSort(choice); //Calls the bubble sort to sort the ar array.
		   arr.display(count); //Displays the entire array of players.
	   }
	   else if ( choice >= 3 && choice <= 5) 
	   {
		   arr.selectionSort(choice); //Calls the selection sort to sort the ar array.
		   arr.display(count);
	   }
	   else if (choice == 0)
	   {
		   break;
	   }
	   else if (choice==6)
	   {
		   System.out.print("Bye!");
	   }
	   else
	   {
		   System.out.println("Invalid input");
	   }
	   
   
   } while (choice != 6);
   }  
}  

