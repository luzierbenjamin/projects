
import random
import csv
import time
import sys
numquestions= int(input("How many questions would you like? 10/20")) #asks user for 10 or 20 questions
while numquestions not in [10, 20]:
    print("Invalid input. Please enter either 10 or 20.")
    numquestions = int(input("How many questions do you want on the quiz? (10 or 20) "))
start = time.time() #time starts for program
studentanswerlist = [] # stores the student answers into a list to read to file
    
def login(studentdatabase): 
    '''
    Has a user sign in and makes sure it is a valid login, exits program if failed 3 times.
    '''
    while True:
        try:
            studentfirstname = input("First name: ")
            studentlastname = input("Last name:")
            errornum = 0
            studentid = input("Enter ID (must be A followed by 5 numbers): ")
            if errornum == 3:
                print("Exiting program! Bye!")
                exit()
            if studentid[0] != 'A':
                errornum = errornum + 1
                raise ValueError("First character of ID must be A.")
            if len(studentid) != 6:
                errornum = errornum + 1
                raise ValueError("ID length must be 6, A followed by 5 integers")
            student = [studentfirstname, studentlastname, studentid]
            studentdatabase.append(student)
            return student
        except ValueError as ve:
            print("Error: ", ve)

            
def getquizdatabank(filename): 
    '''
    Gets the quizdatabank from the testbank file and returns it
    '''
    quizdatabank = [] # Creates a list for the databank.
    with open (filename, 'r') as file:
        reader = csv.reader(file)
        for line in file: # Reads the file and puts each string, seperated by ',', into each variable then appends it to the databank list.
            question = []
            prompt, solution1, solution2, solution3, answer = line.strip().split(",")
            question.append(prompt)
            question.append(solution1)
            question.append(solution2)
            question.append(solution3)
            question.append(answer)
            quizdatabank.append(question)
    return quizdatabank

def getnewquiz(quizdatabank): 
    '''
    Takes the quizdatabank and finds 10/20 random questions to make a quiz.
    '''
    count = 0
    quiz = [] # Create a new quiz list.
    questionnumbertracker = [] # Track each question so none are repeated.
    starttime = time.time()
    while count < numquestions:
        repeatquestion = False
        randomquestion = random.randint(0, len(quizdatabank)-1) # Gets a random index for a question.
        for index in range(len(questionnumbertracker)): 
            if questionnumbertracker[index] != randomquestion: # Checks if two questions are the same, if they are it doesn't increment count so it repeats.
                repeatquestion == True
        if repeatquestion == False:
            questionnumbertracker.append(randomquestion) #Gets the random question and then adds it to the list.
            quiz.append(quizdatabank[randomquestion])
            count = count + 1
    return quiz
    return numquestions

def displayquiz(quiz): 
    '''
    Takes in the quiz lsit and returns the correct question number.
    '''
    start_displayquiz = time.time()
    print("You have 600 seconds to complete the quiz.")
    while True:
        count = 0
        correctquestions = 0
        validInputs = ['A', 'B', 'C', 'a', 'b', 'c'] #Only accepts A-D as valid inputs
        while count < numquestions and time.time() - start_displayquiz < 600: #Displays the 10/20 questions.
            print("Question ", (count + 1), ".\n", quiz[count][0], "A.", quiz[count][1], "B.", quiz[count][2], "C.", quiz[count][3])
            studentanswer = input("Your answer => ") # Gets each answer individually.
            studentanswerlist.append(studentanswer)
            while studentanswer not in validInputs:
                studentanswer = input("Your answer => ") # Gets each answer individually.
            if studentanswer.lower() == quiz[count][4].lower(): # If they get the question right, it increments correct questions.
                correctquestions = correctquestions + 1
            count = count + 1
            print("Time elapsed currently: ", round(time.time() - start_displayquiz, 2))
        end_displayquiz = time.time()
        elapsed_time_displayquiz = round(end_displayquiz - start_displayquiz, 2)

        
        return correctquestions
        return studentanswerlist


def endOfQuiz(correctquestions, numquestions, student, quiz): 
    '''
    After the quiz is finished, gathers information on the user and stores it into a file
    '''
    if numquestions == 10:
        score= (correctquestions / 10) * 100
        score = round(score, 2)
    if numquestions == 20:
        score = (correctquestions / 20) * 100
        score = round(score, 2)
    print("Your score was " + str(score) + '%')
    end = time.time() #end of timer 
    elapsedTime= end-start 
    print("Your elapsed time was: " + str(elapsedTime) + ' seconds.')
    fileName=student[2] + student[0] + student[1] +".txt" #Write to file
    with open(fileName, 'w') as f:
        f.write("Student ID: " + student[2] + '\n')
        f.write("First Name: " + student[0] + '\n')
        f.write("Last Name: " + student[1] + '\n')
        f.write("Quiz Score: " + str(score) + '\n')
        f.write("Time elapsed: " + str(elapsedTime) + " Seconds" + '\n')
        for line in quiz:
            f.write("Question: " + str(line) + "\n") 
        for ans in studentanswerlist:
            f.write("Your Answer: " + str(ans) + "\n") 
        
        
        
def quitProgram(): 
    '''
    function to either start a new quiz or exit the program
    '''
    while True:
        runagain = input("Enter Q to exit or S to start another Quiz. ") #Restarts Quiz
        if runagain == 'S':
            main()
        elif runagain == 'Q':
            print("Thanks for playing!") #Ends Game
            break
        else:
            print("Invalid input, enter Q or S.")
        
def main():
    studentdatabase = []
    student = login(studentdatabase)
    filename = "testbank.csv" #Filename
    quizdatabank = getquizdatabank(filename)
    quiz = getnewquiz(quizdatabank)
    correctquestions = displayquiz(quiz)
    endOfQuiz(correctquestions, numquestions, student, quiz)
    quitProgram()
    
if __name__ == '__main__':    
    main()