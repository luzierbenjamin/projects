package assignment1_374;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Person {
	
		String lastName, firstName, College, Height, Position, Exp;
		int number, age, weight;
		public Person(String fname, String lname, int num, String pos, String h, int w, int a, String e, String col) {
			firstName=new String();
			lastName=new String();
			lastName=lname;
			firstName=fname;
			number=num;
			Position=new String();
			Position = pos;
			Height=new String();
			Height = h;
			age=a;
			weight=w;
			Exp=new String();
			Exp=e;
			College=new String();
			College=col;
		}


		
	}