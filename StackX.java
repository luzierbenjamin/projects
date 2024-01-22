package assign2_374;

public class StackX {

		   private int maxSize;        // size of stack array
		   private char[] stackArray;
		   private int top;            // top of stack
		   
		   public String toString()
		   {
			   String elements = "[ ";
			   for (int i=0; i<top; i++)
				   elements += stackArray[i] + " ";
			   elements += "]";
			   return elements;
		   }
		   
		
		   public StackX(int s)         // constructor
		      {
		      maxSize = s;             // set array size
		      stackArray = new char[maxSize];  // create array
		      top = -1;                // no items yet
		      }
		
		   public void push(char j)    // put item on top of stack
		      {
		      stackArray[++top] = j;     // increment top, insert item
		      }

		   public char pop()           // take item from top of stack
		      {
		      return stackArray[top--];  // access item, decrement top
		      }
		
		   public char peek()          // peek at top of stack
		      {
		      return stackArray[top];
		      }
	
		   public boolean isEmpty()    // true if stack is empty
		      {
		      return (top == -1);
		      }
		
		   public boolean isFull()     // true if stack is full
		      {
		      return (top == maxSize-1);
		      }
	
		   }  