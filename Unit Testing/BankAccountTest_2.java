import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class BankAccountTest {

    BankAccount account = new BankAccount("Rakib", 5000);

    // ====================================
    // assertEquals()
    // ====================================

    @Test
    void testDepositValid() {
        account.deposit(1000);
        assertEquals(6000, account.getBalance());
    }

    @Test
    void testWithdrawValid() {
        account.withdraw(2000);
        assertEquals(3000, account.getBalance());
    }

    // ====================================
    // assertThrows()
    // ====================================

    @Test
    void testDepositInvalid() {
        assertThrows(IllegalArgumentException.class, () -> {
            account.deposit(-500);
        });
    }

    @Test
    void testWithdrawInvalid() {
        assertThrows(IllegalArgumentException.class, () -> {
            account.withdraw(10000);
        });
    }

    @Test
    void testNegativeInitialBalance() {
        assertThrows(IllegalArgumentException.class, () -> {
            new BankAccount("Rahim", -100);
        });
    }

    // ====================================
    // assertNull()
    // ====================================

    @Test
    void testAccountTypeInvalid() {
        assertNull(account.getAccountType("ABC"));
    }

    @Test
    void testAccountTypeNull() {
        assertNull(account.getAccountType(null));
    }

    // ====================================
    // assertNotNull()
    // ====================================

    @Test
    void testAccountTypeValid() {
        assertNotNull(account.getAccountType("SAV"));
    }

    @Test
    void testAccountHolderNotNull() {
        assertNotNull(account.getAccountHolder());
    }

    // ====================================
    // assertTrue()
    // ====================================

    @Test
    void testMinimumBalanceValid() {
        assertTrue(account.hasMinimumBalance());
    }

    @Test
    void testSavingsAccountValid() {
        assertTrue(account.getAccountType("SAV").equals("Savings"));
    }

    // ====================================
    // assertFalse()
    // ====================================

    @Test
    void testMinimumBalanceInvalid() {
        BankAccount acc = new BankAccount("Karim", 500);
        assertFalse(acc.hasMinimumBalance());
    }

    @Test
    void testCurrentIsNotSavings() {
        assertFalse("Savings".equals(account.getAccountType("CUR")));
    }
}
