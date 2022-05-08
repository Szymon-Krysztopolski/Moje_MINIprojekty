import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.util.*;
import javax.swing.*;


public class Window {
    private final static int MyFrame_window_width = 600;
    private final static int MyFrame_window_height = 400;
    private final static int button_run_width = 100;
    private final static int button_run_height = 40;

    private final static int text_input_width = 200;
    private final static int text_input_height = 40;

    private static final int RadCb_width = 100;
    private static final int RadCb_height = 40;

    private static final int margin = 40;
    private static final int top_menu_height = 20;


    final static String name_textIn1="fileIn1";
    final static String name_textIn2="fileIn2";
    final static String name_textOut="fileOut";
    final static String name_Rencrypt="encrypt";
    final static String name_Rdecrypt="decrypt";
    final static String name_cbBoost="boost";

    public static void start() {
        JFrame MyFrame = new JFrame();
        MyFrame.setTitle("visual cryptography");
        MyFrame.setSize(MyFrame_window_width, MyFrame_window_height);
        // ---------------------------------------------------------

        JTextField fileIn1 = new JTextField();
        JTextField fileIn2 = new JTextField();
        JTextField fileOut = new JTextField();

        fileIn1.setName(name_textIn1);
        fileIn2.setName(name_textIn2);
        fileOut.setName(name_textOut);

        fileIn1.setBounds(
            2 * margin,
            margin,
            text_input_width,
            text_input_height);

        fileIn2.setBounds(
            2 * margin,
            2 * margin + text_input_height,
            text_input_width,
            text_input_height);

        fileOut.setBounds(
            2 * margin,
            3 * margin + 2 * text_input_height,
            text_input_width,
            text_input_height);

        MyFrame.add(fileIn1);
        MyFrame.add(fileIn2);
        MyFrame.add(fileOut);
        // ---------------------------------------------------------
        JLabel label_warning = new JLabel();
        // label_warning.setName(name_laberWarning);
        label_warning.setBounds(margin / 2, 4 * margin + 3 * text_input_height, 2 * text_input_width,
                text_input_height);

        JLabel label_fileIn1 = new JLabel("fileIn1");
        JLabel label_fileIn2 = new JLabel("fileIn2");
        JLabel label_fileOut = new JLabel("fileOut");

        label_fileIn1.setBounds(2 * margin, margin - text_input_height, 2 * text_input_width, text_input_height);
        label_fileIn2.setBounds(2 * margin, 2 * margin, 2 * text_input_width, text_input_height);
        label_fileOut.setBounds(2 * margin, 3 * margin + text_input_height, 2 * text_input_width, text_input_height);

        MyFrame.add(label_fileIn1);
        MyFrame.add(label_fileIn2);
        MyFrame.add(label_fileOut);
        MyFrame.add(label_warning);
        // ---------------------------------------------------------
        JCheckBox cb = new JCheckBox("Boost");
        cb.setName(name_cbBoost);

        cb.setBounds(
            MyFrame_window_width / 2 + 2 * margin,
            margin + 2 * RadCb_height,
            RadCb_width,
            RadCb_height);

        MyFrame.add(cb);
        // ---------------------------------------------------------
        ButtonGroup g1 = new ButtonGroup();

        JRadioButton r1 = new JRadioButton(name_Rencrypt);
        JRadioButton r2 = new JRadioButton(name_Rdecrypt);

        r1.setName(name_Rencrypt);
        r2.setName(name_Rdecrypt);

        r1.setBounds(
            MyFrame_window_width / 2 + 2 * margin,
            margin,
            RadCb_width,
            RadCb_height);

        r2.setBounds(
            MyFrame_window_width / 2 + 2 * margin,
            margin + RadCb_height,
            RadCb_width,
            RadCb_height);

        r1.setSelected(true);

        g1.add(r1);
        g1.add(r2);

        MyFrame.add(r1);
        MyFrame.add(r2);
        // ---------------------------------------------------------
        JButton button1 = new JButton("Run");

        button1.setBounds(
            MyFrame_window_width - button_run_width - margin,
            MyFrame_window_height - button_run_height - margin - top_menu_height,
            button_run_width,
            button_run_height);

        button1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Manager.logic(label_warning, Window.getAllComponents(MyFrame));
            }
        });

        MyFrame.add(button1);
        // ---------------------------------------------------------
        MyFrame.setLayout(null);
        MyFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MyFrame.setVisible(true);
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
