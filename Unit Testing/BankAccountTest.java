import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class BankAccountTest {

    private BankAccount account;

    @BeforeEach
    void setUp() {
        account = new BankAccount(1001);
    }

    @Test
    void testCreateValidAccount() {
        assertEquals(1001, account.getAccount());
    }

    @Test
    void testCreateInvalidAccount() {
        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> new BankAccount(0)
        );

        assertEquals("Account Number must be positive", exception.getMessage());
    }

    @Test
    void testGetAccount() {
        assertEquals(1001, account.getAccount());
    }

    @Test
    void testSetValidAccount() {
        account.setAccount(2002);

        assertEquals(2002, account.getAccount());
        assertEquals(0, account.getBalance());
    }

    @Test
    void testSetInvalidAccount() {

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> account.setAccount(-10)
        );

        assertEquals("Account Number must be positive", exception.getMessage());
    }

    @Test
    void testInitialBalance() {
        assertEquals(0, account.getBalance());
    }

    @Test
    void testDepositValidAmount() {

        account.deposit(500);

        assertEquals(500, account.getBalance());
    }

    @Test
    void testDepositInvalidAmount() {

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> account.deposit(0)
        );

        assertEquals("Deposit amount must be greater than 0",
                exception.getMessage());
    }

    @Test
    void testWithdrawValidAmount() {

        account.deposit(1000);

        account.withdraw(300);

        assertEquals(700, account.getBalance());
    }

    @Test
    void testWithdrawMoreThanBalance() {

        account.deposit(500);

        Exception exception = assertThrows(
                IllegalStateException.class,
                () -> account.withdraw(600)
        );

        assertEquals("Insufficient Balance",
                exception.getMessage());
    }

    @Test
    void testWithdrawInvalidAmount() {

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> account.withdraw(0)
        );

        assertEquals("Withdraw amount must be greater than 0",
                exception.getMessage());
    }
}
