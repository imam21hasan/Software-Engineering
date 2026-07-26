import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class UserRegistrationTest {

    private UserRegistration userRegistration;

    @BeforeEach
    void setUp() {
        userRegistration = new UserRegistration();
    }

    @Test
    void testAddValidUser() {
        User user = new User("Alice", "alice@example.com", "password123");
        assertTrue(userRegistration.addUser(user));
        assertEquals(user, userRegistration.findUser("alice@example.com"));
    }

    @Test
    void testAddNullUserThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> userRegistration.addUser(null));
    }

    @Test
    void testAddUserWithEmptyNameThrowsException() {
        User user = new User("", "bob@example.com", "password123");
        assertThrows(IllegalArgumentException.class, () -> userRegistration.addUser(user));
    }

    @Test
    void testAddUserWithEmptyEmailThrowsException() {
        User user = new User("Bob", "", "password123");
        assertThrows(IllegalArgumentException.class, () -> userRegistration.addUser(user));
    }

    @Test
    void testAddUserWithEmptyPasswordThrowsException() {
        User user = new User("Charlie", "charlie@example.com", "");
        assertThrows(IllegalArgumentException.class, () -> userRegistration.addUser(user));
    }

    @Test
    void testFindExistingUser() {
        User user = new User("David", "david@example.com", "securePass");
        userRegistration.addUser(user);
        assertEquals(user, userRegistration.findUser("david@example.com"));
    }

    @Test
    void testFindNonExistingUserReturnsNull() {
        assertNull(userRegistration.findUser("nonexistent@example.com"));
    }

    @Test
    void testFindUserWithEmptyEmailThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> userRegistration.findUser(""));
    }

    @Test
    void testLoginSuccess() {
        User user = new User("Eve", "eve@example.com", "mypassword");
        userRegistration.addUser(user);
        assertTrue(userRegistration.login("eve@example.com", "mypassword"));
    }

    @Test
    void testLoginFailureWrongPassword() {
        User user = new User("Frank", "frank@example.com", "correctPass");
        userRegistration.addUser(user);
        assertFalse(userRegistration.login("frank@example.com", "wrongPass"));
    }

    @Test
    void testLoginFailureNonExistingUser() {
        assertFalse(userRegistration.login("ghost@example.com", "password"));
    }

    @Test
    void testLoginWithEmptyEmailThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> userRegistration.login("", "password"));
    }

    @Test
    void testLoginWithEmptyPasswordThrowsException() {
        assertThrows(IllegalArgumentException.class, () -> userRegistration.login("user@example.com", ""));
    }
}
