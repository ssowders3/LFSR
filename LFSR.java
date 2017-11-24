import java.util.*;
import java.io.*;
import java.math.*;


public class LFSR {
    public static void main (String[] args) {

	      LFSR(10);
	      LCG(10);
        pi_estimator();
    }


  public static double LFSR(int size) {
  int start = 12456723;
	int[] headCount = new int[25];
	System.out.println("LFSR random numbers:");
	double ans = 0;
	int count = 0;
	int countT = 0;
	for (int i = 0; i < size; i++) {
	    //System.out.println(Integer.toBinaryString(start));
	    int bit24 = start >> 24;
	    bit24 = bit24 & 1;
	    int bit23 = start >> 23;
	    bit23 = bit23 & 1;
	    int bit22 = start >> 22;
	    bit22 = bit22 & 1;
	    int bit17 = start >> 17;
	    bit17 = bit17 & 1;
	    int XOR = bit24 ^ bit23 ^ bit22 ^ bit17;
	    start = start << 1 ^ XOR;
	    start = start % (int) Math.pow(2,24);
	    ans = start/Math.pow(2,24);
      // double newAns = ans * 10000000;
      // newAns = Math.floor(newAns);
      // start = (int) newAns;
	    //System.out.println(Integer.toBinaryString(start));
	    System.out.println(ans);

	    if ( ans > .5) {
		      count++;
		      countT = 0;
	    } else {
		      countT++;
		        if (countT < 2 && count > 0) {
		            headCount[count - 1] = headCount[count - 1] + 1;
		            count = 0;
		        }
	    }
	  }
	if (count > 0) {
	    headCount[count - 1] = headCount[count - 1] + 1;

	}

	for (int s = 0; s < 25; s++) {
	    System.out.print(headCount[s] + " ");
	}
  System.out.println(ans);
  return 0.0;
	//System.out.println();
    }

  public static void LCG(int size) {
	System.out.println("LCG random numbers:");
	int start = 12456723;
	double ans;
	int[] headCount = new int[25];
	int count = 0;
	int countT = 0;
	for(int i = 0; i < size; i++) {
	    start =(int) (1140671485*start + 128201163) % (int) Math.pow(2,24);
	    ans = Math.abs(start / Math.pow(2,24));
      // double newAns = ans * 10000000;
      // newAns = Math.floor(newAns);
      // start = (int) newAns;
	    if ( ans > .5) {
		      count++;
		      countT = 0;
		      //System.out.println("H");
	    } else {
		      //System.out.println("T");
		      countT++;
		      if (countT < 2 && count > 0) {
		          headCount[count - 1] = headCount[count - 1] + 1;
		            count = 0;
		      }
	    }
	    System.out.println(ans);
	}
	if (count > 0) {
	    headCount[count - 1] = headCount[count - 1] + 1;
	}
	for (int s = 0; s < 25; s++) {
	    System.out.print(headCount[s] + " ");
	}
	//System.out.println();

    }


    public static void pi_estimator() {
        long z=0, n=1000000;
        double x, y, pi;

        Random rnd = new Random();

        for (long i=0; i < n; ++i) {
          x = rnd.nextDouble();
          y = rnd.nextDouble();
          if (Math.sqrt(x*x + y*y) <= 1) z++;
        }

        pi = 4.0*z/n;
        System.out.println("Pi is estimated to be " + pi);


    }
}
