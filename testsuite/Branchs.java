
/** Java test suite for Javel.
    Copyright (c) 2002 Laurent Gregoire - laurent.gregoire@icam.fr
    Test for: various branches operations (if/else, while, do, for)
    and dead code optimization.  */

public class Branchs {

	/** Test for if (cond) {  } */
	public int f1(int i) {
		int j = i;
		if (i <= 10) {
			j = i;
		}
		return j;
	}

	/** Test for if (cond) {  } else {  } */
	public int f2(int i) {
		int j = 0;
		if (i > 10) {
			j = 10;
		} else {
			j = i;
		}
		return j;
	}

	/** Dead code is optimized away by some compilers.
	    Determine which level of cleverness it is... */
	public int f3() {
		int someVariable = 1;
		if (false) {
			/** Removed by jikes 1.12 and kjc 1.4F */
			someVariable = 0;
		}
		if (0 == 1) {
			/** Removed by jikes 1.12 and kjc 1.4F */
			someVariable = 1;
		}
		int i = 0;
		if (i == 1) {
			/** NOT removed by jikes 1.12 and kjc 1.4F,
			    Test NOT removed by jikes 1.12 and kjc 1.4F */
			someVariable = 2;
		}
		int j = 0;
		if (true) {
			/** Test removed by jikes 1.12 and kjc 1.4F */
			j = 1;
		}
		if (j == 0) {
			/** NOT removed by jikes 1.12 and kjc 1.4F,
			    Test NOT removed by jikes 1.12 and kjc 1.4F */
			someVariable = 3;
		}
		return someVariable;
	}
}

