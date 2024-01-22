package assign2_374;
import java.util.Scanner;

public class PalindromeApp {

	public static void main(String[] args) {
		   Scanner kbd = new Scanner(System.in);
		
			System.out.print("Enter a phrase (or 'quit'): ");
			String phrase = kbd.nextLine();
			while (!phrase.equals("quit"))
			{
				System.out.print(phrase);
				if (isPalindromeQUEUE(phrase))
					System.out.println(" is a palindrome");
				else
					System.out.println(" is NOT a palindrome");
				System.out.print("Enter a phrase (or 'quit'): ");
			  	phrase = kbd.nextLine();
			}
		}
		
		// the input parameter "word" consists of zero or more characters
		// this function determines if the initial word is a palindrome (true)
		// or not (false)
		private static boolean isPalindromeSTACK(String word)
		{
			word = word.toLowerCase();	//Forces lower case, removes punctuation, and spaces. 
			word = word.replaceAll("\\s+", ""); 
			word = word.replaceAll("[^a-zA-Z]", "");
			String reversed;	
			int stackSize = word.length(); //Creates the max size of the stack to the length of the word.
			int j;
			char ch; //Each char in the word.
			StackX theStack = new StackX(stackSize); //Creates the stack
			for (j=0; j < word.length(); j++)
			{
				ch = word.charAt(j); //Add the characters to the stack.
				theStack.push(ch);
			}
			reversed = "";
			while (!theStack.isEmpty())
			{
				ch = theStack.pop();
				reversed = reversed + ch; //Reverses the string by having pop return each value into the reversed string.
			}
			return reversed.equals(word); //Returns true if the reversed and word are equal and false if not.
		}
		private static boolean isPalindromeQUEUE(String word)
		{
			word = word.toLowerCase(); //1
			word = word.replaceAll("\\s+", ""); //1
			word = word.replaceAll("[^a-zA-Z]", ""); //1
			int i; //1
			char ch; //1
			String reversed; //1
			reversed = ""; //1
			int queueSize = word.length(); //1
			Queue theQueue = new Queue(queueSize); //1
			for (i=0; i < word.length(); i++) //n
			{
				ch = word.charAt(i); //n
				theQueue.insert(ch); //n
			}
			while (!theQueue.isEmpty())   //n 
			{
				ch = theQueue.remove();   //n
				reversed = ch + reversed;  //n
			}
			
			
			
			return reversed.equals(word); //1
		}

	}