
/** Java test suite for Javel.
    Copyright (c) 2002 Laurent Gregoire - laurent.gregoire@icam.fr
    Test for: various comparison operations (ifx, if_icmpx, ifnull...) */

public class Compare {

	/** Test if_icmpx */
	public int f1(int i, int j) {
		int k = 0;
		if (i == j) { k = 1; }
		if (i != j) { k = 2; }
		if (i <  j) { k = 3; }
		if (i >  j) { k = 4; }
		if (i <= j) { k = 5; }
		if (i >= j) { k = 6; }
		return k;
	}

	/** Test if_x */
	public int f2(int i) {
		int k = 0;
		if (i == 0) { k = 1; }
		if (i != 0) { k = 2; }
		if (i <  0) { k = 3; }
		if (i >  0) { k = 4; }
		if (i <= 0) { k = 5; }
		if (i >= 0) { k = 6; }
		return k;
	}

	/** Test ifnull, ifnonnull */
	public int f3(Compare t) {
		int k = 0;
		if (t == null) { k = 1; }
		if (t != null) { k = 2; }
		return k;
	}

	/** Test complex operations */
	public int f4(int i, int j, int k) {
		int l = 0;
		if (i == j && j == k) { l = 1; }
		if (i == j || j == k) { l = 2; }
		if (!(i > j || i < j)) { l = 3; }
		return l;
	}

	/** Test reference comparison */
	public int f5(String s1, String s2) {
		int k = 0;
		if (s1 == s2) { k = 1; }
		if (s1 != s2) { k = 2; }
		return k;
	}

	/** Test lcmp */
	public int f6(long i, long j) {
		int k = 0;
		if (i > j) { k = 1; }
		if (i < j) { k = 2; }
		if (i >= j) { k = 1; }
		if (i <= j) { k = 2; }
		return k;
	}
}

