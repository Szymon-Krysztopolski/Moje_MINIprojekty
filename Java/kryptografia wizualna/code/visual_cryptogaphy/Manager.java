import java.awt.*;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import javax.swing.*;
import java.util.*;

public class Manager {
    static JLabel label_warning;

    static String textFileIn1, textFileIn2, textFileOut;
    static int mode_encORdec = -1, is_boost = 0;

    public static void logic(JLabel lw, ArrayList<Component> c) {
        label_warning = lw;
        set_error("");

        for (Component i : c) {
            if (i.getName() != null) {
                switch (i.getName()) {
                    case Window.name_textIn1:
                        textFileIn1 = ((JTextField) i).getText();
                        break;
                    case Window.name_textIn2:
                        textFileIn2 = ((JTextField) i).getText();
                        break;
                    case Window.name_textOut:
                        textFileOut = ((JTextField) i).getText();
                        break;

                    case Window.name_Rencrypt:
                        if (((JRadioButton) i).isSelected())
                            mode_encORdec = 0;
                        break;
                    case Window.name_Rdecrypt:
                        if (((JRadioButton) i).isSelected())
                            mode_encORdec = 1;
                        break;

                    case Window.name_cbBoost:
                        if (((JCheckBox) i).isSelected())
                            is_boost = 1;
                        else
                            is_boost = 0;
                        break;
                }
            }
        }
        Visualization v = new Visualization();

        try {
            if (mode_encORdec == 0) {
                v.encryptionBMP(textFileIn1, textFileOut);
            } else {
                int mode = is_boost;
                v.decryptionBMP(textFileIn1, textFileIn2, textFileOut, mode);
            }
        } catch (IOException e1) {
            e1.printStackTrace();
            label_warning.setText("Error with file");
        }

    }

    public static void set_error(String s) {
        label_warning.setText(s);
    }
}
