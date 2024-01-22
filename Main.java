package assignment5;

public class Main { //Precondition: runs automatically Role: operate the main code Postcondition: run the source code

	public static void main(String[] args) {
		many_names small = new many_names();
		many_names medium = new many_names(10);
		many_names large = new many_names(12, 15);

		int gross = 144;
		double pi = 3.1415;
		double payroll = 12.50;

		System.out.println("Guess, which function that has been invoked?");
		System.out.println("------------------------------------------");

		System.out.println("small.display(void)");
		small.display();

		System.out.println("\nsmall.display(100)");
		small.display(100);

	System.out.println("\nsmall.display(gross, 100)"); // Note: Java does not support multiple parameters in this way
	small.display(gross, 100); // You may need to modify this call or the method signature

	System.out.println("\nsmall.display(payroll)");
	small.display((payroll));

	System.out.println("\nmedium.display(void)");
	medium.display();

	System.out.println("\nlarge.display(pi)");
	large.display(pi);

// An example call to "operator+"
	SRU CS1 = new SRU(10, 15);
	SRU CS2 = new SRU(10, 15);
	SRU Gross = SRU.add(CS1, CS2);
	Gross.print();

	System.out.println("Gross= " + (payroll + pi));
	}

}
