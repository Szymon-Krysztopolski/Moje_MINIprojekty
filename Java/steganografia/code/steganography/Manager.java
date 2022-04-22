import java.awt.*;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import javax.swing.*;
import java.util.*;

public class Manager {
    static JLabel label_warning;

    public static void logic(JLabel lw, ArrayList<Component> c) throws IOException {
        label_warning = lw;
        int err = 0;
        String err_mess = "";
        int mode_encORdec = -1, mode_cipherType = -1;
        int is_file = 0, is_text = 0;
        Long key_seed = -1L;
        String key_seed_text = "0";

        String file_in = "", file_out = "";
        String in = "";
        JTextArea textOutArea = new JTextArea();

        set_error("");
        for (Component i : c) {
            //System.out.println(i.getName());
            if (i.getName() != null) {
                switch (i.getName()) {
                    case Window.name_textIn:
                        in = ((JTextArea) i).getText();
                        break;
                    case Window.name_textOut:
                        textOutArea = (JTextArea) i;
                        break;
                    case Window.name_fileIn:
                        if (((JTextField) i).getText().compareTo(i.getName()) == 0) {
                            err = 1;
                            err_mess = "err with " + i.getName();
                        } else {
                            file_in = ((JTextField) i).getText();
                        }
                        break;
                    case Window.name_fileOut:
                        file_out = ((JTextField) i).getText();
                        break;
                    case Window.name_keySeed:
                        key_seed_text = ((JTextField) i).getText();
                        break;
                    case Window.name_encrypt:
                        if (((JRadioButton) i).isSelected())
                            mode_encORdec = 0;
                        break;
                    case Window.name_decrypt:
                        if (((JRadioButton) i).isSelected())
                            mode_encORdec = 1;
                        break;
                    case Window.name_plaintext:
                        if (((JRadioButton) i).isSelected())
                            mode_cipherType = 0;
                        break;
                    case Window.name_ciphertext:
                        if (((JRadioButton) i).isSelected())
                            mode_cipherType = 1;
                        break;
                    case Window.name_cbFile:
                        if (((JCheckBox) i).isSelected())
                            is_file = 1;
                        break;
                    case Window.name_cbText:
                        if (((JCheckBox) i).isSelected())
                            is_text = 1;
                        break;
                }
            }
        }

        if (mode_cipherType == 1) {
            if (key_seed_text.matches("-?(0|[1-9]\\d*)") && Long.parseLong(key_seed_text) > 0) {
                key_seed = Long.parseLong(key_seed_text);
            } else {
                err = 1;
                err_mess = "problem with seed";
            }
        }

        if (is_file + is_text == 0) {
            err = 1;
            err_mess = "select minimum 1 mode: text OR/AND file";
        }

        if (err == 1) {
            set_error(err_mess);
            err = 0;
        } else {
            textOutArea.setForeground(Color.BLACK);
            MyfileReader steganography = new MyfileReader();
            if (mode_cipherType == 0) { //plaintext
                if (mode_encORdec == 0) { //encrypt
                    if(is_file==1){
                        steganography.encryptFile2Image("files/text/" + in, "files/photos/" + file_in, "files/encrypted/" + file_out);
                        textOutArea.setText("text from file, check it");
                    } else {
                        byte[] tmp = in.getBytes(StandardCharsets.UTF_8);
                        steganography.encryptMess2Image(tmp, tmp.length, "files/photos/" + file_in, "files/encrypted/" + file_out);
                        textOutArea.setText("text from TextInput, check it");
                    }
                } else if (mode_encORdec == 1) { //decrypt
                    if (is_file == 1) {
                        steganography.decryptMessFromImage2File("files/photos/" + file_in, "files/decrypted/" + file_out);
                        textOutArea.setText("check folder");
                    }
                    if (is_text == 1) {
                        byte [] tmp = steganography.decryptMessFromImage2Text("files/photos/" + file_in, 0);
                        String res = new String(tmp, StandardCharsets.UTF_8);
                        textOutArea.setText(res);
                    }
                }
            } else { //ciphertext
                if (mode_encORdec == 0) { //encrypt
                    if(is_file==1){
                        steganography.encryptFile2Image_key("files/text/" + in, "files/photos/" + file_in, "files/encrypted/" + file_out, key_seed);
                        textOutArea.setText("text from file, check it");
                    } else {
                        byte[] tmp = in.getBytes(StandardCharsets.UTF_8);
                        steganography.encryptMess2Image_key(tmp, tmp.length, "files/photos/" + file_in, "files/encrypted/" + file_out, key_seed);
                        textOutArea.setText("text from TextInput, check it");
                    }
                } else if(mode_encORdec == 1) { //decrypt
                    if(is_file==1){
                        steganography.decryptMessFromImage2File_key("files/photos/" + file_in, "files/decrypted/" + file_out, key_seed);
                        textOutArea.setText("check folder");
                    } 
                    if(is_text==1){
                        byte [] tmp = steganography.decryptMessFromImage2Text_key("files/photos/" + file_in, key_seed);
                        String res = new String(tmp, StandardCharsets.UTF_8);
                        textOutArea.setText(res);
                    }
                }
            }
        }
    }

    public static void set_error(String s) {
        label_warning.setText(s);
    }
}