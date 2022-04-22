import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.util.*;
import javax.swing.*;

public class Window {
    private final int MyFrame_window_width = 800;
    private final int MyFrame_window_height = 500;
    private final int button_run_width = 100;
    private final int button_run_height = 40;

    private final int text_input_width = 200;
    private final int text_input_height = 40;

    private final int RadCb_width = 100;
    private final int RadCb_height = 40;

    private final int margin = 40;
    private final int top_menu_height = 20;

    final String ph_textIn = "text input";
    final String ph_textOut = "text output";
    final String ph_fileIn = "file in";
    final String ph_fileOut = "file out";
    final String ph_keySeed = "key seed";

    final static String name_laberWarning = "warning";
    final static String name_textIn = "text input";
    final static String name_textOut = "text output";
    final static String name_fileIn = "file in";
    final static String name_fileOut = "file out";
    final static String name_keySeed = "key seed";
    final static String name_encrypt = "encrypt";
    final static String name_decrypt = "decrypt";
    final static String name_plaintext = "plain text";
    final static String name_ciphertext = "ciphertext";
    final static String name_cbFile = "file";
    final static String name_cbText = "text";
    final static String name_Butt = "best button";

    public void start() {
        // ---------------------------------
        JFrame MyFrame = new JFrame();
        MyFrame.setSize(MyFrame_window_width, MyFrame_window_height);

        // ---------------------------------
        JLabel label_warning = new JLabel();
        label_warning.setName(name_laberWarning);
        label_warning.setBounds(margin/2, 0, 2*text_input_width, text_input_height);
        MyFrame.add(label_warning);

        // ---------------------------------

        JTextArea textIn = new JTextArea(ph_textIn);
        JTextArea textOut = new JTextArea(ph_textOut);

        textIn.setBounds(
                margin,
                margin,
                MyFrame_window_width / 2 - 2 * margin,
                MyFrame_window_height / 2 - 2 * margin);
        textOut.setBounds(
                margin,
                2 * margin + (MyFrame_window_height / 2 - 2 * margin),
                MyFrame_window_width / 2 - 2 * margin,
                MyFrame_window_height / 2 - 2 * margin);
        textIn.setBorder(BorderFactory.createLineBorder(Color.black));
        textOut.setBorder(BorderFactory.createLineBorder(Color.black));

        textIn.addFocusListener((FocusListener) new MyFocusListener(textIn, ph_textIn));
        textOut.addFocusListener((FocusListener) new MyFocusListener(textOut, ph_textOut));

        textIn.setName(name_textIn);
        textOut.setName(name_textOut);

        textIn.setForeground(Color.GRAY);
        textOut.setForeground(Color.GRAY);

        MyFrame.add(textIn);
        MyFrame.add(textOut);
        // ---------------------------------

        JTextField fileIn = new JTextField(ph_fileIn);
        JTextField fileOut = new JTextField(ph_fileOut);
        JTextField keySeed = new JTextField(ph_keySeed);
        fileIn.setForeground(Color.GRAY);
        fileOut.setForeground(Color.GRAY);
        keySeed.setForeground(Color.GRAY);

        fileIn.setBounds(
                MyFrame_window_width / 2 + 2 * margin,
                margin,
                text_input_width,
                text_input_height);

        fileOut.setBounds(
                MyFrame_window_width / 2 + 2 * margin,
                2 * margin + text_input_height,
                text_input_width,
                text_input_height);

        keySeed.setBounds(
                MyFrame_window_width / 2 + 2 * margin,
                3 * margin + 2 * text_input_height,
                text_input_width,
                text_input_height);

        fileIn.addFocusListener((FocusListener) new MyFocusListener(fileIn, ph_fileIn));
        fileOut.addFocusListener((FocusListener) new MyFocusListener(fileOut, ph_fileOut));
        keySeed.addFocusListener((FocusListener) new MyFocusListener(keySeed, ph_keySeed));
        
        fileIn.setName(name_fileIn);
        fileOut.setName(name_fileOut);
        keySeed.setName(name_keySeed);

        MyFrame.add(fileIn);
        MyFrame.add(fileOut);
        MyFrame.add(keySeed);
        // ---------------------------------

        ButtonGroup g1 = new ButtonGroup();
        ButtonGroup g2 = new ButtonGroup();

        JRadioButton g1r1 = new JRadioButton("encrypt");
        JRadioButton g1r2 = new JRadioButton("decrypt");
        JRadioButton g2r1 = new JRadioButton("plain text");
        JRadioButton g2r2 = new JRadioButton("ciphertext");
        g1r1.setName(name_encrypt);
        g1r2.setName(name_decrypt);
        g2r1.setName(name_plaintext);
        g2r2.setName(name_ciphertext);

        g1r1.setBounds(
                MyFrame_window_width / 2 + 2 * margin,
                4 * margin + 3 * text_input_height,
                RadCb_width,
                RadCb_height);

        g1r2.setBounds(
                MyFrame_window_width / 2 + 2 * margin,
                4 * margin + 3 * text_input_height + RadCb_height,
                RadCb_width,
                RadCb_height);

        g2r1.setBounds(
                MyFrame_window_width / 2 + 2 * margin + RadCb_width,
                4 * margin + 3 * text_input_height,
                RadCb_width,
                RadCb_height);

        g2r2.setBounds(
                MyFrame_window_width / 2 + 2 * margin + RadCb_width,
                4 * margin + 3 * text_input_height + RadCb_height,
                RadCb_width,
                RadCb_height);

        g1r1.setSelected(true);
        g2r1.setSelected(true);

        g1.add(g1r1);
        g1.add(g1r2);
        g2.add(g2r1);
        g2.add(g2r2);

        MyFrame.add(g1r1);
        MyFrame.add(g1r2);
        MyFrame.add(g2r1);
        MyFrame.add(g2r2);
        // ---------------------------------

        JCheckBox cb_file = new JCheckBox("file");
        JCheckBox cb_text = new JCheckBox("text");
        cb_file.setName(name_cbFile);
        cb_text.setName(name_cbText);

        cb_file.setBounds(
                MyFrame_window_width / 2 + 2 * margin,
                4 * margin + 3 * text_input_height + 2 * RadCb_height,
                RadCb_width,
                RadCb_height);

        cb_text.setBounds(
                MyFrame_window_width / 2 + 2 * margin + RadCb_width,
                4 * margin + 3 * text_input_height + 2 * RadCb_height,
                RadCb_width,
                RadCb_height);

        MyFrame.add(cb_file);
        MyFrame.add(cb_text);
        // ---------------------------------

        JButton button1 = new JButton("Run");
        // button1.setMargin(new Insets(0, 0, 0, 0));
        button1.setBounds(
                MyFrame_window_width - button_run_width - margin,
                MyFrame_window_height - button_run_height - margin - top_menu_height,
                button_run_width,
                button_run_height);

        button1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                        Manager.logic(label_warning,Window.getAllComponents(MyFrame));
                } catch (IOException e1) {
                        e1.printStackTrace();
                        label_warning.setText("Error with file");
                }
            }
        });

        button1.setName("best button");
        MyFrame.add(button1);
        // ---------------------------------

        MyFrame.setLayout(null);
        MyFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MyFrame.setVisible(true);
        // ---------------------------------
    }

    public static ArrayList<Component> getAllComponents(final Container c) {
        Component[] comps = c.getComponents();
        ArrayList<Component> compList = new ArrayList<Component>();
        for (Component comp : comps) {
            compList.add(comp);
            if (comp instanceof Container)
                compList.addAll(getAllComponents((Container) comp));
        }
        return compList;
    }
}