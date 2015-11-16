
/** Java test suite for Javel.
    Copyright (c) 2002 Laurent Gregoire - laurent.gregoire@icam.fr
    Test for: Various constant / variable loading and storing operations. */

public class LoadStore {

	public void f1() {
		/** Test for iconst_n */
		int im1 = -1;
		int i0 = 0;
		int i1 = 1;
		int i2 = 2;
		int i3 = 3;
		int i4 = 4;
		int i5 = 5;
		/** Test for bipush */
		int i6 = 6;
		int i7 = -2;
		int i8 = 127;
		int i9 = -127;
		/** Test for sipush */
		int i10 = 31987;
		int i11 = -20456;
	}

	public void f2() {
		/** Test for lconst_n */
		long l1 = 0;
		long l2 = 1;
	}

	public void f3() {
		/** Test for aconst_null */
		String s = null;
	}
}

