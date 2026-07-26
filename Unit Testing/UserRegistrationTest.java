import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class UserRegistrationTest {

    private UserRegistration registration;
    private User user;

    @BeforeEach
    void setUp() {
        registration = new UserRegistration();
        user = new User("Hasan", "hasan@gmail.com", "12345");
    }

   
    @Test
    void testAddValidUser() {

        boolean result = registration.addUser(user);

        assertTrue(result);
        assertEquals(1, registration.users.size());
    }

    @Test
    void testAddNullUser() {

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> registration.addUser(null)
        );

        assertEquals("User cannot be null", exception.getMessage());
    }

    @Test
    void testAddUserWithEmptyName() {

        User user = new User("", "abc@gmail.com", "123");

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> registration.addUser(user)
        );

        assertEquals("Name cannot be empty",
                exception.getMessage());
    }

    @Test
    void testAddUserWithEmptyEmail() {

        User user = new User("Hasan", "", "123");

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> registration.addUser(user)
        );

        assertEquals("Email cannot be empty",
                exception.getMessage());
    }

    @Test
    void testAddUserWithEmptyPassword() {

        User user = new User("Hasan", "abc@gmail.com", "");

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> registration.addUser(user)
        );

        assertEquals("Password cannot be empty",
                exception.getMessage());
    }

   
    @Test
    void testFindExistingUser() {

        registration.addUser(user);

        User foundUser = registration.findUser("hasan@gmail.com");

        assertNotNull(foundUser);
        assertEquals("Hasan", foundUser.getName());
        assertEquals("hasan@gmail.com", foundUser.getEmail());
    }

    @Test
    void testFindNonExistingUser() {

        User foundUser = registration.findUser("abc@gmail.com");

        assertNull(foundUser);
    }

    @Test
    void testFindUserWithEmptyEmail() {

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> registration.findUser("")
        );

        assertEquals("Email field is empty",
                exception.getMessage());
    }


    @Test
    void testLoginSuccess() {

        registration.addUser(user);

        boolean result = registration.login(
                "hasan@gmail.com",
                "12345"
        );

        assertTrue(result);
    }

    @Test
    void testLoginWrongPassword() {

        registration.addUser(user);

        boolean result = registration.login(
                "hasan@gmail.com",
                "wrongpassword"
        );

        assertFalse(result);
    }

    @Test
    void testLoginNonExistingUser() {

        boolean result = registration.login(
                "abc@gmail.com",
                "12345"
        );

        assertFalse(result);
    }

    @Test
    void testLoginWithEmptyEmail() {

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> registration.login("", "12345")
        );

        assertEquals("Email cannot be empty",
                exception.getMessage());
    }

    @Test
    void testLoginWithEmptyPassword() {

        Exception exception = assertThrows(
                IllegalArgumentException.class,
                () -> registration.login("hasan@gmail.com", "")
        );

        assertEquals("Password cannot be empty",
                exception.getMessage());
    }

}