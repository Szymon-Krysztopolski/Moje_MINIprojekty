import java.io.*;
import java.nio.file.Files;
import java.util.*;

public class MyfileReader {
    final int Pixels_start=256; //hex(256) = 100
    final byte myEOF = (byte) 0xff;

    public byte[] readFile2Bytes(String file_in) throws IOException{
        File imgPath = new File(file_in);
        byte[] data = Files.readAllBytes(imgPath.toPath());
        return data;
    }

    public void encryptMess2Image(byte[] mess_bytes,int len, String file_image, String file_output) throws IOException{
        byte[] image_bytes = this.readFile2Bytes(file_image);

        if(Byte.SIZE*(len+Pixels_start)>image_bytes.length) {
            System.out.println("Image is too small!");
            throw new IOException();
        } else {
            for(int i=Pixels_start;i<len+Pixels_start;i++){
                byte poz = (byte) 128;
                for(int j=0;j<Byte.SIZE;j++){
                    byte bit = (byte)(mess_bytes[i-Pixels_start] & poz);

                    image_bytes[i*Byte.SIZE+j] &= 0xfe;
                    byte tmp = (byte) ((bit&0xff) >>> (Byte.SIZE-j-1));
                    image_bytes[i*Byte.SIZE+j] |= tmp;

                    poz = (byte) ((poz&0xff)>>>1);
                }
            }
            for(int j=0;j<Byte.SIZE;j++)
                image_bytes[Byte.SIZE*(Pixels_start+len)+j] |= 0x01;
            
            File outputFile = new File(file_output);
            Files.write(outputFile.toPath(), image_bytes);
        }
    }

    public void encryptFile2Image(String file_mess, String file_image, String file_output) throws IOException{
        byte[] mess_bytes = this.readFile2Bytes(file_mess);
        encryptMess2Image(mess_bytes, mess_bytes.length, file_image, file_output);
    }

    public void encryptMess2Image_key(byte[] mess_bytes, int len, String file_image, String file_output, long seed) throws IOException{
        byte[] random_bytes = this.random_key(seed, len+Byte.SIZE);
        byte[] mess_bytesEOF = new byte[mess_bytes.length+Byte.SIZE];

        for(int i=0;i<len;i++){
            mess_bytesEOF[i]=(byte) (mess_bytes[i]^random_bytes[i]);
        }
        for(int i=len;i<len+Byte.SIZE;i++){
            mess_bytesEOF[i]=(byte) (0xff^random_bytes[i]);
        }

        encryptMess2Image(mess_bytesEOF, mess_bytesEOF.length, file_image, file_output);
    }

    public void encryptFile2Image_key(String file_mess, String file_image, String file_output, long seed) throws IOException{
        byte[] mess_bytes = this.readFile2Bytes(file_mess);
        encryptMess2Image_key(mess_bytes, mess_bytes.length, file_image, file_output, seed);
    }

    //-----------------------------------------------------------------------------------------------

    public void decryptMessFromImage2File_key(String file_image, String file_output, long seed) throws IOException{
        byte[] out = decryptMessFromImage2Text_key(file_image, seed);
        File outputFile = new File(file_output);
        Files.write(outputFile.toPath(), out);
    }

    public byte[] decryptMessFromImage2Text_key(String file_image, long seed) throws IOException{
        byte[] mess_bytes = this.decryptMessFromImage2Text(file_image, 1);
        byte[] random_bytes = this.random_key(seed, mess_bytes.length);
        int i;
        for(i=0;i<mess_bytes.length;i++){
            mess_bytes[i]^=random_bytes[i];
            if(mess_bytes[i]==myEOF) break;
        }
        
        byte[] res = new byte[i];
        for(i=0;i<res.length;i++){
            res[i]=mess_bytes[i];
        }

        return res;
    }

    public void decryptMessFromImage2File(String file_image, String file_output) throws IOException{
        byte[] out = decryptMessFromImage2Text(file_image, 0);
        File outputFile = new File(file_output);
        Files.write(outputFile.toPath(), out);
    }

    public byte[] decryptMessFromImage2Text(String file_image, int mode) throws IOException{
        byte[] image_bytes = this.readFile2Bytes(file_image);
        ArrayList<Byte> mess_bytes = new ArrayList<>();

        byte myByte=0x00;
        int counter=0;

        for(int i=Pixels_start*Byte.SIZE;i<image_bytes.length;i++){
            byte bit=(byte)(image_bytes[i] & 0x01);
            myByte|=bit;
            
            if(++counter % Byte.SIZE == 0){
                if(myByte==myEOF && mode==0) break; else{ 
                    mess_bytes.add(myByte);
                    counter=0;
                    myByte=0x00;
                }
            }
            myByte<<=1;
        }
        
        byte[] out = new byte[mess_bytes.size()];
        for(int i=0;i<mess_bytes.size();i++){
            out[i]=mess_bytes.get(i);
        }

        return out;
    }

    public byte[] random_key(long seed, int len){
        byte[] tab = new byte[len];
        Random rd = new Random(seed);
        rd.nextBytes(tab);
        
        return tab;
    }
}