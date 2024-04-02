using System;


// NameSpace
namespace NumberGuesser
{
    // Main Class
    internal class Program
    {
        //Entry Point Method
        static void Main(string[] args)
        {
            getAppInfo(); //Run intro function

            string name = greetUser(); //get username and greet
            
            while (true)
            {
                //Set number
                //Create new random object
                Random random = new Random();
                int correctNumber = random.Next(1, 11);

                //set guess variable
                int guessVar = 0;

                //Ask user for number
                Console.WriteLine("Guess a number between 1 & 10!");

                //While guess is not correct        
                while (guessVar != correctNumber)
                {
                    //get user input
                    string inputNum = Console.ReadLine();

                    //make sure it is correct value
                    if (!int.TryParse(inputNum, out guessVar))
                    {
                        //print error message
                        printColorMessage(ConsoleColor.Red, "Please enter a valid integer.");
                        continue;
                    }

                    //Cast to int and put in guess
                    guessVar = Int32.Parse(inputNum);

                    //Match Guess to answer
                    if (guessVar != correctNumber)
                    {
                        //inform unsuccesfull attempt
                        printColorMessage(ConsoleColor.Red, guessVar + " is not the correct number, try again!");
                       
              
                    }
                }

                //Output Success message!
                printColorMessage(ConsoleColor.Yellow, "Congratulations " + name + "! " + guessVar + " is the correct number! Thanks for playing!");

                //Ask to play again
                Console.WriteLine("Play again? [Y or N]");

                //get response
                string response = Console.ReadLine().ToUpper();

                if (response == "Y")
                {
                    continue;
                }
                else if (response == "N")
                {
                    return;
                }
                else
                {
                    return;
                }
            }
        }

        static void getAppInfo()
        {
            //Start//
            string appName = "Number Guesser";
            string appVersion = "1.0.0";
            string appAuthor = "Benjamin Luzier";

            //Change text color for header
            Console.ForegroundColor = ConsoleColor.Green;

            //write out app info
            Console.WriteLine("{0}: Version {1} by {2}", appName, appVersion, appAuthor);

            //reset text color
            Console.ResetColor();
        }

        static string greetUser()
        {
            //ask users name
            Console.WriteLine("What is your name?");

            //Get user input
            string name = Console.ReadLine();

            Console.WriteLine("Hello {0}, lets play a game!", name);

            return name;
        }

        //Print Colored message
        static void printColorMessage(ConsoleColor color, string message)
        {
            Console.ForegroundColor = color;
            Console.WriteLine(message);
            Console.ResetColor();
        }
    }
}
