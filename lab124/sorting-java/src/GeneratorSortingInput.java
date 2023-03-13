import java.io.*;

public class GeneratorSortingInput {
	public static void main( String[] args ) throws Exception
	{
		final int MAX = 10000;
		java.util.Random rand = new java.util.Random(5);
		
		System.out.println(4); 
		int numItems = 100;
		
		System.out.println(numItems);
		for (int i = 0; i < numItems; ++i)
		{
			System.out.print((rand.nextInt(MAX)) + " ");
		}
		System.out.println();
		

		numItems = 1000;
		System.out.println(numItems);
		for (int i = 0; i < numItems; ++i)
		{
			System.out.print((rand.nextInt(MAX)) + " ");
		}
		System.out.println();

		numItems = 10000;
		System.out.print(numItems);
		for (int i = 0; i < numItems; ++i)
		{
			if (i % 10000 == 0)
				System.out.println();
			System.out.print((rand.nextInt(MAX)) + " ");
		}
		System.out.println();
		
		numItems = 100000;
		System.out.print(numItems);
		for (int i = 0; i < numItems; ++i)
		{
			if (i % 10000 == 0)
				System.out.println();
			System.out.print((rand.nextInt(MAX)) + " ");
		}
		System.out.println();

	}

}
