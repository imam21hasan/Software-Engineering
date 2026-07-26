import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class BankAccountTest {

    private BankAccount acc;
    
    @BeforeEach
    void setup() {
    	acc=new BankAccount(100);
    }
    
    @Test
    void createValidBankAccount() {
    	assertEquals(100,acc.getAccount());
    }
    
    @Test
    void createInvalidBankAccount(){
    	Exception e=assertThrows(IllegalArgumentException.class,()-> new BankAccount(0));
    	assertEquals("Account Number must be positive",e.getLocalizedMessage());
    }
    
    @Test
    void primaryAccount() {
    	assertEquals(100,acc.getAccount());
    }
    
    @Test
    void validSetAccount() {
    	acc.setAccount(1002);
    	assertEquals(1002,acc.getAccount());
    }
    
    @Test
    void invalidSetAccount() {
    	Exception e=assertThrows(IllegalArgumentException.class,()-> acc.setAccount(0));
    	
    	assertEquals("Account Number must be positive",e.getMessage());
    }
    
    @Test
    void initailBalance() {
    	assertEquals(0,acc.getBalance());
    }
    
    @Test
    void validDeposit() {
    	acc.deposit(500);
    	
    	assertEquals(500,acc.getBalance());
    }
    
    @Test
    void invalidDeposit(){
    	Exception e=assertThrows(IllegalArgumentException.class,()-> acc.deposit(0));
    	
    	assertEquals("Deposit amount must be greater than 0",e.getMessage());
    }
    
    @Test
    void validWithdraw() {
    	acc.deposit(1000);
    	acc.withdraw(600);
    	assertEquals(400,acc.getBalance());
    }
    
    @Test
    void invalidWithdraw() {
    	Exception e=assertThrows(IllegalArgumentException.class,()->acc.withdraw(0));
    	
    	assertEquals("Withdraw amount must be greater than 0",e.getMessage());
    }
    
    @Test
    void excessWithdraw() {
    	acc.deposit(500);
    	Exception e=assertThrows(IllegalStateException.class,()->acc.withdraw(600));
    	
    	assertEquals("Insufficient Balance",e.getMessage());
    }
    
    
    
    
    
    
}