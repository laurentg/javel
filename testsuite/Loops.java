
public class Loops {

	public int f() {

		int i = 0, j = 5;

		while (i < 10) {

			i += 1;
			j += i;
		}
		return j;
	}

	public int g() {

		int i = 0;

		do {
			i += 1;

		} while (i < 10);

		return i;
	}
}
