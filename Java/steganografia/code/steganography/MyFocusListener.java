import javax.swing.text.JTextComponent;
import java.awt.*;
import java.awt.event.*;

public class MyFocusListener implements FocusListener{
    private String text;
    private JTextComponent ob;

    MyFocusListener(JTextComponent ob,String text){
        this.text=text;
        this.ob=ob;
    }

    @Override
    public void focusGained(FocusEvent e) {
        if (ob.getText().equals(text)) {
            ob.setText("");
            ob.setForeground(Color.BLACK);
        }
    }
    @Override
    public void focusLost(FocusEvent e) {
        if (ob.getText().isEmpty()) {
            ob.setText(text);
            ob.setForeground(Color.GRAY);
        }
    };
}
