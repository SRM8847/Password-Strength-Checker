import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class PasswordStrengthChecker extends JFrame {
    private JTextField passwordField;
    private JLabel resultLabel;

    public PasswordStrengthChecker() {
        setTitle("Password Strength Checker");
        setSize(600, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new GridLayout(3, 1));

        JLabel promptLabel = new JLabel("Enter a password between 8-32 characters:");
        add(promptLabel);

        passwordField = new JTextField();
        add(passwordField);

        JButton checkButton = new JButton("Check Strength");
        add(checkButton);

        resultLabel = new JLabel("", SwingConstants.CENTER);
        add(resultLabel);

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String password = passwordField.getText();
                int strengthScore = calculatePasswordStrength(password);
                resultLabel.setText("Password: " + password + " | Strength Score: " + strengthScore + "/10");
            }
        });
    }

    private int calculatePasswordStrength(String password) {
        if (password.length() < 8 || password.length() > 32) {
            return 0;
        }

        int score = 0;

        if (password.length() >= 8) score++;
        if (password.length() >= 12) score++;
        if (password.length() >= 16) score++;

        if (password.matches(".*[a-z].*")) score++;
        if (password.matches(".*[A-Z].*")) score++;
        if (password.matches(".*[0-9].*")) score++;
        if (password.matches(".*[!@#$%^&*()].*")) score++;

        if (password.length() >= 12 && password.matches(".*[a-z].*") && password.matches(".*[A-Z].*") && password.matches(".*[0-9].*") && password.matches(".*[!@#$%^&*()].*")) {
            score++;
        }

        return score;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new PasswordStrengthChecker().setVisible(true);
            }
        });
    }
}
