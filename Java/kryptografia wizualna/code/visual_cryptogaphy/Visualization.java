import java.io.*;
import java.util.Random;
import java.awt.Color;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;

public class Visualization {
    String Path4Source = "files/source/";
    String Path4EncFiles = "files/encryted/";
    String Path4DecFiles = "files/decrypted/";

    Random rand = new Random();

    public void encryptionBMP(String fileInText, String fileOutText) throws IOException {
        File fileOut1 = new File(Path4EncFiles + fileOutText + "1" + ".bmp");
        File fileOut2 = new File(Path4EncFiles + fileOutText + "2" + ".bmp");

        File file = new File(Path4Source+fileInText + ".bmp");
        BufferedImage img = ImageIO.read(file);
        BufferedImage imgOut1 = new BufferedImage(2 * img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_RGB);
        BufferedImage imgOut2 = new BufferedImage(2 * img.getWidth(), img.getHeight(), BufferedImage.TYPE_INT_RGB);

        for (int y = 0; y < img.getHeight(); y++) {
            for (int x = 0; x < img.getWidth(); x++) {
                int randVal = rand.nextInt(2);

                int pixel = img.getRGB(x, y);
                Color color = new Color(pixel, true);

                int red = color.getRed();
                int green = color.getGreen();
                int blue = color.getBlue();

                int mainColor = 255 * (((red + green + blue) / 3) / 128);

                Color first = new Color(0);
                Color second = new Color(0);

                if (randVal == 0) {
                    first = Color.black;
                    second = Color.white;
                } else {
                    first = Color.white;
                    second = Color.black;
                }

                if (mainColor == 0) { // black
                    imgOut1.setRGB(2 * x, y, first.getRGB());
                    imgOut1.setRGB(2 * x + 1, y, second.getRGB());
                    imgOut2.setRGB(2 * x, y, second.getRGB());
                    imgOut2.setRGB(2 * x + 1, y, first.getRGB());
                } else { // white
                    imgOut1.setRGB(2 * x, y, first.getRGB());
                    imgOut1.setRGB(2 * x + 1, y, second.getRGB());
                    imgOut2.setRGB(2 * x, y, first.getRGB());
                    imgOut2.setRGB(2 * x + 1, y, second.getRGB());
                }
            }
        }
        ImageIO.write(imgOut1, "bmp", fileOut1);
        ImageIO.write(imgOut2, "bmp", fileOut2);
    }

    public void decryptionBMP(String fileInText1, String fileInText2, String fileOutText, int mode) throws IOException {
        final int NumOfPiexelColors = 4;

        File file1 = new File(Path4Source + fileInText1 + ".bmp");
        File file2 = new File(Path4Source + fileInText2 + ".bmp");
        BufferedImage img1 = ImageIO.read(file1);
        BufferedImage img2 = ImageIO.read(file2);

        if (img1.getHeight() != img2.getHeight() || img1.getWidth() != img2.getWidth())
            throw new IOException();

        File fileOut = new File(Path4DecFiles + fileOutText + ".bmp");
        BufferedImage imgOut = new BufferedImage(img1.getWidth() / 2, img1.getHeight(), BufferedImage.TYPE_INT_RGB);

        for (int y = 0; y < img1.getHeight(); y++) {
            for (int x = 0; x < img1.getWidth(); x += 2) {
                Color[] colors = { // == NumOfPiexelColors
                        new Color(img1.getRGB(x, y), true),
                        new Color(img1.getRGB(x + 1, y), true),
                        new Color(img2.getRGB(x, y), true),
                        new Color(img2.getRGB(x + 1, y), true)
                };
                int[] mainColors = new int[NumOfPiexelColors];

                for (int i = 0; i < NumOfPiexelColors; i++) {
                    mainColors[i] = 0;

                    mainColors[i] += colors[i].getRed();
                    mainColors[i] += colors[i].getBlue();
                    mainColors[i] += colors[i].getGreen();

                    mainColors[i] = 255 * ((mainColors[i] / 3) / 128);
                    mainColors[i] = Math.min(mainColors[i], 255);
                    mainColors[i] = Math.max(mainColors[i], 0);
                }

                int tmp = 0;
                if (mode == 1) {
                    tmp = Math.abs((mainColors[0] + mainColors[2]) / 2
                            - (mainColors[1] + mainColors[3]) / 2);
                } else {
                    tmp = 255 - ((mainColors[0] + mainColors[2]) % 256 + (mainColors[1] + mainColors[3]) % 256) / 2;
                }
                imgOut.setRGB(x / 2, y, new Color(tmp, tmp, tmp).getRGB());
            }
        }
        ImageIO.write(imgOut, "bmp", fileOut);
    }
}
