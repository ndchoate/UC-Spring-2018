import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FirstDatabaseForm {
    private JButton connectToDatabaseButton;
    private JButton addADeveloperInputButton;
    private JButton addLevelOfEffortButton;
    private JButton configurationFormButton;
    private JButton addANoteInputButton;
    private JButton requestReviewInputFormButton;
    private JButton updateStatusInputFormButton;
    private JButton businessReviewInputFormButton;
    private JButton reportRequestInputFormButton;
    private JButton pendingReviewInputFormButton;
    private JButton assignedInputFormButton;
    private JButton peerReviewInputFormButton;
    private JButton developmentInputFormButton;
    private JButton pendingDevelopmentInputFormButton;

    public FirstDatabaseForm() {
        connectToDatabaseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Open connect to Database form
                new ConnectForm();
                //FirstDatabaseForm.this.setVisible(false);
            }
        });
    }
}
