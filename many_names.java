package assignment5;
import java.text.DecimalFormat;

public class many_names {
	private int length;
	private int width;

// Default constructor
	public many_names() {
		length = 8;
		width = 8;
	}

// Constructor with one parameter
	public many_names(int len) {
		length = len;
		width = 8;
	}

// Constructor with two parameters
	public many_names(int len, int wid) {
		length = len;
		width = wid;
	}

// Void display method Precondition: Is called by main() Role: role is to Print the display Postcondition: Display with length * width
	public void display() {
		System.out.println("From void display() function, Area = " + length * width);
	}

// Display method with one parameter Is called by main() Role: role is to Print the display, when there is one parameter Postcondition: Display one(which is a parameter) * width
	public void display(int one) {
		System.out.println("From int display() function, Area = " + one * width);
	}

// Display method with two parameters Is called by main() Role: role is to Print the display with 2 parameters given Postcondition: Display with one * two using both parameters given
	public void display(int one, int two) {
		System.out.println("From two int display() function, Area = " + one * two);
	}

// Display method with one double parameter Is called by main() Role: role is to Print the display with a double parameter given Postcondition: Display with the double parameter * width
	public void display(double number) {
		DecimalFormat decimalFormat = new DecimalFormat("#.####");
		System.out.println("From float display() function, Area = " + decimalFormat.format(number * width));
	}
	}

	class SRU {

		private double real;
		private double imag;

// Constructor with default values
		public SRU(double r, double i) {
			real = r;
			imag = i;
		}

// Print method Is called by main() Role: role is to Print the overloaded operator Gross = Postcondition: Display with both real and imag values
		public void print() {
			System.out.println("*** Overloaded Operator ***");
			System.out.println("Gross =" + (int)real + " + i" + (int)imag);
		}

// Overloaded addition operator Is called by main() Role: role is to add cq.real and c2.real, c1.imag and c2.imag Postcondition: Returns the added results to main
		public static SRU add(SRU c1, SRU c2) {
			return new SRU(c1.real + c2.real, c1.imag + c2.imag);
		}
	}

	