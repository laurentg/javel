
/** Java test suite for Javel.
    Copyright (c) 2002 Laurent Gregoire - laurent.gregoire@icam.fr
    Test for: various conversions (i2l, l2i...) */

public class Conversions {

	/** Test for i2l, l2i. */
	public void f1() {
		int i1 = 1, i2 = 3;
		long l1 = i1 + i2;
		int i3 = (int)l1;
	}
}
