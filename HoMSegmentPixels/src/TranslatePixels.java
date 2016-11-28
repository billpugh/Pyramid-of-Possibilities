import java.awt.image.BufferedImage;
import java.io.File;
import java.util.Iterator;

import javax.imageio.ImageIO;


public class TranslatePixels {

	
	static int xOffsets[] = {0, 2, 4, 5, 6, 8, 10};
	static int xMiddleOffsets[] = { 2, 4, 5, 6, 8};
	
	// y offsets are 0..20
	static int yOffsets[] = {0, 1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 19, 20};
	static int yMiddle = 10;
	static int yLast = 20;
	static int yFirst = 0;
	static int xFirst = 0;
	static int xLast = 10;
	static BufferedImage img;
	public static void main(String args[]) throws Exception {
		System.out.printf("%d x %d\n", xOffsets.length, yOffsets.length);
		img = ImageIO.read(new File("digits.png"));
		int width = img.getWidth();
		int height = img.getHeight();
		System.out.printf("Size %d x %d%n",  width, height);
		for(int p = 0; p < 40; p++) {
			System.out.printf("%x ", img.getRGB(p, 0));
		}
		
		System.out.println();
		System.out.println();
		
		System.out.print("{");
		for(int digit = 0; digit < 10; digit++) {
			
			doDigit2(digit);
			if (digit < 9)
				System.out.println(",");
			else
				System.out.println("};");
		}
		
		
		
	}	
	
	static void doDigit1(int digit) {
		int pos = digit == 0 ? 144 : (digit-1)*16;
		System.out.printf("%d:\n", digit);
		for (int y : yOffsets) {
			
		for(int x : xOffsets) {
			int rgb =  img.getRGB(pos+x,  y);
			if (rgb == -1)
				System.out.print(".");
			else
				System.out.print("x");
		}
		System.out.println();
		}
		System.out.println();
		
	}
	
	static void doDigit2(int digit) {
		StringBuilder builder = new StringBuilder("{");
		int pos = digit == 0 ? 144 : (digit-1)*16;
		for(int x : xMiddleOffsets)
			doPixel(pos+x, yFirst, builder);
		
		for(int y : yOffsets)
			doPixel(pos+xLast, y, builder);
		
		for(int x : reverse(xMiddleOffsets))
			doPixel(pos+x, yLast, builder);
		
		for (int y : reverse(yOffsets)) 
			doPixel(pos+xFirst, y, builder);
		
		for(int x : xMiddleOffsets)
			doPixel(pos+x, yMiddle, builder);
		System.out.printf("// %d\n  ", digit);

		builder.setLength(builder.length()-2);;
		builder.append("}");
		System.out.print(builder);
	}

	private static void doPixel(int x, int y, StringBuilder builder) {
		int rgb =  img.getRGB(x,  y);
		if (rgb == -1)
			builder.append("0, ");
		else
			builder.append("1, ");
		
	}
	static Iterable<Integer> reverse(int [] base) {
		return new Reverse(base);
	}
	
	static class Reverse implements Iterable<Integer> {

		final int [] base;
		Reverse(int [] base) {
			this.base = base;
		}
		@Override
		public Iterator<Integer> iterator() {
			return new Iterator<Integer>() {
				int nextIndex = base.length-1;

				@Override
				public boolean hasNext() {
					return nextIndex >= 0;
				}

				@Override
				public Integer next() {
					return base[nextIndex--];
				}

				@Override
				public void remove() {
					throw new UnsupportedOperationException();
				}};
		}
		
	}
	
		

	
}
